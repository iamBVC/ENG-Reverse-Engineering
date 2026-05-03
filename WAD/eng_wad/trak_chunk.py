"""
TRAK chunk parser/exporter.

TRAK is a level chunk whose four-byte WAD tag is stored as KART on disk
because WAD chunk tags are byte-reversed.  The human-readable tag is TRAK.

This module is based on the executable routines that load and fix up TRAK:

    sub_42AAC0(FILE *Stream, int *ElementSize)
        - allocates and reads the whole TRAK chunk into memory
        - reads the first uint32 as record_count
        - calls sub_5563F0(&cursor, record_count, &dword_5846EC)

    sub_5563F0(int *cursor, int record_count, DWORD *out_records)
        - treats the first table as record_count records of 0x84 bytes
        - for every record, assigns three runtime pointers into following data:
              record + 0x70 = Table A pointer, count at +0x6C, stride 24
              record + 0x74 = Table B pointer, count at +0x6E, stride 28
              record + 0x80 = Table C/D/E pointer, counts at +0x78/+0x7A/+0x7C, stride 32
        - for every Table B entry, converts the 16-bit field at +0x08 into
          a runtime pointer:
              *(DWORD *)(entry + 0x08) = dword_581154 + 20 * old_u16_value

Confirmed packed file layout:

    struct TRAKFile {
        uint32 record_count;
        TRAKRecord records[record_count];       // 0x84 bytes each
        TableAEntry table_a_for_record_0[];     // count = rec.a_count, stride 24
        TableBEntry table_b_for_record_0[];     // count = rec.b_count, stride 28
        TableCDEEntry table_cde_for_record_0[]; // count = c+d+e, stride 32
        TableAEntry table_a_for_record_1[];
        TableBEntry table_b_for_record_1[];
        TableCDEEntry table_cde_for_record_1[];
        ...
    };

Current interpretation:

    TRAK is probably a spatial track/navigation/collision/render-support graph,
    not a cinematic camera spline. Each record describes a cell/sector volume.
    Table A and Table B form local triangle surfaces for that cell/sector:

        TableAEntry, 24 bytes:
            float x, y, z;      // point position
            float nx, ny, nz;   // normal

        TableBEntry, 28 bytes:
            uint16 flags;
            uint16 i0, i1, i2;              // indices into this record's Table A
            uint16 material_table_index;    // changed to runtime pointer by EXE
            uint16 unknown;
            float plane_nx, plane_ny, plane_nz, plane_d;

    Table C/D/E is confirmed as three adjacent 32-byte collision/contact
    polygon sublists.  The runtime normally scans the combined C+D+E array.
    Every entry is a compact plane plus 3 or 4 edge half-space tests:

        +0x00 u8  flags, bit0 selects triangle(3 edges)/quad(4 edges)
        +0x01 u8  surface/contact id; 17/18 are conditionally skipped, 30 is invalid/no contact
        +0x02 s8  plane normal/coefficient X, scaled by 32
        +0x03 s8  plane normal/coefficient Y/up, scaled by 32
        +0x04 s8  plane normal/coefficient Z, scaled by 32
        +0x06 s16 plane constant
        +0x08      3 or 4 x 6-byte edge equations
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path

from .binary import u16, u32

TRAK_RECORD_SIZE = 0x84
TRAK_TABLE_A_STRIDE = 24
TRAK_TABLE_B_STRIDE = 28
TRAK_TABLE_CDE_STRIDE = 32


# ---------------------------------------------------------------------------
# Decoded structures
# ---------------------------------------------------------------------------

@dataclass
class TrakTableAEntry:
    """One 24-byte Table A entry: position XYZ plus normal XYZ."""
    record: int
    index: int
    file_offset: int
    x: float
    y: float
    z: float
    nx: float
    ny: float
    nz: float


@dataclass
class TrakTableBEntry:
    """
    One 28-byte Table B entry.

    This has the same broad shape as STPC triangle records: three vertex
    indices, a material/surface index, an unknown u16, and a plane equation.
    The executable rewrites the material/surface index at runtime into a
    pointer to dword_581154 + 20 * material_index, so the file value exported
    here is the original compact u16 index.
    """
    record: int
    index: int
    file_offset: int
    flags: int
    i0: int
    i1: int
    i2: int
    material_index: int
    unknown: int
    plane_nx: float
    plane_ny: float
    plane_nz: float
    plane_d: float


@dataclass
class CollisionEdge6:
    """One 6-byte collision edge half-space equation inside a C/D/E entry."""
    x_q32: int
    y_q32: int
    z_q32: int
    unknown_03: int
    d: int


@dataclass
class TrakTableCDEEntry:
    """One decoded 32-byte collision/contact entry from the combined C/D/E table area."""
    record: int
    group: str
    group_index: int
    combined_index: int
    file_offset: int
    raw: bytes
    flags: int
    surface_id: int
    normal_x_q32: int
    normal_y_q32: int
    normal_z_q32: int
    unknown_05: int
    plane_d: int
    edge_count: int
    edges: list[CollisionEdge6]

    @property
    def is_quad(self) -> bool:
        return bool(self.flags & 1)

    @property
    def normal(self) -> tuple[float, float, float]:
        """Plane normal/coefficient components after the executable's q32 scale."""
        return (self.normal_x_q32 * 32.0, self.normal_y_q32 * 32.0, self.normal_z_q32 * 32.0)

    @property
    def surface_note(self) -> str:
        if self.surface_id in (17, 18):
            return "conditionally skipped surface id"
        if self.surface_id == 30:
            return "invalid/no-contact surface id"
        return ""


