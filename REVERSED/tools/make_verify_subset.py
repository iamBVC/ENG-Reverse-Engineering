"""make_verify_subset.py - build a small, linkable DLL from the decompiled side.

The full bulk cannot be linked yet: it references the binary's own CRT/SEH helpers
(`__allmul`, `__CxxThrowException@8`, ...) which the generator leaves to the system,
plus the Win32/DirectX/Miles imports.  That is a link-level problem, not a
correctness problem.

For verification we only need the functions the harness can actually drive, so this
emits one translation unit: the preamble, the decompiled bodies, cdecl wrappers with
the same names the hand-ported DLL exports, and two kinds of documented patches -
BODY_PATCHES for decompiler artefacts, CHECKPOINT_ANCHORS for progress markers in
the MAP loader.

    python tools/make_verify_subset.py
"""

from __future__ import annotations

import csv
import importlib.util
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEC = ROOT / "decompiled"
OUT = ROOT / "harness"

spec = importlib.util.spec_from_file_location("make_bulk", ROOT / "tools" / "make_bulk.py")
make_bulk = importlib.util.module_from_spec(spec)
spec.loader.exec_module(make_bulk)

NL = chr(10)                 # a real newline in the generated C
ESC_N = chr(92) + "n"        # the two characters backslash + n for a C literal

WRAPPERS = {
    "sub_41EF00": "WH_EXPORT void *wh_sub_41EF00(int size) { return (void *)sub_41EF00(size); }",
    "sub_41EEE0": "WH_EXPORT void  wh_sub_41EEE0(void) { sub_41EEE0(); }",
    "sub_41ED90": "WH_EXPORT void *wh_sub_41ED90(int size) { return (void *)sub_41ED90(size); }",
    "sub_4136C0": "WH_EXPORT int wh_sub_4136C0(int a, int b) { return sub_4136C0(a, b); }",
    "sub_4255A0": "WH_EXPORT int wh_sub_4255A0(void) { return sub_4255A0(); }",
    "sub_426860": "WH_EXPORT int wh_sub_426860(void) { return sub_426860(); }",
    "sub_406E30": "WH_EXPORT void wh_sub_406E30(void) { sub_406E30(); }",
    "sub_4155E0": "WH_EXPORT void wh_sub_4155E0(void) { sub_4155E0(); }",
    "sub_41D330": "WH_EXPORT void wh_sub_41D330(void) { sub_41D330(); }",
    "sub_41E1B0": "WH_EXPORT void wh_sub_41E1B0(void) { sub_41E1B0(); }",
    "sub_40E0A0": "WH_EXPORT void wh_sub_40E0A0(void) { sub_40E0A0(); }",
    "sub_5563F0": "WH_EXPORT int wh_sub_5563F0(void *cursor_slot, int record_count, void *out_records) "
                  "{ return sub_5563F0((int *)cursor_slot, record_count, (int *)out_records); }",
    "sub_42AC50": "WH_EXPORT void wh_sub_42AC50(void *world, void *stream) "
                  "{ sub_42AC50((uint *)world, (undefined4)(size_t)stream); }",
}

# Hand fixes applied to decompiled bodies that are specific to *this* subset.
# The general ones - including the switch/case and the two restored `__ftol` operands
# for sub_42AC50 - live in src_generated/bulk_patches.csv and are applied here too
# (see load_bulk_patches): the harness is supposed to verify the *bulk* implementation,
# and while the two tables were separate this side drifted - the generated
# ghidra_prototypes.h declared `int sub_406E30()` (the bulk patches its `void` return
# type) against a `void` definition here, C2371, until the shared table was applied.
BODY_PATCHES = {
    "sub_42AC50": [
        # the conversions the greyscale colour path needs (the driver disables that path,
        # 0x6D7C61 set); they only have to link, so they go to a stub
        ("__ftol()", "groove_ftol()"),
    ],
}


def load_bulk_patches() -> dict[str, list[tuple[str, str]]]:
    """(find, replace) rows per function, from the recorded table."""
    out: dict[str, list[tuple[str, str]]] = {}
    path = ROOT / "src_generated" / "bulk_patches.csv"
    if not path.exists():
        return out
    with path.open(encoding="utf-8", newline="") as fh:
        for row in csv.DictReader(fh):
            out.setdefault(row["function"], []).append((row["find"], row["replace"]))
    return out

