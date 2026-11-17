"""Copy legacy Windows compatibility fields from the original PE image."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


_PE_SIGNATURE = b"PE\0\0"
_IMAGE_FILE_HEADER_SIZE = 20
_OPTIONAL_HEADER_SIZE_FIELD_OFFSET = 16
_PE32_MAGIC = 0x10B
_PE32_PLUS_MAGIC = 0x20B
_SUBSYSTEM_VERSION_OFFSET = 0x30
_DLL_CHARACTERISTICS_OFFSET = 0x46


def _optional_header(path: Path, data: bytes) -> tuple[int, int]:
    if len(data) < 0x40 or data[:2] != b"MZ":
        raise ValueError(f"{path} is not a valid DOS/PE image")

    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    header_start = pe_offset + len(_PE_SIGNATURE)
    optional_start = header_start + _IMAGE_FILE_HEADER_SIZE
    if pe_offset > len(data) or data[pe_offset:header_start] != _PE_SIGNATURE:
        raise ValueError(f"{path} has no valid PE signature")
    if len(data) < optional_start:
        raise ValueError(f"{path} has a truncated COFF header")

    optional_size = struct.unpack_from(
        "<H", data, header_start + _OPTIONAL_HEADER_SIZE_FIELD_OFFSET
    )[0]
    if len(data) < optional_start + optional_size or optional_size < _DLL_CHARACTERISTICS_OFFSET + 2:
        raise ValueError(f"{path} has a truncated optional header")
    magic = struct.unpack_from("<H", data, optional_start)[0]
    if magic not in (_PE32_MAGIC, _PE32_PLUS_MAGIC):
        raise ValueError(f"{path} has unsupported optional-header magic 0x{magic:04x}")
    return optional_start, optional_size


def read_compat_fields(path: Path) -> dict[str, int]:
    data = path.read_bytes()
    optional_start, _ = _optional_header(path, data)
    major, minor = struct.unpack_from("<HH", data, optional_start + _SUBSYSTEM_VERSION_OFFSET)
    dll_characteristics = struct.unpack_from(
        "<H", data, optional_start + _DLL_CHARACTERISTICS_OFFSET
    )[0]
    return {
        "major_subsystem_version": major,
        "minor_subsystem_version": minor,
        "dll_characteristics": dll_characteristics,
    }


def copy_compat_fields(target: Path, reference: Path) -> dict[str, dict[str, int]]:
    target_data = bytearray(target.read_bytes())
    reference_data = reference.read_bytes()
    target_optional, target_size = _optional_header(target, target_data)
    reference_optional, reference_size = _optional_header(reference, reference_data)
    if target_size < _DLL_CHARACTERISTICS_OFFSET + 2 or reference_size < _DLL_CHARACTERISTICS_OFFSET + 2:
        raise ValueError("optional headers do not contain all compatibility fields")

    before = read_compat_fields(target)
    major_minor = reference_data[
        reference_optional + _SUBSYSTEM_VERSION_OFFSET : reference_optional + _SUBSYSTEM_VERSION_OFFSET + 4
    ]
    dll_characteristics = reference_data[
        reference_optional + _DLL_CHARACTERISTICS_OFFSET : reference_optional + _DLL_CHARACTERISTICS_OFFSET + 2
    ]
    target_data[
        target_optional + _SUBSYSTEM_VERSION_OFFSET : target_optional + _SUBSYSTEM_VERSION_OFFSET + 4
    ] = major_minor
    target_data[
        target_optional + _DLL_CHARACTERISTICS_OFFSET : target_optional + _DLL_CHARACTERISTICS_OFFSET + 2
    ] = dll_characteristics
    target.write_bytes(target_data)
    return {"before": before, "after": read_compat_fields(target)}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", type=Path, help="rebuilt PE image to update")
    parser.add_argument("reference", type=Path, help="original PE image to copy fields from")
    args = parser.parse_args()
    result = copy_compat_fields(args.target, args.reference)
    print(f"Before: {result['before']}")
    print(f"After:  {result['after']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