@dataclass
class TrakRecord:
    """
    One 0x84-byte TRAK main record.

    The first 108 bytes are now mostly identified from sub_402840:

        +0x00      unknown u32/f32 metadata
        +0x04/+08 unknown floats, not used by sub_402840
        +0x0C      eight vec3 culling/bounds points used for frustum tests

    The last 24 bytes contain counts plus runtime pointer fields.  In the packed
    file, the runtime pointer slots are normally zero or meaningless;
    sub_5563F0 overwrites them after loading.
    """
    index: int
    file_offset: int
    center: tuple[float, float, float]
    corners: list[tuple[float, float, float]]
    a_count: int
    b_count: int
    c_count: int
    d_count: int
    e_count: int
    runtime_ptr_a_file_value: int
    runtime_ptr_b_file_value: int
    runtime_ptr_cde_file_value: int
    pad_7e: int
    table_a_file_offset: int
    table_b_file_offset: int
    table_cde_file_offset: int
    table_a: list[TrakTableAEntry]
    table_b: list[TrakTableBEntry]
    table_cde: list[TrakTableCDEEntry]


@dataclass
class TrakFile:
    """Fully parsed TRAK chunk."""
    record_count: int
    records: list[TrakRecord]
    source_size: int
    parsed_size: int

    @property
    def total_a_entries(self) -> int:
        return sum(r.a_count for r in self.records)

    @property
    def total_b_entries(self) -> int:
        return sum(r.b_count for r in self.records)

    @property
    def total_c_entries(self) -> int:
        return sum(r.c_count for r in self.records)

    @property
    def total_d_entries(self) -> int:
        return sum(r.d_count for r in self.records)

    @property
    def total_e_entries(self) -> int:
        return sum(r.e_count for r in self.records)


@dataclass
class TrakExportResult:
    trak: TrakFile
    out_dir: Path


# ---------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------

def _vec3(buf: bytes, off: int) -> tuple[float, float, float]:
    return struct.unpack_from("<3f", buf, off)


def _s8(v: int) -> int:
    return v - 256 if v >= 128 else v


def _i16(buf: bytes, off: int) -> int:
    return struct.unpack_from("<h", buf, off)[0]


def _decode_collision_entry(raw: bytes) -> tuple[int, int, int, int, int, int, int, int, list[CollisionEdge6]]:
    """Decode one 32-byte C/D/E collision/contact entry.

    Confirmed by sub_4036D0/sub_403AD0/sub_4042F0/sub_4046E0.  The runtime
    treats the three C/D/E groups as one combined array for most collision
    tests.  flags bit0 changes the number of 6-byte edge equations from 3 to 4.
    """
    flags = raw[0]
    surface_id = raw[1]
    nx = _s8(raw[2])
    ny = _s8(raw[3])
    nz = _s8(raw[4])
    unknown_05 = _s8(raw[5])
    plane_d = struct.unpack_from("<h", raw, 6)[0]
    edge_count = 3 + (flags & 1)
    edges: list[CollisionEdge6] = []
    for i in range(edge_count):
        eo = 8 + i * 6
        edges.append(CollisionEdge6(
            x_q32=_s8(raw[eo + 0]),
            y_q32=_s8(raw[eo + 1]),
            z_q32=_s8(raw[eo + 2]),
            unknown_03=_s8(raw[eo + 3]),
            d=struct.unpack_from("<h", raw, eo + 4)[0],
        ))
    return flags, surface_id, nx, ny, nz, unknown_05, plane_d, edge_count, edges


