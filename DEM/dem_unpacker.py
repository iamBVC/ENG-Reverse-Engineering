#!/usr/bin/env python3
"""
dem_unpacker.py — experimental .DEM demo-input unpacker for Disney's The Emperor's New Groove.

The .DEM files seen next to some .WAD levels appear to be standalone demo/playback
recordings, not WAD chunks.  They are likely used by the game for attract-mode or
scripted input playback.

Observed structure from T1L1M001.DEM and T1L2M001.DEM:

    +0x00  u32 frame_count
    +0x04  frame_count x DemoFrame8

DemoFrame8 is exactly 8 bytes:

    +0x00  u16 buttons_or_flags
           This behaves like a bit field.  The bit positions line up well with
           the common PlayStation controller button mask, but this mapping should
           still be treated as tentative until confirmed in-game.

           Tentative mapping:
               0x0001 SELECT
               0x0002 L3
               0x0004 R3
               0x0008 START
               0x0010 UP
               0x0020 RIGHT
               0x0040 DOWN
               0x0080 LEFT
               0x0100 L2
               0x0200 R2
               0x0400 L1
               0x0800 R1
               0x1000 TRIANGLE
               0x2000 CIRCLE
               0x4000 CROSS
               0x8000 SQUARE

    +0x02  u16 angle_or_heading
           Values are usually 0..4095, so this looks like a 12-bit angle.
           angle_degrees = value * 360 / 4096 is exported as a convenience.

    +0x04  u8  field4
           Usually 0x00 or 0x80.  Unknown.  It may be an analog/control flag.

    +0x05  u8  field5
           Usually 0x01.  Rare values such as 0x02, 0x04, 0x05 appear near the
           beginning of recordings.  Unknown.  It may be a mode/state byte.

    +0x06  u8  field6
    +0x07  u8  field7
           These often take values 0x00, 0x7F, or 0x80.  They look analog-like,
           but the exact meaning is not confirmed.  They are exported both raw
           and as signed values around an assumed center of 0x80.

This script intentionally preserves all raw fields.  The named button/angle output
is a helper for investigation, not a claim that the format is fully decoded.

Usage:
    python dem_unpacker.py T1L1M001.DEM -o dem_out/T1L1M001
    python dem_unpacker.py T1L1M001.DEM T1L2M001.DEM -o dem_out
"""

from __future__ import annotations

import argparse
import csv
import json
import math
import struct
from collections import Counter
from dataclasses import asdict, dataclass
from pathlib import Path

BUTTON_BITS: list[tuple[str, int]] = [
    ("SELECT",   0x0001),
    ("L3",       0x0002),
    ("R3",       0x0004),
    ("START",    0x0008),
    ("UP",       0x0010),
    ("RIGHT",    0x0020),
    ("DOWN",     0x0040),
    ("LEFT",     0x0080),
    ("L2",       0x0100),
    ("R2",       0x0200),
    ("L1",       0x0400),
    ("R1",       0x0800),
    ("TRIANGLE", 0x1000),
    ("CIRCLE",   0x2000),
    ("CROSS",    0x4000),
    ("SQUARE",   0x8000),
]


@dataclass
class DemFrame:
    frame: int
    buttons: int
    angle_raw: int
    field4: int
    field5: int
    field6: int
    field7: int

    @property
    def angle_degrees(self) -> float:
        """Interpret angle_raw as a 12-bit turn value.  Diagnostic only."""
        return (self.angle_raw & 0x0FFF) * 360.0 / 4096.0

    @property
    def pressed_names(self) -> list[str]:
        return [name for name, bit in BUTTON_BITS if self.buttons & bit]

    @property
    def field6_signed_80(self) -> int:
        """field6 as a tentative analog byte centered on 0x80."""
        return self.field6 - 0x80

    @property
    def field7_signed_80(self) -> int:
        """field7 as a tentative analog byte centered on 0x80."""
        return self.field7 - 0x80

    def raw_hex(self) -> str:
        return struct.pack("<HHBBBB", self.buttons, self.angle_raw, self.field4, self.field5, self.field6, self.field7).hex(" ")


