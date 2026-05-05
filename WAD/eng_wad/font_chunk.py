"""font_chunk.py - executable-confirmed FONT glyph metrics.

The FONT chunk is loaded by sub_558C90.  The loader allocates 0x800 bytes,
reads 256 records, and stores the table pointer in both the WAD context at
+0x10 and global dword_6DA354.
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path

from .material_chunk import RuntimeMaterial


FONT_RECORD_COUNT = 256
FONT_RECORD_SIZE = 8
FONT_CHUNK_SIZE = FONT_RECORD_COUNT * FONT_RECORD_SIZE
SPACE_ADVANCE = 10


@dataclass(frozen=True)
class FontGlyph:
    """One 8-byte FONT table entry."""

    codepoint: int
    material_index_00: int
    y_center_offset_02: int
    advance_width_04: int
    draw_height_06: int

    @property
    def is_defined(self) -> bool:
        return any((
            self.material_index_00,
            self.y_center_offset_02,
            self.advance_width_04,
            self.draw_height_06,
        ))

    @property
    def char_display(self) -> str:
        if self.codepoint == 0:
            return "\\0"
        if self.codepoint == 9:
            return "\\t"
        if self.codepoint == 10:
            return "\\n"
        if self.codepoint == 13:
            return "\\r"
        if self.codepoint == 32:
            return "space"
        ch = chr(self.codepoint)
        if ch.isprintable():
            return ch
        return ""


@dataclass(frozen=True)
class FontChunk:
    """Decoded 256-entry FONT table."""

    glyphs: list[FontGlyph]
    raw_size: int

    def text_width(self, text: str) -> int:
        """Match the common text-width path: space is a hardcoded 10 pixels."""

        width = 0
        for ch in text:
            code = ord(ch) & 0xFF
            if code == 0:
                break
            if code == 32:
                width += SPACE_ADVANCE
            else:
                width += self.glyphs[code].advance_width_04
        return width


def parse_font_chunk(data: bytes) -> FontChunk:
    if len(data) != FONT_CHUNK_SIZE:
        raise ValueError(f"FONT chunk must be exactly 0x800 bytes, got {len(data)}")

    glyphs = []
    for codepoint in range(FONT_RECORD_COUNT):
        off = codepoint * FONT_RECORD_SIZE
        glyphs.append(FontGlyph(
            codepoint=codepoint,
            material_index_00=struct.unpack_from("<H", data, off + 0)[0],
            y_center_offset_02=struct.unpack_from("<H", data, off + 2)[0],
            advance_width_04=struct.unpack_from("<H", data, off + 4)[0],
            draw_height_06=struct.unpack_from("<H", data, off + 6)[0],
        ))
    return FontChunk(glyphs=glyphs, raw_size=len(data))


def export_font(
    font: FontChunk,
    out_dir: Path,
    *,
    materials: list[RuntimeMaterial] | None = None,
    texture_count: int | None = None,
) -> dict:
    """Export FONT metrics and optional material/texture cross-references."""

    out_dir.mkdir(parents=True, exist_ok=True)
    materials = materials or []
    mat_by_i = {m.index: m for m in materials}
    defined = [g for g in font.glyphs if g.is_defined]
    material_indices = [g.material_index_00 for g in defined]
    advance_values = [g.advance_width_04 for g in defined]
    height_values = [g.draw_height_06 for g in defined]
    material_ref_existing_count = sum(1 for g in defined if g.material_index_00 in mat_by_i) if materials else ""

    summary = {
        "raw_size": font.raw_size,
        "record_count": len(font.glyphs),
        "record_size": FONT_RECORD_SIZE,
        "defined_glyph_count": len(defined),
        "space_advance_hardcoded": SPACE_ADVANCE,
        "material_index_min": min(material_indices) if material_indices else "",
        "material_index_max": max(material_indices) if material_indices else "",
        "advance_width_min": min(advance_values) if advance_values else "",
        "advance_width_max": max(advance_values) if advance_values else "",
        "draw_height_min": min(height_values) if height_values else "",
        "draw_height_max": max(height_values) if height_values else "",
        "material_count": len(materials),
        "defined_glyph_material_refs_found": material_ref_existing_count,
        "defined_glyph_material_refs_missing": (len(defined) - material_ref_existing_count) if materials else "",
        "texture_count": texture_count if texture_count is not None else "",
        "confirmed_loader": "sub_558C90 reads 256 records of four u16 values into dword_6DA354.",
        "confirmed_consumers": "Text width uses record +0x04 as advance; drawing passes +0x00 to sub_435D10, uses +0x02 as y-center adjustment, +0x04 as width, and +0x06 as height.",
    }

    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    with (out_dir / "glyph_metrics.csv").open("w", newline="", encoding="utf-8") as f:
        fieldnames = [
            "codepoint", "codepoint_hex", "char", "defined",
            "material_index_00", "material_exists", "texture_index", "texture_exists",
            "material_x0", "material_y0", "material_x1", "material_y1", "material_flags_hex",
            "y_center_offset_02", "advance_width_04", "draw_height_06",
        ]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for g in font.glyphs:
            m = mat_by_i.get(g.material_index_00) if g.is_defined else None
            tex_i = m.texture_index if m is not None else ""
            w.writerow({
                "codepoint": g.codepoint,
                "codepoint_hex": f"0x{g.codepoint:02X}",
                "char": g.char_display,
                "defined": g.is_defined,
                "material_index_00": g.material_index_00,
                "material_exists": (m is not None) if (materials and g.is_defined) else "",
                "texture_index": tex_i,
                "texture_exists": (0 <= tex_i < texture_count) if (m is not None and texture_count is not None) else "",
                "material_x0": m.x0 if m is not None else "",
                "material_y0": m.y0 if m is not None else "",
                "material_x1": m.x1 if m is not None else "",
                "material_y1": m.y1 if m is not None else "",
                "material_flags_hex": f"0x{m.flags:04X}" if m is not None else "",
                "y_center_offset_02": g.y_center_offset_02,
                "advance_width_04": g.advance_width_04,
                "draw_height_06": g.draw_height_06,
            })

    samples = ["Village Chapter 1", "PAUSE", "0123456789", "The Emperor's New Groove"]
    with (out_dir / "text_width_samples.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["sample", "width"])
        w.writeheader()
        for sample in samples:
            w.writerow({"sample": sample, "width": font.text_width(sample)})

    return summary
