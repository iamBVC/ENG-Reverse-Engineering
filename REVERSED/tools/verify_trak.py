"""verify_trak.py - check the decompiled TRAK loader against real game data.

Feeds a real `TRAK` chunk (from a shipped WAD) to the decompiled `sub_5563F0` in
the harness DLL, then verifies what it produced against an independent computation
straight from the same bytes:

  * the three sub-array offsets it allocated per record (24 bytes per vertex,
    28 per triangle, 32 per collision entry, in that order, bump-allocated from
    the end of the 132-byte header table), and
  * every triangle's material index, recovered from the pointer it stored
    (`base + 20 * index`).

So this compares the *code* against the format spec, not against another copy of
itself.  The driver is 32-bit C because the Python here is 64-bit and cannot load
the DLL.

    python tools/verify_trak.py                       # uses t1l1m001.wad
    python tools/verify_trak.py --wad t1l1m003.wad
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

HEADER = 132          # GeometryRecord84


def expected(chunk: bytes) -> tuple[list[dict], list[tuple[int, int, int]]]:
    """Independent model: walk the format the loader follows, from the bytes."""
    count = struct.unpack_from("<I", chunk, 0)[0]
    cursor = 4 + HEADER * count
    records: list[dict] = []
    materials: list[tuple[int, int, int]] = []

    for i in range(count):
        base = 4 + HEADER * i
        vc = struct.unpack_from("<H", chunk, base + 0x6C)[0]
        tc = struct.unpack_from("<H", chunk, base + 0x6E)[0]
        coll = sum(struct.unpack_from("<H", chunk, base + off)[0]
                   for off in (0x78, 0x7A, 0x7C))

        def alloc(nbytes: int) -> int:
            nonlocal cursor
            if nbytes == 0:
                return 0
            start = cursor
            cursor += nbytes
            return start

        vtx = alloc(24 * vc)
        tri = alloc(28 * tc)
        col = alloc(32 * coll)
        records.append({"vc": vc, "tc": tc, "coll": coll,
                        "vtx": vtx, "tri": tri, "col": col})
        for j in range(tc):
            materials.append((i, j, struct.unpack_from("<H", chunk, tri + 28 * j + 8)[0]))
    return records, materials


def parse_dump(path: Path) -> tuple[dict, list[dict], list[tuple[int, int, int]]]:
    header: dict[str, int] = {}
    records: list[dict] = []
    materials: list[tuple[int, int, int]] = []
    for line in path.read_text(encoding="ascii", errors="replace").splitlines():
        parts = line.split()
        if not parts:
            continue
        if parts[0] == "#":
            for kv in parts[1:]:
                if "=" in kv:
                    k, v = kv.split("=", 1)
                    try:
                        header[k] = int(v, 16) if (len(v) == 8 and all(c in "0123456789ABCDEF" for c in v)) else int(v)
                    except ValueError:
                        pass
        elif parts[0] == "REC":
            fields = dict(p.split("=") for p in parts[2:])
            records.append({k.replace("_off", ""): (int(v, 16) if k.endswith("off") else int(v))
                            for k, v in fields.items()})
        elif parts[0] == "TRI":
            materials.append((int(parts[1]), int(parts[2]), int(parts[3].split("=")[1])))
    return header, records, materials


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--wad", default="t1l1m001.wad")
    args = ap.parse_args()

    wad_path = REPO / "WAD" / args.wad
    data, chunks, by_tag = read_wad(wad_path)
    chunk = chunk_bytes(data, by_tag["TRAK"])
    print(f"{args.wad}: TRAK chunk {len(chunk):,} bytes")

    tmp = ROOT / "build"
    tmp.mkdir(exist_ok=True)
    src = tmp / "_trak_chunk.bin"
    src.write_bytes(chunk)
    dump = tmp / "_trak_dump.txt"

    proc = subprocess.run([str(tmp / "drive_trak.exe"), str(src), str(dump)],
                          capture_output=True, text=True, cwd=str(ROOT))
    print((proc.stdout or proc.stderr).strip())
    if not dump.exists():
        print("the driver produced no dump")
        return 1

    header, got_records, got_materials = parse_dump(dump)
    exp_records, exp_materials = expected(chunk)

    print(f"records   : driver={len(got_records)} expected={len(exp_records)}")
    print(f"triangles : driver={len(got_materials)} expected={len(exp_materials)}")
    if header:
        print(f"headers_off={header.get('headers_off', -1):#x} "
              f"cursor_end={header.get('cursor_end', -1):#x}")

    bad_records = 0
    for i, (g, e) in enumerate(zip(got_records, exp_records)):
        diffs = [k for k in ("vc", "tc", "coll", "vtx", "tri", "col") if g[k] != e[k]]
        if diffs:
            bad_records += 1
            if bad_records <= 5:
                print(f"  REC {i}: differs in {','.join(diffs)}")
                for k in diffs:
                    print(f"      {k}: driver={g[k]} expected={e[k]}")

    bad_tri = 0
    for (gi, gj, gidx), (ei, ej, eidx) in zip(got_materials, exp_materials):
        if (gi, gj) != (ei, ej) or gidx != eidx:
            bad_tri += 1
            if bad_tri <= 5:
                print(f"  TRI {gi} {gj}: index driver={gidx} expected={eidx}")

    print()
    if not bad_records and not bad_tri:
        print(f"PASS: all {len(got_records)} records and {len(got_materials)} triangle "
              f"material indices match the independent model")
    else:
        print(f"FAIL: {bad_records} records and {bad_tri} triangle indices differ")
    return 1 if (bad_records or bad_tri) else 0


if __name__ == "__main__":
    raise SystemExit(main())