def parse_trak_chunk(buf: bytes) -> TrakFile:
    """
    Parse a raw TRAK chunk according to sub_5563F0's confirmed layout.

    The parser consumes the file exactly the same way the game loader does:

        1. read uint32 record_count
        2. skip record_count * 0x84 bytes for the fixed record table
        3. for each record, assign Table A, Table B, and combined C/D/E slices
           from the variable data stream using the counts stored in that record

    If parsed_size == source_size, all bytes in the chunk have been accounted
    for structurally.  Table C/D/E field semantics are still unknown, but their
    offsets, sizes, and grouping are known.
    """
    if len(buf) < 4:
        raise ValueError("TRAK data is too small to contain a record count")

    record_count = u32(buf, 0)
    record_table_off = 4
    variable_off = record_table_off + record_count * TRAK_RECORD_SIZE

    if variable_off > len(buf):
        raise ValueError(
            f"TRAK record table overruns chunk: count={record_count}, "
            f"record_table_end={variable_off}, chunk_size={len(buf)}"
        )

    records: list[TrakRecord] = []
    cursor = variable_off

    for rec_index in range(record_count):
        rec_off = record_table_off + rec_index * TRAK_RECORD_SIZE

        center = _vec3(buf, rec_off + 0x00)
        corners = [_vec3(buf, rec_off + 0x0C + i * 12) for i in range(8)]

        a_count = u16(buf, rec_off + 0x6C)
        b_count = u16(buf, rec_off + 0x6E)
        ptr_a_file_value = u32(buf, rec_off + 0x70)
        ptr_b_file_value = u32(buf, rec_off + 0x74)
        c_count = u16(buf, rec_off + 0x78)
        d_count = u16(buf, rec_off + 0x7A)
        e_count = u16(buf, rec_off + 0x7C)
        pad_7e = u16(buf, rec_off + 0x7E)
        ptr_cde_file_value = u32(buf, rec_off + 0x80)

        table_a_off = cursor
        table_a_size = a_count * TRAK_TABLE_A_STRIDE
        cursor += table_a_size

        table_b_off = cursor
        table_b_size = b_count * TRAK_TABLE_B_STRIDE
        cursor += table_b_size

        table_cde_off = cursor
        cde_total = c_count + d_count + e_count
        table_cde_size = cde_total * TRAK_TABLE_CDE_STRIDE
        cursor += table_cde_size

        if cursor > len(buf):
            raise ValueError(
                f"TRAK variable tables overrun chunk while parsing record {rec_index}: "
                f"cursor={cursor}, chunk_size={len(buf)}"
            )

        table_a: list[TrakTableAEntry] = []
        for i in range(a_count):
            off = table_a_off + i * TRAK_TABLE_A_STRIDE
            x, y, z, nx, ny, nz = struct.unpack_from("<6f", buf, off)
            table_a.append(TrakTableAEntry(rec_index, i, off, x, y, z, nx, ny, nz))

        table_b: list[TrakTableBEntry] = []
        for i in range(b_count):
            off = table_b_off + i * TRAK_TABLE_B_STRIDE
            flags, i0, i1, i2, material_index, unknown = struct.unpack_from("<6H", buf, off)
            plane_nx, plane_ny, plane_nz, plane_d = struct.unpack_from("<4f", buf, off + 12)
            table_b.append(TrakTableBEntry(
                rec_index, i, off,
                flags, i0, i1, i2,
                material_index, unknown,
                plane_nx, plane_ny, plane_nz, plane_d,
            ))

        table_cde: list[TrakTableCDEEntry] = []
        combined_index = 0
        for group, group_count in (("C", c_count), ("D", d_count), ("E", e_count)):
            for group_index in range(group_count):
                off = table_cde_off + combined_index * TRAK_TABLE_CDE_STRIDE
                raw = buf[off:off + TRAK_TABLE_CDE_STRIDE]
                flags, surface_id, nx, ny, nz, unk05, plane_d, edge_count, edges = _decode_collision_entry(raw)
                table_cde.append(TrakTableCDEEntry(
                    rec_index, group, group_index, combined_index, off, raw,
                    flags, surface_id, nx, ny, nz, unk05, plane_d, edge_count, edges
                ))
                combined_index += 1

        records.append(TrakRecord(
            index=rec_index,
            file_offset=rec_off,
            center=center,
            corners=corners,
            a_count=a_count,
            b_count=b_count,
            c_count=c_count,
            d_count=d_count,
            e_count=e_count,
            runtime_ptr_a_file_value=ptr_a_file_value,
            runtime_ptr_b_file_value=ptr_b_file_value,
            runtime_ptr_cde_file_value=ptr_cde_file_value,
            pad_7e=pad_7e,
            table_a_file_offset=table_a_off,
            table_b_file_offset=table_b_off,
            table_cde_file_offset=table_cde_off,
            table_a=table_a,
            table_b=table_b,
            table_cde=table_cde,
        ))

    return TrakFile(
        record_count=record_count,
        records=records,
        source_size=len(buf),
        parsed_size=cursor,
    )


