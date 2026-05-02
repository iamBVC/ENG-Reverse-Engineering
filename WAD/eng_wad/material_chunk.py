"""
material_chunk.py — executable-informed TEXT material/UV table exports.

The trailing table after the TEXT texture records was originally treated as a
palette.  The renderer pseudocode shows it is actually expanded into 20-byte
runtime material records at dword_581154.  The 8 disk bytes map sparsely into
that runtime record:

    disk[0..1] -> runtime +0x00 u16 flags
    disk[2]    -> runtime +0x02 signed/unsigned texture page index
    disk[3]    -> runtime +0x03 extra/source/animation index, often 0xFF
    disk[4]    -> runtime +0x04 source x0 texel
    disk[5]    -> runtime +0x08 source x1 texel
    disk[6]    -> runtime +0x0C source y0 texel
    disk[7]    -> runtime +0x10 source y1 texel

sub_407240 then converts these texel rectangles to UV floats:

    u0 = x0 / texture_width
    u1 = (x1 + 1) / texture_width
    v0 = y0 / texture_height
    v1 = (y1 + 1) / texture_height

Some flags request padded/doubled copy operations for runtime texture pages;
those are preserved as diagnostics but not fully emulated yet.
"""

from __future__ import annotations

import csv
import json
import shutil
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from .text_chunk import TextChunk
from .trak_chunk import TrakFile
from .stpc_chunk import STPCExportResult


@dataclass(frozen=True)
class RuntimeMaterial:
    index: int
    flags: int
    texture_index: int
    extra: int
    x0: int
    x1: int
    y0: int
    y1: int

    @property
    def is_color_only(self) -> bool:
        # Renderer checks flags & 1 and calls funcs_42EBE7 on bytes +4,+8,+12,+16
        # instead of using a texture page.
        return bool(self.flags & 0x0001)

    @property
    def blend_mode(self) -> int:
        return (self.flags >> 12) & 0x7

    @property
    def flip_or_alpha_bit_2(self) -> bool:
        return bool(self.flags & 0x0002)

    @property
    def padded_border(self) -> bool:
        return bool(self.flags & 0x0004)

    @property
    def double_width(self) -> bool:
        return bool(self.flags & 0x0008)

    @property
    def double_height(self) -> bool:
        return bool(self.flags & 0x0010)

    @property
    def generated_page(self) -> bool:
        # sub_407240 sets bit 0x20 when splitting animated/packed materials to
        # generated 256x256 pages.
        return bool(self.flags & 0x0020)

    def rect_width(self) -> int:
        w = self.x1 - self.x0 + 1
        if self.double_width:
            w *= 2
        if self.padded_border:
            w += 2
        return w

    def rect_height(self) -> int:
        h = self.y1 - self.y0 + 1
        if self.double_height:
            h *= 2
        if self.padded_border:
            h += 2
        return h

    def uv_rect(self, tex_w: int = 256, tex_h: int = 256) -> tuple[float, float, float, float]:
        # These are the exact base formulas used by sub_407240 for ordinary
        # non-generated material records.  V is not flipped here; OBJ exporters
        # can choose whether to invert V for their target viewer.
        return (
            self.x0 / float(tex_w),
            (self.x1 + 1) / float(tex_w),
            self.y0 / float(tex_h),
            (self.y1 + 1) / float(tex_h),
        )


def parse_runtime_materials(text: TextChunk) -> list[RuntimeMaterial]:
    mats: list[RuntimeMaterial] = []
    for i in range(text.pal_count):
        e = text.pal_raw[i * 8:(i + 1) * 8]
        if len(e) < 8:
            break
        flags = e[0] | (e[1] << 8)
        # In the EXE this is sometimes read as signed char, but observed texture
        # page indices are ordinary non-negative bytes.  Keep the raw unsigned
        # value; diagnostic CSV exposes it directly.
        mats.append(RuntimeMaterial(
            index=i,
            flags=flags,
            texture_index=e[2],
            extra=e[3],
            x0=e[4],
            x1=e[5],
            y0=e[6],
            y1=e[7],
        ))
    return mats


