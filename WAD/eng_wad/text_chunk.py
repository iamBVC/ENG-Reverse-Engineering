"""
text_chunk.py — TEXT chunk parser and texture/palette exporters.

Despite the name, the TEXT chunk is not text strings.  In observed level WADs it
contains texture-like 256x256 compressed byte planes plus a palette/metadata table.

Confirmed structure from tested files:

    +0x00  u32  count1, usually 0
    +0x04  u32  texture_count, 18 in t1l1m001

    repeated texture_count times:
        +0x00  u32  flags
                      bit 0x80 appears to mean compressed
                      low bits 0x01..0x07 likely describe format/type
        +0x04  u32  width
        +0x08  u32  height
        +0x0C  u32  compressed_size
        +0x10  bytes compressed texture/control-map data

    after all textures:
        u32 palette_entry_count
        repeated palette_entry_count times, 8 bytes each:
            byte 0  metadata field A
            byte 1  metadata field B
            byte 2  metadata field C
            byte 3  marker, usually 0xFF
            byte 4  RGB red
            byte 5  RGB green
            byte 6  RGB blue
            byte 7  extra/flags metadata

Important warning:
    The palette table can contain more than 256 entries, but each decompressed
    texture byte is only 0..255.  Therefore a direct pixel->palette lookup is a
    useful diagnostic, but the full material/texture mapping is not fully decoded.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from .binary import Reader
from .lzss import decompress_lzss


@dataclass
class TextureRecord:
    index: int
    flags: int
    width: int
    height: int
    comp_size: int
    comp_data: bytes


@dataclass
class TextChunk:
    count1: int
    textures: list[TextureRecord]
    pal_count: int
    pal_raw: bytes
    palettes: list[tuple[int, int, int]]

    @property
    def palette_struct(self) -> list[tuple[int, int, int, int, int, int, int, int]]:
        return [tuple(self.pal_raw[i * 8:(i + 1) * 8]) for i in range(self.pal_count)]  # type: ignore[list-item]


def parse_text_chunk(data: bytes) -> TextChunk:
    r = Reader(data)
    count1 = r.u32()
    texture_count = r.u32()

    textures: list[TextureRecord] = []
    for i in range(texture_count):
        flags = r.u32()
        width = r.u32()
        height = r.u32()
        comp_size = r.u32()
        comp_data = r.read(comp_size)
        textures.append(TextureRecord(i, flags, width, height, comp_size, comp_data))

    pal_count = r.u32()
    pal_raw = r.read(pal_count * 8)
    palettes: list[tuple[int, int, int]] = []
    for i in range(pal_count):
        e = pal_raw[i * 8:(i + 1) * 8]
        palettes.append((e[4], e[5], e[6]))

    return TextChunk(count1=count1, textures=textures, pal_count=pal_count, pal_raw=pal_raw, palettes=palettes)


def _require_pillow():
    try:
        from PIL import Image
        return Image
    except ImportError as exc:  # pragma: no cover
        raise RuntimeError("Pillow is required for texture export. Install with: pip install Pillow") from exc


def save_field_image(
    out_path: Path,
    pixels: bytes | bytearray,
    palette_struct: list[tuple[int, ...]],
    field_index: int,
    width: int,
    height: int,
    *,
    missing_value: int = 0,
) -> None:
    """
    Diagnostic view: treat each decompressed texture byte as an index into the
    first 256 palette entries and save one selected palette byte as grayscale.

    This does NOT prove the final material mapping.  It is a visualization aid.
    """
    Image = _require_pillow()

    if not 0 <= field_index <= 7:
        raise ValueError(f"field_index must be 0..7, got {field_index}")

    expected = width * height
    if len(pixels) < expected:
        pixels = bytes(pixels) + bytes(expected - len(pixels))
    elif len(pixels) > expected:
        pixels = pixels[:expected]

    raw = bytearray(expected)
    for n, p in enumerate(pixels):
        raw[n] = palette_struct[p][field_index] if p < len(palette_struct) else missing_value

    out_path.parent.mkdir(parents=True, exist_ok=True)
    Image.frombytes("L", (width, height), bytes(raw)).save(out_path)


def export_textures(text: TextChunk, out_dir: Path, *, verbose: bool = True, export_fields: bool = True) -> None:
    """Export TEXT textures, palette files, and optional palette-field diagnostics."""
    Image = _require_pillow()

    textures_dir = out_dir / "textures"
    palette_dir = out_dir / "palette"
    fields_dir = out_dir / "texture_fields"
    textures_dir.mkdir(parents=True, exist_ok=True)
    palette_dir.mkdir(parents=True, exist_ok=True)

    pal_rgb_flat: list[int] = []
    for r, g, b in text.palettes[:256]:
        pal_rgb_flat.extend([r, g, b])
    while len(pal_rgb_flat) < 256 * 3:
        pal_rgb_flat.extend([0, 0, 0])

    palette_struct = text.palette_struct

    for tex in text.textures:
        target = tex.width * tex.height
        pixels = decompress_lzss(tex.comp_data, target)
        if len(pixels) < target:
            pixels += bytes(target - len(pixels))

        img_l = Image.frombytes("L", (tex.width, tex.height), pixels)
        img_l.save(textures_dir / f"texture_{tex.index:02d}_grey.png")

        img_p = Image.frombytes("P", (tex.width, tex.height), pixels)
        img_p.putpalette(pal_rgb_flat)
        img_p.convert("RGB").save(textures_dir / f"texture_{tex.index:02d}_pal.png")

        if export_fields:
            for field_index, field_name in [
                (0, "meta0"), (1, "meta1"), (2, "meta2"), (3, "marker"),
                (4, "rgb_r"), (5, "rgb_g"), (6, "rgb_b"), (7, "extra"),
            ]:
                save_field_image(
                    fields_dir / f"texture_{tex.index:02d}_field{field_index}_{field_name}.png",
                    pixels,
                    palette_struct,
                    field_index,
                    tex.width,
                    tex.height,
                )

        if verbose:
            print(f"  texture_{tex.index:02d}: {tex.width}×{tex.height} flags=0x{tex.flags:04X} comp={tex.comp_size:,}B")

    # Palette swatch image.
    n = len(text.palettes)
    sw_w = min(n, 64) if n else 1
    sw_h = (n + sw_w - 1) // sw_w if n else 1
    swatch = Image.new("RGB", (sw_w, sw_h))
    px = swatch.load()
    for idx, color in enumerate(text.palettes):
        row, col = divmod(idx, sw_w)
        px[col, row] = color
    swatch.save(palette_dir / "palette.png")

    (palette_dir / "palette.bin").write_bytes(text.pal_raw)

    with (palette_dir / "palette_debug.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["idx", "a", "b", "c", "marker", "R", "G", "B", "extra"])
        for i in range(text.pal_count):
            w.writerow([i, *text.pal_raw[i * 8:(i + 1) * 8]])

    print(f"  → textures/ ({len(text.textures)} texture records)")
    print(f"  → palette/palette.png, palette.bin, palette_debug.csv")
