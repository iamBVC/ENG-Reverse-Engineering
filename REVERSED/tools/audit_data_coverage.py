"""Audit Ghidra data symbols against the generated globals used by the rebuild.

This is a source-coverage check, not proof that every reconstructed value is
semantically correct. It distinguishes referenced data missing a generated
definition from unreferenced exports and labels that point into executable code.
"""

from __future__ import annotations

import csv
import re
import sys
from dataclasses import dataclass
from pathlib import Path

from pe_tools import PE


ROOT = Path(__file__).resolve().parents[1]
IDENTIFIER_RE = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")
ADDRESS_COMMENT_RE = re.compile(r"/\*\s*0x([0-9A-Fa-f]{8})\b")
DEFINE_RE = re.compile(r"^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.+?)\s*$", re.M)
DECLARATION_RE = re.compile(
    r"^\s*(?:const\s+)?(?:unsigned\s+)?"
    r"(?:long\s+long|long|int|short|char|float|double|code|FARPROC|"
    r"[A-Za-z_][A-Za-z0-9_]*)\s*(?:\*\s*)*"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]\n]*\]\s*)?(?:=|;)",
    re.M,
)


@dataclass(frozen=True)
class DataEntry:
    name: str
    address: int
    size: int
    datatype: str


def parse_data_csv(text: str) -> list[DataEntry]:
    """Parse the Ghidra export, including legacy unquoted commas in names."""
    reader = csv.reader(text.splitlines())
    next(reader, None)
    entries: list[DataEntry] = []
    for line_number, fields in enumerate(reader, start=2):
        if len(fields) < 4:
            raise ValueError(f"Invalid data export row {line_number}: {fields!r}")
        name = ",".join(fields[:-3])
        address_text, size_text, datatype = fields[-3:]
        try:
            address = int(address_text, 16)
            size = max(1, int(size_text))
        except ValueError as exc:
            raise ValueError(f"Invalid data export row {line_number}: {fields!r}") from exc
        entries.append(DataEntry(name, address, size, datatype))
    return entries


def classify_entries(
    entries: list[DataEntry],
    *,
    represented_names: set[str],
    represented_addresses: set[int],
    storage_ranges: list[tuple[int, int]],
    referenced_names: set[str],
    code_ranges: list[tuple[int, int]],
    image_ranges: list[tuple[int, int]],
) -> dict[str, list[DataEntry]]:
    """Classify each export row without treating unused data as a missing global."""
    result = {
        "represented": [],
        "referenced_unrepresented": [],
        "unreferenced_unrepresented": [],
        "code_address": [],
        "outside_image": [],
    }
    for entry in entries:
        address = entry.address
        if any(start <= address < end for start, end in code_ranges):
            result["code_address"].append(entry)
        elif not any(start <= address < end for start, end in image_ranges):
            result["outside_image"].append(entry)
        elif (
            entry.name in represented_names
            or address in represented_addresses
            or any(start <= address < end for start, end in storage_ranges)
        ):
            result["represented"].append(entry)
        elif entry.name in referenced_names:
            result["referenced_unrepresented"].append(entry)
        else:
            result["unreferenced_unrepresented"].append(entry)
    return result


def generated_global_names(source: str) -> set[str]:
    """Return names with actual global definitions in the generated C file."""
    return set(DECLARATION_RE.findall(source))


def header_aliases(header: str) -> dict[str, str]:
    """Read simple generated aliases, including aliases to table storage macros."""
    return {name: target.strip() for name, target in DEFINE_RE.findall(header)}


def table_ranges(path: Path, defined_names: set[str]) -> list[tuple[int, int]]:
    """Return emitted object extents from array/record and scalar overrides."""
    ranges: list[tuple[int, int]] = []
    with path.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            kind = row["type"]
            try:
                start = int(row["name"].rsplit("_", 1)[1], 16)
                parts = kind.split(":")
                if kind in {"floatfile", "float"}:
                    size = 4
                elif kind in {"doublefile", "double"}:
                    size = 8
                elif kind in {"pointer", "int", "bytepointerfile"}:
                    size = 4
                elif kind.startswith(("dwords:", "record:", "functions:", "array:", "string:")):
                    size = int(parts[1], 16)
                else:
                    continue
            except (IndexError, ValueError):
                continue
            if size > 0 and (
                row["name"] in defined_names
                or f"{row['name']}_storage" in defined_names
            ):
                ranges.append((start, start + size))
    return ranges


