"""gen_reg_arg_patches.py - restore a value MSVC put in ECX just before a call.

The class this sweeps
---------------------
MSVC passes the first argument of a `__fastcall`/`__thiscall` callee in ECX.  The rebuild
compiles those callees as plain C (the convention is dropped in C mode - see the README), so
the *caller* has to pass the value explicitly, and Ghidra's C drops it.  That is invisible to
the compiler here because the bulk uses K&R prototypes, so no arity is checked: it surfaces
only at run time.  The first static-initialiser cluster died twice from two of these - `call
0` inside initialiser 13, and a write to `[this+8]` once the object was passed at all.

What is provable from the bytes, and therefore what this patches
---------------------------------------------------------------
    B9 <imm32>       mov ecx, <address>      (a fixed global object)
    E9/E8 <rel32>    jmp/call <callee>       (a callee this build also compiles)

The row it writes inserts `(undefined4 *)&DAT_<addr>` as the call's first argument, and it
uses the *symbol*, never the address: an address from the original's layout is unmapped in
the rebuild (measured - the constructor faulted writing `[this+8]` when the literal was used).

Everything else is *reported*, not patched: when ECX comes from a register or from memory it
is the caller's own `this` or a parameter, and the listing has to be read to decide - that is
tools/dropped_arg_report.py's job.

    python tools/gen_reg_arg_patches.py --dry-run     # list the sites
    python tools/gen_reg_arg_patches.py               # record the rows
"""
from __future__ import annotations

import csv
import io
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pe_tools import PE  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
EXE = ROOT.parent / "WAD" / "groove.exe"
DEC = ROOT / "decompiled"
PATCHES = ROOT / "src_generated" / "bulk_patches.csv"
GLOBALS_H = ROOT / "src_generated" / "ghidra_globals.h"
DATA_LO, DATA_HI = 0x570000, 0x6DB935
TEXT_LO, TEXT_HI = 0x401000, 0x56E000


def decompiled_entries() -> list[int]:
    out = []
    for p in DEC.glob("sub_*.c"):
        m = re.match(r"sub_([0-9A-F]{6})\.c$", p.name)
        if m:
            out.append(int(m.group(1), 16))
    return sorted(out)


def globals_declared() -> set[str]:
    return set(re.findall(r"\b(DAT_[0-9a-fA-F]{8})\b", GLOBALS_H.read_text(encoding="utf-8")))


def scan(pe: PE, entries: list[int], declared: set[str]):
    """(caller, callee, object) for every `mov ecx,<global>; jmp/call <known fn>` site."""
    text = pe.read(TEXT_LO, TEXT_HI - TEXT_LO)
    sites, reported = [], []
    for i in range(len(text) - 10):
        if text[i] != 0xB9:
            continue
        obj = struct.unpack_from("<I", text, i + 1)[0]
        if text[i + 5] not in (0xE9, 0xE8) or not (DATA_LO <= obj < DATA_HI):
            continue
        va = TEXT_LO + i
        callee = (va + 10 + struct.unpack_from("<i", text, i + 6)[0]) & 0xFFFFFFFF
        if callee not in entries:
            continue                       # a callee this build does not compile
        caller = None
        for a in entries:
            if a <= va:
                caller = a
            else:
                break
        if caller is None or va - caller > 0x1000:
            continue
        name = "DAT_%08X" % obj
        if name not in declared:
            reported.append((caller, va, obj, name))
            continue
        sites.append((caller, callee, obj))
    return sites, reported


def patch_row(caller: int, callee: int, obj: int, body: str):
    """A (function, find, replace) row, or None with a reason."""
    call = "sub_%06X(" % callee
    n = body.count(call)
    if n != 1:
        return None, "it calls sub_%06X %d time(s)" % (callee, n)
    arg = "(undefined4 *)&DAT_%08X" % obj
    if body.count(call + ")") == 1:                     # no arguments today
        find = call + ")"
        if body.count(find) != 1:
            return None, "%s is not unique" % find
    else:                                               # arguments follow: put ours first
        find = call
    return ("sub_%06X" % caller, find, "%s%s%s" % (call, arg, ")" if find.endswith(")") else ", ")), None


def main() -> int:
    dry = "--dry-run" in sys.argv
    pe = PE(EXE)
    entries = decompiled_entries()
    sites, reported = scan(pe, entries, globals_declared())

    # rows already in the table: a hand-written fix and this tool would otherwise both
    # claim the same call site (the second row's pattern no longer matches, so it is only
    # noise - but the table is the record, so keep it clean).
    existing = set()
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8") as fh:
            for r in csv.DictReader(fh):
                existing.add((r["function"], r["find"]))

    rows, humans = [], 0
    for caller, callee, obj in sites:
        body = (DEC / ("sub_%06X.c" % caller)).read_text(encoding="utf-8", errors="replace")
        row, why = patch_row(caller, callee, obj, body)
        if row is not None and (row[0], row[1]) in existing:
            print("  already recorded: %s %s" % (row[0], row[1]))
            continue
        if row is None:
            print("  needs a human: sub_%06X -> sub_%06X (ECX=0x%06X) - %s"
                  % (caller, callee, obj, why))
            humans += 1
            continue
        rows.append(row)
        print("  %-12s -> %-12s  ECX=0x%06X  (%s)" % (row[0], "sub_%06X" % callee, obj, row[1]))

    for caller, va, obj, name in reported:
        print("  not emitted: sub_%06X sets ECX=0x%06X at 0x%06X but %s has no definition"
              % (caller, obj, va, name))

    print()
    print("provable sites %d, patchable %d, need a human %d" % (len(sites), len(rows), humans))
    if dry or not rows:
        print("dry run - nothing written" if dry else "nothing to write")
        return 0

    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\r\n")
    for row in rows:
        w.writerow(list(row))
    text = PATCHES.read_bytes().decode("utf-8")
    if not text.endswith("\r\n"):
        text += "\r\n"
    added = 0
    for line in buf.getvalue().splitlines(keepends=True):
        if line.strip() and line not in text:
            text += line
            added += 1
    PATCHES.write_bytes(text.encode("utf-8"))
    print("rows added:", added)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
