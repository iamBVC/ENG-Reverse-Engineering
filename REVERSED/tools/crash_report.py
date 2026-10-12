"""crash_report.py - turn "it segfaults" into a function name.

    python tools/crash_report.py [path\\to\\groove_rebuild.exe]

Runs the rebuild under gdb, then resolves each backtrace frame through the
linker map that `harness/build_dlls.bat` now writes (build/groove_rebuild.map).

Two things make an absolute address useless on its own, and this script handles
both:

  * the image is relocated, so subtract the module handle - which `exe_main.c`
    logs as `hInst=` in groove_trace.log;
  * the map records addresses at its *preferred* base, so the map address is
    converted the same way before the lookup.

Resolution is interval-based: a frame is reported as `<symbol>+<offset>` together
with the distance to the next following symbol, because a large offset means the
frame is really in a region the map does not name (a static CRT object, say) and
should not be trusted to that symbol.

gdb is expected at $GDB or D:\\Programmi\\MinGW\\bin\\gdb.
"""
from __future__ import annotations

import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent          # ...\REVERSED
MAP = ROOT / "build" / "groove_rebuild.map"
TRACE = ROOT / "build" / "run" / "groove_trace.log"

def default_exe() -> Path:
    """The run-directory copy is the one with the game's assets next to it."""
    run_dir = ROOT / "build" / "run" / "groove_rebuild.exe"
    return run_dir if run_dir.exists() else ROOT / "build" / "groove_rebuild.exe"


exe = Path(sys.argv[1]) if len(sys.argv) > 1 else default_exe()
print("target:", exe)
gdb = os.environ.get("GDB", r"D:\Programmi\MinGW\bin\gdb")


def load_map() -> tuple[int, list[tuple[int, str]]]:
    """(preferred base, [(address, name)] sorted) from the linker's map."""
    if not MAP.exists():
        raise SystemExit(f"no map file at {MAP} - build with harness\\build_dlls.bat")
    pref = None
    ents: list[tuple[int, str]] = []
    for line in MAP.read_text(encoding="latin1", errors="replace").splitlines():
        # the map writes addresses with lowercase hex digits as often as not, so
        # match both cases - an uppercase-only pattern silently dropped ~80% of the
        # symbols and made every resolution look "coarse" (measured)
        m = re.match(r"\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+(\S+)\s+([0-9A-Fa-f]{8})", line)
        if m:
            ents.append((int(m.group(4), 16), m.group(3)))
        m2 = re.match(r"\s*Preferred load address is ([0-9A-Fa-f]+)", line)
        if m2:
            pref = int(m2.group(1), 16)
    if pref is None:
        raise SystemExit("map has no preferred load address")
    ents.sort()
    return pref, ents


def main() -> int:
    pref, ents = load_map()

    if TRACE.exists():
        TRACE.unlink()
    run = subprocess.run(
        [gdb, "-batch", "-ex", "run", "-ex", "bt 14",
         "-ex", "info registers eip eax ecx edx esp",
         "--args", str(exe)],
        cwd=exe.parent, capture_output=True, text=True, timeout=300, errors="replace",
    )
    if not run.stdout and not run.stderr:
        print("[!] gdb produced no output - is it at %s ?" % gdb)
    text = run.stdout + run.stderr

    trace = TRACE.read_text(errors="replace") if TRACE.exists() else ""
    m = re.search(r"hInst=([0-9A-Fa-f]+)", trace)
    if not m:
        print("[!] no hInst in groove_trace.log - cannot derelocate; showing raw")
        base = None
    else:
        base = int(m.group(1), 16)
        print("module base = 0x%08X (map preferred base 0x%08X)" % (base, pref))

    print("\ntrace tail:")
    for line in trace.strip().splitlines()[-8:]:
        print("   ", line.rstrip())

    print("\ngdb:")
    for line in text.splitlines():
        s = line.strip()
        if not ("SIGSEGV" in s or re.match(r"^#\d", s) or s.startswith(("eip", "eax", "ecx", "edx", "esp"))):
            continue
        note = ""
        mm = re.match(r"^#\d+\s+0x([0-9a-fA-F]+)", s)
        if mm and base is not None:
            rva = int(mm.group(1), 16) - base
            prev = nxt = None
            for a, n in ents:
                if a - pref <= rva:
                    prev = (a, n)
                elif nxt is None:
                    nxt = (a, n)
                    break
            if prev is None:
                note = "   -> rva 0x%X is before every symbol" % rva
            else:
                gap = (nxt[0] - prev[0]) if nxt else -1
                note = "   -> rva 0x%06X  %s+0x%X   (next symbol %s, %d bytes away)" % (
                    rva, prev[1], rva - (prev[0] - pref), nxt[1] if nxt else "-", gap)
                if gap > 0x2000:
                    note += "  <- offset too large to trust"
        print("   ", s[:100] + note)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
