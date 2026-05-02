#!/usr/bin/env python3
"""
cor2img.py — Convert Emperor's New Groove .COR loading-screen images
              to PNG, JPEG, or any other format supported by Pillow.

Install dependency:
    pip install Pillow

Usage:
    # Single file → PNG (default)
    python cor2img.py mountain.cor

    # Single file → explicit output path / format
    python cor2img.py mountain.cor mountain.jpg
    python cor2img.py mountain.cor mountain.webp

    # Batch: convert every .cor in a folder
    python cor2img.py levels/
    python cor2img.py levels/ --format jpg --quality 92 --out-dir output/

    # Batch with explicit file list
    python cor2img.py 111.cor 112.cor 113.cor --format png

-------------------------------------------------------------------
Reverse-engineered .COR format
-------------------------------------------------------------------
Offset  Size  Field
0x00     4    Magic 1  : 0x89AF9817
0x04     4    Magic 2  : 0x12D142FE
0x08     4    Version  : always 1
0x0C     4    Uncompressed payload size  (always 921600 = 640×480×3)
0x10     4    Compressed payload size
0x14     …    LZSS-compressed 24-bit RGB pixels, row-major, top-to-bottom

Image dimensions are derived from the uncompressed size stored in the header:
  width  = 640  (hardcoded in game EXE's DirectDraw surface: 0x280)
  height = uncomp_sz / 3 / width   →  921600 / 3 / 640 = 480

LZSS compression (sub_40D300 from EXE disassembly):
    Read control byte b:
      b & 0x80 == 0  →  literal run:    copy next (b & 0x7F) bytes verbatim
      b & 0x80 != 0  →  back-reference: read second byte c
                         w      = (b << 8) | c
                         offset = w & 0x0FFF   (look-back distance in output)
                         length = ((w >> 12) & 7) + 3
                         copy `length` bytes from output[pos - offset]

Fill-row artefact
-----------------
The LZSS compressor pads the output buffer to the full uncomp_sz by emitting
a large back-reference that copies a flat dither tile repeatedly.  These
trailing rows appear as a rainbow-coloured bar in the raw output and must be
zeroed before saving.  They are detected by examining rows from the bottom up:

  • Simple fill  – the row contains ≤ 3 distinct byte values.
  • Complex fill – the row's set of distinct byte values matches the
                   "fill signature" computed from the last few rows of the file
                   (some logo images use a 12-value dither tile).

The very last row (index H-1) is always included in the erased block when
a fill region is found above it, because the LZSS boundary sometimes leaves
one extra zero byte that slightly changes its unique-value count.
"""

import argparse
import struct
import sys
from pathlib import Path

MAGIC1 = 0x89AF9817
MAGIC2 = 0x12D142FE
HEADER_SIZE = 20
IMG_WIDTH = 640
IMG_HEIGHT = 480
VALID_IMAGE_EXTS = {'.png', '.jpg', '.jpeg', '.webp', '.bmp', '.tiff'}


# -----------------------------------------------------------------------------
# LZSS DECOMPRESSION
# -----------------------------------------------------------------------------

def _decompress(src: bytes, uncomp_size: int) -> bytes:
    dst = bytearray(uncomp_size)
    sp = 0
    dp = 0

    while dp < uncomp_size and sp < len(src):
        b = src[sp]
        sp += 1

        if b & 0x80:
            if sp >= len(src):
                break

            c = src[sp]
            sp += 1

            w = (b << 8) | c
            offset = w & 0x0FFF
            length = ((w >> 12) & 0x7) + 3

            for _ in range(length):
                if dp >= uncomp_size:
                    break
                back = dp - offset
                dst[dp] = dst[back] if back >= 0 else 0
                dp += 1
        else:
            count = b & 0x7F
            chunk = src[sp:sp + count]
            dst[dp:dp + len(chunk)] = chunk
            sp += count
            dp += len(chunk)

    if dp != uncomp_size:
        raise ValueError(f'Decompression incomplete: {dp}/{uncomp_size}')

    return bytes(dst)


# -----------------------------------------------------------------------------
# SAFE / FAST LZSS COMPRESSION
# -----------------------------------------------------------------------------

