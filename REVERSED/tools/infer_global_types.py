"""infer_global_types.py - let the compiler tell us what each global really is.

The bulk translation unit decodes the same memory slot as an integer, a float or a
pointer depending on the function that touches it, and that is not knowable from the
symbol table: Ghidra records almost everything as `undefined4`, and the listing's
`flt_xxxx dd xx` labels are guesses (the fixed-point globals used as `A*A + B*B >> 12`
prove it - see the note in make_bulk.py).

So the type is inferred from *evidence*: compile, read the type errors, work out which
type each erroring use demands, write the result to src_generated/type_overrides.csv
(make_bulk.py applies it), and repeat until it stops improving.  Every round reports
the clean-function count, so the effect of an inference is measured, never assumed.

    python tools/infer_global_types.py --rounds 5
"""

from __future__ import annotations

import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
OVERRIDES = OUT / "type_overrides.csv"

# A global's name always ends in its address, e.g. DAT_006d7b98 or _DAT_0057db20.
SYM_PATTERN = r"[A-Za-z_][A-Za-z0-9_]*_[0-9a-f]{6,8}"
SYM_RE = re.compile(SYM_PATTERN)

# For a C2440 the message names the type the expression was converted *to*, which is
# the most direct evidence available ("impossibile convertire da 'X' a 'Y'").
CONVERT_RE = re.compile(r"da '([^']*)' a '([^']*)'")

# Fallback rules, searched in the window around the erroring line; the first match
# wins for the symbols on that line.
RULES = [
    (re.compile(r"\((?:float|double)\)\s*" + SYM_PATTERN), "float"),
    (re.compile(r"\((\w+)\s*\*+\s*\)\s*" + SYM_PATTERN), "pointer"),
    # bit operations demand an integer
    (re.compile(SYM_PATTERN + r"\s*(?:>>|<<|&|\||\^|%)\s"), "int"),
    # arithmetic against a float literal
    (re.compile(SYM_PATTERN + r"\s*[-+*/]\s*\d+\.\d"), "float"),
]



# ---------------------------------------------------------------------------
# Seeding from the binary itself
# ---------------------------------------------------------------------------
# The strong signal: an x87 instruction whose memory operand is a data address
# proves that slot is a float (or double).  `fld ds:flt_6D7B98` is evidence;
# `flt_6D7B98 dd ?` on its own is IDA guessing from the bytes, which the
# fixed-point globals prove is unreliable.  Only operand references count here.
X87_OPERAND_RE = re.compile(
    r"\b(?:fld|fst|fstp|fadd|faddp|fsub|fsubp|fsubr|fsubrp|fmul|fmulp|fdiv|fdivp|"
    r"fdivr|fdivrp|fcom|fcomp|fcompp|fchs|fabs)\s+(?:ds:)?(flt|dbl)_([0-9A-Fa-f]{6,8})")


def seed_from_asm(asm_path: Path) -> dict[str, str]:
    """symbol name -> 'float'/'double', from x87 operands in the listing.

    The keys must be the *generator's* symbol names (Ghidra's `DAT_006d7b98`), not
    the listing's `flt_6D7B98`: an earlier version emitted the listing spelling, so
    the seed matched nothing and its "no change" measurement was vacuous.
    """
    out: dict[str, str] = {}
    if not asm_path.exists():
        return out
    text = asm_path.read_text(encoding="latin1", errors="replace")
    for kind, addr in X87_OPERAND_RE.findall(text):
        value = int(addr, 16)
        ftype = "float" if kind == "flt" else "double"
        out["DAT_%08x" % value] = ftype
        out["_DAT_%08x" % value] = ftype
        out["flt_%06X" % value] = ftype
        out["flt_%08x" % value] = ftype
        out["dbl_%06X" % value] = ftype
    return out


def unary_deref_symbol(line: str) -> str | None:
    """The symbol a *unary* dereference applies to, if any.

    `A * B` is a multiplication, not a dereference: the character before the star
    (skipping spaces) has to be something that cannot end an operand.  A regex-only
    version of this fired on every multiplication.
    """
    for m in re.finditer(r"\*\s*(" + SYM_PATTERN + r")", line):
        i = m.start() - 1
        while i >= 0 and line[i] == " ":
            i -= 1
        if i < 0 or line[i] in "([{,:;=&|+-*/%<>!?~^":
            return m.group(1)
    return None


