"""gen_arity_patches.py - reconcile callee parameter lists with the call sites.

`C2197` ("troppi argomenti") happens when a call site passes more arguments than the
callee's definition declares.  Ghidra infers a signature from *one* call site, so a
function that the original called with extra values (typically in registers, which the
decompiler cannot see) ends up with a short parameter list.

Two shapes, two different fixes - the second one is why this tool no longer widens
every callee it sees:

* the definition already names parameters  -> **widen** it with unused ones.  The
  decompiled body only ever reads the parameters it names, so the extra arguments are
  ignored exactly as an unused register would be.  `sub_43B080` (2 -> 5) is this case.
* the definition is `(void)` - a *null subroutine*, e.g. `sub_426500`, whose whole
  body in the original is the single byte `C3` (`ret`) -> **replace `(void)` with
  `()`**.  Its call sites pass anywhere from 0 to 5 arguments
  (`sub_426500(s_Failed_to_load_ambient_sound_id___00578ec8, uVar8)` next to
  `sub_426500()`), and a visible definition with named parameters can only satisfy
  one of them: widening it to 5 moved the error to the 0-argument callers
  (`C2198` in `sub_4268C0`, measured).  An old-style `()` *definition* carries no
  parameter information at all, so every arity is accepted.  Measured with the
  toolchain used here: `int g() { return 2; }` compiles against `g()`, `g(1,2,3)`
  and `g(0x10,1,2,3,4)` in the same translation unit.

`C2198` (too *few* arguments) is not handled here: for the sites in this binary the
missing argument is the implicit `this` of a `__thiscall` call, which Ghidra dropped,
and inventing a value would be wrong - `sub_413BF0` is `basic_string::_Tidy(bool)`,
so a padded `0` becomes a NULL `this` and the body writes through it.  Those sites are
restored by hand from the listing (`mov ecx, ebp` = the enclosing `this`, `lea ecx,
[var_3C]` = a local object) and recorded in bulk_patches.csv like every other fix.
A tool cannot synthesize them: the call target is a FLIRT name in the listing
(`?_Tidy@?$basic_string@...`), not the `sub_XXXX` name Ghidra uses, so the call
instruction cannot be located by name.

The patches go into the recorded table (src_generated/bulk_patches.csv), so each one
survives regeneration and can be reviewed.

    python tools/compile_check.py            # fresh log first
    python tools/gen_arity_patches.py
"""

from __future__ import annotations

import csv
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "src_generated"
BUILD = ROOT / "build"
PATCHES = OUT / "bulk_patches.csv"

ERROR_RE = re.compile(r"(chunk_\d+\.c)\((\d+)\): error (C\d+): ([^\n]*)")
MARKER_RE = re.compile(r"^/\* ==== ([\w@]+) ==== \*/")


def split_top_level(text: str) -> list[str]:
    depth = 0
    parts, cur = [], ""
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


def chunk_owners(fname: str) -> tuple[list[str], dict[int, str]]:
    """(lines, line number -> function name) for one generated chunk."""
    try:
        lines = (OUT / "chunks" / fname).read_text(
            encoding="utf-8", errors="replace").splitlines()
    except FileNotFoundError:
        return [], {}
    own: dict[int, str] = {}
    cur = "?"
    for i, line in enumerate(lines, 1):
        m = MARKER_RE.match(line)
        if m:
            cur = m.group(1)
        own[i] = cur
    return lines, own


def bulk_locations() -> tuple[dict[str, str], list[str]]:
    """name -> signature line, taken from the generated bulk itself.

    The patch is applied to the bulk, so the text to match has to come from there -
    matching against `decompiled/` left two patches unable to find their line, because
    the generator rewrites and renames parts of those bodies on the way in.

    Ghidra wraps long parameter lists over several lines; those definitions are
    reported instead of being mangled (`sig.rindex(')')` used to raise on them).
    """
    out: dict[str, str] = {}
    wrapped: list[str] = []
    for chunk in sorted((OUT / "chunks").glob("*.c")):
        lines = chunk.read_text(encoding="utf-8", errors="replace").splitlines()
        cur = None
        for line in lines:
            m = MARKER_RE.match(line)
            if m:
                cur = m.group(1)
                continue
            if cur and (cur + "(") in line and not line.strip().startswith(("#", "/*")):
                sig = line.strip().rstrip(" {")
                if ")" not in sig:
                    wrapped.append(cur)          # wrapped signature: hand fix
                else:
                    out[cur] = sig
                cur = None
    return out, wrapped


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py first")
    text = log.read_text(encoding="latin1", errors="replace")

    # a function that is excluded from the clean subset cannot be compiled at all, so
    # a patch for it would never be applied - only noise in the table
    failed = OUT / "failed.txt"
    excluded = ({ln.strip() for ln in failed.read_text(encoding="utf-8").splitlines()
                 if ln.strip()} if failed.exists() else set())

    sources: dict[str, tuple[list[str], dict[int, str]]] = {}
    wanted: dict[str, int] = {}
    skipped_excluded = 0

    for fname, line_no, code, msg in ERROR_RE.findall(text):
        if code != "C2197":
            continue
        if fname not in sources:
            sources[fname] = chunk_owners(fname)
        src, own = sources[fname]
        i = int(line_no) - 1
        if not (0 <= i < len(src)):
            continue
        if own.get(int(line_no), "?") in excluded:
            skipped_excluded += 1
            continue
        call = src[i]
        # `NAME(...)` - take the first symbol with an argument list on that line
        hit = re.search(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^;]*)\)", call)
        if not hit:
            continue
        callee, args = hit.group(1), hit.group(2)
        passed = len(split_top_level(args)) if args.strip() else 0
        if passed > wanted.get(callee, 0):
            wanted[callee] = passed

    locations, wrapped = bulk_locations()
    rows = []
    for callee, passed in sorted(wanted.items()):
        sig = locations.get(callee)
        if not sig:
            continue
        declared = len(split_params(sig))
        inside = sig[sig.index("(") + 1:sig.rindex(")")].strip()
        if inside == "void":
            new_sig = sig[:sig.index("(") + 1] + ")"
            what = "null subroutine: (void) -> ()"
        else:
            if passed <= declared:
                continue
            added = "".join(f"int unused_arg_{declared + k}, " for k in range(passed - declared))
            new_sig = sig[:sig.index("(") + 1] + (inside + ", " + added).rstrip(", ") + ")"
            what = f"{declared} -> {passed} parameters"
        rows.append((callee, sig, new_sig))
        print(f"  {callee}: {what}")

    existing = []
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8") as fh:
            existing = [r for r in csv.DictReader(fh)]
    have = {(r["function"], r["find"]) for r in existing}
    added = 0
    for fn, find, repl in rows:
        if (fn, find) not in have:
            existing.append({"function": fn, "find": find, "replace": repl})
            added += 1

    with PATCHES.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=["function", "find", "replace"])
        w.writeheader()
        w.writerows(existing)
    print(f"added {added} arity patches; table now has {len(existing)} rows")
    if wrapped:
        print(f"  note: {len(wrapped)} definitions wrap over several lines and were "
              f"left for hand fixing: {', '.join(sorted(wrapped)[:6])}")
    if skipped_excluded:
        print(f"  note: {skipped_excluded} call site(s) are in functions excluded "
              f"from the clean subset (failed.txt)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
