"""pe_tools.py - PE32 reader + IDA listing function extractor.

Used by the groove.exe decompilation harness to pull the *original* machine code
of a single function straight out of the shipped executable, so a recompiled
function can be compared against it byte for byte.

Facts about the target (checked by `python tools/pe_tools.py --info`):

    groove.exe      1,642,496 bytes, PE32 (x86), ImageBase 0x400000
    linker version  6.0  (this is the reason byte-exact matching needs MSVC 6)
    .text           vaddr 0x1000, rawptr 0x1000  ->  file offset == RVA
    .reloc          0x2E0000; the HIGHLOW entries mark the dwords that hold
                    absolute addresses (needed for relocation-aware matching)

The IDA listing names every function `sub_<6 hex digits>`, and those digits are
the function's *virtual address*, so the listing alone is enough to cut the
original bytes out of the exe.
"""

from __future__ import annotations

import re
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path

IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_REL_BASED_HIGHLOW = 3

_FUNC_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s+proc\s+near")
_VA_RE = re.compile(r"^sub_([0-9A-Fa-f]{6})$")
_ARG_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)=\s*(dword|word|byte)\s+ptr\s+([0-9A-Fa-f]+)h?$")
_CALL_RE = re.compile(r"\bcall\s+([A-Za-z_][A-Za-z0-9_]*)")
_LABEL_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*:")


@dataclass(frozen=True)
class Section:
    name: str
    vaddr: int
    vsize: int
    rawptr: int
    rawsize: int
    chars: int

    @property
    def is_code(self) -> bool:
        return bool(self.chars & (IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE))


class PE:
    def __init__(self, path: str | Path):
        self.path = Path(path)
        self.data = self.path.read_bytes()
        pe_off = struct.unpack_from("<I", self.data, 0x3C)[0]
        if self.data[pe_off:pe_off + 4] != b"PE\0\0":
            raise ValueError(f"{self.path} is not a PE file")
        machine, nsec, timestamp, _, _, optsize, _ = struct.unpack_from("<HHIIIHH", self.data, pe_off + 4)
        self.machine = machine
        self.timestamp = timestamp
        opt = pe_off + 24
        self.opt_magic = struct.unpack_from("<H", self.data, opt)[0]
        self.linker_version = (self.data[opt + 2], self.data[opt + 3])
        self.image_base = struct.unpack_from("<I", self.data, opt + 28)[0]
        self.sections: list[Section] = []
        off = opt + optsize
        for _ in range(nsec):
            name = self.data[off:off + 8].rstrip(b"\0").decode("latin1")
            vsize, vaddr, rawsize, rawptr, _, _, _, _, chars = struct.unpack_from("<IIIIIIHHI", self.data, off + 8)
            self.sections.append(Section(name, vaddr, vsize, rawptr, rawsize, chars))
            off += 40
        self._reloc_dwords = self._parse_relocs()

    # -- address translation ------------------------------------------------
    def section_for_rva(self, rva: int) -> Section | None:
        for s in self.sections:
            if s.vaddr <= rva < s.vaddr + max(s.vsize, s.rawsize):
                return s
        return None

    def va_to_offset(self, va: int) -> int:
        s = self.section_for_rva(va - self.image_base)
        if s is None:
            raise ValueError(f"VA 0x{va:X} is not inside any section")
        return s.rawptr + (va - self.image_base - s.vaddr)

    def read(self, va: int, size: int) -> bytes:
        off = self.va_to_offset(va)
        return self.data[off:off + size]

    # -- relocations --------------------------------------------------------
    def _parse_relocs(self) -> set[int]:
        """Return the set of VAs whose dword holds an absolute address."""
        dwords: set[int] = set()
        s = next((x for x in self.sections if x.name == ".reloc"), None)
        if s is None:
            return dwords
        end = s.rawptr + s.rawsize
        p = s.rawptr
        while p + 8 <= end:
            page, blocksize = struct.unpack_from("<II", self.data, p)
            if blocksize < 8:
                break
            n = (blocksize - 8) // 2
            for i in range(n):
                entry = struct.unpack_from("<H", self.data, p + 8 + i * 2)[0]
                if (entry >> 12) == IMAGE_REL_BASED_HIGHLOW:
                    dwords.add(self.image_base + page + (entry & 0xFFF))
            p += blocksize
        return dwords

    @property
    def reloc_dwords(self) -> set[int]:
        return self._reloc_dwords


# ---------------------------------------------------------------------------
# IDA listing model
# ---------------------------------------------------------------------------

@dataclass
class Function:
    name: str
    va: int | None
    size: int = 0
    lines: int = 0
    insns: int = 0
    args: list[str] = field(default_factory=list)
    callees: list[str] = field(default_factory=list)
    ret_bytes: int = 0              # >0 => stdcall with N bytes of arguments
    asm_start: int = 0              # 1-based line numbers in the listing
    asm_end: int = 0

    @property
    def is_leaf(self) -> bool:
        return not self.callees

    @property
    def convention(self) -> str:
        return "stdcall" if self.ret_bytes else "cdecl"

    def signature(self) -> str:
        kind = {"dword": "int", "word": "short", "byte": "char"}
        types = []
        for a in self.args:
            m = _ARG_RE.match(a)
            types.append(kind.get(m.group(2), "int") if m else "int")
        return f"{self.name}({', '.join(types) if types else 'void'}) /* {self.convention} */"


