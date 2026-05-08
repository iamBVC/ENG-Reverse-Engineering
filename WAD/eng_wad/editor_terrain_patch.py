"""Serialize WAD editor terrain edits back into MAP/TRAK chunks.

Chunk-level moves are saved as MAP tile definition translation changes.
Residual vertex edits are saved into TRAK Table A.  TRAK Table B plane
equations are refreshed for triangles that reference edited vertices so the
render/collision surface data stays coherent.
"""

from __future__ import annotations

import math
import struct
from dataclasses import dataclass
from typing import Any

EPSILON = 1.0e-4


@dataclass
class TerrainPatchResult:
    map_data: bytes
    trak_data: bytes
    map_changed: bool = False
    trak_changed: bool = False
    moved_tiles: int = 0
    patched_vertices: int = 0
    patched_planes: int = 0

    @property
    def changed(self) -> bool:
        return self.map_changed or self.trak_changed


def serialize_scene_terrain_edits(
    scene: Any,
    mapx: Any,
    trak: Any,
    map_data: bytes,
    trak_data: bytes,
    *,
    terrain_yaw_sign: int = 1,
    epsilon: float = EPSILON,
) -> TerrainPatchResult:
    """Patch MAP/TRAK bytes so the edited SceneData terrain can be saved."""

    map_out = bytearray(map_data)
    trak_out = bytearray(trak_data)
    transforms = [_tile_transform(mapx, i, terrain_yaw_sign) for i in range(len(mapx.tiles))]
    tile_offsets = _detect_uniform_tile_offsets(scene, mapx, trak, transforms, epsilon)
    vertex_updates = _collect_vertex_updates(scene, mapx, trak, transforms, tile_offsets, epsilon)

    moved_tiles = _apply_tile_offsets(map_out, mapx, tile_offsets, epsilon)
    patched_vertices = _apply_vertex_updates(trak_out, trak, vertex_updates, epsilon)
    patched_planes = _refresh_touched_planes(trak_out, trak, set(vertex_updates), epsilon) if patched_vertices else 0
    if moved_tiles or patched_vertices:
        _sync_scene_terrain(scene, mapx, trak, terrain_yaw_sign)

    return TerrainPatchResult(
        map_data=bytes(map_out),
        trak_data=bytes(trak_out),
        map_changed=moved_tiles > 0,
        trak_changed=patched_vertices > 0 or patched_planes > 0,
        moved_tiles=moved_tiles,
        patched_vertices=patched_vertices,
        patched_planes=patched_planes,
    )


def _fixed12_signed(v: int) -> float:
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0] / 4096.0


def _pack_fixed12(v: float) -> int:
    return int(round(v * 4096.0)) & 0xFFFFFFFF


def _rotate_xz(x: float, z: float, angle: float) -> tuple[float, float]:
    c, s = math.cos(angle), math.sin(angle)
    return x * c - z * s, x * s + z * c


def _tile_transform(mapx: Any, tile_i: int, terrain_yaw_sign: int) -> dict[str, Any]:
    td = mapx.tile_defs[tile_i] if tile_i < len(mapx.tile_defs) else None
    if td is not None:
        tx = _fixed12_signed(td.u32_12)
        ty = _fixed12_signed(td.u32_16)
        raw_z = _fixed12_signed(td.u32_20)
        tz = -raw_z
        yaw_units = td.u32_04 & 0xFFFF
    else:
        tile = mapx.tiles[tile_i]
        tx, ty, tz = tile.x, tile.y, tile.z
        raw_z = -tz
        yaw_units = 0
    yaw = terrain_yaw_sign * (yaw_units / 4096.0) * math.tau if yaw_units else 0.0
    return {"td": td, "tx": tx, "ty": ty, "tz": tz, "raw_z": raw_z, "yaw": yaw}


def _world_from_local(v: Any, transform: dict[str, Any]) -> list[float]:
    yaw = transform["yaw"]
    rx, rz = _rotate_xz(v.x, v.z, yaw) if yaw else (v.x, v.z)
    return [
        transform["tx"] + rx,
        transform["ty"] + v.y,
        -(transform["tz"] + rz),
    ]


def _local_from_world(p: list[float], transform: dict[str, Any]) -> tuple[float, float, float]:
    rx = p[0] - transform["tx"]
    rz = -p[2] - transform["tz"]
    yaw = transform["yaw"]
    lx, lz = _rotate_xz(rx, rz, -yaw) if yaw else (rx, rz)
    return lx, p[1] - transform["ty"], lz


def _dist(a: tuple[float, float, float] | list[float], b: tuple[float, float, float] | list[float]) -> float:
    return max(abs(a[0] - b[0]), abs(a[1] - b[1]), abs(a[2] - b[2]))


