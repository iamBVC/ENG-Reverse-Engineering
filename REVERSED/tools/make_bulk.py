"""make_bulk.py - turn the Ghidra output into translation units a compiler can chew.

Reads the complete, address-reconciled Ghidra export and overlays hand-recovered
sources by function identity, then writes into
`REVERSED/src_generated/`:

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
from code_label_aliases import aliases_for_code_labels  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DEC = ROOT / "decompiled_ghidra_complete_20261018_all"
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
CODE_LABEL_RE = re.compile(r"\b((?:Unwind|Catch|LAB|FUN)_[0-9a-fA-F]{6,8})\b")
MANUAL_SWITCH_RE = re.compile(
    r"switch\s*\(\s*\(&switchD_[0-9A-Fa-f]{6,8}::switchdataD_"
    r"(?P<table>[0-9A-Fa-f]{6,8})\s*\)\s*\[\s*(?P<selector>[A-Za-z_]\w*)\s*\]\s*\)\s*\{")
MANUAL_CASE_RE = re.compile(r"case\s+\(undefined\s*\*\)\s*0x([0-9A-Fa-f]+)\s*:")
POINTER_SWITCH_RE = re.compile(r"switch\s*\(\s*(?P<expression>[A-Za-z_]\w*)\s*\)\s*\{")
POINTER_INTEGER_CASE_RE = re.compile(r"case\s+\(float\s*\*\)\s*0x([0-9A-Fa-f]+)\s*:")

FIELD_MACRO = {1: "G_BYTE", 2: "G_WORD", 4: "G_DWORD"}

# The binary's CRT / DirectX / Miles code is not game logic: in a rebuild it comes
# from the system, and Ghidra's names for it (`operator_new`, `_malloc`,
# `DirectDrawCreate`, `RtlUnwind`, `__CxxThrowException@8`) either collide with the
# real headers or are not legal identifiers.  Only the game's own functions are
# generated - declaring `RtlUnwind` ourselves, for instance, made *every* chunk
# fail with C2373 against winnt.h.
GAME_FUNC_RE = re.compile(
    r"^(sub_[0-9A-Fa-f]{6,8}|FUN_[0-9A-Fa-f]{8}|Catch[@_]|Unwind[@_]|entry$)")


def is_game_code(name: str) -> bool:
    return bool(GAME_FUNC_RE.match(name))


def canonical_function_name(name: str) -> str:
    """Normalize address-based names so zero-padded exports share one identity."""
    match = re.fullmatch(r"sub_([0-9A-Fa-f]+)", name)
    if match:
        return f"sub_{int(match.group(1), 16):X}"
    return name


def read_merged_function_fragments(path: Path) -> dict[str, str]:
    """Read Ghidra entries that are verified interior fragments of a parent body."""
    if not path.is_file():
        return {}
    fragments: dict[str, str] = {}
    with path.open(newline="", encoding="utf-8-sig") as stream:
        for row in csv.DictReader(stream):
            fragment = row["fragment"].strip()
            parent = row["parent"].strip()
            if not fragment or not parent or fragment == parent:
                raise ValueError(f"invalid merged function fragment row: {row}")
            if fragment in fragments:
                raise ValueError(f"duplicate merged function fragment: {fragment}")
            fragments[fragment] = parent
    return fragments


def collect_source_files(export_dirs: list[Path], recovered_dir: Path) -> dict[str, tuple[Path, str]]:
    """Merge indexed Ghidra exports and recovered overrides by function name.

    Indexed exports are read from their manifest, not by globbing: stale C files
    left beside an export must not silently enter the build. Indexless supplemental
    exports use their verified function-address filename. Recovered files have the
    highest precedence and are normalized against Ghidra's zero-padded names.
    """
    by_address: dict[int, tuple[str, Path]] = {}
    for directory in export_dirs:
        index_path = directory / "_index.csv"
        if index_path.exists():
            with index_path.open(newline="", encoding="utf-8-sig") as fh:
                rows = csv.DictReader(fh)
                for row in rows:
                    raw_name = row["name"].strip()
                    filename = row.get("file", "").strip() or f"{raw_name}.c"
                    path = directory / filename
                    if not path.is_file():
                        raise FileNotFoundError(
                            f"indexed source missing for {raw_name}: {path}")
                    address = int(row["address"].removeprefix("0x"), 16)
                    if address in by_address:
                        raise ValueError(f"duplicate exported function address: {address:08X}")
                    by_address[address] = (raw_name, path)
        else:
            for path in sorted(directory.glob("*.c")):
                address = addr_of(path.stem)
                if address is None:
                    raise ValueError(f"cannot determine function address from {path}")
                if address in by_address:
                    raise ValueError(f"duplicate exported function address: {address:08X}")
                by_address[address] = (path.stem, path)

    for path in sorted(recovered_dir.glob("*.c")):
        address = addr_of(path.stem)
        if address is None:
            raise ValueError(f"cannot determine recovered function address from {path}")
        by_address[address] = (path.stem, path)

    name_groups: dict[str, list[tuple[int, str, Path]]] = {}
    for address, (raw_name, path) in by_address.items():
        name_groups.setdefault(canonical_function_name(raw_name), []).append(
            (address, raw_name, path))

    sources: dict[str, tuple[Path, str]] = {}
    for name, entries in name_groups.items():
        preferred_address = addr_of(name)
        primary = next((entry for entry in entries if entry[0] == preferred_address), None)
        if len(entries) > 1 and primary is None:
            raise ValueError(f"duplicate function name has no address-matching owner: {name}")
        for address, raw_name, path in entries:
            output_name = name if len(entries) == 1 or (primary and address == primary[0]) else f"sub_{address:X}"
            if output_name in sources:
                raise ValueError(f"duplicate generated function name: {output_name}")
            sources[output_name] = (path, raw_name)
    fragment_path = recovered_dir.parent / "src_generated" / "merged_function_fragments.csv"
    for fragment, parent in read_merged_function_fragments(fragment_path).items():
        if fragment not in sources:
            raise ValueError(f"merged fragment is not in the current Ghidra harvest: {fragment}")
        if parent not in sources:
            raise ValueError(f"merged-fragment parent is not in the current harvest: {parent}")
        if sources[parent][0].parent.resolve() != recovered_dir.resolve():
            raise ValueError(f"merged-fragment parent lacks a recovered implementation: {parent}")
        del sources[fragment]
    return sources


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


def rename_definition(body: str, original_name: str, output_name: str) -> str:
    """Rename only a function declarator, leaving comments and call sites intact."""
    if original_name == output_name:
        return body
    signature = definition_signature(body)
    if not signature:
        return body
    renamed, count = re.subn(
        rf"\b{re.escape(original_name)}\b(?=\s*\()",
        output_name, signature, count=1)
    return body.replace(signature, renamed, 1) if count else body


def apply_bulk_patches(body: str, patches: list[tuple[str, str]]) -> tuple[str, int, list[str]]:
    """Apply ordered, literal body patches and report unmatched patterns."""
    applied = 0
    missing: list[str] = []
    for find, replacement in patches:
        if find in body:
            body = body.replace(find, replacement)
            applied += 1
        else:
            missing.append(find)
    return body, applied, missing


def instrument_render_queue_writes(body: str, function_name: str) -> str:
    """Trace stores to the menu render queue's suspect bucket range.

    The diagnostic reports the previous bucket head, the new node, and its
    next-link before each non-clear store. It is deliberately limited to the
    buckets observed corrupt in the frame trace and does not alter the store.
    """
    pattern = re.compile(
        r"^(?P<indent>[ \t]*)\(&DAT_005f6ef8\)\[(?P<index>[^\]]+)\]"
        r"[ \t]*=[ \t]*(?P<value>[^;]+);",
        re.M,
    )
    serial = 0

    def add_trace(match: re.Match[str]) -> str:
        nonlocal serial
        value = match.group("value").strip()
        if value in {"0", "0x0", "NULL", "(void *)0x0"}:
            return match.group(0)

        serial += 1
        indent = match.group("indent")
        index = match.group("index").strip()
        suffix = serial
        return (
            f"{indent}{{\n"
            f"{indent}  uint32_t __groove_queue_index_{suffix} = (uint32_t)({index});\n"
            f"{indent}  uint32_t __groove_queue_old_{suffix} = "
            f"(uint32_t)(&DAT_005f6ef8)[__groove_queue_index_{suffix}];\n"
            f"{indent}  uint32_t __groove_queue_new_{suffix} = "
            f"(uint32_t)(uintptr_t)({value});\n"
            f"{indent}  uint32_t __groove_queue_next_{suffix} = 0xffffffffu;\n"
            f"{indent}  if (__groove_queue_new_{suffix} >= (uint32_t)DAT_00586568 &&\n"
            f"{indent}      __groove_queue_new_{suffix} < (uint32_t)DAT_00586568 + 0x7d000u)\n"
            f"{indent}    __groove_queue_next_{suffix} = *(uint32_t *)(uintptr_t)__groove_queue_new_{suffix};\n"
            f"{indent}  if (__groove_queue_index_{suffix} >= 4600u &&\n"
            f"{indent}      __groove_queue_index_{suffix} <= 4700u) {{\n"
            f"{indent}    static uint32_t __groove_queue_trace_count_{suffix};\n"
            f"{indent}    if (__groove_queue_trace_count_{suffix}++ < 80u) {{\n"
            f"{indent}      fprintf(stderr, \"[queue-store] fn={function_name} bucket=%u "
            f"old=%08x new=%08x next=%08x\\n\", "
            f"__groove_queue_index_{suffix}, __groove_queue_old_{suffix}, "
            f"__groove_queue_new_{suffix}, __groove_queue_next_{suffix});\n"
            f"{indent}      fflush(stderr);\n"
            f"{indent}    }}\n"
            f"{indent}  }}\n"
            f"{indent}}}\n"
            f"{match.group(0)}"
        )

    return pattern.sub(add_trace, body)


# `local_1c`, `uStack_148`, `stack0xfffffebf` ... : stack slots Ghidra names.
LOCAL_USE_RE = re.compile(r"\b((?:local|uStack|iStack|stack0x|pvStack|cStack|bStack|sStack)_[0-9a-fA-F]+)\b")
LOCAL_DECL_RE = re.compile(r"^[ \t]*(?:[A-Za-z_][A-Za-z0-9_]*[ \t\*]+)+(local_[0-9a-fA-F]+)\b", re.M)


def undeclared_locals(body: str) -> set[str]:
    """Stack variables the decompiler used but never declared.

    A known Ghidra quirk (usually after an unresolved jump table): the function
    has to be fixed by hand, so these are reported rather than papered over.
    """
    decls = {m for m in re.findall(r"^[ \t]*[A-Za-z_][A-Za-z0-9_]*[ \t\*]*\b(local_[0-9a-fA-F]+)\b", body, re.M)}
    stack_name = r"(?:(?:u|i|b|c|s|pv)Stack_[0-9a-fA-F]+|stack0x[0-9a-fA-F]+)"
    decls |= {m for m in re.findall(
        rf"^[ \t]*[^;\n]*\b({stack_name})\b[ \t]*;", body, re.M)}
    used = set(LOCAL_USE_RE.findall(body))
    return used - decls


def unresolved_artifacts(body: str, signature: str | None) -> set[str]:
    """Return register/decompiler artifacts that are not modeled as parameters."""
    comment = re.compile(re.escape("/*") + ".*?" + re.escape("*/"), re.S)
    code_hits = set(ARTIFACT_RE.findall(comment.sub("", body)))
    declared_inputs = set(ARTIFACT_RE.findall(signature or ""))
    return code_hits - declared_inputs


def sanitize_name(name: str) -> str:
    """`Catch@0040fb87` -> `Catch_0040fb87`.

    Ghidra's exception analysis names catch blocks with an embedded address,
    which is not a legal C identifier.
    """
    return re.sub(r"[^A-Za-z0-9_]", "_", name)


def sanitize_signature_names(signature: str, renames: dict[str, str]) -> str:
    """Apply the same symbol renames to a captured C function signature."""
    for original, safe in renames.items():
        signature = signature.replace(original, safe)
    return signature


def _matching_brace(text: str, opening: int) -> int:
    """Return the closing brace matching ``opening``, ignoring comments/literals."""
    depth = 0
    state = "code"
    escaped = False
    index = opening
    while index < len(text):
        char = text[index]
        following = text[index + 1] if index + 1 < len(text) else ""
        if state == "line_comment":
            if char == "\n":
                state = "code"
        elif state == "block_comment":
            if char == "*" and following == "/":
                state = "code"
                index += 1
        elif state in {"string", "char"}:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif (state == "string" and char == '"') or (state == "char" and char == "'"):
                state = "code"
        elif char == "/" and following == "/":
            state = "line_comment"
            index += 1
        elif char == "/" and following == "*":
            state = "block_comment"
            index += 1
        elif char == '"':
            state = "string"
        elif char == "'":
            state = "char"
        elif char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return index
        index += 1
    raise ValueError("unclosed brace in Ghidra manual switch")


def rewrite_manual_switches(body: str, read_targets) -> tuple[str, int]:
    """Convert Ghidra's non-C pointer-table switch syntax using the PE's table order.

    Ghidra emits case labels as code pointers but uses a synthetic C++ namespace in
    the switch expression. The source compiler only needs the integral selector; map
    each target label back to its actual ordinal in the original PE jump table.
    ``read_targets(address, count)`` must return the binary's little-endian targets.
    """
    out = []
    cursor = 0
    rewritten = 0
    while match := MANUAL_SWITCH_RE.search(body, cursor):
        opening = match.end() - 1
        closing = _matching_brace(body, opening)
        switch_text = body[match.start():closing + 1]
        case_matches = list(MANUAL_CASE_RE.finditer(switch_text, match.end() - match.start()))
        targets = [int(case.group(1), 16) for case in case_matches]
        if not targets or len(set(targets)) != len(targets):
            raise ValueError(f"invalid case labels in manual switch at table {match.group('table')}")
        table_address = int(match.group("table"), 16)
        table_targets = list(read_targets(table_address, len(targets)))
        if len(table_targets) != len(targets) or set(table_targets) != set(targets):
            raise ValueError(
                f"PE jump table {table_address:08X} does not match Ghidra case labels: "
                f"{table_targets!r} vs {targets!r}")

        for case in reversed(case_matches):
            target = int(case.group(1), 16)
            ordinal = table_targets.index(target)
            switch_text = (switch_text[:case.start()] + f"case {ordinal}:"
                           + switch_text[case.end():])
        header = MANUAL_SWITCH_RE.match(switch_text)
        if header is None:
            raise AssertionError("manual switch header was lost during rewrite")
        switch_text = (switch_text[:header.start()]
                       + f"switch ((unsigned char){match.group('selector')}) {{"
                       + switch_text[header.end():])
        out.append(body[cursor:match.start()])
        out.append(switch_text)
        cursor = closing + 1
        rewritten += 1
    out.append(body[cursor:])
    return "".join(out), rewritten


def rewrite_pointer_integer_switches(body: str) -> tuple[str, int]:
    """Make Ghidra's pointer-typed integer selectors valid integral C switches."""
    out = []
    cursor = 0
    rewritten = 0
    while match := POINTER_SWITCH_RE.search(body, cursor):
        opening = match.end() - 1
        closing = _matching_brace(body, opening)
        switch_text = body[match.start():closing + 1]
        case_matches = list(POINTER_INTEGER_CASE_RE.finditer(
            switch_text, match.end() - match.start()))
        if not case_matches:
            out.append(body[cursor:closing + 1])
            cursor = closing + 1
            continue
        for case in reversed(case_matches):
            value = case.group(1).lower()
            switch_text = (switch_text[:case.start()] + f"case 0x{value}:"
                           + switch_text[case.end():])
        header = POINTER_SWITCH_RE.match(switch_text)
        if header is None:
            raise AssertionError("pointer switch header was lost during rewrite")
        switch_text = (switch_text[:header.start()]
                       + f"switch ((uintptr_t){match.group('expression')}) {{"
                       + switch_text[header.end():])
        out.append(body[cursor:match.start()])
        out.append(switch_text)
        cursor = closing + 1
        rewritten += 1
    out.append(body[cursor:])
    return "".join(out), rewritten



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