# ---------------------------------------------------------------------------
# CSV exports
# ---------------------------------------------------------------------------

def _record_bounds(record: TrakRecord) -> tuple[float, float, float, float, float, float]:
    pts = [record.center] + record.corners
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    zs = [p[2] for p in pts]
    return min(xs), min(ys), min(zs), max(xs), max(ys), max(zs)


def write_records_csv(trak: TrakFile, path: Path) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "record", "file_offset_hex", "center_x", "center_y", "center_z",
            "a_count_vertices", "b_count_triangles", "c_count", "d_count", "e_count",
            "table_a_off_hex", "table_b_off_hex", "table_cde_off_hex",
            "ptr_a_file", "ptr_b_file", "ptr_cde_file", "pad_7e",
            "min_x", "min_y", "min_z", "max_x", "max_y", "max_z",
        ])
        for r in trak.records:
            w.writerow([
                r.index, f"0x{r.file_offset:08X}", *r.center,
                r.a_count, r.b_count, r.c_count, r.d_count, r.e_count,
                f"0x{r.table_a_file_offset:08X}",
                f"0x{r.table_b_file_offset:08X}",
                f"0x{r.table_cde_file_offset:08X}",
                r.runtime_ptr_a_file_value,
                r.runtime_ptr_b_file_value,
                r.runtime_ptr_cde_file_value,
                r.pad_7e,
                *_record_bounds(r),
            ])


def write_table_a_csv(trak: TrakFile, path: Path) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow(["record", "vertex", "file_offset_hex", "x", "y", "z", "nx", "ny", "nz"])
        for r in trak.records:
            for v in r.table_a:
                w.writerow([r.index, v.index, f"0x{v.file_offset:08X}", v.x, v.y, v.z, v.nx, v.ny, v.nz])


def write_table_b_csv(trak: TrakFile, path: Path) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "record", "triangle", "file_offset_hex", "flags_hex", "flags_dec",
            "i0", "i1", "i2", "indices_valid", "material_index", "unknown",
            "plane_nx", "plane_ny", "plane_nz", "plane_d",
        ])
        for r in trak.records:
            for t in r.table_b:
                indices_valid = (
                    t.i0 < r.a_count and t.i1 < r.a_count and t.i2 < r.a_count and
                    len({t.i0, t.i1, t.i2}) == 3
                )
                w.writerow([
                    r.index, t.index, f"0x{t.file_offset:08X}", f"0x{t.flags:04X}", t.flags,
                    t.i0, t.i1, t.i2, int(indices_valid), t.material_index, t.unknown,
                    t.plane_nx, t.plane_ny, t.plane_nz, t.plane_d,
                ])


