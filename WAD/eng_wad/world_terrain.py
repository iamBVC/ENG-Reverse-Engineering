"""world_terrain.py — textured TRAK terrain export using confirmed sub_556510 UVs."""

from __future__ import annotations

import math
import struct
from pathlib import Path

from .map_full_chunk import MapFullExe
from .trak_chunk import TrakFile
from .material_chunk import RuntimeMaterial


def _i32_from_u32(v: int) -> int:
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0]


def _fixed12_signed_from_u32(v: int) -> float:
    return _i32_from_u32(v) / 4096.0


def _angle4096_to_radians(v: int, *, sign: int = 1) -> float:
    return sign * ((v & 0xFFFF) / 4096.0) * math.tau


def _rotate_xz(x: float, z: float, angle_rad: float) -> tuple[float, float]:
    c = math.cos(angle_rad)
    s = math.sin(angle_rad)
    return (x * c - z * s, x * s + z * c)


def _obj_vertex_line(x: float, y: float, z: float, *, scale: float, flip_z: bool) -> str:
    z2 = -z if flip_z else z
    return f"v {x * scale:.9g} {y * scale:.9g} {z2 * scale:.9g}\n"


def _obj_normal_line(nx: float, ny: float, nz: float, *, flip_z: bool) -> str:
    nz2 = -nz if flip_z else nz
    return f"vn {nx:.9g} {ny:.9g} {nz2:.9g}\n"


def _remap_texture_index(
    *,
    material_index: int,
    raw_texture_index: int,
    texture_count: int,
) -> int | None:
    """Map runtime material texture-page id to exported TEXT PNG index.

    Direct mapping was visually validated for terrain after earlier texture-index
    diagnostics looked worse than the default.
    """
    if texture_count <= 0:
        return None
    raw = raw_texture_index & 0xFF
    return raw if 0 <= raw < texture_count else None


def write_world_mtl(
    path: Path,
    materials: list[RuntimeMaterial] | None = None,
    *,
    texture_prefix: str = "textures",
    texture_count: int | None = None,
) -> None:
    """Write world materials.

    The ordinary terrain/object OBJs still use simple diffuse colours.  When a
    material table is available, we also emit map_Kd bindings for material names
    used by the textured terrain export.

    Terrain texture lookup uses the direct runtime page id, which was the
    visually validated path after texture-index diagnostics were removed.
    """
    mat_by_i = {m.index: m for m in (materials or [])}
    if texture_count is None:
        texture_count = 256
    with path.open("w", encoding="utf-8") as f:
        f.write("# Materials for reconstructed WAD world exports.\n")
        f.write("newmtl trak_surface\nKd 0.55 0.55 0.55\nKa 0 0 0\n\n")
        f.write("newmtl stpc_mat_default\nKd 0.75 0.75 0.75\nKa 0 0 0\n\n")
        # A broad set is enough for most material ids without bloating too much.
        for i in range(1024):
            m = mat_by_i.get(i)
            shade = 0.25 + ((i * 37) % 100) / 160.0
            f.write(f"newmtl stpc_mat_{i:04d}\nKd {shade:.3f} {min(1.0, shade+0.12):.3f} {max(0.0, shade-0.08):.3f}\nKa 0 0 0\n")
            if m is not None and not m.is_color_only:
                tex_i = _remap_texture_index(material_index=i, raw_texture_index=m.texture_index, texture_count=texture_count)
                if tex_i is not None:
                    f.write(f"map_Kd {texture_prefix}/texture_{tex_i:02d}.png\n")
                f.write(f"# raw_texture_page={m.texture_index} texture={tex_i} rect={m.x0},{m.y0}..{m.x1},{m.y1} flags=0x{m.flags:04X}\n")
            f.write("\n")
            f.write(f"newmtl trak_mat_{i:04d}\nKd {shade:.3f} {shade:.3f} {shade:.3f}\nKa 0 0 0\n")
            if m is not None and not m.is_color_only:
                tex_i = _remap_texture_index(material_index=i, raw_texture_index=m.texture_index, texture_count=texture_count)
                if tex_i is not None:
                    f.write(f"map_Kd {texture_prefix}/texture_{tex_i:02d}.png\n")
                f.write(f"# raw_texture_page={m.texture_index} texture={tex_i} material_rect_texels={m.x0},{m.y0},{m.x1},{m.y1} flags=0x{m.flags:04X}\n")
            f.write("\n")




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