def rewrite_verified_e9_tail_jump(body: str, name: str,
                                  machine_code: bytes) -> tuple[str, bool]:
    """Emit a naked jump only when Ghidra's tail call matches the original E9."""
    address = addr_of(name)
    if address is None or len(machine_code) < 5 or machine_code[0] != 0xE9:
        return body, False
    target_address = (address + 5 + struct.unpack_from("<i", machine_code, 1)[0]) & 0xFFFFFFFF
    pattern = re.compile(
        rf"(?m)^(?P<return>undefined[0-9]*)\s+{re.escape(name)}\s*\(void\)\s*"
        rf"\{{\s*return\s+(?P<target>[A-Za-z_][A-Za-z0-9_]*)\s*\(\s*\);\s*\}}")
    match = pattern.search(body)
    if match is None or addr_of(match.group("target")) != target_address:
        return body, False
    target = sanitize_name(match.group("target"))
    replacement = (
        f"__declspec(naked) {match.group('return')} {name}(void)\n"
        f"{{\n  __asm {{ jmp {target} }}\n}}")
    return body[:match.start()] + replacement + body[match.end():], True


def main() -> int:
    OUT.mkdir(exist_ok=True)
    # Merge the fixed inventory with entries absent from its export, then prefer
    # hand-recovered definitions. Names are normalized by function identity so
    # `sub_0054FBD0.c` and `sub_54FBD0.c` cannot become duplicate definitions.
    source_files = collect_source_files([DEC], ROOT / "src_recovered")
    files = [(name, *source_files[name]) for name in sorted(source_files)]
    if not files:
        print(f"no decompiled sources in {DEC}; run tools/ghidra_decompile.bat first")
        return 1

    exe = PE(ROOT.parent / "Game" / "groove.exe")

    # ---- data symbols Ghidra knows about ---------------------------------
    data: dict[int, tuple[str, int, str]] = {}
    data_csv = DEC / "_data.csv"
    if data_csv.exists():
        with data_csv.open(encoding="utf-8") as fh:
            reader = csv.reader(fh)
            next(reader, None)
            for fields in reader:
                # Older Ghidra exports did not quote commas inside symbol names.
                # Recover the three trailing metadata fields before sanitising.
                if len(fields) < 4:
                    raise ValueError(f"Invalid data export row: {fields!r}")
                row = dict(zip(("name", "address", "size", "datatype"),
                               [",".join(fields[:-3]), *fields[-3:]]))
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
    manual_switches_rewritten = 0
    pointer_switches_rewritten = 0
    verified_e9_thunks = 0
    for source_name, path, raw_source_name in files:
        if not is_game_code(source_name):
            continue
        body = path.read_text(encoding="utf-8", errors="replace")
        # Ghidra can assign one symbol name to two distinct entry addresses.
        # Keep the address-matching definition's original name and rename only
        # the conflicting definition's declarator to its own address.
        body = rename_definition(body, raw_source_name, source_name)
        name = renames.get(source_name, sanitize_name(source_name))
        body = instrument_render_queue_writes(body, name)
        for bad, good in renames.items():
            if bad in body:
                body = body.replace(bad, good)
        body = normalize(body)
        body, switch_count = rewrite_manual_switches(
            body, lambda address, count: struct.unpack(
                f"<{count}I", exe.read(address, count * 4)))
        manual_switches_rewritten += switch_count
        body, pointer_switch_count = rewrite_pointer_integer_switches(body)
        pointer_switches_rewritten += pointer_switch_count
        body, patch_count, missing_patches = apply_bulk_patches(
            body, bulk_patches.get(name, []))
        # These two display-mode setup failures must return to the caller's mode
        # retry loop. The CSV substitutions can be shadowed when duplicate Ghidra
        # exports for this address are merged, so enforce the control-flow repair
        # on the final selected body as well.
        if name == "sub_410700":
            for local in ("local_94", "local_58"):
                body = re.sub(
                    rf"__CxxThrowException_8\(&{local},&DAT_0056eff0\);",
                    "    sub_410ED0();\n"
                    "    ExceptionList = local_10;\n"
                    "    return 0;",
                    body,
                )
        patched += patch_count
        for find in missing_patches:
            print(f"  note: patch pattern not found in {name}: {find[:40]!r}")
        # a patch whose replacement text was truncated (an unquoted comma in the CSV is
        # the usual cause) leaves an unterminated /* behind, and the *next* function then
        # fails with a syntax error that points nowhere near the patch.  Cheap net:
        if body.count("/*") != body.count("*/"):
            print(f"  note: unbalanced comment in {name} after patching "
                  f"({body.count('/*')} vs {body.count('*/')} - check the replacement "
                  f"text in bulk_patches.csv for a missing quote)")
        if name in auto_decls:
            lines = body.splitlines()
            for i, line in enumerate(lines):
                if line.strip() == "{":
                    inject = ["  " + ctype + " " + nm + ";" for nm, ctype in auto_decls[name]]
                    lines[i + 1:i + 1] = inject
                    body = chr(10).join(lines)
                    injected += len(inject)
                    break
        sig = definition_signature(body)
        if sig:
            signatures[name] = sig
        function_address = addr_of(name)
        if function_address is not None:
            body, was_e9_thunk = rewrite_verified_e9_tail_jump(
                body, name, exe.read(function_address, 5))
            verified_e9_thunks += int(was_e9_thunk)
        bodies[name] = body
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

    # Duplicate Ghidra exports may overwrite an earlier function body in the loop
    # above. Apply this control-flow repair to the final selected definition.
    if "sub_410700" in bodies:
        body = bodies["sub_410700"]
        for local in ("local_94", "local_58"):
            body = re.sub(
                rf"__CxxThrowException_8\(&{local},&DAT_0056eff0\);",
                "    sub_410ED0();\n"
                "    ExceptionList = local_10;\n"
                "    return 0;",
                body,
            )
        bodies["sub_410700"] = body

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

    # the functions this rebuild contains: an initialised function pointer in the
    # original's data can be re-pointed at the rebuilt one when its address matches
    body_names = set(bodies)

    # Pointers *inside* the original's data.  A slot that holds the address of another
    # datum - a string table, a vtable, an array - is initialised numerically otherwise,
    # and the rebuild relocates that target, so the number would point at the wrong byte.
    # Pulling the target into the referenced set gives it a definition and a declaration,
    # and then the initialiser can be the symbol the linker fixes up.
    promoted = 0
    # Explicitly typed record members may have no individually exported datum.
    for symbol, kind in type_overrides.items():
        address = addr_of(symbol)
        if address is not None and address not in data:
            if kind == "pointer":
                data[address] = (symbol, 4, "pointer")
            elif kind.startswith("string:"):
                data[address] = (symbol, int(kind.split(":")[1], 16), "string")
            elif kind == "int":
                data[address] = (symbol, 4, "undefined4")
    # Pointer members in a confirmed initialized record are references even
    # when decompiled code names only the first member of the table.
    for name, kind in type_overrides.items():
        if kind.startswith("record:") and kind.endswith(":file"):
            start = int(name.rsplit("_", 1)[1], 16)
            end = start + int(kind.split(":")[1], 16)
            for address, (symbol, _, dtype) in data.items():
                if start <= address < end and dtype == "pointer" and IDENT_RE.match(symbol):
                    referenced.setdefault(address, set()).add(symbol)
    for a in list(referenced):
        size = data.get(a, (None, 4, None))[1]
        try:
            raw = exe.read(a, min(size, 4))
        except ValueError:
            continue
        if len(raw) < 4:
            continue
        v = struct.unpack("<I", raw)[0]
        if v in data and v not in referenced and not data[v][2] == "string":
            referenced.setdefault(v, set()).add(data[v][0])
            promoted += 1
        elif v in data and v not in referenced and data[v][2] == "string":
            referenced.setdefault(v, set()).add(data[v][0])
            promoted += 1
    if promoted:
        print(f"  note: {promoted} datum(s) are pointer targets inside the original's "
              f"data and were pulled in as referenced")

    # A datum the code *assigns* is runtime state, not a constant: the heap allocator's
    # head (0x586584) holds `d2 33 e0 33` in the file, but at run time it is whatever the
    # allocator put there, and initialising it with the file's bytes made every allocation
    # return that number as a pointer - the differential harness caught it (3 failures,
    # was 1).  So the initial value is only used for data no body writes.
    written: set[str] = set()
    for body in bodies.values():
        for name in set(re.findall(r"\b([A-Za-z_][A-Za-z0-9_]*)\b\s*(?:\[[^\]]*\])?\s*(?:\.[A-Za-z_]+\s*)?=(?!=)", body)):
            written.add(name)

    defs: list[str] = []
    decls: list[str] = []
    # Confirmed DWORD tables retain scalar lvalues at every original offset.
    # Separate linker globals cannot support rep stosd or pointer iteration.
    table_ranges = []
    for name, kind in type_overrides.items():
        if kind.startswith(("dwords:", "record:", "functions:")):
            start = int(name.rsplit("_", 1)[1], 16)
            parts = kind.split(":")
            size = int(parts[1], 16)
            if size <= 0 or size % 4:
                raise ValueError(f"Invalid DWORD table size: {name}={kind}")
            table_ranges.append((start, start + size, name))
    for start, end, name in table_ranges:
        kind = type_overrides[name]
        parts = kind.split(":")
        size = end - start
        storage = name + "_storage"
        if len(parts) > 2 and parts[2] == "file" and kind.startswith("record:"):
            # A file-backed record can contain pointers even when Ghidra exported
            # each slot as `undefined *`.  Promote only values that point to a
            # known string (including explicitly recovered one-byte strings) or
            # to one of the functions being rebuilt; other DWORDs stay scalar.
            for offset, value in enumerate(struct.unpack(f"<{size // 4}I", exe.read(start, size))):
                slot = start + offset * 4
                slot_name, slot_width, _ = data.get(slot, (f"DAT_{slot:08X}", 4, "undefined4"))
                target = data.get(value)
                target_is_string = bool(target and (
                    target[2] == "string"
                    or type_overrides.get(target[0], "").startswith("string:")
                ))
                target_is_function = f"sub_{value:06X}" in body_names
                if target_is_string or target_is_function:
                    data[slot] = (slot_name, slot_width, "pointer")
                    if target_is_string:
                        referenced.setdefault(value, set()).add(target[0])
        if kind.startswith("functions:"):
            addresses = struct.unpack(f"<{size // 4}I", exe.read(start, size))
            entries = [f"(code *)&sub_{value:06X}" if value else "0" for value in addresses]
            defs.append(f"code *{storage}[{size // 4}] = {{{','.join(entries)}}};")
            decls.append(f"extern code *{storage}[{size // 4}];")
            continue
        if len(parts) > 2 and parts[2] == "file":
            entries = []
            for offset, value in enumerate(struct.unpack(f"<{size // 4}I", exe.read(start, size))):
                datum = data.get(start + offset * 4)
                target = next((r for r in table_ranges if r[0] <= value < r[1]), None)
                if target and ((datum and datum[2] == "pointer") or
                           type_overrides.get(f"DAT_{start + offset * 4:08x}") == "pointer"):
                    entries.append(f"(int)((unsigned char *){target[2]}_storage + {value - target[0]})")
                elif datum and datum[2] == "pointer" and value in referenced:
                    target_name = data.get(value, (f"DAT_{value:08X}",))[0]
                    entries.append(f"(int)&{target_name}")
                elif datum and datum[2] == "pointer" and f"sub_{value:06X}" in body_names:
                    # Records can contain callbacks beside data pointers. The
                    # original VA must become the rebuilt function's address.
                    entries.append(f"(int)&sub_{value:06X}")
                else:
                    entries.append(f"0x{value:08x}")
            values = ",".join(entries)
        else:
            values = "0"
        defs.append(f"int {storage}[{size // 4}] = {{{values}}};")
        decls.append(f"extern int {storage}[{size // 4}];")
    for a in sorted(referenced):
        table = next((r for r in table_ranges if r[0] <= a < r[1]), None)
        if table:
            start, end, name = table
            record = type_overrides[name].startswith("record:")
            if (a - start) % 4 and not record:
                raise ValueError(f"Unaligned symbol inside DWORD table: {a:08x}")
            canonical = data.get(a, (f"DAT_{a:08X}",))[0]
            for alias in sorted(referenced[a] | {canonical}):
                if IDENT_RE.match(alias):
                    if record:
                        _, width, dtype = data.get(a, (canonical, 4, "undefined4"))
                        ctype = "unsigned int *" if dtype == "pointer" else (
                            "int" if alias.startswith("_DAT_") or width >= 4 else
                            "unsigned short" if width == 2 else "unsigned char")
                        member_override = type_overrides.get(alias) or type_overrides.get(data.get(a, (canonical,))[0])
                        if member_override == "int":
                            ctype = "int"
                        elif member_override in {"float", "floatfile", "double"}:
                            ctype = "float" if member_override == "floatfile" else member_override
                        decls.append(f"#define {alias} (*({ctype} *)((unsigned char *){name}_storage + {a - start}))")
                    else:
                        decls.append(f"#define {alias} ({name}_storage[{(a - start) // 4}])")
            continue
        canonical, size, _dt = data.get(a, (f"DAT_{a:08X}", 4, "undefined"))
        if canonical.startswith(("flt_", "dbl_")):
            continue                                   # emitted as constants below
        # A `string:<hex>` override says "this datum is a NUL-terminated string of at most
        # that many bytes": Ghidra's symbol table records the one-byte access it saw, so
        # the mode string at 0x570350 is declared `'r'` while the file holds "rb" - passed
        # to fopen, a one-byte mode is a truncation.  This is a *recorded* decision per
        # symbol because a broad "looks printable" rule turned scalars into strings and cost
        # 931 compile errors (measured); the bytes are the evidence, the override is the fix.
        ov = type_overrides.get(canonical)
        if ov is not None and ov.startswith("string:"):
            try:
                size = int(ov.split(":", 1)[1], 16)
            except ValueError:
                pass
            _dt = "string"

        if _dt == "string":
            # The real bytes are in the executable, so emit the actual literal.  The second
            # condition catches the strings Ghidra typed as one byte because it only saw a
            # single-byte access: `DAT_00570350` is `'r'` while the file holds "rb" (passed
            # to fopen as the mode), `DAT_00570300` is `'%'` while the file holds "%d".
            # Reading the bytes *is* the evidence, and a truncated mode is a silent
            # misbehaviour - in the save path it is what stops the run.
            try:
                raw = exe.read(a, size)
            except ValueError:
                raw = b""
            if not raw.endswith(b"\0"):
                raw += b"\0"
            lit = ",".join(str(b) for b in raw)
            defs.append(f"const char {canonical}[] = {{{lit}}};   /* 0x{a:08X} */")
            decls.append(f"extern const char {canonical}[];")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        override = type_overrides.get(canonical)
        if override is not None and override.startswith("string:"):
            override = None          # handled at the top of the iteration
        is_buffer = False
        if override is not None and override.startswith("array:"):
            # `array:0x800` - "this datum is a buffer of that many bytes".  Ghidra's symbol
            # table records only the access it saw, so a 2 KB scratch buffer the code fills
            # through `&DAT_x` is declared one byte: `DAT_0057ddc4` is written with 0x800
            # bytes by the registry reader (`sub_4058A0`, which sets `local_4 = 0x800`), and
            # a one-byte declaration means the rebuild overwrites everything after it in the
            # data section.  Sizing it has to be a *recorded* decision per symbol - a broad
            # "address-taken means buffer" rule turned scalar globals into arrays and cost
            # 265 compile errors, so it is an override instead.
            size = int(override.split(":", 1)[1], 16)
            is_buffer = True
            override = None
        if override is not None:
            if override in {"floatfile", "doublefile"}:
                ctype = "float" if override == "floatfile" else "double"
                value = struct.unpack("<f" if ctype == "float" else "<d",
                                      exe.read(a, 4 if ctype == "float" else 8))[0]
                suffix = "f" if ctype == "float" else ""
                defs.append(f"{ctype} {canonical} = {value!r}{suffix};")
                decls.append(f"extern {ctype} {canonical};")
                for other in sorted(referenced[a] - {canonical}):
                    if IDENT_RE.match(other):
                        decls.append(f"#define {other} {canonical}")
                continue
            if override == "bytepointerfile":
                value = struct.unpack("<I", exe.read(a, 4))[0]
                target = data[value][0]
                defs.append(f"unsigned char *{canonical} = (unsigned char *)&{target};")
                decls.append(f"extern unsigned char *{canonical};")
                continue
            ctype = {"float": "float", "double": "double",
                     "pointer": "unsigned int *"}.get(override, "int")
            defs.append(f"{ctype} {canonical};   /* 0x{a:08X}, type inferred from use */")
            decls.append(f"extern {ctype} {canonical};")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        if canonical.startswith("PTR_sub_"):
            ctype = "code *"
        elif _dt == "pointer" or _dt.endswith("*"):
            # Ghidra's own symbol table says this datum holds an address.  That is
            # evidence the usage heuristics were ignoring: `PTR_s_Inserire_il_CD_...` was
            # typed `int`, so a string-table pointer was initialised as the *number*
            # 0x579BD0 - which is the game main's crash (it hands that to MessageBoxA).
            ctype = "unsigned int *"
        elif canonical in funcptr_syms:
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
        def target_bytes(v: int, cap: int = 512) -> bytes | None:
            """A NUL-terminated, printable string at `v` in the original's image, if any.

            Used for pointer slots whose target has no symbol: those are string tables,
            and the string is what the code will dereference.
            """
            sec = exe.section_for_rva(v - exe.image_base)
            if sec is None or sec.is_code:
                return None
            try:
                raw = exe.read(v, cap)
            except ValueError:
                return None
            end = raw.find(b"\0")
            if end < 1:
                return None
            text = raw[:end]
            if not all(0x20 <= b < 0x7F for b in text):
                return None
            return text + b"\0"

        def initial(a: int, n: int) -> bytes:
            """The datum's initial value, read out of groove.exe.

            Everything except strings and floats used to be emitted *zero*, and the
            original's data section is not all zero: 0x583374 holds two floats, 0x585A68
            holds 500, 0x5846E4 another float pair.  A rebuild that computes those
            constants as 0 gets wrong values - and where a table entry or a divisor is
            involved, faults.  Slots in the image's BSS read as zero in the original as
            well (checked: 0x581168, 0x58115C), so nothing changes for those.
            """
            # Only a *data* section holds initialised values.  Some symbols the table
            # places in `.text` (and some it places nowhere) were read as code bytes:
            # 0x33E033D2 is two `xor` instructions, and initialising the allocator's
            # cursor with that made every allocation return garbage - the differential
            # harness caught it (3 failures, was 1).
            sec = exe.section_for_rva(a - exe.image_base)
            if sec is None or sec.is_code:
                return b""
            try:
                return exe.read(a, n)
            except ValueError:
                return b""

        if size > 4 and (is_buffer or not ctype.endswith("*")):
            # a multi-byte datum is an array in the original; declaring it as one
            # scalar would let the code (and the harness) write past its storage
            elem = {8: "long long", 4: "int"}.get(4, "int")
            count = max(1, (size + 3) // 4)
            raw = b"" if (referenced[a] & written) else initial(a, 4 * count)
            raw = raw.ljust(4 * count, b"\0")
            if any(raw):
                vals = struct.unpack(f"<{count}i", raw)
                defs.append(f"{elem} {canonical}[{count}] = "
                            f"{{{', '.join(str(v) for v in vals)}}};"
                            f"   /* 0x{a:08X}, {size} byte(s), initial value from groove.exe */")
            else:
                defs.append(f"{elem} {canonical}[{count}];   /* 0x{a:08X}, {size} byte(s) */")
            decls.append(f"extern {elem} {canonical}[{count}];")
            for other in sorted(referenced[a] - {canonical}):
                if IDENT_RE.match(other):
                    decls.append(f"#define {other} {canonical}")
            continue
        spellings = referenced[a]
        if spellings & written:
            raw = b""            # runtime state: the file's bytes are not its initial value
        else:
            raw = initial(a, size)
        value = struct.unpack("<I", raw.ljust(4, b"\0"))[0] if raw else 0
        if ctype.startswith(("code", "FARPROC")):
            # a function-pointer slot: the original's value is an address in the original
            # image, so initialise it *symbolically* when the target is a function that
            # this rebuild also contains - otherwise leave it alone (the code assigns
            # these before calling through them).
            target = f"sub_{value:06X}" if value >= 0x400000 and f"sub_{value:06X}" in body_names else None
            if target:
                defs.append(f"{ctype} {canonical} = ({ctype})&{target};"
                            f"   /* 0x{a:08X}, initial function pointer from groove.exe */")
            else:
                defs.append(f"{ctype} {canonical};   /* 0x{a:08X}, {size} byte(s) */")
        elif value and ctype.endswith("*"):
            # a pointer that points *inside* the image: symbol when the target is one of
            # the data symbols, numeric otherwise (neither is safe to dereference, but
            # the symbolic form is what the linker can fix up)
            tname = data.get(value)
            if tname and value in referenced:
                # the target is one of the symbols this translation unit defines, so the
                # symbolic form is both legal and linkable
                tname = renames.get(tname[0], tname[0])
                defs.append(f"{ctype} {canonical} = ({ctype})&{tname};"
                            f"   /* 0x{a:08X}, initial pointer from groove.exe */")
            else:
                # Either the target has no symbol here, or it has one this unit does not
                # define (the promotion above covers the common case; this is the rest,
                # and picking `&name` for an undefined name is exactly the C2065 that
                # stopped the build).  Materialise what it pointed at instead. - a
                # string table entry, typically (`PTR_s_Inserire_il_CD_..._0057ba3c =
                # 0x579BD0`).  Keeping the number points at whatever the rebuild has at
                # that address, which is how the game's main crashed: it hands the value
                # to MessageBoxA as the message text.  So materialise the bytes it pointed
                # at and point at *those*.
                text = target_bytes(value)
                if text:
                    safe = f"groove_str_{value:08X}"
                    defs.append(f"const char {safe}[] = "
                                f"{{{','.join(str(b) for b in text)}}};"
                                f"   /* 0x{value:06X}, {len(text)} byte(s), string from groove.exe */")
                    decls.append(f"extern const char {safe}[];")
                    defs.append(f"{ctype} {canonical} = ({ctype}){safe};"
                                f"   /* 0x{a:08X}, initial pointer to a materialised string */")
                else:
                    defs.append(f"{ctype} {canonical} = ({ctype})0x{value:X};"
                                f"   /* 0x{a:08X}, initial value from groove.exe */")
        elif value and not ctype.endswith("*"):
            defs.append(f"{ctype} {canonical} = 0x{value:X};"
                        f"   /* 0x{a:08X}, {size} byte(s), initial value from groove.exe */")
        else:
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
    # Compare labels in the exact spelling used by generated C. In fresh Ghidra
    # exports a referenced `Catch@<address>` can be sanitized in its body while
    # the source-map key remains raw; without this normalization we emit a second,
    # conflicting `void Catch_<address>()` declaration in ghidra_globals.h.
    function_names = {
        renames.get(name, sanitize_name(name))
        for name in set(bodies) | set(protos)
    }
    referenced_labels = {renames.get(label, sanitize_name(label)) for label in referenced_labels}
    defined_labels = {renames.get(label, sanitize_name(label)) for label in defined_labels}
    for lab in sorted(referenced_labels - defined_labels - function_names):
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
        '#include "ghidra_globals.h"\n#include "ghidra_prototypes.h"\n\n'
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
        safe_name = renames.get(name, sanitize_name(name))
        safe_sig = sanitize_signature_names(sig, renames)
        if safe_name != name:
            safe_sig = safe_sig.replace(name, safe_name)
        protos[safe_name] = safe_sig

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
        # Naked is a definition-only MSVC attribute; leaking it into the shared
        # prototype header makes every C translation unit fail with C2488.
        s = re.sub(r"\b__declspec\s*\(\s*naked\s*\)", "", sig).strip()
        if n in {"sub_558FF0", "sub_559459"}:
            # These rasterizers consume the first vertex from EAX and the next two
            # from ECX/EDX. Their patched bodies carry that recovered input as an
            # explicit C parameter, so keep the generated declaration in sync.
            if n not in signatures:
                raise ValueError(f"missing patched prototype for {n}")
            loose[n] = s.split("/*", 1)[0].strip()
            continue
        # Windows/DirectDraw callbacks require their exact x86 callee ABI. The two
        # triangle rasterizers also keep exact prototypes: their nine-argument call
        # shape was reconstructed from the original renderer assembly, and all
        # in-image callsites use that shape.
        if n in {"sub_41DDA0", "sub_4116B0", "sub_4116D0", "sub_411D60", "sub_412320", "sub_412640", "sub_412710", "sub_40E960", "sub_41E790", "sub_414600", "sub_41B8A0", "sub_42C180", "sub_402910", "sub_402960", "sub_41E4B0", "sub_41E610", "sub_41E680", "sub_410480", "sub_409510", "sub_41ECE0", "sub_43CD60", "sub_4C0EC0"}:
            loose[n] = s
            continue
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

    label_names = {
        label
        for body in bodies.values()
        for label in re.findall(r"\b(?:LAB|FUN)_[0-9a-fA-F]{1,8}\b", body)
    }
    aliases = aliases_for_code_labels(label_names, set(bodies))

    (OUT / "ghidra_prototypes.h").write_text(
        '/* generated by tools/make_bulk.py - do not edit */\n'
        "#ifndef GHIDRA_PROTOTYPES_H\n#define GHIDRA_PROTOTYPES_H\n\n"
        "#include \"ghidra_shim.h\"\n\n"
        + "\n".join(f"{p};" for p in sorted(protos.values()))
        + "\n\n/* Exact-address aliases for labels Ghidra emitted as external symbols. */\n"
        + "\n".join(f"#define {label} {target}" for label, target in sorted(aliases.items()))
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
    # The artefact scan is about *code*, so comments are stripped first: a recovered body
    # naturally explains the artefact it replaced ("Ghidra read the value back through
    # `in_EAX`"), and scanning the prose classified that function as needing hand fixing and
    # dropped it from the clean subset - measured, on src_recovered/sub_410480.c, which
    # then stayed a stub at run time.
    comment = re.compile(re.escape("/*") + ".*?" + re.escape("*/"), re.S)
    for name in sorted(bodies):
        body = bodies[name]
        code = comment.sub("", body)
        hits = unresolved_artifacts(body, signatures.get(name))
        missing = undeclared_locals(code)
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
        f"manual jump tables rewritten: {manual_switches_rewritten}",
        f"pointer-typed switches rewritten: {pointer_switches_rewritten}",
        f"verified E9 tail jumps preserved: {verified_e9_thunks}",
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