def parse_listing(asm_path: str | Path) -> list[Function]:
    """Parse `groove.exe.asm` into a list of Function records, in address order."""
    asm_path = Path(asm_path)
    funcs: list[Function] = []
    cur: Function | None = None
    arg_lines: list[str] = []
    with asm_path.open("r", encoding="latin1", errors="replace") as fh:
        for lineno, line in enumerate(fh, 1):
            s = line.rstrip("\n")
            m = _FUNC_RE.match(s)
            if m and cur is None:
                name = m.group(1)
                va = None
                vm = _VA_RE.match(name)
                if vm:
                    va = int(vm.group(1), 16)
                cur = Function(name=name, va=va, asm_start=lineno)
                arg_lines = []
                continue
            if cur is None:
                continue
            if s.startswith(cur.name + " endp") or s.strip() == "endp":
                cur.asm_end = lineno
                # args are declared in the first lines of the proc body
                cur.args = [a for a in arg_lines if _ARG_RE.match(a)][:8]
                funcs.append(cur)
                cur = None
                continue
            stripped = s.strip()
            if "=" in stripped and not _LABEL_RE.match(stripped) and len(arg_lines) < 12 and lineno - cur.asm_start < 14:
                arg_lines.append(stripped.replace(" ", "").replace("=dwordptr", "= dword ptr ")
                                 .replace("=wordptr", "= word ptr ").replace("=byteptr", "= byte ptr "))
                continue
            if not stripped or stripped.startswith(";") or _LABEL_RE.match(stripped):
                continue
            cur.lines += 1
            if " " in stripped and not stripped.startswith(("align", "db ", "dd ")):
                cur.insns += 1
            for cm in _CALL_RE.finditer(stripped):
                target = cm.group(1)
                if target not in cur.callees:
                    cur.callees.append(target)
            rm = re.search(r"\bretn\s+([0-9A-Fa-f]+)h?\b", stripped)
            if rm:
                cur.ret_bytes = int(rm.group(1), 16)
    return funcs


def with_sizes(funcs: list[Function]) -> list[Function]:
    """Fill in `size` from consecutive addresses (trailing padding included)."""
    anchored = sorted((f for f in funcs if f.va is not None), key=lambda f: f.va)
    for i, f in enumerate(anchored):
        end = anchored[i + 1].va if i + 1 < len(anchored) else f.va
        f.size = max(0, end - f.va)
    return funcs


def main() -> int:
    here = Path(__file__).resolve().parent
    root = here.parent.parent
    exe = root / "WAD" / "groove.exe"
    asm = root / "WAD" / "groove.exe.asm"
    if "--info" in sys.argv and exe.exists():
        pe = PE(exe)
        print(f"{pe.path.name}: {len(pe.data):,} bytes")
        print(f"  image base    : 0x{pe.image_base:08X}")
        print(f"  linker version: {pe.linker_version[0]}.{pe.linker_version[1]}")
        for s in pe.sections:
            print(f"  {s.name:<8} vaddr=0x{s.vaddr:06X} vsize=0x{s.vsize:06X} {s.rawsize:>8,} raw")
        print(f"  reloc dwords  : {len(pe.reloc_dwords):,}")
    if "--probe" in sys.argv:
        pe = PE(exe)
        for name in sys.argv[sys.argv.index("--probe") + 1:]:
            m = _VA_RE.match(name)
            if not m:
                continue
            va = int(m.group(1), 16)
            print(f"{name} @ 0x{va:X}: {pe.read(va, 16).hex(' ')}")
    funcs = with_sizes(parse_listing(asm))
    anchored = [f for f in funcs if f.va is not None]
    code = sum(f.size for f in anchored)
    print(f"\nlisting: {len(funcs)} functions ({len(anchored)} with addresses), {code:,} code bytes")
    leaf = [f for f in funcs if f.is_leaf]
    small = [f for f in funcs if f.size and f.size <= 64]
    print(f"  leaf functions: {len(leaf)}   functions <= 64 bytes: {len(small)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

def export_names(path: str | Path) -> list[str]:
    """Names in a PE's export table (works for the harness DLLs)."""
    import struct
    data = Path(path).read_bytes()
    pe_off = struct.unpack_from("<I", data, 0x3C)[0]
    opt = pe_off + 24
    magic = struct.unpack_from("<H", data, opt)[0]
    # data directories start right after the fixed optional header fields
    dd = opt + (96 if magic == 0x10B else 112)
    exp_rva, exp_size = struct.unpack_from("<II", data, dd)
    if not exp_rva or not exp_size:
        return []
    pe = PE.__new__(PE)
    pe.data = data
    pe.image_base = struct.unpack_from("<I", data, opt + 28)[0]
    # reuse the section table parse only
    nsec = struct.unpack_from("<H", data, pe_off + 6)[0]
    optsize = struct.unpack_from("<H", data, pe_off + 20)[0]
    pe.sections = []
    off = pe_off + 24 + optsize
    for _ in range(nsec):
        name = data[off:off + 8].rstrip(bytes([0])).decode("latin1")
        vsize, vaddr, rawsize, rawptr = struct.unpack_from("<IIII", data, off + 8)
        pe.sections.append(Section(name, vaddr, vsize, rawptr, rawsize, 0))
        off += 40
    e = pe.va_to_offset(pe.image_base + exp_rva)
    nnames = struct.unpack_from("<I", data, e + 24)[0]
    names_rva = struct.unpack_from("<I", data, e + 32)[0]
    base = pe.va_to_offset(pe.image_base + names_rva)
    out = []
    for i in range(nnames):
        rva = struct.unpack_from("<I", data, base + i * 4)[0]
        o = pe.va_to_offset(pe.image_base + rva)
        end = data.index(bytes([0]), o)
        out.append(data[o:end].decode("latin1"))
    return sorted(out)
