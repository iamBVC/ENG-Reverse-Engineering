"""trak_viewer.py — HTML viewers for TRAK surfaces.

The local viewer shows each TRAK record in its own local coordinates.  The
MAP-placed viewer uses the executable-confirmed MAP tile definition table and
`tile_trak_record_index[]` to place/rotate records back into level space.
"""

from __future__ import annotations

import json
import math
import struct
from pathlib import Path
from typing import Any


def _read_template(name: str) -> str:
    return (Path(__file__).with_name("templates") / name).read_text(encoding="utf-8")


def _i32_from_u32(v: int) -> int:
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0]


def _fixed12(v: int) -> float:
    return _i32_from_u32(v) / 4096.0


def _angle4096_to_radians(v: int, *, sign: int = 1) -> float:
    return sign * ((v & 0xFFFF) / 4096.0) * math.tau


def _rotate_xz(x: float, z: float, angle_rad: float) -> tuple[float, float]:
    c = math.cos(angle_rad)
    s = math.sin(angle_rad)
    return (x * c - z * s, x * s + z * c)


def _valid_tris(record: Any):
    for tri in record.table_b:
        if not (tri.i0 < record.a_count and tri.i1 < record.a_count and tri.i2 < record.a_count):
            continue
        if len({tri.i0, tri.i1, tri.i2}) != 3:
            continue
        yield tri, record.table_a[tri.i0], record.table_a[tri.i1], record.table_a[tri.i2]


def _render_template(path: Path, *, title: str, description: str, triangles: list[dict], centers: list[dict]) -> None:
    html = _read_template("trak_viewer.html")
    html = html.replace("__TITLE__", title)
    html = html.replace("__DESCRIPTION__", description)
    html = html.replace("__TRIANGLES__", json.dumps(triangles, separators=(",", ":")))
    html = html.replace("__CENTERS__", json.dumps(centers, separators=(",", ":")))
    path.write_text(html, encoding="utf-8")


def write_local_trak_viewer_html(trak: Any, path: Path) -> None:
    """Write the local-coordinate TRAK viewer."""
    triangles: list[dict] = []
    centers: list[dict] = []
    for record in trak.records:
        centers.append({
            "rec": record.index,
            "x": record.center[0], "y": record.center[1], "z": record.center[2],
            "a": record.a_count, "b": record.b_count, "c": record.c_count, "d": record.d_count, "e": record.e_count,
        })
        for tri, va, vb, vc in _valid_tris(record):
            cy = (va.y + vb.y + vc.y) / 3.0
            triangles.append({
                "rec": record.index,
                "tri": tri.index,
                "mat": tri.material_index,
                "flags": tri.flags,
                "cy": cy,
                "p": [[va.x, va.y, va.z], [vb.x, vb.y, vb.z], [vc.x, vc.y, vc.z]],
            })
    _render_template(
        path,
        title="TRAK local surface viewer",
        description="Local record preview; records are not MAP placed.",
        triangles=triangles,
        centers=centers,
    )


def _terrain_z_mirror_center(trak: Any, mapx: Any, *, terrain_yaw_sign: int = 1) -> float | None:
    z_min = None
    z_max = None
    for tile_i, tile in enumerate(mapx.tiles):
        if tile_i >= len(mapx.tile_trak_indices):
            continue
        rec_i = mapx.tile_trak_indices[tile_i]
        if rec_i < 0 or rec_i >= len(trak.records):
            continue
        record = trak.records[rec_i]
        if tile_i < len(mapx.tile_defs):
            tile_def = mapx.tile_defs[tile_i]
            tz = -_fixed12(tile_def.u32_20)
            yaw_units = tile_def.u32_04 & 0xFFFF
        else:
            tz = tile.z
            yaw_units = 0
        yaw = _angle4096_to_radians(yaw_units, sign=terrain_yaw_sign) if yaw_units else 0.0
        for vertex in record.table_a:
            _rx, rz = _rotate_xz(vertex.x, vertex.z, yaw) if yaw else (vertex.x, vertex.z)
            zz = tz + rz
            z_min = zz if z_min is None else min(z_min, zz)
            z_max = zz if z_max is None else max(z_max, zz)
    if z_min is None or z_max is None:
        return None
    return (z_min + z_max) * 0.5


def write_map_placed_trak_viewer_html(
    trak: Any,
    mapx: Any,
    path: Path,
    *,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
) -> None:
    """Write `trak/viewer.html` with TRAK records placed by MAP tile transforms."""
    triangles: list[dict] = []
    centers: list[dict] = []
    mirror_center = _terrain_z_mirror_center(trak, mapx, terrain_yaw_sign=terrain_yaw_sign) if mirror_terrain_z else None

    for tile_i, tile in enumerate(mapx.tiles):
        if tile_i >= len(mapx.tile_trak_indices):
            continue
        rec_i = mapx.tile_trak_indices[tile_i]
        if rec_i < 0 or rec_i >= len(trak.records):
            continue
        record = trak.records[rec_i]
        if tile_i < len(mapx.tile_defs):
            tile_def = mapx.tile_defs[tile_i]
            tx = _fixed12(tile_def.u32_12)
            ty = _fixed12(tile_def.u32_16)
            tz = -_fixed12(tile_def.u32_20)
            yaw_units = tile_def.u32_04 & 0xFFFF
        else:
            tx, ty, tz = tile.x, tile.y, tile.z
            yaw_units = 0
        yaw = _angle4096_to_radians(yaw_units, sign=terrain_yaw_sign) if yaw_units else 0.0

        placed_vertices: list[tuple[float, float, float]] = []
        for vertex in record.table_a:
            rx, rz = _rotate_xz(vertex.x, vertex.z, yaw) if yaw else (vertex.x, vertex.z)
            raw_z = tz + rz
            out_z = (2.0 * mirror_center - raw_z) if mirror_center is not None else raw_z
            placed_vertices.append((tx + rx, ty + vertex.y, out_z))

        if placed_vertices:
            cx = sum(v[0] for v in placed_vertices) / len(placed_vertices)
            cy = sum(v[1] for v in placed_vertices) / len(placed_vertices)
            cz = sum(v[2] for v in placed_vertices) / len(placed_vertices)
            centers.append({"tile": tile_i, "rec": record.index, "x": cx, "y": cy, "z": cz, "a": record.a_count, "b": record.b_count})

        for tri in record.table_b:
            if not (tri.i0 < len(placed_vertices) and tri.i1 < len(placed_vertices) and tri.i2 < len(placed_vertices)):
                continue
            if len({tri.i0, tri.i1, tri.i2}) != 3:
                continue
            pa = placed_vertices[tri.i0]
            pb = placed_vertices[tri.i1]
            pc = placed_vertices[tri.i2]
            cy = (pa[1] + pb[1] + pc[1]) / 3.0
            triangles.append({
                "tile": tile_i,
                "rec": record.index,
                "tri": tri.index,
                "mat": tri.material_index,
                "flags": tri.flags,
                "cy": cy,
                "p": [list(pa), list(pb), list(pc)],
            })

    _render_template(
        path,
        title="TRAK MAP-placed surface viewer",
        description="MAP-placed TRAK terrain; tile translations and yaw are applied.",
        triangles=triangles,
        centers=centers,
    )
