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


def _fixed12(v: int) -> float:
    return v / 4096.0


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
    """One 90-byte Section 3 disk record, expanded by the game to 92 bytes."""

    index: int
    file_offset: int
    raw: bytes
    rt_00: int
    rt_04: int
    rt_08: int
    rt_0C: int
    rt_10: int
    rt_14: int
    rt_18: int
    rt_1C: int
    flags_20: int
    rt_24: int
    stpc_relative_ptr_28: int
    rt_2C: int
    rt_30: int
    rt_34: int
    rt_38_u16: int
    range_a_min_3C: int
    range_b_min_40: int
    range_a_max_44_raw: int
    range_b_max_48_raw: int
    rt_4C: int
    rt_50: int
    rt_54_u16: int
    rt_56_u16: int
    rt_58: int

    @property
    def sets_dword_584644(self) -> bool:
        return bool(self.flags_20 & 0x08)

    @property
    def stpc_ptr_expr(self) -> str:
        if self.stpc_relative_ptr_28 == 0:
            return "NULL"
        return f"STPC_base+0x{self.stpc_relative_ptr_28:08X}"

    @property
    def range_a_max_44_runtime(self) -> int:
        if self.range_a_max_44_raw <= self.range_a_min_3C:
            return self.range_a_min_3C + (self.range_a_min_3C >> 1)
        return self.range_a_max_44_raw

    @property
    def range_b_max_48_runtime(self) -> int:
        if self.range_a_max_44_raw <= self.range_a_min_3C:
            return self.range_b_min_40 + (self.range_b_min_40 >> 1)
        return self.range_b_max_48_raw

    @property
    def u32_values(self) -> list[int]:
        return [
            self.rt_00, self.rt_04, self.rt_08, self.rt_0C,
            self.rt_10, self.rt_14, self.rt_18, self.rt_1C,
            self.flags_20, self.rt_24, self.stpc_relative_ptr_28,
            self.rt_2C, self.rt_30, self.rt_34,
            self.range_a_min_3C, self.range_b_min_40,
            self.range_a_max_44_raw, self.range_b_max_48_raw,
            self.rt_4C, self.rt_50, self.rt_58,
        ]

    @property
    def u16_at_56(self) -> int:
        return self.rt_38_u16

    @property
    def u16_at_84(self) -> int:
        return self.rt_56_u16

    @property
    def u16_at_86(self) -> int:
        return self.rt_58 & 0xFFFF