def kind_of_ctype(ctype: str) -> str:
    if ctype in ("float", "double"):
        return ctype
    if "*" in ctype:
        return "pointer"
    return "int"


def load_overrides() -> dict[str, str]:
    if not OVERRIDES.exists():
        return {}
    with OVERRIDES.open(encoding="utf-8") as fh:
        return {r["name"]: r["type"] for r in csv.DictReader(fh)}


def save_overrides(table: dict[str, str]) -> None:
    OVERRIDES.parent.mkdir(parents=True, exist_ok=True)
    with OVERRIDES.open("w", newline="", encoding="utf-8") as fh:
        w = csv.writer(fh)
        w.writerow(["name", "type"])
        for name in sorted(table):
            w.writerow([name, table[name]])


def error_lines() -> list[tuple[str, str, str, str]]:
    """(code, message, source line, window) for every type-related error."""
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        return []
    text = log.read_text(encoding="latin1", errors="replace")
    wanted = ("C2440", "C2296", "C2297", "C2040", "C2100", "C2109", "C2110")
    out: list[tuple[str, str, str, str]] = []
    pattern = r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)"
    for fname, line, code, msg in re.findall(pattern, text):
        if code not in wanted:
            continue
        path = OUT / "chunks" / fname
        try:
            src = path.read_text(encoding="utf-8", errors="replace").splitlines()
        except FileNotFoundError:
            continue
        i = int(line) - 1
        if 0 <= i < len(src):
            lo, hi = max(0, i - 4), min(len(src), i + 5)
            out.append((code, msg, src[i], chr(10).join(src[lo:hi])))
    return out


def infer(errors: list[tuple[str, str, str, str]], table: dict[str, str]) -> int:
    """Add the types the errors demand; returns how many symbols were typed."""
    added = 0
    for code, msg, line, window in errors:
        names = SYM_RE.findall(line)
        if not names:
            continue
        kind = None
        if code == "C2440":
            hit = CONVERT_RE.search(msg)
            if hit:
                # A cast names the type the value had to BECOME (e.g.
                # `(float)DAT_x` means DAT_x is a float); a plain assignment names
                # the value's OWN type, because it is the target that is wrong
                # (`DAT_x = some_float;` means DAT_x should hold a float, not that
                # the float should become a pointer).
                has_cast = re.search(r"\(\s*\w+\s*\**\s*\)\s*" + SYM_PATTERN, line) is not None
                kind = kind_of_ctype(hit.group(2 if has_cast else 1))
        if kind is None:
            deref = unary_deref_symbol(line)
            if deref:
                kind = "pointer"
        if kind is None:
            for rx, rule_kind in RULES:
                if rx.search(window):
                    kind = rule_kind
                    break
        if kind is None and code in ("C2296", "C2297"):
            # `A * B` with operands of the wrong type: float when the surrounding
            # statement is float arithmetic, otherwise an integer
            kind = "float" if ("(float)" in window or "float " in window) else "int"
        if kind is None:
            continue
        for name in names:
            if name not in table:
                table[name] = kind
                added += 1
    return added



