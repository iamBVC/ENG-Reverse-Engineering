"""
SMPC chunk parser/exporter.

SMPC is the level sound/music chunk.  The four-byte WAD tag is stored as
CPMS on disk (byte-reversed).  The human-readable tag is SMPC.

Loader traced from the executable:

    sub_558D30(FILE *Stream, int *ElementSize)
        - reads u32 sound_count into [edi+0x1C]
        - if non-zero: calls sub_545350(ElementSize, Stream, mode=1)
        - if zero:     stores 0 at [edi+0x18]

    sub_545350(int *ElementSize, FILE *Stream, int mode)
        case 1 (SMPC path):
        - allocates sound_count * 24-byte runtime slots at [edi+0x18]
        - for each sound:
              reads u32 resource_type  (always 0x20677663 = "cvg ")
              reads u32 data_size      (total bytes including 20-byte CVG header)
              reads data_size bytes into a heap buffer
              calls _AAL_LoadResource(buffer, data_size) -> handle
              queries _AAL_GetSampleRate, _AAL_GetADSVolume,
                      _AAL_GetADSFlags, _AAL_GetLoopType
              stores runtime slot: data_size, sample_rate_fp, volume,
                                   flags, loop_type, buffer_ptr, aal_handle

On-disk layout (confirmed from binary survey of t1l1m001 — 56 sounds,
241,332 bytes total):

    struct SMPCChunk {
        uint32_t sound_count;
        SMPCEntry entries[sound_count];
    };

    struct SMPCEntry {
        uint32_t resource_type;   // always 0x20677763 = "cvg "
        uint32_t data_size;       // byte count of what follows (incl. CVG header)
        CvgHeader header;         // 20 bytes
        uint8_t  audio_data[data_size - 20];
    };

CVG header (20 bytes, Argonaut proprietary audio container):

    +0x00  u32  sample_rate      e.g. 8000, 11025, 22050, 38000
    +0x04  u16  block_align      scales with rate: 11025->1024, 22050->2048
    +0x06  u16  codec_quality    127 most common; 25/45/50/60/85 also seen
    +0x08  u32  channels         1=mono (common); 65793 appears for some entries
    +0x0C  u16  amplitude        143 (0x8F) or 255 (0xFF)
    +0x0E  u16  unknown_0E       66 most common, 68-70 also seen
    +0x10  u32  audio_data_size  always equals data_size - 20

The audio encoding used inside the CVG blob is undocumented here; it is
handled entirely by the AAL (Argonaut Audio Library).  The raw bytes are
preserved verbatim by this parser.
"""

from __future__ import annotations

import csv
import struct
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

CVG_MAGIC = 0x20677663  # "cvg " as little-endian u32
CVG_HEADER_SIZE = 20
SMPC_ENTRY_OVERHEAD = 8  # resource_type (4) + data_size (4)


# ---------------------------------------------------------------------------
# Decoded structures
# ---------------------------------------------------------------------------

@dataclass
class CvgHeader:
    """20-byte CVG audio container header."""
    sample_rate: int
    block_align: int
    codec_quality: int
    channels: int
    amplitude: int
    unknown_0E: int
    audio_data_size: int


@dataclass
class SmpcSound:
    """One SMPC sound entry with its CVG header and raw audio payload."""
    index: int
    file_offset: int        # byte offset of the resource_type field in the chunk
    resource_type: int      # always CVG_MAGIC
    data_size: int          # total bytes after resource_type/data_size fields
    header: CvgHeader
    audio_data: bytes       # raw encoded audio (length == header.audio_data_size)

    @property
    def resource_tag(self) -> str:
        b = struct.pack("<I", self.resource_type)
        return b.decode("ascii", errors="replace")

    @property
    def total_entry_bytes(self) -> int:
        return SMPC_ENTRY_OVERHEAD + self.data_size


@dataclass
class SmpcChunk:
    """Parsed SMPC chunk."""
    sound_count: int
    sounds: List[SmpcSound] = field(default_factory=list)


# ---------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------

