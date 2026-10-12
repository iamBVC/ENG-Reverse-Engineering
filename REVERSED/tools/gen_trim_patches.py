"""gen_trim_patches.py - drop arguments the callee never reads.

The arity widening in gen_arity_patches.py assumes Ghidra under-declared a callee.  For
*cdecl* functions IDA settles it: every argument is on the stack, so the listing's `args`
list is the complete parameter list, and when it agrees with the definition the call site
carrying the extra argument is the thing that is wrong.

Dropping a trailing argument there is safe and is what the original's own code did with it
- the value went on the stack and the callee never read it.  Nothing about the call's
result changes.

    python tools/compile_check.py --chunk 480     # fresh log, after reverting a widening
    rm src_generated/failed.txt
    python tools/gen_trim_patches.py
"""

from __future__ import annotations

import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
PATCHES = OUT / "bulk_patches.csv"

ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")
CALL_RE = re.compile(r"'[^']*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)'")
MARKER_RE = re.compile(r"^/\* ==== ([\w@]+) ==== \*/", re.M)


def split_top_level(text: str) -> list[str]:
    depth, parts, cur = 0, [], ""
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


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py --chunk 480 first")
    text = log.read_text(encoding="latin1", errors="replace")

    # IDA's argument count per function, from the listing's own arg list
    import csv as _csv
    ida: dict[str, int] = {}
    with (ROOT / "functions.csv").open(encoding="utf-8") as fh:
        for row in _csv.DictReader(fh):
            args = row["args"].strip()
            ida[row["name"]] = 0 if not args else len(split_top_level(args))

    files = {}
    for path in sorted((OUT / "chunks").glob("*.c")):
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        own, cur = {}, "?"
        for i, line in enumerate(lines, 1):
            m = MARKER_RE.match(line)
            if m:
                cur = m.group(1)
            own[i] = cur
        files[path.name] = (lines, own)

    defs: dict[str, str] = {}
    for lines, _ in files.values():
        cur = None
        for line in lines:
            m = MARKER_RE.match(line)
            if m:
                cur = m.group(1)
                continue
            if cur and (cur + "(") in line and not line.strip().startswith(("#", "/*")):
                defs.setdefault(cur, line.strip())
                cur = None

    rows, report = [], []
    seen: set[tuple[str, str]] = set()
    for fname, line, code, msg in ERROR_RE.findall(text):
        if code != "C2197":
            continue
        m = CALL_RE.match(msg)
        if not m:
            continue
        callee, declared = m.group(1), m.group(2)
        lines, own = files.get(fname, ([], {}))
        i = int(line)
        call_line = lines[i - 1].strip() if i <= len(lines) else ""
        caller = own.get(i, "?")
        d = defs.get(callee, "")
        if "(" not in d:
            report.append((callee, caller, call_line, "no definition found"))
            continue
        defined = len(split_top_level(d[d.index("(") + 1:d.rindex(")")])
                      ) if d[d.index("(") + 1:d.rindex(")")].strip() not in ("", "void") else 0
        if ida.get(callee) != defined:
            report.append((callee, caller, call_line,
                           f"IDA says {ida.get(callee, '?')} args, definition has {defined}: "
                           f"not the trim case"))
            continue
        if not call_line.endswith(");") or call_line.count("(") != call_line.count(")"):
            report.append((callee, caller, call_line, "call spans several lines"))
            continue
        open_at = call_line.index(callee + "(") + len(callee) + 1
        close_at = call_line.rindex(")")
        args = split_top_level(call_line[open_at:close_at])
        if len(args) <= defined:
            report.append((callee, caller, call_line, "call already passes few enough"))
            continue
        trimmed = call_line[:open_at] + ",".join(args[:defined]) + call_line[close_at:]
        key = (caller, call_line)
        if key in seen:
            continue
        seen.add(key)
        rows.append({"function": caller, "find": call_line, "replace": trimmed})
        report.append((callee, caller, call_line, f"drop {len(args) - defined} trailing arg(s)"))

    existing = []
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8", newline="") as fh:
            existing = [r for r in csv.DictReader(fh)]
    have = {(r["function"], r["find"]) for r in existing}
    added = [r for r in rows if (r["function"], r["find"]) not in have]
    existing.extend(added)
    if added:
        with PATCHES.open("w", newline="", encoding="utf-8") as fh:
            w = csv.DictWriter(fh, fieldnames=["function", "find", "replace"])
            w.writeheader()
            w.writerows(existing)

    print(f"added {len(added)} trim patches (table now {len(existing)} rows)")
    for r in added[:10]:
        print(f"   {r['function']:<12} {r['find'][:46]:<48} -> {r['replace'][:46]}")
    other = [r for r in report if "drop" not in r[3]]
    if other:
        print(f"\n{len(other)} C2197 site(s) not trimmed:")
        for callee, caller, call, why in other[:8]:
            print(f"   {callee:<14} from {caller:<12} {why}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
