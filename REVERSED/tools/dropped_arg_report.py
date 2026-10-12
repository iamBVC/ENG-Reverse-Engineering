"""dropped_arg_report.py - the work queue for "too few arguments" (C2198).

Ghidra drops the argument MSVC passed in a register.  For `__thiscall`/`__fastcall` that
is usually the leading `this`, which is why the call sites in the decompiled source are one
argument short and the callee's parameters are one slot out of line at run time.

This tool lists the sites and, for each one, the *evidence* needed to restore the argument:

  * the callee's declaration (so the number of missing arguments is known),
  * the caller's listing around the call, when IDA defined the caller - `mov ecx, ...`
    immediately before the `call` is the dropped argument, and its absence means ECX is
    the caller's own incoming `this`,
  * a byte-scan hint for callers IDA never defined (they live inside library regions).
    The hint is an opcode scan, so it can match bytes inside another instruction: treat it
    as a pointer to look at, not as proof.

Nothing is written automatically.  Every restore is a recorded row in
src_generated/bulk_patches.csv, and the numbers to watch are in the header of this
docstring's companion in the README: the normal measure (`--chunk 40`) hides these errors
because the callee's definition is in another translation unit, so use

    python tools/compile_check.py --chunk 480     # full visibility, 106 errors today
    python tools/dropped_arg_report.py            # ...then this
    rm src_generated/failed.txt                   # that run writes the 40 to failed.txt

    python tools/dropped_arg_report.py --callee sub_414600
"""

from __future__ import annotations

import collections
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pe_tools import PE, parse_listing, with_sizes  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"
OUT = ROOT / "src_generated"
ASM = ROOT.parent / "WAD" / "groove.exe.asm"
EXE = ROOT.parent / "WAD" / "groove.exe"
MARKER = re.compile(r"^/\* ==== ([\w@]+) ==== \*/", re.M)
ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")
CALL_RE = re.compile(r"'[^']*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)'")

# writes to ECX an opcode scan can see (imm32 / [mem] / [esp+..] / [ebp+..] / pop / lea / xor)
WRITERS = {
    (0xB9,): "mov ecx, imm32",
    (0x8B, 0x0D): "mov ecx, [imm32]",
    (0x8B, 0x0C, 0x24): "mov ecx, [esp]",
    (0x59,): "pop ecx",
    (0x8D, 0x0D): "lea ecx, [imm32]",
    (0x33, 0xC9): "xor ecx, ecx",
}


def chunks() -> dict[str, tuple[list[str], dict[int, str]]]:
    out = {}
    for path in sorted((OUT / "chunks").glob("*.c")):
        text = path.read_text(encoding="utf-8", errors="replace").splitlines()
        own, cur = {}, "?"
        for i, line in enumerate(text, 1):
            m = MARKER.match(line)
            if m:
                cur = m.group(1)
            own[i] = cur
        out[path.name] = (text, own)
    return out


def definitions(files) -> dict[str, str]:
    out = {}
    for text, _ in files.values():
        cur = None
        for line in text:
            m = MARKER.match(line)
            if m:
                cur = m.group(1)
                continue
            if cur and (cur + "(") in line and not line.strip().startswith(("#", "/*")):
                out.setdefault(cur, line.strip())
                cur = None
    return out


def listing_window(by_name, caller: str, callee: str, before: int = 6) -> list[str]:
    """the caller's instructions leading up to `call <callee>`, when IDA has them."""
    fn = by_name.get(caller)
    if fn is None or fn.va is None:
        return []
    lines = ASM.read_text(encoding="latin1", errors="replace").splitlines()
    body = [l.rstrip() for l in lines[fn.asm_start:fn.asm_end]]
    for i, line in enumerate(body):
        if re.search(r"\bcall\s+" + re.escape(callee) + r"\b", line):
            return body[max(0, i - before):i + 1]
    return []


def byte_hint(pe, by_name, caller: str, callee: str) -> str:
    fn = by_name.get(caller)
    if fn is None or fn.va is None:
        return "no listing and no address: nothing to look at here"
    try:
        code = pe.read(fn.va, max(1, fn.size))
    except ValueError:
        return "not inside a section?"
    target = by_name.get(callee)
    tva = target.va if target else None
    for i in range(len(code) - 5):
        if code[i] != 0xE8:
            continue
        tgt = fn.va + i + 5 + struct.unpack_from("<i", code, i + 1)[0]
        if tva is not None and tgt != tva:
            continue
        last = None
        j = 0
        while j < i:
            hit = next((d for p, d in WRITERS.items() if tuple(code[j:j + len(p)]) == p), None)
            if hit:
                last = (hit, j)
                j += 1
            else:
                j += 1
        if last is None:
            return "byte scan: no ECX write seen -> ECX is probably the incoming this"
        raw = " ".join(f"{b:02x}" for b in code[last[1]:last[1] + 10])
        return (f"byte scan hint at +{last[1]}: {last[0]}  [{raw}]"
                f"   ({i - last[1]} bytes before the call)")
    return "no call to the callee found in the bytes"


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py --chunk 480 first")
    text = log.read_text(encoding="latin1", errors="replace")
    files = chunks()
    defs = definitions(files)

    sites = collections.defaultdict(list)
    for fname, line, code, msg in ERROR_RE.findall(text):
        if code != "C2198":
            continue
        m = CALL_RE.match(msg)
        if not m:
            continue
        src, own = files.get(fname, ([], {}))
        i = int(line)
        sites[m.group(1)].append((own.get(i, "?"), src[i - 1].strip() if i <= len(src) else ""))

    wanted = sys.argv[sys.argv.index("--callee") + 1] if "--callee" in sys.argv else None
    wanted = [wanted] if wanted else sorted(sites, key=lambda c: -len(sites[c]))
    if not wanted:
        print("no C2198 sites in the log")
        return 0

    by_name = {f.name: f for f in with_sizes(parse_listing(ASM))}
    pe = PE(EXE)
    total = sum(len(sites[c]) for c in wanted)

    print(f"{len(wanted)} callee(s), {total} site(s).  Evidence per site, then a suggested row.\n")
    for callee in wanted:
        if callee not in sites:
            print(f"== {callee}: no sites in this log")
            continue
        print(f"== {callee}   ({len(sites[callee])} site(s))")
        print(f"   declared: {defs.get(callee, '?')}")
        for caller, call in sites[callee]:
            print(f"   from {caller}: {call[:70]}")
            window = listing_window(by_name, caller, callee)
            if window:
                for line in window:
                    print(f"        | {line.strip()}")
            else:
                print(f"        | {byte_hint(pe, by_name, caller, callee)}")
            print(f"        -> suggested: insert the value ECX holds as the first argument")
        print()
    print("Record the fix in src_generated/bulk_patches.csv (quote fields containing commas),")
    print("then re-measure: tools/compile_check.py --chunk 480 should lose those sites.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