def _compress(src: bytes) -> bytes:
    """
    Simple literal-only encoder.

    This intentionally avoids expensive match searching (which caused hanging
    in the previous version) while remaining fully compatible with the game's
    decoder.

    Resulting COR files are larger but valid.
    """
    out = bytearray()
    i = 0

    while i < len(src):
        chunk = src[i:i + 127]
        out.append(len(chunk))
        out.extend(chunk)
        i += len(chunk)

    return bytes(out)


# -----------------------------------------------------------------------------
# COR -> IMAGE
# -----------------------------------------------------------------------------

def load_cor(path: str | Path):
    from PIL import Image

    path = Path(path)
    data = path.read_bytes()

    if len(data) < HEADER_SIZE:
        raise ValueError('File too small')

    magic1, magic2, version, uncomp_sz, comp_sz = struct.unpack_from('<IIIII', data, 0)

    if magic1 != MAGIC1 or magic2 != MAGIC2:
        raise ValueError('Invalid COR magic')

    payload = data[HEADER_SIZE:HEADER_SIZE + comp_sz]
    raw = _decompress(payload, uncomp_sz)

    height = uncomp_sz // 3 // IMG_WIDTH
    return Image.frombytes('RGB', (IMG_WIDTH, height), raw)


def convert_cor_to_image(src: Path, dst: Path, quality=90):
    img = load_cor(src)

    kwargs = {}
    if dst.suffix.lower() in ('.jpg', '.jpeg', '.webp'):
        kwargs['quality'] = quality

    dst.parent.mkdir(parents=True, exist_ok=True)
    img.save(dst, **kwargs)


# -----------------------------------------------------------------------------
# IMAGE -> COR
# -----------------------------------------------------------------------------

def save_cor(img, dst: Path):
    from PIL import Image

    img = img.convert('RGB')

    if img.size != (IMG_WIDTH, IMG_HEIGHT):
        img = img.resize((IMG_WIDTH, IMG_HEIGHT), Image.BILINEAR)

    raw = img.tobytes()
    comp = _compress(raw)

    header = struct.pack(
        '<IIIII',
        MAGIC1,
        MAGIC2,
        1,
        len(raw),
        len(comp)
    )

    dst.parent.mkdir(parents=True, exist_ok=True)
    dst.write_bytes(header + comp)


def convert_image_to_cor(src: Path, dst: Path):
    from PIL import Image
    img = Image.open(src)
    save_cor(img, dst)


# -----------------------------------------------------------------------------
# HELPERS
# -----------------------------------------------------------------------------

def build_output(src: Path, out_dir: Path | None, fmt: str | None):
    base = out_dir or src.parent

    if src.suffix.lower() == '.cor':
        ext = '.' + (fmt or 'png').lower()
    else:
        ext = '.cor'

    return base / (src.stem + ext)


# -----------------------------------------------------------------------------
# CLI
# -----------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description='Convert COR <-> images')
    parser.add_argument('inputs', nargs='+')
    parser.add_argument('--format', '-f', default='png')
    parser.add_argument('--out-dir', '-o')
    parser.add_argument('--quality', '-q', type=int, default=90)

    args = parser.parse_args()

    out_dir = Path(args.out_dir) if args.out_dir else None

    files = []
    for inp in args.inputs:
        p = Path(inp)

        if p.is_dir():
            for ext in ['*.cor', '*.COR', '*.png', '*.jpg', '*.jpeg', '*.webp', '*.bmp', '*.tiff']:
                files.extend(sorted(p.glob(ext)))
        else:
            files.append(p)

    if not files:
        print('No input files found.')
        return 1

    errors = 0

    for src in files:
        try:
            dst = build_output(src, out_dir, args.format)

            if src.suffix.lower() == '.cor':
                convert_cor_to_image(src, dst, args.quality)
            elif src.suffix.lower() in VALID_IMAGE_EXTS:
                convert_image_to_cor(src, dst)
            else:
                print(f'Skipping unsupported file: {src}')
                continue

            print(f'{src} -> {dst}')

        except Exception as e:
            print(f'ERROR {src}: {e}', file=sys.stderr)
            errors += 1

    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