def _terrain_sub_556510_uvs(
    mat: RuntimeMaterial | None,
    face_flags: int,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return the terrain UV triplet reconstructed from EXE sub_556510.

    The renderer does *not* use BRender's generic quad flag selector for these
    terrain faces.  In sub_556510, after the material pointer has been resolved
    from TRAK Table B entry +0x08, the code writes per-vertex UVs directly into
    the temporary render vertex buffer:

        output vertex 0: floats at +0x18/+0x1C
        output vertex 1: floats at +0x38/+0x3C
        output vertex 2: floats at +0x58/+0x5C

    The source values are the runtime material floats:

        material +0x04 = u0
        material +0x08 = u1
        material +0x0C = v0
        material +0x10 = v1

    and the selector bits are TRAK face flags:

        0x0800  chooses the upper/lower branch
        0x0010  chooses the alternate top-row branch inside 0x0800
        0x0020  swaps U endpoints inside each branch

    This intentionally mirrors the pseudocode literally, including the fact that
    triangle vertices are consumed in file order i0, i1, i2.
    """
    if mat is None or mat.is_color_only:
        u0, u1, v0, v1 = 0.0, 1.0, 0.0, 1.0
    else:
        u0, u1, v0, v1 = mat.uv_rect(tex_w, tex_h)
    if flip_v_for_obj:
        v0, v1 = 1.0 - v0, 1.0 - v1

    swap_u = bool(face_flags & 0x0020)
    if face_flags & 0x0800:
        if face_flags & 0x0010:
            # sub_556510 LABEL_232 path with V fixed to material +0x0C for
            # vertices 0/1 and +0x10 for vertex 2.
            return (
                (u1 if swap_u else u0, v0),
                (u0 if swap_u else u1, v0),
                (u0 if swap_u else u1, v1),
            )
        # 0x0800 set, 0x0010 clear.
        return (
            (u0 if swap_u else u1, v1),
            (u1 if swap_u else u0, v1),
            (u1 if swap_u else u0, v0),
        )

    # 0x0800 clear.
    return (
        (u0 if swap_u else u1, v1),
        (u1 if swap_u else u0, v1),
        (u0 if swap_u else u1, v0),
    )


def _material_uvs_for_triangle(
    mat: RuntimeMaterial | None,
    *,
    tex_w: int = 256,
    tex_h: int = 256,
    flip_v_for_obj: bool = True,
    tri=None,
) -> tuple[tuple[float, float], tuple[float, float], tuple[float, float]]:
    """Return terrain UVs using the EXE-proven sub_556510 mapping.

    Visual validation confirmed this is the correct path for textured terrain:
    TRAK face flags 0x0800, 0x0010, and 0x0020 select the three UVs from
    the runtime material rectangle.  Older diagnostic UV variants were removed
    from the normal exporter after this mapping was confirmed.
    """
    if tri is not None:
        return _terrain_sub_556510_uvs(mat, tri.flags, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)

    # Fallback for unexpected calls without a TRAK triangle.
    tl, tr, bl, br = _uv_rect_corners(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=flip_v_for_obj)
    return (bl, br, tl)

def write_textured_terrain_obj(
    *,
    path: Path,
    mapx: MapFullExe,
    trak: TrakFile,
    materials: list[RuntimeMaterial],
    scale: float = 1.0,
    flip_z: bool = False,
    terrain_yaw_sign: int = 1,
    mirror_terrain_z: bool = True,
    mtl_name: str = "world.mtl",
) -> Path:
    """Write the default textured terrain OBJ.

    The UV mapping follows the visually confirmed terrain path reconstructed
    from sub_556510: each TRAK face writes UVs directly from the resolved
    runtime material rectangle using face flag bits 0x0800, 0x0010, and 0x0020.
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
        f.write("# Textured terrain export. Texture page + material rectangle are EXE-confirmed.\n")
        f.write("# UV mapping: terrain renderer sub_556510.\n")
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
                uvs = _material_uvs_for_triangle(mat, tex_w=tex_w, tex_h=tex_h, flip_v_for_obj=True, tri=tri)
                for u, v in uvs:
                    f.write(f"vt {u:.9g} {v:.9g}\n")
                a = vbase + tri.i0
                b = vbase + tri.i1
                c = vbase + tri.i2
                f.write(f"f {a}/{vtbase}/{a} {b}/{vtbase+1}/{b} {c}/{vtbase+2}/{c}\n")
                vtbase += 3
            vbase += rec.a_count
    return path



