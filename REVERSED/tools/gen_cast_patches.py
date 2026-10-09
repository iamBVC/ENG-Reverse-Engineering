"""gen_cast_patches.py - insert the `(int)` intermediate MSVC needs in a *cast*.

Scope, measured rather than assumed: this tool only helps `C2440` errors whose
message is about a **conversion that is written as a cast on the erroring line**,
i.e. the target type appears there as `(T)` and the operand cannot convert to it
directly:

    (ushort *)(float_expression)   ->  (ushort *)(int)(float_expression)
    (float)pointer_typed_global    ->  (float)(int)pointer_typed_global

On the bulk as of this round it finds **nothing**: the two `C2440`s that were in the
log when this was written were plain assignments, not casts -

    error C2440: '=': impossibile convertire da 'float' a 'unsigned int *'
    sub_410700:  DAT_00583390 = _DAT_00583388 - param_4;

- and their cause was not a cast at all: `make_bulk.py`'s unary-`*` test mistook
`a * DAT_00583390` for a dereference and declared the slot `unsigned int *`, so the
fix belongs in the *generator*, not at the assignment.  (An earlier version of this
docstring claimed "almost every remaining C2440 has the same shape"; the log did not
support that and the claim is gone.)

Two limits worth knowing before trusting it:

* one cast per line per round.  The occurrence patched is the *first* one of the
  target type on the line; if that one already carries `(int)`, the line is skipped
  from then on, even when a later occurrence on the same line still errors.  So
  "found nothing" and "fixed everything" are both possible outcomes of one round -
  `tools/compile_check.py` decides.
* it never invents a cast where the source has none (it cannot know which operand the
  compiler meant), which is why the two `C2440`s above were reported as skipped.

Sites in functions excluded from the clean subset (failed.txt) are ignored: a patch
there would never be compiled.

    python tools/compile_check.py       # fresh log first
    python tools/gen_cast_patches.py
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
CONVERT_RE = re.compile(r"(?:da|from) '([^']*)' (?:a|to) '([^']*)'")


def main() -> int:
    log = BUILD / "_bulk_compile.log"
    if not log.exists():
        raise SystemExit(f"{log} missing - run tools/compile_check.py first")
    text = log.read_text(encoding="latin1", errors="replace")

    failed = OUT / "failed.txt"
    excluded = ({ln.strip() for ln in failed.read_text(encoding="utf-8").splitlines()
                 if ln.strip()} if failed.exists() else set())

    owners: dict[str, dict[int, str]] = {}
    sources: dict[str, list[str]] = {}
    rows: list[dict] = []
    have: set[tuple[str, str]] = set()
    skipped_no_cast = 0
    skipped_other = 0

    for fname, line_no, code, msg in ERROR_RE.findall(text):
        if code != "C2440":
            continue
        hit = CONVERT_RE.search(msg)
        if not hit:
            skipped_other += 1
            continue
        target = hit.group(2)
        if fname not in sources:
            try:
                sources[fname] = (OUT / "chunks" / fname).read_text(
                    encoding="utf-8", errors="replace").splitlines()
            except FileNotFoundError:
                sources[fname] = []
            cur, own = "?", {}
            for i, line in enumerate(sources[fname], 1):
                m = MARKER_RE.match(line)
                if m:
                    cur = m.group(1)
                own[i] = cur
            owners[fname] = own
        src = sources[fname]
        i = int(line_no) - 1
        if not (0 <= i < len(src)):
            continue
        line = src[i]
        fn = owners[fname].get(i + 1, "?")
        if fn in excluded:
            skipped_other += 1
            continue

        # the cast to insert after: the first one of the target type that is not
        # already followed by an integer conversion
        cast_re = re.compile(re.escape("(" + target + ")") + r"(?!\s*\(\s*int\s*\))")
        m = cast_re.search(line)
        if not m:
            # no cast of that type on the line: an assignment or a call argument,
            # which needs a type decision, not a cast
            skipped_no_cast += 1
            continue
        if (fn, line.strip()) in have:
            skipped_other += 1
            continue
        have.add((fn, line.strip()))
        new_line = line[:m.end()] + "(int)" + line[m.end():]
        rows.append({"function": fn, "find": line.strip(), "replace": new_line.strip()})

    existing: list[dict] = []
    if PATCHES.exists():
        with PATCHES.open(encoding="utf-8") as fh:
            existing = [r for r in csv.DictReader(fh)]
    existing_keys = {(r["function"], r["find"]) for r in existing}
    added = [r for r in rows if (r["function"], r["find"]) not in existing_keys]
    existing.extend(added)

    with PATCHES.open("w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=["function", "find", "replace"])
        w.writeheader()
        w.writerows(existing)
    print(f"added {len(added)} cast patches; table now has {len(existing)} rows")
    if skipped_no_cast:
        print(f"  note: {skipped_no_cast} C2440 line(s) have no cast of the target type "
              f"- they need a type decision (type_overrides.csv), not a cast")
    if skipped_other:
        print(f"  note: {skipped_other} C2440 line(s) skipped (already patched, or the "
              f"function is excluded from the clean subset)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
