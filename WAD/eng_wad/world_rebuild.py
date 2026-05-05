"""
world_rebuild.py — confirmed TRAK/MAP/STPC world reconstruction exporter.

This module combines the parts of the WAD that are now structurally decoded:

    TRAK  -> terrain/world sector triangle geometry
    MAP   -> object placement records with confirmed 12.12 fixed-point XYZ
    STPC  -> mesh bank plus object-definition/script data

The important bridge is the MAP object field named stpc_object_def_offset in the
reverse-engineering notes.  At runtime the game converts it to:

    dword_6D9DBC + stpc_object_def_offset

where dword_6D9DBC is the raw STPC chunk base.  Some of those object-definition
records contain 0x00B2 script operands that point at decoded STPC mesh-record
offsets.

This exporter is deliberately conservative around unresolved STPC object-definition details:

* It only instances STPC meshes when an STPC object script 0x00B2 operand
  resolves to a decoded mesh-record offset inside the object's bounded
  definition scan window.
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
from .stpc_chunk import MeshCandidate, STPCExportResult, stpc_triangle_uvs
from .trak_chunk import TrakFile
from .text_chunk import TextChunk
from .material_chunk import RuntimeMaterial, parse_runtime_materials, copy_textures_for_world
from .world_terrain import write_world_mtl, write_textured_terrain_obj
from .world_viewer import _collect_world_obj_assets, write_world_viewer_html


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
    rot_x_units: int
    rot_y_units: int
    rot_z_units: int
    actor_rot_x_fixed: int
    actor_rot_y_fixed: int
    actor_rot_z_fixed: int
    local_count: int
    section2_index_or_sentinel: int
    stack_word_count: int
    stack_arg_count: int
    spawn_flags: int
    extra_count: int
    section4_index_or_sentinel: int
    spawn_aux: int
    flags: int
    skip_initial_spawn: bool
    extra_u16: int
    route_transform_x: float | None = None
    route_transform_y: float | None = None
    route_transform_z: float | None = None
    route_transform_rot_x_units: int | None = None
    route_transform_yaw_units: int | None = None
    route_transform_rot_z_units: int | None = None


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
    script_x_offset: float = 0.0
    script_y_offset: float = 0.0
    script_z_offset: float = 0.0
    script_yaw_units: int | None = None
    script_transform_source: str = ""


@dataclass
class WorldRebuildResult:
    output_dir: Path
    object_instances: list[WorldObjectInstance]
    mesh_reference_hits: list[StpcMeshReferenceHit]
    unique_objects_with_hits: int
    unique_meshes_referenced: int
    combined_obj_path: Path | None
    terrain_obj_path: Path | None
    terrain_and_objects_obj_path: Path | None = None


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
        route_x = route_y = route_z = None
        route_rot_x_units = None
        route_yaw_units = None
        route_rot_z_units = None
        if 0 <= o.section4_index_raw < len(mapx.section4):
            route = mapx.section4[o.section4_index_raw]
            # Opcode 0xFE (sub_54DFE0) copies Section4 +0x18/+0x1C/+0x20
            # into actor +0x30/+0x34/+0x38, and Section4 +0x08/+0x0C/+0x10
            # into actor rotations +0x20/+0x24/+0x28 after << 12.
            route_x = _fixed12(route.u32_24)
            route_y = _fixed12(route.u32_28)
            route_z = _fixed12(route.u32_32)
            route_rot_x_units = route.small_a
            route_yaw_units = route.small_b
            route_rot_z_units = route.small_c
        out.append(WorldObjectInstance(
            object_index=o.index,
            stpc_def_offset=o.name_or_string_offset,
            world_x=_fixed12(o.u32_16),
            world_y=_fixed12(o.u32_20),
            world_z=_fixed12(o.u32_24),
            rot_x_units=o.rot_x_units,
            rot_y_units=o.rot_y_units,
            rot_z_units=o.rot_z_units,
            actor_rot_x_fixed=o.actor_rot_x_fixed,
            actor_rot_y_fixed=o.actor_rot_y_fixed,
            actor_rot_z_fixed=o.actor_rot_z_fixed,
            local_count=o.local_count,
            section2_index_or_sentinel=o.section2_index_raw,
            stack_word_count=o.stack_word_count,
            stack_arg_count=o.stack_arg_count,
            spawn_flags=o.spawn_flags,
            extra_count=o.extra_count,
            section4_index_or_sentinel=o.section4_index_raw,
            spawn_aux=o.spawn_aux_raw,
            flags=o.flags,
            skip_initial_spawn=o.skip_initial_spawn,
            extra_u16=o.extra_u16,
            route_transform_x=route_x,
            route_transform_y=route_y,
            route_transform_z=route_z,
            route_transform_rot_x_units=route_rot_x_units,
            route_transform_yaw_units=route_yaw_units,
            route_transform_rot_z_units=route_rot_z_units,
        ))
    return out


def scan_stpc_definition_for_mesh_offsets(
    *,
    stpc_bytes: bytes,
    instances: list[WorldObjectInstance],
    meshes: list[MeshCandidate],
    scan_bytes: int = 2048,
    dedupe_per_object_mesh: bool = True,
    stop_at_next_definition: bool = True,
    follow_script_pointers: bool = True,
    max_script_pointer_depth: int = 1,
) -> list[StpcMeshReferenceHit]:
    """Find script opcode 0x00B2 references to decoded STPC mesh records.

    The STPC object-definition VM is only partially decoded, but the executable
    pattern for mesh references is clear in the object streams:

        u16 opcode = 0x00B2
        u16 arg_or_zero
        u32 stpc_relative_geometry_offset

    Earlier exports byte-scanned every u32 value.  That produced false positives
    such as ordinary constants equal to 4, and long scan windows could bleed into
    the next object definition.  Restricting to the B2 operand and stopping at
    the next known MAP object-definition offset keeps the binding conservative.

    Some B2 operands point at shared object-script blocks instead of geometry.
    For objects without a direct geometry operand, follow those immediate script
    pointers one bounded level and use mesh operands found there.  This recovers
    delegated definitions without letting a common script chain pull unrelated
    meshes into objects that already named their geometry directly.
    """
    mesh_by_offset = {m.offset: m for m in meshes}
    if not mesh_by_offset:
        return []

    unique_definition_offsets = sorted({
        inst.stpc_def_offset for inst in instances
        if 0 <= inst.stpc_def_offset < len(stpc_bytes)
    })
    def bounded_scan_end(start: int) -> int:
        end = min(len(stpc_bytes), start + max(0, scan_bytes))
        if stop_at_next_definition:
            for def_off in unique_definition_offsets:
                if def_off > start:
                    end = min(end, def_off)
                    break
        return end

    def iter_b2_operands(start: int, end: int) -> Iterable[tuple[int, int]]:
        if start < 0 or start >= len(stpc_bytes):
            return
        for off in range(start, max(start, end - 7)):
            if struct.unpack_from("<I", stpc_bytes, off)[0] != 0x000000B2:
                continue
            target = struct.unpack_from("<I", stpc_bytes, off + 4)[0]
            yield off, target

    @dataclass
    class _StackValue:
        value: int
        kind: str = "value"
        origin_offset: int | None = None

    @dataclass
    class _SimHit:
        selection_offset: int
        hit_file_offset: int
        mesh_offset: int
        script_x_offset: float
        script_y_offset: float
        script_z_offset: float
        script_yaw_units: int | None
        source: str

    def _pop_value(stack: list[_StackValue]) -> int:
        return stack.pop().value if stack else 0

    def _movement_delta(op: int, amount_fixed: int, yaw_rad: float) -> tuple[float, float, float] | None:
        amount = amount_fixed / 4096.0
        if op == 0x0103:
            return (0.0, amount, 0.0)
        if op == 0x0104:
            return (0.0, -amount, 0.0)
        local_x = local_z = 0.0
        if op in {0x0061, 0x00E3}:
            local_x = amount
        elif op in {0x0062, 0x00E4}:
            local_x = -amount
        elif op in {0x005F, 0x0125}:
            local_z = amount
        elif op in {0x0060, 0x0126}:
            local_z = -amount
        elif op == 0x005D:
            return (0.0, amount, 0.0)
        else:
            return None
        dx, dz = _rotate_xz(local_x, local_z, yaw_rad) if yaw_rad else (local_x, local_z)
        return (dx, 0.0, dz)

    def simulate_mesh_assignments(
        *,
        start: int,
        end: int,
        selection_base: int,
        yaw_rad: float,
        yaw_units: int | None,
        route_transform: tuple[float, float, float, int | None] | None = None,
        inherited_x: float = 0.0,
        inherited_y: float = 0.0,
        inherited_z: float = 0.0,
        inherited_route: bool = False,
        depth: int = 0,
    ) -> list[_SimHit]:
        """Decode the placement-related subset of the STPC script VM.

        The executable shows that opcodes 0x94/0xE0 create child actors that
        inherit the parent's current transform, and that common movement
        opcodes mutate actor +30/+34/+38 before a later 0x54 model bind.  This
        simulator intentionally handles only those placement effects; unknown
        opcodes are left alone so existing mesh selection stays conservative.
        """
        if depth > max_script_pointer_depth or start < 0 or start >= len(stpc_bytes):
            return []
        pc = start
        stack: list[_StackValue] = []
        x = inherited_x
        y = inherited_y
        z = inherited_z
        current_yaw_rad = yaw_rad
        current_yaw_units = yaw_units
        used_route_transform = inherited_route
        out: list[_SimHit] = []
        steps = 0
        while pc + 4 <= end and steps < 512:
            steps += 1
            op_offset = pc
            raw = struct.unpack_from("<I", stpc_bytes, pc)[0]
            op = raw & 0xFFFF
            pc += 4

            if op <= 0x0044:
                if op == 0x0044:
                    imm = (raw >> 16) & 0xFFFF
                    if imm & 0x8000:
                        imm -= 0x10000
                    stack.append(_StackValue(imm))
                continue

            if op == 0x0045:
                if pc + 4 > end:
                    break
                stack.append(_StackValue(_i32_from_u32(struct.unpack_from("<I", stpc_bytes, pc)[0])))
                pc += 4
                continue

            if op == 0x00B2:
                if pc + 4 > end:
                    break
                target = struct.unpack_from("<i", stpc_bytes, pc)[0]
                pc += 4
                if target >= 0:
                    stack.append(_StackValue(target, "stpc_ptr", op_offset))
                else:
                    # Negative operands resolve through the DEFANIM.WAD pointer
                    # table at runtime; the WAD-local exporter cannot bind them
                    # to an STPC mesh without that external table.
                    stack.append(_StackValue(target, "external_anim_ptr", op_offset))
                continue

            if op == 0x0054:
                if not stack:
                    continue
                value = stack.pop()
                if value.kind == "stpc_ptr" and value.value in mesh_by_offset:
                    origin = value.origin_offset if value.origin_offset is not None else op_offset
                    source = "script_vm_child" if depth else "script_vm_direct"
                    if used_route_transform:
                        source += "_route"
                    out.append(_SimHit(
                        selection_offset=selection_base,
                        hit_file_offset=origin,
                        mesh_offset=value.value,
                        script_x_offset=x,
                        script_y_offset=y,
                        script_z_offset=z,
                        script_yaw_units=current_yaw_units,
                        source=source,
                    ))
                continue

            if op in {0x0094, 0x00E0}:
                child = stack.pop() if stack else _StackValue(0)
                # sub_553170 consumes five dwords plus one extra output dword
                # from the parent stream before sub_54BFC0 starts the child.
                if pc + 24 > end:
                    break
                pc += 24
                if (
                    follow_script_pointers
                    and child.kind == "stpc_ptr"
                    and child.value not in mesh_by_offset
                    and 0 <= child.value < len(stpc_bytes)
                    and depth < max_script_pointer_depth
                ):
                    child_end = bounded_scan_end(child.value)
                    child_selection = (
                        child.origin_offset - selection_base
                        if child.origin_offset is not None
                        else op_offset - selection_base
                    )
                    out.extend(simulate_mesh_assignments(
                        start=child.value,
                        end=child_end,
                        selection_base=child.value + child_selection,
                        yaw_rad=current_yaw_rad,
                        yaw_units=current_yaw_units,
                        route_transform=route_transform,
                        inherited_x=x,
                        inherited_y=y,
                        inherited_z=z,
                        inherited_route=used_route_transform,
                        depth=depth + 1,
                    ))
                continue

            if op == 0x00D4:
                # sub_553EF0 consumes two dwords and records an alternate PC.
                # It does not change actor placement.
                pc += 8
                continue

            if op == 0x00FE:
                if route_transform is not None:
                    route_x, route_y, route_z, route_yaw = route_transform
                    x = route_x - inst.world_x
                    y = route_y - inst.world_y
                    z = route_z - inst.world_z
                    used_route_transform = True
                    if route_yaw is not None:
                        current_yaw_units = route_yaw
                        current_yaw_rad = _angle4096_to_radians(route_yaw)
                continue

            delta = _movement_delta(op, _pop_value(stack), current_yaw_rad)
            if delta is not None:
                dx, dy, dz = delta
                x += dx
                y += dy
                z += dz

        return out

    hits: list[StpcMeshReferenceHit] = []
    for inst in instances:
        start = inst.stpc_def_offset
        if start < 0 or start >= len(stpc_bytes):
            continue
        end = bounded_scan_end(start)
        yaw_rad = _angle4096_to_radians(inst.rot_y_units)
        route_transform = None
        if (
            inst.route_transform_x is not None
            and inst.route_transform_y is not None
            and inst.route_transform_z is not None
        ):
            route_transform = (
                inst.route_transform_x,
                inst.route_transform_y,
                inst.route_transform_z,
                inst.route_transform_yaw_units,
            )
        sim_hits = simulate_mesh_assignments(
            start=start,
            end=end,
            selection_base=start,
            yaw_rad=yaw_rad,
            yaw_units=inst.rot_y_units,
            route_transform=route_transform,
            depth=0,
        )
        sim_by_hit: dict[tuple[int, int], _SimHit] = {
            (h.hit_file_offset, h.mesh_offset): h for h in sim_hits
        }
        direct_operands = list(iter_b2_operands(start, end))
        candidate_refs: list[tuple[int, int, int]] = []

        for off, target in direct_operands:
            if target in mesh_by_offset:
                candidate_refs.append((off - start, off, target))

        if not candidate_refs and follow_script_pointers and max_script_pointer_depth > 0:
            for ptr_off, ptr_target in direct_operands:
                if ptr_target in mesh_by_offset or not (0 <= ptr_target < len(stpc_bytes)):
                    continue
                ptr_end = bounded_scan_end(ptr_target)
                for nested_off, nested_target in iter_b2_operands(ptr_target, ptr_end):
                    if nested_target not in mesh_by_offset:
                        continue
                    # Keep primary-hit ordering tied to the object's own script
                    # operand, not the absolute position of the shared block.
                    candidate_refs.append((ptr_off - start, nested_off, nested_target))

        seen_meshes: set[int] = set()
        dup_index = 0
        for selection_offset, off, target in sorted(candidate_refs):
            mesh = mesh_by_offset[target]
            if dedupe_per_object_mesh and mesh.index in seen_meshes:
                continue
            seen_meshes.add(mesh.index)
            sim = sim_by_hit.get((off, target))
            hits.append(StpcMeshReferenceHit(
                object_index=inst.object_index,
                stpc_def_offset=inst.stpc_def_offset,
                scan_start=start,
                scan_end=end,
                hit_file_offset=off,
                hit_relative_offset=selection_offset,
                mesh_index=mesh.index,
                mesh_offset=target,
                duplicate_index_for_object=dup_index,
                script_x_offset=sim.script_x_offset if sim else 0.0,
                script_y_offset=sim.script_y_offset if sim else 0.0,
                script_z_offset=sim.script_z_offset if sim else 0.0,
                script_yaw_units=sim.script_yaw_units if sim else None,
                script_transform_source=sim.source if sim else "",
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
    flip_z: bool = True,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = False,
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
                tz0 = -_fixed12_signed_from_u32(td.u32_20)
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
        if terrain_z_mirror_center is not None:
            f.write("# Terrain Z is mirrored around the terrain center for diagnostics.\n")
        else:
            f.write("# Terrain Z uses the MAP terrain-space axis directly; actor/object Z is negated into this space.\n")
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
                tx = _fixed12_signed_from_u32(td.u32_12)
                ty = _fixed12_signed_from_u32(td.u32_16)
                tz = -_fixed12_signed_from_u32(td.u32_20)
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
                tx = _fixed12_signed_from_u32(td.u32_12)
                ty = _fixed12_signed_from_u32(td.u32_16)
                tz = -_fixed12_signed_from_u32(td.u32_20)
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
    hit: StpcMeshReferenceHit | None = None,
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
    materials: list[RuntimeMaterial] | None = None,
) -> int:
    """Append one STPC mesh instance to an open OBJ file.

    Append one STPC mesh instance to an open OBJ file.

    Important coordinate note: after visual validation, terrain.obj is the
    reference orientation.  MAP object positions are stored as 12.12 fixed-point
    actor coordinates.  Terrain queries in the executable negate actor Z before
    comparing against MAP terrain space, so the normal world export uses
    object_z_sign=-1 and no centered mirror.
    """
    f.write(f"\no {object_name}\n")
    f.write(f"# MAP object {inst.object_index}; STPC mesh {mesh.index}; mesh_offset=0x{mesh.offset:08X}\n")
    yaw_units = hit.script_yaw_units if (hit is not None and hit.script_yaw_units is not None) else inst.rot_y_units
    script_x = hit.script_x_offset if hit is not None else 0.0
    script_y = hit.script_y_offset if hit is not None else 0.0
    script_z = hit.script_z_offset if hit is not None else 0.0
    script_source = hit.script_transform_source if hit is not None else ""
    f.write(f"# raw_translation={inst.world_x:.9g},{inst.world_y:.9g},{inst.world_z:.9g}; script_actor_offset={script_x:.9g},{script_y:.9g},{script_z:.9g}; script_transform_source={script_source}; render_z_sign={object_z_sign}; local_z_sign={local_z_sign}; object_yaw={yaw_units if apply_object_yaw else 0}; object_z_mirror_center={object_z_mirror_center}; object_alignment_offset={object_x_offset:.9g},{object_y_offset:.9g},{object_z_offset:.9g}\n")
    yaw = _angle4096_to_radians(yaw_units, sign=object_yaw_sign) if apply_object_yaw else 0.0
    base_x = inst.world_x + script_x
    base_y = inst.world_y + script_y
    base_z = object_z_sign * (inst.world_z + script_z)
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
        # after all source-coordinate conversion so it behaves like a simple
        # world-space nudge against terrain.obj.
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
    mat_by_i = {m.index: m for m in (materials or [])}
    vt_index = getattr(f, "_eng_next_vt_index", 1)
    normal_base = vertex_base
    for tri in mesh.triangles:
        if not (tri.i0 < mesh.vertex_count and tri.i1 < mesh.vertex_count and tri.i2 < mesh.vertex_count):
            continue
        if len({tri.i0, tri.i1, tri.i2}) != 3:
            continue
        if tri.material != current_mat:
            current_mat = tri.material
            f.write(f"usemtl stpc_mat_{current_mat:04d}\n")
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
        f.write(f"f {a}/{vt_index}/{na} {b}/{vt_index + 1}/{nb} {c}/{vt_index + 2}/{nc}\n")
        vt_index += 3
    setattr(f, "_eng_next_vt_index", vt_index)
    return vertex_base + mesh.vertex_count


def write_instanced_stpc_objs(
    *,
    out_dir: Path,
    instances: list[WorldObjectInstance],
    hits: list[StpcMeshReferenceHit],
    meshes: list[MeshCandidate],
    scale: float = 1.0,
    flip_z: bool = True,
    write_per_object: bool = False,
    object_z_sign: int = -1,
    local_z_sign: int = -1,
    apply_object_yaw: bool = True,
    object_yaw_sign: int = 1,
    object_z_mirror_center: float | None = None,
    object_x_offset: float = 0.0,
    object_y_offset: float = 0.0,
    object_z_offset: float = 0.0,
    materials: list[RuntimeMaterial] | None = None,
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
            vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, hit=hit, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset, materials=materials)

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
                hit=hit,
                scale=scale, flip_z=flip_z, vertex_base=1,
                object_z_sign=object_z_sign, local_z_sign=local_z_sign,
                apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign,
                object_z_mirror_center=object_z_mirror_center,
                object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset, materials=materials,
            )

    # Primary-only file: first/earliest hit per object.  This is often the most
    # useful visual export while the STPC object-definition script is unknown.
    first_by_object: dict[int, StpcMeshReferenceHit] = {}
    for hit in sorted(hits, key=lambda h: (h.object_index, h.duplicate_index_for_object)):
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
            vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, hit=hit, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset, materials=materials)

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
                for hit in sorted(obj_hits, key=lambda h: h.duplicate_index_for_object):
                    mesh = by_mesh.get(hit.mesh_index)
                    if mesh is None:
                        continue
                    name = f"object_{object_index:03d}_mesh_{mesh.index:03d}_hit_{hit.duplicate_index_for_object:02d}"
                    vbase = _write_instanced_mesh_obj(f, mesh, inst, object_name=name, hit=hit, scale=scale, flip_z=flip_z, vertex_base=vbase, object_z_sign=object_z_sign, local_z_sign=local_z_sign, apply_object_yaw=apply_object_yaw, object_yaw_sign=object_yaw_sign, object_z_mirror_center=object_z_mirror_center, object_x_offset=object_x_offset, object_y_offset=object_y_offset, object_z_offset=object_z_offset, materials=materials)
    return primary




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

def write_world_combined_obj(
    world_dir: Path,
    *,
    include_terrain: bool = True,
    terrain_name: str = "terrain.obj",
    object_name: str | None = None,
    output_name: str = "combined.obj",
    description: str = "Combined reconstructed world: TRAK terrain + primary STPC object instances.",
) -> Path | None:
    """Create a tiny OBJ wrapper that references terrain and instance geometry.

    OBJ cannot include other OBJ files, so this function concatenates the two
    generated OBJs when both exist.  It rewrites face indices while copying the
    second file to keep the combined OBJ valid.
    """
    terrain = world_dir / terrain_name
    if object_name is None:
        primary = world_dir / "objects_primary.obj"
        all_candidates = world_dir / "objects_all_candidates.obj"
        inst = primary if primary.exists() else all_candidates
    else:
        inst = world_dir / object_name
    if not inst.exists() and not terrain.exists():
        return None
    out = world_dir / output_name

    vertex_offset = 0
    texture_offset = 0
    normal_offset = 0

    def copy_obj(src: Path, dst, *, add_offsets: bool) -> tuple[int, int]:
        nonlocal vertex_offset, texture_offset, normal_offset
        local_v = 0
        local_vt = 0
        local_n = 0
        for line in src.read_text(encoding="utf-8", errors="replace").splitlines():
            if line.startswith("mtllib"):
                continue
            if line.startswith("v "):
                local_v += 1
                dst.write(line + "\n")
            elif line.startswith("vt "):
                local_vt += 1
                dst.write(line + "\n")
            elif line.startswith("vn "):
                local_n += 1
                dst.write(line + "\n")
            elif line.startswith("f ") and add_offsets:
                parts = line.split()[1:]
                new_parts = []
                for p in parts:
                    bits = p.split("/")
                    vi = int(bits[0]) + vertex_offset
                    if len(bits) >= 3:
                        vt = int(bits[1]) + texture_offset if bits[1] else None
                        ni = int(bits[2]) + normal_offset if bits[2] else None
                        if vt is not None and ni is not None:
                            new_parts.append(f"{vi}/{vt}/{ni}")
                        elif ni is not None:
                            new_parts.append(f"{vi}//{ni}")
                        elif vt is not None:
                            new_parts.append(f"{vi}/{vt}")
                        else:
                            new_parts.append(str(vi))
                    elif len(bits) == 2 and bits[1]:
                        vt = int(bits[1]) + texture_offset
                        new_parts.append(f"{vi}/{vt}")
                    else:
                        new_parts.append(str(vi))
                dst.write("f " + " ".join(new_parts) + "\n")
            else:
                dst.write(line + "\n")
        vertex_offset += local_v
        texture_offset += local_vt
        normal_offset += local_n
        return local_v, local_vt, local_n

    with out.open("w", encoding="utf-8", newline="\n") as f:
        f.write("mtllib world.mtl\n")
        f.write(f"# {description}\n")
        if include_terrain and terrain.exists():
            f.write("\no terrain\n")
            copy_obj(terrain, f, add_offsets=True)
        if inst.exists():
            f.write("\n# --- STPC object instances ---\n")
            copy_obj(inst, f, add_offsets=True)
    return out


def write_terrain_and_objects_obj(
    world_dir: Path,
    *,
    textured_terrain_obj: Path | None = None,
    object_obj: Path | None = None,
) -> Path | None:
    """Write the single textured terrain + placed primary objects OBJ."""
    terrain_name = "terrain.obj"
    if textured_terrain_obj is not None and textured_terrain_obj.exists():
        terrain_name = textured_terrain_obj.name
    elif (world_dir / "terrain_textured.obj").exists():
        terrain_name = "terrain_textured.obj"

    object_name = "objects_primary.obj"
    if object_obj is not None and object_obj.exists():
        object_name = object_obj.name

    return write_world_combined_obj(
        world_dir,
        terrain_name=terrain_name,
        object_name=object_name,
        output_name="terrain_and_objects.obj",
        description="Textured terrain plus placed STPC object instances.",
    )




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
    flip_z: bool = True,
    write_terrain: bool = True,
    write_per_object: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = False,
    stpc_object_z_sign: int = -1,
    stpc_local_z_sign: int = -1,
    apply_stpc_object_yaw: bool = True,
    stpc_object_yaw_sign: int = 1,
    mirror_stpc_objects_z: bool = False,
    object_x_offset: float = 0.0,
    object_y_offset: float = 0.0,
    object_z_offset: float = 0.0,
) -> WorldRebuildResult:
    """Export the reconstructed level world into `out_dir`.

    Confirmed pieces:
    * TRAK terrain geometry is placed with MAP tile position/yaw in terrain space.
    * STPC object candidates are translated with MAP object XYZ.
    * STPC object Z is negated into terrain space, matching the terrain-query path in the executable.

    Still unresolved:
    * Full STPC object-definition semantics.
    * Object scale and material/texture assignment.
    """
    out_dir.mkdir(parents=True, exist_ok=True)
    materials = parse_runtime_materials(text_chunk) if text_chunk is not None else []
    texture_count = len(text_chunk.textures) if text_chunk is not None else 0
    write_world_mtl(out_dir / "world.mtl", materials, texture_count=texture_count)
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
            mirror_terrain_z=mirror_terrain_z,
            write_per_tile_dir=None,
        )

    textured_terrain_obj = None
    if terrain_obj is not None and materials:
        try:
            textured_terrain_obj = write_textured_terrain_obj(
                path=out_dir / "terrain_textured.obj",
                mapx=mapx,
                trak=trak,
                materials=materials,
                scale=scale,
                flip_z=flip_z,
                terrain_yaw_sign=terrain_yaw_sign,
                mirror_terrain_z=mirror_terrain_z,
                mtl_name="world.mtl",
            )
        except Exception:
            # Keep the stable geometry export even if the experimental textured
            # export hits an unexpected material row.
            textured_terrain_obj = None

    # UV/texture-index comparison folders were removed after terrain_textured.obj
    # was validated against the EXE sub_556510 terrain renderer.

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
            "tx": _fixed12_signed_from_u32(mapx.tile_defs[i].u32_12) if i < len(mapx.tile_defs) else t.x,
            "ty": _fixed12_signed_from_u32(mapx.tile_defs[i].u32_16) if i < len(mapx.tile_defs) else t.y,
            "raw_tz": -_fixed12_signed_from_u32(mapx.tile_defs[i].u32_20) if i < len(mapx.tile_defs) else t.z,
            "terrain_z_mirror_enabled": mirror_terrain_z,
            "yaw_units_4096": (mapx.tile_defs[i].u32_04 & 0xFFFF) if i < len(mapx.tile_defs) else 0,
            "yaw_degrees": (((mapx.tile_defs[i].u32_04 & 0xFFFF) / 4096.0) * 360.0 * terrain_yaw_sign) if i < len(mapx.tile_defs) else 0.0,
            "source": "tile_defs_24",
        } for i, t in enumerate(mapx.tiles)
    ))

    _write_csv(out_dir / "stpc_instance_transforms.csv", [
        "object_index","raw_x","raw_y","raw_z","render_x","render_y","render_z",
        "final_world_flip_z","final_obj_z",
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
            "final_world_flip_z": flip_z,
            "final_obj_z": -(((2.0 * object_z_mirror_center - (stpc_object_z_sign * o.world_z)) if object_z_mirror_center is not None else stpc_object_z_sign * o.world_z) + object_z_offset) if flip_z else (((2.0 * object_z_mirror_center - (stpc_object_z_sign * o.world_z)) if object_z_mirror_center is not None else stpc_object_z_sign * o.world_z) + object_z_offset),
            "object_z_sign": stpc_object_z_sign,
            "local_z_sign": stpc_local_z_sign,
            "object_z_mirror_enabled": object_z_mirror_center is not None,
            "object_z_mirror_center": object_z_mirror_center if object_z_mirror_center is not None else "",
            "object_x_offset": object_x_offset,
            "object_y_offset": object_y_offset,
            "object_z_offset": object_z_offset,
            "yaw_units_4096": o.rot_y_units,
            "yaw_degrees": (o.rot_y_units / 4096.0) * 360.0 * stpc_object_yaw_sign if apply_stpc_object_yaw else 0.0,
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
        materials=materials,
    )
    world_combined = write_world_combined_obj(out_dir)
    terrain_and_objects = write_terrain_and_objects_obj(
        out_dir,
        textured_terrain_obj=textured_terrain_obj,
        object_obj=combined_obj,
    )

    # CSV: all MAP object placements.
    _write_csv(out_dir / "map_object_instances.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","world_x","world_y","world_z",
        "mesh_hit_count","mesh_indices",
        "rot_x_units","rot_y_units","rot_z_units","actor_rot_x_fixed","actor_rot_y_fixed","actor_rot_z_fixed",
        "local_count","section2_index_or_sentinel","stack_word_count","stack_arg_count",
        "spawn_flags","spawn_flags_hex","extra_count","section4_index_or_sentinel",
        "spawn_aux","spawn_aux_hex","flags","flags_hex","skip_initial_spawn","extra_u16",
        "route_transform_x","route_transform_y","route_transform_z",
        "route_transform_rot_x_units","route_transform_yaw_units","route_transform_rot_z_units",
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
            "rot_x_units": o.rot_x_units,
            "rot_y_units": o.rot_y_units,
            "rot_z_units": o.rot_z_units,
            "actor_rot_x_fixed": o.actor_rot_x_fixed,
            "actor_rot_y_fixed": o.actor_rot_y_fixed,
            "actor_rot_z_fixed": o.actor_rot_z_fixed,
            "local_count": o.local_count,
            "section2_index_or_sentinel": o.section2_index_or_sentinel,
            "stack_word_count": o.stack_word_count,
            "stack_arg_count": o.stack_arg_count,
            "spawn_flags": o.spawn_flags,
            "spawn_flags_hex": _hex(o.spawn_flags),
            "extra_count": o.extra_count,
            "section4_index_or_sentinel": o.section4_index_or_sentinel,
            "spawn_aux": o.spawn_aux,
            "spawn_aux_hex": _hex(o.spawn_aux),
            "flags": o.flags,
            "flags_hex": f"0x{o.flags:04X}",
            "skip_initial_spawn": o.skip_initial_spawn,
            "extra_u16": o.extra_u16,
            "route_transform_x": o.route_transform_x if o.route_transform_x is not None else "",
            "route_transform_y": o.route_transform_y if o.route_transform_y is not None else "",
            "route_transform_z": o.route_transform_z if o.route_transform_z is not None else "",
            "route_transform_rot_x_units": o.route_transform_rot_x_units if o.route_transform_rot_x_units is not None else "",
            "route_transform_yaw_units": o.route_transform_yaw_units if o.route_transform_yaw_units is not None else "",
            "route_transform_rot_z_units": o.route_transform_rot_z_units if o.route_transform_rot_z_units is not None else "",
        } for o in instances
    ))

    # CSV: one row per exact mesh-offset hit found in an object definition.
    _write_csv(out_dir / "stpc_mesh_reference_hits.csv", [
        "object_index","stpc_def_offset","stpc_def_offset_hex","scan_start","scan_end",
        "hit_file_offset","hit_relative_offset","mesh_index","mesh_offset","mesh_offset_hex",
        "duplicate_index_for_object","script_x_offset","script_y_offset","script_z_offset",
        "script_yaw_units","script_transform_source",
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
            "script_x_offset": h.script_x_offset,
            "script_y_offset": h.script_y_offset,
            "script_z_offset": h.script_z_offset,
            "script_yaw_units": h.script_yaw_units if h.script_yaw_units is not None else "",
            "script_transform_source": h.script_transform_source,
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
        "terrain_textured_obj": str(textured_terrain_obj.name) if textured_terrain_obj else None,
        "terrain_uv_mapping": "validated game terrain UV mapping",
        "terrain_placement": "MAP tile fixed XYZ + tile yaw + tile_trak_record_index + TRAK local vertices",
        "terrain_yaw_sign": terrain_yaw_sign,
        "world_flip_z": flip_z,
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
        "objects_all_candidates_obj": "objects_all_candidates.obj" if hits else None,
        "objects_by_hit_folder": "objects_by_hit/",
        "objects_primary_obj": str(combined_obj.name) if combined_obj else None,
        "combined_obj": str(world_combined.name) if world_combined else None,
        "terrain_and_objects_obj": str(terrain_and_objects.name) if terrain_and_objects else None,
        "important_note": "Terrain is the validated orientation. STPC instances use MAP object XYZ plus decoded STPC script actor offsets for movement-before-bind, child-spawn, and Section4 route-transform cases, object yaw from the active actor transform, and final object alignment offsets. Full STPC object-definition semantics are still partial; STPC UVs/material texture pages are exported from the current EXE-derived material path where available; use objects_by_hit/ and diagnostics/ for validation.",
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
        terrain_and_objects_obj_path=terrain_and_objects,
    )


# Backwards-compatible name used by earlier project patches.
def export_world_rebuild_export(**kwargs):
    return export_world(**kwargs)

# Backwards-compatible internal name.
def write_world_combined_export_obj(world_dir: Path, *, include_terrain: bool = True) -> Path | None:
    return write_world_combined_obj(world_dir, include_terrain=include_terrain)
