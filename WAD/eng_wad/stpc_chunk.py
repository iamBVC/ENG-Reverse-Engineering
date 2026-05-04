#!/usr/bin/env python3
"""
stpc_chunk.py — importable STPC static-geometry unpacker.

This module is a reverse-engineering helper for the STPC chunk used by
Disney's / Argonaut's Emperor's New Groove level WAD files.

It can be used in two ways:

    1) As a standalone command-line tool:

        python stpc_unpacker.py stpc.bin -o stpc_obj

    2) As a library from wad_extractor.py:

        from eng_wad.stpc_chunk import export_stpc_meshes_from_bytes

        result = export_stpc_meshes_from_bytes(stpc_bytes, out_dir / "stpc_obj")

The current parser is intentionally conservative.  The full STPC container is
not completely decoded yet, but the static mesh records inside the blob are
reliably identifiable by a repeated header/vertex/triangle layout.

Observed STPC high-level layout
-------------------------------

The file/chunk begins with a small little-endian uint32 value.  In the tested
level this behaves like a top-level count or table length, but it is not yet
safe to use it as the only source of truth for parsing the whole chunk.

After that, the blob contains several recognizable mesh-like records plus other
still-unknown data.  Because the unknown sections may contain collision, BSP,
render batching, visibility, or material lookup data, this module scans for
valid mesh records instead of assuming every byte belongs to a linear array.

Recognized mesh record shape
----------------------------

All integer and float fields are little-endian.

    record +0x00  u32/f32      unknown field; sometimes looks like metadata
    record +0x04  f32          unknown header float
    record +0x08  f32          unknown header float
    record +0x0C  8 x vec3     96 bytes of culling/bounds points.
                                sub_402840 transforms these points and OR/ANDs
                                clip outcodes for frustum rejection.

    record +0x6C  u32          packed mesh counts:
                                    low  16 bits = vertex_count
                                    high 16 bits = triangle_count

    record +0x70  u32          unknown header word
    record +0x74  u32          unknown header word
    record +0x78  u32          unknown header word
    record +0x7C  u32          unknown header word
    record +0x80  u32          unknown header word
    record +0x84  u32          repeated vertex_count
                                This duplicate count is a strong signature.
    record +0x88  u32          unknown header word

    record +0x8C  vertices     vertex_count entries, 24 bytes each:
                                    float x, y, z
                                    float nx, ny, nz

    ...          triangles     triangle_count entries, 28 bytes each:
                                    u16 face_flags
                                    u16 i0, i1, i2
                                    u16 material_or_texture_id
                                    u16 unknown
                                    float plane_nx, plane_ny, plane_nz, plane_d

Exported files
--------------

    manifest.csv               one row per detected mesh
    mesh_XXX_off_XXXXXXXX.obj  one OBJ per detected mesh
    combined.obj               all detected meshes in one OBJ
    faces_debug.csv            optional per-triangle metadata dump

Important limitations
---------------------

This is not yet a complete STPC semantic decoder.  OBJ geometry is valid, and
the shared GeometryRecord84/STPC-like render layout is now mostly confirmed from
sub_402840/sub_556510/sub_41FB30.  Material table binding is partially decoded,
but object-local texture coordinates and high-level STPC container tables still
need more work.
"""

from __future__ import annotations

import argparse
import csv
import math
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable


# Size of the decoded mesh-record header before vertex data begins.
HEADER_SIZE = 0x8C

# Vertex format currently confirmed from extracted meshes:
#     float x, y, z
#     float nx, ny, nz
VERTEX_STRIDE = 24

# Triangle format currently confirmed from extracted meshes:
#     6 x uint16 + 4 x float
TRI_STRIDE = 28


# ---------------------------------------------------------------------------
# Binary helpers
# ---------------------------------------------------------------------------

def u16(buf: bytes, off: int) -> int:
    """Read an unsigned little-endian 16-bit integer."""
    return struct.unpack_from("<H", buf, off)[0]


def u32(buf: bytes, off: int) -> int:
    """Read an unsigned little-endian 32-bit integer."""
    return struct.unpack_from("<I", buf, off)[0]