def write_table_cde_csv(trak: TrakFile, path: Path) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        headers = [
            "record", "group", "group_index", "combined_index", "file_offset_hex",
            "flags_hex", "is_quad", "surface_id", "surface_note",
            "normal_x_q32", "normal_y_q32", "normal_z_q32", "normal_scaled_x", "normal_scaled_y", "normal_scaled_z",
            "unknown_05_s8", "plane_d", "edge_count",
        ]
        for i in range(4):
            headers += [f"edge{i}_x_q32", f"edge{i}_y_q32", f"edge{i}_z_q32", f"edge{i}_unknown_03", f"edge{i}_d"]
        headers += ["raw_hex"]
        headers += [f"u16_{i:02d}" for i in range(16)]
        headers += [f"u32_{i:02d}" for i in range(8)]
        w.writerow(headers)
        for r in trak.records:
            for e in r.table_cde:
                u16s = struct.unpack("<16H", e.raw)
                u32s = struct.unpack("<8I", e.raw)
                edge_cols: list[int | str] = []
                for i in range(4):
                    if i < len(e.edges):
                        edge = e.edges[i]
                        edge_cols += [edge.x_q32, edge.y_q32, edge.z_q32, edge.unknown_03, edge.d]
                    else:
                        edge_cols += ["", "", "", "", ""]
                w.writerow([
                    r.index, e.group, e.group_index, e.combined_index,
                    f"0x{e.file_offset:08X}",
                    f"0x{e.flags:02X}", int(e.is_quad), e.surface_id, e.surface_note,
                    e.normal_x_q32, e.normal_y_q32, e.normal_z_q32, *e.normal,
                    e.unknown_05, e.plane_d, e.edge_count,
                    *edge_cols,
                    e.raw.hex(" "),
                    *u16s, *u32s,
                ])


# ---------------------------------------------------------------------------
# OBJ and viewer exports
# ---------------------------------------------------------------------------

def write_mtl(path: Path) -> None:
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Materials for diagnostic TRAK exports.\n")
        f.write("# OBJ/MTL transparency support varies by viewer; AABB/center exports use real faces.\n\n")
        f.write("newmtl trak_volume\nKd 0.2 0.6 1.0\nKa 0.0 0.0 0.0\nKs 0.0 0.0 0.0\nd 0.25\n\n")
        f.write("newmtl trak_aabb\nKd 0.1 0.45 1.0\nKa 0.0 0.0 0.0\nKs 0.0 0.0 0.0\nd 0.18\n\n")
        f.write("newmtl trak_center\nKd 1.0 0.85 0.1\nKa 0.0 0.0 0.0\nKs 0.0 0.0 0.0\n\n")
        f.write("newmtl trak_surface\nKd 0.8 0.8 0.8\nKa 0.0 0.0 0.0\nKs 0.0 0.0 0.0\n\n")
        # Generic material-index buckets.  The game maps these through dword_581154,
        # which is not fully decoded yet; these names keep OBJ files importable.
        for i in range(512):
            hue = (i * 37) % 360
            # Simple deterministic color palette without external dependencies.
            r = ((hue * 3) % 255) / 255.0
            g = ((hue * 5 + 80) % 255) / 255.0
            b = ((hue * 7 + 160) % 255) / 255.0
            f.write(f"newmtl trak_mat_{i:04d}\nKd {r:.3f} {g:.3f} {b:.3f}\nKa 0.0 0.0 0.0\nKs 0.0 0.0 0.0\n\n")


def write_record_volumes_obj(trak: TrakFile, path: Path, *, scale: float = 1.0, flip_z: bool = False) -> None:
    """Export the 8 corner points of every TRAK record as diagnostic box-like volumes."""
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib trak.mtl\n")
        f.write("# TRAK record volumes from the 0x84-byte main record table.\n")
        f.write("# These are diagnostic sector/cell boxes, not final render geometry.\n")
        vbase = 1
        edges = [(0,1),(1,3),(3,2),(2,0),(4,5),(5,7),(7,6),(6,4),(0,4),(1,5),(2,6),(3,7)]
        for r in trak.records:
            f.write(f"\no trak_record_{r.index:03d}\nusemtl trak_volume\n")
            for x, y, z in r.corners:
                z2 = -z if flip_z else z
                f.write(f"v {x*scale:.9g} {y*scale:.9g} {z2*scale:.9g}\n")
            for a, b in edges:
                f.write(f"l {vbase+a} {vbase+b}\n")
            vbase += 8




def _valid_table_b_triangles(record: TrakRecord):
    """Yield valid Table B triangles with their resolved Table A vertices.

    Table B indices are local to one TRAK record.  That means record 10's
    triangle index 0 refers to record 10's Table A vertex 0, not to a global
    vertex array.  Keeping this helper centralized prevents accidental global
    indexing mistakes in OBJ/HTML exporters.
    """
    for t in record.table_b:
        if not (t.i0 < record.a_count and t.i1 < record.a_count and t.i2 < record.a_count):
            continue
        if len({t.i0, t.i1, t.i2}) != 3:
            continue
        yield t, record.table_a[t.i0], record.table_a[t.i1], record.table_a[t.i2]