def commented_object_ranges(source: str) -> list[tuple[int, int]]:
    """Read exact sizes recorded beside generated definitions."""
    pattern = re.compile(
        r"/\*\s*0x([0-9A-Fa-f]{8})\s*,\s*(\d+)\s+byte(?:\(s\))?"
    )
    return [
        (int(address, 16), int(size))
        for address, size in pattern.findall(source)
        if int(size) > 0
    ]


def initializer_ranges(source: str) -> list[tuple[int, int]]:
    """Return byte extents for generated string arrays with explicit initializers."""
    pattern = re.compile(
        r"^\s*const\s+char\s+[A-Za-z_][A-Za-z0-9_]*\s*\[\s*\]\s*"
        r"=\s*\{([^}]*)\};\s*/\*\s*0x([0-9A-Fa-f]{8})\b",
        re.M,
    )
    ranges = []
    for values, address in pattern.findall(source):
        size = len([value for value in values.split(",") if value.strip()])
        if size:
            start = int(address, 16)
            ranges.append((start, start + size))
    return ranges


def run_audit(root: Path = ROOT) -> tuple[dict[str, list[DataEntry]], list[DataEntry]]:
    export_path = root / "decompiled_ghidra_12_1_4_fixed" / "_data.csv"
    globals_path = root / "src_generated" / "ghidra_globals.c"
    header_path = root / "src_generated" / "ghidra_globals.h"
    bulk_path = root / "src_generated" / "bulk_all.c"
    overrides_path = root / "src_generated" / "type_overrides.csv"
    exe_path = root.parent / "Game" / "groove.exe"

    entries = parse_data_csv(export_path.read_text(encoding="utf-8-sig"))
    globals_source = globals_path.read_text(encoding="utf-8", errors="replace")
    header = header_path.read_text(encoding="utf-8", errors="replace")
    bulk = bulk_path.read_text(encoding="utf-8", errors="replace")
    defined = generated_global_names(globals_source)
    aliases = header_aliases(header)
    represented_names = defined | {
        alias for alias, target in aliases.items()
        if target.split("(", 1)[0].strip() in defined
    }
    represented_addresses = {
        int(value, 16) for value in ADDRESS_COMMENT_RE.findall(globals_source)
    }
    storage = table_ranges(overrides_path, defined)
    storage.extend(
        (start, start + size)
        for start, size in commented_object_ranges(globals_source)
    )
    storage.extend(initializer_ranges(globals_source))
    referenced = set(IDENTIFIER_RE.findall(bulk))

    pe = PE(exe_path)
    code_ranges = [
        (pe.image_base + section.vaddr,
         pe.image_base + section.vaddr + max(section.vsize, section.rawsize))
        for section in pe.sections if section.is_code
    ]
    image_ranges = [
        (pe.image_base + section.vaddr,
         pe.image_base + section.vaddr + max(section.vsize, section.rawsize))
        for section in pe.sections
    ]
    return classify_entries(
        entries,
        represented_names=represented_names,
        represented_addresses=represented_addresses,
        storage_ranges=storage,
        referenced_names=referenced,
        code_ranges=code_ranges,
        image_ranges=image_ranges,
    ), entries


def main() -> int:
    result, entries = run_audit()
    for label, rows in result.items():
        print(f"{label:28}: {len(rows)} rows / {len({r.address for r in rows})} addresses")
    missing = result["referenced_unrepresented"]
    if missing:
        print("\nReferenced exports without a generated definition:")
        for row in missing[:40]:
            print(f"  {row.name:48} 0x{row.address:08X} size={row.size} {row.datatype}")
        if len(missing) > 40:
            print(f"  ... and {len(missing) - 40} more")
    print(f"\nTotal Ghidra data export rows: {len(entries)}")
    print("Coverage is provenance only; initial values and binary semantics require separate verification.")
    return 1 if missing else 0


if __name__ == "__main__":
    raise SystemExit(main())
