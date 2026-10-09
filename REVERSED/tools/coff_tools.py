"""coff_tools.py - minimal COFF (.obj) reader for the matching harness.

MSVC emits 32-bit COFF object files.  This reads the symbol table and the raw
section bytes back out, so the bytes of a single recompiled C function can be
extracted and compared against the original executable.

Only what the harness needs is implemented:
  * section headers (incl. the `/N` long-name form)
  * the symbol table (18-byte records, with aux records skipped)
  * per-section relocation entries, so DIR32 fields can be masked out when the
    rebuilt function is compared "modulo relocations" (globals live at different
    addresses in any rebuild, so their absolute dwords can never match as-is)
"""

from __future__ import annotations

import struct
from dataclasses import dataclass, field
from pathlib import Path

IMAGE_REL_I386_DIR32 = 0x0006
DIR32_TYPES = {IMAGE_REL_I386_DIR32, 0x0014, 0x0015, 0x0007}  # DIR32, REL32, DIR32NB, SECTION


@dataclass
class ObjSection:
    name: str
    raw_size: int
    raw_ptr: int
    reloc_ptr: int
    reloc_count: int
    chars: int
    data: bytes = b""
    reloc_offsets: set[int] = field(default_factory=set)


@dataclass
class ObjSymbol:
    name: str
    value: int
    section: int
    type: int
    storage: int


class CoffObject:
    def __init__(self, path: str | Path):
        self.path = Path(path)
        self.data = self.path.read_bytes()
        (self.machine, nsec, _, sym_ptr, nsyms, opt_size, _) = struct.unpack_from("<HHIIIHH", self.data, 0)
        if self.machine != 0x14C:
            raise ValueError(f"{self.path}: not an i386 COFF object (machine 0x{self.machine:04X})")
        self.sym_ptr = sym_ptr
        self.nsyms = nsyms
        self.sections = self._read_sections(nsec, 20 + opt_size)
        self.symbols = self._read_symbols(sym_ptr, nsyms)

    # -- parsing ------------------------------------------------------------
    def _read_sections(self, nsec: int, off: int) -> list[ObjSection]:
        secs: list[ObjSection] = []
        for _ in range(nsec):
            raw_name = self.data[off:off + 8]
            name = raw_name.rstrip(b"\0").decode("latin1")
            if name.startswith("/") and name[1:].isdigit():
                name = self._string(int(name[1:]))
            _, _vaddr, rawsize, rawptr, relptr, _, nrel, _, chars = struct.unpack_from("<IIIIIIHHI", self.data, off + 8)
            s = ObjSection(name=name, raw_size=rawsize, raw_ptr=rawptr,
                           reloc_ptr=relptr, reloc_count=nrel, chars=chars)
            if rawsize:
                s.data = self.data[rawptr:rawptr + rawsize]
            for r in range(nrel):
                s.reloc_offsets.add(struct.unpack_from("<I", self.data, relptr + r * 10)[0])
            secs.append(s)
            off += 40
        return secs

    def _read_symbols(self, sym_ptr: int, nsyms: int) -> list[ObjSymbol]:
        syms: list[ObjSymbol] = []
        i = 0
        while i < nsyms:
            off = sym_ptr + i * 18
            raw = self.data[off:off + 18]
            if len(raw) < 18:
                break
            if raw[0:4] == b"\0\0\0\0":
                name = self._string(struct.unpack_from("<I", raw, 4)[0])
            else:
                name = raw[0:8].split(b"\0")[0].decode("latin1")
            value, section, _typ, storage, naux = struct.unpack_from("<IhHBB", raw, 8)
            syms.append(ObjSymbol(name, value, section, _typ, storage))
            i += 1 + naux
        return syms

    def _string(self, offset: int) -> str:
        start = self.sym_ptr + self.nsyms * 18 + offset
        end = self.data.index(b"\0", start)
        return self.data[start:end].decode("latin1")

    # -- public API ---------------------------------------------------------
    def functions(self) -> dict[str, tuple[bytes, set[int]]]:
        """Map C function name -> (code bytes, relocated byte offsets inside them)."""
        by_section: dict[int, list[ObjSymbol]] = {}
        for s in self.symbols:
            if s.section > 0 and s.storage in (2, 3) and not s.name.startswith("."):
                by_section.setdefault(s.section, []).append(s)
        out: dict[str, tuple[bytes, set[int]]] = {}
        for sec_index, syms in by_section.items():
            sec = self.sections[sec_index - 1]
            if "text" not in sec.name:
                continue
            syms.sort(key=lambda s: s.value)
            for j, s in enumerate(syms):
                start = s.value
                end = syms[j + 1].value if j + 1 < len(syms) else sec.raw_size
                if end <= start:
                    continue
                body = sec.data[start:end].rstrip(b"\xcc\x90")   # drop inter-function padding
                reloc = {o - start for o in sec.reloc_offsets if start <= o < start + len(body)}
                out[strip_decoration(s.name)] = (body, reloc)
        return out


def strip_decoration(name: str) -> str:
    """Recover the plain function name from the linker's symbol decoration.

    C mode      : `_sub_415AB0` / `_sub_415AB0@8`
    C++ mode    : `?sub_415AB0@@YAXXZ` (cdecl), `?sub_413B10@@YGXPAX@Z` (fastcall),
                  `?sub_41BCB0@@YGPAXPAX@Z`
    """
    n = name
    if n.startswith("?"):
        return n[1:].split("@@")[0].split("@")[0]
    if n.startswith("_"):
        n = n[1:]
    if n.startswith("@"):
        n = n[1:]
    if "@" in n:
        n = n.split("@", 1)[0]
    return n
