"""Check the narrowly scoped PE compatibility metadata copier."""

import struct
import tempfile
from pathlib import Path

from match_pe_compat_metadata import copy_compat_fields, read_compat_fields


def make_pe(path: Path, *, subsystem_version: tuple[int, int], dll_characteristics: int) -> None:
    data = bytearray(0x200)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<H", data, 0x80 + 4 + 16, 0xE0)
    optional = 0x80 + 4 + 20
    struct.pack_into("<H", data, optional, 0x10B)
    struct.pack_into("<HH", data, optional + 0x30, *subsystem_version)
    struct.pack_into("<H", data, optional + 0x46, dll_characteristics)
    data[0x180:] = bytes(range(0x80))
    path.write_bytes(data)


with tempfile.TemporaryDirectory() as directory:
    root = Path(directory)
    reference = root / "original.exe"
    rebuilt = root / "rebuilt.exe"
    make_pe(reference, subsystem_version=(4, 0), dll_characteristics=0)
    make_pe(rebuilt, subsystem_version=(6, 0), dll_characteristics=0x8140)

    before = rebuilt.read_bytes()
    copy_compat_fields(rebuilt, reference)
    after = rebuilt.read_bytes()

    assert read_compat_fields(rebuilt) == read_compat_fields(reference)
    assert before[:0x80 + 24 + 0x30] == after[:0x80 + 24 + 0x30]
    assert before[0x80 + 24 + 0x34:0x80 + 24 + 0x46] == after[0x80 + 24 + 0x34:0x80 + 24 + 0x46]
    assert before[0x80 + 24 + 0x48:] == after[0x80 + 24 + 0x48:]

print("PE compatibility metadata copy changes only subsystem version and DLL flags.")
