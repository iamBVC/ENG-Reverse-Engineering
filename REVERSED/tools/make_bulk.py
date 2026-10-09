"""make_bulk.py - turn the Ghidra output into translation units a compiler can chew.

Reads `REVERSED/decompiled/` (produced by tools/ghidra_decompile.bat) and writes
into `REVERSED/src_generated/`:

    ghidra_globals.c      definitions for every DAT_/UNK_/off_/... the C refers to
                          (with the sizes Ghidra recorded), real float/double
                          constants read straight out of groove.exe, and #define
                          aliases so `_DAT_xxxx` and `DAT_xxxx` alias one object
    ghidra_prototypes.h   a prototype for every decompiled function
    bulk_all.c            every function body in address order (the full rebuild)
    clean_subset.c        only the functions whose C needs no hand fixing
    report.txt            how many functions landed in each bucket, and why

The two buckets matter: `clean_subset.c` is what can plausibly compile today,
`bulk_all.c` is the whole game and is the long-term target.

    python tools/make_bulk.py
    python tools/make_bulk.py --compile     also try compiling the clean subset
"""

from __future__ import annotations

import csv
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pe_tools import PE  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DEC = ROOT / "decompiled"
OUT = ROOT / "src_generated"

# identifiers Ghidra emits for data it could not name
SYMBOL_RE = re.compile(
    r"\b((?:DAT|UNK|PTR|_DAT|_UNK|off|s|byte|word|dword|flt|dbl|uRam)_[0-9a-fA-F]{6,8})\b")

# partial-register / partial-call knowledge: the decompiler knew a value was in a
# register on entry or left in one on exit, so a human has to look at the caller.
ARTIFACT_RE = re.compile(
    r"\b(unaff_[A-Z0-9]+|extraout_[A-Z0-9]+|in_[A-Z]{2,3}|in_stack_[0-9A-Fa-f]+|"
    r"uRam[0-9a-fA-F]+|baddata|halt_baddata|__in\(|__out\(|func_0x)")

FUNC_RE = re.compile(r"^(?:[A-Za-z_][\w \*]*?\s)?(sub_[0-9A-F]{6})\s*\(([^;{]*)\)\s*$", re.M)


IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

# Ghidra idioms that need rewriting before a C compiler will take the source.
# `x._<offset>_<size>_` is how the decompiler names an unnamed struct/union field;
# `NAME_<size>` is a sub-part of a datum at the same address.
# the value carrying a sub-field can be indexed or reached through a pointer:
# `x[i]._0_1_`, `p->f._2_2_` are the same idea as `x._0_1_`
FIELD_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*(?:\s*\[[^\]]*\]|->[A-Za-z_][A-Za-z0-9_]*)*)\._(\d+)_(\d+)_")
FIELD_WRITE_RE = re.compile(
    r"^([ \t]*)([A-Za-z_][A-Za-z0-9_]*)\._(\d+)_3_ = ([^;]+);", re.M)
SUBNAME_RE = re.compile(r"\b((?:DAT|UNK|_DAT|_UNK)_[0-9a-fA-F]{8})_([0-9])\b")
LABREF_RE = re.compile(r"&(LAB_[0-9a-fA-F]{8})\b")
LABDEF_RE = re.compile(r"^(LAB_[0-9a-fA-F]{8}):", re.M)
# Ghidra names the SEH unwind blocks and catch handlers it synthesises; they are
# *code* labels, and some share an address with a data symbol, so they must never
# be aliased onto the data name.
CODE_LABEL_RE = re.compile(r"\b((?:Unwind|Catch|LAB)_[0-9a-fA-F]{8})\b")

FIELD_MACRO = {1: "G_BYTE", 2: "G_WORD", 4: "G_DWORD"}

# The binary's CRT / DirectX / Miles code is not game logic: in a rebuild it comes
# from the system, and Ghidra's names for it (`operator_new`, `_malloc`,
# `DirectDrawCreate`, `RtlUnwind`, `__CxxThrowException@8`) either collide with the
# real headers or are not legal identifiers.  Only the game's own functions are
# generated - declaring `RtlUnwind` ourselves, for instance, made *every* chunk
# fail with C2373 against winnt.h.
GAME_FUNC_RE = re.compile(r"^(sub_[0-9A-F]{6}|Catch_|Unwind_|entry$)")


