"""lgpc_chunk.py - LGPC localized text/dialogue table.

LGPC is loaded by sub_558DB0 into dword_6DA334/dword_6DA338.  Runtime text
lookup uses a column/dialogue index and a selected row; in the tested Italian
PC WADs row 0 is the visible localized line and row 1 is a "#..." voice/id tag.
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class LgpcEntry:
    column: int
    row: int
    entry_index: int
    byte_size: int
    raw: bytes
    text: str

    @property
    def voice_tag(self) -> str:
        return self.text[1:] if self.text.startswith("#") else ""


@dataclass(frozen=True)
class LgpcChunk:
    row_count_minus_one: int
    column_count: int
    unknown_header_08: int
    entries: list[LgpcEntry]
    raw_size: int

    @property
    def row_count(self) -> int:
        return self.row_count_minus_one + 1

    @property
    def entry_count(self) -> int:
        return self.row_count * self.column_count

    def get(self, column: int, row: int) -> LgpcEntry | None:
        if column < 0 or column >= self.column_count or row < 0 or row >= self.row_count:
            return None
        return self.entries[column * self.row_count + row]


def _decode_entry(raw: bytes) -> str:
    return raw.split(b"\x00", 1)[0].decode("latin-1", errors="replace")


def parse_lgpc_chunk(data: bytes) -> LgpcChunk:
    if len(data) < 12:
        raise ValueError(f"LGPC chunk is too small: {len(data)} bytes")

    row_count_minus_one, column_count, unknown_header_08 = struct.unpack_from("<III", data, 0)
    row_count = row_count_minus_one + 1
    entry_count = row_count * column_count
    sizes_off = 12
    data_off = sizes_off + entry_count * 4
    if data_off > len(data):
        raise ValueError(f"LGPC size table needs {data_off} bytes, chunk has {len(data)}")

    sizes = [struct.unpack_from("<I", data, sizes_off + i * 4)[0] for i in range(entry_count)]
    payload_size = sum(sizes)
    if data_off + payload_size != len(data):
        raise ValueError(
            f"LGPC payload size mismatch: header+sizes={data_off}, payload={payload_size}, chunk={len(data)}"
        )

    entries: list[LgpcEntry] = []
    off = data_off
    for i, size in enumerate(sizes):
        raw = data[off:off + size]
        column = i // row_count
        row = i % row_count
        entries.append(LgpcEntry(column, row, i, size, raw, _decode_entry(raw)))
        off += size

    return LgpcChunk(row_count_minus_one, column_count, unknown_header_08, entries, len(data))


def export_lgpc(lgpc: LgpcChunk, out_dir: Path) -> dict:
    out_dir.mkdir(parents=True, exist_ok=True)
    payload_size = sum(entry.byte_size for entry in lgpc.entries)
    summary = {
        "raw_size": lgpc.raw_size,
        "row_count_minus_one": lgpc.row_count_minus_one,
        "row_count": lgpc.row_count,
        "column_count": lgpc.column_count,
        "entry_count": lgpc.entry_count,
        "unknown_header_08": lgpc.unknown_header_08,
        "payload_size": payload_size,
        "confirmed_loader": "LGPC first u32 is incremented into dword_6DA338; dword_6DA334 is a pointer matrix of row_count*column_count string blobs.",
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    with (out_dir / "entries.csv").open("w", newline="", encoding="utf-8") as f:
        fieldnames = ["column", "row", "entry_index", "byte_size", "voice_tag", "text"]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for entry in lgpc.entries:
            w.writerow({
                "column": entry.column,
                "row": entry.row,
                "entry_index": entry.entry_index,
                "byte_size": entry.byte_size,
                "voice_tag": entry.voice_tag,
                "text": entry.text,
            })

    with (out_dir / "dialogue_lines.csv").open("w", newline="", encoding="utf-8") as f:
        fieldnames = ["line_index", "text", "voice_tag", "text_size", "voice_tag_size"]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for column in range(lgpc.column_count):
            text_entry = lgpc.get(column, 0)
            voice_entry = lgpc.get(column, lgpc.row_count - 1)
            w.writerow({
                "line_index": column,
                "text": text_entry.text if text_entry is not None else "",
                "voice_tag": voice_entry.voice_tag if voice_entry is not None else "",
                "text_size": text_entry.byte_size if text_entry is not None else "",
                "voice_tag_size": voice_entry.byte_size if voice_entry is not None else "",
            })

    return summary
