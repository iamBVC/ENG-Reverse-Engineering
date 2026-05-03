"""light_chunk.py — LGHT chunk parser/exporter.

The LGHT layout is now backed by the PC executable loader:

    sub_558880 dispatches chunk tag 0x4C474854 ("LGHT") to sub_42C180.
    sub_42C180 reads the disk records and calls sub_41B8A0.
    sub_41B8A0 allocates the 112-byte runtime light object.

Disk records are packed and type-dependent:

    u32 count

    type 1 directional:
        u8 type, r, g, b
        f32 dir_x, dir_y, dir_z       # runtime negates z and normalizes vector

    type 2 point/ranged:
        u8 type, r, g, b
        f32 x, y, z                   # runtime negates z
        f32 inner_radius, outer_radius
        u8 falloff_or_mode

    type 4 negative/special point:
        same payload as type 2, but the loader converts color to negative values
        and constructs a runtime type-2 light.
"""

from __future__ import annotations

import csv
import math
from pathlib import Path
from typing import Any

from .binary import Reader


def _byte_to_intensity(v: int) -> float:
    """LGHT color byte -> runtime float intensity, matching sub_42C180."""
    return (2.0 * float(v)) / 255.0


def _normalize_vec3(x: float, y: float, z: float) -> tuple[float, float, float]:
    mag = math.sqrt(x * x + y * y + z * z)
    if mag == 0.0:
        return 0.0, 0.0, 0.0
    return x / mag, y / mag, z / mag


def _common(idx: int, offset: int, ltype: int, rb: int, gb: int, bb: int) -> dict[str, Any]:
    return {
        "idx": idx,
        "file_offset": offset,
        "disk_type": ltype,
        "r_byte": rb,
        "g_byte": gb,
        "b_byte": bb,
        "r_intensity": _byte_to_intensity(rb),
        "g_intensity": _byte_to_intensity(gb),
        "b_intensity": _byte_to_intensity(bb),
    }


def parse_lght_chunk(data: bytes) -> list[dict[str, Any]]:
    """Parse an LGHT chunk into typed records.

    Returned dictionaries include both disk values and executable-derived runtime
    values.  Unknown/unsupported record types are preserved as much as possible
    instead of silently guessing a fixed size.
    """
    r = Reader(data)
    if len(data) < 4:
        return []
    count = r.u32()
    lights: list[dict[str, Any]] = []

    for idx in range(count):
        if not r.can_read(4):
            lights.append({
                "idx": idx,
                "file_offset": r.tell(),
                "disk_type": "truncated",
                "kind": "truncated",
                "error": "not enough bytes for LGHT record header",
            })
            break

        off = r.tell()
        ltype = r.u8()
        rb = r.u8()
        gb = r.u8()
        bb = r.u8()
        rec = _common(idx, off, ltype, rb, gb, bb)

        if ltype == 1:
            if not r.can_read(12):
                rec.update(kind="truncated_directional", error="not enough bytes for type-1 payload")
                lights.append(rec)
                break
            dir_x = r.f32()
            dir_y = r.f32()
            dir_z_disk = r.f32()
            dir_z_runtime = -dir_z_disk
            ndx, ndy, ndz = _normalize_vec3(dir_x, dir_y, dir_z_runtime)
            rec.update({
                "kind": "directional",
                "runtime_type": 1,
                "disk_size": 16,
                "f0": dir_x,
                "f1": dir_y,
                "f2": dir_z_disk,
                "f3": None,
                "f4": None,
                "extra_u8": None,
                "dir_x": dir_x,
                "dir_y": dir_y,
                "dir_z_disk": dir_z_disk,
                "dir_z_runtime": dir_z_runtime,
                "dir_x_normalized": ndx,
                "dir_y_normalized": ndy,
                "dir_z_normalized": ndz,
                "x": None,
                "y": None,
                "z_disk": None,
                "z_runtime": None,
                "inner_radius": None,
                "outer_radius": None,
                "inner_radius_sq": None,
                "outer_radius_sq": None,
                "inv_radius_range": None,
                "runtime_r": rec["r_intensity"],
                "runtime_g": rec["g_intensity"],
                "runtime_b": rec["b_intensity"],
            })
        elif ltype in (2, 4):
            if not r.can_read(21):
                rec.update(kind="truncated_point", error="not enough bytes for type-2/type-4 payload")
                lights.append(rec)
                break
            x = r.f32()
            y = r.f32()
            z_disk = r.f32()
            inner = r.f32()
            outer = r.f32()
            extra = r.u8()
            z_runtime = -z_disk
            if ltype == 4:
                rr = -((rec["r_intensity"] + 1.0) * 0.5)
                rg = -((rec["g_intensity"] + 1.0) * 0.5)
                rb_runtime = -((rec["b_intensity"] + 1.0) * 0.5)
                kind = "negative_point"
            else:
                rr = rec["r_intensity"]
                rg = rec["g_intensity"]
                rb_runtime = rec["b_intensity"]
                kind = "point"
            rec.update({
                "kind": kind,
                "runtime_type": 2,
                "disk_size": 25,
                "f0": x,
                "f1": y,
                "f2": z_disk,
                "f3": inner,
                "f4": outer,
                "extra_u8": extra,
                "x": x,
                "y": y,
                "z_disk": z_disk,
                "z_runtime": z_runtime,
                "inner_radius": inner,
                "outer_radius": outer,
                "inner_radius_sq": inner * inner,
                "outer_radius_sq": outer * outer,
                "inv_radius_range": (1.0 / (outer - inner)) if outer != inner else None,
                "falloff_or_mode": extra,
                "runtime_r": rr,
                "runtime_g": rg,
                "runtime_b": rb_runtime,
                "dir_x": None,
                "dir_y": None,
                "dir_z_disk": None,
                "dir_z_runtime": None,
                "dir_x_normalized": None,
                "dir_y_normalized": None,
                "dir_z_normalized": None,
            })
        else:
            # Unknown type. Older tooling assumed a 24-byte fixed record; keep a
            # conservative 20-byte float payload if present, but mark it unknown.
            payload = r.read(min(20, r.remaining())) if r.remaining() else b""
            rec.update({
                "kind": "unknown",
                "runtime_type": None,
                "disk_size": 4 + len(payload),
                "unknown_payload_hex": payload.hex(" ").upper(),
                "note": "Unknown LGHT type; parser did not guess a type-specific payload.",
            })
        lights.append(rec)

    return lights


