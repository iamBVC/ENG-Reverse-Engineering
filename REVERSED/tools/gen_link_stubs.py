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
# both link logs are read when they exist: the DLL's and the exe's (the exe needs
# `entry`, which nothing else references, so it is unresolved only in that one)
LOGS = [BUILD / "_bulk_link.log", BUILD / "_exe_link.log"]
HEADERS = [OUT / "ghidra_prototypes.h", OUT / "ghidra_globals.h",
           ROOT / "include" / "ghidra_shim.h"]

# the linker diagnostics are localised, so match the marker and take the next token
SYMBOL_RE = re.compile(r"(?:simbolo\s+esterno|external\s+symbol)\s+([^\s:]+)")

# stubs for these would quietly compute the wrong answer; they are listed separately
# Implemented for real in harness/crt_aliases.c (they are ordinary CRT calls that a
# stub would break: a stub for `_malloc` returns NULL for every allocation).
# keyed by the *C* name, because that is what the lookup below produces: the linker's
# `_fcos` is the C `fcos`.  Spelling these with the leading underscore (the first
# version of this set did) silently matched nothing and emitted `int fcos()` stubs
# against the real definitions in harness/crt_aliases.c (C2371, measured).
REAL_CRT = {
    "_malloc", "_free", "_memset", "_memcpy", "_memmove", "_strlen", "_strcmp",
    "_strncmp", "_strncpy", "_strcmpi", "_strrchr", "fcos", "fsin", "__ftol",
    "__frnd", "operator_new",
    # SDK declarations now resolve these through Ole32 with their actual ABI.
    "CoCreateInstance", "CoInitialize", "CoUninitialize",
}

# Never stub these, whatever a log says: they belong to <string.h>/<math.h>/<stdlib.h>,
# and a stub both shadows the real implementation for the whole image and collides with
# its prototype (C2371/C2040, measured).  They appear in the *exe* link log because the
# runtime's own startup objects reference them - that is library work, not a stub.
STANDARD_C = {
    "memcpy", "memmove", "memset", "strlen", "strcmp", "strncmp", "strncpy",
    "strrchr", "strcmpi", "stricmp", "malloc", "free", "calloc", "realloc",
    "cos", "sin", "tan", "atan", "atan2", "log", "log2", "log10", "exp",
    "pow", "sqrt", "floor", "ceil", "fabs", "modf", "printf", "sprintf",
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


def log_lines() -> list[str]:
    paths = [Path(p) for p in sys.argv[1:]] or [p for p in LOGS if p.exists()]
    if not paths:
        return []
    out: list[str] = []
    for path in paths:
        out.extend(path.read_text(encoding="latin1", errors="replace").splitlines())
    print(f"reading {len(paths)} link log(s): {', '.join(p.name for p in paths)}")
    return out


def previous_stubs() -> set[str]:
    """The symbols already stubbed.  They have to survive regeneration, or the loop is
    self-defeating: once the stubs make the link succeed the log is *clean*, and
    regenerating from a clean log would emit an empty file and break the build again.
    """
    path = OUT / "link_stubs.csv"
    if not path.exists():
        return set()
    with path.open(encoding="utf-8", newline="") as fh:
        return {r["symbol"] for r in csv.DictReader(fh)}


def now_defined(lines: list[str]) -> set[str]:
    """Symbols the linker sees twice (LNK2005): the *real* code defines them now, so
    their stub has to go.  That is what keeps the list honest as functions land."""
    out = set()
    for line in lines:
        if "LNK2005" in line:
            m = re.search(r"LNK2005:\s+([^\s:]+)", line)
            if m:
                out.add(m.group(1))
    return out


def is_game_symbol(sym: str) -> bool:
    """Game code (stub it) versus system code (link a library for it).

    Needed because the two logs mean different things.  The DLL's log is already
    library-clean, so everything in it is stubbable.  The exe's log also carries the
    runtime's *own* startup internals (`_memcpy`, `_cos`, `__imp__malloc`) - and a stub
    for those is actively wrong: it shadows the CRT's implementation for the whole
    image and collides with it (LNK2005, measured).  Those are library work.
    """
    return (sym.startswith(("_sub_", "_LAB_", "_Catch_", "_Unwind_"))
            or sym in ("_entry", "_ExceptionList"))


def unresolved() -> set[str]:
    paths = [Path(p) for p in sys.argv[1:]] or [p for p in LOGS if p.exists()]
    if not paths:
        raise SystemExit("no link log found - run harness/build_dlls.bat bulk once")
    syms: set[str] = set()
    needs_library: set[str] = set()
    for path in paths:
        exe_log = path.name == "_exe_link.log"
        text = path.read_text(encoding="latin1", errors="replace")
        for line in text.splitlines():
            if "LNK2001" not in line and "LNK2019" not in line:
                continue
            for m in SYMBOL_RE.finditer(line):
                sym = m.group(1)
                if exe_log and not is_game_symbol(sym):
                    needs_library.add(sym)
                else:
                    syms.add(sym)
    print(f"reading {len(paths)} link log(s): {', '.join(p.name for p in paths)}")
    syms |= previous_stubs()
    lines = [ln for p in paths for ln in p.read_text(encoding="latin1", errors="replace").splitlines()]
    for gone in sorted(now_defined(lines) & syms):
        print(f"  dropping {gone}: the real code defines it now (LNK2005)")
    if needs_library:
        print(f"  {len(needs_library)} symbol(s) are the runtime's own and are left to the "
              f"libraries, not stubbed: {', '.join(sorted(needs_library)[:8])}"
              + (" ..." if len(needs_library) > 8 else ""))
    return syms - now_defined(lines)


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
    # A stub that says its own name is how a *run* of the image points at the next piece
    # of work: the first line of output names the function the game needed but does not
    # have.  Printed once per symbol, and harmless in the harness DLL (the drivers never
    # reach a stub, and if one ever does, seeing which is the point).
    report = (f'    static int reported = 0;\n'
              f'    if (!reported++) fprintf(stderr, "[stub] %s\\n", "{name}");\n')
    body = report + ('    return 0;\n' if not empty else '')
    return f"{full}\n{{\n{body}}}\n"


def main() -> int:
    syms = unresolved()
    if not syms:
        print("nothing unresolved in the link log(s) - the image links clean")
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
        if lookup in STANDARD_C:
            continue          # a C library function: the library provides it, not a stub
        decl = decls.get(lookup)
        rows.append({"symbol": sym, "c_name": lookup, "kind": kind_of(sym),
                     "declaration": (decl or name), "note": note})

    lines = ["/* generated by tools/gen_link_stubs.py - do not edit",
             " * Stubs so the whole bulk links.  Every entry is one piece of the original",
             " * that is not real code yet: see src_generated/link_stubs.csv.",
             " *",
             " * Each one reports itself the first time it is called, so running the image",
             " * says *which* missing function it walked into. */",
             "#include <stdio.h>",
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
