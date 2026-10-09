"""try_patches.py - greedy per-error type fixes, keeping only the winners.

The remaining type errors are per-site: a `C2440` names the type an expression had to
become, and a `C2296` names the operand that is wrong.  Each erroring line is a
candidate fix - type the symbols on it the way the message says - and each candidate
is *tried and measured*, kept only if the clean-function count goes up.

Same discipline as tools/infer_global_types.py, but the evidence comes from the
compiler's own message rather than from a seed, and the unit is one error line.
Accepted types accumulate in src_generated/type_overrides.csv.

    python tools/try_patches.py --max 25
"""

from __future__ import annotations

import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
OVERRIDES = OUT / "type_overrides.csv"

SYM_PATTERN = r"[A-Za-z_][A-Za-z0-9_]*_[0-9a-f]{6,8}"
SYM_RE = re.compile(SYM_PATTERN)
CONVERT_RE = re.compile(r"da '([^']*)' a '([^']*)'")


def kind_of_ctype(ctype):
    if ctype in ("float", "double"):
        return ctype
    if "*" in ctype:
        return "pointer"
    return "int"


def load_overrides():
    if not OVERRIDES.exists():
        return {}
    with OVERRIDES.open(encoding="utf-8") as fh:
        return {r["name"]: r["type"] for r in csv.DictReader(fh)}


def save_overrides(table):
    OVERRIDES.parent.mkdir(parents=True, exist_ok=True)
    with OVERRIDES.open("w", newline="", encoding="utf-8") as fh:
        w = csv.writer(fh)
        w.writerow(["name", "type"])
        for name in sorted(table):
            w.writerow([name, table[name]])


def regenerate():
    subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                   capture_output=True, text=True)


def clean_count():
    res = subprocess.run([sys.executable, str(ROOT / "tools" / "compile_check.py")],
                         capture_output=True, text=True)
    hit = re.search(r"compiling cleanly\s*:\s*(\d+)", res.stdout)
    return int(hit.group(1)) if hit else -1


def candidates():
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        return []
    text = log.read_text(encoding="latin1", errors="replace")
    out = {}
    pattern = r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)"
    for fname, line_no, code, msg in re.findall(pattern, text):
        if code not in ("C2440", "C2296", "C2297"):
            continue
        try:
            src = (OUT / "chunks" / fname).read_text(encoding="utf-8", errors="replace").splitlines()
        except FileNotFoundError:
            continue
        i = int(line_no) - 1
        if not (0 <= i < len(src)):
            continue
        line = src[i]
        names = SYM_RE.findall(line)
        if not names:
            continue
        kind = None
        if code == "C2440":
            hit = CONVERT_RE.search(msg)
            if hit:
                has_cast = re.search(r"\(\s*\w+\s*\**\s*\)\s*" + SYM_PATTERN, line) is not None
                kind = kind_of_ctype(hit.group(2 if has_cast else 1))
        if kind is None:
            kind = "float"      # the rejected-operand cases are the float tables
        out[fname + ":" + line_no] = [(n, kind) for n in names]
    return sorted(out.items())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max", type=int, default=25)
    args = ap.parse_args()

    table = load_overrides()
    best = clean_count()
    print("baseline: %d clean, %d overrides already applied" % (best, len(table)))

    cands = candidates()
    print("%d candidate lines; trying at most %d\n" % (len(cands), args.max))
    kept = 0
    for label, pairs in cands[:args.max]:
        fresh = [(n, k) for n, k in pairs if n not in table]
        if not fresh:
            continue
        for n, k in fresh:
            table[n] = k
        save_overrides(table)
        regenerate()
        now = clean_count()
        names = ",".join(n for n, _ in fresh)
        if now > best:
            print("  %s  %s -> %s: %d -> %d (+%d)  kept"
                  % (label, names, fresh[0][1], best, now, now - best))
            best = now
            kept += 1
        else:
            for n, _ in fresh:
                table.pop(n, None)
            save_overrides(table)
            regenerate()
    print("\nkept %d fixes; %d clean, %d overrides in the table" % (kept, best, len(table)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
