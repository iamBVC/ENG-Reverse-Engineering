"""gen_this_patches.py - restore the register argument Ghidra dropped at a call site.

The "too few arguments" errors come in two shapes, and this tool handles the one that has
*proof* available:

  * the **callee** is declared `__thiscall`/`__fastcall` - so its `param_1` is the object
    MSVC passed in ECX, and the call site is one argument short because Ghidra never
    modelled the register.  If the **caller** is also `__thiscall`/`__fastcall` and the
    instruction just before the call does not touch `ecx`, the missing argument is the
    caller's own `param_1` - the same reasoning the 11 hand-written sites used, and the
    listing is the evidence;
  * the callee is plain `cdecl` and simply declares more parameters than the call passes.
    That is either a parameter Ghidra invented or one this project's arity widening added,
    and neither the value nor the position can be assumed - those are reported, not patched.

Callers IDA never defined (library regions) are reported with no patch: a byte scan is not
proof.  Everything this writes is a normal row in src_generated/bulk_patches.csv.

    python tools/compile_check.py --chunk 480
    rm src_generated/failed.txt
    python tools/gen_this_patches.py
"""

from __future__ import annotations

import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from pe_tools import parse_listing, with_sizes  # noqa: E402

OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
PATCHES = OUT / "bulk_patches.csv"
ASM = ROOT.parent / "Game" / "groove.exe.asm"

ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")
CALL_RE = re.compile(r"'[^']*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)'")
MARKER_RE = re.compile(r"^/\* ==== ([\w@]+) ==== \*/", re.M)
REGISTERISH = ("__thiscall", "__fastcall")


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


def chunks():
    out = {}
    for path in sorted((OUT / "chunks").glob("*.c")):
        text = path.read_text(encoding="utf-8", errors="replace")
        lines = text.splitlines()
        own, cur = {}, "?"
        for i, line in enumerate(lines, 1):
            m = MARKER_RE.match(line)
            if m:
                cur = m.group(1)
            own[i] = cur
        out[path.name] = (lines, own)
    return out


def signatures(files) -> dict[str, str]:
    out = {}
    for lines, _ in files.values():
        cur = None
        for line in lines:
            m = MARKER_RE.match(line)
            if m:
                cur = m.group(1)
                continue
            if cur and (cur + "(") in line and not line.strip().startswith(("#", "/*")):
                out.setdefault(cur, line.strip())
                cur = None
    return out


def ecx_untouched(by_name, asm_lines, caller: str, callee: str, depth: int = 8) -> bool | None:
    """True/False when the caller has a listing, None when IDA never defined it."""
    fn = by_name.get(caller)
    if fn is None or fn.va is None:
        return None
    body = [l.rstrip() for l in asm_lines[fn.asm_start:fn.asm_end]]
    for i, line in enumerate(body):
        if re.search(r"\bcall\s+" + re.escape(callee) + r"\b", line):
            window = body[max(0, i - depth):i]
            # a call in the window means ECX is whatever that callee left: not provable
            if any(re.search(r"\bcall\s", w) for w in window):
                return False
            return not any(re.search(r"\becx\b", w) for w in window)
    return None


def convention(name: str, sigs) -> str:
    """The callee's declared convention, from the *decompiled* source.

    Not from the chunk: recorded patches can rewrite that line (the `sub_41BCB0`
    return-type fix dropped its `__fastcall`), and the decompiled file is the original
    evidence.  `__thiscall`/`__fastcall` is what says "param_1 arrived in ECX".
    """
    path = ROOT / "decompiled" / (name + ".c")
    if path.exists():
        head = path.read_text(encoding="utf-8", errors="replace").splitlines()[:12]
        for line in head:
            if (name + "(") in line:
                return line
    return sigs.get(name, "")


