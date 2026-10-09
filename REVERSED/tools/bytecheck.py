"""bytecheck.py - the matching verifier for the groove.exe decompilation.

For every function that exists in the original (see `functions.csv`) and was
found in the compiled objects (`build/objects/*.obj`), this compares the
recompiled machine code against the original bytes cut out of `WAD/groove.exe`,
and updates the `status` column of `functions.csv`.

Verdicts
--------
  EXACT   the recompiled function is byte-for-byte identical to the original
  RELOC   identical once absolute-address dwords are masked out.  Globals live
          at different addresses in any independent rebuild, so this is the
          practical ceiling unless the link layout is reproduced too
  DIFF    a real code difference; the first mismatching offset is printed

Usage
-----
    python tools/bytecheck.py                     compare every object in build/objects
    python tools/bytecheck.py --only sub_41EF00   restrict to named functions
    python tools/bytecheck.py --dump sub_41EF00   show the two byte streams
    python tools/bytecheck.py --list              show the work queue only
"""

from __future__ import annotations

import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from coff_tools import CoffObject  # noqa: E402
from pe_tools import PE, parse_listing, with_sizes  # noqa: E402

PAD = b"\xcc\x90"


def trim_padding(code: bytes) -> bytes:
    return code.rstrip(PAD)


def normalize(code: bytes, relocs: set[int]) -> bytes:
    """Zero out the dwords that hold absolute addresses."""
    if not relocs:
        return code
    out = bytearray(code)
    for off in relocs:
        for i in range(4):
            if off + i < len(out):
                out[off + i] = 0
    return bytes(out)


def compare(orig: bytes, orig_relocs: set[int], new: bytes, new_relocs: set[int]):
    if orig == new:
        return "exact", None
    a = normalize(orig, orig_relocs)
    b = normalize(new, new_relocs)
    if a == b:
        return "reloc", None
    for i in range(min(len(a), len(b))):
        if a[i] != b[i]:
            return "diff", i
    return "diff", min(len(a), len(b))


def dump(name: str, orig: bytes, new: bytes, offset: int | None) -> None:
    print(f"\n  {name}")
    print(f"    original ({len(orig)} B): {orig.hex(' ')}")
    print(f"    rebuilt  ({len(new)} B): {new.hex(' ')}")
    if offset is not None:
        print(f"    first difference at +0x{offset:X}")
        lo = max(0, offset - 4)
        print(f"      original [{lo:02X}..]: {orig[lo:offset + 6].hex(' ')}")
        print(f"      rebuilt  [{lo:02X}..]: {new[lo:offset + 6].hex(' ')}")
    print()


def main() -> int:
    root = Path(__file__).resolve().parent.parent.parent
    rev = root / "REVERSED"
    pe = PE(root / "WAD" / "groove.exe")
    listing = {f.name: f for f in with_sizes(parse_listing(root / "WAD" / "groove.exe.asm")) if f.va}

    manifest_path = rev / "functions.csv"
    rows: list[dict] = []
    if manifest_path.exists():
        with manifest_path.open(newline="", encoding="utf-8") as fh:
            rows = list(csv.DictReader(fh))
    known = {r["name"] for r in rows}

    if "--list" in sys.argv:
        todo = [r for r in rows if r["status"] == "todo"]
        print(f"{len(todo)} functions still todo (smallest first):")
        for r in todo[:25]:
            print(f"   {r['name']:<18} {r['address']:<10} {r['size']:>4} B  {r['convention']}")
        return 0

    objs = sorted((rev / "build" / "objects").glob("*.obj")) if (rev / "build" / "objects").exists() else []
    compiled: dict[str, tuple[bytes, set[int]]] = {}
    for obj in objs:
        for name, val in CoffObject(obj).functions().items():
            compiled[name] = val

    only = set(sys.argv[sys.argv.index("--only") + 1:]) if "--only" in sys.argv else None
    want_dump = sys.argv[sys.argv.index("--dump") + 1:] if "--dump" in sys.argv else []

    print(f"objects        : {len(objs)}")
    print(f"compiled funcs : {len(compiled)}  ({sum(1 for n in compiled if n in known)} with a counterpart in groove.exe)")
    print()

    verdicts = {"exact": [], "reloc": [], "diff": []}
    for name, (new_code, new_relocs) in sorted(compiled.items(), key=lambda kv: kv[0]):
        if name not in known:
            continue
        if only and name not in only:
            continue
        f = listing[name]
        orig = trim_padding(pe.read(f.va, f.size))
        new_code = trim_padding(new_code)
        orig_relocs = {va - f.va for va in pe.reloc_dwords if f.va <= va < f.va + len(orig)}
        new_relocs = {o for o in new_relocs if o < len(new_code)}
        verdict, offset = compare(orig, orig_relocs, new_code, new_relocs)
        verdicts[verdict].append(name)
        where = f" first diff @ +0x{offset:X}" if offset is not None else ""
        print(f"  {verdict.upper():<5} {name:<18} orig {len(orig):>4} B / new {len(new_code):>4} B{where}")
        if name in want_dump:
            dump(name, orig, new_code, offset)
        if not only:
            for r in rows:
                if r["name"] == name:
                    r["status"] = verdict
                    break

    if rows and not only:
        with manifest_path.open("w", newline="", encoding="utf-8") as fh:
            w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
            w.writeheader()
            w.writerows(rows)

    matched = len(verdicts["exact"]) + len(verdicts["reloc"])
    print()
    print(f"EXACT {len(verdicts['exact'])} | RELOC {len(verdicts['reloc'])} | DIFF {len(verdicts['diff'])} "
          f"-> {matched} matching of {matched + len(verdicts['diff'])} compared")
    return 1 if verdicts["diff"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
