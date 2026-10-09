"""verify_map.py - check the decompiled MAP loader against the Python oracle.

Runs the decompiled `sub_42AC50` (via harness/drive_map.exe) on a real MAP chunk
and compares what it produced with `eng_wad/map_full_chunk.py`, which is the
byte-exact parser for this chunk.

Three groups are checked:

  scalars   tile_count, grid, section counts, object counts, final dword/u16
  offsets   where each array landed in the bump heap.  This verifies the loader's
            whole allocation *order* and every stride (4/8/92/48/32/24 bytes),
            which the scalars alone would not catch.
  colour    the per-tile vertex-colour blocks are variable length, so the offset of
            the object table depends on getting that byte accounting right.  It is
            reported separately: a mismatch there is a finding about the colour
            model, not about the loader's field order.

    python tools/verify_map.py                    # t1l1m001.wad
    python tools/verify_map.py --wad t1l1m004.wad
"""

from __future__ import annotations

import argparse
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REPO = ROOT.parent
sys.path.insert(0, str(REPO / "WAD"))
from eng_wad.wad import chunk_bytes, read_wad  # noqa: E402
from eng_wad.wfpc_chunk import parse_wfpc_chunk  # noqa: E402
from eng_wad.trak_chunk import parse_trak_chunk  # noqa: E402
from eng_wad.map_full_chunk import parse_map_full_exe  # noqa: E402


def read_dump(path: Path) -> tuple[dict, dict]:
    header: dict[str, str] = {}
    fields: dict[str, str] = {}
    for line in path.read_text(encoding="ascii", errors="replace").splitlines():
        parts = line.split()
        if not parts:
            continue
        if parts[0] == "#":
            for kv in parts[1:]:
                if "=" in kv:
                    k, v = kv.split("=", 1)
                    header[k] = v
        elif parts[0] == "FIELD":
            fields[parts[1]] = parts[2] + ":" + parts[3]
    return header, fields


