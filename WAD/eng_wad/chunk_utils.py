"""chunk_utils.py - small reusable WAD chunk helpers."""

from __future__ import annotations

import struct


def quick_element_count(tag: str, data: bytes) -> str:
    """Return a compact best-effort count label for overview tables."""
    try:
        n = struct.unpack_from("<I", data, 0)[0] if len(data) >= 4 else None
        labels = {
            "MAP ": "tiles",
            "TRAK": "records",
            "STPC": "defs",
            "SMPC": "sounds",
            "AMPC": "ambients",
            "LGHT": "lights",
            "TEXT": "textures",
            "LGPC": "lines",
        }
        if n is not None and tag in labels:
            return f"{n} {labels[tag]}"
    except Exception:
        pass
    return "-"
