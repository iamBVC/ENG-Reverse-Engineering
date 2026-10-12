"""Resolve a desktop crash trace against its matching x86 linker map; no launch."""
from pathlib import Path
import re
import sys
from bisect import bisect_right
from pe_tools import PE

ROOT = Path(__file__).resolve().parent.parent

def main():
    trace = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "build/run/groove_trace.log"
    map_file = Path(sys.argv[2]) if len(sys.argv) > 2 else ROOT / "build/groove_rebuild.map"
    exe_file = Path(sys.argv[3]) if len(sys.argv) > 3 else ROOT / "build/groove_rebuild.exe"
    text = trace.read_text(errors="replace")
    crashes = re.findall(r"\[crash\] code=([0-9a-fA-F]+) address=([0-9a-fA-F]+) "
                         r"module=([0-9a-fA-F]+) rva=([0-9a-fA-F]+)", text)
    if not crashes:
        print("No unhandled-exception record in this trace; last startup messages:")
        print("\n".join(text.splitlines()[-8:]))
        return 0
    mapping = map_file.read_text(encoding="latin1")
    preferred = re.search(r"Preferred load address is ([0-9a-fA-F]+)", mapping)
    if preferred is None:
        raise SystemExit("map has no preferred load address")
    base = int(preferred[1], 16)
    entries = sorted((int(m[2], 16) - base, m[1]) for m in re.finditer(
        r"^\s*[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8})", mapping, re.M))
    offsets = [offset for offset, _ in entries]
    image = PE(exe_file)
    for code, address, module, raw_rva in crashes:
        rva = int(raw_rva, 16)
        print(f"Exception 0x{code} at 0x{address}; image base 0x{module}, RVA 0x{rva:X}")
        if image.section_for_rva(rva) is None:
            print("  Fault address is outside this executable; no local symbol assigned.")
            continue
        index = bisect_right(offsets, rva) - 1
        if index < 0:
            print("  Fault is before the first map symbol.")
            continue
        start, name = entries[index]
        print(f"  Nearest map symbol: {name}+0x{rva - start:X} (use the matching build's map)")
    for line in text.splitlines():
        if line.startswith("[crash] access=") or line.startswith("[crash] eip="):
            print(line)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
