"""raw_export.py — export chunks that are not fully decoded yet."""

from __future__ import annotations

from pathlib import Path


RAW_EXPORTS = {
    "FONT": "font.bin",
    "AMPC": "ambient_audio.bin",
    "TRAK": "trak.bin",
    "STPC": "stpc.bin",
    "SMPC": "smpc.bin",
    "SRPC": "srpc.bin",
    "LGPC": "lgpc.bin",
    "WFPC": "wfpc.bin",
}


def export_raw_chunk(tag: str, data: bytes, raw_dir: Path) -> Path:
    """Write raw bytes for a not-yet-decoded or partially decoded chunk."""
    raw_dir.mkdir(parents=True, exist_ok=True)
    filename = RAW_EXPORTS.get(tag, f"{tag.strip().lower() or 'chunk'}.bin")
    path = raw_dir / filename
    path.write_bytes(data)
    return path