def is_game_code(name: str) -> bool:
    return bool(GAME_FUNC_RE.match(name))


def normalize(body: str) -> str:
    """Rewrite the Ghidra-isms that stop a C compiler accepting the source.

    First a naming difference: Windows names the LARGE_INTEGER struct member `u`
    where Ghidra prints `s`.  Same layout, different name, so map the access.

    Kept deliberately conservative: only patterns whose meaning is unambiguous
    (a sub-field of a variable, or a sub-part of a named datum) are touched.
    """
    body = body.replace(".s.LowPart", ".u.LowPart").replace(".s.HighPart", ".u.HighPart")

    # `__fastcall` / `__stdcall` on a *generated* body is an error generator:
    #   * a prototype with an empty parameter list is rejected for them (C2709), so
    #     make_bulk emitted no prototype at all;
    #   * then a call that appears *before* the definition made MSVC invent an
    #     implicit `int name()` declaration (cdecl), which the definition contradicts
    #     - C2373 "redefinition; different type modifiers", measured on 9 functions
    #     (e.g. `sub_40E080()` called at chunk_002 line 250, defined `__fastcall` at
    #     271).
    # Dropping the keyword makes both the caller and the callee cdecl, which is the
    # same approximation the shim already makes for `__thiscall`, and it is
    # self-consistent inside a rebuild: the decompiled call sites do not set up
    # registers for these arguments anyway.  The hand-ported track in src/ keeps the
    # real keyword, because there it buys byte-exactness.
    body = re.sub(r"\b__(?:fastcall|stdcall)\s*", "", body)

    # A label has to be followed by a *statement*: Ghidra writes labels at the end of
    # a block (`LAB_004054a3:` on the line before `}`), and C rejects that - MSVC
    # reports it as C2143 "missing ';' before '}'", which points at the brace rather
    # than at the label.  A null statement after every label is harmless when the
    # label is followed by real code, and fixes it when it is not (2 functions).
    body = re.sub(r"^((?:LAB|Catch|Unwind)_[0-9a-fA-F]+):[ \t]*$", r"\1: ;", body, flags=re.M)

    # writes of a 3-byte field must become a statement, not an lvalue
    body = FIELD_WRITE_RE.sub(lambda m: f"{m.group(1)}G_WR3({m.group(2)}, {m.group(3)}, {m.group(4)});",
                              body)

    def field(m):
        var, off, size = m.group(1), m.group(2), int(m.group(3))
        if size == 3:
            return f"G_RD3({var}, {off})"
        macro = FIELD_MACRO.get(size)
        return f"{macro}({var}, {off})" if macro else f"G_DWORD({var}, {off})"

    body = FIELD_RE.sub(field, body)

    def subname(m):
        base, size = m.group(1), int(m.group(2))
        macro = {1: "G_BYTE", 2: "G_WORD"}.get(size, "G_DWORD")
        return f"{macro}({base}, 0)"

    return SUBNAME_RE.sub(subname, body)


def definition_signature(body: str) -> str | None:
    """The full signature Ghidra wrote above the function's opening brace.

    Ghidra wraps long parameter lists over several lines, so the signature is
    every consecutive non-blank line going back from the lone `{` - taking only
    the last one produces garbage like `LPRECT param_6);`.
    """
    lines = body.splitlines()
    for i, line in enumerate(lines):
        if line.strip() == "{":
            j = i - 1
            while j >= 0 and not lines[j].strip():       # skip the blank line
                j -= 1
            parts: list[str] = []
            while j >= 0:
                s = lines[j].strip()
                if not s or s.startswith("/*") or s.startswith("*"):
                    break
                parts.insert(0, s)
                j -= 1
            if parts:
                return " ".join(" ".join(parts).split())
            break
    return None


