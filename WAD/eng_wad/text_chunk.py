"""
text_chunk.py — TEXT chunk parser and texture/palette exporters.

Despite the name, the TEXT chunk is not text strings.  In observed level WADs it
contains texture records compressed as RGB555 word run-length streams.  Earlier
versions of this tool treated the texture payloads as LZSS-compressed 8-bit
palette indices; that was wrong for the main WAD TEXT/TXET texture images.

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
        +0x10  bytes compressed texture data

Texture payload format:
    The compressed stream is a sequence of little-endian 16-bit packets.

    packet < 0x8000:
        packet is a literal count, followed by that many RGB555 words.

    packet & 0x8000:
        packet is a repeat count encoded as 0x10000 - packet, followed by one
        RGB555 word repeated that many times.

    RGB555 words are xRRRRRGGGGGBBBBB.  Values are expanded to 8-bit channels by
    left-shifting each 5-bit channel by 3.  The exporter can write them as RGB
    or BGR; BGR is the current default diagnostic output because visual testing
    showed the previous RGB export had too much blue where red was expected.

After all texture records there may still be a palette/metadata table.  The
palette is preserved because it may be used by materials or other texture modes,
but it is no longer used to decode the main exported PNG textures.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from .binary import Reader


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



def rgb555_to_rgb(word: int) -> tuple[int, int, int]:
    """Convert a little-endian RGB555 word to 8-bit RGB.

    This intentionally matches the community Java extractor: channels are
    expanded with a simple left shift instead of bit replication.
    """
    word &= 0xFFFF
    r = ((word & 0x7C00) >> 10) << 3
    g = ((word & 0x03E0) >> 5) << 3
    b = (word & 0x001F) << 3
    return r, g, b


def _order_rgb_channels(r: int, g: int, b: int, channel_order: str) -> tuple[int, int, int]:
    """Return channels in the requested export order.

    The source word is decoded as RGB555, but some game/runtime paths appear to
    treat the 16-bit word as BGR555.  Keeping this as an exporter option lets us
    compare both interpretations without touching the proven RLE decoder.
    """
    if channel_order.lower() == "bgr":
        return b, g, r
    return r, g, b


def decompress_rgb555_rle(src: bytes, pixel_count: int, *, channel_order: str = "bgr") -> tuple[bytes, dict[str, int]]:
    """Decode the TEXT/TXET RGB555 RLE stream to packed RGB bytes.

    Returns (rgb_bytes, stats).  The output is padded/truncated to exactly
    pixel_count pixels so partially decoded experimental files still export.
    """
    out = bytearray(pixel_count * 3)
    sp = 0
    op = 0
    literal_packets = 0
    repeat_packets = 0
    literal_pixels = 0
    repeat_pixels = 0

    while sp + 2 <= len(src) and op < pixel_count:
        packet = int.from_bytes(src[sp:sp + 2], "little")
        sp += 2

        if packet & 0x8000:
            if sp + 2 > len(src):
                break
            word = int.from_bytes(src[sp:sp + 2], "little")
            sp += 2
            count = 0x10000 - packet
            r, g, b = _order_rgb_channels(*rgb555_to_rgb(word), channel_order)
            repeat_packets += 1
            repeat_pixels += count
            for _ in range(count):
                if op >= pixel_count:
                    break
                p = op * 3
                out[p:p + 3] = bytes((r, g, b))
                op += 1
        else:
            count = packet
            literal_packets += 1
            literal_pixels += count
            for _ in range(count):
                if sp + 2 > len(src) or op >= pixel_count:
                    break
                word = int.from_bytes(src[sp:sp + 2], "little")
                sp += 2
                r, g, b = _order_rgb_channels(*rgb555_to_rgb(word), channel_order)
                p = op * 3
                out[p:p + 3] = bytes((r, g, b))
                op += 1

    stats = {
        "pixels_decoded": op,
        "bytes_consumed": sp,
        "bytes_total": len(src),
        "literal_packets": literal_packets,
        "repeat_packets": repeat_packets,
        "literal_pixels_declared": literal_pixels,
        "repeat_pixels_declared": repeat_pixels,
        "channel_order": channel_order,
    }
    return bytes(out), stats

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


def export_textures(
    text: TextChunk,
    out_dir: Path,
    *,
    verbose: bool = True,
    export_fields: bool = True,
    texture_channel_order: str = "bgr",
) -> None:
    """Export TEXT textures, material-table bytes, and optional diagnostics.

    ``texture_channel_order`` may be ``"bgr"`` or ``"rgb"``.  BGR is the
    current default because visual feedback showed the older RGB export was
    blue/red swapped for terrain textures.
    """
    Image = _require_pillow()

    textures_dir = out_dir / "textures"
    palette_dir = out_dir / "palette"
    fields_dir = out_dir / "texture_fields"
    textures_dir.mkdir(parents=True, exist_ok=True)
    palette_dir.mkdir(parents=True, exist_ok=True)

    palette_struct = text.palette_struct

    decode_rows: list[list[int | str]] = []

    for tex in text.textures:
        target = tex.width * tex.height
        rgb, stats = decompress_rgb555_rle(tex.comp_data, target, channel_order=texture_channel_order)

        Image.frombytes("RGB", (tex.width, tex.height), rgb).save(
            textures_dir / f"texture_{tex.index:02d}.png"
        )

        decode_rows.append([
            tex.index,
            f"0x{tex.flags:04X}",
            tex.width,
            tex.height,
            tex.comp_size,
            stats["pixels_decoded"],
            target,
            stats["bytes_consumed"],
            stats["bytes_total"],
            stats["literal_packets"],
            stats["repeat_packets"],
            stats["channel_order"],
        ])

        # Keep optional legacy diagnostics, but do not confuse them with the real
        # texture decode.  These visualize the low byte of each RGB555 word as if
        # it were a palette index, which is only useful when investigating older
        # assumptions.
        if export_fields:
            legacy_index = bytes(rgb[i] for i in range(0, len(rgb), 3))[:target]
            for field_index, field_name in [
                (0, "meta0"), (1, "meta1"), (2, "meta2"), (3, "marker"),
                (4, "rgb_r"), (5, "rgb_g"), (6, "rgb_b"), (7, "extra"),
            ]:
                save_field_image(
                    fields_dir / f"texture_{tex.index:02d}_legacy_field{field_index}_{field_name}.png",
                    legacy_index,
                    palette_struct,
                    field_index,
                    tex.width,
                    tex.height,
                )

        if verbose:
            print(
                f"  texture_{tex.index:02d}: {tex.width}×{tex.height} "
                f"flags=0x{tex.flags:04X} comp={tex.comp_size:,}B "
                f"decoded={stats['pixels_decoded']:,}/{target:,} pixels "
                f"channels={stats['channel_order']}"
            )

    with (textures_dir / "texture_decode_stats.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "texture_index", "flags", "width", "height", "compressed_size",
            "pixels_decoded", "pixels_expected", "bytes_consumed", "bytes_total",
            "literal_packets", "repeat_packets", "channel_order",
        ])
        w.writerows(decode_rows)

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

    print(f"  → textures/ ({len(text.textures)} RGB555 RLE texture records, channel_order={texture_channel_order})")
    print(f"  → palette/palette.png, palette.bin, palette_debug.csv")
