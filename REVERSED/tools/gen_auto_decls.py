"""gen_auto_decls.py - declare the locals and parameters Ghidra forgot.

A recurring `C2065` ("undeclared identifier") class in the bulk is not a bug in the
decompiled *logic*: the function uses `_param_9`, `local_50` or `hdc`, but the
decompiler never emitted a declaration for it (it happens when a value arrives in a
register on entry, or after an unresolved jump table).  The name, the function and the
use are all visible in the compiler's output, so the declaration can be generated:

    NAME->x   or  *NAME  or  NAME[    ->  a pointer
    otherwise                         ->  an int

The result goes to src_generated/auto_decls.csv, which make_bulk.py injects at the top
of the function body.  These declarations are *approximate* by construction - a
pointer where the real code held an integer still compiles and still has the right
width - so they are recorded in their own file rather than mixed into the
hand-checked patch table.

    python tools/compile_check.py   # fresh log first
    python tools/gen_auto_decls.py
"""

from __future__ import annotations

import csv
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
TARGET = OUT / "auto_decls.csv"

ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")
NAME_RE = re.compile(r"^(_?param_[0-9a-f]+|local_[0-9a-f]+|[a-z][a-z0-9]{1,6})$")
SKIP = {"int", "char", "float", "double", "void", "long", "short", "unsigned", "signed",
        "size_t", "file", "code", "bool", "byte", "uint", "ushort", "uchar", "ulong",
        "nan", "null", "true", "false"}


def chunk_owners(fname: str) -> dict[int, str]:
    """line number -> the function that owns it, from the `==== name ====` markers."""
    try:
        lines = (OUT / "chunks" / fname).read_text(encoding="utf-8", errors="replace").splitlines()
    except FileNotFoundError:
        return {}
    cur, own = "?", {}
    for i, line in enumerate(lines, 1):
        hit = re.match(r"^/\* ==== ([\w@]+) ==== \*/", line)
        if hit:
            cur = hit.group(1)
        own[i] = cur
    return own


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py first")
    text = log.read_text(encoding="latin1", errors="replace")

    owners: dict[str, dict[int, str]] = {}
    sources: dict[str, list[str]] = {}
    decls: dict[tuple[str, str], str] = {}

    for fname, line_no, code, _msg in ERROR_RE.findall(text):
        if code != "C2065":
            continue
        if fname not in owners:
            owners[fname] = chunk_owners(fname)
            try:
                sources[fname] = (OUT / "chunks" / fname).read_text(
                    encoding="utf-8", errors="replace").splitlines()
            except FileNotFoundError:
                sources[fname] = []
        names = re.findall(r"'([^']+)'", _msg)
        if not names:
            continue
        name = names[0]
        if not NAME_RE.match(name) or name in SKIP:
            continue
        fn = owners[fname].get(int(line_no), "?")
        if fn == "?":
            continue
        src = sources[fname]
        use = src[int(line_no) - 1] if 0 < int(line_no) <= len(src) else ""
        pointer = (re.search(re.escape(name) + r"\s*(?:->|\[)", use) is not None
                   or re.search(r"\*\s*" + re.escape(name) + r"\b", use) is not None)
        decls[(fn, name)] = "unsigned int *" if pointer else "int"

    with TARGET.open("w", newline="", encoding="utf-8") as fh:
        w = csv.writer(fh)
        w.writerow(["function", "name", "type"])
        for (fn, name), ctype in sorted(decls.items()):
            w.writerow([fn, name, ctype])
    print(f"wrote {TARGET} with {len(decls)} declarations "
          f"for {len({fn for fn, _ in decls})} functions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
