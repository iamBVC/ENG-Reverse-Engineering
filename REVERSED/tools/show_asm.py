"""show_asm.py - print the full listing of one or more functions.

    python tools/show_asm.py sub_415AB0 sub_41EF00
    python tools/show_asm.py --around 0x41EF00      functions near an address
    python tools/show_asm.py --list-leaf --max 32   smallest leaf functions
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from pe_tools import parse_listing, with_sizes  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent.parent
ASM = ROOT / "WAD" / "groove.exe.asm"


def main() -> int:
    funcs = with_sizes(parse_listing(ASM))
    by_name = {f.name: f for f in funcs}

    if "--list-leaf" in sys.argv:
        cap = int(sys.argv[sys.argv.index("--max") + 1]) if "--max" in sys.argv else 32
        leaves = [f for f in funcs if f.is_leaf and 0 < f.size <= cap]
        for f in sorted(leaves, key=lambda x: x.size):
            print(f"{f.name:<18} 0x{f.va:06X} {f.size:>4} B  {f.insns:>2} insn  {f.signature()}")
        print(f"\n{len(leaves)} leaf functions <= {cap} bytes")
        return 0

    if "--around" in sys.argv:
        va = int(sys.argv[sys.argv.index("--around") + 1], 16)
        near = [f for f in funcs if f.va and abs(f.va - va) < 0x400]
        for f in near:
            print(f"{f.name} 0x{f.va:06X} {f.size} B")
        return 0

    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    lines = ASM.read_text(encoding="latin1", errors="replace").splitlines()
    for name in names:
        f = by_name.get(name)
        if f is None:
            print(f"!! {name}: not found")
            continue
        print(f"===== {name}  0x{f.va:06X}  {f.size} bytes  {f.convention}"
              f"  args={','.join(f.args) or '-'}  callees={','.join(f.callees) or '-'}")
        for line in lines[f.asm_start - 1:f.asm_end]:
            print(line)
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