def parse_dem(data: bytes) -> list[DemFrame]:
    """Parse a DEM file from bytes and return one DemFrame per recorded frame."""
    if len(data) < 4:
        raise ValueError("DEM file is too small to contain a frame count")

    frame_count = struct.unpack_from("<I", data, 0)[0]
    expected_size = 4 + frame_count * 8
    if len(data) != expected_size:
        raise ValueError(
            f"Unexpected DEM size: header says {frame_count} frames, "
            f"expected {expected_size} bytes, got {len(data)} bytes"
        )

    frames: list[DemFrame] = []
    off = 4
    for i in range(frame_count):
        buttons, angle_raw, field4, field5, field6, field7 = struct.unpack_from("<HHBBBB", data, off)
        frames.append(DemFrame(i, buttons, angle_raw, field4, field5, field6, field7))
        off += 8
    return frames


def load_dem(path: Path) -> list[DemFrame]:
    return parse_dem(path.read_bytes())


def summarize(frames: list[DemFrame]) -> dict:
    """Return a JSON-serializable summary useful for reverse engineering."""
    button_counts = {}
    for name, bit in BUTTON_BITS:
        count = sum(1 for fr in frames if fr.buttons & bit)
        if count:
            button_counts[name] = count

    def counter_dict(values):
        return {str(k): v for k, v in Counter(values).most_common()}

    angle_values = [fr.angle_raw for fr in frames]
    return {
        "frame_count": len(frames),
        "duration_if_30fps_seconds": len(frames) / 30.0,
        "duration_if_60fps_seconds": len(frames) / 60.0,
        "unique_exact_frames": len({fr.raw_hex() for fr in frames}),
        "buttons_pressed_frame_counts_tentative": button_counts,
        "buttons_raw_common": counter_dict(fr.buttons for fr in frames),
        "angle_raw_min": min(angle_values) if angle_values else None,
        "angle_raw_max": max(angle_values) if angle_values else None,
        "angle_raw_unique_count": len(set(angle_values)),
        "field4_common": counter_dict(fr.field4 for fr in frames),
        "field5_common": counter_dict(fr.field5 for fr in frames),
        "field6_common": counter_dict(fr.field6 for fr in frames),
        "field7_common": counter_dict(fr.field7 for fr in frames),
    }


