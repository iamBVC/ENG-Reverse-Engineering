"""
lzss.py — decompressor for the LZSS-style streams used by the game.

Observed in Emperor's New Groove .WAD/.COR data:

    Read control byte b:

      (b & 0x80) == 0
          Literal run.  Copy the next (b & 0x7F) bytes directly to output.

      (b & 0x80) != 0
          Back-reference.  Read one more byte c and form:

              w      = (b << 8) | c
              offset = w & 0x0FFF
              length = ((w >> 12) & 7) + 3

          Then repeat-copy from dst[dp - offset].  The currently confirmed
          extractor behavior uses a fixed source address for every byte of the
          run, not a sliding dst[dp - offset + i] source.
"""

from __future__ import annotations


def decompress_lzss(src: bytes, uncomp_size: int) -> bytes:
    """Decompress src into exactly uncomp_size bytes, padding unfinished output with zeros."""
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
            end = min(sp + count, len(src))
            chunk = src[sp:end]
            dst[dp:dp + len(chunk)] = chunk
            sp += count
            dp += len(chunk)

    return bytes(dst)
