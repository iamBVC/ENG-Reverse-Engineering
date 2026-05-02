"""
map_full_chunk.py — executable-confirmed MAP chunk parser/exporter.

This module parses the MAP chunk using the layout revealed by the game's
loader function `sub_42AC50`.

Why this exists separately from map_chunk.py
-------------------------------------------
The older `map_chunk.py` was a safe, exploratory parser written before the
loader was known.  It could recover the tile list and grid, but it treated some
runtime-expanded structures as if they were stored with the same stride on disk.
The executable shows that several MAP records are expanded when loaded:

    section3: 90 bytes on disk -> 92 bytes at runtime
    section4: 34 bytes on disk -> 48 bytes at runtime
    tile defs: 24 bytes on disk -> 32 bytes at runtime
    object records: 58 bytes on disk -> 72 bytes at runtime

The parser below follows the file reads in sub_42AC50 and exports everything in
CSV form, including the important MAP tile -> TRAK record mapping and the
per-TRAK-vertex color/light data embedded in MAP.

Important terminology
---------------------
The names Section3/Section4/etc. are intentionally conservative.  The loader
confirms their byte layout and relationships, but not all field meanings are
known yet.  Comments mark which fields are confirmed and which are hypotheses.
"""

from __future__ import annotations

import csv
import json
import math
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from .binary import u16, u32
from .trak_chunk import TrakFile


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _f32(buf: bytes, off: int) -> float:
    return struct.unpack_from("<f", buf, off)[0]


def _hex(buf: bytes) -> str:
    return buf.hex(" ")


def _safe_float(v: int) -> float:
    return struct.unpack("<f", struct.pack("<I", v & 0xFFFFFFFF))[0]