def ecx_expression(by_name, asm_lines, caller: str, callee: str, depth: int = 8):
    """(C expression for ECX, why-not) from the caller's listing."""
    fn = by_name.get(caller)
    if fn is None or fn.va is None:
        return None, "no listing for the caller (library region)"
    body = [l.rstrip() for l in asm_lines[fn.asm_start:fn.asm_end]]
    for i, line in enumerate(body):
        if re.search(r"\bcall\s+" + re.escape(callee) + r"\b", line):
            window = body[max(0, i - depth):i]
            if any(re.search(r"\bcall\s", w) for w in window):
                return None, "a call sits between the last ECX write and this call"
            writes = [w for w in window if re.search(r"\becx\b", w)]
            if not writes:
                return "", "no ECX write: use the caller's own this if it is a member"
            w = writes[-1].strip()
            m = re.search(r"(?:mov|lea)\s+ecx,\s*(?:ds:)?(?:dword_|off_)?([0-9A-Fa-f]{6,8})\b", w)
            if m:
                return f"(int)DAT_{int(m.group(1), 16):08x}", None
            m = re.search(r"mov\s+ecx,\s*(?:\[|ds:)\s*(?:dword_|off_)?([0-9A-Fa-f]{6,8})\b", w)
            if m:
                return f"DAT_{int(m.group(1), 16):08x}", None
            return None, f"ECX comes from `{w[:44]}`, needs reading"
    return None, "no call to the callee found in the listing"


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py --chunk 480 first")
    text = log.read_text(encoding="latin1", errors="replace")
    files = chunks()
    sigs = signatures(files)
    by_name = {f.name: f for f in with_sizes(parse_listing(ASM))}
    asm_lines = ASM.read_text(encoding="latin1", errors="replace").splitlines()

    rows, report = [], []
    for fname, line, code, msg in ERROR_RE.findall(text):
        if code != "C2198":
            continue
        m = CALL_RE.match(msg)
        if not m:
            continue
        callee, declared = m.group(1), m.group(2)
        caller = files.get(fname, ([], {}))[1].get(int(line), "?")
        src = files.get(fname, ([], []))[0]
        call = src[int(line) - 1].strip() if int(line) <= len(src) else ""
        # Ghidra wraps long calls over several lines.  A patch is applied to *text*, so a
        # fragment is not patchable: prepending an argument to half a call leaves the rest
        # of the expression dangling and breaks the function (measured - it cost 6 errors
        # in the normal build).  Only complete, single-line calls are handled.
        if not call.endswith(");") or call.count("(") != call.count(")"):
            report.append((callee, caller, call,
                           "the call spans several lines: not patchable as text"))
            continue
        cdef, fdef = convention(callee, sigs), convention(caller, sigs)
        if not any(k in cdef for k in REGISTERISH):
            report.append((callee, caller, call,
                           "callee is not thiscall/fastcall: an invented or widened param"))
            continue
        expr, why = ecx_expression(by_name, asm_lines, caller, callee)
        if expr is None:
            report.append((callee, caller, call, why))
            continue
        if expr == "":       # ECX untouched: only provable for a member caller
            if not any(k in fdef for k in REGISTERISH):
                report.append((callee, caller, call, "no ECX write, but the caller is not a "
                                                        "member function either"))
                continue
            expr = "param_1"
        # prepend the dropped argument, and keep whatever followed the closing paren
        # (`);`, `); ` ...).  Dropping it cost four `C2146: missing ';'` errors in the
        # normal build, which is how this line got its shape.
        open_at, close_at = call.index("("), call.rindex(")")
        inner = call[open_at + 1:close_at]
        new = (call[:open_at + 1]
               + (expr + ", " + inner if inner else expr)
               + call[close_at:])
        rows.append({"function": caller, "find": call, "replace": new})

    existing = []
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8", newline="") as fh:
            existing = [r for r in csv.DictReader(fh)]
    have = {(r["function"], r["find"]) for r in existing}
    added = []
    for r in rows:            # dedupe within the run too: two sites can share a call text
        if (r["function"], r["find"]) in have:
            continue
        have.add((r["function"], r["find"]))
        added.append(r)
    existing.extend(added)
    if added:
        with PATCHES.open("w", newline="", encoding="utf-8") as fh:
            w = csv.DictWriter(fh, fieldnames=["function", "find", "replace"])
            w.writeheader()
            w.writerows(existing)

    print(f"added {len(added)} this-restores (table now {len(existing)} rows)")
    for r in added:
        print(f"   {r['function']:<12} {r['find'][:52]}  ->  {r['replace'][:52]}")
    if report:
        print(f"\n{len(report)} site(s) left for hand work:")
        for callee, caller, call, why in report:
            print(f"   {callee:<14} from {caller:<12} {call[:44]:<46} {why}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
