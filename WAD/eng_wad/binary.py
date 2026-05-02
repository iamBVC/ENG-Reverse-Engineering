"""
binary.py — tiny binary-reading helpers used by the WAD parsers.

The Emperor's New Groove level files are little-endian.  "Little-endian" means
that multi-byte numbers are stored with the least significant byte first.  For
example, the uint32 value 0x12345678 is stored as the byte sequence:

    78 56 34 12

This module deliberately keeps the helpers small and explicit.  The project is
for reverse engineering, so readability is more important than cleverness.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass


def u16(buf: bytes, off: int) -> int:
    """Read an unsigned 16-bit little-endian integer from buf at off."""
    return struct.unpack_from("<H", buf, off)[0]


def u32(buf: bytes, off: int) -> int:
    """Read an unsigned 32-bit little-endian integer from buf at off."""
    return struct.unpack_from("<I", buf, off)[0]


def f32(buf: bytes, off: int) -> float:
    """Read a 32-bit little-endian floating-point value from buf at off."""
    return struct.unpack_from("<f", buf, off)[0]


def read_vec3(buf: bytes, off: int) -> tuple[float, float, float]:
    """Read three little-endian floats: x, y, z."""
    return struct.unpack_from("<3f", buf, off)


@dataclass
class Reader:
    """
    Cursor-based reader over a bytes object.

    Reverse-engineering code often needs to read a structure field-by-field.
    Reader stores a current cursor position and advances after every read.
    """

    buf: bytes
    pos: int = 0

    def remaining(self) -> int:
        return len(self.buf) - self.pos

    def tell(self) -> int:
        return self.pos

    def seek(self, pos: int) -> None:
        self.pos = pos

    def u8(self) -> int:
        v = self.buf[self.pos]
        self.pos += 1
        return v

    def u16(self) -> int:
        v = struct.unpack_from("<H", self.buf, self.pos)[0]
        self.pos += 2
        return v

    def u32(self) -> int:
        v = struct.unpack_from("<I", self.buf, self.pos)[0]
        self.pos += 4
        return v

    def f32(self) -> float:
        v = struct.unpack_from("<f", self.buf, self.pos)[0]
        self.pos += 4
        return v

    def read(self, n: int) -> bytes:
        v = self.buf[self.pos:self.pos + n]
        self.pos += n
        return v

    def skip(self, n: int) -> None:
        self.pos += n

    def can_read(self, n: int) -> bool:
        return 0 <= n <= self.remaining()


def hexdump(data: bytes, max_len: int = 64) -> str:
    """Return a compact hex preview, useful for parse logs."""
    shown = data[:max_len]
    text = " ".join(f"{b:02X}" for b in shown)
    if len(data) > max_len:
        text += " ..."
    return text
