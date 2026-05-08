"""memory_wad.py - RAM-backed editable WAD chunk store."""

from __future__ import annotations

import struct
from pathlib import Path

from .wad import WadChunk


class MemoryWad:
    """Keep editable WAD chunks in RAM instead of a temporary work folder."""

    def __init__(self, wad_path: Path) -> None:
        self.wad_path = wad_path
        self.entries: list[dict] = []
        self._chunks: list[bytearray] = []

    def extract(self, wad_data: bytes, chunks: list[WadChunk]) -> None:
        """Copy all chunk payloads into memory."""
        self.entries = []
        self._chunks = []
        for i, chunk in enumerate(chunks):
            payload = wad_data[chunk.offset: chunk.offset + chunk.size]
            self._chunks.append(bytearray(payload))
            self.entries.append({
                "index": i,
                "tag": chunk.tag,
                "original_offset": chunk.offset,
                "original_size": chunk.size,
                "bin_file": f"chunk_{i:03d}_{chunk.tag.strip() or 'UNK'} (RAM)",
            })

    def get_chunk_data(self, tag: str) -> bytes | None:
        """Read the first in-memory chunk matching *tag*."""
        for e in self.entries:
            if e["tag"] == tag:
                return bytes(self._chunks[e["index"]])
        return None

    def get_chunk_data_by_index(self, index: int) -> bytes | None:
        if 0 <= index < len(self._chunks):
            return bytes(self._chunks[index])
        return None

    def save_chunk_data(self, tag: str, data: bytes) -> bool:
        """Replace the first in-memory chunk matching *tag*."""
        for e in self.entries:
            if e["tag"] == tag:
                self._chunks[e["index"]] = bytearray(data)
                return True
        return False

    def save_chunk_data_by_index(self, index: int, data: bytes) -> bool:
        if 0 <= index < len(self._chunks):
            self._chunks[index] = bytearray(data)
            return True
        return False

    def chunk_info(self) -> list[dict]:
        out = []
        for e in self.entries:
            index = e["index"]
            out.append({**e, "current_size": len(self._chunks[index])})
        return out

    def pack_wad(self, out_path: Path) -> None:
        """Write current in-memory chunks to a WAD file."""
        chunk_blocks = [
            (e["tag"], bytes(self._chunks[e["index"]]))
            for e in self.entries
        ]
        total = 4 + sum(8 + len(d) for _, d in chunk_blocks)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        with out_path.open("wb") as f:
            f.write(struct.pack("<I", total - 4))
            for tag, cdata in chunk_blocks:
                tag_b = tag.encode("ascii", errors="replace")[:4].ljust(4, b"\x00")
                f.write(bytes(reversed(tag_b)))
                f.write(struct.pack("<I", len(cdata)))
                f.write(cdata)

    @property
    def is_open(self) -> bool:
        return bool(self.entries)
