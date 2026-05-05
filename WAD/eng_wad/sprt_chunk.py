"""sprt_chunk.py - SPRT sprite material-base chunk diagnostics.

The game loader does not load image pixels from SPRT.  It reads a base material
index used by the 2D sprite renderer.  Sprite art itself is represented by TEXT
textures plus runtime material rectangles.

Confirmed loader (loc_558AD1):
  u32 material_base_index -> dword_5FF728
  IF WFPC bit 0x100000:
    u32 count
    u32 optional_values[count] -> unk_5FCFA0
All sampled WADs are 4 bytes (no optional table).

Renderer formula (sub_425D40):
  material_index = material_base + sprite_id * 2 + variant_or_frame
  material_ptr   = dword_581154 + material_index * 20   (RuntimeMaterial20)

Runtime sprite object (SpriteObject64, stride 0x40, 15 instances at 0x573410):
  +0x00  u16  alpha          0=invisible, 0x7F=max; guard for draw function
  +0x02  u8   countdown      fade delay counter
  +0x03  u8   direction      1=fade-in, 0=fade-out
  +0x05  u8   frame_idx      current animation frame
  +0x06  u8   unk (init 1)
  +0x07  u8   loop_flag
  +0x08  u8   scale_flag
  +0x0C  u32  sprite_id      slot: material_base + id*2 + variant
  +0x14  u32  anim_pos
  +0x18  i32  screen_x       init -32 (off-screen)
  +0x28  i32  screen_x_int   if nonzero, integer x override
  +0x2C  u8   anim_mode      0=frame_idx*2, nonzero=use frame_table
  +0x2F  u8[] frame_table    lookup indexed by frame_idx when anim_mode!=0

Known sprite_id ranges (from static BSS data section defaults):
  2/6/8, 3/7/9  character-form pairs (3 game-state variants)
  0x0A-0x11     8-frame animation set
  0x13-0x22     16-frame animation set
  0x23-0x2A     8-frame animation set
  0x33-0x3A     8-frame animation set (primary HUD element)
  0x41+         positional/dynamic sprites
  0x45-0x4C     8-frame animation set
  0x4D = 77     fixed HUD sprite at screen (32, 166)
  0x5A+         positional/dynamic sprite
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path

from .material_chunk import RuntimeMaterial


@dataclass(frozen=True)
class SprtChunk:
    """Decoded SPRT chunk.

    `material_base_index` is copied to executable global `dword_5FF728`.
    If WFPC flags bit 0x100000 is already active, the loader also reads an
    optional u32 table into `unk_5FCFA0`; none of the currently sampled level
    WADs use that extended payload.
    """

    material_base_index: int
    optional_table: list[int]
    raw_size: int

    @property
    def optional_table_count(self) -> int:
        return len(self.optional_table)


def parse_sprt_chunk(data: bytes) -> SprtChunk:
    if len(data) < 4:
        raise ValueError(f"SPRT chunk is too small: {len(data)} bytes")
    material_base_index = struct.unpack_from("<I", data, 0)[0]
    optional_table: list[int] = []
    if len(data) >= 8:
        count = struct.unpack_from("<I", data, 4)[0]
        need = 8 + count * 4
        if need > len(data):
            raise ValueError(f"SPRT optional table count {count} needs {need} bytes, chunk has {len(data)}")
        optional_table = [struct.unpack_from("<I", data, 8 + i * 4)[0] for i in range(count)]
    elif len(data) != 4:
        raise ValueError(f"SPRT chunk has unsupported trailing byte count: {len(data)}")
    return SprtChunk(material_base_index=material_base_index, optional_table=optional_table, raw_size=len(data))


def export_sprt(
    sprt: SprtChunk,
    out_dir: Path,
    *,
    materials: list[RuntimeMaterial] | None = None,
    texture_count: int | None = None,
) -> dict:
    """Export SPRT diagnostics and sprite material-slot mapping."""

    out_dir.mkdir(parents=True, exist_ok=True)
    materials = materials or []
    mat_by_i = {m.index: m for m in materials}
    material_count = len(materials)
    remaining = max(0, material_count - sprt.material_base_index)
    sprite_slot_count = remaining // 2 if material_count else 0

    summary = {
        "raw_size": sprt.raw_size,
        "material_base_index": sprt.material_base_index,
        "optional_table_count": sprt.optional_table_count,
        "material_count": material_count,
        "texture_count": texture_count if texture_count is not None else "",
        "remaining_materials_from_base": remaining if material_count else "",
        "paired_sprite_slot_count_from_materials": sprite_slot_count if material_count else "",
        "confirmed_loader": "SPRT first u32 is copied to dword_5FF728; sprite renderer uses it as material_base + sprite_id*2 + variant/frame.",
    }

    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    with (out_dir / "sprite_material_slots.csv").open("w", newline="", encoding="utf-8") as f:
        fieldnames = [
            "sprite_slot", "variant", "material_index", "material_exists",
            "texture_index", "texture_exists", "x0", "y0", "x1", "y1", "flags_hex",
        ]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        limit = sprite_slot_count if material_count else 0
        for slot in range(limit):
            for variant in range(2):
                mat_i = sprt.material_base_index + slot * 2 + variant
                m = mat_by_i.get(mat_i)
                tex_i = m.texture_index if m is not None else ""
                w.writerow({
                    "sprite_slot": slot,
                    "variant": variant,
                    "material_index": mat_i,
                    "material_exists": m is not None,
                    "texture_index": tex_i,
                    "texture_exists": (0 <= tex_i < texture_count) if (m is not None and texture_count is not None) else "",
                    "x0": m.x0 if m is not None else "",
                    "y0": m.y0 if m is not None else "",
                    "x1": m.x1 if m is not None else "",
                    "y1": m.y1 if m is not None else "",
                    "flags_hex": f"0x{m.flags:04X}" if m is not None else "",
                })

    if sprt.optional_table:
        with (out_dir / "optional_table.csv").open("w", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(f, fieldnames=["index", "value", "value_hex"])
            w.writeheader()
            for i, value in enumerate(sprt.optional_table):
                w.writerow({"index": i, "value": value, "value_hex": f"0x{value:08X}"})

    return summary
