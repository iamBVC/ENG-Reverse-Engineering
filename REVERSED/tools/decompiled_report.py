"""decompiled_report.py - audit the Ghidra output in REVERSED/decompiled/.

Answers the question "what is between the decompiled C and a compiling
translation unit?" by counting the Ghidra pseudo-types, intrinsics and unnamed
symbols the output actually uses.  Run after tools/ghidra_decompile.bat.

    python tools/decompiled_report.py
    python tools/decompiled_report.py --functions      list the function inventory
"""

from __future__ import annotations

import csv
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEC = ROOT / "decompiled"

# Ghidra pseudo-types that need typedefs in the shim header.
PSEUDO_TYPES = [
    "undefined8", "undefined4", "undefined2", "undefined1", "undefined",
    "ulonglong", "longlong", "ushort", "uchar", "uint", "ulong", "byte", "code",
]

# Ghidra intrinsics/macros that need real implementations or hand fixes.
INTRINSICS = [
    "CONCAT44", "CONCAT31", "CONCAT22", "CONCAT13", "CONCAT12", "CONCAT11",
    "SUB84", "SUB41", "SUB42", "ZEXT14", "ZEXT24", "ZEXT12", "SEXT14", "SEXT24",
    "__CFADD__", "__CFSUB__", "__OFADD__", "__OFSUB__", "__PAIR64__",
    "__umulh", "__divdi3", "__moddi3", "__udivdi3", "__umoddi3",
    "__security_check_cookie", "_DAT_", "__return_address",
]

# Compiler-generated artefacts from partial register knowledge.
ARTIFACTS = [
    "unaff_", "extraout_", "in_stack_", "in_EAX", "in_ECX", "in_EDX", "in_EBX",
    "in_ESP", "in_EBP", "in_ESI", "in_EDI", "uRam", "UNK_", "LAB_", "SUB_",
]

SYMBOL_RE = re.compile(r"\b(DAT_[0-9a-fA-F]{8}|UNK_[0-9a-fA-F]{8}|LAB_[0-9a-fA-F]{8}|"
                       r"PTR_[0-9a-fA-F]{8}|s_[0-9a-fA-F]{8})\b")
FUNC_DEF_RE = re.compile(r"^[A-Za-z_][\w \*]*\b(sub_[0-9A-F]{6})\s*\(", re.M)


def main() -> int:
    files = sorted(p for p in DEC.glob("*.c"))
    if not files:
        print(f"no decompiled .c files in {DEC} - run tools/ghidra_decompile.bat first")
        return 1

    text = "\n".join(p.read_text(encoding="utf-8", errors="replace") for p in files)
    lines = text.count("\n")
    print(f"files      : {len(files)}")
    print(f"total lines: {lines:,}")
    print(f"total size : {sum(p.stat().st_size for p in files)/1024:.0f} KiB")

    index = DEC / "_index.csv"
    if index.exists():
        rows = list(csv.DictReader(index.open(encoding="utf-8")))
        ok = sum(1 for r in rows if r["status"] == "ok")
        bad = [r for r in rows if r["status"] != "ok"]
        print(f"decompiled : {ok}/{len(rows)} ok")
        for r in bad:
            print(f"   FAILED {r['name']} @ {r['address']} ({r['size']} bytes)")

    print("\npseudo-types (need typedefs in the shim header):")
    for t in PSEUDO_TYPES:
        n = len(re.findall(r"\b" + t + r"\b", text))
        if n:
            print(f"   {t:<12} {n:>7}")

    print("\nintrinsics (need implementations or hand fixes):")
    for t in INTRINSICS:
        n = len(re.findall(r"\b" + re.escape(t), text))
        if n:
            print(f"   {t:<24} {n:>7}")

    print("\ncompiler artefacts (partial-register / undeclared labels):")
    for t in ARTIFACTS:
        n = len(re.findall(re.escape(t), text))
        if n:
            print(f"   {t + '<...>':<24} {n:>7}")

    syms = Counter(SYMBOL_RE.findall(text))
    by_kind: Counter = Counter(s.split("_")[0] for s in syms)
    print(f"\nunnamed data/code symbols: {len(syms)} distinct "
          f"({', '.join(f'{k}:{v}' for k, v in by_kind.most_common())})")
    print("   " + ", ".join(s for s, _ in syms.most_common(12)))

    if "--functions" in sys.argv:
        print("\nfunction inventory (first 40 by address):")
        fns = sorted(FUNC_DEF_RE.findall(text))
        for f in fns[:40]:
            print("   " + f)
        print(f"   ... {len(fns)} function definitions found in the .c files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