def groups_by_address(seed: dict[str, str], span: int) -> dict[int, list[str]]:
    """Seeded symbols grouped by address, `span` bytes at a time."""
    wanted = set()
    for _code, _msg, line, _window in error_lines():
        wanted.update(SYM_RE.findall(line))
    groups: dict[int, list[str]] = {}
    for name in wanted:
        if name not in seed:
            continue
        hit = re.search(r"([0-9a-f]{6,8})$", name)
        if hit:
            groups.setdefault(int(hit.group(1), 16) // span, []).append(name)
    return groups


def groups_by_error_line(seed: dict[str, str]) -> dict[int, list[str]]:
    """Seeded symbols grouped as they co-occur on an error line.

    This is the unit that matters: `DAT_006d7b98 * _DAT_0057db20` only compiles when
    *both* slots are floats, so trying symbols one at a time (or by address) misses
    it, while the pair together is exactly the fix.
    """
    groups: dict[int, list[str]] = {}
    for _code, _msg, line, _window in error_lines():
        names = sorted({n for n in SYM_RE.findall(line) if n in seed})
        if names:
            key = int(names[0].split("_")[-1], 16)
            groups.setdefault(key, names)
    return groups


def implicated_families(seed: dict[str, str], span: int = 16, mode: str = "address") -> dict[int, list[str]]:
    return groups_by_error_line(seed) if mode == "error" else groups_by_address(seed, span)
    """Placeholder replaced above."""


def greedy_families(seed: dict[str, str], table: dict[str, str], best: int,
                    max_families: int, span: int = 16, mode: str = "error",
                    passes: int = 3) -> tuple[int, int]:
    """Try each implicated family; keep only the ones that improve the count."""
    kept = 0
    for p in range(passes):
        groups = implicated_families(seed, span, mode)
        fresh_groups = {k: [n for n in v if n not in table] for k, v in groups.items()}
        fresh_groups = {k: v for k, v in fresh_groups.items() if v}
        if not fresh_groups:
            break
        print(f"pass {p + 1}: {len(fresh_groups)} families implicated, span {span} bytes")
        chosen = sorted(fresh_groups.items(), key=lambda kv: -len(kv[1]))[:max_families]
        best, added_now = _try_families(seed, table, best, chosen, span)
        kept += added_now
        if not added_now:
            break
    return best, kept


def _try_families(seed, table, best, chosen, span):
    kept = 0
    for i, (page, names) in enumerate(chosen, 1):
        fresh = [n for n in names if n not in table]
        if not fresh:
            continue
        added = {n: seed[n] for n in fresh}
        table.update(added)
        save_overrides(table)
        subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                       capture_output=True, text=True)
        now = clean_count()
        if now > best:
            print(f"  [{i}/{len(chosen)}] group 0x{page * span:05X} ({len(fresh)} symbols): "
                  f"{best} -> {now} ({now - best:+d})  kept")
            best = now
            kept += 1
        else:
            for n in added:
                del table[n]
            save_overrides(table)
            subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                           capture_output=True, text=True)
    return best, kept


def clean_count() -> int:
    res = subprocess.run([sys.executable, str(ROOT / "tools" / "compile_check.py")],
                         capture_output=True, text=True)
    hit = re.search(r"compiling cleanly\s*:\s*(\d+)", res.stdout)
    return int(hit.group(1)) if hit else -1


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rounds", type=int, default=5)
    ap.add_argument("--families", action="store_true")
    ap.add_argument("--max-families", type=int, default=40)
    ap.add_argument("--family-span", type=int, default=16)
    ap.add_argument("--group", default="error", choices=("error", "address"))
    args = ap.parse_args()

    table = load_overrides()
    before = clean_count()
    print(f"baseline (no overrides): {before} functions compiling cleanly")

    seeded = {k: v for k, v in seed_from_asm(ROOT.parent / "WAD" / "groove.exe.asm").items()
              if k not in table}
    table.update(seeded)
    best = before
    if seeded:
        save_overrides(table)
        subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                       capture_output=True, text=True)
        after = clean_count()
        print(f"seeded {len(seeded)} types from x87 operands in the listing "
              f"(total {len(table)}): clean {before} -> {after} ({after - before:+d})")
        if after <= before:
            print("  the seed did not help: reverting the seeded keys only")
            for n in seeded:
                table.pop(n, None)          # keep overrides that already earned their place
            if table:
                save_overrides(table)
            else:
                OVERRIDES.unlink(missing_ok=True)
            subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                           capture_output=True, text=True)
        else:
            best = after
    print(f"working baseline: {best} functions compiling cleanly")

    for rnd in range(1, args.rounds + 1):
        added = infer(error_lines(), table)
        print(f"\nround {rnd}: {added} new types inferred (total {len(table)})")
        if not added:
            print("nothing new to infer - stopping")
            break
        save_overrides(table)
        subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                       capture_output=True, text=True)
        now = clean_count()
        print(f"  clean functions: {best} -> {now} ({now - best:+d})")
        if now <= best:
            print("  no gain: reverting the inferences from this round")
            table.clear()
            OVERRIDES.unlink(missing_ok=True)
            subprocess.run([sys.executable, str(ROOT / "tools" / "make_bulk.py")],
                           capture_output=True, text=True)
            break
        best = now

    if args.families:
        best, kept = greedy_families(
            seed_from_asm(ROOT.parent / "WAD" / "groove.exe.asm"),
            table, best, args.max_families, args.family_span, args.group)
        print(f"\nfamily search kept {kept} families")

    print(f"\nfinal: {best} functions compiling cleanly, {len(table)} overrides in the table")
    print(f"table: {OVERRIDES}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
