"""gen_link_stubs.py - give the bulk image a definition for every symbol it misses.

The decompiled program references things a rebuild does not contain yet:

  * 55 code labels Ghidra turned into `LAB_xxxx` values (SEH handlers, jump tables),
  * the ~39 game functions whose bodies are still excluded from the compile (the
    `unaff_*` / `in_stack_*` artefact class and the two undecompilable giants),
  * the ~37 Miles Sound System entry points (`_AAL_*`),
  * Win32/COM/DirectX/Miles APIs and MSVC 6 CRT internals that the modern system
    libraries do not export under the spelling the call sites use,
  * `ExceptionList`, the SEH chain head - the shim models it as a global, and a
    global needs a definition like any other.

Writing those definitions makes the image *link*; it does not make it *work*.  So this
tool is deliberately loud about what it emits: every stub is classified, counted, and
written to src_generated/link_stubs.csv, and the ones that would silently compute the
wrong thing (the 64-bit divide helpers `__alldiv`/`__aulldiv`/`__allmul`/`__allshl`)
are called out separately in the summary - a stub for `__alldiv` returns 0 for every
64-bit division, which is worse than an unresolved symbol if anything runs it.

Signatures are copied from the generated headers when they exist (so a stub cannot
disagree with the prototype the compiler already saw), and fall back to

    RET name(args)

    { return 0; }        or `{ }` for a void return.

    python tools/compile_check.py            # keep the objects fresh
    harness\\build_dlls.bat bulk              # fails once, writing _bulk_link.log
    python tools/gen_link_stubs.py           # ...then generate the stubs
    harness\\build_dlls.bat bulk              # ...and link again
"""

from __future__ import annotations

import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
LOG = BUILD / "_bulk_link.log"
HEADERS = [OUT / "ghidra_prototypes.h", OUT / "ghidra_globals.h",
           ROOT / "include" / "ghidra_shim.h"]

# the linker diagnostics are localised, so match the marker and take the next token
SYMBOL_RE = re.compile(r"(?:simbolo\s+esterno|external\s+symbol)\s+([^\s:]+)")

# stubs for these would quietly compute the wrong answer; they are listed separately
# Implemented for real in harness/crt_aliases.c (they are ordinary CRT calls that a
# stub would break: a stub for `_malloc` returns NULL for every allocation).
REAL_CRT = {
    "_malloc", "_free", "operator_new", "_memset", "_memcpy", "_memmove",
    "_strlen", "_strcmp", "_strncmp", "_strncpy", "_strcmpi", "_strrchr",
    "_fcos", "_fsin", "__ftol", "__frnd",
}

DANGEROUS = {
    "__alldiv": "64-bit signed divide helper (MSVC 6 convention: args in EDX:EAX/stack)",
    "__aulldiv": "64-bit unsigned divide helper",
    "__aullrem": "64-bit unsigned remainder helper",
    "__allmul": "64-bit multiply helper",
    "__allshl": "64-bit shift helper",
    "_fptan": "x87 tan helper (operand on the FPU stack, not a C call)",
    "_fpatan": "x87 atan helper",
    "_flsall": "x87 80-bit load/store helper (float10 conversions)",
    "__cfltcvt": "MSVC 6 float->string conversion helper",
    "__fassign": "MSVC 6 float formatting helper",
}


def unresolved() -> set[str]:
    if not LOG.exists():
        raise SystemExit(f"{LOG} missing - run harness/build_dlls.bat bulk once")
    text = LOG.read_text(encoding="latin1", errors="replace")
    syms = set()
    for line in text.splitlines():
        if "LNK2001" not in line and "LNK2019" not in line:
            continue
        for m in SYMBOL_RE.finditer(line):
            syms.add(m.group(1))
    return syms


def declarations() -> dict[str, str]:
    """C-level name -> its declaration text, from the generated headers."""
    out: dict[str, str] = {}
    for path in HEADERS:
        if not path.exists():
            continue
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            # the generated headers carry trailing comments (`void LAB_x();   /* code
            # label used as a value */`) - without stripping them the parser misses the
            # declaration and the stub falls back to `int name()`, which then collides
            # with the real prototype (C2371, measured)
            line = re.sub(r"/\*.*?\*/", "", line).strip()
            if not line.endswith(";") or line.startswith(("#", "/*", "*")):
                continue
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", line)
            if m:
                out.setdefault(m.group(1), line.rstrip(";"))
                continue
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*(\[[^\]]*\])?;$", line)
            if m:
                out.setdefault(m.group(1), line.rstrip(";"))
    return out


