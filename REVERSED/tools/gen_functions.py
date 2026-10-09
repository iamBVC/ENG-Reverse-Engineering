"""gen_functions.py - build the decompilation work queue from the IDA listing.

Writes `REVERSED/functions.csv`, one row per function, ordered by ascending size
so the mechanical (leaf, small) functions can be knocked out first.

Columns
-------
name            IDA name (also the C identifier used in src/)
address         virtual address in groove.exe
size            bytes, from the gap to the next function (includes padding)
insns           instruction lines in the listing
convention      cdecl / stdcall (detected from `retn N`)
args            guessed parameter types from the `arg_N=` prologue lines
leaf            True when the function calls no other function in the listing
callees         space-separated callee names
status          todo | draft | exact | reloc | mismatch | not_ported  (bytecheck.py updates this)
"""

from __future__ import annotations

import csv
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pe_tools import with_sizes, parse_listing  # noqa: E402

FIELDS = ["name", "address", "size", "insns", "kind", "convention", "args", "leaf", "callees", "status"]

_JUMP_THUNK = re.compile(r"^jmp\s+sub_[0-9A-Fa-f]{6}$")
_ARG_DECL = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*=\s")


def classify(func, lines: list[str]) -> str:
    """game | ilt_thunk | nullsub | library.

    `ilt_thunk` is the incremental-link thunk the MSVC linker emits before a
    real body (`jmp sub_XXXXXX` + padding) - it simply does not exist in a clean
    rebuild, so it must not count as reverse-engineering work.
    """
    body = []
    for line in lines[func.asm_start - 1:func.asm_end]:
        s = line.strip()
        if not s or s.startswith(";") or "proc near" in s or s.endswith("endp"):
            continue
        if _ARG_DECL.match(s):
            continue
        body.append(s)
    if len(body) == 1 and _JUMP_THUNK.match(body[0]):
        return "ilt_thunk"
    if not body or func.name.startswith("nullsub_"):
        return "nullsub"
    if not func.name.startswith("sub_"):
        return "library"
    return "game"


def build(root: Path) -> Path:
    asm = root / "WAD" / "groove.exe.asm"
    all_lines = asm.read_text(encoding="latin1", errors="replace").splitlines()
    funcs = with_sizes(parse_listing(asm))
    funcs.sort(key=lambda f: (f.size or 0, f.name))
    out = root / "REVERSED" / "functions.csv"
    with out.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=FIELDS)
        w.writeheader()
        for f in funcs:
            kind = classify(f, all_lines)
            w.writerow({
                "name": f.name,
                "address": f"0x{f.va:06X}" if f.va else "",
                "size": f.size,
                "insns": f.insns,
                "kind": kind,
                "convention": f.convention,
                "args": ",".join(a.split("=")[0] for a in f.args),
                "leaf": int(f.is_leaf),
                "callees": " ".join(f.callees),
                "status": "thunk" if kind == "ilt_thunk" else "todo",
            })
    return out


if __name__ == "__main__":
    import collections

    root = Path(__file__).resolve().parent.parent.parent
    path = build(root)
    print(f"wrote {path}")
    rows = list(csv.DictReader(path.open(encoding="utf-8")))
    kinds = collections.Counter(r["kind"] for r in rows)
    for k, v in kinds.most_common():
        print(f"  {k:<10} {v:>5}")
    game = [r for r in rows if r["kind"] == "game"]
    leaf = [r for r in game if r["leaf"] == "1" and 0 < int(r["size"]) <= 32]
    print(f"\nreal game functions to reverse: {len(game)}")
    print(f"of which leaf <= 32 bytes     : {len(leaf)}  (the starting batch)")
    for r in leaf[:12]:
        print(f"   {r['name']:<18} {r['address']:<10} {r['size']:>3} B  {r['convention']}")