# Progress markers for the MAP loader, so a fault can be attributed to a load stage
# instead of guessed at.
CHECKPOINT_ANCHORS = [
    ("uVar8 = sub_41EF00(local_10 * 4);", "section2"),
    ("uVar8 = sub_41EF00(*puVar12 * 0x5c);", "section3"),
    ("uVar8 = sub_41EF00(*puVar12 * 0x30);", "section4"),
    ("DAT_006da350 = sub_41EF00(0x100);", "section5"),
    ("uVar8 = sub_41EF00(puVar5[6] * puVar5[5] * 4);", "grid_flat"),
    ("uVar8 = sub_41EF00(*puVar5 << 5);", "placements"),
    ("uVar8 = sub_41EF00(*puVar5 << 2);", "tile_trak"),
    ("uVar8 = sub_41EF00(*puVar12 * 0x18);", "optional20"),
    ("uVar8 = sub_41EF00(iVar18);", "colours"),
    ("sub_41EF00((uVar8 - 1) * local_18 * 4);", "colour_layers"),
    ("uVar11 = sub_41EF00((uint)*(ushort *)", "colour_extra"),
    ("*(undefined4 *)(puVar5[0x16] + iVar9) = uVar11;", "tile"),
    ("uVar8 = sub_41EF00(*puVar12 * 0x48);", "objects"),
    ("DAT_006d9c90 = sub_41EF00(DAT_006d9cc0 * 8);", "group_table"),
    ("DAT_006da320 = 100;", "final"),
]

NOTE = """
/* Deliberately absent from this side:
 *   sub_415A90 / sub_415AB0 / sub_415AD0 / sub_415AF0   - supplied by io_substitutes.c
 *   sub_40D900 / sub_40D910 / sub_40E020 / sub_41EEA0   - not separate Ghidra functions
 */
"""


def patches_for(name):
    """(search, replace) pairs to apply to one decompiled body."""
    out = list(BODY_PATCHES.get(name, []))
    if name == "sub_42AC50":
        for anchor, label in CHECKPOINT_ANCHORS:
            if label == "tile":
                marker = ('printf("[map] tile %d' + ESC_N + '", iVar9); fflush(stdout);'
                          + NL + anchor)
            else:
                marker = 'printf("[map] ' + label + ESC_N + '"); fflush(stdout);' + NL + anchor
            out.append((anchor, marker))
    return out


def missing_bodies_from_link_log():
    """Functions the last link wanted: the in-binary CRT/C++ helpers."""
    log = ROOT / "build" / "_ghidra_link.log"
    if not log.exists():
        return set()
    text = log.read_text(encoding="latin1", errors="replace")
    wanted = set()
    for line in text.splitlines():
        if "LNK2001" not in line and "LNK2019" not in line:
            continue
        for m in re.finditer(r"_?(sub_[0-9A-F]{6})\b", line):
            wanted.add(m.group(1))
    return {w for w in wanted if (DEC / (w + ".c")).exists()}


def main():
    preamble = ("#include <stdio.h>" + NL
                + '#include "ghidra_shim.h"' + NL
                + '#include "ghidra_globals.h"' + NL
                + '#include "ghidra_prototypes.h"' + NL + NL
                + "#define WH_EXPORT __declspec(dllexport)" + NL)
    parts = ["/* generated by tools/make_verify_subset.py - do not edit */", preamble]
    included, skipped = [], []
    for name, wrapper in WRAPPERS.items():
        path = DEC / (name + ".c")
        if not path.exists():
            skipped.append(name)
            continue
        parts.append(NL + "/* ==== " + name + " ==== */" + NL)
        body = make_bulk.normalize(path.read_text(encoding="utf-8", errors="replace"))
        for old, new in load_bulk_patches().get(name, []) + patches_for(name):
            if old not in body:
                print("  note: pattern not found in " + name + ": " + repr(old[:40]))
            body = body.replace(old, new)
        parts.append(body)
        parts.append(wrapper + NL)
        included.append(name)

    carried = sorted(missing_bodies_from_link_log() - set(included))
    for name in carried:
        parts.append(NL + "/* ==== " + name + " (carried) ==== */" + NL)
        parts.append(make_bulk.normalize((DEC / (name + ".c")).read_text(encoding="utf-8", errors="replace")))
        parts.append(NL)

    parts.append(NOTE)
    (OUT / "verify_subset.c").write_text(NL.join(parts), encoding="utf-8")
    print("wrote harness/verify_subset.c: " + str(len(included)) + " functions"
          + (", " + str(len(carried)) + " carried dependencies" if carried else ""))
    if skipped:
        print("  skipped (no separate Ghidra function): " + ", ".join(skipped))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
