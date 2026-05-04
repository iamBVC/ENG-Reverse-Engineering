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

CVG header (20 bytes, PC variant):

    +0x00  u32  sample_rate      e.g. 8000, 11025, 22050, 38000
    +0x04  u16  block_align      AAL streaming PCM output buffer size (~46 ms at
                                 the given rate); NOT the codec block size
    +0x06  u16  codec_quality    127 most common; 25/45/50/60/85 also seen;
                                 semantic meaning unclear (not standard ADPCM param)
    +0x08  u32  channels         1=mono; non-1 values (e.g. 65793, 529) have
                                 unclear encoding — treated as mono when decoding
    +0x0C  u16  amplitude        runtime volume scale used by AAL; 143 or 255
    +0x0E  u16  unknown_0E       66 most common, 68-70 also seen
    +0x10  u32  audio_data_size  always equals data_size - 20; always divisible
                                 by 16 (one PSX ADPCM block = 16 bytes)

Audio codec: PlayStation SPU ADPCM (AV_CODEC_ID_ADPCM_PSX).
Confirmed by: (a) all audio_data_size values are divisible by 16, and
(b) FFmpeg libavformat/argo_cvg.c uses ADPCM_PSX for CVG files.
Each 16-byte block decodes to 28 signed 16-bit PCM samples.
The PS1 CVG format uses a 12-byte header; the PC variant here uses 20 bytes
that add explicit sample_rate and AAL-specific fields.
"""

from __future__ import annotations

import array
import csv
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import List

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
# PSX ADPCM decoder (WAV export)
# ---------------------------------------------------------------------------
# CVG audio data uses PlayStation SPU ADPCM, confirmed by:
#   1. All audio_data_size values are exactly divisible by 16 (the PSX block size)
#   2. FFmpeg libavformat/argo_cvg.c uses AV_CODEC_ID_ADPCM_PSX for CVG files
#   3. No IMA step tables exist in groove.exe — decoding is done by the AAL DLL
#
# PSX ADPCM block layout (16 bytes → 28 PCM16 samples):
#   byte 0:   shift_factor (bits 0-3) | filter_index (bits 4-7)
#   byte 1:   loop/flag bits (bit 0 = loop_end, bit 1 = loop_repeat, bit 2 = loop_start)
#   bytes 2-15: 14 bytes of 4-bit ADPCM nibbles, low nibble first per byte (28 nibbles)
#
# CVG block_align is NOT the codec block size.  It is the AAL streaming PCM output
# buffer size (always ~46 ms: block_align / (2 * sample_rate) ≈ 0.046 s).

_PSX_FILTER = [
    (  0,   0),
    ( 60,   0),
    (115, -52),
    ( 98, -55),
    (122, -60),
]
PSX_BLOCK_SIZE = 16
PSX_SAMPLES_PER_BLOCK = 28


def _decode_psx_adpcm(data: bytes) -> array.array:
    """Decode PSX ADPCM (SPU/XA-ADPCM) to signed 16-bit PCM samples.

    Per nibble decode:
      sample = (sign_extend(nibble, 4) << 12 >> shift)
               + (f1 * prev1 + f2 * prev2 + 32) // 64
      clamp to [-32768, 32767]
    """
    samples: list[int] = []
    prev1 = prev2 = 0
    length = len(data)
    pos = 0

    while pos + PSX_BLOCK_SIZE <= length:
        byte0 = data[pos]
        shift = byte0 & 0xF
        fi = min((byte0 >> 4) & 0xF, 4)
        flag = data[pos + 1] & 0x7
        f1, f2 = _PSX_FILTER[fi]
        pos += 2

        for _ in range(14):
            byte = data[pos]; pos += 1
            for nibble in (byte & 0x0F, (byte >> 4) & 0x0F):
                if flag >= 7:
                    s = 0
                else:
                    n4 = nibble if nibble < 8 else nibble - 16  # sign-extend 4-bit
                    s = (n4 << 12) >> shift
                    s = s + (f1 * prev1 + f2 * prev2 + 32) // 64
                    s = max(-32768, min(32767, s))
                prev2, prev1 = prev1, s
                samples.append(s)

    return array.array("h", samples)


def _write_wav_pcm16(path: Path, pcm: array.array, sample_rate: int) -> None:
    """Write a minimal mono 16-bit PCM WAV file."""
    if sys.byteorder != "little":
        pcm = array.array("h", pcm)
        pcm.byteswap()
    data_bytes = len(pcm) * 2
    with open(path, "wb") as f:
        f.write(b"RIFF")
        f.write(struct.pack("<I", 36 + data_bytes))
        f.write(b"WAVE")
        f.write(b"fmt ")
        f.write(struct.pack("<I", 16))
        f.write(struct.pack("<HH", 1, 1))             # PCM, mono
        f.write(struct.pack("<II", sample_rate, sample_rate * 2))  # rate, byte rate
        f.write(struct.pack("<HH", 2, 16))            # block align, bits/sample
        f.write(b"data")
        f.write(struct.pack("<I", data_bytes))
        pcm.tofile(f)


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


def export_wav(chunk: SmpcChunk, out_dir: Path) -> None:
    """Export sounds as WAV files decoded from PSX ADPCM.

    CVG audio data uses PlayStation SPU ADPCM (AV_CODEC_ID_ADPCM_PSX),
    confirmed by the 16-byte-aligned block structure and FFmpeg's argo_cvg.c.
    All sounds are decoded as mono; ``channels`` field values other than 1
    have unclear encoding and are treated as mono pending further analysis.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    for snd in chunk.sounds:
        wav_path = out_dir / f"sound_{snd.index:03d}.wav"
        try:
            pcm = _decode_psx_adpcm(snd.audio_data)
            if pcm:
                _write_wav_pcm16(wav_path, pcm, snd.header.sample_rate)
        except Exception:
            pass


def export_all(chunk: SmpcChunk, out_dir: Path) -> None:
    """Run all exporters: .cvg files, manifest CSV, raw audio bins, and WAV."""
    export_sounds(chunk, out_dir / "cvg")
    export_manifest_csv(chunk, out_dir / "smpc_manifest.csv")
    export_raw_audio(chunk, out_dir / "raw_audio")
    export_wav(chunk, out_dir / "wav")


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