def parse(data: bytes | memoryview, base_offset: int = 0) -> SmpcChunk:
    """Parse a raw SMPC chunk blob (everything after the WAD chunk header).

    ``base_offset`` is added to all reported ``file_offset`` values so
    callers that work with the full WAD file can correlate positions.
    """
    view = memoryview(data) if not isinstance(data, memoryview) else data
    pos = 0

    def read_u16() -> int:
        nonlocal pos
        (v,) = struct.unpack_from("<H", view, pos)
        pos += 2
        return v

    def read_u32() -> int:
        nonlocal pos
        (v,) = struct.unpack_from("<I", view, pos)
        pos += 4
        return v

    sound_count = read_u32()
    chunk = SmpcChunk(sound_count=sound_count)

    for i in range(sound_count):
        entry_start = base_offset + pos

        resource_type = read_u32()
        data_size = read_u32()

        if data_size < CVG_HEADER_SIZE:
            raise ValueError(
                f"Sound {i} at 0x{entry_start:08X}: data_size={data_size} < "
                f"CVG_HEADER_SIZE={CVG_HEADER_SIZE}"
            )

        # --- CVG header ---
        sample_rate = read_u32()
        block_align = read_u16()
        codec_quality = read_u16()
        channels = read_u32()
        amplitude = read_u16()
        unknown_0E = read_u16()
        audio_data_size = read_u32()

        expected_audio = data_size - CVG_HEADER_SIZE
        if audio_data_size != expected_audio:
            raise ValueError(
                f"Sound {i}: CVG audio_data_size={audio_data_size} != "
                f"data_size-{CVG_HEADER_SIZE}={expected_audio}"
            )

        # --- raw audio payload ---
        audio_data = bytes(view[pos : pos + audio_data_size])
        pos += audio_data_size

        cvg_hdr = CvgHeader(
            sample_rate=sample_rate,
            block_align=block_align,
            codec_quality=codec_quality,
            channels=channels,
            amplitude=amplitude,
            unknown_0E=unknown_0E,
            audio_data_size=audio_data_size,
        )
        chunk.sounds.append(
            SmpcSound(
                index=i,
                file_offset=entry_start,
                resource_type=resource_type,
                data_size=data_size,
                header=cvg_hdr,
                audio_data=audio_data,
            )
        )

    return chunk


# ---------------------------------------------------------------------------
# Exporters
# ---------------------------------------------------------------------------

def export_sounds(chunk: SmpcChunk, out_dir: Path) -> None:
    """Write each sound as a raw .cvg file (header + audio data).

    The file contains the original CVG header followed by the raw encoded
    audio bytes, identical to what the game passes to _AAL_LoadResource.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    for snd in chunk.sounds:
        cvg_path = out_dir / f"sound_{snd.index:03d}.cvg"
        with open(cvg_path, "wb") as f:
            # Reconstruct the exact bytes the game reads: header then audio
            f.write(struct.pack("<I", snd.resource_type))
            f.write(struct.pack("<I", snd.data_size))
            hdr = snd.header
            f.write(struct.pack(
                "<IHHIHHi",
                hdr.sample_rate,
                hdr.block_align,
                hdr.codec_quality,
                hdr.channels,
                hdr.amplitude,
                hdr.unknown_0E,
                hdr.audio_data_size,
            ))
            f.write(snd.audio_data)


def export_manifest_csv(chunk: SmpcChunk, csv_path: Path) -> None:
    """Write a CSV manifest of all sounds with their CVG header fields."""
    csv_path.parent.mkdir(parents=True, exist_ok=True)
    with open(csv_path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=[
            "index", "file_offset", "resource_tag",
            "data_size", "sample_rate", "block_align",
            "codec_quality", "channels", "amplitude",
            "unknown_0E", "audio_data_size",
        ])
        writer.writeheader()
        for snd in chunk.sounds:
            hdr = snd.header
            writer.writerow({
                "index": snd.index,
                "file_offset": f"0x{snd.file_offset:08X}",
                "resource_tag": snd.resource_tag,
                "data_size": snd.data_size,
                "sample_rate": hdr.sample_rate,
                "block_align": hdr.block_align,
                "codec_quality": hdr.codec_quality,
                "channels": hdr.channels,
                "amplitude": hdr.amplitude,
                "unknown_0E": hdr.unknown_0E,
                "audio_data_size": hdr.audio_data_size,
            })


def export_raw_audio(chunk: SmpcChunk, out_dir: Path) -> None:
    """Write only the raw audio payloads (no CVG header) as .bin files.

    These are the encoded audio bytes that AAL decodes internally.
    Useful for format research — e.g. comparing against known ADPCM patterns.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    for snd in chunk.sounds:
        bin_path = out_dir / f"sound_{snd.index:03d}_audio.bin"
        bin_path.write_bytes(snd.audio_data)


def export_all(chunk: SmpcChunk, out_dir: Path) -> None:
    """Run all exporters: .cvg files, manifest CSV, and raw audio bins."""
    export_sounds(chunk, out_dir / "cvg")
    export_manifest_csv(chunk, out_dir / "smpc_manifest.csv")
    export_raw_audio(chunk, out_dir / "raw_audio")


# ---------------------------------------------------------------------------
# Summary helper
# ---------------------------------------------------------------------------

def print_summary(chunk: SmpcChunk) -> None:
    """Print a human-readable summary of the parsed SMPC chunk."""
    print(f"SMPC: {chunk.sound_count} sounds")
    for snd in chunk.sounds:
        hdr = snd.header
        mono_str = "mono" if hdr.channels == 1 else f"ch={hdr.channels}"
        print(
            f"  [{snd.index:3d}] @0x{snd.file_offset:08X}  "
            f"{hdr.sample_rate:5d}Hz  {mono_str:12s}  "
            f"quality={hdr.codec_quality:3d}  "
            f"audio={hdr.audio_data_size:6d}B  "
            f"tag={snd.resource_tag!r}"
        )