def f32(buf: bytes, off: int) -> float:
    """Read a little-endian IEEE754 float."""
    return struct.unpack_from("<f", buf, off)[0]


def read_vec3(buf: bytes, off: int) -> tuple[float, float, float]:
    """Read three consecutive little-endian floats."""
    return struct.unpack_from("<3f", buf, off)


def sane_float(v: float, limit: float = 100000.0) -> bool:
    """
    Return True for finite coordinate-like values.

    The limit is intentionally generous because the game world can be large,
    but it filters NaN/Inf and random integer bit-patterns interpreted as floats.
    """
    return math.isfinite(v) and abs(v) <= limit


def normal_len_ok(nx: float, ny: float, nz: float) -> bool:
    """
    Return True when a vector looks like a normal.

    Exported STPC normals and plane normals are usually close to unit length.
    The range is loose because some game data may contain quantization, axis
    transforms, or slightly denormalized values.
    """
    n = math.sqrt(nx * nx + ny * ny + nz * nz)
    return 0.25 <= n <= 1.75


# ---------------------------------------------------------------------------
# Decoded structures
# ---------------------------------------------------------------------------

@dataclass
class Vertex:
    """One decoded STPC vertex."""
    x: float
    y: float
    z: float
    nx: float
    ny: float
    nz: float


@dataclass
class Triangle:
    """
    One decoded STPC triangle.

    The first six uint16 values are useful even before their exact meanings are
    fully known.  i0/i1/i2 are vertex indices.  material is currently exported
    as an OBJ material group named mat_XXXX.
    """
    flags: int
    i0: int
    i1: int
    i2: int
    material: int
    unknown: int
    plane_nx: float
    plane_ny: float
    plane_nz: float
    plane_d: float


def triangle_flag_notes(flags: int) -> str:
    """Human-readable notes for confirmed triangle flag bits.

    These names come from sub_556510/sub_41FB30.  Some low bits are still render
    state/effect related, so the labels stay conservative.
    """
    notes: list[str] = []
    if flags & 0x0001:
        notes.append("material_special_or_color_path")
    if flags & 0x0002:
        notes.append("effect_queue_related")
    if flags & 0x0008:
        notes.append("batch_or_material_break")
    if flags & 0x0010:
        notes.append("uv_branch_0x10")
    if flags & 0x0020:
        notes.append("uv_swap_or_filter_bit")
    if flags & 0x0400:
        notes.append("backface_cull_override")
    if flags & 0x0800:
        notes.append("terrain_uv_branch_0x800")
    return ";".join(notes)


@dataclass
class MeshCandidate:
    """A mesh record found inside an STPC blob."""
    index: int
    offset: int
    vertex_count: int
    triangle_count: int
    valid_triangles: int
    score: float
    header_words: tuple[int, int, int, int, int, int, int, int]
    bounds_min: tuple[float, float, float]
    bounds_max: tuple[float, float, float]
    vertices: list[Vertex]
    triangles: list[Triangle]

    @property
    def vertex_offset(self) -> int:
        return self.offset + HEADER_SIZE

    @property
    def triangle_offset(self) -> int:
        return self.vertex_offset + self.vertex_count * VERTEX_STRIDE

    @property
    def end_offset(self) -> int:
        return self.triangle_offset + self.triangle_count * TRI_STRIDE


@dataclass
class STPCExportResult:
    """Summary returned by the library export API."""
    top_count: int
    input_size: int
    output_dir: Path
    meshes: list[MeshCandidate]
    manifest_path: Path
    combined_obj_path: Path | None
    mesh_obj_paths: list[Path]
    faces_debug_path: Path | None


# ---------------------------------------------------------------------------
# Parsing
# ---------------------------------------------------------------------------

def parse_vertices(buf: bytes, off: int, count: int) -> list[Vertex]:
    """Parse count vertices from a known STPC vertex block."""
    vertices: list[Vertex] = []

    for i in range(count):
        p = off + i * VERTEX_STRIDE
        x, y, z, nx, ny, nz = struct.unpack_from("<6f", buf, p)
        vertices.append(Vertex(x, y, z, nx, ny, nz))

    return vertices


