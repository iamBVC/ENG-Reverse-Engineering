"""Decode the diagnostic DirectDraw surface without depending on desktop capture."""
from collections import Counter
from pathlib import Path
import struct
import sys

source = Path(sys.argv[1])
output = source.with_suffix('.bmp')
data = source.read_bytes()
width, height, pitch, bits, red, green, blue, alpha = struct.unpack_from('<8I', data)
assert bits in (16, 24, 32), bits
assert width * (bits // 8) <= pitch and len(data) == 32 + pitch * height
row_size = (width * 3 + 3) & ~3
image = bytearray(row_size * height)
counts = Counter()

def channel(pixel, mask):
    if not mask:
        return 0
    shift = (mask & -mask).bit_length() - 1
    return ((pixel & mask) >> shift) * 255 // (mask >> shift)

for y in range(height):
    for x in range(width):
        offset = 32 + y * pitch + x * (bits // 8)
        pixel = int.from_bytes(data[offset:offset + bits // 8], 'little')
        rgb = (channel(pixel, red), channel(pixel, green), channel(pixel, blue))
        counts[rgb] += 1
        offset = y * row_size + x * 3
        image[offset:offset + 3] = bytes(reversed(rgb))

header = struct.pack('<2sIHHI', b'BM', 54 + len(image), 0, 0, 54)
header += struct.pack('<IiiHHIIiiII', 40, width, -height, 1, 24, 0, len(image), 0, 0, 0, 0)
output.write_bytes(header + image)
print(f'{width}x{height}, {bits} bits, masks={red:08x}/{green:08x}/{blue:08x}, unique colors={len(counts)}')
print('Most frequent colors:', counts.most_common(5))
print(output.resolve())