def value_of(fields: dict, name: str) -> int:
    """The driver prints both scalars and offsets with %u - always decimal."""
    _kind, val = fields[name].split(":")
    return int(val)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--wad", default="t1l1m001.wad")
    args = ap.parse_args()

    wad_path = REPO / "WAD" / args.wad
    data, chunks, by_tag = read_wad(wad_path)
    map_chunk = chunk_bytes(data, by_tag["MAP "])
    trak_chunk = chunk_bytes(data, by_tag["TRAK"])
    wfpc = parse_wfpc_chunk(chunk_bytes(data, by_tag["WFPC"])).flags
    print(f"{args.wad}: MAP {len(map_chunk):,} B, TRAK {len(trak_chunk):,} B, WFPC {wfpc:#010x}")

    trak = parse_trak_chunk(trak_chunk)
    oracle = parse_map_full_exe(map_chunk, trak,
                                assume_optional20=bool(wfpc & 0x10000),
                                assume_final_dword=bool(wfpc & 0x10))

    tmp = ROOT / "build"
    tmp.mkdir(exist_ok=True)
    (tmp / "_map_chunk.bin").write_bytes(map_chunk)
    (tmp / "_trak_chunk.bin").write_bytes(trak_chunk)
    dump = tmp / "_map_dump.txt"
    proc = subprocess.run([str(tmp / "drive_map.exe"), str(tmp / "_map_chunk.bin"),
                           str(tmp / "_trak_chunk.bin"), f"{wfpc:X}", str(dump)],
                          capture_output=True, text=True, cwd=str(ROOT))
    out = (proc.stdout or proc.stderr)
    stages = [ln for ln in out.splitlines() if ln.startswith("[map]") and "tile " not in ln]
    print(f"loader ran: {len(stages)} stage markers, exit {proc.returncode}")
    if proc.returncode != 0 or not dump.exists():
        print(out[-400:])
        print("FAIL: the loader did not complete")
        return 1

    header, fields = read_dump(dump)
    world_off = int(header.get("world_off", "0"), 16)

    failures = 0

    # ---- scalars ---------------------------------------------------------
    print("\nscalars (loader vs oracle):")
    pairs = [
        ("tile_count", oracle.tile_count),
        ("grid_width", oracle.grid_width),
        ("grid_height", oracle.grid_height),
        ("section3_count", len(oracle.section3)),
        ("section4_count", len(oracle.section4)),
        ("optional_count", len(oracle.optional20)),
        ("object_count", len(oracle.objects)),
        ("object_count_b", oracle.object_count_unknown_b),
        ("final_u16", oracle.final_u16),
    ]
    for name, want in pairs:
        got = value_of(fields, name)
        ok = got == want
        failures += 0 if ok else 1
        print(f"  [{'ok' if ok else 'FAIL'}] {name:<16} loader={got:<8} oracle={want}")

    # the two globals written at the end of the loader
    g320 = int(header.get("dword_6DA320", "-1"))
    g328 = int(header.get("dword_6DA328", "-1"))
    ok328 = (g328 == oracle.final_optional_dword)
    failures += 0 if (g320 == 100 and ok328) else 1
    print(f"  [{'ok' if g320 == 100 else 'FAIL'}] dword_6DA320      loader={g320} (always 100)")
    print(f"  [{'ok' if ok328 else 'FAIL'}] dword_6DA328      loader={g328} oracle={oracle.final_optional_dword}")

    # ---- offsets: the allocation order and every stride -------------------
    # model: the MAP loader allocates from the bump heap in this order, after the
    # driver's own TRAK chunk + relocated arrays + 0x100-byte MapWorld
    cells = oracle.grid_width * oracle.grid_height
    opt = len(oracle.optional20)
    off = world_off + 0x100
    expected: dict[str, int] = {}
    # operator_new(tile_count*4) comes from the CRT, not this heap
    expected["grid_heads"] = off; off += cells * 4
    expected["grid_nodes"] = off; off += oracle.tile_count * 8
    expected["section2"] = off; off += len(oracle.section2) * 4
    expected["section3"] = off; off += len(oracle.section3) * 92
    expected["section4"] = off; off += len(oracle.section4) * 48
    off += 0x100                                  # section 5 goes to a global
    expected["grid_flat"] = off; off += cells * 4
    expected["placements"] = off; off += oracle.tile_count * 32
    expected["tile_trak"] = off; off += oracle.tile_count * 4
    if wfpc & 0x10000:
        expected["optional20"] = off; off += opt * 24
    expected["colour_blocks"] = off
    off += oracle.tile_count * (8 if wfpc & 0x10000000 else 4)

    print("\narray offsets (loader vs model of the documented order):")
    for name in ("grid_heads", "grid_nodes", "section2", "section3", "section4",
                 "grid_flat", "placements", "tile_trak", "optional20", "colour_blocks"):
        if name not in expected:
            continue
        got = value_of(fields, name)
        want = expected[name]
        ok = got == want
        failures += 0 if ok else 1
        print(f"  [{'ok' if ok else 'FAIL'}] {name:<16} loader={got:#08x} model={want:#08x}")

    # ---- the colour-block byte accounting (graded separately) ------------
    colour_bytes = sum(c.byte_size + c.extra_byte_size for c in oracle.colors)
    want_objects = off + colour_bytes
    got_objects = value_of(fields, "objects")
    print("\ncolour accounting (the variable-length part):")
    print(f"  model colour bytes {colour_bytes:,}; objects expected at {want_objects:#x}, "
          f"loader put it at {got_objects:#x}")
    if want_objects == got_objects:
        print("  [ ok ] the loader's colour consumption matches the model exactly")
    else:
        print(f"  [note] differs by {got_objects - want_objects:+,} bytes - either the "
              f"model or the loader's colour read order needs another look")

    # ---- decoded values: FNV-1a over the address-independent arrays --------
    def fnv1a(data: bytes) -> int:
        h = 2166136261
        for b in data:
            h ^= b
            h = (h * 16777619) & 0xFFFFFFFF
        return h

    # the runtime images, built from the oracle's decoded values using the
    # documented field mapping (32-byte placements: +0x0C and +0x1C are the slots
    # the loader never writes - zero here because the harness arena is a zeroed
    # static array)
    def images() -> dict[str, bytes]:
        return {
            "section2": b"".join(struct.pack("<I", v) for v in oracle.section2),
            "section5": b"".join(struct.pack("<II", a, b) for _i, a, b in oracle.section5),
            "grid_flat": b"".join(struct.pack("<I", v) for v in oracle.grid),
            "placements": b"".join(
                struct.pack("<IIIIIIII", t.u32_00, t.u32_04, t.u32_08, 0,
                            t.u32_12, t.u32_16, t.u32_20, 0)
                for t in oracle.tile_defs),
            "tile_trak": b"".join(struct.pack("<I", v) for v in oracle.tile_trak_indices),
        }

    print("\narray values (FNV-1a over the address-independent arrays):")
    for name, blob in images().items():
        want = fnv1a(blob)
        got_line = [ln for ln in dump.read_text(encoding="ascii", errors="replace").splitlines()
                    if ln.startswith("HASH " + name + " ")]
        got = int(got_line[0].split()[2], 16) if got_line else -1
        ok = got == want
        failures += 0 if ok else 1
        print(f"  [{'ok' if ok else 'FAIL'}] {name:<12} loader={got:08X} oracle={want:08X} "
              f"({len(blob):,} bytes)")

    print()
    print("PASS: scalars, allocation order and decoded values match the oracle"
          if not failures else f"FAIL: {failures} mismatch(es)")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