def parse_triangles(buf: bytes, off: int, count: int) -> list[Triangle]:
    """Parse count triangles from a known STPC triangle block."""
    triangles: list[Triangle] = []

    for i in range(count):
        p = off + i * TRI_STRIDE

        flags, i0, i1, i2, material, unknown = struct.unpack_from("<6H", buf, p)
        plane_nx, plane_ny, plane_nz, plane_d = struct.unpack_from("<4f", buf, p + 12)

        triangles.append(Triangle(
            flags=flags,
            i0=i0,
            i1=i1,
            i2=i2,
            material=material,
            unknown=unknown,
            plane_nx=plane_nx,
            plane_ny=plane_ny,
            plane_nz=plane_nz,
            plane_d=plane_d,
        ))

    return triangles


def compute_bounds(vertices: list[Vertex]) -> tuple[tuple[float, float, float], tuple[float, float, float]]:
    """Compute axis-aligned bounds from decoded vertices."""
    if not vertices:
        return (0.0, 0.0, 0.0), (0.0, 0.0, 0.0)

    xs = [v.x for v in vertices]
    ys = [v.y for v in vertices]
    zs = [v.z for v in vertices]

    return (min(xs), min(ys), min(zs)), (max(xs), max(ys), max(zs))


def try_parse_mesh(
    buf: bytes,
    off: int,
    index: int,
    min_vertices: int,
    max_vertices: int,
    max_triangles: int,
) -> MeshCandidate | None:
    """
    Try to parse one mesh record at absolute offset off.

    This returns None if the bytes at off do not look like a valid STPC mesh
    record.  The validation is intentionally strict enough to reject random
    bytes but loose enough to keep currently confirmed meshes.
    """
    if off + HEADER_SIZE > len(buf):
        return None

    packed = u32(buf, off + 0x6C)
    vertex_count = packed & 0xFFFF
    triangle_count = (packed >> 16) & 0xFFFF

    repeated_vertex_count = u32(buf, off + 0x84)

    # Signature checks.  The repeated vertex count at +0x84 is one of the most
    # useful ways to distinguish real mesh records from random data.
    if vertex_count < min_vertices:
        return None
    if vertex_count > max_vertices:
        return None
    if triangle_count <= 0 or triangle_count > max_triangles:
        return None
    if repeated_vertex_count != vertex_count:
        return None

    vertex_off = off + HEADER_SIZE
    triangle_off = vertex_off + vertex_count * VERTEX_STRIDE
    end_off = triangle_off + triangle_count * TRI_STRIDE

    if end_off > len(buf):
        return None

    # Validate bounding/corner floats.  Observed records contain 24 reasonable
    # floats starting at +0x0C, probably 8 local bbox/corner vectors.
    try:
        bound_probe = struct.unpack_from("<24f", buf, off + 0x0C)
    except struct.error:
        return None

    if not all(sane_float(v) for v in bound_probe):
        return None

    vertices = parse_vertices(buf, vertex_off, vertex_count)

    sane_vertices = 0
    sane_normals = 0
    for v in vertices:
        if sane_float(v.x) and sane_float(v.y) and sane_float(v.z):
            sane_vertices += 1
        if sane_float(v.nx) and sane_float(v.ny) and sane_float(v.nz) and normal_len_ok(v.nx, v.ny, v.nz):
            sane_normals += 1

    if sane_vertices != vertex_count:
        return None

    triangles = parse_triangles(buf, triangle_off, triangle_count)

    valid_triangles = 0
    for tri in triangles:
        indices_ok = (
            tri.i0 < vertex_count and
            tri.i1 < vertex_count and
            tri.i2 < vertex_count and
            len({tri.i0, tri.i1, tri.i2}) == 3
        )

        plane_ok = (
            sane_float(tri.plane_nx) and
            sane_float(tri.plane_ny) and
            sane_float(tri.plane_nz) and
            sane_float(tri.plane_d) and
            normal_len_ok(tri.plane_nx, tri.plane_ny, tri.plane_nz)
        )

        if indices_ok and plane_ok:
            valid_triangles += 1

    score = 0.0
    if triangle_count:
        score += 0.70 * (valid_triangles / triangle_count)
    if vertex_count:
        score += 0.30 * (sane_normals / vertex_count)

    if valid_triangles == 0:
        return None

    header_words = tuple(u32(buf, off + 0x6C + i * 4) for i in range(8))
    bounds_min, bounds_max = compute_bounds(vertices)

    return MeshCandidate(
        index=index,
        offset=off,
        vertex_count=vertex_count,
        triangle_count=triangle_count,
        valid_triangles=valid_triangles,
        score=score,
        header_words=header_words,
        bounds_min=bounds_min,
        bounds_max=bounds_max,
        vertices=vertices,
        triangles=triangles,
    )