# `local_1c`, `uStack_148`, `stack0xfffffebf` ... : stack slots Ghidra names.
LOCAL_USE_RE = re.compile(r"\b((?:local|uStack|iStack|stack0x|pvStack|cStack|bStack|sStack)_[0-9a-fA-F]+)\b")
LOCAL_DECL_RE = re.compile(r"^[ \t]*(?:[A-Za-z_][A-Za-z0-9_]*[ \t\*]+)+(local_[0-9a-fA-F]+)\b", re.M)


def undeclared_locals(body: str) -> set[str]:
    """Stack variables the decompiler used but never declared.

    A known Ghidra quirk (usually after an unresolved jump table): the function
    has to be fixed by hand, so these are reported rather than papered over.
    """
    decls = {m for m in re.findall(r"^[ \t]*[A-Za-z_][A-Za-z0-9_]*[ \t\*]*\b(local_[0-9a-fA-F]+)\b", body, re.M)}
    decls |= {m for m in re.findall(r"^[ \t]*[^;\n]*\b(uStack_[0-9a-fA-F]+|iStack_[0-9a-fA-F]+)\b[ \t]*;", body, re.M)}
    used = set(LOCAL_USE_RE.findall(body))
    return used - decls


def sanitize_name(name: str) -> str:
    """`Catch@0040fb87` -> `Catch_0040fb87`.

    Ghidra's exception analysis names catch blocks with an embedded address,
    which is not a legal C identifier.
    """
    return re.sub(r"[^A-Za-z0-9_]", "_", name)



# Only labels that carry a literal value count as evidence: IDA names plenty of
# slots `flt_xxxxxxxx dd ?` by guessing from the bytes, and those turned out to be
# fixed-point integers (e.g. 0x6DA2D0, used as `A*A + B*B >> 12`).
FLOAT_LABEL_RE = re.compile(r"^(flt|dbl)_([0-9A-Fa-f]{6,8})\s+d[dbq]\s+[-0-9]", re.M)


def float_symbols(asm_path: Path) -> dict[int, str]:
    """address -> 'float'/'double', from the listing's own data labels.

    Ghidra records these as `undefined4`, but the listing names them `flt_xxxxxx`
    with the value, which is exactly the evidence needed: using them as integers
    produced ~200 type errors in the bulk.
    """
    out: dict[int, str] = {}
    if not asm_path.exists():
        return out
    text = asm_path.read_text(encoding="latin1", errors="replace")
    for kind, addr in FLOAT_LABEL_RE.findall(text):
        out[int(addr, 16)] = "float" if kind == "flt" else "double"
    return out


def addr_of(name: str) -> int | None:
    m = re.search(r"([0-9a-fA-F]{6,8})$", name)
    if not m:
        return None
    return int(m.group(1), 16)