def _write_csv(path: Path, fieldnames: list[str], rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            w.writerow(row)


def collect_trak_material_usage(trak: TrakFile) -> Counter[int]:
    c: Counter[int] = Counter()
    for rec in trak.records:
        for tri in rec.table_b:
            c[tri.material_index] += 1
    return c


def collect_stpc_material_usage(stpc_result: STPCExportResult | None) -> Counter[int]:
    c: Counter[int] = Counter()
    if stpc_result is None:
        return c
    for mesh in stpc_result.meshes:
        for tri in mesh.triangles:
            c[tri.material] += 1
    return c


def export_material_diagnostics(
    *,
    text: TextChunk,
    out_dir: Path,
    trak: TrakFile | None = None,
    stpc_result: STPCExportResult | None = None,
    terrain_texture_hint_range: range = range(5, 10),
) -> list[RuntimeMaterial]:
    """Export material/texture binding diagnostics.

    Returns the parsed runtime material rows so callers can use them for OBJ/MTL
    generation.
    """
    mats = parse_runtime_materials(text)
    out_dir.mkdir(parents=True, exist_ok=True)

    tex_sizes = {t.index: (t.width, t.height) for t in text.textures}
    max_tex = len(text.textures) - 1

    _write_csv(out_dir / "runtime_material_table_20.csv", [
        "material_index", "flags_hex", "flags_dec", "texture_index", "texture_exists", "extra_byte",
        "x0", "x1", "y0", "y1", "rect_width_effective", "rect_height_effective",
        "u0", "u1", "v0", "v1", "is_color_only", "blend_mode", "flag_0002", "padded_border", "double_width", "double_height", "generated_page", "terrain_texture_hint",
    ], (
        {
            "material_index": m.index,
            "flags_hex": f"0x{m.flags:04X}",
            "flags_dec": m.flags,
            "texture_index": m.texture_index,
            "texture_exists": 0 <= m.texture_index <= max_tex,
            "extra_byte": m.extra,
            "x0": m.x0, "x1": m.x1, "y0": m.y0, "y1": m.y1,
            "rect_width_effective": m.rect_width(),
            "rect_height_effective": m.rect_height(),
            "u0": m.uv_rect(*tex_sizes.get(m.texture_index, (256, 256)))[0],
            "u1": m.uv_rect(*tex_sizes.get(m.texture_index, (256, 256)))[1],
            "v0": m.uv_rect(*tex_sizes.get(m.texture_index, (256, 256)))[2],
            "v1": m.uv_rect(*tex_sizes.get(m.texture_index, (256, 256)))[3],
            "is_color_only": m.is_color_only,
            "blend_mode": m.blend_mode,
            "flag_0002": m.flip_or_alpha_bit_2,
            "padded_border": m.padded_border,
            "double_width": m.double_width,
            "double_height": m.double_height,
            "generated_page": m.generated_page,
            "terrain_texture_hint": m.texture_index in terrain_texture_hint_range,
        } for m in mats
    ))

    _write_csv(out_dir / "texture_inventory.csv", [
        "texture_index", "filename", "width", "height", "flags_hex", "compressed_size", "terrain_texture_hint",
    ], (
        {
            "texture_index": t.index,
            "filename": f"texture_{t.index:02d}.png",
            "width": t.width,
            "height": t.height,
            "flags_hex": f"0x{t.flags:08X}",
            "compressed_size": t.comp_size,
            "terrain_texture_hint": t.index in terrain_texture_hint_range,
        } for t in text.textures
    ))

    trak_usage = collect_trak_material_usage(trak) if trak is not None else Counter()
    stpc_usage = collect_stpc_material_usage(stpc_result)
    mat_by_i = {m.index: m for m in mats}

    _write_csv(out_dir / "trak_terrain_material_usage.csv", [
        "material_index", "triangle_count", "texture_index", "texture_exists", "x0", "x1", "y0", "y1", "u0", "u1", "v0", "v1", "flags_hex", "terrain_texture_hint",
    ], (
        {
            "material_index": idx,
            "triangle_count": count,
            "texture_index": mat_by_i[idx].texture_index if idx in mat_by_i else "",
            "texture_exists": (0 <= mat_by_i[idx].texture_index <= max_tex) if idx in mat_by_i else False,
            "x0": mat_by_i[idx].x0 if idx in mat_by_i else "",
            "x1": mat_by_i[idx].x1 if idx in mat_by_i else "",
            "y0": mat_by_i[idx].y0 if idx in mat_by_i else "",
            "y1": mat_by_i[idx].y1 if idx in mat_by_i else "",
            "u0": mat_by_i[idx].uv_rect(*tex_sizes.get(mat_by_i[idx].texture_index, (256, 256)))[0] if idx in mat_by_i else "",
            "u1": mat_by_i[idx].uv_rect(*tex_sizes.get(mat_by_i[idx].texture_index, (256, 256)))[1] if idx in mat_by_i else "",
            "v0": mat_by_i[idx].uv_rect(*tex_sizes.get(mat_by_i[idx].texture_index, (256, 256)))[2] if idx in mat_by_i else "",
            "v1": mat_by_i[idx].uv_rect(*tex_sizes.get(mat_by_i[idx].texture_index, (256, 256)))[3] if idx in mat_by_i else "",
            "flags_hex": f"0x{mat_by_i[idx].flags:04X}" if idx in mat_by_i else "",
            "terrain_texture_hint": (mat_by_i[idx].texture_index in terrain_texture_hint_range) if idx in mat_by_i else False,
        } for idx, count in trak_usage.most_common()
    ))

    _write_csv(out_dir / "stpc_material_usage.csv", [
        "material_index", "triangle_count", "texture_index", "texture_exists", "x0", "x1", "y0", "y1", "flags_hex",
    ], (
        {
            "material_index": idx,
            "triangle_count": count,
            "texture_index": mat_by_i[idx].texture_index if idx in mat_by_i else "",
            "texture_exists": (0 <= mat_by_i[idx].texture_index <= max_tex) if idx in mat_by_i else False,
            "x0": mat_by_i[idx].x0 if idx in mat_by_i else "",
            "x1": mat_by_i[idx].x1 if idx in mat_by_i else "",
            "y0": mat_by_i[idx].y0 if idx in mat_by_i else "",
            "y1": mat_by_i[idx].y1 if idx in mat_by_i else "",
            "flags_hex": f"0x{mat_by_i[idx].flags:04X}" if idx in mat_by_i else "",
        } for idx, count in stpc_usage.most_common()
    ))

    # Per-texture usage summary helps verify your hint that texture_05..09 are
    # mostly terrain pages.
    tex_usage = defaultdict(lambda: {"terrain_triangles": 0, "stpc_triangles": 0, "materials": set()})
    for idx, count in trak_usage.items():
        m = mat_by_i.get(idx)
        if m:
            row = tex_usage[m.texture_index]
            row["terrain_triangles"] += count
            row["materials"].add(idx)
    for idx, count in stpc_usage.items():
        m = mat_by_i.get(idx)
        if m:
            row = tex_usage[m.texture_index]
            row["stpc_triangles"] += count
            row["materials"].add(idx)
    _write_csv(out_dir / "texture_material_usage_summary.csv", [
        "texture_index", "terrain_triangles", "stpc_triangles", "material_count", "material_indices", "terrain_texture_hint",
    ], (
        {
            "texture_index": tex_i,
            "terrain_triangles": info["terrain_triangles"],
            "stpc_triangles": info["stpc_triangles"],
            "material_count": len(info["materials"]),
            "material_indices": " ".join(str(x) for x in sorted(info["materials"])),
            "terrain_texture_hint": tex_i in terrain_texture_hint_range,
        } for tex_i, info in sorted(tex_usage.items())
    ))

    summary = {
        "material_count": len(mats),
        "texture_count": len(text.textures),
        "trak_unique_materials": len(trak_usage),
        "stpc_unique_materials": len(stpc_usage),
        "terrain_texture_hint_indices": list(terrain_texture_hint_range),
        "confirmed_from_exe": {
            "material_stride": 20,
            "texture_page_field": "runtime material +0x02",
            "source_rect_fields": "+0x04 x0, +0x08 x1, +0x0C y0, +0x10 y1",
            "uv_formula": "x0/w, (x1+1)/w, y0/h, (y1+1)/h",
        },
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "README_materials.txt").write_text(
        "TEXT trailing 8-byte rows are expanded by the EXE into dword_581154 20-byte material records.\n"
        "The important fields are texture_index and x0/x1/y0/y1.\n"
        "UVs are confirmed for the material rectangle, but per-triangle corner orientation is still a probe.\n",
        encoding="utf-8",
    )
    return mats


def copy_textures_for_world(textures_dir: Path, world_textures_dir: Path) -> None:
    world_textures_dir.mkdir(parents=True, exist_ok=True)
    if not textures_dir.exists():
        return
    for p in sorted(textures_dir.glob("texture_*.png")):
        # Skip old diagnostic variants if present.
        if "_field_" in p.name or p.name.endswith("_grey.png") or p.name.endswith("_pal.png"):
            continue
        shutil.copy2(p, world_textures_dir / p.name)