def export_lights(lights: list[dict[str, Any]], out_dir: Path) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)

    fields = [
        "idx", "file_offset", "disk_type", "kind", "runtime_type", "disk_size",
        "r_byte", "g_byte", "b_byte",
        "r_intensity", "g_intensity", "b_intensity",
        "runtime_r", "runtime_g", "runtime_b",
        "f0", "f1", "f2", "f3", "f4", "extra_u8",
        "dir_x", "dir_y", "dir_z_disk", "dir_z_runtime",
        "dir_x_normalized", "dir_y_normalized", "dir_z_normalized",
        "x", "y", "z_disk", "z_runtime",
        "inner_radius", "outer_radius", "inner_radius_sq", "outer_radius_sq",
        "inv_radius_range", "falloff_or_mode", "unknown_payload_hex", "error", "note",
    ]
    with (out_dir / "lights.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields, extrasaction="ignore")
        w.writeheader()
        for lt in lights:
            w.writerow(lt)

    counts: dict[str, int] = {}
    for lt in lights:
        counts[str(lt.get("kind", "unknown"))] = counts.get(str(lt.get("kind", "unknown")), 0) + 1

    with (out_dir / "summary.txt").open("w", encoding="utf-8") as f:
        f.write("LGHT chunk summary\n")
        f.write("==================\n\n")
        f.write(f"light_count: {len(lights)}\n")
        for kind, n in sorted(counts.items()):
            f.write(f"{kind}: {n}\n")
        f.write("\nExecutable-backed interpretation:\n")
        f.write("- type 1: directional light; f0/f1/f2 are direction x/y/z, z is negated at runtime, then normalized.\n")
        f.write("- type 2: point/ranged light; f0/f1/f2 are position x/y/z, z is negated at runtime.\n")
        f.write("- type 4: special/negative point light; payload matches type 2, but runtime color is negative.\n")
        f.write("- RGB bytes are converted to 0.0..2.0 intensity with (2 * byte) / 255.\n")
        f.write("- type 2/4 f3/f4 are inner/outer radius candidates; runtime stores radius, radius squared, and 1/(outer-inner).\n")
        f.write("- type 2/4 final byte is still named falloff_or_mode until the lighting evaluator is reversed.\n")

    print(f"  → lights/lights.csv ({len(lights)} light sources)")
    print("  → lights/summary.txt")