def _write_csv(path: Path, fieldnames: list[str], rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            w.writerow(row)


class Cursor:
    """Tiny bounds-checked little-endian file cursor."""

    def __init__(self, data: bytes):
        self.data = data
        self.off = 0

    def tell(self) -> int:
        return self.off

    def remaining(self) -> int:
        return len(self.data) - self.off

    def read(self, n: int) -> bytes:
        if self.off + n > len(self.data):
            raise ValueError(f"MAP read past end: off={self.off}, need={n}, size={len(self.data)}")
        out = self.data[self.off:self.off + n]
        self.off += n
        return out

    def u16(self) -> int:
        out = u16(self.data, self.off)
        self.off += 2
        return out

    def u32(self) -> int:
        out = u32(self.data, self.off)
        self.off += 4
        return out

    def f32(self) -> float:
        out = _f32(self.data, self.off)
        self.off += 4
        return out


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------


@dataclass
class MapTileExe:
    """One 24-byte tile record from the start of MAP."""

    index: int
    file_offset: int
    x: float
    y: float
    z: float
    unk_float: float
    flags_or_id: int
    nonzero_marker: int


@dataclass
class MapSection3Record:
    index: int
    file_offset: int
    raw: bytes
    u32_values: list[int]
    u16_at_56: int
    u16_at_84: int
    u16_at_86: int


@dataclass
class MapSection4Record:
    """One 34-byte Section 4 disk record, expanded by the game to 48 bytes."""

    index: int
    file_offset: int
    raw: bytes
    link_next_flag: int
    link_prev_file_value: int
    small_a: int
    small_b: int
    small_c: int
    u32_24: int
    u32_28: int
    u32_32: int
    u32_40: int
    u32_44: int


@dataclass
class MapTileDefExe:
    """One 24-byte tile definition record, expanded by the game to 32 bytes."""

    index: int
    file_offset: int
    u32_00: int
    u32_04: int
    u32_08: int
    u32_16: int
    u32_20: int
    u32_24: int


@dataclass
class MapOptionalRecord20:
    """
    Optional 20-byte-on-disk table loaded when dword_6DA330 & 0x10000 is set.

    The loader stores a runtime pointer at +20 using the temporary Block list
    created from tile records whose `nonzero_marker` is nonzero.  In file form
    we only have the first five u32 values; the exporter adds block_tile_index.
    """

    index: int
    file_offset: int
    u32_00: int
    u32_04: int
    u32_08: int
    u32_12: int
    trak_record_index_16: int
    block_tile_index: int | None


@dataclass
class MapColorBlock:
    """
    Per-tile color/light data.

    The loader reads one RGBA byte per TRAK Table A vertex for the tile's mapped
    TRAK record.  If the maximum alpha byte is greater than one, it reads extra
    color layers.  These bytes are transformed for rendering at runtime, but the
    CSV keeps the original file bytes.
    """

    tile_index: int
    trak_record_index: int
    vertex_count: int
    color_offset: int
    layer_count: int
    byte_size: int
    max_alpha_first_layer: int
    extra_trak_record_index: int | None
    extra_vertex_count: int
    extra_color_offset: int | None
    extra_layer_count: int
    extra_byte_size: int


@dataclass
class MapObjectRecord:
    """
    One 58-byte object/logic-like record near the end of MAP.

    The executable expands this to 72 bytes and fixes up two fields into
    pointers: one into Section2 and one into Section4.  This is likely a real
    gameplay/logic/entity table, but the field meanings are still not fully
    decoded.
    """

    index: int
    file_offset: int
    raw: bytes
    small_00: int
    small_04: int
    small_08: int
    u32_16: int
    u32_20: int
    u32_24: int
    name_or_string_offset: int
    u32_36: int
    section2_index_or_sentinel: int
    u32_44: int
    u32_48: int
    u32_52: int
    u32_56: int
    section4_index_or_sentinel: int
    u32_64: int
    u16_68: int
    u16_70: int


@dataclass
class MapFullExe:
    source_size: int
    parsed_size: int
    tile_count: int
    grid_width: int
    grid_height: int
    tiles: list[MapTileExe]
    block_tile_indices: list[int]
    section2: list[int]
    section3: list[MapSection3Record]
    section4: list[MapSection4Record]
    section5: list[tuple[int, int, int]]
    grid: list[int]
    tile_defs: list[MapTileDefExe]
    tile_trak_indices: list[int]
    optional20: list[MapOptionalRecord20]
    colors: list[MapColorBlock]
    object_count_unknown_b: int
    objects: list[MapObjectRecord]
    final_optional_dword: int | None
    final_u16: int
    warnings: list[str]


# ---------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------


def _read_color_layers(cur: Cursor, vertex_count: int) -> tuple[int, int, int, int]:
    """Read the MAP color layers for a TRAK vertex list and return stats."""
    if vertex_count <= 0:
        return cur.tell(), 0, 0, 0
    start = cur.tell()
    first = cur.read(4 * vertex_count)
    max_alpha = max(first[3::4]) if first else 0
    layers = max(1, max_alpha)
    if max_alpha > 1:
        cur.read(4 * vertex_count * (max_alpha - 1))
    return start, layers, cur.tell() - start, max_alpha


def parse_map_full_exe(map_data: bytes, trak: TrakFile, *, assume_optional20: bool = True, assume_final_dword: bool = True) -> MapFullExe:
    """
    Parse a MAP chunk using sub_42AC50's confirmed read order.

    For the currently tested PC WADs, the optional 20-byte table and final
    optional dword are present.  These correspond to flags tested in the loader:

        dword_6DA330 & 0x10000   -> optional 20-byte records are present
        dword_6DA330 & 0x10      -> final dword before the final u16 is present

    The options are exposed so the parser can still be used for older or variant
    files if a future WAD omits either table.
    """
    cur = Cursor(map_data)
    warnings: list[str] = []

    tile_count = cur.u32()
    grid_width = cur.u32()
    grid_height = cur.u32()

    tiles: list[MapTileExe] = []
    block_tile_indices: list[int] = []
    for i in range(tile_count):
        off = cur.tell()
        raw = cur.read(24)
        x, y, z, unk = struct.unpack_from("<4f", raw, 0)
        flags_or_id, nonzero_marker = struct.unpack_from("<2I", raw, 16)
        tiles.append(MapTileExe(i, off, x, y, z, unk, flags_or_id, nonzero_marker))
        if nonzero_marker:
            block_tile_indices.append(i)

    section2_count = cur.u32()
    section2 = [cur.u32() for _ in range(section2_count)]

    section3_count = cur.u32()
    section3: list[MapSection3Record] = []
    for i in range(section3_count):
        off = cur.tell()
        raw = cur.read(90)
        # The record is not naturally aligned on disk. Export broad fields for analysis.
        vals = []
        for o in [0,4,8,12,16,20,24,28,32,36,40,44,48,52,58,62,66,70,74,78,86]:
            if o + 4 <= len(raw):
                vals.append(struct.unpack_from("<I", raw, o)[0])
        section3.append(MapSection3Record(i, off, raw, vals, struct.unpack_from("<H", raw, 56)[0], struct.unpack_from("<H", raw, 84)[0], struct.unpack_from("<H", raw, 86)[0]))

    section4_count = cur.u32()
    section4: list[MapSection4Record] = []
    for i in range(section4_count):
        off = cur.tell()
        raw = cur.read(34)
        section4.append(MapSection4Record(
            index=i,
            file_offset=off,
            raw=raw,
            link_next_flag=struct.unpack_from("<I", raw, 0)[0],
            link_prev_file_value=struct.unpack_from("<I", raw, 4)[0],
            small_a=struct.unpack_from("<H", raw, 8)[0],
            small_b=struct.unpack_from("<H", raw, 10)[0],
            small_c=struct.unpack_from("<H", raw, 12)[0],
            u32_24=struct.unpack_from("<I", raw, 14)[0],
            u32_28=struct.unpack_from("<I", raw, 18)[0],
            u32_32=struct.unpack_from("<I", raw, 22)[0],
            u32_40=struct.unpack_from("<I", raw, 26)[0],
            u32_44=struct.unpack_from("<I", raw, 30)[0],
        ))

    section5 = []
    for i in range(32):
        off = cur.tell()
        a = cur.u32()
        b = cur.u32()
        section5.append((i, a, b))

    grid = [cur.u32() for _ in range(grid_width * grid_height)]

    tile_defs: list[MapTileDefExe] = []
    for i in range(tile_count):
        off = cur.tell()
        vals = [cur.u32(), cur.u32(), cur.u32(), cur.u32(), cur.u32(), cur.u32()]
        tile_defs.append(MapTileDefExe(i, off, *vals))

    tile_trak_indices = [cur.u32() for _ in range(tile_count)]
    for i, idx in enumerate(tile_trak_indices):
        if idx >= trak.record_count:
            warnings.append(f"tile {i} references invalid TRAK record {idx}")

    optional20: list[MapOptionalRecord20] = []
    if assume_optional20:
        opt_count = cur.u32()
        if opt_count > tile_count * 4:
            raise ValueError(f"MAP optional20 count is implausible: {opt_count}")
        for i in range(opt_count):
            off = cur.tell()
            vals = [cur.u32(), cur.u32(), cur.u32(), cur.u32(), cur.u32()]
            block_tile = block_tile_indices[i] if i < len(block_tile_indices) else None
            optional20.append(MapOptionalRecord20(i, off, vals[0], vals[1], vals[2], vals[3], vals[4], block_tile))
            if vals[4] >= trak.record_count:
                warnings.append(f"optional20[{i}] references invalid TRAK record {vals[4]}")

    # Fast lookup used by the loader when it reads an extra color block for a tile.
    extra_trak_by_tile = {
        rec.block_tile_index: rec.trak_record_index_16
        for rec in optional20
        if rec.block_tile_index is not None and rec.trak_record_index_16 < trak.record_count
    }

    colors: list[MapColorBlock] = []
    for tile_i, trak_i in enumerate(tile_trak_indices):
        if trak_i >= trak.record_count:
            # Keep parser moving only when possible. Invalid indices are a hard error for colors.
            raise ValueError(f"cannot read colors: tile {tile_i} has invalid TRAK index {trak_i}")
        vertex_count = trak.records[trak_i].a_count
        color_offset, layers, byte_size, max_alpha = _read_color_layers(cur, vertex_count)

        extra_trak = extra_trak_by_tile.get(tile_i)
        extra_vc = 0
        extra_off = None
        extra_layers = 0
        extra_bytes = 0
        if extra_trak is not None:
            extra_vc = trak.records[extra_trak].a_count
            extra_off, extra_layers, extra_bytes, _extra_max = _read_color_layers(cur, extra_vc)

        colors.append(MapColorBlock(
            tile_index=tile_i,
            trak_record_index=trak_i,
            vertex_count=vertex_count,
            color_offset=color_offset,
            layer_count=layers,
            byte_size=byte_size,
            max_alpha_first_layer=max_alpha,
            extra_trak_record_index=extra_trak,
            extra_vertex_count=extra_vc,
            extra_color_offset=extra_off,
            extra_layer_count=extra_layers,
            extra_byte_size=extra_bytes,
        ))

    object_count = cur.u32()
    object_count_unknown_b = cur.u32()
    objects: list[MapObjectRecord] = []
    for i in range(object_count):
        off = cur.tell()
        raw = cur.read(58)
        objects.append(MapObjectRecord(
            index=i,
            file_offset=off,
            raw=raw,
            small_00=struct.unpack_from("<H", raw, 0)[0],
            small_04=struct.unpack_from("<H", raw, 2)[0],
            small_08=struct.unpack_from("<H", raw, 4)[0],
            u32_16=struct.unpack_from("<I", raw, 6)[0],
            u32_20=struct.unpack_from("<I", raw, 10)[0],
            u32_24=struct.unpack_from("<I", raw, 14)[0],
            name_or_string_offset=struct.unpack_from("<I", raw, 18)[0],
            u32_36=struct.unpack_from("<I", raw, 22)[0],
            section2_index_or_sentinel=struct.unpack_from("<I", raw, 26)[0],
            u32_44=struct.unpack_from("<I", raw, 30)[0],
            u32_48=struct.unpack_from("<I", raw, 34)[0],
            u32_52=struct.unpack_from("<I", raw, 38)[0],
            u32_56=struct.unpack_from("<I", raw, 42)[0],
            section4_index_or_sentinel=struct.unpack_from("<I", raw, 46)[0],
            u32_64=struct.unpack_from("<I", raw, 50)[0],
            u16_68=struct.unpack_from("<H", raw, 54)[0],
            u16_70=struct.unpack_from("<H", raw, 56)[0],
        ))

    # The first four tested PC levels have no optional 0x200000 chain table, but
    # they do have the final dword controlled by dword_6DA330 & 0x10.
    final_optional_dword = cur.u32() if assume_final_dword else None
    final_u16 = cur.u16()

    if cur.tell() != len(map_data):
        warnings.append(f"parser ended at 0x{cur.tell():X}; chunk size is 0x{len(map_data):X}; remaining={len(map_data)-cur.tell()}")

    return MapFullExe(
        source_size=len(map_data),
        parsed_size=cur.tell(),
        tile_count=tile_count,
        grid_width=grid_width,
        grid_height=grid_height,
        tiles=tiles,
        block_tile_indices=block_tile_indices,
        section2=section2,
        section3=section3,
        section4=section4,
        section5=section5,
        grid=grid,
        tile_defs=tile_defs,
        tile_trak_indices=tile_trak_indices,
        optional20=optional20,
        colors=colors,
        object_count_unknown_b=object_count_unknown_b,
        objects=objects,
        final_optional_dword=final_optional_dword,
        final_u16=final_u16,
        warnings=warnings,
    )


# ---------------------------------------------------------------------------
# Exporters
# ---------------------------------------------------------------------------


def export_map_full_exe(parsed: MapFullExe, out_dir: Path) -> None:
    """Write executable-confirmed MAP diagnostics into a dedicated folder."""
    out_dir.mkdir(parents=True, exist_ok=True)

    summary = {
        "source_size": parsed.source_size,
        "parsed_size": parsed.parsed_size,
        "parsed_all_bytes": parsed.source_size == parsed.parsed_size,
        "tile_count": parsed.tile_count,
        "grid_width": parsed.grid_width,
        "grid_height": parsed.grid_height,
        "section2_count": len(parsed.section2),
        "section3_count": len(parsed.section3),
        "section4_count": len(parsed.section4),
        "section5_count": len(parsed.section5),
        "tile_def_count": len(parsed.tile_defs),
        "tile_trak_index_count": len(parsed.tile_trak_indices),
        "optional20_count": len(parsed.optional20),
        "color_block_count": len(parsed.colors),
        "color_total_bytes": sum(c.byte_size + c.extra_byte_size for c in parsed.colors),
        "object_count": len(parsed.objects),
        "object_count_unknown_b": parsed.object_count_unknown_b,
        "final_optional_dword": parsed.final_optional_dword,
        "final_u16": parsed.final_u16,
        "warnings": parsed.warnings,
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    _write_csv(out_dir / "tiles_24.csv", ["index","file_offset","x","y","z","unk_float","flags_or_id","nonzero_marker"], (t.__dict__ for t in parsed.tiles))
    _write_csv(out_dir / "section2_u32.csv", ["index","value","value_hex"], ({"index":i,"value":v,"value_hex":f"0x{v:08X}"} for i,v in enumerate(parsed.section2)))
    _write_csv(out_dir / "section3_records_90.csv", ["index","file_offset","raw_hex","u32_values","u16_at_56","u16_at_84","u16_at_86"], (
        {"index":r.index,"file_offset":r.file_offset,"raw_hex":_hex(r.raw),"u32_values":" ".join(str(v) for v in r.u32_values),"u16_at_56":r.u16_at_56,"u16_at_84":r.u16_at_84,"u16_at_86":r.u16_at_86} for r in parsed.section3
    ))
    _write_csv(out_dir / "section4_records_34.csv", ["index","file_offset","raw_hex","link_next_flag","link_prev_file_value","small_a","small_b","small_c","u32_24","u32_28","u32_32","u32_40","u32_44"], (
        {"index":r.index,"file_offset":r.file_offset,"raw_hex":_hex(r.raw),"link_next_flag":r.link_next_flag,"link_prev_file_value":r.link_prev_file_value,"small_a":r.small_a,"small_b":r.small_b,"small_c":r.small_c,"u32_24":r.u32_24,"u32_28":r.u32_28,"u32_32":r.u32_32,"u32_40":r.u32_40,"u32_44":r.u32_44} for r in parsed.section4
    ))
    _write_csv(out_dir / "section5_32x8.csv", ["index","u32_00","u32_04"], ({"index":i,"u32_00":a,"u32_04":b} for i,a,b in parsed.section5))
    _write_csv(out_dir / "grid_u32.csv", ["cell_index","x","y","value","value_hex"], (
        {"cell_index":i,"x":i % parsed.grid_width,"y":i // parsed.grid_width,"value":v,"value_hex":f"0x{v:08X}"} for i,v in enumerate(parsed.grid)
    ))
    _write_csv(out_dir / "tile_defs_24.csv", ["index","file_offset","u32_00","u32_04","u32_08","u32_16","u32_20","u32_24"], (td.__dict__ for td in parsed.tile_defs))
    _write_csv(out_dir / "tile_trak_record_indices.csv", ["tile_index","trak_record_index"], ({"tile_index":i,"trak_record_index":v} for i,v in enumerate(parsed.tile_trak_indices)))
    _write_csv(out_dir / "optional20_records.csv", ["index","file_offset","u32_00","u32_04","u32_08","u32_12","trak_record_index_16","block_tile_index"], (r.__dict__ for r in parsed.optional20))
    _write_csv(out_dir / "vertex_color_blocks.csv", ["tile_index","trak_record_index","vertex_count","color_offset","layer_count","byte_size","max_alpha_first_layer","extra_trak_record_index","extra_vertex_count","extra_color_offset","extra_layer_count","extra_byte_size"], (c.__dict__ for c in parsed.colors))
    _write_csv(out_dir / "objects_58.csv", ["index","file_offset","raw_hex","small_00","small_04","small_08","u32_16","u32_20","u32_24","name_or_string_offset","u32_36","section2_index_or_sentinel","u32_44","u32_48","u32_52","u32_56","section4_index_or_sentinel","u32_64","u16_68","u16_70"], (
        {"index":o.index,"file_offset":o.file_offset,"raw_hex":_hex(o.raw),"small_00":o.small_00,"small_04":o.small_04,"small_08":o.small_08,"u32_16":o.u32_16,"u32_20":o.u32_20,"u32_24":o.u32_24,"name_or_string_offset":o.name_or_string_offset,"u32_36":o.u32_36,"section2_index_or_sentinel":o.section2_index_or_sentinel,"u32_44":o.u32_44,"u32_48":o.u32_48,"u32_52":o.u32_52,"u32_56":o.u32_56,"section4_index_or_sentinel":o.section4_index_or_sentinel,"u32_64":o.u32_64,"u16_68":o.u16_68,"u16_70":o.u16_70} for o in parsed.objects
    ))

    # Small OBJ marker file for object-like MAP records. Some fields may be fixed
    # point, indices, or flags; this file is only a visual diagnostic for fields
    # that look like plausible coordinates after reinterpretation.
    # We intentionally keep it conservative and do not claim these are instances.
    with (out_dir / "object_record_float_probe.obj").open("w", encoding="utf-8") as f:
        f.write("# Diagnostic only: each object record exports several u32 fields reinterpreted as float triplets when finite.\n")
        vi = 1
        for o in parsed.objects:
            vals = [o.u32_16, o.u32_20, o.u32_24, o.u32_44, o.u32_48, o.u32_52, o.u32_56]
            floats = [_safe_float(v) for v in vals]
            # Emit two candidate triplets if they look finite and not tiny denormals.
            for triplet_index, triplet in enumerate((floats[0:3], floats[3:6])):
                if all(math.isfinite(x) and abs(x) < 1_000_000 for x in triplet) and any(abs(x) > 0.001 for x in triplet):
                    x, y, z = triplet
                    s = 10.0
                    f.write(f"o object_{o.index:03d}_candidate_{triplet_index}\n")
                    f.write(f"v {x-s} {y} {z}\n")
                    f.write(f"v {x+s} {y} {z}\n")
                    f.write(f"v {x} {y-s} {z}\n")
                    f.write(f"v {x} {y+s} {z}\n")
                    f.write(f"v {x} {y} {z-s}\n")
                    f.write(f"v {x} {y} {z+s}\n")
                    f.write(f"l {vi} {vi+1}\n")
                    f.write(f"l {vi+2} {vi+3}\n")
                    f.write(f"l {vi+4} {vi+5}\n")
                    vi += 6


