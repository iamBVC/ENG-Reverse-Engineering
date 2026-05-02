"""
wad.py — WAD container scanning.

A level .WAD file is a chunk container.  It is not a ZIP archive and it does not
have a global directory at the end.  Instead, chunks are stored one after another.

Confirmed high-level format:

    +0x00  u32  total_file_size_minus_4
    +0x04  repeated chunks until EOF:

        +0x00  char[4]  tag stored reversed for little-endian reading
        +0x04  u32      chunk data size in bytes
        +0x08  bytes    chunk data

Tag example:

    The human-readable tag TEXT appears in the file as the byte sequence:

        54 58 45 54?  No — tags are read reversed by the original code.

    This scanner reverses the 4 bytes to present tags as humans expect:

        INFO, VERS, WFPC, TEXT, FONT, SPRT, NAME, SMPC, AMPC,
        SRPC, TRAK, STPC, MAP , LGHT, LNFO, LGPC
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from .binary import u32


@dataclass(frozen=True)
class WadChunk:
    tag: str
    offset: int
    size: int

    @property
    def end(self) -> int:
        return self.offset + self.size


def scan_chunks(data: bytes) -> list[WadChunk]:
    """Return a linear list of chunks: tag, data offset, data size."""
    chunks: list[WadChunk] = []
    off = 4

    while off + 8 <= len(data):
        raw_tag = data[off:off + 4]
        tag = raw_tag[::-1].decode("ascii", errors="replace")
        size = u32(data, off + 4)
        data_off = off + 8

        if size < 0 or data_off + size > len(data):
            break

        chunks.append(WadChunk(tag=tag, offset=data_off, size=size))
        off = data_off + size

    return chunks


def read_wad(path: Path) -> tuple[bytes, list[WadChunk], dict[str, WadChunk]]:
    """Read a WAD file and return bytes, ordered chunks, and a tag lookup map."""
    data = path.read_bytes()
    chunks = scan_chunks(data)
    by_tag = {chunk.tag: chunk for chunk in chunks}
    return data, chunks, by_tag


def chunk_bytes(data: bytes, chunk: WadChunk) -> bytes:
    return data[chunk.offset:chunk.end]


def chunk_manifest_lines(path: Path, data: bytes, chunks: list[WadChunk]) -> list[str]:
    lines = [
        f"Source file : {path.name}",
        f"File size   : {len(data):,} bytes",
        f"Chunks      : {len(chunks)}",
        "",
        "Chunk manifest:",
    ]
    for chunk in chunks:
        lines.append(f"  [{chunk.offset:8d}]  {chunk.tag:6s}  {chunk.size:12,} B")
    lines.append("")
    return lines