def write_frames_csv(frames: list[DemFrame], path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        header = [
            "frame", "buttons_hex", "buttons_dec", "pressed_tentative",
            "angle_raw", "angle_degrees_12bit",
            "field4_hex", "field4_dec", "field5_hex", "field5_dec",
            "field6_hex", "field6_dec", "field6_signed_center_80",
            "field7_hex", "field7_dec", "field7_signed_center_80",
            "raw_8_bytes_hex",
        ]
        header.extend(f"btn_{name}" for name, _ in BUTTON_BITS)
        w.writerow(header)

        for fr in frames:
            row = [
                fr.frame,
                f"0x{fr.buttons:04X}", fr.buttons,
                "+".join(fr.pressed_names),
                fr.angle_raw, f"{fr.angle_degrees:.6f}",
                f"0x{fr.field4:02X}", fr.field4,
                f"0x{fr.field5:02X}", fr.field5,
                f"0x{fr.field6:02X}", fr.field6, fr.field6_signed_80,
                f"0x{fr.field7:02X}", fr.field7, fr.field7_signed_80,
                fr.raw_hex(),
            ]
            row.extend(1 if fr.buttons & bit else 0 for _, bit in BUTTON_BITS)
            w.writerow(row)


def write_runs_csv(frames: list[DemFrame], path: Path) -> None:
    """Run-length encode exact identical 8-byte records."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "run", "start_frame", "frame_count", "end_frame_inclusive",
            "buttons_hex", "pressed_tentative", "angle_raw", "angle_degrees_12bit",
            "field4", "field5", "field6", "field7", "raw_8_bytes_hex",
        ])
        if not frames:
            return

        run_index = 0
        start = 0
        last = frames[0].raw_hex()
        for i in range(1, len(frames) + 1):
            key = frames[i].raw_hex() if i < len(frames) else None
            if key == last:
                continue
            fr = frames[start]
            count = i - start
            w.writerow([
                run_index, start, count, i - 1,
                f"0x{fr.buttons:04X}", "+".join(fr.pressed_names),
                fr.angle_raw, f"{fr.angle_degrees:.6f}",
                fr.field4, fr.field5, fr.field6, fr.field7, fr.raw_hex(),
            ])
            run_index += 1
            start = i
            last = key


def write_viewer_html(frames: list[DemFrame], path: Path, title: str) -> None:
    """Write a dependency-free HTML timeline viewer for quick visual inspection."""
    data = []
    for fr in frames:
        data.append({
            "frame": fr.frame,
            "buttons": fr.buttons,
            "pressed": fr.pressed_names,
            "angle": fr.angle_raw,
            "deg": round(fr.angle_degrees, 4),
            "f4": fr.field4,
            "f5": fr.field5,
            "f6": fr.field6,
            "f7": fr.field7,
            "raw": fr.raw_hex(),
        })

    payload = json.dumps(data)
    button_payload = json.dumps([name for name, _ in BUTTON_BITS])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>{title} DEM viewer</title>
<style>
body {{ margin: 0; font-family: system-ui, sans-serif; background: #111; color: #eee; }}
header {{ padding: 12px 16px; background: #1c1c1c; border-bottom: 1px solid #333; }}
main {{ padding: 16px; }}
canvas {{ background: #181818; border: 1px solid #333; display: block; max-width: 100%; }}
.controls {{ display: flex; gap: 16px; align-items: center; margin-bottom: 10px; flex-wrap: wrap; }}
.box {{ background:#1d1d1d; border:1px solid #333; padding:10px; margin-top:10px; white-space: pre-wrap; font-family: ui-monospace, SFMono-Regular, Menlo, Consolas, monospace; }}
small {{ color:#aaa; }}
</style>
</head>
<body>
<header>
  <strong>{title}</strong> — DEM input timeline<br>
  <small>Top graph: 12-bit angle. Rows: tentative button bits. Bottom: unknown bytes field4..field7.</small>
</header>
<main>
  <div class="controls">
    <label>Frame <input id="frame" type="range" min="0" max="{max(len(frames)-1,0)}" value="0" style="width:420px"></label>
    <button id="prev">◀</button><button id="next">▶</button>
    <span id="frameLabel"></span>
  </div>
  <canvas id="cv" width="1200" height="720"></canvas>
  <div id="details" class="box"></div>
</main>
<script>
const frames = {payload};
const buttonNames = {button_payload};
const cv = document.getElementById('cv');
const ctx = cv.getContext('2d');
const slider = document.getElementById('frame');
const label = document.getElementById('frameLabel');
const details = document.getElementById('details');
const leftPad = 90, topPad = 30, angleH = 170, rowH = 20, gap = 16;
const buttonTop = topPad + angleH + gap;
const fieldsTop = buttonTop + buttonNames.length * rowH + gap;

function xForFrame(i) {{ return leftPad + i * (cv.width - leftPad - 20) / Math.max(frames.length - 1, 1); }}
function yForAngle(a) {{ return topPad + angleH - (a & 4095) * angleH / 4095; }}

function draw(selected) {{
  ctx.clearRect(0,0,cv.width,cv.height);
  ctx.fillStyle = '#181818'; ctx.fillRect(0,0,cv.width,cv.height);
  ctx.strokeStyle = '#333'; ctx.lineWidth = 1;
  for (let i=0;i<=4;i++) {{
    const y = topPad + i*angleH/4;
    ctx.beginPath(); ctx.moveTo(leftPad,y); ctx.lineTo(cv.width-20,y); ctx.stroke();
    ctx.fillStyle = '#aaa'; ctx.fillText(String(Math.round((4-i)*4095/4)), 10, y+4);
  }}
  ctx.fillStyle = '#ddd'; ctx.fillText('angle_raw', 10, topPad - 8);
  ctx.strokeStyle = '#66ccff'; ctx.lineWidth = 2; ctx.beginPath();
  frames.forEach((fr,i)=>{{ const x=xForFrame(i), y=yForAngle(fr.angle); if(i===0)ctx.moveTo(x,y); else ctx.lineTo(x,y); }});
  ctx.stroke();

  buttonNames.forEach((name, bi)=>{{
    const y = buttonTop + bi*rowH;
    ctx.fillStyle = '#aaa'; ctx.fillText(name, 10, y+14);
    ctx.strokeStyle = '#252525'; ctx.beginPath(); ctx.moveTo(leftPad,y+10); ctx.lineTo(cv.width-20,y+10); ctx.stroke();
    ctx.fillStyle = '#90ee90';
    frames.forEach((fr,i)=>{{ if(fr.pressed.includes(name)) {{ const x=xForFrame(i); ctx.fillRect(x, y+2, Math.max(1,(cv.width-leftPad-20)/frames.length), rowH-4); }} }});
  }});

  const fieldNames = ['field4','field5','field6','field7'];
  fieldNames.forEach((name, fi)=>{{
    const y0 = fieldsTop + fi*62;
    ctx.fillStyle = '#aaa'; ctx.fillText(name, 10, y0+28);
    ctx.strokeStyle = '#333'; ctx.strokeRect(leftPad, y0, cv.width-leftPad-20, 50);
    ctx.strokeStyle = ['#ffcc66','#ff6699','#cc99ff','#ffffff'][fi];
    ctx.beginPath();
    frames.forEach((fr,i)=>{{
      const val = [fr.f4, fr.f5, fr.f6, fr.f7][fi];
      const x = xForFrame(i); const y = y0 + 50 - val*50/255;
      if(i===0) ctx.moveTo(x,y); else ctx.lineTo(x,y);
    }});
    ctx.stroke();
  }});

  const sx = xForFrame(selected);
  ctx.strokeStyle = '#ff4444'; ctx.lineWidth = 1;
  ctx.beginPath(); ctx.moveTo(sx, 0); ctx.lineTo(sx, cv.height); ctx.stroke();
}}

function update() {{
  const i = Number(slider.value);
  const fr = frames[i];
  label.textContent = `frame ${{i}} / ${{frames.length-1}}`;
  details.textContent = JSON.stringify(fr, null, 2);
  draw(i);
}}
slider.addEventListener('input', update);
document.getElementById('prev').onclick = () => {{ slider.value = Math.max(0, Number(slider.value)-1); update(); }};
document.getElementById('next').onclick = () => {{ slider.value = Math.min(frames.length-1, Number(slider.value)+1); update(); }};
update();
</script>
</body>
</html>
""", encoding="utf-8")