@dataclass
class MapSection4Record:
    """One 34-byte Section 4 disk record, expanded by the game to 48 bytes."""

    index: int
    file_offset: int
    raw: bytes
    link_next_raw_00: int
    link_prev_raw_04: int
    rt_08_u16: int
    yaw_units_0C: int
    rt_10_u16: int
    route_x_18: int
    route_y_1C: int
    route_z_20: int
    rt_28: int
    rt_2C: int

    @property
    def link_next_flag(self) -> int:
        return self.link_next_raw_00

    @property
    def link_prev_file_value(self) -> int:
        return self.link_prev_raw_04

    @property
    def small_a(self) -> int:
        return self.rt_08_u16

    @property
    def small_b(self) -> int:
        return self.yaw_units_0C

    @property
    def small_c(self) -> int:
        return self.rt_10_u16

    @property
    def u32_24(self) -> int:
        return self.route_x_18

    @property
    def u32_28(self) -> int:
        return self.route_y_1C

    @property
    def u32_32(self) -> int:
        return self.route_z_20

    @property
    def u32_40(self) -> int:
        return self.rt_28

    @property
    def u32_44(self) -> int:
        return self.rt_2C


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
    """One packed 58-byte MAP object record as it appears on disk.

    sub_42AC50 expands this to a 72-byte runtime object record.  sub_54CFC0
    later converts that runtime record into SpawnParams + Transform32 and calls
    sub_54BFC0 to create an Actor340.  Field names below follow that proven
    path where possible.
    """

    index: int
    file_offset: int
    raw: bytes

    rot_x_units: int           # +0x00 u16, runtime u32; actor receives << 12
    rot_y_units: int           # +0x02 u16
    rot_z_units: int           # +0x04 u16

    pos_x_fixed12: int         # +0x06 s/u32, copied directly to Transform32
    pos_y_fixed12: int         # +0x0A
    pos_z_fixed12: int         # +0x0E

    script_offset: int         # +0x12, runtime pointer = CPTS base + offset
    local_count: int           # +0x16, Actor340 +0x100
    section2_index_raw: int    # +0x1A, sentinel => NULL, else section2 + 4*idx
    stack_word_count: int      # +0x1E, passed as sub_54BFC0 a4
    stack_arg_count: int       # +0x22, SpawnParams.initial_stack_count
    spawn_flags: int           # +0x26, Actor340 +0xEC and +0x138
    extra_count: int           # +0x2A, optional extra array count
    section4_index_raw: int    # +0x2E, sentinel => NULL, else section4 + 48*idx
    spawn_aux_raw: int         # +0x32, runtime +0x40; may become section4 tail ptr
    flags: int                 # +0x36 u16; bit 1 means skip initial spawn
    extra_u16: int             # +0x38 u16

    @property
    def skip_initial_spawn(self) -> bool:
        return bool(self.flags & 0x0002)

    @property
    def pos_x(self) -> float:
        return self.pos_x_fixed12 / 4096.0

    @property
    def pos_y(self) -> float:
        return self.pos_y_fixed12 / 4096.0

    @property
    def pos_z(self) -> float:
        return self.pos_z_fixed12 / 4096.0

    @property
    def actor_rot_x_fixed(self) -> int:
        return self.rot_x_units << 12

    @property
    def actor_rot_y_fixed(self) -> int:
        return self.rot_y_units << 12

    @property
    def actor_rot_z_fixed(self) -> int:
        return self.rot_z_units << 12

    # Backward-compatible aliases used by older world_rebuild.py paths.
    @property
    def small_00(self) -> int:
        return self.rot_x_units

    @property
    def small_04(self) -> int:
        return self.rot_y_units

    @property
    def small_08(self) -> int:
        return self.rot_z_units

    @property
    def u32_16(self) -> int:
        return self.pos_x_fixed12 & 0xFFFFFFFF

    @property
    def u32_20(self) -> int:
        return self.pos_y_fixed12 & 0xFFFFFFFF

    @property
    def u32_24(self) -> int:
        return self.pos_z_fixed12 & 0xFFFFFFFF

    @property
    def name_or_string_offset(self) -> int:
        return self.script_offset

    @property
    def u32_36(self) -> int:
        return self.local_count

    @property
    def section2_index_or_sentinel(self) -> int:
        return self.section2_index_raw

    @property
    def u32_44(self) -> int:
        return self.stack_word_count

    @property
    def u32_48(self) -> int:
        return self.stack_arg_count

    @property
    def u32_52(self) -> int:
        return self.spawn_flags

    @property
    def u32_56(self) -> int:
        return self.extra_count

    @property
    def section4_index_or_sentinel(self) -> int:
        return self.section4_index_raw

    @property
    def u32_64(self) -> int:
        return self.spawn_aux_raw

    @property
    def u16_68(self) -> int:
        return self.flags

    @property
    def u16_70(self) -> int:
        return self.extra_u16


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
        section3.append(MapSection3Record(
            index=i,
            file_offset=off,
            raw=raw,
            rt_00=struct.unpack_from("<I", raw, 0)[0],
            rt_04=struct.unpack_from("<I", raw, 4)[0],
            rt_08=struct.unpack_from("<I", raw, 8)[0],
            rt_0C=struct.unpack_from("<I", raw, 12)[0],
            rt_10=struct.unpack_from("<I", raw, 16)[0],
            rt_14=struct.unpack_from("<I", raw, 20)[0],
            rt_18=struct.unpack_from("<I", raw, 24)[0],
            rt_1C=struct.unpack_from("<I", raw, 28)[0],
            flags_20=struct.unpack_from("<I", raw, 32)[0],
            rt_24=struct.unpack_from("<I", raw, 36)[0],
            stpc_relative_ptr_28=struct.unpack_from("<I", raw, 40)[0],
            rt_2C=struct.unpack_from("<I", raw, 44)[0],
            rt_30=struct.unpack_from("<I", raw, 48)[0],
            rt_34=struct.unpack_from("<I", raw, 52)[0],
            rt_38_u16=struct.unpack_from("<H", raw, 56)[0],
            range_a_min_3C=struct.unpack_from("<I", raw, 58)[0],
            range_b_min_40=struct.unpack_from("<I", raw, 62)[0],
            range_a_max_44_raw=struct.unpack_from("<I", raw, 66)[0],
            range_b_max_48_raw=struct.unpack_from("<I", raw, 70)[0],
            rt_4C=struct.unpack_from("<I", raw, 74)[0],
            rt_50=struct.unpack_from("<I", raw, 78)[0],
            rt_54_u16=struct.unpack_from("<H", raw, 82)[0],
            rt_56_u16=struct.unpack_from("<H", raw, 84)[0],
            rt_58=struct.unpack_from("<I", raw, 86)[0],
        ))

    section4_count = cur.u32()
    section4: list[MapSection4Record] = []
    for i in range(section4_count):
        off = cur.tell()
        raw = cur.read(34)
        section4.append(MapSection4Record(
            index=i,
            file_offset=off,
            raw=raw,
            link_next_raw_00=struct.unpack_from("<I", raw, 0)[0],
            link_prev_raw_04=struct.unpack_from("<I", raw, 4)[0],
            rt_08_u16=struct.unpack_from("<H", raw, 8)[0],
            yaw_units_0C=struct.unpack_from("<H", raw, 10)[0],
            rt_10_u16=struct.unpack_from("<H", raw, 12)[0],
            route_x_18=struct.unpack_from("<I", raw, 14)[0],
            route_y_1C=struct.unpack_from("<I", raw, 18)[0],
            route_z_20=struct.unpack_from("<I", raw, 22)[0],
            rt_28=struct.unpack_from("<I", raw, 26)[0],
            rt_2C=struct.unpack_from("<I", raw, 30)[0],
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
            rot_x_units=struct.unpack_from("<H", raw, 0)[0],
            rot_y_units=struct.unpack_from("<H", raw, 2)[0],
            rot_z_units=struct.unpack_from("<H", raw, 4)[0],
            pos_x_fixed12=struct.unpack_from("<i", raw, 6)[0],
            pos_y_fixed12=struct.unpack_from("<i", raw, 10)[0],
            pos_z_fixed12=struct.unpack_from("<i", raw, 14)[0],
            script_offset=struct.unpack_from("<I", raw, 18)[0],
            local_count=struct.unpack_from("<I", raw, 22)[0],
            section2_index_raw=struct.unpack_from("<I", raw, 26)[0],
            stack_word_count=struct.unpack_from("<I", raw, 30)[0],
            stack_arg_count=struct.unpack_from("<I", raw, 34)[0],
            spawn_flags=struct.unpack_from("<I", raw, 38)[0],
            extra_count=struct.unpack_from("<I", raw, 42)[0],
            section4_index_raw=struct.unpack_from("<I", raw, 46)[0],
            spawn_aux_raw=struct.unpack_from("<I", raw, 50)[0],
            flags=struct.unpack_from("<H", raw, 54)[0],
            extra_u16=struct.unpack_from("<H", raw, 56)[0],
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
        "section3_global_record_count": sum(1 for r in parsed.section3 if r.sets_dword_584644),
        "section4_count": len(parsed.section4),
        "section5_count": len(parsed.section5),
        "tile_def_count": len(parsed.tile_defs),
        "tile_trak_index_count": len(parsed.tile_trak_indices),
        "optional20_count": len(parsed.optional20),
        "color_block_count": len(parsed.colors),
        "color_total_bytes": sum(c.byte_size + c.extra_byte_size for c in parsed.colors),
        "object_count": len(parsed.objects),
        "object_skip_initial_spawn_count": sum(1 for o in parsed.objects if o.skip_initial_spawn),
        "object_initial_spawn_count": sum(1 for o in parsed.objects if not o.skip_initial_spawn),
        "object_count_unknown_b": parsed.object_count_unknown_b,
        "final_optional_dword": parsed.final_optional_dword,
        "final_u16": parsed.final_u16,
        "warnings": parsed.warnings,
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    _write_csv(out_dir / "tiles_24.csv", ["index","file_offset","x","y","z","unk_float","flags_or_id","nonzero_marker"], (t.__dict__ for t in parsed.tiles))
    _write_csv(out_dir / "section2_u32.csv", ["index","value","value_hex"], ({"index":i,"value":v,"value_hex":f"0x{v:08X}"} for i,v in enumerate(parsed.section2)))
    section3_fields = [
        "index","file_offset","raw_hex",
        "rt_00","rt_04","rt_08","rt_0C","rt_10","rt_14","rt_18","rt_1C",
        "flags_20","flags_20_hex","sets_dword_584644","rt_24",
        "stpc_relative_ptr_28","stpc_relative_ptr_28_hex","stpc_ptr_expr",
        "rt_2C","rt_30","rt_34","rt_38_u16",
        "range_a_min_3C","range_a_min_3C_fixed12",
        "range_b_min_40","range_b_min_40_fixed12",
        "range_a_max_44_raw","range_a_max_44_raw_fixed12",
        "range_b_max_48_raw","range_b_max_48_raw_fixed12",
        "range_a_max_44_runtime","range_a_max_44_runtime_fixed12",
        "range_b_max_48_runtime","range_b_max_48_runtime_fixed12",
        "rt_4C","rt_50","rt_54_u16","rt_56_u16","rt_58","rt_58_hex",
        "u32_values",
    ]
    _write_csv(out_dir / "section3_records_90.csv", section3_fields, (
        {
            "index": r.index,
            "file_offset": r.file_offset,
            "raw_hex": _hex(r.raw),
            "rt_00": r.rt_00,
            "rt_04": r.rt_04,
            "rt_08": r.rt_08,
            "rt_0C": r.rt_0C,
            "rt_10": r.rt_10,
            "rt_14": r.rt_14,
            "rt_18": r.rt_18,
            "rt_1C": r.rt_1C,
            "flags_20": r.flags_20,
            "flags_20_hex": f"0x{r.flags_20:08X}",
            "sets_dword_584644": r.sets_dword_584644,
            "rt_24": r.rt_24,
            "stpc_relative_ptr_28": r.stpc_relative_ptr_28,
            "stpc_relative_ptr_28_hex": f"0x{r.stpc_relative_ptr_28:08X}",
            "stpc_ptr_expr": r.stpc_ptr_expr,
            "rt_2C": r.rt_2C,
            "rt_30": r.rt_30,
            "rt_34": r.rt_34,
            "rt_38_u16": r.rt_38_u16,
            "range_a_min_3C": r.range_a_min_3C,
            "range_a_min_3C_fixed12": _fixed12(r.range_a_min_3C),
            "range_b_min_40": r.range_b_min_40,
            "range_b_min_40_fixed12": _fixed12(r.range_b_min_40),
            "range_a_max_44_raw": r.range_a_max_44_raw,
            "range_a_max_44_raw_fixed12": _fixed12(r.range_a_max_44_raw),
            "range_b_max_48_raw": r.range_b_max_48_raw,
            "range_b_max_48_raw_fixed12": _fixed12(r.range_b_max_48_raw),
            "range_a_max_44_runtime": r.range_a_max_44_runtime,
            "range_a_max_44_runtime_fixed12": _fixed12(r.range_a_max_44_runtime),
            "range_b_max_48_runtime": r.range_b_max_48_runtime,
            "range_b_max_48_runtime_fixed12": _fixed12(r.range_b_max_48_runtime),
            "rt_4C": r.rt_4C,
            "rt_50": r.rt_50,
            "rt_54_u16": r.rt_54_u16,
            "rt_56_u16": r.rt_56_u16,
            "rt_58": r.rt_58,
            "rt_58_hex": f"0x{r.rt_58:08X}",
            "u32_values": " ".join(str(v) for v in r.u32_values),
        } for r in parsed.section3
    ))
    section4_fields = [
        "index","file_offset","raw_hex",
        "link_next_raw_00","link_prev_raw_04","rt_08_u16","yaw_units_0C","rt_10_u16",
        "route_x_18","route_x_18_fixed12","route_y_1C","route_y_1C_fixed12",
        "route_z_20","route_z_20_fixed12","rt_28","rt_2C",
        "link_next_flag","link_prev_file_value","small_a","small_b","small_c",
        "u32_24","u32_28","u32_32","u32_40","u32_44",
    ]
    _write_csv(out_dir / "section4_records_34.csv", section4_fields, (
        {
            "index": r.index,
            "file_offset": r.file_offset,
            "raw_hex": _hex(r.raw),
            "link_next_raw_00": r.link_next_raw_00,
            "link_prev_raw_04": r.link_prev_raw_04,
            "rt_08_u16": r.rt_08_u16,
            "yaw_units_0C": r.yaw_units_0C,
            "rt_10_u16": r.rt_10_u16,
            "route_x_18": r.route_x_18,
            "route_x_18_fixed12": _fixed12(r.route_x_18),
            "route_y_1C": r.route_y_1C,
            "route_y_1C_fixed12": _fixed12(r.route_y_1C),
            "route_z_20": r.route_z_20,
            "route_z_20_fixed12": _fixed12(r.route_z_20),
            "rt_28": r.rt_28,
            "rt_2C": r.rt_2C,
            "link_next_flag": r.link_next_flag,
            "link_prev_file_value": r.link_prev_file_value,
            "small_a": r.small_a,
            "small_b": r.small_b,
            "small_c": r.small_c,
            "u32_24": r.u32_24,
            "u32_28": r.u32_28,
            "u32_32": r.u32_32,
            "u32_40": r.u32_40,
            "u32_44": r.u32_44,
        } for r in parsed.section4
    ))
    _write_csv(out_dir / "section5_32x8.csv", ["index","u32_00","u32_04"], ({"index":i,"u32_00":a,"u32_04":b} for i,a,b in parsed.section5))
    _write_csv(out_dir / "grid_u32.csv", ["cell_index","x","y","value","value_hex"], (
        {"cell_index":i,"x":i % parsed.grid_width,"y":i // parsed.grid_width,"value":v,"value_hex":f"0x{v:08X}"} for i,v in enumerate(parsed.grid)
    ))
    _write_csv(out_dir / "tile_defs_24.csv", ["index","file_offset","u32_00","u32_04","u32_08","u32_16","u32_20","u32_24"], (td.__dict__ for td in parsed.tile_defs))
    _write_csv(out_dir / "tile_trak_record_indices.csv", ["tile_index","trak_record_index"], ({"tile_index":i,"trak_record_index":v} for i,v in enumerate(parsed.tile_trak_indices)))
    _write_csv(out_dir / "optional20_records.csv", ["index","file_offset","u32_00","u32_04","u32_08","u32_12","trak_record_index_16","block_tile_index"], (r.__dict__ for r in parsed.optional20))
    _write_csv(out_dir / "vertex_color_blocks.csv", ["tile_index","trak_record_index","vertex_count","color_offset","layer_count","byte_size","max_alpha_first_layer","extra_trak_record_index","extra_vertex_count","extra_color_offset","extra_layer_count","extra_byte_size"], (c.__dict__ for c in parsed.colors))
    object_fields = [
        "index","file_offset","raw_hex",
        "rot_x_units","rot_y_units","rot_z_units",
        "actor_rot_x_fixed","actor_rot_y_fixed","actor_rot_z_fixed",
        "pos_x_fixed12","pos_y_fixed12","pos_z_fixed12","pos_x","pos_y","pos_z",
        "script_offset","script_offset_hex",
        "local_count","section2_index_raw","section2_valid",
        "stack_word_count","stack_arg_count","spawn_flags","spawn_flags_hex","extra_count",
        "section4_index_raw","section4_valid","spawn_aux_raw","spawn_aux_raw_hex",
        "flags","flags_hex","skip_initial_spawn","extra_u16",
    ]
    _write_csv(out_dir / "objects_58_disk.csv", object_fields, (
        {
            "index": o.index,
            "file_offset": o.file_offset,
            "raw_hex": _hex(o.raw),
            "rot_x_units": o.rot_x_units,
            "rot_y_units": o.rot_y_units,
            "rot_z_units": o.rot_z_units,
            "actor_rot_x_fixed": o.actor_rot_x_fixed,
            "actor_rot_y_fixed": o.actor_rot_y_fixed,
            "actor_rot_z_fixed": o.actor_rot_z_fixed,
            "pos_x_fixed12": o.pos_x_fixed12,
            "pos_y_fixed12": o.pos_y_fixed12,
            "pos_z_fixed12": o.pos_z_fixed12,
            "pos_x": f"{o.pos_x:.9g}",
            "pos_y": f"{o.pos_y:.9g}",
            "pos_z": f"{o.pos_z:.9g}",
            "script_offset": o.script_offset,
            "script_offset_hex": f"0x{o.script_offset:08X}",
            "local_count": o.local_count,
            "section2_index_raw": o.section2_index_raw,
            "section2_valid": 0 <= o.section2_index_raw < len(parsed.section2),
            "stack_word_count": o.stack_word_count,
            "stack_arg_count": o.stack_arg_count,
            "spawn_flags": o.spawn_flags,
            "spawn_flags_hex": f"0x{o.spawn_flags:08X}",
            "extra_count": o.extra_count,
            "section4_index_raw": o.section4_index_raw,
            "section4_valid": 0 <= o.section4_index_raw < len(parsed.section4),
            "spawn_aux_raw": o.spawn_aux_raw,
            "spawn_aux_raw_hex": f"0x{o.spawn_aux_raw:08X}",
            "flags": o.flags,
            "flags_hex": f"0x{o.flags:04X}",
            "skip_initial_spawn": o.skip_initial_spawn,
            "extra_u16": o.extra_u16,
        } for o in parsed.objects
    ))

    # Backward-compatible alias for older scripts.
    try:
        import shutil
        shutil.copyfile(out_dir / "objects_58_disk.csv", out_dir / "objects_58.csv")
    except Exception:
        pass

    _write_csv(out_dir / "objects_72_runtime.csv", [
        "index", "runtime_stride", "rt_00_rot_x_units", "rt_04_rot_y_units", "rt_08_rot_z_units",
        "rt_0C_unwritten", "rt_10_pos_x_fixed12", "rt_14_pos_y_fixed12", "rt_18_pos_z_fixed12",
        "rt_1C_unwritten", "rt_20_script_ptr_expr", "rt_24_local_count",
        "rt_28_section2_ptr_expr", "rt_2C_stack_word_count", "rt_30_stack_arg_count",
        "rt_34_spawn_flags", "rt_38_extra_count", "rt_3C_section4_ptr_expr",
        "rt_40_spawn_aux_or_section4_tail", "rt_44_flags", "rt_46_extra_u16",
    ], (
        {
            "index": o.index,
            "runtime_stride": 72,
            "rt_00_rot_x_units": o.rot_x_units,
            "rt_04_rot_y_units": o.rot_y_units,
            "rt_08_rot_z_units": o.rot_z_units,
            "rt_0C_unwritten": 0,
            "rt_10_pos_x_fixed12": o.pos_x_fixed12,
            "rt_14_pos_y_fixed12": o.pos_y_fixed12,
            "rt_18_pos_z_fixed12": o.pos_z_fixed12,
            "rt_1C_unwritten": 0,
            "rt_20_script_ptr_expr": f"CPTS_base+0x{o.script_offset:X}",
            "rt_24_local_count": o.local_count,
            "rt_28_section2_ptr_expr": (f"section2+4*{o.section2_index_raw}" if 0 <= o.section2_index_raw < len(parsed.section2) else "NULL/sentinel"),
            "rt_2C_stack_word_count": o.stack_word_count,
            "rt_30_stack_arg_count": o.stack_arg_count,
            "rt_34_spawn_flags": f"0x{o.spawn_flags:08X}",
            "rt_38_extra_count": o.extra_count,
            "rt_3C_section4_ptr_expr": (f"section4+48*{o.section4_index_raw}" if 0 <= o.section4_index_raw < len(parsed.section4) else "NULL/sentinel"),
            "rt_40_spawn_aux_or_section4_tail": f"0x{o.spawn_aux_raw:08X}",
            "rt_44_flags": f"0x{o.flags:04X}",
            "rt_46_extra_u16": o.extra_u16,
        } for o in parsed.objects
    ))

    _write_csv(out_dir / "actors_spawn_preview.csv", [
        "object_index", "spawns_initially", "actor_script_pc", "actor_rot_x", "actor_rot_y", "actor_rot_z",
        "actor_pos_x_fixed12", "actor_pos_y_fixed12", "actor_pos_z_fixed12", "actor_pos_x", "actor_pos_y", "actor_pos_z",
        "actor_spawn_flags", "actor_local_count", "actor_stack_word_count", "actor_stack_arg_count", "actor_extra_count", "actor_spawn_aux",
    ], (
        {
            "object_index": o.index,
            "spawns_initially": not o.skip_initial_spawn,
            "actor_script_pc": f"CPTS_base+0x{o.script_offset:X}",
            "actor_rot_x": o.actor_rot_x_fixed,
            "actor_rot_y": o.actor_rot_y_fixed,
            "actor_rot_z": o.actor_rot_z_fixed,
            "actor_pos_x_fixed12": o.pos_x_fixed12,
            "actor_pos_y_fixed12": o.pos_y_fixed12,
            "actor_pos_z_fixed12": o.pos_z_fixed12,
            "actor_pos_x": f"{o.pos_x:.9g}",
            "actor_pos_y": f"{o.pos_y:.9g}",
            "actor_pos_z": f"{o.pos_z:.9g}",
            "actor_spawn_flags": f"0x{o.spawn_flags:08X}",
            "actor_local_count": o.local_count,
            "actor_stack_word_count": o.stack_word_count,
            "actor_stack_arg_count": o.stack_arg_count,
            "actor_extra_count": o.extra_count,
            "actor_spawn_aux": f"0x{o.spawn_aux_raw:08X}",
        } for o in parsed.objects
    ))

    # Confirmed fixed-point object position marker file. Runtime Z mirroring is
    # handled by higher-level world export; this diagnostic keeps MAP coordinates.
    with (out_dir / "object_spawn_points.obj").open("w", encoding="utf-8") as f:
        f.write("# MAP object spawn positions from MapObjectDisk58 / sub_42AC50 -> sub_54CFC0.\n")
        f.write("# Position units are fixed12 divided by 4096. Objects with flags&2 are marked skip_initial_spawn in CSV.\n")
        vi = 1
        for o in parsed.objects:
            x, y, z = o.pos_x, o.pos_y, o.pos_z
            s = 0.75
            f.write(f"o map_object_{o.index:03d}{'_skip' if o.skip_initial_spawn else ''}\n")
            f.write(f"v {x-s:.9g} {y:.9g} {z:.9g}\n")
            f.write(f"v {x+s:.9g} {y:.9g} {z:.9g}\n")
            f.write(f"v {x:.9g} {y-s:.9g} {z:.9g}\n")
            f.write(f"v {x:.9g} {y+s:.9g} {z:.9g}\n")
            f.write(f"v {x:.9g} {y:.9g} {z-s:.9g}\n")
            f.write(f"v {x:.9g} {y:.9g} {z+s:.9g}\n")
            f.write(f"l {vi} {vi+1}\n")
            f.write(f"l {vi+2} {vi+3}\n")
            f.write(f"l {vi+4} {vi+5}\n")
            vi += 6


