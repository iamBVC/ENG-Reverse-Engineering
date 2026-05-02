"""light_chunk.py — LGHT chunk parser/exporter."""

from __future__ import annotations

import csv
from pathlib import Path

from .binary import Reader


def parse_lght_chunk(data: bytes) -> list[dict]:
    """
    Parse the LGHT chunk.

    Observed structure:
        u32 count
        repeated entries, usually at least 24 bytes:
            u8 type
            u8 red
            u8 green
            u8 blue
            f32 f0
            f32 f1
            f32 f2
            f32 f3
            f32 f4

    The meaning of f0..f4 depends on light type and is not fully decoded yet.
    """
    r = Reader(data)
    count = r.u32()
    entry_bytes = (len(data) - 4) // count if count else 0
    lights: list[dict] = []

    for _ in range(count):
        ltype = r.u8()
        lr = r.u8()
        lg = r.u8()
        lb = r.u8()
        f0 = r.f32(); f1 = r.f32(); f2 = r.f32(); f3 = r.f32(); f4 = r.f32()
        lights.append(dict(type=ltype, r=lr, g=lg, b=lb, f0=f0, f1=f1, f2=f2, f3=f3, f4=f4))
        leftover = entry_bytes - 24
        if leftover > 0:
            r.skip(leftover)

    return lights


def export_lights(lights: list[dict], out_dir: Path) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)
    with (out_dir / "lights.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["idx", "type", "r", "g", "b", "f0", "f1", "f2", "f3", "f4"])
        for i, lt in enumerate(lights):
            w.writerow([i, lt["type"], lt["r"], lt["g"], lt["b"], lt["f0"], lt["f1"], lt["f2"], lt["f3"], lt["f4"]])
    print(f"  → lights/lights.csv ({len(lights)} light sources)")
