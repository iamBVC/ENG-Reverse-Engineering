"""
world_rebuild.py — confirmed TRAK/MAP/STPC world reconstruction exporter.

This module combines the parts of the WAD that are now structurally decoded:

    TRAK  -> terrain/world sector triangle geometry
    MAP   -> object placement records with confirmed 12.12 fixed-point XYZ
    STPC  -> mesh bank plus object-definition/script data

The important bridge is the MAP object field named stpc_object_def_offset in the
reverse-engineering notes.  At runtime the game converts it to:

    dword_6D9DBC + stpc_object_def_offset

where dword_6D9DBC is the raw STPC chunk base.  Many of those object-definition
records contain 32-bit values that match decoded STPC mesh-record offsets.

This exporter is deliberately conservative around unresolved STPC object-definition details:

* It only instances STPC meshes when an exact little-endian u32 match to a
  decoded mesh-record offset is found inside the object's STPC definition scan
  window.
* It uses the confirmed MAP object XYZ as translation.
* It applies the confirmed MAP tile placement/yaw to TRAK terrain.
* It applies the confirmed MAP object XYZ and the validated coordinate-basis fix
  to STPC object candidates.
* STPC object scale and full object-definition semantics are still unresolved;
  diagnostic CSV files preserve the raw fields used by the exporter.
"""

from __future__ import annotations

import csv
import json
import math
import shutil
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from .map_full_chunk import MapFullExe, MapObjectRecord
from .stpc_chunk import MeshCandidate, STPCExportResult
from .trak_chunk import TrakFile
from .text_chunk import TextChunk
from .material_chunk import RuntimeMaterial, parse_runtime_materials, copy_textures_for_world


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------

@dataclass
class WorldObjectInstance:
    """A MAP object placement converted to world units."""
    object_index: int
    stpc_def_offset: int
    world_x: float
    world_y: float
    world_z: float
    small_00: int
    small_04: int
    small_08: int
    field_16: int
    section2_index_or_sentinel: int
    field_1e: int
    field_22: int
    field_26_angle_candidate: int
    field_2a: int
    section4_index_or_sentinel: int
    field_32: int
    field_36: int
    field_38: int


@dataclass
class StpcMeshReferenceHit:
    """One exact mesh-offset reference found inside an STPC object definition."""
    object_index: int
    stpc_def_offset: int
    scan_start: int
    scan_end: int
    hit_file_offset: int
    hit_relative_offset: int
    mesh_index: int
    mesh_offset: int
    duplicate_index_for_object: int


@dataclass
class WorldRebuildResult:
    output_dir: Path
    object_instances: list[WorldObjectInstance]
    mesh_reference_hits: list[StpcMeshReferenceHit]
    unique_objects_with_hits: int
    unique_meshes_referenced: int
    combined_obj_path: Path | None
    terrain_obj_path: Path | None


# ---------------------------------------------------------------------------
# Small helpers
# ---------------------------------------------------------------------------

def _i32_from_u32(v: int) -> int:
    """Interpret an unsigned 32-bit integer as signed."""
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0]


def _fixed12(v: int) -> float:
    """Convert a MAP 12.12 fixed-point coordinate to float world units."""
    return _i32_from_u32(v) / 4096.0


def _angle4096_to_radians(v: int, *, sign: int = 1) -> float:
    """Convert the game's common 0..4095 angle unit to radians.

    MAP terrain tile definitions use values like 0, 1024, 2048, and 3072.
    That strongly indicates 4096 units per full turn.  Some object records use
    arbitrary values in the same range, so the same conversion is useful for
    object-yaw experiments.
    """
    return sign * ((v & 0xFFFF) / 4096.0) * (math.tau)


def _rotate_xz(x: float, z: float, angle_rad: float) -> tuple[float, float]:
    """Rotate an X/Z pair around the vertical Y axis."""
    c = math.cos(angle_rad)
    s = math.sin(angle_rad)
    return (x * c - z * s, x * s + z * c)


def _fixed12_signed_from_u32(v: int) -> float:
    """Alias used where exported CSV names should remind us values are signed."""
    return _fixed12(v)


def _hex(v: int) -> str:
    return f"0x{v:08X}"