def main() -> int:
    OUT.mkdir(exist_ok=True)
    files = sorted(p for p in DEC.glob("*.c"))   # note: real functions named _fread etc. exist
    if not files:
        print(f"no decompiled sources in {DEC}; run tools/ghidra_decompile.bat first")
        return 1

    exe = PE(ROOT.parent / "WAD" / "groove.exe")

    # ---- data symbols Ghidra knows about ---------------------------------
    data: dict[int, tuple[str, int, str]] = {}
    data_csv = DEC / "_data.csv"
    if data_csv.exists():
        with data_csv.open(encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                a = addr_of(row["name"])
                if a is None:
                    continue
                try:
                    size = int(row["size"])
                except ValueError:
                    size = 4
                data.setdefault(a, (row["name"], max(1, size), row["datatype"]))

    # ---- rename anything that is not a legal C identifier -------------------
    # Two sources: the function list (Ghidra's exception analysis writes
    # `Catch@<addr>`) and the data symbol table (string labels come straight from
    # the program: `s_Couldn't_open_mode_00571660`).  The mapping has to be
    # applied to the bodies as well, otherwise the two disagree.
    renames: dict[str, str] = {}
    _used: set[str] = set()

    def need_rename(name: str) -> str:
        if IDENT_RE.match(name):
            return name
        if name in renames:
            return renames[name]
        safe = sanitize_name(name)
        while safe in _used:
            safe += "_"
        renames[name] = safe
        _used.add(safe)
        return safe

    for a, (nm, _sz, _dt) in data.items():
        safe = need_rename(nm)
        if safe != nm:
            data[a] = (safe, _sz, _dt)

    protos: dict[str, str] = {}
    fn_csv = DEC / "_functions.csv"
    if fn_csv.exists():
        with fn_csv.open(encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                raw = row["name"]
                if not is_game_code(raw):
                    continue          # CRT / DirectX / Miles: the system provides it
                safe = need_rename(raw)
                protos[safe] = row["signature"].replace(";", ",").replace(raw, safe)

    # ---- collect referenced data symbols ---------------------------------
    # Hand fixes for the per-site problems: decompiler artefacts and type mismatches
    # that no generator rule can decide (see the note in README).  Keeping them in a
    # CSV means every fix is recorded, reviewable and survives regeneration - which
    # is how the ~200-function queue is meant to be worked through.
    # Declarations for locals/parameters Ghidra never emitted (tools/gen_auto_decls.py):
    # approximate by construction, so they live in their own file rather than in the
    # hand-checked patch table.
    auto_decls: dict[str, list[tuple[str, str]]] = {}
    decl_path = OUT / "auto_decls.csv"
    if decl_path.exists():
        with decl_path.open(encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                auto_decls.setdefault(row["function"], []).append((row["name"], row["type"]))

    bulk_patches: dict[str, list[tuple[str, str]]] = {}
    patch_path = OUT / "bulk_patches.csv"
    if patch_path.exists():
        with patch_path.open(encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                bulk_patches.setdefault(row["function"], []).append((row["find"], row["replace"]))

    bodies: dict[str, str] = {}
    signatures: dict[str, str] = {}
    referenced: dict[int, set[str]] = {}
    patched = 0
    injected = 0
    for path in files:
        if not is_game_code(path.stem):
            continue
        body = path.read_text(encoding="utf-8", errors="replace")
        name = renames.get(path.stem, path.stem)
        for bad, good in renames.items():
            if bad in body:
                body = body.replace(bad, good)
        body = normalize(body)
        for find, repl in bulk_patches.get(name, []):
            if find in body:
                body = body.replace(find, repl)
                patched += 1
            else:
                print(f"  note: patch pattern not found in {name}: {find[:40]!r}")
        if name in auto_decls:
            lines = body.splitlines()
            for i, line in enumerate(lines):
                if line.strip() == "{":
                    inject = ["  " + ctype + " " + nm + ";" for nm, ctype in auto_decls[name]]
                    lines[i + 1:i + 1] = inject
                    body = chr(10).join(lines)
                    injected += len(inject)
                    break
        bodies[name] = body
        sig = definition_signature(body)
        if sig:
            signatures[name] = sig
        # any identifier that ends in an address is a data reference: this covers
        # DAT_/UNK_/off_/s_/flt_ as well as the composed forms Ghidra emits
        # (PTR_DAT_00570340, s___08X__04X_005702a0, ...)
        for m in re.finditer(r"\b([A-Za-z_][A-Za-z0-9_]*?[0-9a-fA-F]{6,8})\b(?![ \t]*\()", body):
            sym = m.group(1)
            if sym.startswith(("sub_", "param_", "local_", "uStack_")):
                continue
            if CODE_LABEL_RE.match(sym):
                continue          # a code label, declared as a function below
            a = addr_of(sym)
            if a is not None:
                referenced.setdefault(a, set()).add(sym)

    # ---- how each data symbol is used, so the definition has the right type --
    # Three different questions, three different pieces of evidence:
    #   * a *unary* dereference        -> the datum holds an address
    #   * `(*DAT_x)(...)`              -> the datum holds a *function* address
    #   * `DAT_x[...]` / `(&DAT_x)[i]` -> the datum is an array
    #
    # The unary `*` test has to tell `*DAT_x` from `a * DAT_x`.  The old lookbehind
    # only inspected the character immediately before the `*` - which is a *space*
    # in `a * DAT_x`, so every global used as a multiplier was declared
    # `unsigned int *` and then failed C2296/C2297/C2440 at the multiplication
    # (23 errors, e.g. `uVar2 = DAT_00583378 * DAT_00583374;`).  Requiring the
    # preceding *token* to be a delimiter is what makes the `*` unary.
    DEREF_RE = re.compile(r"(?:[\n\(\[,;={?:&|+\-*/%!<>~])\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\b")
    CALLPTR_RE = re.compile(r"\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*\(")
    ARRAY_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)[ \t]*\[")
    # `*(&DAT_x)[i]` - the element is dereferenced, so the datum is an array *of
    # pointers*.  The bare `(&DAT_x)[i]` shape must NOT count as array evidence:
    # that is how the decompiler writes a lookup into a table of scalars
    # (`(&DAT_00574318)[uVar8 & 0xfff] * local_20`), and treating it as a pointer
    # turned 4 errors into 45 (measured).
    ARRAY_REF_RE = re.compile(r"\*\s*\(\s*&\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*\[")

    pointer_syms: set[str] = set()
    array_syms: set[str] = set()
    funcptr_syms: set[str] = set()
    # ... and of the function pointers, the ones the Win32 API owns: they are filled
    # by `GetProcAddress` and compared against `(FARPROC)0x0`, which is `__stdcall`,
    # so they must be `FARPROC` - the rest are `code *` (cdecl, `int (*)()`), because
    # they are assigned the address of an internal label (`DAT_0058372c =
    # &LAB_00415010;`).  Declaring the internal ones `FARPROC` fails at the
    # assignment (C2440, 15 errors, measured).
    win32ptr_syms: set[str] = set()
    for body in bodies.values():
        pointer_syms.update(DEREF_RE.findall(body))
        funcptr_syms.update(CALLPTR_RE.findall(body))
        array_syms.update(ARRAY_RE.findall(body))
        array_syms.update(ARRAY_REF_RE.findall(body))
        for line in body.splitlines():
            if "FARPROC" in line or "GetProcAddress" in line:
                win32ptr_syms.update(SYMBOL_RE.findall(line))

    # ---- emit globals -----------------------------------------------------
    # Definitions go in the .c, declarations and aliases in the .h.  Splitting
    # them is what lets the bulk *link*: with everything in one file, every
    # translation unit that included it defined the same globals (LNK2005).
    #
    # Type overrides are per-symbol decisions learned from compiler errors by
    # tools/infer_global_types.py; they take precedence over the heuristics below
    # because they are the only evidence-based source available.
    type_overrides: dict[str, str] = {}
    ov_path = OUT / "type_overrides.csv"
    if ov_path.exists():
        with ov_path.open(encoding="utf-8") as fh:
            type_overrides = {r["name"]: r["type"] for r in csv.DictReader(fh)}

    defs: list[str] = []
    decls: list[str] = []
    for a in sorted(referenced):
        canonical, size, _dt = data.get(a, (f"DAT_{a:08X}", 4, "undefined"))
        if canonical.startswith(("flt_", "dbl_")):
            continue                                   # emitted as constants below
        if _dt == "string":
            # the real bytes are in the executable, so emit the actual literal
            try:
                raw = exe.read(a, size)
            except ValueError:
                raw = b""
            lit = ",".join(str(b) for b in raw)
            defs.append(f"const char {canonical}[] = {{{lit}}};   /* 0x{a:08X} */")
            decls.append(f"extern const char {canonical}[];")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        override = type_overrides.get(canonical)
        if override is not None:
            ctype = {"float": "float", "double": "double",
                     "pointer": "unsigned int *"}.get(override, "int")
            defs.append(f"{ctype} {canonical};   /* 0x{a:08X}, type inferred from use */")
            decls.append(f"extern {ctype} {canonical};")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        if canonical in funcptr_syms:
            # the code calls through it - `(*DAT_x)(...)` - so it holds a function
            # address; which flavour depends on who fills it in (see above).
            ctype = "FARPROC" if canonical in win32ptr_syms else "code *"
        elif canonical in pointer_syms:
            # the decompiler dereferences it, so the datum holds an address
            ctype = "unsigned int *"
        elif canonical in array_syms:
            ctype = "unsigned int *"
        elif size >= 8:
            ctype = "unsigned long long"
        elif size >= 4:
            # `int`, not `unsigned int`: the original compares these slots with
            # signed instructions (`jle`/`jl`), and an unsigned declaration silently
            # changes the result for negative values.  The differential harness
            # caught exactly that in sub_41EF00 (a -8 request returned NULL on the
            # decompiled side and rewound the heap on the hand-ported side).
            ctype = "int"
        elif size == 2:
            ctype = "unsigned short"
        else:
            ctype = "unsigned char"
        if size > 4 and not ctype.endswith("*"):
            # a multi-byte datum is an array in the original; declaring it as one
            # scalar would let the code (and the harness) write past its storage
            elem = {8: "long long", 4: "int"}.get(4, "int")
            count = max(1, (size + 3) // 4)
            defs.append(f"{elem} {canonical}[{count}];   /* 0x{a:08X}, {size} byte(s) */")
            decls.append(f"extern {elem} {canonical}[{count}];")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        defs.append(f"{ctype} {canonical};   /* 0x{a:08X}, {size} byte(s) */")
        decls.append(f"extern {ctype} {canonical};")
        for other in sorted(referenced[a] - {canonical}):
            # only spellings that are legal macro names can be aliased; the others
            # were rewritten in the bodies by the rename pass
            if IDENT_RE.match(other):
                decls.append(f"#define {other} {canonical}")

    # ---- code labels referenced as values (SEH handlers, unwind blocks) -----
    defined_labels = set()
    referenced_labels = set()
    for body in bodies.values():
        defined_labels.update(LABDEF_RE.findall(body))
        referenced_labels.update(LABREF_RE.findall(body))
        referenced_labels.update(CODE_LABEL_RE.findall(body))
    # a Catch_ name may also be a real function (the renamed `Catch@<addr>` ones)
    # Unprototyped on purpose: these blocks are entered with whatever the call
    # site set up (SEH handoff), so a `(void)` declaration would reject the
    # arguments the decompiled code passes.
    for lab in sorted(referenced_labels - defined_labels - set(bodies) - set(protos)):
        decls.append(f"void {lab}();   /* code label used as a value */")

    # ---- emit float/double constants with their real values --------------
    constants: list[str] = []
    for a in sorted(referenced):
        canonical = data.get(a, (f"DAT_{a:08X}", 4, "undefined"))[0]
        try:
            raw = exe.read(a, 8)
        except ValueError:
            continue
        if canonical.startswith("dbl_") and len(raw) >= 8:
            v = struct.unpack_from("<d", raw, 0)[0]
            constants.append(f"const double {canonical} = {v!r};   /* 0x{a:08X} */")
            decls.append(f"extern const double {canonical};")
        elif canonical.startswith("flt_") and len(raw) >= 4:
            v = struct.unpack_from("<f", raw, 0)[0]
            constants.append(f"const float {canonical} = {v!r}f;   /* 0x{a:08X} */")
            decls.append(f"extern const float {canonical};")

    (OUT / "ghidra_globals.c").write_text(
        '/* generated by tools/make_bulk.py - do not edit */\n'
        '#include "ghidra_shim.h"\n'
        '#include "ghidra_globals.h"\n\n'
        "/* ---- data definitions -------------------------------------------- */\n"
        + "\n".join(defs)
        + "\n\n/* ---- floating point constants (values read from groove.exe) ------ */\n"
        + "\n".join(constants) + "\n",
        encoding="utf-8")

    # machine-readable map of address -> generated name, used by tools/make_getters.py
    with (OUT / "symbols.csv").open("w", newline="", encoding="utf-8") as fh:
        w = csv.writer(fh)
        w.writerow(["name", "address", "size"])
        for a in sorted(referenced):
            canonical, size, _dt = data.get(a, (f"DAT_{a:08X}", 4, "undefined"))
            w.writerow([canonical, f"{a:08X}", size])

    (OUT / "ghidra_globals.h").write_text(
        '/* generated by tools/make_bulk.py - do not edit */\n'
        "#ifndef GHIDRA_GLOBALS_H\n#define GHIDRA_GLOBALS_H\n\n"
        "/* externs for the data the decompiled code uses, plus #define aliases for\n"
        "   the spellings Ghidra used for the same address (DAT_x / _DAT_x / PTR_x). */\n"
        + "\n".join(decls)
        + "\n\n#endif\n",
        encoding="utf-8")

    # ---- prototypes -------------------------------------------------------
    # Prefer the signature Ghidra actually wrote in front of the body: a
    # prototype that disagrees with its definition is a C2371 error, and the
    # signature CSV is a second-hand copy of exactly that line.
    for name, sig in signatures.items():
        protos[name] = sig

    # The C runtime and the compiler own the `__`-prefixed names (__alldiv,
    # __frnd, ...): declaring them ourselves collides with the CRT headers, so
    # leave those to the CRT and only keep the bodies.
    for name in list(protos):
        if name.startswith("__"):
            del protos[name]

    # Declare them without a parameter list (K&R style).  Ghidra infers a
    # function's parameters from *one* site, but the same function is called with
    # different argument counts elsewhere in this binary, and a full prototype
    # turns every such site into a hard error (C2197/C2198).  `RET name();` keeps
    # the return type (what the callers actually depend on) and accepts any
    # arguments.  The hand-ported track in src/ keeps its exact prototypes; this
    # loosening applies only to the generated bulk translation unit.
    # A prototype must never be able to break the whole translation unit, so the
    # return type is validated against the types we actually have declarations for
    # and anything unrecognised falls back to `int` (the loose style already
    # accepts any arguments, and the alternative is a syntax error that stops
    # every chunk from compiling).
    KNOWN_RETURN = re.compile(
        r"^(void|char|short|int|long|unsigned|signed|float|double|size_t|"
        r"undefined[0-9]*|uint[0-9]*|int[0-9]*|byte|uchar|ushort|ulonglong|longlong|"
        r"ulong|float10|bool|code|HRESULT|DWORD|WORD|BYTE|BOOL|LONG|UINT|ULONG|"
        r"HANDLE|HWND|HDC|HMODULE|HINSTANCE|LPVOID|LPCVOID|LPCSTR|LPSTR|LPRECT|"
        r"SIZE_T|FARPROC|WPARAM|LPARAM|PVOID|UINT_PTR|LPTOP_LEVEL_EXCEPTION_FILTER|"
        r"EXCEPTION_DISPOSITION|EXCEPTION_POINTERS|EXCEPTION_RECORD|CONTEXT)$")

    # Loosen *only* the parameter list.  Keeping the declared return type verbatim
    # matters: `char *`, `undefined *` and `void __fastcall` all have to survive, or
    # the declaration disagrees with its own definition (C2040 "differs in levels of
    # indirection", C2373 "type modifiers differ", C2371 "different basic types").
    loose: dict[str, str] = {}
    for n, sig in protos.items():
        s = sig.strip()
        if "::" in s or "@" in s:
            continue                       # not expressible in C
        m = re.match(r"^(.*?)\b" + re.escape(n) + r"\s*\(", s)
        rtype = (m.group(1).strip() if m else "")
        if rtype and not rtype.startswith("int") and not KNOWN_RETURN.match(rtype.split()[0]):
            # an unknown Ghidra type (unkbyte10, ...): fall back to int, which is
            # always assignment-compatible in these expressions
            rtype = "int"
        # `__fastcall`/`__stdcall` definitions are cdecl by the time they reach here
        # (normalize() strips the keyword), so the loose prototype really is
        # "unspecified arguments" for them as well.
        loose[n] = f"{rtype} {n}()" if rtype else f"int {n}()"
    protos = loose

    (OUT / "ghidra_prototypes.h").write_text(
        '/* generated by tools/make_bulk.py - do not edit */\n'
        "#ifndef GHIDRA_PROTOTYPES_H\n#define GHIDRA_PROTOTYPES_H\n\n"
        "#include \"ghidra_shim.h\"\n\n"
        + "\n".join(f"{p};" for p in sorted(protos.values()))
        + "\n\n#endif\n",
        encoding="utf-8")

    # ---- buckets ----------------------------------------------------------
    # the header, not the .c: every translation unit needs the declarations, but
    # only ghidra_globals.c may define them (otherwise the link reports LNK2005)
    preamble = ('#include "ghidra_shim.h"\n#include "ghidra_globals.h"\n'
                '#include "ghidra_prototypes.h"\n\n')

    # functions the compiler rejected on the previous pass (compile_check.py writes
    # this): they are excluded so the chunks build, and they form the fix queue
    known_bad: set[str] = set()
    failed_list = OUT / "failed.txt"
    if failed_list.exists():
        known_bad = {ln.strip() for ln in failed_list.read_text(encoding="utf-8").splitlines() if ln.strip()}

    clean: list[str] = []
    dirty: list[str] = []
    reasons: dict[str, int] = {}
    for name in sorted(bodies):
        body = bodies[name]
        hits = set(ARTIFACT_RE.findall(body))
        missing = undeclared_locals(body)
        if hits or missing:
            dirty.append(name)
            for h in hits:
                key = re.sub(r"[0-9a-fA-F]+$", "", h)
                reasons[key] = reasons.get(key, 0) + 1
            if missing:
                reasons["undeclared local"] = reasons.get("undeclared local", 0) + 1
        elif name in known_bad:
            dirty.append(name)
            reasons["compile error (excluded)"] = reasons.get("compile error (excluded)", 0) + 1
        else:
            clean.append(name)

    def emit(path: Path, names: list[str], title: str) -> None:
        with path.open("w", encoding="utf-8") as fh:
            fh.write(f"/* generated by tools/make_bulk.py - {title} */\n")
            fh.write(preamble)
            fh.write(f"/* {len(names)} functions */\n\n")
            for n in names:
                # the marker is what lets the compile log be mapped back to a
                # function, so per-function progress can be counted
                fh.write(f"\n/* ==== {n} ==== */\n")
                fh.write(bodies[n])
                fh.write("\n")

    emit(OUT / "bulk_all.c", sorted(bodies), "every decompiled function")
    emit(OUT / "clean_subset.c", clean, "functions with no decompiler artefacts")

    report = [
        f"decompiled files          : {len(bodies)}", 
        f"data symbols referenced    : {len(referenced)} ({len(defs)} definitions, {len(decls)} declarations/aliases)",
        f"float/double constants     : {len(constants)}",
        f"functions with prototypes  : {len(protos)}",
        f"names sanitised for C      : {len(renames)}",
        f"hand patches applied       : {patched}",
        f"auto declarations injected  : {injected}",
        "",
        f"clean subset (compilable?) : {len(clean)}",
        f"needs hand fixing          : {len(dirty)}",
        f"excluded because they fail to compile: {len(known_bad)}",
        "",
        "artefact reasons (functions affected):",
    ]
    for k, v in sorted(reasons.items(), key=lambda kv: -kv[1]):
        report.append(f"   {k:<16} {v}")
    (OUT / "report.txt").write_text("\n".join(report) + "\n", encoding="utf-8")
    print("\n".join(report))
    print(f"\nwrote {OUT}")

    if "--compile" in sys.argv:
        try_compile()
    return 0


def try_compile() -> None:
    """Delegate to tools/compile_check.py.

    The single-file compile that used to live here was misleading: MSVC stops
    after ~100 errors per translation unit, so most of the file was never checked
    and the "clean" count came out too high (996 instead of the real 901).
    compile_check.py splits the subset into small chunks so every function gets a
    real verdict.
    """
    subprocess.run([sys.executable, str(Path(__file__).resolve().parent / "compile_check.py")])


if __name__ == "__main__":
    raise SystemExit(main())