def export_dem(path: Path, out_dir: Path) -> dict:
    frames = load_dem(path)
    out_dir.mkdir(parents=True, exist_ok=True)

    write_frames_csv(frames, out_dir / "frames.csv")
    write_runs_csv(frames, out_dir / "runs.csv")
    write_viewer_html(frames, out_dir / "viewer.html", path.name)

    summary = summarize(frames)
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    return summary


def main() -> int:
    ap = argparse.ArgumentParser(description="Experimental unpacker for ENG .DEM demo playback/input files.")
    ap.add_argument("inputs", nargs="+", type=Path, help="One or more .DEM files")
    ap.add_argument("-o", "--out-dir", type=Path, default=Path("dem_out"), help="Output root directory")
    args = ap.parse_args()

    errors = 0
    for dem_path in args.inputs:
        out = args.out_dir / dem_path.stem if len(args.inputs) > 1 else args.out_dir
        try:
            summary = export_dem(dem_path, out)
        except Exception as exc:
            print(f"[DEM] ERROR {dem_path}: {exc}")
            errors += 1
            continue

        print(f"[DEM] {dem_path.name}")
        print(f"      frames={summary['frame_count']} size={dem_path.stat().st_size:,} bytes")
        print(f"      duration≈{summary['duration_if_30fps_seconds']:.2f}s at 30 fps / {summary['duration_if_60fps_seconds']:.2f}s at 60 fps")
        print(f"      wrote {out}")

    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