def scan_meshes(
    buf: bytes,
    *,
    alignment: int = 4,
    min_score: float = 0.85,
    min_vertices: int = 3,
    max_vertices: int = 20000,
    max_triangles: int = 50000,
) -> list[MeshCandidate]:
    """
    Scan an STPC blob for mesh-like records.

    This intentionally scans instead of trusting a full container parser because
    STPC contains extra data between and/or after recognizable mesh records.
    Once the remaining tables are decoded, this function can be replaced by a
    strict table-driven parser while keeping the export API stable.
    """
    if alignment <= 0:
        raise ValueError("alignment must be >= 1")

    raw_candidates: list[MeshCandidate] = []

    # The first dword appears to be a top-level count/table field, so scanning
    # starts at offset 4 by default.
    start = 4
    candidate_index = 0

    for off in range(start, len(buf) - HEADER_SIZE, alignment):
        mesh = try_parse_mesh(buf, off, candidate_index, min_vertices, max_vertices, max_triangles)
        if mesh is None:
            continue

        if mesh.score < min_score:
            continue

        raw_candidates.append(mesh)
        candidate_index += 1

    # Remove duplicate candidates with the same offset, preferring high score.
    by_offset: dict[int, MeshCandidate] = {}
    for mesh in raw_candidates:
        old = by_offset.get(mesh.offset)
        if old is None or mesh.score > old.score:
            by_offset[mesh.offset] = mesh

    meshes = sorted(by_offset.values(), key=lambda m: m.offset)

    # Re-number after sorting so filenames are stable and sequential.
    for i, mesh in enumerate(meshes):
        mesh.index = i

    return meshes


# ---------------------------------------------------------------------------
# Export helpers
# ---------------------------------------------------------------------------

def iter_material_ids(meshes: Iterable[MeshCandidate]) -> list[int]:
    """Return sorted material IDs used by all valid triangles."""
    mats: set[int] = set()
    for mesh in meshes:
        for tri in mesh.triangles:
            if tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count:
                if len({tri.i0, tri.i1, tri.i2}) == 3:
                    mats.add(tri.material)
    return sorted(mats)


def _material_by_index(materials) -> dict[int, object]:
    """Return a loose index -> material map without importing material_chunk.

    stpc_chunk is imported by material_chunk, so this module intentionally uses
    duck typing for RuntimeMaterial-like objects.
    """
    return {int(getattr(m, "index")): m for m in (materials or []) if hasattr(m, "index")}


def _material_texture_index(mat: object | None, texture_count: int | None) -> int | None:
    if mat is None or bool(getattr(mat, "is_color_only", False)):
        return None
    raw = int(getattr(mat, "texture_index", -1)) & 0xFF
    if texture_count is not None and not (0 <= raw < texture_count):
        return None
    return raw


def _material_uv_rect(mat: object | None, *, flip_v_for_obj: bool = True) -> tuple[float, float, float, float]:
    if mat is None or bool(getattr(mat, "is_color_only", False)) or not hasattr(mat, "uv_rect"):
        u0, u1, v0, v1 = 0.0, 1.0, 0.0, 1.0
    else:
        u0, u1, v0, v1 = getattr(mat, "uv_rect")()
    if flip_v_for_obj:
        v0, v1 = 1.0 - v0, 1.0 - v1
    return u0, u1, v0, v1


