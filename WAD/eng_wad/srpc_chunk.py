"""srpc_chunk.py — CPRS/SRPC streamed speech table parser/exporter.

EXE-backed reverse engineering summary:

* WAD tag 0x53525043 appears as human label ``SRPC`` in this tool.
* The original loader calls ``sub_545350(level_context, stream, 2)``.
* Case 2 reads ``count`` then ``count * 16`` bytes into ``dword_6D91C4``.
* Runtime playback (``sub_546620``) treats entries as slices of
  ``Music/ENGLISH.CVS`` and sends each slice to AAL as resource type 0x15.
* The CVS slices are PlayStation/SPU ADPCM frames: 16 bytes per frame,
  28 mono samples per frame. ``rate_or_timing`` converts to Hz as
  ``rate_or_timing * 44100 / 4096``; 2048 therefore means 22050 Hz.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import csv
import shutil
import subprocess
import wave

from .binary import Reader


@dataclass(frozen=True)
class SRPCEntry:
    index: int
    unknown_00: int
    rate_or_timing: int
    unknown_06: int
    cvs_offset: int
    cvs_size: int

    @property
    def cvs_aligned_size(self) -> int:
        """Runtime aligns the stream size up to 0x800 before AAL load."""
        return (self.cvs_size + 0x7FF) & ~0x7FF

    @property
    def sample_rate(self) -> int:
        # sub_546620 computes approximately rate_or_timing * 44100 / 4096.
        return int((self.rate_or_timing * 44100) // 4096)

    @property
    def spu_frame_count(self) -> int:
        return self.cvs_size // 16

    @property
    def sample_count(self) -> int:
        return self.spu_frame_count * 28

    @property
    def duration_seconds(self) -> float:
        sr = self.sample_rate
        return self.sample_count / sr if sr else 0.0


@dataclass(frozen=True)
class SRPCChunk:
    count: int
    entries: list[SRPCEntry]


def parse_srpc_chunk(data: bytes) -> SRPCChunk:
    r = Reader(data)
    count = r.u32()
    entries: list[SRPCEntry] = []
    for i in range(count):
        unknown_00 = r.u32()
        rate_or_timing = r.u16()
        unknown_06 = r.u16()
        cvs_offset = r.u32()
        cvs_size = r.u32()
        entries.append(
            SRPCEntry(
                index=i,
                unknown_00=unknown_00,
                rate_or_timing=rate_or_timing,
                unknown_06=unknown_06,
                cvs_offset=cvs_offset,
                cvs_size=cvs_size,
            )
        )
    return SRPCChunk(count=count, entries=entries)


_PSX_FILTERS: tuple[tuple[int, int], ...] = (
    (0, 0),
    (60, 0),
    (115, -52),
    (98, -55),
    (122, -60),
)


def decode_psx_spu_adpcm_mono(data: bytes) -> list[int]:
    """Decode mono PlayStation/SPU ADPCM frames to signed 16-bit PCM samples.

    Each frame is 16 bytes and produces 28 samples. The decoder accepts slices
    with padding; trailing bytes after the last full frame are ignored.
    """
    hist1 = 0
    hist2 = 0
    out: list[int] = []

    full_len = len(data) - (len(data) % 16)
    for off in range(0, full_len, 16):
        header = data[off]
        shift = header & 0x0F
        filt = (header >> 4) & 0x0F
        if filt >= len(_PSX_FILTERS):
            filt = 0
        f0, f1 = _PSX_FILTERS[filt]

        for byte in data[off + 2: off + 16]:
            for nibble in (byte & 0x0F, byte >> 4):
                if nibble >= 8:
                    nibble -= 16
                sample = (nibble << 12) >> shift
                sample += ((hist1 * f0 + hist2 * f1 + 32) >> 6)
                if sample > 32767:
                    sample = 32767
                elif sample < -32768:
                    sample = -32768
                out.append(sample)
                hist2 = hist1
                hist1 = sample
    return out


def write_wav_from_pcm16_mono(samples: list[int], sample_rate: int, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with wave.open(str(path), "wb") as wav:
        wav.setnchannels(1)
        wav.setsampwidth(2)
        wav.setframerate(sample_rate)
        wav.writeframes(b"".join(int(s).to_bytes(2, "little", signed=True) for s in samples))


def _convert_wav_to_mp3(wav_path: Path, mp3_path: Path) -> bool:
    ffmpeg = shutil.which("ffmpeg")
    if not ffmpeg:
        return False
    mp3_path.parent.mkdir(parents=True, exist_ok=True)
    try:
        subprocess.run(
            [ffmpeg, "-hide_banner", "-loglevel", "error", "-y", "-i", str(wav_path), str(mp3_path)],
            check=True,
        )
        return True
    except Exception:
        return False


def find_cvs_for_wad(wad_path: Path, explicit_path: Path | None = None) -> Path | None:
    """Find a likely localized CVS stream file for SRPC speech exports."""
    if explicit_path:
        return explicit_path if explicit_path.exists() else None

    candidates = [
        wad_path.parent / "Music" / "ENGLISH.CVS",
        wad_path.parent / "Music" / "english.CVS",
        wad_path.parent / "ENGLISH.CVS",
        wad_path.parent / "english.CVS",
        Path.cwd() / "Music" / "ENGLISH.CVS",
        Path.cwd() / "english.CVS",
    ]
    for p in candidates:
        if p.exists():
            return p
    return None


def export_srpc(
    srpc: SRPCChunk,
    out_dir: Path,
    *,
    cvs_path: Path | None = None,
    export_slices: bool = True,
    export_wav: bool = True,
    export_mp3: bool = False,
) -> dict[str, int | bool | str]:
    """Export SRPC metadata and, when CVS is available, decoded speech files."""
    out_dir.mkdir(parents=True, exist_ok=True)
    csv_path = out_dir / "srpc_entries.csv"
    with csv_path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "index",
            "unknown_00",
            "rate_or_timing",
            "unknown_06",
            "cvs_offset",
            "cvs_size",
            "cvs_aligned_size_runtime",
            "sample_rate_hz",
            "spu_frame_count",
            "sample_count",
            "duration_seconds",
            "cvs_range_valid",
        ])
        cvs_len = cvs_path.stat().st_size if cvs_path and cvs_path.exists() else None
        for e in srpc.entries:
            valid = cvs_len is not None and e.cvs_offset >= 0 and e.cvs_offset + e.cvs_size <= cvs_len
            w.writerow([
                e.index,
                e.unknown_00,
                e.rate_or_timing,
                e.unknown_06,
                e.cvs_offset,
                e.cvs_size,
                e.cvs_aligned_size,
                e.sample_rate,
                e.spu_frame_count,
                e.sample_count,
                f"{e.duration_seconds:.6f}",
                int(bool(valid)),
            ])

    summary_lines = [
        "SRPC / CPRS streamed speech table",
        "==================================",
        "",
        f"Entries: {srpc.count}",
        "Disk entry size: 16 bytes",
        "Runtime file: Music/ENGLISH.CVS or localized equivalent",
        "Codec: PlayStation/SPU ADPCM, mono, 16-byte frames, 28 samples/frame",
        "Sample rate: rate_or_timing * 44100 / 4096",
        "Runtime AAL resource type: 0x15",
        "",
        "Struct:",
        "  u32 unknown_00",
        "  u16 rate_or_timing",
        "  u16 unknown_06",
        "  u32 cvs_offset",
        "  u32 cvs_size",
        "",
    ]

    written_slices = 0
    written_wav = 0
    written_mp3 = 0
    mp3_requested_but_unavailable = False

    if cvs_path and cvs_path.exists():
        cvs_data = cvs_path.read_bytes()
        summary_lines.append(f"CVS source: {cvs_path}")
        summary_lines.append(f"CVS size: {len(cvs_data):,} bytes")
        for e in srpc.entries:
            if e.cvs_offset + e.cvs_size > len(cvs_data):
                continue
            raw = cvs_data[e.cvs_offset:e.cvs_offset + e.cvs_size]
            stem = f"speech_{e.index:04d}_id_{e.unknown_00:04d}"
            if export_slices:
                p = out_dir / "cvs_slices" / f"{stem}.cvs"
                p.parent.mkdir(parents=True, exist_ok=True)
                p.write_bytes(raw)
                written_slices += 1
            wav_path: Path | None = None
            if export_wav or export_mp3:
                samples = decode_psx_spu_adpcm_mono(raw)
                wav_path = out_dir / "wav" / f"{stem}.wav"
                write_wav_from_pcm16_mono(samples, e.sample_rate, wav_path)
                written_wav += 1
            if export_mp3 and wav_path:
                ok = _convert_wav_to_mp3(wav_path, out_dir / "mp3" / f"{stem}.mp3")
                if ok:
                    written_mp3 += 1
                else:
                    mp3_requested_but_unavailable = True
    else:
        summary_lines.append("CVS source: not found/provided; exported metadata only.")

    summary_lines += [
        "",
        f"CVS slices written: {written_slices}",
        f"WAV files written: {written_wav}",
        f"MP3 files written: {written_mp3}",
    ]
    if mp3_requested_but_unavailable:
        summary_lines.append("MP3 note: ffmpeg was not available or conversion failed for at least one file.")
    (out_dir / "summary.txt").write_text("\n".join(summary_lines) + "\n", encoding="utf-8")

    return {
        "entries": srpc.count,
        "slices": written_slices,
        "wav": written_wav,
        "mp3": written_mp3,
        "cvs_found": bool(cvs_path and cvs_path.exists()),
        "mp3_unavailable": mp3_requested_but_unavailable,
    }
