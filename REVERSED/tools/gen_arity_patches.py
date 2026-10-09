"""gen_arity_patches.py - widen callees that are called with more arguments.

`C2197` ("troppi argomenti") happens when a call site passes more arguments than the
callee's definition declares.  Ghidra infers a signature from *one* call site, so a
function that the original called with extra values (typically in registers, which the
decompiler cannot see) ends up with a short parameter list.

Since the decompiled body only ever reads the parameters it names, widening the
definition is safe: the extra arguments are ignored exactly as an unused register
would be.  The patches go into the recorded table (src_generated/bulk_patches.csv), so
each one survives regeneration and can be reviewed.

`C2198` (too *few* arguments) is the mirror image and is *not* handled here: filling
in values at the call site would invent data, so those stay in the per-function queue.

    python tools/compile_check.py            # fresh log first
    python tools/gen_arity_patches.py
"""

from __future__ import annotations

import csv
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
PATCHES = OUT / "bulk_patches.csv"

ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")


def split_top_level(text: str) -> list[str]:
    depth = 0
    parts, cur = [], ""
    for ch in text:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur)
    return parts


def definition_of(name: str) -> tuple[str, int] | None:
    """(signature line, parameter count) from the decompiled source.

    The brace is not always on a line of its own - `void sub_426500(void) {` is the
    shape that made the first version return nothing at all - so the signature is
    found by looking for the name followed by a parameter list.
    """
    path = ROOT / "decompiled" / (name + ".c")
    if not path.exists():
        return None
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    for line in lines:
        sig = line.strip()
        if not sig.startswith("{") and name + "(" in sig and sig.rstrip(" {").endswith(")"):
            args = sig[sig.index("(") + 1:sig.rindex(")")]
            args = args.strip()
            if not args or args == "void":
                return sig.rstrip(" {"), 0
            return sig.rstrip(" {"), len(split_top_level(args))
    return None


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py first")
    text = log.read_text(encoding="latin1", errors="replace")

    sources: dict[str, list[str]] = {}
    wanted: dict[str, int] = {}

    for fname, line_no, code, msg in ERROR_RE.findall(text):
        if code != "C2197":
            continue
        if fname not in sources:
            try:
                sources[fname] = (OUT / "chunks" / fname).read_text(
                    encoding="utf-8", errors="replace").splitlines()
            except FileNotFoundError:
                sources[fname] = []
        src = sources[fname]
        i = int(line_no) - 1
        if not (0 <= i < len(src)):
            continue
        call = src[i]
        # `NAME(...)` — take the first symbol with an argument list on that line
        hit = re.search(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^;]*)\)", call)
        if not hit:
            continue
        callee, args = hit.group(1), hit.group(2)
        passed = len(split_top_level(args)) if args.strip() else 0
        if passed > wanted.get(callee, 0):
            wanted[callee] = passed

    rows = []
    for callee, passed in sorted(wanted.items()):
        info = definition_of(callee)
        if not info:
            continue
        sig, declared = info
        if passed <= declared:
            continue
        extra = passed - declared
        new_sig = sig[:sig.rindex(")")] + "".join(
            f", int unused_arg_{declared + k}" for k in range(extra)) + ")"
        rows.append((callee, sig, new_sig))
        print(f"  {callee}: {declared} -> {passed} parameters")

    existing = []
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8") as fh:
            existing = [r for r in csv.DictReader(fh)]
    have = {(r["function"], r["find"]) for r in existing}
    for fn, find, repl in rows:
        if (fn, find) not in have:
            existing.append({"function": fn, "find": find, "replace": repl})

    with PATCHES.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=["function", "find", "replace"])
        w.writeheader()
        w.writerows(existing)
    print(f"added {len(rows)} arity patches; table now has {len(existing)} rows")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