def _table_a_bounds(record: TrakRecord) -> tuple[float, float, float, float, float, float] | None:
    """Return bounds of the decoded Table A vertices for one record.

    This is more useful than the 8 header corner vectors for visualization:
    the header vectors are confirmed as 9 vec3 values, but their exact semantic
    meaning/order is not fully decoded.  Table A, however, is confirmed by the
    executable and by valid triangle output.
    """
    if not record.table_a:
        return None
    xs = [v.x for v in record.table_a]
    ys = [v.y for v in record.table_a]
    zs = [v.z for v in record.table_a]
    return min(xs), min(ys), min(zs), max(xs), max(ys), max(zs)


def _write_box_faces(f, min_x: float, min_y: float, min_z: float, max_x: float, max_y: float, max_z: float,
                     *, scale: float, flip_z: bool, start_index: int) -> int:
    """Write an AABB as normal OBJ faces and return the next vertex index."""
    pts = [
        (min_x, min_y, min_z), (max_x, min_y, min_z), (max_x, max_y, min_z), (min_x, max_y, min_z),
        (min_x, min_y, max_z), (max_x, min_y, max_z), (max_x, max_y, max_z), (min_x, max_y, max_z),
    ]
    for x, y, z in pts:
        z2 = -z if flip_z else z
        f.write(f"v {x*scale:.9g} {y*scale:.9g} {z2*scale:.9g}\n")
    faces = [(0,1,2,3), (4,7,6,5), (0,4,5,1), (1,5,6,2), (2,6,7,3), (3,7,4,0)]
    for face in faces:
        a, b, c, d = (start_index + i for i in face)
        f.write(f"f {a} {b} {c} {d}\n")
    return start_index + 8


def write_record_aabbs_obj(trak: TrakFile, path: Path, *, scale: float = 1.0, flip_z: bool = False) -> None:
    """Export one visible AABB per TRAK record using decoded Table A vertex bounds.

    This replaces the earlier record_volumes.obj as the primary record-level
    visualization.  The old file used the 8 vectors from the 0x84-byte record
    header as line segments; many 3D tools either hide OBJ line primitives or
    import them poorly, and the header-corner ordering is not fully understood.
    AABB boxes are derived from the confirmed decoded triangle vertices, so they
    are visible and useful for locating each record/sector in 3D.
    """
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib trak.mtl\n")
        f.write("# TRAK record AABBs generated from each record's decoded Table A vertices.\n")
        f.write("# These are diagnostic sector bounds, not original game render geometry.\n")
        vbase = 1
        for r in trak.records:
            bounds = _table_a_bounds(r)
            if bounds is None:
                continue
            f.write(f"\no trak_record_{r.index:03d}_aabb\nusemtl trak_aabb\n")
            vbase = _write_box_faces(f, *bounds, scale=scale, flip_z=flip_z, start_index=vbase)


def write_record_center_markers_obj(trak: TrakFile, path: Path, *, scale: float = 1.0, flip_z: bool = False) -> None:
    """Export a tiny cube marker at every TRAK record center.

    Centers come from the first vec3 in each 0x84-byte record.  The marker size
    is chosen from the global Table A bounding box so the cubes remain visible
    in Blender/MeshLab without overwhelming the surfaces.
    """
    all_vertices = [v for r in trak.records for v in r.table_a]
    if all_vertices:
        min_x, min_y, min_z = min(v.x for v in all_vertices), min(v.y for v in all_vertices), min(v.z for v in all_vertices)
        max_x, max_y, max_z = max(v.x for v in all_vertices), max(v.y for v in all_vertices), max(v.z for v in all_vertices)
        span = max(max_x-min_x, max_y-min_y, max_z-min_z, 1.0)
    else:
        span = 1.0
    half = span * 0.0025
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib trak.mtl\n")
        f.write("# Tiny cube markers at TRAK record centers.\n")
        vbase = 1
        for r in trak.records:
            cx, cy, cz = r.center
            bounds = (cx-half, cy-half, cz-half, cx+half, cy+half, cz+half)
            f.write(f"\no trak_record_{r.index:03d}_center\nusemtl trak_center\n")
            vbase = _write_box_faces(f, *bounds, scale=scale, flip_z=flip_z, start_index=vbase)