def _write_csv(path: Path, fieldnames: list[str], rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            w.writerow(row)


def _obj_vertex_line(x: float, y: float, z: float, *, scale: float, flip_z: bool) -> str:
    z2 = -z if flip_z else z
    return f"v {x * scale:.9g} {y * scale:.9g} {z2 * scale:.9g}\n"


def _obj_normal_line(nx: float, ny: float, nz: float, *, flip_z: bool) -> str:
    nz2 = -nz if flip_z else nz
    return f"vn {nx:.9g} {ny:.9g} {nz2:.9g}\n"


def _write_marker_cross_obj(path: Path, instances: list[WorldObjectInstance], hits_by_object: dict[int, list[StpcMeshReferenceHit]], *, scale: float, flip_z: bool) -> None:
    """Write small cross markers at every MAP object position."""
    if instances:
        xs = [o.world_x for o in instances]
        ys = [o.world_y for o in instances]
        zs = [o.world_z for o in instances]
        span = max(max(xs)-min(xs), max(ys)-min(ys), max(zs)-min(zs), 1.0)
    else:
        span = 1.0
    s = span * 0.005
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Cross markers at confirmed MAP object XYZ positions.\n")
        f.write("# Objects with mesh-reference hits are named object_XXX_hits_N.\n")
        v = 1
        for o in instances:
            n_hits = len(hits_by_object.get(o.object_index, []))
            f.write(f"\no object_{o.object_index:03d}_hits_{n_hits}\n")
            pts = [
                (o.world_x-s, o.world_y, o.world_z), (o.world_x+s, o.world_y, o.world_z),
                (o.world_x, o.world_y-s, o.world_z), (o.world_x, o.world_y+s, o.world_z),
                (o.world_x, o.world_y, o.world_z-s), (o.world_x, o.world_y, o.world_z+s),
            ]
            for x, y, z in pts:
                f.write(_obj_vertex_line(x, y, z, scale=scale, flip_z=flip_z))
            f.write(f"l {v} {v+1}\n")
            f.write(f"l {v+2} {v+3}\n")
            f.write(f"l {v+4} {v+5}\n")
            v += 6


# ---------------------------------------------------------------------------
# Core extraction logic
# ---------------------------------------------------------------------------

def build_world_object_instances(mapx: MapFullExe) -> list[WorldObjectInstance]:
    """Convert MAP object records into confirmed world-position rows."""
    out: list[WorldObjectInstance] = []
    for o in mapx.objects:
        out.append(WorldObjectInstance(
            object_index=o.index,
            stpc_def_offset=o.name_or_string_offset,
            world_x=_fixed12(o.u32_16),
            world_y=_fixed12(o.u32_20),
            world_z=_fixed12(o.u32_24),
            small_00=o.small_00,
            small_04=o.small_04,
            small_08=o.small_08,
            field_16=o.u32_36,
            section2_index_or_sentinel=o.section2_index_or_sentinel,
            field_1e=o.u32_44,
            field_22=o.u32_48,
            field_26_angle_candidate=o.u32_52,
            field_2a=o.u32_56,
            section4_index_or_sentinel=o.section4_index_or_sentinel,
            field_32=o.u32_64,
            field_36=o.u16_68,
            field_38=o.u16_70,
        ))
    return out


def scan_stpc_definition_for_mesh_offsets(
    *,
    stpc_bytes: bytes,
    instances: list[WorldObjectInstance],
    meshes: list[MeshCandidate],
    scan_bytes: int = 2048,
    dedupe_per_object_mesh: bool = True,
) -> list[StpcMeshReferenceHit]:
    """Find exact u32 references to decoded STPC mesh-record offsets.

    The STPC object-definition format is still not fully decoded, so we do not
    parse opcodes yet.  We scan each object's definition window byte-by-byte for
    little-endian u32 values equal to one of the known mesh record offsets.  A
    byte-by-byte scan is intentional because object definitions are not always
    4-byte aligned.
    """
    mesh_by_offset = {m.offset: m for m in meshes}
    if not mesh_by_offset:
        return []

    hits: list[StpcMeshReferenceHit] = []
    for inst in instances:
        start = inst.stpc_def_offset
        if start < 0 or start >= len(stpc_bytes):
            continue
        end = min(len(stpc_bytes), start + max(0, scan_bytes))
        seen_meshes: set[int] = set()
        dup_index = 0
        # Need at least four bytes for a u32.
        for off in range(start, max(start, end - 3)):
            val = struct.unpack_from("<I", stpc_bytes, off)[0]
            mesh = mesh_by_offset.get(val)
            if mesh is None:
                continue
            if dedupe_per_object_mesh and mesh.index in seen_meshes:
                continue
            seen_meshes.add(mesh.index)
            hits.append(StpcMeshReferenceHit(
                object_index=inst.object_index,
                stpc_def_offset=inst.stpc_def_offset,
                scan_start=start,
                scan_end=end,
                hit_file_offset=off,
                hit_relative_offset=off - start,
                mesh_index=mesh.index,
                mesh_offset=mesh.offset,
                duplicate_index_for_object=dup_index,
            ))
            dup_index += 1
    return hits


# ---------------------------------------------------------------------------
# OBJ exporters
# ---------------------------------------------------------------------------


def _write_trak_record_instance_obj(
    f,
    record,
    *,
    name: str,
    tx: float,
    ty: float,
    tz: float,
    yaw_units: int = 0,
    yaw_sign: int = 1,
    terrain_z_mirror_center: float | None = None,
    scale: float,
    flip_z: bool,
    vertex_base: int,
    material_prefix: str = "trak_mat",
) -> int:
    """Append one MAP-placed TRAK record mesh to an open OBJ file.

    Important: TRAK Table A coordinates are local to a MAP tile/sector.  The
    MAP tile record supplies the translation that places the surface in the
    world.  The previous exporter wrote these local vertices directly, which is
    why every terrain sector appeared stacked around the origin.
    """
    if not record.table_a or not record.table_b:
        return vertex_base
    f.write(f"\no {name}\n")
    yaw = _angle4096_to_radians(yaw_units, sign=yaw_sign) if yaw_units else 0.0
    f.write(f"# TRAK record {record.index}; MAP tile translation={tx:.9g},{ty:.9g},{tz:.9g}; yaw_units={yaw_units}; yaw_sign={yaw_sign}; terrain_z_mirror_center={terrain_z_mirror_center}\n")
    for v in record.table_a:
        rx, rz = _rotate_xz(v.x, v.z, yaw) if yaw else (v.x, v.z)
        raw_z = tz + rz
        out_z = (2.0 * terrain_z_mirror_center - raw_z) if terrain_z_mirror_center is not None else raw_z
        f.write(_obj_vertex_line(tx + rx, ty + v.y, out_z, scale=scale, flip_z=flip_z))
    for v in record.table_a:
        rnx, rnz = _rotate_xz(v.nx, v.nz, yaw) if yaw else (v.nx, v.nz)
        if terrain_z_mirror_center is not None:
            rnz = -rnz
        f.write(_obj_normal_line(rnx, v.ny, rnz, flip_z=flip_z))
    current_mat = None
    for tri in record.table_b:
        if not (tri.i0 < record.a_count and tri.i1 < record.a_count and tri.i2 < record.a_count):
            continue
        if len({tri.i0, tri.i1, tri.i2}) != 3:
            continue
        if tri.material_index != current_mat:
            current_mat = tri.material_index
            f.write(f"usemtl {material_prefix}_{current_mat:04d}\n")
        a = vertex_base + tri.i0
        b = vertex_base + tri.i1
        c = vertex_base + tri.i2
        f.write(f"f {a}//{a} {b}//{b} {c}//{c}\n")
    return vertex_base + record.a_count


def write_map_placed_trak_terrain_obj(
    *,
    path: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    write_per_tile_dir: Path | None = None,
) -> tuple[Path, int, int]:
    """Write world-placed terrain by applying MAP tile XYZ to TRAK meshes.

    MAP has one tile record per terrain tile and a parallel
    tile_trak_record_index array.  The TRAK record gives the local surface mesh;
    the MAP tile's x/y/z gives the world placement.  This is currently the best
    confirmed terrain reconstruction path.
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    placed = 0
    skipped = 0

    # Compute the raw terrain Z center before writing.  A simple sign flip around
    # world origin can separate terrain from MAP/STPC objects.  The visual
    # validation showed the terrain should instead be mirrored inside its own
    # world bounds.
    z_min = None
    z_max = None
    if mirror_terrain_z:
        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                continue
            rec = trak.records[rec_i]
            if not rec.table_a:
                continue
            if tile_i < len(mapx.tile_defs):
                td = mapx.tile_defs[tile_i]
                tz0 = -_fixed12_signed_from_u32(td.u32_24)
                yaw_units0 = td.u32_04 & 0xFFFF
            else:
                tz0 = tile.z
                yaw_units0 = 0
            yaw0 = _angle4096_to_radians(yaw_units0, sign=terrain_yaw_sign) if yaw_units0 else 0.0
            for vv in rec.table_a:
                _, rz0 = _rotate_xz(vv.x, vv.z, yaw0) if yaw0 else (vv.x, vv.z)
                zz = tz0 + rz0
                z_min = zz if z_min is None else min(z_min, zz)
                z_max = zz if z_max is None else max(z_max, zz)
    terrain_z_mirror_center = ((z_min + z_max) * 0.5) if (mirror_terrain_z and z_min is not None and z_max is not None) else None

    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# World-placed TRAK terrain.  Each MAP tile translates one TRAK record mesh.\n")
        f.write("# Terrain Z is mirrored around the terrain center by default so it matches the validated MAP/STPC object coordinate basis without moving the level away from its original bounds.\n")
        vbase = 1
        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                skipped += 1
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                skipped += 1
                continue
            rec = trak.records[rec_i]
            before = vbase
            name = f"map_tile_{tile_i:04d}_trak_{rec_i:03d}"
            # The tile definition stores the same placement as 12.12 fixed
            # point plus a 4096-unit yaw.  The first tile table stores XYZ as
            # floats and the yaw bits as a denormal-looking float; using the
            # tile definition avoids that misleading float interpretation.
            if tile_i < len(mapx.tile_defs):
                td = mapx.tile_defs[tile_i]
                tx = _fixed12_signed_from_u32(td.u32_16)
                ty = _fixed12_signed_from_u32(td.u32_20)
                tz = -_fixed12_signed_from_u32(td.u32_24)
                yaw_units = td.u32_04 & 0xFFFF
            else:
                tx, ty, tz = tile.x, tile.y, tile.z
                yaw_units = int(tile.unk_float) if isinstance(tile.unk_float, int) else 0
            vbase = _write_trak_record_instance_obj(
                f, rec, name=name, tx=tx, ty=ty, tz=tz, yaw_units=yaw_units, yaw_sign=terrain_yaw_sign,
                terrain_z_mirror_center=terrain_z_mirror_center, scale=scale, flip_z=flip_z, vertex_base=vbase,
            )
            if vbase != before:
                placed += 1
            else:
                skipped += 1
    if write_per_tile_dir is not None:
        write_per_tile_dir.mkdir(parents=True, exist_ok=True)
        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                continue
            rec = trak.records[rec_i]
            if not rec.table_a or not rec.table_b:
                continue
            if tile_i < len(mapx.tile_defs):
                td = mapx.tile_defs[tile_i]
                tx = _fixed12_signed_from_u32(td.u32_16)
                ty = _fixed12_signed_from_u32(td.u32_20)
                tz = -_fixed12_signed_from_u32(td.u32_24)
                yaw_units = td.u32_04 & 0xFFFF
            else:
                tx, ty, tz, yaw_units = tile.x, tile.y, tile.z, 0
            one = write_per_tile_dir / f"tile_{tile_i:04d}_trak_{rec_i:03d}_yaw_{yaw_units:04d}.obj"
            with one.open("w", encoding="utf-8", newline="\n") as f:
                f.write("mtllib ../world.mtl\n")
                _write_trak_record_instance_obj(
                    f, rec, name=f"tile_{tile_i:04d}_trak_{rec_i:03d}",
                    tx=tx, ty=ty, tz=tz, yaw_units=yaw_units, yaw_sign=terrain_yaw_sign,
                    terrain_z_mirror_center=terrain_z_mirror_center, scale=scale, flip_z=flip_z, vertex_base=1,
                )
    return path, placed, skipped

def _write_instanced_mesh_obj(
    f,
    mesh: MeshCandidate,
    inst: WorldObjectInstance,
    *,
    object_name: str,
    scale: float,
    flip_z: bool,
    vertex_base: int,
    object_z_sign: int = -1,
    local_z_sign: int = -1,
    apply_object_yaw: bool = True,
    object_yaw_sign: int = 1,
    object_z_mirror_center: float | None = None,
    object_x_offset: float = 0.0,
    object_y_offset: float = 0.0,
    object_z_offset: float = 0.0,
) -> int:
    """Append one STPC mesh instance to an open OBJ file.

    Append one STPC mesh instance to an open OBJ file.

    Important coordinate note: after visual validation, terrain.obj is the
    reference orientation.  MAP object positions are still correct in magnitude
    but need the same centered Z-space mirror as the terrain/object basis when
    written into the combined world.  object_z_mirror_center mirrors the whole
    transformed STPC vertex around the level's Z center, preserving level bounds
    while correcting the left/right mirrored placement.
    """
    f.write(f"\no {object_name}\n")
    f.write(f"# MAP object {inst.object_index}; STPC mesh {mesh.index}; mesh_offset=0x{mesh.offset:08X}\n")
    f.write(f"# raw_translation={inst.world_x:.9g},{inst.world_y:.9g},{inst.world_z:.9g}; render_z_sign={object_z_sign}; local_z_sign={local_z_sign}; object_yaw={inst.small_04 if apply_object_yaw else 0}; object_z_mirror_center={object_z_mirror_center}; object_alignment_offset={object_x_offset:.9g},{object_y_offset:.9g},{object_z_offset:.9g}\n")
    yaw = _angle4096_to_radians(inst.small_04, sign=object_yaw_sign) if apply_object_yaw else 0.0
    base_x = inst.world_x
    base_y = inst.world_y
    base_z = object_z_sign * inst.world_z
    mirror_object_z = object_z_mirror_center is not None
    for v in mesh.vertices:
        lx = v.x
        lz = local_z_sign * v.z
        rx, rz = _rotate_xz(lx, lz, yaw) if yaw else (lx, lz)
        out_x = base_x + rx
        out_y = base_y + v.y
        out_z = base_z + rz
        if mirror_object_z:
            out_z = 2.0 * object_z_mirror_center - out_z
        # Final user-tunable alignment correction. This is deliberately applied
        # after all source-coordinate conversion/mirroring so it behaves like a
        # simple world-space nudge against the validated terrain.obj.
        out_x += object_x_offset
        out_y += object_y_offset
        out_z += object_z_offset
        f.write(_obj_vertex_line(out_x, out_y, out_z, scale=scale, flip_z=flip_z))
    for v in mesh.vertices:
        nx = v.nx
        nz = local_z_sign * v.nz
        rnx, rnz = _rotate_xz(nx, nz, yaw) if yaw else (nx, nz)
        if mirror_object_z:
            rnz = -rnz
        f.write(_obj_normal_line(rnx, v.ny, rnz, flip_z=flip_z))
    current_mat: int | None = None
    for tri in mesh.triangles:
        if not (tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count):
            continue
        if len({tri.i0, tri.i1, tri.i2}) != 3:
            continue
        if tri.material != current_mat:
            current_mat = tri.material
            f.write(f"usemtl stpc_mat_{current_mat:04d}\n")
        a = vertex_base + tri.i0
        b = vertex_base + tri.i1
        c = vertex_base + tri.i2
        f.write(f"f {a}//{a} {b}//{b} {c}//{c}\n")
    return vertex_base + mesh.vertex_count


def write_instanced_stpc_objs(
    *,
    out_dir: Path,
    instances: list[WorldObjectInstance],
    hits: list[StpcMeshReferenceHit],
    meshes: list[MeshCandidate],
    scale: float = 1.0,
    flip_z: bool = False,
    write_per_object: bool = False,
    object_z_sign: int = -1,
    local_z_sign: int = -1,
    apply_object_yaw: bool = True,
    object_yaw_sign: int = 1,
    object_z_mirror_center: float | None = None,
    object_x_offset: float = 0.0,
    object_y_offset: float = 0.0,
    object_z_offset: float = 0.0,
) -> Path | None:
    """Write combined and single-hit STPC instance OBJ files.

    Earlier builds wrote one OBJ per MAP object, but each object can currently
    have several mesh-reference hits because the STPC object-definition language
    is still being decoded.  That made those files look like multiple unrelated
    meshes merged together.

    This version always writes:
      * objects_all_candidates.obj  — all candidate hits together
      * objects_by_hit/*.obj        — exactly one mesh per file
      * objects_primary.obj         — only the first/earliest hit per object

    If write_per_object is true it also writes grouped files for comparison in
    diagnostics/objects_grouped_by_object/, but those are explicitly named grouped.
    """
    if not hits:
        return None
    out_dir.mkdir(parents=True, exist_ok=True)
    by_object = {o.object_index: o for o in instances}
    by_mesh = {m.index: m for m in meshes}

    # Combined file: one object/group per MAP-object/mesh-hit pair.
    combined = out_dir / "objects_all_candidates.obj"
    with combined.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# STPC meshes translated to confirmed MAP object XYZ.\n")
        f.write("# Coordinate-basis fix and experimental yaw are applied; scale is still unresolved.\n")
        vbase = 1
        for hit in hits:
            inst = by_object.get(hit.object_index)
            mesh = by_mesh.get(hit.mesh_index)
            if inst is None or mesh is None:
                continue
            name = f"object_{inst.object_index:03d}_mesh_{mesh.index:03d}_hit_{hit.duplicate_index_for_object:02d}"
            vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset)

    # Single-hit files: exactly one STPC mesh per OBJ file.
    by_hit_dir = out_dir / "objects_by_hit"
    by_hit_dir.mkdir(parents=True, exist_ok=True)
    for hit in hits:
        inst = by_object.get(hit.object_index)
        mesh = by_mesh.get(hit.mesh_index)
        if inst is None or mesh is None:
            continue
        path = by_hit_dir / f"object_{inst.object_index:03d}_hit_{hit.duplicate_index_for_object:02d}_mesh_{mesh.index:03d}.obj"
        with path.open("w", encoding="utf-8", newline="\n") as f:
            f.write("mtllib ../world.mtl\n")
            _write_instanced_mesh_obj(
                f, mesh, inst,
                object_name=f"object_{inst.object_index:03d}_hit_{hit.duplicate_index_for_object:02d}_mesh_{mesh.index:03d}",
                scale=scale, flip_z=flip_z, vertex_base=1,
                object_z_sign=object_z_sign, local_z_sign=local_z_sign,
                apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign,
                object_z_mirror_center=object_z_mirror_center,
                object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset,
            )

    # Primary-only file: first/earliest hit per object.  This is often the most
    # useful visual probe while the STPC object-definition script is unknown.
    first_by_object: dict[int, StpcMeshReferenceHit] = {}
    for hit in sorted(hits, key=lambda h: (h.object_index, h.hit_relative_offset, h.mesh_index)):
        first_by_object.setdefault(hit.object_index, hit)
    primary = out_dir / "objects_primary.obj"
    with primary.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# One earliest mesh-reference hit per MAP object.\n")
        vbase = 1
        for object_index, hit in sorted(first_by_object.items()):
            inst = by_object.get(object_index)
            mesh = by_mesh.get(hit.mesh_index)
            if inst is None or mesh is None:
                continue
            name = f"object_{object_index:03d}_primary_mesh_{mesh.index:03d}"
            vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset)

    if write_per_object:
        grouped_dir = out_dir / "diagnostics" / "objects_grouped_by_object"
        grouped_dir.mkdir(parents=True, exist_ok=True)
        hits_by_object: dict[int, list[StpcMeshReferenceHit]] = {}
        for h in hits:
            hits_by_object.setdefault(h.object_index, []).append(h)
        for object_index, obj_hits in sorted(hits_by_object.items()):
            inst = by_object.get(object_index)
            if inst is None:
                continue
            path = grouped_dir / f"object_{object_index:03d}_all_candidate_hits.obj"
            with path.open("w", encoding="utf-8", newline="\n") as f:
                f.write("mtllib ../../world.mtl\n")
                f.write(f"# GROUPED candidate STPC hits for MAP object {object_index}.\n")
                f.write("# This may intentionally contain multiple meshes; use objects_by_hit/ for singular meshes.\n")
                f.write(f"# position={inst.world_x:.9g},{inst.world_y:.9g},{inst.world_z:.9g}\n")
                vbase = 1
                for hit in sorted(obj_hits, key=lambda h: (h.hit_relative_offset, h.mesh_index)):
                    mesh = by_mesh.get(hit.mesh_index)
                    if mesh is None:
                        continue
                    name = f"object_{object_index:03d}_mesh_{mesh.index:03d}_hit_{hit.duplicate_index_for_object:02d}"
                    vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset)
    return combined




def _obj_bounds_z(path: Path) -> tuple[float | None, float | None]:
    """Return min/max unscaled OBJ Z coordinate from vertex lines in an OBJ file."""
    if not path.exists():
        return None, None
    z_min = None
    z_max = None
    with path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            if not line.startswith("v "):
                continue
            parts = line.split()
            if len(parts) < 4:
                continue
            try:
                z = float(parts[3])
            except ValueError:
                continue
            z_min = z if z_min is None else min(z_min, z)
            z_max = z if z_max is None else max(z_max, z)
    return z_min, z_max

def write_world_combined_obj(world_dir: Path, *, include_terrain: bool = True) -> Path | None:
    """Create a tiny OBJ wrapper that references terrain and instance geometry.

    OBJ cannot include other OBJ files, so this function concatenates the two
    generated OBJs when both exist.  It rewrites face indices while copying the
    second file to keep the combined OBJ valid.
    """
    terrain = world_dir / "terrain.obj"
    inst = world_dir / "objects_all_candidates.obj"
    if not inst.exists() and not terrain.exists():
        return None
    out = world_dir / "combined.obj"

    vertex_offset = 0
    normal_offset = 0

    def copy_obj(src: Path, dst, *, add_offsets: bool) -> tuple[int, int]:
        nonlocal vertex_offset, normal_offset
        local_v = 0
        local_n = 0
        for line in src.read_text(encoding="utf-8", errors="replace").splitlines():
            if line.startswith("mtllib"):
                continue
            if line.startswith("v "):
                local_v += 1
                dst.write(line + "\n")
            elif line.startswith("vn "):
                local_n += 1
                dst.write(line + "\n")
            elif line.startswith("f ") and add_offsets:
                parts = line.split()[1:]
                new_parts = []
                for p in parts:
                    bits = p.split("/")
                    # Supports v//n emitted by our exporters.
                    vi = int(bits[0]) + vertex_offset
                    if len(bits) >= 3 and bits[2]:
                        ni = int(bits[2]) + normal_offset
                        new_parts.append(f"{vi}//{ni}")
                    else:
                        new_parts.append(str(vi))
                dst.write("f " + " ".join(new_parts) + "\n")
            else:
                dst.write(line + "\n")
        vertex_offset += local_v
        normal_offset += local_n
        return local_v, local_n

    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write("# Combined reconstructed world: TRAK terrain + translated STPC object candidates.\n")
        if include_terrain and terrain.exists():
            f.write("\no terrain\n")
            copy_obj(terrain, f, add_offsets=True)
        if inst.exists():
            f.write("\n# --- STPC translated candidate instances ---\n")
            copy_obj(inst, f, add_offsets=True)
    return out


TERRAIN_TEXTURE_REMAP_VARIANTS = (
    "direct",
    "shift_p1",
    "shift_m1",
    "shift_p2",
    "shift_m2",
    "shift_p3",
    "shift_m3",
    "shift_p4",
    "shift_m4",
    "shift_p5",
    "shift_m5",
    "shift_p8",
    "shift_m8",
    "terrain_05_09_mod_raw",
    "terrain_05_09_mod_raw_minus3",
    "material_index_mod_texture_count",
    "material_index_05_09_mod",
)


def _remap_texture_index(
    *,
    material_index: int,
    raw_texture_index: int,
    texture_count: int,
    mode: str = "direct",
) -> int | None:
    """Map a runtime material texture-page id to an exported TEXT PNG index.

    The EXE-proven field at runtime material +0x02 indexes dword_58114C, the
    runtime texture-page table.  The first probe assumed that this page id was
    identical to the raw TEXT record index.  Visual feedback shows that this may
    be wrong, so the exporter can now write controlled remap variants without
    changing geometry or UV rectangles.
    """
    if texture_count <= 0:
        return None

    raw = raw_texture_index & 0xFF
    if mode == "direct":
        mapped = raw
    elif mode.startswith("shift_p"):
        mapped = raw + int(mode.removeprefix("shift_p"))
    elif mode.startswith("shift_m"):
        mapped = raw - int(mode.removeprefix("shift_m"))
    elif mode == "terrain_05_09_mod_raw":
        mapped = 5 + (raw % 5)
    elif mode == "terrain_05_09_mod_raw_minus3":
        mapped = 5 + ((raw - 3) % 5)
    elif mode == "material_index_mod_texture_count":
        mapped = material_index
    elif mode == "material_index_05_09_mod":
        mapped = 5 + (material_index % 5)
    else:
        mapped = raw

    # Direct mode preserves invalid ids as missing texture paths so bad data is
    # visible in diagnostics.  Experimental remap modes wrap to available PNGs.
    if mode == "direct":
        return mapped if 0 <= mapped < texture_count else None
    return mapped % texture_count


def write_world_mtl(
    path: Path,
    materials: list[RuntimeMaterial] | None = None,
    *,
    texture_prefix: str = "textures",
    texture_count: int | None = None,
    texture_remap_mode: str = "direct",
) -> None:
    """Write world materials.

    The ordinary terrain/object OBJs still use simple diffuse colours.  When a
    material table is available, we also emit map_Kd bindings for material names
    used by the textured terrain probe.

    ``texture_remap_mode`` is intentionally diagnostic.  The executable shows
    material +0x02 indexes the runtime page table dword_58114C; it may not be a
    direct TEXT-record number.
    """
    mat_by_i = {m.index: m for m in (materials or [])}
    if texture_count is None:
        texture_count = 256
    with path.open("w", encoding="utf-8") as f:
        f.write("# Materials for reconstructed WAD world exports.\n")
        f.write(f"# texture_remap_mode={texture_remap_mode}\n")
        f.write("newmtl trak_surface\nKd 0.55 0.55 0.55\nKa 0 0 0\n\n")
        f.write("newmtl stpc_mat_default\nKd 0.75 0.75 0.75\nKa 0 0 0\n\n")
        # A broad set is enough for most material ids without bloating too much.
        for i in range(1024):
            m = mat_by_i.get(i)
            shade = 0.25 + ((i * 37) % 100) / 160.0
            f.write(f"newmtl stpc_mat_{i:04d}\nKd {shade:.3f} {min(1.0, shade+0.12):.3f} {max(0.0, shade-0.08):.3f}\nKa 0 0 0\n")
            if m is not None and not m.is_color_only:
                tex_i = _remap_texture_index(material_index=i, raw_texture_index=m.texture_index, texture_count=texture_count, mode=texture_remap_mode)
                f.write(f"# raw_texture_page={m.texture_index} remapped_texture={tex_i} rect={m.x0},{m.y0}..{m.x1},{m.y1} flags=0x{m.flags:04X}\n")
            f.write("\n")
            f.write(f"newmtl trak_mat_{i:04d}\nKd {shade:.3f} {shade:.3f} {shade:.3f}\nKa 0 0 0\n")
            if m is not None and not m.is_color_only:
                tex_i = _remap_texture_index(material_index=i, raw_texture_index=m.texture_index, texture_count=texture_count, mode=texture_remap_mode)
                if tex_i is not None:
                    f.write(f"map_Kd {texture_prefix}/texture_{tex_i:02d}.png\n")
                f.write(f"# raw_texture_page={m.texture_index} remapped_texture={tex_i} material_rect_texels={m.x0},{m.y0},{m.x1},{m.y1} flags=0x{m.flags:04X}\n")
            f.write("\n")




TERRAIN_UV_VARIANTS = (
    "default",
    "flip_u",
    "flip_v",
    "flip_uv",
    "rot90_cw",
    "rot90_ccw",
    "rot180",
    "diag_alt",
)

# Deeper UV probes.  The first set chooses one of the four possible right-triangle
# halves inside the material rectangle.  The second set lets TRAK/material bits
# select the half per face.  The last two derive UVs from the triangle's local
# X/Z shape, which is useful if the game projects terrain UVs rather than using
# a fixed corner ordering.
TERRAIN_UV_DEEP_TESTS = (
    "rect_tl_tr_bl",
    "rect_tr_br_bl",
    "rect_tl_br_bl",
    "rect_tl_tr_br",
    "flags_low2_rect",
    "unknown_low2_rect",
    "material_flags_2_3_rect",
    "material_flags_3_4_rect",
    "vertex_xz_bbox",
    "vertex_zx_bbox",
)


def _apply_terrain_uv_variant(
    uvs: tuple[tuple[float, float], tuple[float, float], tuple[float, float]],
    variant: str,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return one experimental UV corner-order variant.

    The EXE confirms which texture page and rectangle each material uses, but
    the terrain triangle records still need one final corner-order convention.
    These variants keep the same confirmed rectangle and only change which
    corner is assigned to each triangle vertex.
    """
    a, b, c = uvs
    if variant == "default":
        return (a, b, c)
    if variant == "flip_u":
        return (b, a, c)
    if variant == "flip_v":
        return (c, b, a)
    if variant == "flip_uv":
        return (b, c, a)
    if variant == "rot90_cw":
        return (c, a, b)
    if variant == "rot90_ccw":
        return (b, c, a)
    if variant == "rot180":
        return (c, a, b)
    if variant == "diag_alt":
        return (a, c, b)
    return (a, b, c)

def _uv_rect_corners(
    mat: RuntimeMaterial | None,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return material rectangle corners as TL, TR, BL, BR in OBJ UV space."""
    if mat is None or mat.is_color_only:
        u0, u1, v0, v1 = 0.0, 1.0, 0.0, 1.0
    else:
        u0, u1, v0, v1 = mat.uv_rect(tex_w, tex_h)
    if flip_v_for_obj:
        v0, v1 = 1.0 - v0, 1.0 - v1
    tl = (u0, v0)
    tr = (u1, v0)
    bl = (u0, v1)
    br = (u1, v1)
    return tl, tr, bl, br


def _rect_half_uvs(
    mat: RuntimeMaterial | None,
    selector: int,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Choose one of four triangle halves of the material rectangle."""
    tl, tr, bl, br = _uv_rect_corners(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    choices = (
        (tl, tr, bl),  # upper/left half
        (tr, br, bl),  # lower/right half sharing TR-BL diagonal
        (tl, br, bl),  # lower/left half sharing TL-BR diagonal
        (tl, tr, br),  # upper/right half sharing TL-BR diagonal
    )
    return choices[selector & 3]


def _geometry_projected_uvs(
    rec,
    tri,
    mat: RuntimeMaterial | None,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
    swap_axes: bool = False,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Map triangle local X/Z extents into the material rectangle.

    This is diagnostic only.  If a geometry-projected probe looks better than
    fixed rectangle halves, the game is probably deriving terrain UVs from a
    projection or from additional per-vertex fields we have not decoded yet.
    """
    tl, tr, bl, br = _uv_rect_corners(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    u_min, v_top = tl
    u_max, _ = tr
    _, v_bottom = bl
    verts = [rec.table_a[tri.i0], rec.table_a[tri.i1], rec.table_a[tri.i2]]
    a_vals = [v.z if swap_axes else v.x for v in verts]
    b_vals = [v.x if swap_axes else v.z for v in verts]
    amin, amax = min(a_vals), max(a_vals)
    bmin, bmax = min(b_vals), max(b_vals)
    da = (amax - amin) or 1.0
    db = (bmax - bmin) or 1.0
    out = []
    for av, bv in zip(a_vals, b_vals):
        u = u_min + ((av - amin) / da) * (u_max - u_min)
        v = v_bottom + ((bv - bmin) / db) * (v_top - v_bottom)
        out.append((u, v))
    return tuple(out)  # type: ignore[return-value]


def _material_uvs_for_triangle(
    mat: RuntimeMaterial | None,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
    variant: str = "default",
    tri=None,
    rec=None,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return a per-triangle UV assignment for a material rectangle.

    ``default`` preserves the old probe.  Additional variants test whether TRAK
    face flags, the unknown triangle u16, material flags, or local X/Z geometry
    choose the triangle half/orientation inside the material rectangle.
    """
    # Historical default used by terrain_textured_probe.obj.
    tl, tr, bl, br = _uv_rect_corners(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    base = (bl, br, tl)

    if variant in TERRAIN_UV_VARIANTS:
        return _apply_terrain_uv_variant(base, variant)

    if variant == "rect_tl_tr_bl":
        return (tl, tr, bl)
    if variant == "rect_tr_br_bl":
        return (tr, br, bl)
    if variant == "rect_tl_br_bl":
        return (tl, br, bl)
    if variant == "rect_tl_tr_br":
        return (tl, tr, br)
    if variant == "flags_low2_rect" and tri is not None:
        return _rect_half_uvs(mat, tri.flags & 3, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    if variant == "unknown_low2_rect" and tri is not None:
        return _rect_half_uvs(mat, tri.unknown & 3, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    if variant == "material_flags_2_3_rect" and mat is not None:
        return _rect_half_uvs(mat, (mat.flags >> 2) & 3, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    if variant == "material_flags_3_4_rect" and mat is not None:
        return _rect_half_uvs(mat, (mat.flags >> 3) & 3, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    if variant == "vertex_xz_bbox" and tri is not None and rec is not None:
        return _geometry_projected_uvs(rec, tri, mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj, swap_axes=False)
    if variant == "vertex_zx_bbox" and tri is not None and rec is not None:
        return _geometry_projected_uvs(rec, tri, mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj, swap_axes=True)

    return base


def write_textured_terrain_probe_obj(
    *,
    path: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    materials: list[RuntimeMaterial],
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    uv_variant: str = "default",
    mtl_name: str = "world.mtl",
) -> Path:
    """Write a first textured-terrain OBJ probe using confirmed material rects.

    This is intentionally separate from terrain.obj.  terrain.obj is the trusted
    geometry export; terrain_textured_probe.obj is for validating material/UV
    binding.  The texture page and UV rectangle are confirmed from sub_407240;
    per-face UV corner orientation is still experimental.
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    mat_by_i = {m.index: m for m in materials}

    z_min = None
    z_max = None
    if mirror_terrain_z:
        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                continue
            rec = trak.records[rec_i]
            if not rec.table_a:
                continue
            if tile_i < len(mapx.tile_defs):
                td = mapx.tile_defs[tile_i]
                tz0 = -_fixed12_signed_from_u32(td.u32_24)
                yaw_units0 = td.u32_04 & 0xFFFF
            else:
                tz0 = tile.z
                yaw_units0 = 0
            yaw0 = _angle4096_to_radians(yaw_units0, sign=terrain_yaw_sign) if yaw_units0 else 0.0
            for vv in rec.table_a:
                _, rz0 = _rotate_xz(vv.x, vv.z, yaw0) if yaw0 else (vv.x, vv.z)
                zz = tz0 + rz0
                z_min = zz if z_min is None else min(z_min, zz)
                z_max = zz if z_max is None else max(z_max, zz)
    terrain_z_mirror_center = ((z_min + z_max) * 0.5) if (mirror_terrain_z and z_min is not None and z_max is not None) else None

    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write(f"mtllib {mtl_name}\n")
        f.write("# Textured terrain probe. Texture page + material rectangle are EXE-confirmed.\n")
        f.write(f"# UV variant: {uv_variant}\n")
        f.write("# Per-triangle UV corner orientation is still experimental.\n")
        vbase = 1
        vtbase = 1
        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                continue
            rec = trak.records[rec_i]
            if not rec.table_a or not rec.table_b:
                continue
            if tile_i < len(mapx.tile_defs):
                td = mapx.tile_defs[tile_i]
                tx = _fixed12_signed_from_u32(td.u32_16)
                ty = _fixed12_signed_from_u32(td.u32_20)
                tz = -_fixed12_signed_from_u32(td.u32_24)
                yaw_units = td.u32_04 & 0xFFFF
            else:
                tx, ty, tz = tile.x, tile.y, tile.z
                yaw_units = 0
            yaw = _angle4096_to_radians(yaw_units, sign=terrain_yaw_sign) if yaw_units else 0.0
            f.write(f"\no textured_map_tile_{tile_i:04d}_trak_{rec_i:03d}\n")
            for v in rec.table_a:
                rx, rz = _rotate_xz(v.x, v.z, yaw) if yaw else (v.x, v.z)
                raw_z = tz + rz
                out_z = (2.0 * terrain_z_mirror_center - raw_z) if terrain_z_mirror_center is not None else raw_z
                f.write(_obj_vertex_line(tx + rx, ty + v.y, out_z, scale=scale, flip_z=flip_z))
            for v in rec.table_a:
                rnx, rnz = _rotate_xz(v.nx, v.nz, yaw) if yaw else (v.nx, v.nz)
                if terrain_z_mirror_center is not None:
                    rnz = -rnz
                f.write(_obj_normal_line(rnx, v.ny, rnz, flip_z=flip_z))
            current_mat = None
            for tri in rec.table_b:
                if not (tri.i0 < rec.a_count and tri.i1 < rec.a_count and tri.i2 < rec.a_count):
                    continue
                if len({tri.i0, tri.i1, tri.i2}) != 3:
                    continue
                mat = mat_by_i.get(tri.material_index)
                if tri.material_index != current_mat:
                    current_mat = tri.material_index
                    f.write(f"usemtl trak_mat_{current_mat:04d}\n")
                tex_w = tex_h = 256
                uvs = _material_uvs_for_triangle(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=True, variant=uv_variant, tri=tri, rec=rec)
                for u, v in uvs:
                    f.write(f"vt {u:.9g} {v:.9g}\n")
                a = vbase + tri.i0
                b = vbase + tri.i1
                c = vbase + tri.i2
                f.write(f"f {a}/{vtbase}/{a} {b}/{vtbase+1}/{b} {c}/{vtbase+2}/{c}\n")
                vtbase += 3
            vbase += rec.a_count
    return path



def write_terrain_uv_variant_objs(
    *,
    out_dir: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    materials: list[RuntimeMaterial],
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    texture_count: int = 0,
    texture_remap_mode: str = "direct",
) -> Path:
    """Write textured terrain OBJ variants with working MTL/PNG paths.

    Earlier variant exports reused a parent MTL path.  Many OBJ viewers resolve
    ``map_Kd`` paths relative to the OBJ, not the MTL, so the textures could
    appear missing even though the OBJ had vt/usemtl records.  This folder gets
    its own MTL whose texture paths are explicitly relative to the variant OBJ
    files: ``../textures/texture_XX.png``.
    """
    variants_dir = out_dir / "terrain_uv_variants"
    variants_dir.mkdir(parents=True, exist_ok=True)

    # Keep the variant folder self-contained.  Some OBJ viewers resolve map_Kd
    # relative to the OBJ, some relative to the MTL, and some reject parent
    # directory references such as ../textures entirely.  The working
    # terrain_textured_probe.obj lives beside world.mtl and uses
    # textures/texture_XX.png, so mirror that layout here: each variant folder
    # gets its own textures/ directory and MTL entries that never leave the
    # folder.
    copy_textures_for_world(out_dir / "textures", variants_dir / "textures")
    write_world_mtl(variants_dir / "world_uv_variants.mtl", materials, texture_prefix="textures", texture_count=texture_count, texture_remap_mode=texture_remap_mode)

    rows = []
    for variant in TERRAIN_UV_VARIANTS:
        obj_path = variants_dir / f"terrain_textured_{variant}.obj"
        write_textured_terrain_probe_obj(
            path=obj_path,
            mapx=mapx,
            trak=trak,
            materials=materials,
            scale=scale,
            flip_z=flip_z,
            terrain_yaw_sign=terrain_yaw_sign,
            mirror_terrain_z=mirror_terrain_z,
            uv_variant=variant,
            mtl_name="world_uv_variants.mtl",
        )
        rows.append({
            "variant": variant,
            "obj": obj_path.name,
            "mtl": "world_uv_variants.mtl",
            "texture_path_style": "textures/texture_XX.png",
        })

    _write_csv(variants_dir / "uv_variants.csv", ["variant", "obj", "mtl", "texture_path_style"], rows)
    return variants_dir


def write_terrain_uv_deep_test_objs(
    *,
    out_dir: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    materials: list[RuntimeMaterial],
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    texture_count: int = 0,
    texture_remap_mode: str = "direct",
) -> Path:
    """Write a second, stronger UV diagnostic set.

    These tests do not change material texture pages.  They only vary how each
    terrain triangle chooses a sub-rectangle corner order.  The set includes
    fixed rectangle halves, TRAK flag-driven selection, material-flag-driven
    selection, and local X/Z projection tests.
    """
    deep_dir = out_dir / "terrain_uv_deep_tests"
    deep_dir.mkdir(parents=True, exist_ok=True)
    copy_textures_for_world(out_dir / "textures", deep_dir / "textures")
    write_world_mtl(
        deep_dir / "world_uv_deep_tests.mtl",
        materials,
        texture_prefix="textures",
        texture_count=texture_count,
        texture_remap_mode=texture_remap_mode,
    )

    rows = []
    for variant in TERRAIN_UV_DEEP_TESTS:
        obj_path = deep_dir / f"terrain_textured_{variant}.obj"
        write_textured_terrain_probe_obj(
            path=obj_path,
            mapx=mapx,
            trak=trak,
            materials=materials,
            scale=scale,
            flip_z=flip_z,
            terrain_yaw_sign=terrain_yaw_sign,
            mirror_terrain_z=mirror_terrain_z,
            uv_variant=variant,
            mtl_name="world_uv_deep_tests.mtl",
        )
        rows.append({
            "variant": variant,
            "obj": obj_path.name,
            "mtl": "world_uv_deep_tests.mtl",
            "texture_remap_mode": texture_remap_mode,
            "notes": "direct texture pages; only UV selection/orientation changes",
        })

    _write_csv(deep_dir / "uv_deep_tests.csv", ["variant", "obj", "mtl", "texture_remap_mode", "notes"], rows)
    (deep_dir / "README_uv_deep_tests.txt").write_text(
        "Open these OBJ files if the simple terrain_uv_variants/ set all looks wrong.\n"
        "They test triangle-half selection and flag-driven UV selection while keeping the default texture pages.\n"
        "If flags_low2_rect or unknown_low2_rect looks better, the corresponding TRAK triangle field likely controls UV orientation.\n"
        "If vertex_xz_bbox or vertex_zx_bbox looks better, UVs are probably projected from geometry or stored in an undecoded per-vertex field.\n",
        encoding="utf-8",
    )
    return deep_dir


def write_terrain_texture_index_variant_objs(
    *,
    out_dir: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    materials: list[RuntimeMaterial],
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    texture_count: int = 0,
    uv_variant: str = "default",
) -> Path:
    """Write terrain OBJ variants that only change material->texture-page mapping.

    These files are for testing whether runtime material byte +0x02 maps
    directly to TEXT texture_NN.png or through some dword_58114C page remap.
    Geometry, material rectangles, and UV corner order stay fixed.
    """
    variants_root = out_dir / "terrain_texture_index_variants"
    variants_root.mkdir(parents=True, exist_ok=True)

    rows: list[dict] = []
    material_rows: list[dict] = []

    for mode in TERRAIN_TEXTURE_REMAP_VARIANTS:
        mode_dir = variants_root / mode
        mode_dir.mkdir(parents=True, exist_ok=True)
        copy_textures_for_world(out_dir / "textures", mode_dir / "textures")
        write_world_mtl(
            mode_dir / "world_texture_remap.mtl",
            materials,
            texture_prefix="textures",
            texture_count=texture_count,
            texture_remap_mode=mode,
        )
        obj_path = mode_dir / "terrain_textured.obj"
        write_textured_terrain_probe_obj(
            path=obj_path,
            mapx=mapx,
            trak=trak,
            materials=materials,
            scale=scale,
            flip_z=flip_z,
            terrain_yaw_sign=terrain_yaw_sign,
            mirror_terrain_z=mirror_terrain_z,
            uv_variant=uv_variant,
            mtl_name="world_texture_remap.mtl",
        )
        rows.append({
            "texture_remap_mode": mode,
            "folder": mode,
            "obj": "terrain_textured.obj",
            "mtl": "world_texture_remap.mtl",
            "uv_variant": uv_variant,
        })

        # Keep a compact audit for the most-used terrain materials.
        counts: dict[int, int] = {}
        for rec in trak.records:
            for tri in rec.table_b:
                counts[tri.material_index] = counts.get(tri.material_index, 0) + 1
        mat_by_i = {m.index: m for m in materials}
        for mat_i, count in sorted(counts.items(), key=lambda kv: kv[1], reverse=True)[:80]:
            m = mat_by_i.get(mat_i)
            if m is None:
                continue
            mapped = _remap_texture_index(material_index=mat_i, raw_texture_index=m.texture_index, texture_count=texture_count, mode=mode)
            material_rows.append({
                "texture_remap_mode": mode,
                "material_index": mat_i,
                "terrain_triangles": count,
                "raw_texture_page": m.texture_index,
                "mapped_texture_png": mapped if mapped is not None else "",
                "rect": f"{m.x0},{m.y0},{m.x1},{m.y1}",
                "flags_hex": f"0x{m.flags:04X}",
            })

    _write_csv(variants_root / "texture_index_variants.csv", ["texture_remap_mode", "folder", "obj", "mtl", "uv_variant"], rows)
    _write_csv(variants_root / "texture_index_variant_material_audit.csv", [
        "texture_remap_mode", "material_index", "terrain_triangles", "raw_texture_page",
        "mapped_texture_png", "rect", "flags_hex",
    ], material_rows)
    (variants_root / "README_texture_index_variants.txt").write_text(
        "These variants test whether runtime material +0x02 maps directly to TEXT texture_NN.png.\n"
        "Open each <mode>/terrain_textured.obj. Geometry and UV rectangles are identical; only map_Kd texture PNG indices change.\n"
        "If one folder has the correct terrain images, that reveals the missing dword_58114C page remap.\n",
        encoding="utf-8",
    )
    return variants_root


# ---------------------------------------------------------------------------
# HTML viewer
# ---------------------------------------------------------------------------


def _collect_world_obj_assets(world_dir: Path) -> list[Path]:
    """Collect generated world OBJ files for the standalone viewer.

    The viewer must work when opened directly from file://, so it cannot fetch
    OBJ files.  We embed selected generated OBJ text directly into the HTML.
    Aggregate duplicates are loaded but hidden by default.
    """
    preferred = [
        world_dir / "terrain.obj",
        world_dir / "terrain_textured_probe.obj",
        world_dir / "objects_all_candidates.obj",
        world_dir / "objects_primary.obj",
        world_dir / "map_object_markers.obj",
        world_dir / "combined.obj",
    ]
    assets: list[Path] = [p for p in preferred if p.exists()]
    by_hit = world_dir / "objects_by_hit"
    if by_hit.exists():
        assets.extend(sorted(by_hit.glob("*.obj")))
    seen: set[Path] = set()
    unique: list[Path] = []
    for a in assets:
        rp = a.resolve()
        if rp not in seen:
            seen.add(rp)
            unique.append(a)
    return unique


def write_world_viewer_html(path: Path, obj_assets: list[Path]) -> None:
    """Write a standalone WebGL OBJ viewer.

    No load button and no local server are required.  The generated OBJ contents
    are embedded directly in this HTML, so it works when opened by double-clicking
    the file in a browser.
    """
    world_dir = path.parent
    embedded = []
    for obj_path in obj_assets:
        try:
            rel = obj_path.relative_to(world_dir).as_posix()
        except ValueError:
            rel = obj_path.name
        try:
            text = obj_path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        default_visible = rel in {"terrain.obj", "objects_all_candidates.obj"}
        embedded.append({"name": rel, "text": text, "visible": default_visible})

    payload = json.dumps(embedded, separators=(",", ":"))
    html = r"""<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>WAD Standalone World Viewer</title>
<style>
html,body{margin:0;width:100%;height:100%;overflow:hidden;background:#101014;color:#e8e8e8;font-family:system-ui,-apple-system,Segoe UI,sans-serif}
#ui{position:fixed;left:12px;top:12px;max-height:calc(100vh - 24px);width:360px;overflow:auto;background:#181820e8;border:1px solid #3a3a46;border-radius:12px;box-shadow:0 8px 28px #000a;padding:12px;z-index:2}
#ui h1{font-size:15px;margin:0 0 8px}
#ui .row{display:flex;gap:8px;align-items:center;margin:6px 0;flex-wrap:wrap}
#ui button{background:#2b2b38;color:#fff;border:1px solid #55566b;border-radius:8px;padding:5px 9px;cursor:pointer}
#ui button:hover{background:#38384a}
#assetList{margin-top:8px;border-top:1px solid #333442;padding-top:8px}
.asset{display:grid;grid-template-columns:22px 1fr auto;gap:6px;align-items:center;font:12px ui-monospace,Menlo,Consolas,monospace;padding:3px 0;border-bottom:1px solid #252530}
.asset small{color:#aaa}
#status{font:12px ui-monospace,Menlo,Consolas,monospace;color:#cfcfd8;white-space:pre-wrap;margin-top:8px}
#help{font-size:12px;color:#b9b9c5;line-height:1.35;margin-top:8px}
canvas{display:block;width:100vw;height:100vh}
</style>
</head>
<body>
<div id="ui">
  <h1>WAD standalone 3D world viewer</h1>
  <div class="row">
    <button id="fitBtn">Fit</button>
    <button id="topBtn">Top</button>
    <button id="isoBtn">Iso</button>
    <button id="allBtn">All</button>
    <button id="noneBtn">None</button>
  </div>
  <div id="assetList"></div>
  <div id="status">Parsing embedded OBJ data…</div>
  <div id="help">No local server is needed. Drag left mouse to orbit, right/middle drag to pan, wheel to zoom. Each checkbox toggles one generated OBJ file. By default, terrain.obj and objects_all_candidates.obj are visible; duplicate aggregate/single-hit files are loaded but hidden.</div>
</div>
<canvas id="glcanvas"></canvas>
<script>
const EMBEDDED_OBJS = __EMBEDDED_OBJS__;
const canvas = document.getElementById('glcanvas');
const gl = canvas.getContext('webgl', {antialias:true, preserveDrawingBuffer:false});
const assetList = document.getElementById('assetList');
const statusEl = document.getElementById('status');
if (!gl) { statusEl.textContent = 'WebGL is not available in this browser.'; throw new Error('no webgl'); }

const vsSource = `
attribute vec3 aPosition;
attribute vec3 aNormal;
uniform mat4 uMVP;
uniform mat4 uModel;
uniform vec3 uColor;
uniform vec3 uLightDir;
varying vec3 vColor;
void main() {
  vec3 n = normalize((uModel * vec4(aNormal, 0.0)).xyz);
  float d = max(dot(n, normalize(uLightDir)), 0.0);
  vColor = uColor * (0.35 + 0.65 * d);
  gl_Position = uMVP * vec4(aPosition, 1.0);
}`;
const fsSource = `
precision mediump float;
varying vec3 vColor;
void main() { gl_FragColor = vec4(vColor, 1.0); }`;
function shader(type, src) { const s = gl.createShader(type); gl.shaderSource(s, src); gl.compileShader(s); if(!gl.getShaderParameter(s, gl.COMPILE_STATUS)) throw new Error(gl.getShaderInfoLog(s)); return s; }
const prog = gl.createProgram();
gl.attachShader(prog, shader(gl.VERTEX_SHADER, vsSource));
gl.attachShader(prog, shader(gl.FRAGMENT_SHADER, fsSource));
gl.linkProgram(prog);
if(!gl.getProgramParameter(prog, gl.LINK_STATUS)) throw new Error(gl.getProgramInfoLog(prog));
gl.useProgram(prog);
const loc = {
  aPosition: gl.getAttribLocation(prog, 'aPosition'),
  aNormal: gl.getAttribLocation(prog, 'aNormal'),
  uMVP: gl.getUniformLocation(prog, 'uMVP'),
  uModel: gl.getUniformLocation(prog, 'uModel'),
  uColor: gl.getUniformLocation(prog, 'uColor'),
  uLightDir: gl.getUniformLocation(prog, 'uLightDir')
};

function parseOBJ(text) {
  const verts = [[0,0,0]];
  const outP = [];
  const outN = [];
  const lines = text.split(/\r?\n/);
  for (const line0 of lines) {
    const line = line0.trim();
    if (!line || line[0] === '#') continue;
    const p = line.split(/\s+/);
    if (p[0] === 'v' && p.length >= 4) {
      verts.push([parseFloat(p[1]), parseFloat(p[2]), parseFloat(p[3])]);
    } else if (p[0] === 'f' && p.length >= 4) {
      const ids = p.slice(1).map(tok => {
        const raw = tok.split('/')[0];
        let i = parseInt(raw, 10);
        if (i < 0) i = verts.length + i;
        return i;
      }).filter(i => Number.isFinite(i) && i > 0 && i < verts.length);
      for (let k=1; k+1<ids.length; k++) {
        const tri = [verts[ids[0]], verts[ids[k]], verts[ids[k+1]]];
        const ux = tri[1][0]-tri[0][0], uy = tri[1][1]-tri[0][1], uz = tri[1][2]-tri[0][2];
        const vx = tri[2][0]-tri[0][0], vy = tri[2][1]-tri[0][1], vz = tri[2][2]-tri[0][2];
        let nx = uy*vz-uz*vy, ny = uz*vx-ux*vz, nz = ux*vy-uy*vx;
        const nl = Math.hypot(nx,ny,nz) || 1; nx/=nl; ny/=nl; nz/=nl;
        for (const v of tri) { outP.push(v[0],v[1],v[2]); outN.push(nx,ny,nz); }
      }
    }
  }
  return {positions:new Float32Array(outP), normals:new Float32Array(outN), vertexCount:outP.length/3};
}
function makeBuffer(data) { const b = gl.createBuffer(); gl.bindBuffer(gl.ARRAY_BUFFER,b); gl.bufferData(gl.ARRAY_BUFFER,data,gl.STATIC_DRAW); return b; }
const palette = [[0.56,0.56,0.58],[0.95,0.62,0.28],[0.35,0.65,1.0],[0.55,0.9,0.55],[0.9,0.5,0.75],[0.85,0.8,0.45],[0.6,0.5,0.95],[0.45,0.85,0.85]];
const assets = [];
let globalMin=[ Infinity, Infinity, Infinity], globalMax=[-Infinity,-Infinity,-Infinity];
function addBounds(pos) { for(let i=0;i<pos.length;i+=3){ const x=pos[i],y=pos[i+1],z=pos[i+2]; if(x<globalMin[0])globalMin[0]=x; if(y<globalMin[1])globalMin[1]=y; if(z<globalMin[2])globalMin[2]=z; if(x>globalMax[0])globalMax[0]=x; if(y>globalMax[1])globalMax[1]=y; if(z>globalMax[2])globalMax[2]=z; } }
for (let i=0;i<EMBEDDED_OBJS.length;i++) {
  const e = EMBEDDED_OBJS[i];
  const geom = parseOBJ(e.text);
  const asset = {name:e.name, vertexCount:geom.vertexCount, visible:e.visible, color:palette[i%palette.length], posBuf:makeBuffer(geom.positions), normBuf:makeBuffer(geom.normals)};
  assets.push(asset);
  if (geom.vertexCount) addBounds(geom.positions);
}

function buildUI() {
  assetList.innerHTML = '';
  for (const a of assets) {
    const row = document.createElement('label'); row.className='asset';
    const cb = document.createElement('input'); cb.type='checkbox'; cb.checked=a.visible;
    cb.oninput = () => { a.visible = cb.checked; requestAnimationFrame(draw); };
    const name = document.createElement('span'); name.textContent = a.name;
    const count = document.createElement('small'); count.textContent = a.vertexCount.toLocaleString() + ' vtx';
    row.appendChild(cb); row.appendChild(name); row.appendChild(count); assetList.appendChild(row);
  }
}
buildUI();

function mat4Identity() { return [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]; }
function mat4Mul(a,b) { const o=new Array(16); for(let c=0;c<4;c++) for(let r=0;r<4;r++) o[c*4+r]=a[0*4+r]*b[c*4+0]+a[1*4+r]*b[c*4+1]+a[2*4+r]*b[c*4+2]+a[3*4+r]*b[c*4+3]; return o; }
function perspective(fovy, aspect, near, far) { const f=1/Math.tan(fovy/2), nf=1/(near-far); return [f/aspect,0,0,0, 0,f,0,0, 0,0,(far+near)*nf,-1, 0,0,2*far*near*nf,0]; }
function lookAt(eye,center,up) {
  let zx=eye[0]-center[0],zy=eye[1]-center[1],zz=eye[2]-center[2]; let zl=Math.hypot(zx,zy,zz)||1; zx/=zl; zy/=zl; zz/=zl;
  let xx=up[1]*zz-up[2]*zy,xy=up[2]*zx-up[0]*zz,xz=up[0]*zy-up[1]*zx; let xl=Math.hypot(xx,xy,xz)||1; xx/=xl; xy/=xl; xz/=xl;
  let yx=zy*xz-zz*xy, yy=zz*xx-zx*xz, yz=zx*xy-zy*xx;
  return [xx,yx,zx,0, xy,yy,zy,0, xz,yz,zz,0, -(xx*eye[0]+xy*eye[1]+xz*eye[2]), -(yx*eye[0]+yy*eye[1]+yz*eye[2]), -(zx*eye[0]+zy*eye[1]+zz*eye[2]), 1];
}
let center=[0,0,0], radius=50, yaw=-0.8, pitch=0.75, distance=120, pan=[0,0,0];
function fit() {
  if (!Number.isFinite(globalMin[0])) return;
  center=[(globalMin[0]+globalMax[0])/2,(globalMin[1]+globalMax[1])/2,(globalMin[2]+globalMax[2])/2];
  const sx=globalMax[0]-globalMin[0], sy=globalMax[1]-globalMin[1], sz=globalMax[2]-globalMin[2];
  radius=Math.max(sx,sy,sz,1); distance=radius*1.9; pan=[0,0,0];
}
function setTop() { yaw=0; pitch=Math.PI/2-0.001; draw(); }
function setIso() { yaw=-0.78; pitch=0.72; draw(); }
fit();
function resize() { const dpr=window.devicePixelRatio||1; canvas.width=Math.floor(innerWidth*dpr); canvas.height=Math.floor(innerHeight*dpr); gl.viewport(0,0,canvas.width,canvas.height); draw(); }
addEventListener('resize', resize);
function cameraEye() { const cp=Math.cos(pitch), sp=Math.sin(pitch), cy=Math.cos(yaw), sy=Math.sin(yaw); return [center[0]+pan[0]+distance*cp*sy, center[1]+pan[1]+distance*sp, center[2]+pan[2]+distance*cp*cy]; }
function draw() {
  gl.enable(gl.DEPTH_TEST); gl.disable(gl.CULL_FACE); gl.clearColor(0.06,0.06,0.08,1); gl.clear(gl.COLOR_BUFFER_BIT|gl.DEPTH_BUFFER_BIT);
  const aspect = canvas.width/Math.max(1,canvas.height); const proj=perspective(45*Math.PI/180, aspect, Math.max(0.01, radius/1000), radius*20+distance*5);
  const target=[center[0]+pan[0],center[1]+pan[1],center[2]+pan[2]]; const view=lookAt(cameraEye(), target, [0,1,0]); const mvp=mat4Mul(proj, view); const model=mat4Identity();
  gl.uniformMatrix4fv(loc.uMVP,false,new Float32Array(mvp)); gl.uniformMatrix4fv(loc.uModel,false,new Float32Array(model)); gl.uniform3f(loc.uLightDir, -0.35, 0.8, 0.45);
  let tris=0, shown=0;
  for (const a of assets) { if(!a.visible || !a.vertexCount) continue; shown++; tris += a.vertexCount/3; gl.uniform3f(loc.uColor,a.color[0],a.color[1],a.color[2]);
    gl.bindBuffer(gl.ARRAY_BUFFER,a.posBuf); gl.enableVertexAttribArray(loc.aPosition); gl.vertexAttribPointer(loc.aPosition,3,gl.FLOAT,false,0,0);
    gl.bindBuffer(gl.ARRAY_BUFFER,a.normBuf); gl.enableVertexAttribArray(loc.aNormal); gl.vertexAttribPointer(loc.aNormal,3,gl.FLOAT,false,0,0);
    gl.drawArrays(gl.TRIANGLES,0,a.vertexCount);
  }
  statusEl.textContent = `${shown} / ${assets.length} OBJ files visible\n${Math.round(tris).toLocaleString()} triangles drawn\nBounds: X ${globalMin[0].toFixed(2)}..${globalMax[0].toFixed(2)}  Y ${globalMin[1].toFixed(2)}..${globalMax[1].toFixed(2)}  Z ${globalMin[2].toFixed(2)}..${globalMax[2].toFixed(2)}`;
}
let dragging=false, button=0, lastX=0, lastY=0;
canvas.addEventListener('mousedown', e => { dragging=true; button=e.button; lastX=e.clientX; lastY=e.clientY; });
addEventListener('mouseup', () => dragging=false);
canvas.addEventListener('contextmenu', e => e.preventDefault());
canvas.addEventListener('mousemove', e => { if(!dragging) return; const dx=e.clientX-lastX, dy=e.clientY-lastY; lastX=e.clientX; lastY=e.clientY; if(button===0){ yaw -= dx*0.006; pitch = Math.max(-1.45, Math.min(1.45, pitch - dy*0.006)); } else { const k=distance/600; pan[0]-=dx*k*Math.cos(yaw); pan[2]+=dx*k*Math.sin(yaw); pan[1]+=dy*k; } draw(); });
canvas.addEventListener('wheel', e => { e.preventDefault(); distance *= e.deltaY < 0 ? 0.9 : 1.1; distance=Math.max(radius*0.03,distance); draw(); }, {passive:false});
document.getElementById('fitBtn').onclick=()=>{fit();draw();};
document.getElementById('topBtn').onclick=setTop;
document.getElementById('isoBtn').onclick=setIso;
document.getElementById('allBtn').onclick=()=>{for(const a of assets)a.visible=true; buildUI(); draw();};
document.getElementById('noneBtn').onclick=()=>{for(const a of assets)a.visible=false; buildUI(); draw();};
resize(); draw();
</script>
</body>
</html>""".replace("__EMBEDDED_OBJS__", payload)
    path.write_text(html, encoding="utf-8")


# ---------------------------------------------------------------------------
# Public export API
# ---------------------------------------------------------------------------

def export_world(
    *,
    out_dir: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    stpc_bytes: bytes,
    stpc_result: STPCExportResult,
    text_chunk: TextChunk | None = None,
    scan_bytes: int = 2048,
    scale: float = 1.0,
    flip_z: bool = False,
    write_terrain: bool = True,
    write_per_object: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    stpc_object_z_sign: int = -1,
    stpc_local_z_sign: int = -1,
    apply_stpc_object_yaw: bool = True,
    stpc_object_yaw_sign: int = 1,
    mirror_stpc_objects_z: bool = True,
    object_x_offset: float = 0.0,
    object_y_offset: float = 0.0,
    object_z_offset: float = 1.5,
    world_terrain_uv_variant: str = "default",
    write_terrain_uv_variants: bool = True,
    write_terrain_uv_deep_tests: bool = True,
    world_terrain_texture_remap: str = "direct",
    write_terrain_texture_index_variants: bool = True,
) -> WorldRebuildResult:
    """Export the reconstructed level world into `out_dir`.

    Confirmed pieces:
    * TRAK terrain geometry is placed with MAP tile position/yaw and mirrored on Z around the terrain center to match MAP/STPC object space.
    * STPC object candidates are translated with MAP object XYZ.
    * STPC object candidates are mirrored around the same world Z center by default, matching the visually validated terrain orientation.

    Still unresolved:
    * Full STPC object-definition semantics.
    * Object scale and material/texture assignment.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    materials = parse_runtime_materials(text_chunk) if text_chunk is not None else []
    texture_count = len(text_chunk.textures) if text_chunk is not None else 0
    write_world_mtl(out_dir / "world.mtl", materials, texture_count=texture_count, texture_remap_mode=world_terrain_texture_remap)
    if text_chunk is not None:
        copy_textures_for_world(out_dir.parent / "textures", out_dir / "textures")

    instances = build_world_object_instances(mapx)
    hits = scan_stpc_definition_for_mesh_offsets(
        stpc_bytes=stpc_bytes,
        instances=instances,
        meshes=stpc_result.meshes,
        scan_bytes=scan_bytes,
        dedupe_per_object_mesh=True,
    )
    hits_by_object: dict[int, list[StpcMeshReferenceHit]] = {}
    for h in hits:
        hits_by_object.setdefault(h.object_index, []).append(h)

    terrain_obj: Path | None = None
    terrain_tiles_written = 0
    terrain_tiles_skipped = 0
    if write_terrain:
        # `terrain_trak.obj` is now the MAP-placed terrain.  The previous local
        # only export stacked every TRAK record around the origin and is kept as
        # a diagnostic name only through the dedicated TRAK folder.
        terrain_obj = out_dir / "terrain.obj"
        _, terrain_tiles_written, terrain_tiles_skipped = write_map_placed_trak_terrain_obj(
            path=terrain_obj,
            mapx=mapx,
            trak=trak,
            scale=scale,
            flip_z=flip_z,
            terrain_yaw_sign=terrain_yaw_sign,
            write_per_tile_dir=None,
        )

    textured_terrain_obj = None
    if terrain_obj is not None and materials:
        try:
            textured_terrain_obj = write_textured_terrain_probe_obj(
                path=out_dir / "terrain_textured_probe.obj",
                mapx=mapx,
                trak=trak,
                materials=materials,
                scale=scale,
                flip_z=flip_z,
                terrain_yaw_sign=terrain_yaw_sign,
                mirror_terrain_z=mirror_terrain_z,
                uv_variant=world_terrain_uv_variant,
                mtl_name="world.mtl",
            )
        except Exception:
            # Keep the stable geometry export even if the experimental textured
            # probe hits an unexpected material row.
            textured_terrain_obj = None

    terrain_uv_variants_dir = None
    if terrain_obj is not None and materials and write_terrain_uv_variants:
        try:
            terrain_uv_variants_dir = write_terrain_uv_variant_objs(
                out_dir=out_dir,
                mapx=mapx,
                trak=trak,
                materials=materials,
                scale=scale,
                flip_z=flip_z,
                terrain_yaw_sign=terrain_yaw_sign,
                mirror_terrain_z=mirror_terrain_z,
                texture_count=texture_count,
                texture_remap_mode=world_terrain_texture_remap,
            )
        except Exception:
            terrain_uv_variants_dir = None

    terrain_uv_deep_tests_dir = None
    if terrain_obj is not None and materials and write_terrain_uv_deep_tests:
        try:
            terrain_uv_deep_tests_dir = write_terrain_uv_deep_test_objs(
                out_dir=out_dir,
                mapx=mapx,
                trak=trak,
                materials=materials,
                scale=scale,
                flip_z=flip_z,
                terrain_yaw_sign=terrain_yaw_sign,
                mirror_terrain_z=mirror_terrain_z,
                texture_count=texture_count,
                texture_remap_mode=world_terrain_texture_remap,
            )
        except Exception:
            terrain_uv_deep_tests_dir = None

    terrain_texture_index_variants_dir = None
    if terrain_obj is not None and materials and write_terrain_texture_index_variants:
        try:
            terrain_texture_index_variants_dir = write_terrain_texture_index_variant_objs(
                out_dir=out_dir,
                mapx=mapx,
                trak=trak,
                materials=materials,
                scale=scale,
                flip_z=flip_z,
                terrain_yaw_sign=terrain_yaw_sign,
                mirror_terrain_z=mirror_terrain_z,
                texture_count=texture_count,
                uv_variant=world_terrain_uv_variant,
            )
        except Exception:
            terrain_texture_index_variants_dir = None

    terrain_z_min, terrain_z_max = _obj_bounds_z(terrain_obj) if terrain_obj else (None, None)
    object_z_mirror_center = None
    if mirror_stpc_objects_z and terrain_z_min is not None and terrain_z_max is not None:
        object_z_mirror_center = (terrain_z_min + terrain_z_max) * 0.5

    _write_marker_cross_obj(out_dir / "map_object_markers.obj", instances, hits_by_object, scale=scale, flip_z=flip_z)

    # CSV: exact transforms currently used by the world exporter.  These files
    # are intentionally redundant with map_full/ because they show the exporter
    # interpretation, not just the raw file fields.
    _write_csv(out_dir / "terrain_tile_transforms.csv", [
        "tile_index","trak_record_index","tx","ty","raw_tz","terrain_z_mirror_enabled","yaw_units_4096","yaw_degrees","source"
    ], (
        {
            "tile_index": i,
            "trak_record_index": mapx.tile_trak_indices[i] if i < len(mapx.tile_trak_indices) else -1,
            "tx": _fixed12_signed_from_u32(mapx.tile_defs[i].u32_16) if i < len(mapx.tile_defs) else t.x,
            "ty": _fixed12_signed_from_u32(mapx.tile_defs[i].u32_20) if i < len(mapx.tile_defs) else t.y,
            "raw_tz": -_fixed12_signed_from_u32(mapx.tile_defs[i].u32_24) if i < len(mapx.tile_defs) else t.z,
            "terrain_z_mirror_enabled": mirror_terrain_z,
            "yaw_units_4096": (mapx.tile_defs[i].u32_04 & 0xFFFF) if i < len(mapx.tile_defs) else 0,
            "yaw_degrees": (((mapx.tile_defs[i].u32_04 & 0xFFFF) / 4096.0) * 360.0 * terrain_yaw_sign) if i < len(mapx.tile_defs) else 0.0,
            "source": "tile_defs_24",
        } for i, t in enumerate(mapx.tiles)
    ))

    _write_csv(out_dir / "stpc_instance_transforms.csv", [
        "object_index","raw_x","raw_y","raw_z","render_x","render_y","render_z",
        "object_z_sign","local_z_sign","object_z_mirror_enabled","object_z_mirror_center","object_x_offset","object_y_offset","object_z_offset","yaw_units_4096","yaw_degrees","apply_yaw"
    ], (
        {
            "object_index": o.object_index,
            "raw_x": o.world_x,
            "raw_y": o.world_y,
            "raw_z": o.world_z,
            "render_x": o.world_x + object_x_offset,
            "render_y": o.world_y + object_y_offset,
            "render_z": ((2.0 * object_z_mirror_center - (stpc_object_z_sign * o.world_z)) if object_z_mirror_center is not None else stpc_object_z_sign * o.world_z) + object_z_offset,
            "object_z_sign": stpc_object_z_sign,
            "local_z_sign": stpc_local_z_sign,
            "object_z_mirror_enabled": object_z_mirror_center is not None,
            "object_z_mirror_center": object_z_mirror_center if object_z_mirror_center is not None else "",
            "object_x_offset": object_x_offset,
            "object_y_offset": object_y_offset,
            "object_z_offset": object_z_offset,
            "yaw_units_4096": o.small_04,
            "yaw_degrees": (o.small_04 / 4096.0) * 360.0 * stpc_object_yaw_sign if apply_stpc_object_yaw else 0.0,
            "apply_yaw": apply_stpc_object_yaw,
        } for o in instances
    ))

    combined_obj = write_instanced_stpc_objs(
        out_dir=out_dir,
        instances=instances,
        hits=hits,
        meshes=stpc_result.meshes,
        scale=scale,
        flip_z=flip_z,
        write_per_object=write_per_object,
        object_z_sign=stpc_object_z_sign,
        local_z_sign=stpc_local_z_sign,
        apply_object_yaw=apply_stpc_object_yaw,
        object_yaw_sign=stpc_object_yaw_sign,
        object_z_mirror_center=object_z_mirror_center,
        object_x_offset=object_x_offset,
        object_y_offset=object_y_offset,
        object_z_offset=object_z_offset,
    )
    world_combined = write_world_combined_obj(out_dir)

    # CSV: all MAP object placements.
    _write_csv(out_dir / "map_object_instances.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","world_x","world_y","world_z",
        "mesh_hit_count","mesh_indices","small_00","small_04","small_08","field_16",
        "section2_index_or_sentinel","field_1e","field_22","field_26_angle_candidate",
        "field_26_hex","field_2a","section4_index_or_sentinel","field_32","field_36","field_38",
    ], (
        {
            "object_index": o.object_index,
            "stpc_def_offset": o.stpc_def_offset,
            "stpc_def_offset_hex": _hex(o.stpc_def_offset),
            "world_x": o.world_x,
            "world_y": o.world_y,
            "world_z": o.world_z,
            "mesh_hit_count": len(hits_by_object.get(o.object_index, [])),
            "mesh_indices": " ".join(str(h.mesh_index) for h in hits_by_object.get(o.object_index, [])),
            "small_00": o.small_00,
            "small_04": o.small_04,
            "small_08": o.small_08,
            "field_16": o.field_16,
            "section2_index_or_sentinel": o.section2_index_or_sentinel,
            "field_1e": o.field_1e,
            "field_22": o.field_22,
            "field_26_angle_candidate": o.field_26_angle_candidate,
            "field_26_hex": _hex(o.field_26_angle_candidate),
            "field_2a": o.field_2a,
            "section4_index_or_sentinel": o.section4_index_or_sentinel,
            "field_32": o.field_32,
            "field_36": o.field_36,
            "field_38": o.field_38,
        } for o in instances
    ))

    # CSV: one row per exact mesh-offset hit found in an object definition.
    _write_csv(out_dir / "stpc_mesh_reference_hits.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","scan_start","scan_end",
        "hit_file_offset","hit_relative_offset","mesh_index","mesh_offset","mesh_offset_hex",
        "duplicate_index_for_object",
    ], (
        {
            "object_index": h.object_index,
            "stpc_def_offset": h.stpc_def_offset,
            "stpc_def_offset_hex": _hex(h.stpc_def_offset),
            "scan_start": h.scan_start,
            "scan_end": h.scan_end,
            "hit_file_offset": h.hit_file_offset,
            "hit_relative_offset": h.hit_relative_offset,
            "mesh_index": h.mesh_index,
            "mesh_offset": h.mesh_offset,
            "mesh_offset_hex": _hex(h.mesh_offset),
            "duplicate_index_for_object": h.duplicate_index_for_object,
        } for h in hits
    ))

    # CSV: unique object definitions observed from MAP objects.
    defs: dict[int, dict] = {}
    for o in instances:
        d = defs.setdefault(o.stpc_def_offset, {"count": 0, "objects": []})
        d["count"] += 1
        d["objects"].append(o.object_index)
    _write_csv(out_dir / "stpc_object_defs.csv", [
        "stpc_def_offset","stpc_def_offset_hex","object_count","object_indices","in_stpc_range","first_32_bytes_hex",
    ], (
        {
            "stpc_def_offset": off,
            "stpc_def_offset_hex": _hex(off),
            "object_count": info["count"],
            "object_indices": " ".join(str(i) for i in info["objects"]),
            "in_stpc_range": 0 <= off < len(stpc_bytes),
            "first_32_bytes_hex": stpc_bytes[off:min(len(stpc_bytes), off+32)].hex(" ") if 0 <= off < len(stpc_bytes) else "",
        } for off, info in sorted(defs.items())
    ))

    write_world_viewer_html(out_dir / "world_viewer.html", _collect_world_obj_assets(out_dir))

    summary = {
        "map_object_count": len(instances),
        "stpc_mesh_count": len(stpc_result.meshes),
        "scan_bytes_per_object_definition": scan_bytes,
        "mesh_reference_hit_count": len(hits),
        "objects_with_mesh_hits": len({h.object_index for h in hits}),
        "unique_meshes_referenced": len({h.mesh_index for h in hits}),
        "terrain_obj": str(terrain_obj.name) if terrain_obj else None,
        "terrain_textured_probe_obj": str(textured_terrain_obj.name) if textured_terrain_obj else None,
        "terrain_textured_uv_variant": world_terrain_uv_variant,
        "terrain_texture_remap": world_terrain_texture_remap,
        "terrain_uv_variants_dir": str(terrain_uv_variants_dir.name) if terrain_uv_variants_dir else None,
        "terrain_uv_deep_tests_dir": str(terrain_uv_deep_tests_dir.name) if terrain_uv_deep_tests_dir else None,
        "terrain_texture_index_variants_dir": str(terrain_texture_index_variants_dir.name) if terrain_texture_index_variants_dir else None,
        "terrain_placement": "MAP tile fixed XYZ + tile yaw + tile_trak_record_index + TRAK local vertices",
        "terrain_yaw_sign": terrain_yaw_sign,
        "mirror_terrain_z": mirror_terrain_z,
        "stpc_object_z_sign": stpc_object_z_sign,
        "stpc_local_z_sign": stpc_local_z_sign,
        "mirror_stpc_objects_z": mirror_stpc_objects_z,
        "stpc_object_z_mirror_center": object_z_mirror_center,
        "object_alignment_offset": {"x": object_x_offset, "y": object_y_offset, "z": object_z_offset},
        "apply_stpc_object_yaw": apply_stpc_object_yaw,
        "stpc_object_yaw_sign": stpc_object_yaw_sign,
        "terrain_tiles_written": terrain_tiles_written,
        "terrain_tiles_skipped": terrain_tiles_skipped,
        "objects_all_candidates_obj": str(combined_obj.name) if combined_obj else None,
        "objects_by_hit_folder": "objects_by_hit/",
        "objects_primary_obj": "objects_primary.obj" if hits else None,
        "combined_obj": str(world_combined.name) if world_combined else None,
        "important_note": "Terrain is the validated orientation. STPC instances use MAP object XYZ, centered Z mirror, experimental object yaw from small_04, and final object alignment offsets. Scale, materials, and full object-definition semantics are still unresolved; use objects_by_hit/ and diagnostics/ for validation.",
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    return WorldRebuildResult(
        output_dir=out_dir,
        object_instances=instances,
        mesh_reference_hits=hits,
        unique_objects_with_hits=summary["objects_with_mesh_hits"],
        unique_meshes_referenced=summary["unique_meshes_referenced"],
        combined_obj_path=combined_obj,
        terrain_obj_path=terrain_obj,
    )


# Backwards-compatible name used by earlier project patches.
def export_world_rebuild_probe(**kwargs):
    return export_world(**kwargs)

# Backwards-compatible internal name.
def write_world_combined_probe_obj(world_dir: Path, *, include_terrain: bool = True) -> Path | None:
    return write_world_combined_obj(world_dir, include_terrain=include_terrain)