def c_name(sym: str) -> tuple[str | None, str]:
    """(C spelling, note).  None => cannot be expressed as a C symbol."""
    if sym.startswith("__imp__"):
        return None, "import-address entry: needs the import library, '@' is not legal in C"
    if sym.startswith("_?"):
        return None, "C++ mangled name"
    if sym.startswith("_") and "@" in sym:
        name, _, n = sym[1:].partition("@")
        try:
            argc = int(n) // 4
        except ValueError:
            return None, "malformed stdcall decoration"
        args = ",".join(["int"] * argc) if argc else "void"
        return f"__stdcall {name}({args})", f"stdcall with {argc} argument(s)"
    if sym.startswith("_"):
        return sym[1:], ""
    return sym, ""


def body_for(name: str, decl: str | None) -> str:
    """A definition for one symbol.

    Three cases, and the difference matters:
      * the headers declare a *datum* (ExceptionList) -> define the datum, or the
        definition would be a stray statement and C would reject the file;
      * the headers declare a *function* -> copy the declaration verbatim and add a
        body, so the stub cannot disagree with the prototype the compiler already saw;
      * nothing declares it (the Miles entry points, most CRT internals) -> a
        K&R-style function stub: `int name()`, which accepts any arguments the call
        sites pass (measured: MSVC accepts that for every arity).
    """
    if decl and "(" not in decl:
        return decl.replace("extern ", "").strip() + ";\n"
    full = (decl or f"int {name}()").replace("extern ", "").strip()
    rtype = full.split("(")[0].strip()
    empty = rtype.startswith("void") and "*" not in rtype
    return f"{full}\n{{\n    {'' if empty else 'return 0;'}\n}}\n"


def main() -> int:
    syms = unresolved()
    if not syms:
        print(f"nothing unresolved in {LOG.name} - the image links clean")
        return 0
    decls = declarations()

    rows = []
    not_stubbable = []
    for sym in sorted(syms):
        name, note = c_name(sym)
        if name is None:
            not_stubbable.append((sym, note))
            continue
        # the C identifier of `__stdcall f(...)` is `f`; look that up
        lookup = re.sub(r"^__stdcall\s+", "", name).split("(")[0].strip()
        if lookup in REAL_CRT:
            continue          # harness/crt_aliases.c implements this one properly
        decl = decls.get(lookup)
        rows.append({"symbol": sym, "c_name": lookup, "kind": kind_of(sym),
                     "declaration": (decl or name), "note": note})

    lines = ["/* generated by tools/gen_link_stubs.py - do not edit",
             " * Stubs so the whole bulk links.  Every entry is one piece of the original",
             " * that is not real code yet: see src_generated/link_stubs.csv. */",
             '#include "ghidra_shim.h"', '#include "ghidra_globals.h"',
             '#include "ghidra_prototypes.h"', ""]
    counts: dict[str, int] = {}
    for r in rows:
        lines.append(f"/* {r['kind']}: {r['symbol']} */")
        lines.append(body_for(r["c_name"], decls.get(r["c_name"])))
        counts[r["kind"]] = counts.get(r["kind"], 0) + 1
    (OUT / "link_stubs.c").write_text("\n".join(lines), encoding="utf-8")

    with (OUT / "link_stubs.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=["symbol", "c_name", "kind", "note",
                                           "declaration"])
        w.writeheader()
        w.writerows(rows)

    print(f"wrote {OUT.name}/link_stubs.c: {len(rows)} stubs")
    for k, v in sorted(counts.items(), key=lambda kv: -kv[1]):
        print(f"   {k:<28} {v}")
    if not_stubbable:
        print(f"\n{len(not_stubbable)} symbol(s) cannot be stubbed from C:")
        for sym, note in not_stubbable:
            print(f"   {sym:<44} {note}")
    dangerous = [r for r in rows if r["c_name"] in DANGEROUS]
    if dangerous:
        print(f"\n[!] {len(dangerous)} stub(s) would compute a *wrong* result if executed:")
        for r in dangerous:
            print(f"   {r['c_name']:<12} {DANGEROUS[r['c_name']]}")
    return 0


def kind_of(sym: str) -> str:
    if sym.startswith("_LAB_") or sym.startswith("_Catch_") or sym.startswith("_Unwind_"):
        return "code label"
    if sym.startswith("_sub_"):
        return "game function (body still excluded)"
    if "AAL_" in sym or "AIL_" in sym:
        return "Miles sound API"
    if sym.startswith("___") or sym in (
            "_builtin_strncpy", "_CARRY4", "_SQRT", "_SUB104", "_LOCK", "_UNLOCK",
            "_fcos", "_fsin", "_fptan", "_fpatan", "_flsall", "_timeGetTime"):
        return "MSVC 6 CRT / compiler helper"
    if sym in ("_CoCreateInstance", "_CoInitialize", "_CoUninitialize", "_ExceptionList",
               "_timeGetTime", "_DirectDrawCreate", "_DirectDrawEnumerateA",
               "_DirectDrawEnumerateExA", "_DirectInputCreateA"):
        return "Win32/COM/DirectX API"
    return "other"


if __name__ == "__main__":
    raise SystemExit(main())