def write_table_b_surfaces_obj(trak: TrakFile, path: Path, *, scale: float = 1.0, flip_z: bool = False) -> None:
    """Export Table A/B as actual triangle surfaces per TRAK record."""
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib trak.mtl\n")
        f.write("# TRAK Table A/B triangle surfaces.\n")
        f.write("# Table A = position + normal. Table B = indexed triangles + plane/material fields.\n")
        vertex_base = 1
        for r in trak.records:
            f.write(f"\no trak_surface_record_{r.index:03d}\nusemtl trak_surface\n")
            for v in r.table_a:
                z = -v.z if flip_z else v.z
                f.write(f"v {v.x*scale:.9g} {v.y*scale:.9g} {z*scale:.9g}\n")
            for v in r.table_a:
                nz = -v.nz if flip_z else v.nz
                f.write(f"vn {v.nx:.9g} {v.ny:.9g} {nz:.9g}\n")
            current_mat: int | None = None
            for t in r.table_b:
                if not (t.i0 < r.a_count and t.i1 < r.a_count and t.i2 < r.a_count):
                    continue
                if len({t.i0, t.i1, t.i2}) != 3:
                    continue
                if t.material_index != current_mat:
                    current_mat = t.material_index
                    f.write(f"usemtl trak_mat_{current_mat:04d}\n")
                a = vertex_base + t.i0
                b = vertex_base + t.i1
                c = vertex_base + t.i2
                f.write(f"f {a}//{a} {b}//{b} {c}//{c}\n")
            vertex_base += r.a_count




def write_per_record_surface_objs(trak: TrakFile, out_dir: Path, *, scale: float = 1.0, flip_z: bool = False) -> int:
    """Write one OBJ file per TRAK record using that record's Table A/B triangles.

    The combined table_b_surfaces.obj is convenient for seeing the whole level,
    but one-file-per-record is much easier for debugging sector ownership,
    culling, collision, and possible navigation/camera constraints.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    written = 0
    for r in trak.records:
        valid = list(_valid_table_b_triangles(r))
        if not valid:
            continue
        path = out_dir / f"record_{r.index:03d}_surface.obj"
        with path.open("w", encoding="utf-8", newline="\n") as f:
            # Relative material path because files live inside trak/per_record_surfaces/.
            f.write("mtllib ../trak.mtl\n")
            f.write(f"# TRAK per-record surface OBJ for record {r.index}.\n")
            f.write(f"# vertices={r.a_count} triangles={len(valid)} c/d/e={r.c_count}/{r.d_count}/{r.e_count}\n")
            f.write(f"o trak_record_{r.index:03d}_surface\n")
            for v in r.table_a:
                z = -v.z if flip_z else v.z
                f.write(f"v {v.x*scale:.9g} {v.y*scale:.9g} {z*scale:.9g}\n")
            for v in r.table_a:
                nz = -v.nz if flip_z else v.nz
                f.write(f"vn {v.nx:.9g} {v.ny:.9g} {nz:.9g}\n")
            current_mat: int | None = None
            for t, _a, _b, _c in valid:
                if t.material_index != current_mat:
                    current_mat = t.material_index
                    f.write(f"usemtl trak_mat_{current_mat:04d}\n")
                a = t.i0 + 1
                b = t.i1 + 1
                c = t.i2 + 1
                f.write(f"f {a}//{a} {b}//{b} {c}//{c}\n")
        written += 1
    return written

def write_viewer_html(trak: TrakFile, path: Path) -> None:
    """Write the local-coordinate TRAK viewer from an external HTML template.

    The main extractor overwrites `trak/viewer.html` with a MAP-placed version
    once MAP_FULL has been parsed.  This local version remains useful when a
    raw TRAK chunk is exported without MAP context.
    """
    from .trak_viewer import write_local_trak_viewer_html

    write_local_trak_viewer_html(trak, path)


# ---------------------------------------------------------------------------
# Summary/export orchestration
# ---------------------------------------------------------------------------

def _valid_triangle_counts(trak: TrakFile) -> tuple[int, int, set[int]]:
    valid_triangles = 0
    invalid_triangles = 0
    materials: set[int] = set()
    for r in trak.records:
        for t in r.table_b:
            materials.add(t.material_index)
            ok = t.i0 < r.a_count and t.i1 < r.a_count and t.i2 < r.a_count and len({t.i0, t.i1, t.i2}) == 3
            if ok:
                valid_triangles += 1
            else:
                invalid_triangles += 1
    return valid_triangles, invalid_triangles, materials


def write_summary(trak: TrakFile, path: Path) -> None:
    valid_triangles, invalid_triangles, materials = _valid_triangle_counts(trak)
    summary = f"""TRAK decode summary