def stpc_triangle_uvs(mat: object | None, face_flags: int, *, flip_v_for_obj: bool = True) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return the EXE-style UV triplet for one STPC/TRAK triangle.

    STPC mesh records carry the same 28-byte triangle layout as TRAK and the
    renderer resolves triangle +0x08 to a 20-byte runtime material.  The exact
    per-triangle UV selector is driven by the same confirmed flag bits used by
    sub_556510: 0x0800, 0x0010, and 0x0020.
    """
    u0, u1, v0, v1 = _material_uv_rect(mat, flip_v_for_obj=flip_v_for_obj)
    swap_u = bool(face_flags & 0x0020)
    if face_flags & 0x0800:
        if face_flags & 0x0010:
            return (
                (u1 if swap_u else u0, v0),
                (u0 if swap_u else u1, v0),
                (u0 if swap_u else u1, v1),
            )
        return (
            (u0 if swap_u else u1, v1),
            (u1 if swap_u else u0, v1),
            (u1 if swap_u else u0, v0),
        )
    return (
        (u0 if swap_u else u1, v1),
        (u1 if swap_u else u0, v1),
        (u0 if swap_u else u1, v0),
    )


def write_mtl(
    material_ids: Iterable[int],
    path: Path,
    *,
    materials=None,
    texture_count: int | None = None,
    texture_prefix: str = "../textures",
    material_prefix: str = "mat",
) -> None:
    """Write an OBJ material library for STPC meshes.

    When RuntimeMaterial rows from TEXT are available, material IDs are bound to
    the decoded texture pages.  Otherwise the MTL falls back to deterministic
    diffuse colours so the geometry is still easy to inspect.
    """
    ids = list(material_ids)
    mat_by_i = _material_by_index(materials)
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Auto-generated MTL for STPC OBJ export\n")
        f.write("# Uses TEXT runtime material table when available; otherwise diffuse fallback colours.\n\n")
        for mat_id in ids:
            m = mat_by_i.get(mat_id)
            r = ((mat_id * 37 + 80) % 255) / 255.0
            g = ((mat_id * 67 + 120) % 255) / 255.0
            b = ((mat_id * 97 + 160) % 255) / 255.0
            f.write(f"newmtl {material_prefix}_{mat_id:04d}\n")
            f.write(f"Kd {r:.6f} {g:.6f} {b:.6f}\n")
            f.write("Ka 0.000000 0.000000 0.000000\n")
            f.write("Ks 0.000000 0.000000 0.000000\n")
            f.write("d 1.000000\n")
            tex_i = _material_texture_index(m, texture_count)
            if tex_i is not None:
                f.write(f"map_Kd {texture_prefix}/texture_{tex_i:02d}.png\n")
                f.write(f"# raw_texture_page={getattr(m, 'texture_index', '')} material_rect={getattr(m, 'x0', '')},{getattr(m, 'y0', '')},{getattr(m, 'x1', '')},{getattr(m, 'y1', '')} flags=0x{int(getattr(m, 'flags', 0)):04X}\n")
            f.write("\n")


def write_obj(
    mesh: MeshCandidate,
    path: Path,
    *,
    scale: float = 1.0,
    flip_z: bool = False,
    mtl_name: str | None = None,
    materials=None,
    material_prefix: str = "mat",
) -> None:
    """Write one STPC mesh as a Wavefront OBJ file."""
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write(f"# STPC mesh candidate {mesh.index}\n")
        f.write(f"# source_offset=0x{mesh.offset:08X}\n")
        f.write(f"# vertices={mesh.vertex_count} triangles={mesh.triangle_count} valid_triangles={mesh.valid_triangles}\n")
        f.write(f"# score={mesh.score:.4f}\n")
        f.write("# Vertex format in STPC: float x,y,z + float nx,ny,nz, 24 bytes per vertex.\n")
        f.write("# Triangle format in STPC: 6 uint16 values + float plane equation, 28 bytes per triangle.\n")
        if mtl_name:
            f.write(f"mtllib {mtl_name}\n")
        f.write(f"o stpc_mesh_{mesh.index:03d}\n")

        for v in mesh.vertices:
            z = -v.z if flip_z else v.z
            f.write(f"v {v.x * scale:.9g} {v.y * scale:.9g} {z * scale:.9g}\n")

        for v in mesh.vertices:
            nz = -v.nz if flip_z else v.nz
            f.write(f"vn {v.nx:.9g} {v.ny:.9g} {nz:.9g}\n")

        current_mat: int | None = None
        mat_by_i = _material_by_index(materials)
        vt_index = 1

        for tri in mesh.triangles:
            if not (tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count):
                continue
            if len({tri.i0, tri.i1, tri.i2}) != 3:
                continue

            if tri.material != current_mat:
                current_mat = tri.material
                f.write(f"usemtl {material_prefix}_{current_mat:04d}\n")

            uv0, uv1, uv2 = stpc_triangle_uvs(mat_by_i.get(tri.material), tri.flags)
            f.write(f"vt {uv0[0]:.9g} {uv0[1]:.9g}\n")
            f.write(f"vt {uv1[0]:.9g} {uv1[1]:.9g}\n")
            f.write(f"vt {uv2[0]:.9g} {uv2[1]:.9g}\n")

            # OBJ indices are 1-based.  Normals are per-source vertex; UVs are
            # per-face because the EXE derives them from triangle flags/material.
            a = tri.i0 + 1
            b = tri.i1 + 1
            c = tri.i2 + 1

            f.write(f"f {a}/{vt_index}/{a} {b}/{vt_index + 1}/{b} {c}/{vt_index + 2}/{c}\n")
            vt_index += 3


def write_combined_obj(
    meshes: list[MeshCandidate],
    path: Path,
    *,
    scale: float = 1.0,
    flip_z: bool = False,
    mtl_name: str | None = None,
    materials=None,
    material_prefix: str = "mat",
) -> None:
    """Write all detected STPC meshes into one OBJ file."""
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Combined STPC mesh candidates\n")
        f.write("# Each OBJ object corresponds to one recognized STPC mesh record.\n")
        if mtl_name:
            f.write(f"mtllib {mtl_name}\n")

        vertex_base = 1
        normal_base = 1
        vt_base = 1
        mat_by_i = _material_by_index(materials)

        for mesh in meshes:
            f.write(f"\no stpc_mesh_{mesh.index:03d}_off_{mesh.offset:08X}\n")

            for v in mesh.vertices:
                z = -v.z if flip_z else v.z
                f.write(f"v {v.x * scale:.9g} {v.y * scale:.9g} {z * scale:.9g}\n")

            for v in mesh.vertices:
                nz = -v.nz if flip_z else v.nz
                f.write(f"vn {v.nx:.9g} {v.ny:.9g} {nz:.9g}\n")

            current_mat: int | None = None

            for tri in mesh.triangles:
                if not (tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count):
                    continue
                if len({tri.i0, tri.i1, tri.i2}) != 3:
                    continue

                if tri.material != current_mat:
                    current_mat = tri.material
                    f.write(f"usemtl {material_prefix}_{current_mat:04d}\n")

                uv0, uv1, uv2 = stpc_triangle_uvs(mat_by_i.get(tri.material), tri.flags)
                f.write(f"vt {uv0[0]:.9g} {uv0[1]:.9g}\n")
                f.write(f"vt {uv1[0]:.9g} {uv1[1]:.9g}\n")
                f.write(f"vt {uv2[0]:.9g} {uv2[1]:.9g}\n")

                a = vertex_base + tri.i0
                b = vertex_base + tri.i1
                c = vertex_base + tri.i2
                na = normal_base + tri.i0
                nb = normal_base + tri.i1
                nc = normal_base + tri.i2
                f.write(f"f {a}/{vt_base}/{na} {b}/{vt_base + 1}/{nb} {c}/{vt_base + 2}/{nc}\n")
                vt_base += 3

            vertex_base += mesh.vertex_count
            normal_base += mesh.vertex_count


def write_manifest(meshes: list[MeshCandidate], path: Path) -> None:
    """Write a CSV summary of detected STPC meshes."""
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "mesh",
            "offset_hex",
            "offset_dec",
            "vertex_offset_hex",
            "triangle_offset_hex",
            "end_offset_hex",
            "vertex_count",
            "triangle_count",
            "valid_triangles",
            "score",
            "bounds_min_x",
            "bounds_min_y",
            "bounds_min_z",
            "bounds_max_x",
            "bounds_max_y",
            "bounds_max_z",
            "header_6c_packed_counts",
            "header_70",
            "header_74",
            "header_78",
            "header_7c",
            "header_80",
            "header_84_repeated_vertex_count_or_base_vertex_count",
            "header_88_group_counts_or_unknown",
        ])

        for mesh in meshes:
            w.writerow([
                mesh.index,
                f"0x{mesh.offset:08X}",
                mesh.offset,
                f"0x{mesh.vertex_offset:08X}",
                f"0x{mesh.triangle_offset:08X}",
                f"0x{mesh.end_offset:08X}",
                mesh.vertex_count,
                mesh.triangle_count,
                mesh.valid_triangles,
                f"{mesh.score:.6f}",
                *mesh.bounds_min,
                *mesh.bounds_max,
                *[f"0x{x:08X}" for x in mesh.header_words],
            ])


def write_debug_faces(meshes: list[MeshCandidate], out_dir: Path) -> Path:
    """Write a per-face metadata CSV for reverse-engineering flags/materials."""
    path = out_dir / "faces_debug.csv"
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "mesh",
            "face",
            "flags_hex",
            "flag_notes",
            "flag_material_special_or_color_path",
            "flag_effect_queue_related",
            "flag_batch_or_material_break",
            "flag_uv_branch_0x10",
            "flag_uv_swap_or_filter_bit",
            "flag_backface_cull_override",
            "flag_terrain_uv_branch_0x800",
            "i0",
            "i1",
            "i2",
            "material",
            "unknown",
            "plane_nx",
            "plane_ny",
            "plane_nz",
            "plane_d",
        ])

        for mesh in meshes:
            for i, tri in enumerate(mesh.triangles):
                w.writerow([
                    mesh.index,
                    i,
                    f"0x{tri.flags:04X}",
                    triangle_flag_notes(tri.flags),
                    int(bool(tri.flags & 0x0001)),
                    int(bool(tri.flags & 0x0002)),
                    int(bool(tri.flags & 0x0008)),
                    int(bool(tri.flags & 0x0010)),
                    int(bool(tri.flags & 0x0020)),
                    int(bool(tri.flags & 0x0400)),
                    int(bool(tri.flags & 0x0800)),
                    tri.i0,
                    tri.i1,
                    tri.i2,
                    tri.material,
                    tri.unknown,
                    tri.plane_nx,
                    tri.plane_ny,
                    tri.plane_nz,
                    tri.plane_d,
                ])
    return path


# ---------------------------------------------------------------------------
# Public library API
# ---------------------------------------------------------------------------

def export_stpc_meshes_from_bytes(
    buf: bytes,
    out_dir: Path,
    *,
    alignment: int = 4,
    min_score: float = 0.85,
    min_vertices: int = 3,
    max_vertices: int = 20000,
    max_triangles: int = 50000,
    scale: float = 1.0,
    flip_z: bool = False,
    write_combined: bool = True,
    write_debug: bool = False,
    write_materials: bool = True,
    materials=None,
    texture_count: int | None = None,
    verbose: bool = False,
) -> STPCExportResult:
    """
    Scan an STPC blob and export detected mesh records as OBJ files.

    This is the main function used by wad_extractor.py.  It accepts raw STPC
    bytes directly, so the WAD extractor does not need to create stpc.bin first,
    although it still can and does for archival/debug purposes.
    """
    out_dir.mkdir(parents=True, exist_ok=True)

    top_count = u32(buf, 0) if len(buf) >= 4 else 0

    meshes = scan_meshes(
        buf,
        alignment=alignment,
        min_score=min_score,
        min_vertices=min_vertices,
        max_vertices=max_vertices,
        max_triangles=max_triangles,
    )

    manifest_path = out_dir / "manifest.csv"
    write_manifest(meshes, manifest_path)

    mtl_path: Path | None = None
    mtl_name: str | None = None
    if write_materials and meshes:
        mtl_path = out_dir / "stpc_materials.mtl"
        write_mtl(iter_material_ids(meshes), mtl_path, materials=materials, texture_count=texture_count)
        mtl_name = mtl_path.name

    mesh_obj_paths: list[Path] = []
    for mesh in meshes:
        obj_path = out_dir / f"mesh_{mesh.index:03d}_off_{mesh.offset:08X}.obj"
        write_obj(mesh, obj_path, scale=scale, flip_z=flip_z, mtl_name=mtl_name, materials=materials)
        mesh_obj_paths.append(obj_path)

        if verbose:
            print(
                f"  mesh_{mesh.index:03d}: "
                f"off=0x{mesh.offset:08X} "
                f"v={mesh.vertex_count} "
                f"tri={mesh.triangle_count} "
                f"score={mesh.score:.3f}"
            )

    combined_obj_path: Path | None = None
    if write_combined and meshes:
        combined_obj_path = out_dir / "combined.obj"
        write_combined_obj(meshes, combined_obj_path, scale=scale, flip_z=flip_z, mtl_name=mtl_name, materials=materials)

    faces_debug_path: Path | None = None
    if write_debug:
        faces_debug_path = write_debug_faces(meshes, out_dir)

    return STPCExportResult(
        top_count=top_count,
        input_size=len(buf),
        output_dir=out_dir,
        meshes=meshes,
        manifest_path=manifest_path,
        combined_obj_path=combined_obj_path,
        mesh_obj_paths=mesh_obj_paths,
        faces_debug_path=faces_debug_path,
    )


def export_stpc_meshes_from_file(
    stpc_bin: Path,
    out_dir: Path,
    **kwargs,
) -> STPCExportResult:
    """Read stpc_bin and forward to export_stpc_meshes_from_bytes()."""
    return export_stpc_meshes_from_bytes(stpc_bin.read_bytes(), out_dir, **kwargs)


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(
        description="Experimental unpacker for Emperor's New Groove STPC static geometry blobs."
    )
    ap.add_argument("stpc_bin", type=Path, help="Path to stpc.bin")
    ap.add_argument("-o", "--out-dir", type=Path, default=Path("stpc_out"), help="Output directory")
    ap.add_argument("--alignment", type=int, default=4, help="Scan alignment. Use 1 for exhaustive scan.")
    ap.add_argument("--min-score", type=float, default=0.85, help="Minimum candidate validation score")
    ap.add_argument("--min-vertices", type=int, default=3)
    ap.add_argument("--max-vertices", type=int, default=20000)
    ap.add_argument("--max-triangles", type=int, default=50000)
    ap.add_argument("--scale", type=float, default=1.0, help="OBJ export scale")
    ap.add_argument("--flip-z", action="store_true", help="Flip Z axis in OBJ export")
    ap.add_argument("--no-combined", action="store_true", help="Do not write combined.obj")
    ap.add_argument("--no-mtl", action="store_true", help="Do not write placeholder OBJ material library")
    ap.add_argument("--debug-faces", action="store_true", help="Write faces_debug.csv")
    args = ap.parse_args(argv)

    buf = args.stpc_bin.read_bytes()

    top_count = u32(buf, 0) if len(buf) >= 4 else 0
    print(f"[STPC] file={args.stpc_bin}")
    print(f"[STPC] size={len(buf):,} bytes")
    print(f"[STPC] first_u32/top_count={top_count}")

    result = export_stpc_meshes_from_bytes(
        buf,
        args.out_dir,
        alignment=args.alignment,
        min_score=args.min_score,
        min_vertices=args.min_vertices,
        max_vertices=args.max_vertices,
        max_triangles=args.max_triangles,
        scale=args.scale,
        flip_z=args.flip_z,
        write_combined=not args.no_combined,
        write_debug=args.debug_faces,
        write_materials=not args.no_mtl,
        verbose=True,
    )

    print(f"[STPC] mesh candidates={len(result.meshes)}")
    if result.combined_obj_path is not None:
        print(f"[STPC] wrote {result.combined_obj_path}")
    if result.faces_debug_path is not None:
        print(f"[STPC] wrote {result.faces_debug_path}")
    print(f"[STPC] wrote {result.manifest_path}")

    if not result.meshes:
        print("[STPC] No meshes found. Try lowering --min-score, using --alignment 1, or increasing limits.")
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
