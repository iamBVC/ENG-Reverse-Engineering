"""make_dll_source.py - build the chunk set the harness DLL is compiled from.

Identical to src_generated/chunks/, minus the functions the harness replaces with its
own (harness/substituted.txt, and the reasoning in that file's header).  The bulk keeps
its real versions - this filter only affects the DLL that the drivers load, so the
compile-time picture (`clean subset: 968, 0 errors`) is untouched.

    python tools/make_dll_source.py
    harness\\build_dlls.bat bulk
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src_generated" / "chunks"
OUT = ROOT / "build" / "dll_chunks"
MARKER = re.compile(r"^/\* ==== ([\w@]+) ==== \*/", re.M)


def substituted() -> set[str]:
    path = ROOT / "harness" / "substituted.txt"
    if not path.exists():
        return set()
    names = set()
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#")[0].strip()
        if line:
            names.add(line)
    return names


def main() -> int:
    drop = substituted()
    if not SRC.exists():
        raise SystemExit(f"{SRC} missing - run tools/make_bulk.py and tools/compile_check.py")
    OUT.mkdir(parents=True, exist_ok=True)
    for old in OUT.glob("*.c"):
        old.unlink()

    dropped: list[str] = []
    for chunk in sorted(SRC.glob("*.c")):
        text = chunk.read_text(encoding="utf-8", errors="replace")
        first = MARKER.search(text)
        if not first:
            (OUT / chunk.name).write_text(text, encoding="utf-8")
            continue
        preamble = text[:first.start()]
        blocks = re.split(r"(?=^/\* ==== )", text[first.start():], flags=re.M)
        kept = []
        for block in blocks:
            m = MARKER.search(block)
            if m and m.group(1) in drop:
                dropped.append(m.group(1))
                continue
            kept.append(block)
        (OUT / chunk.name).write_text(preamble + "".join(kept), encoding="utf-8")

    print(f"wrote {len(list(OUT.glob('*.c')))} chunk file(s) to build/dll_chunks")
    print(f"  substituted away: {len(dropped)} function(s)"
          + (f" ({', '.join(sorted(dropped))})" if dropped else ""))
    missing = drop - set(dropped)
    if missing:
        print(f"  [!] listed but not found in the chunks: {', '.join(sorted(missing))}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