def _scene_tri_original(
    mapx: Any,
    trak: Any,
    meta: dict[str, int],
    transforms: list[dict[str, Any]],
) -> tuple[list[list[float]], tuple[int, int, int]] | None:
    tile_i = meta.get("tile_index", -1)
    rec_i = meta.get("trak_index", -1)
    if tile_i < 0 or tile_i >= len(transforms) or rec_i < 0 or rec_i >= len(trak.records):
        return None
    rec = trak.records[rec_i]
    rec_tri_i = meta.get("record_tri_index", -1)
    if rec_tri_i < 0 or rec_tri_i >= len(rec.table_b):
        return None
    tri = rec.table_b[rec_tri_i]
    indices = (meta.get("i0", tri.i0), meta.get("i1", tri.i1), meta.get("i2", tri.i2))
    if any(i < 0 or i >= len(rec.table_a) for i in indices):
        return None
    verts = [_world_from_local(rec.table_a[i], transforms[tile_i]) for i in indices]
    return verts, indices


def _detect_uniform_tile_offsets(
    scene: Any,
    mapx: Any,
    trak: Any,
    transforms: list[dict[str, Any]],
    epsilon: float,
) -> dict[int, tuple[float, float, float]]:
    samples: dict[int, list[tuple[float, float, float]]] = {}
    for tri_i, (verts, _cy) in enumerate(scene.terrain_tris):
        if tri_i >= len(scene.terrain_meta):
            continue
        meta = scene.terrain_meta[tri_i]
        tile_i = meta.get("tile_index", -1)
        if tile_i < 0 or tile_i >= len(transforms) or transforms[tile_i]["td"] is None:
            continue
        original = _scene_tri_original(mapx, trak, meta, transforms)
        if original is None:
            continue
        orig_verts, _indices = original
        bucket = samples.setdefault(tile_i, [])
        for p, o in zip(verts, orig_verts):
            bucket.append((p[0] - o[0], p[1] - o[1], p[2] - o[2]))

    offsets: dict[int, tuple[float, float, float]] = {}
    for tile_i, deltas in samples.items():
        if not deltas:
            continue
        # A chunk move gives almost every vertex in a tile the same world-space
        # delta.  Allow a few outliers so "move chunk, then tweak one triangle"
        # still serializes as MAP translation plus residual TRAK edits.
        buckets: dict[tuple[int, int, int], list[tuple[float, float, float]]] = {}
        scale = max(epsilon * 4.0, 1.0e-5)
        for d in deltas:
            key = (round(d[0] / scale), round(d[1] / scale), round(d[2] / scale))
            buckets.setdefault(key, []).append(d)
        best = max(buckets.values(), key=len)
        offset = (
            sum(d[0] for d in best) / len(best),
            sum(d[1] for d in best) / len(best),
            sum(d[2] for d in best) / len(best),
        )
        if _dist(offset, (0.0, 0.0, 0.0)) <= epsilon:
            continue
        allowed_outliers = max(3, len(deltas) // 20)
        if len(deltas) - len(best) <= allowed_outliers:
            offsets[tile_i] = offset
    return offsets


def _collect_vertex_updates(
    scene: Any,
    mapx: Any,
    trak: Any,
    transforms: list[dict[str, Any]],
    tile_offsets: dict[int, tuple[float, float, float]],
    epsilon: float,
) -> dict[tuple[int, int], tuple[float, float, float]]:
    sums: dict[tuple[int, int], list[float]] = {}
    for tri_i, (verts, _cy) in enumerate(scene.terrain_tris):
        if tri_i >= len(scene.terrain_meta):
            continue
        meta = scene.terrain_meta[tri_i]
        tile_i = meta.get("tile_index", -1)
        rec_i = meta.get("trak_index", -1)
        original = _scene_tri_original(mapx, trak, meta, transforms)
        if original is None:
            continue
        orig_verts, indices = original
        dx, dy, dz = tile_offsets.get(tile_i, (0.0, 0.0, 0.0))
        rec = trak.records[rec_i]
        for p, o, vertex_i in zip(verts, orig_verts, indices):
            residual = [p[0] - dx, p[1] - dy, p[2] - dz]
            if _dist(residual, o) <= epsilon:
                continue
            lx, ly, lz = _local_from_world(residual, transforms[tile_i])
            old = rec.table_a[vertex_i]
            if _dist((lx, ly, lz), (old.x, old.y, old.z)) <= epsilon:
                continue
            bucket = sums.setdefault((rec_i, vertex_i), [0.0, 0.0, 0.0, 0.0])
            bucket[0] += lx
            bucket[1] += ly
            bucket[2] += lz
            bucket[3] += 1.0

    return {
        key: (vals[0] / vals[3], vals[1] / vals[3], vals[2] / vals[3])
        for key, vals in sums.items()
        if vals[3] > 0.0
    }


def _apply_tile_offsets(
    map_out: bytearray,
    mapx: Any,
    tile_offsets: dict[int, tuple[float, float, float]],
    epsilon: float,
) -> int:
    changed = 0
    for tile_i, (dx, dy, dz) in sorted(tile_offsets.items()):
        if _dist((dx, dy, dz), (0.0, 0.0, 0.0)) <= epsilon or tile_i >= len(mapx.tile_defs):
            continue
        td = mapx.tile_defs[tile_i]
        off = td.file_offset
        vals = (
            _pack_fixed12(_fixed12_signed(td.u32_12) + dx),
            _pack_fixed12(_fixed12_signed(td.u32_16) + dy),
            _pack_fixed12(_fixed12_signed(td.u32_20) + dz),
        )
        if off + 24 > len(map_out):
            continue
        struct.pack_into("<III", map_out, off + 12, *vals)
        td.u32_12, td.u32_16, td.u32_20 = vals
        changed += 1
    return changed


def _apply_vertex_updates(
    trak_out: bytearray,
    trak: Any,
    updates: dict[tuple[int, int], tuple[float, float, float]],
    epsilon: float,
) -> int:
    changed = 0
    for (rec_i, vertex_i), (x, y, z) in sorted(updates.items()):
        if rec_i < 0 or rec_i >= len(trak.records):
            continue
        rec = trak.records[rec_i]
        if vertex_i < 0 or vertex_i >= len(rec.table_a):
            continue
        v = rec.table_a[vertex_i]
        if _dist((x, y, z), (v.x, v.y, v.z)) <= epsilon:
            continue
        if v.file_offset + 12 > len(trak_out):
            continue
        struct.pack_into("<3f", trak_out, v.file_offset, x, y, z)
        v.x, v.y, v.z = x, y, z
        changed += 1
    return changed


def _refresh_touched_planes(
    trak_out: bytearray,
    trak: Any,
    touched_vertices: set[tuple[int, int]],
    epsilon: float,
) -> int:
    touched_by_record: dict[int, set[int]] = {}
    for rec_i, vertex_i in touched_vertices:
        touched_by_record.setdefault(rec_i, set()).add(vertex_i)

    changed = 0
    for rec_i, vertex_indices in touched_by_record.items():
        if rec_i < 0 or rec_i >= len(trak.records):
            continue
        rec = trak.records[rec_i]
        for tri in rec.table_b:
            if not ({tri.i0, tri.i1, tri.i2} & vertex_indices):
                continue
            if any(i < 0 or i >= len(rec.table_a) for i in (tri.i0, tri.i1, tri.i2)):
                continue
            plane = _plane_from_vertices(rec.table_a[tri.i0], rec.table_a[tri.i1], rec.table_a[tri.i2])
            if plane is None:
                continue
            nx, ny, nz, d = plane
            old = (tri.plane_nx, tri.plane_ny, tri.plane_nz, tri.plane_d)
            if _dist((nx, ny, nz), old[:3]) <= epsilon and abs(d - old[3]) <= epsilon:
                continue
            if tri.file_offset + 28 > len(trak_out):
                continue
            struct.pack_into("<4f", trak_out, tri.file_offset + 12, nx, ny, nz, d)
            tri.plane_nx, tri.plane_ny, tri.plane_nz, tri.plane_d = nx, ny, nz, d
            changed += 1
    return changed


def _plane_from_vertices(a: Any, b: Any, c: Any) -> tuple[float, float, float, float] | None:
    ux, uy, uz = b.x - a.x, b.y - a.y, b.z - a.z
    vx, vy, vz = c.x - a.x, c.y - a.y, c.z - a.z
    nx = uy * vz - uz * vy
    ny = uz * vx - ux * vz
    nz = ux * vy - uy * vx
    length = math.sqrt(nx * nx + ny * ny + nz * nz)
    if length <= 1.0e-9:
        return None
    nx, ny, nz = nx / length, ny / length, nz / length
    d = -(nx * a.x + ny * a.y + nz * a.z)
    return nx, ny, nz, d


def _sync_scene_terrain(scene: Any, mapx: Any, trak: Any, terrain_yaw_sign: int) -> None:
    """Make the viewport geometry match the saved MAP/TRAK topology."""
    transforms = [_tile_transform(mapx, i, terrain_yaw_sign) for i in range(len(mapx.tiles))]
    xs: list[float] = []
    ys: list[float] = []
    zs: list[float] = []
    for tri_i, (_old_verts, _old_cy) in enumerate(scene.terrain_tris):
        if tri_i >= len(scene.terrain_meta):
            continue
        original = _scene_tri_original(mapx, trak, scene.terrain_meta[tri_i], transforms)
        if original is None:
            continue
        verts, _indices = original
        cy = (verts[0][1] + verts[1][1] + verts[2][1]) / 3.0
        scene.terrain_tris[tri_i] = (verts, cy)
        for v in verts:
            xs.append(v[0]); ys.append(v[1]); zs.append(v[2])
    for p in getattr(scene, "object_positions", []) or []:
        xs.append(p[0]); ys.append(p[1]); zs.append(p[2])
    if xs:
        scene.bounds = (min(xs), min(ys), min(zs), max(xs), max(ys), max(zs))
    if hasattr(scene, "rebuild_terrain_numpy"):
        scene.rebuild_terrain_numpy()