===================

record_count:          {trak.record_count}
source_size:           {trak.source_size}
parsed_size:           {trak.parsed_size}
parsed_all_bytes:      {trak.parsed_size == trak.source_size}

Table A entries:       {trak.total_a_entries}  (stride 24, likely vertex position + normal)
Table B entries:       {trak.total_b_entries}  (stride 28, indexed triangle/plane/material)
Table C entries:       {trak.total_c_entries}  (stride 32, collision/contact plane group 0)
Table D entries:       {trak.total_d_entries}  (stride 32, collision/contact plane group 1)
Table E entries:       {trak.total_e_entries}  (stride 32, collision/contact plane group 2)

Valid B triangles:     {valid_triangles}
Invalid B triangles:   {invalid_triangles}
Unique material index: {len(materials)}

Executable confirmation
-----------------------
sub_42AAC0 reads the TRAK chunk, then calls sub_5563F0.
sub_5563F0 confirms:
  records are 0x84 bytes each
  record+0x6C = Table A count, stride 24, pointer written to +0x70
  record+0x6E = Table B count, stride 28, pointer written to +0x74
  record+0x00/+0x04/+0x08 are still-unknown header values
  record+0x0C..+0x6B are 8 vec3 culling/bounds points used by sub_402840
  record+0x78/+0x7A/+0x7C are combined C/D/E collision entry counts, stride 32, pointer written to +0x80
  each Table B entry +0x08 is converted from a u16 material/global-table index into dword_581154 + 20*index

Interpretation status
---------------------
Table A and Table B are structurally decoded and exported as combined and per-record OBJ surfaces.
record_aabbs.obj is a diagnostic bounding-box view derived from Table A vertices.
Table C/D/E are now decoded as compact collision/contact plane entries.
Each entry stores flags, surface_id, signed q32 plane coefficients, plane_d, and 3/4 edge half-space equations.
TRAK appears to describe level spatial/render/collision sectors, not a simple cinematic camera spline.
"""
    path.write_text(summary, encoding="utf-8")


def export_trak_outputs(trak: TrakFile, out_dir: Path, *, scale: float = 1.0, flip_z: bool = False) -> TrakExportResult:
    """Write all TRAK CSV/OBJ/viewer outputs to a dedicated folder."""
    out_dir.mkdir(parents=True, exist_ok=True)
    write_summary(trak, out_dir / "summary.txt")
    write_records_csv(trak, out_dir / "records.csv")
    write_table_a_csv(trak, out_dir / "table_a_vertices.csv")
    write_table_b_csv(trak, out_dir / "table_b_triangles.csv")
    write_table_cde_csv(trak, out_dir / "table_cde_entries.csv")
    write_mtl(out_dir / "trak.mtl")

    # Main geometry exports.
    write_table_b_surfaces_obj(trak, out_dir / "table_b_surfaces.obj", scale=scale, flip_z=flip_z)
    write_per_record_surface_objs(trak, out_dir / "per_record_surfaces", scale=scale, flip_z=flip_z)

    # Diagnostic record-level exports.  AABBs and center markers are written with
    # faces so they are visible in common 3D tools.  The older header-vector
    # line export is retained but renamed to make its uncertainty explicit.
    write_record_aabbs_obj(trak, out_dir / "record_aabbs.obj", scale=scale, flip_z=flip_z)
    write_record_center_markers_obj(trak, out_dir / "record_centers.obj", scale=scale, flip_z=flip_z)
    write_record_volumes_obj(trak, out_dir / "record_header_vectors_diagnostic.obj", scale=scale, flip_z=flip_z)

    write_viewer_html(trak, out_dir / "viewer.html")
    return TrakExportResult(trak=trak, out_dir=out_dir)


def export_trak_from_bytes(buf: bytes, out_dir: Path, *, scale: float = 1.0, flip_z: bool = False) -> TrakExportResult:
    """Convenience API used by the main WAD extractor."""
    trak = parse_trak_chunk(buf)
    return export_trak_outputs(trak, out_dir, scale=scale, flip_z=flip_z)
