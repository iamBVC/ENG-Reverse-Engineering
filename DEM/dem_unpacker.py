#!/usr/bin/env python3
"""
dem_unpacker.py — .DEM demo-input unpacker for Disney's The Emperor's New Groove.

Current executable-derived frame layout:

    DEMFile:
        +0x00 u32 frame_count
        +0x04 frame_count x DemoFrame8

    DemoFrame8, 8 bytes:
        +0x00 u16 buttons      PlayStation-style button mask
        +0x02 u16 base_angle   copied by the game to word_5FCF00
        +0x04 u16 aux_u16      copied by the game to dword_58471C; no later use confirmed yet
        +0x06 s8  analog_x     signed analog X; game sign-extends and shifts left by 6
        +0x07 s8  analog_y     signed analog Y; game sign-extends and shifts left by 6

The signed analog bytes use normal two's-complement int8 semantics:
    0x00 = 0, 0x7F = +127, 0x80 = -128, 0xFF = -1

This tool preserves the exact bytes while exporting decoded CSV/JSON/HTML helpers.
"""

from __future__ import annotations

import argparse
import csv
import json
import math
import struct
from collections import Counter
from dataclasses import dataclass
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


def s8_from_u8(value: int) -> int:
    """Convert an unsigned byte to signed int8."""
    value &= 0xFF
    return value - 0x100 if value >= 0x80 else value


def u8_from_s8(value: int) -> int:
    """Convert signed int8 to the exact byte that should be written."""
    if not -128 <= value <= 127:
        raise ValueError(f"signed analog byte out of range: {value}; expected -128..127")
    return value & 0xFF


@dataclass(frozen=True)
class DemFrame:
    frame: int
    buttons: int
    base_angle: int
    aux_u16: int
    analog_x: int
    analog_y: int

    @property
    def angle_degrees_12bit(self) -> float:
        """Interpret base_angle as a 12-bit turn value for diagnostics."""
        return (self.base_angle & 0x0FFF) * 360.0 / 4096.0

    @property
    def angle_hi_nibble(self) -> int:
        return (self.base_angle >> 12) & 0x0F

    @property
    def pressed_names(self) -> list[str]:
        return [name for name, bit in BUTTON_BITS if self.buttons & bit]

    @property
    def analog_x_scaled(self) -> int:
        """Game playback scales signed analog X by << 6."""
        return self.analog_x << 6

    @property
    def analog_y_scaled(self) -> int:
        """Game playback scales signed analog Y by << 6."""
        return self.analog_y << 6

    @property
    def analog_magnitude(self) -> float:
        return math.hypot(self.analog_x, self.analog_y)

    @property
    def analog_angle_4096(self) -> int | None:
        """atan2-style analog direction in the game's likely 0..4095 angle domain."""
        if self.analog_x == 0 and self.analog_y == 0:
            return None
        angle = math.atan2(self.analog_x, self.analog_y)
        if angle < 0:
            angle += math.tau
        return int(round(angle * 4096.0 / math.tau)) & 0x0FFF

    @property
    def raw_bytes(self) -> bytes:
        return struct.pack(
            "<HHHBB",
            self.buttons & 0xFFFF,
            self.base_angle & 0xFFFF,
            self.aux_u16 & 0xFFFF,
            u8_from_s8(self.analog_x),
            u8_from_s8(self.analog_y),
        )

    def raw_hex(self) -> str:
        return self.raw_bytes.hex(" ")


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
        buttons, base_angle, aux_u16, analog_x_raw, analog_y_raw = struct.unpack_from("<HHHBB", data, off)
        frames.append(
            DemFrame(
                frame=i,
                buttons=buttons,
                base_angle=base_angle,
                aux_u16=aux_u16,
                analog_x=s8_from_u8(analog_x_raw),
                analog_y=s8_from_u8(analog_y_raw),
            )
        )
        off += 8
    return frames


def serialize_dem(frames: list[DemFrame]) -> bytes:
    """Serialize frames back into the exact DEM binary layout."""
    out = bytearray(4 + len(frames) * 8)
    struct.pack_into("<I", out, 0, len(frames))
    off = 4
    for fr in frames:
        out[off:off + 8] = fr.raw_bytes
        off += 8
    return bytes(out)


def load_dem(path: Path) -> list[DemFrame]:
    return parse_dem(path.read_bytes())


def counter_dict(values):
    return {str(k): v for k, v in Counter(values).most_common()}


def summarize(frames: list[DemFrame]) -> dict:
    button_counts = {}
    for name, bit in BUTTON_BITS:
        count = sum(1 for fr in frames if fr.buttons & bit)
        if count:
            button_counts[name] = count

    angles = [fr.base_angle for fr in frames]
    aux_values = [fr.aux_u16 for fr in frames]
    analog_x_values = [fr.analog_x for fr in frames]
    analog_y_values = [fr.analog_y for fr in frames]

    return {
        "frame_count": len(frames),
        "duration_if_30fps_seconds": len(frames) / 30.0,
        "duration_if_60fps_seconds": len(frames) / 60.0,
        "unique_exact_frames": len({fr.raw_hex() for fr in frames}),
        "buttons_pressed_frame_counts": button_counts,
        "buttons_raw_common": counter_dict(fr.buttons for fr in frames),
        "base_angle_min": min(angles) if angles else None,
        "base_angle_max": max(angles) if angles else None,
        "base_angle_unique_count": len(set(angles)),
        "aux_u16_common": counter_dict(aux_values),
        "aux_u16_hex_common": {f"0x{k:04X}": v for k, v in Counter(aux_values).most_common()},
        "analog_x_s8_min": min(analog_x_values) if analog_x_values else None,
        "analog_x_s8_max": max(analog_x_values) if analog_x_values else None,
        "analog_x_s8_common": counter_dict(analog_x_values),
        "analog_y_s8_min": min(analog_y_values) if analog_y_values else None,
        "analog_y_s8_max": max(analog_y_values) if analog_y_values else None,
        "analog_y_s8_common": counter_dict(analog_y_values),
    }


def write_frames_csv(frames: list[DemFrame], path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        header = [
            "frame",
            "buttons_hex", "buttons_dec", "pressed",
            "base_angle", "base_angle_degrees_12bit", "base_angle_hi_nibble",
            "aux_u16_hex", "aux_u16_dec", "aux_lo_hex", "aux_hi_hex",
            "analog_x_s8", "analog_x_raw_hex", "analog_x_scaled_game",
            "analog_y_s8", "analog_y_raw_hex", "analog_y_scaled_game",
            "analog_magnitude", "analog_angle_4096",
            "raw_8_bytes_hex",
        ]
        header.extend(f"btn_{name}" for name, _ in BUTTON_BITS)
        w.writerow(header)

        for fr in frames:
            row = [
                fr.frame,
                f"0x{fr.buttons:04X}", fr.buttons, "+".join(fr.pressed_names),
                fr.base_angle, f"{fr.angle_degrees_12bit:.6f}", fr.angle_hi_nibble,
                f"0x{fr.aux_u16:04X}", fr.aux_u16, f"0x{fr.aux_u16 & 0xFF:02X}", f"0x{fr.aux_u16 >> 8:02X}",
                fr.analog_x, f"0x{u8_from_s8(fr.analog_x):02X}", fr.analog_x_scaled,
                fr.analog_y, f"0x{u8_from_s8(fr.analog_y):02X}", fr.analog_y_scaled,
                f"{fr.analog_magnitude:.6f}", "" if fr.analog_angle_4096 is None else fr.analog_angle_4096,
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
            "buttons_hex", "pressed", "base_angle", "base_angle_degrees_12bit",
            "aux_u16_hex", "aux_u16_dec", "analog_x_s8", "analog_y_s8", "raw_8_bytes_hex",
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
                fr.base_angle, f"{fr.angle_degrees_12bit:.6f}",
                f"0x{fr.aux_u16:04X}", fr.aux_u16, fr.analog_x, fr.analog_y, fr.raw_hex(),
            ])
            run_index += 1
            start = i
            last = key


def write_viewer_html(frames: list[DemFrame], path: Path, title: str) -> None:
    """Write a dependency-free HTML timeline viewer for quick visual inspection."""
    data = [{
        "frame": fr.frame,
        "buttons": fr.buttons,
        "pressed": fr.pressed_names,
        "base_angle": fr.base_angle,
        "deg": round(fr.angle_degrees_12bit, 4),
        "aux": fr.aux_u16,
        "ax": fr.analog_x,
        "ay": fr.analog_y,
        "raw": fr.raw_hex(),
    } for fr in frames]

    payload = json.dumps(data)
    button_payload = json.dumps([name for name, _ in BUTTON_BITS])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>{title} DEM viewer</title>
<style>
body {{ margin:0; font-family:system-ui,sans-serif; background:#111; color:#eee; }}
header {{ padding:12px 16px; background:#1c1c1c; border-bottom:1px solid #333; }}
main {{ padding:16px; }}
canvas {{ background:#181818; border:1px solid #333; display:block; max-width:100%; }}
.controls {{ display:flex; gap:16px; align-items:center; margin-bottom:10px; flex-wrap:wrap; }}
.box {{ background:#1d1d1d; border:1px solid #333; padding:10px; margin-top:10px; white-space:pre-wrap; font-family:ui-monospace,SFMono-Regular,Menlo,Consolas,monospace; }}
small {{ color:#aaa; }}
</style>
</head>
<body>
<header>
  <strong>{title}</strong> — DEM input timeline<br>
  <small>Frame = buttons, base_angle, aux_u16, signed analog_x, signed analog_y.</small>
</header>
<main>
  <div class="controls">
    <label>Frame <input id="frame" type="range" min="0" max="{max(len(frames)-1,0)}" value="0" style="width:420px"></label>
    <button id="prev">◀</button><button id="next">▶</button>
    <span id="frameLabel"></span>
  </div>
  <canvas id="cv" width="1200" height="620"></canvas>
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
const leftPad = 100, topPad = 30, angleH = 130, rowH = 18, gap = 14;
const buttonTop = topPad + angleH + gap;
const fieldsTop = buttonTop + buttonNames.length * rowH + gap;
function xForFrame(i) {{ return leftPad + i * (cv.width - leftPad - 20) / Math.max(frames.length - 1, 1); }}
function yForAngle(a) {{ return topPad + angleH - (a & 4095) * angleH / 4095; }}
function yForS8(y0, v) {{ return y0 + 50 - ((v + 128) / 255) * 50; }}
function draw(selected) {{
  ctx.clearRect(0,0,cv.width,cv.height); ctx.fillStyle='#181818'; ctx.fillRect(0,0,cv.width,cv.height);
  ctx.strokeStyle='#333'; ctx.lineWidth=1;
  for (let i=0;i<=4;i++) {{ const y=topPad+i*angleH/4; ctx.beginPath(); ctx.moveTo(leftPad,y); ctx.lineTo(cv.width-20,y); ctx.stroke(); ctx.fillStyle='#aaa'; ctx.fillText(String(Math.round((4-i)*4095/4)),10,y+4); }}
  ctx.fillStyle='#ddd'; ctx.fillText('base_angle',10,topPad-8);
  ctx.strokeStyle='#66ccff'; ctx.lineWidth=2; ctx.beginPath();
  frames.forEach((fr,i)=>{{ const x=xForFrame(i), y=yForAngle(fr.base_angle); if(i===0)ctx.moveTo(x,y); else ctx.lineTo(x,y); }}); ctx.stroke();
  buttonNames.forEach((name,bi)=>{{ const y=buttonTop+bi*rowH; ctx.fillStyle='#aaa'; ctx.fillText(name,10,y+13); ctx.strokeStyle='#252525'; ctx.beginPath(); ctx.moveTo(leftPad,y+9); ctx.lineTo(cv.width-20,y+9); ctx.stroke(); ctx.fillStyle='#90ee90'; frames.forEach((fr,i)=>{{ if(fr.pressed.includes(name)) {{ const x=xForFrame(i); ctx.fillRect(x,y+2,Math.max(1,(cv.width-leftPad-20)/frames.length),rowH-4); }} }}); }});
  const tracks=[['aux_u16','aux',0,65535,'#ffcc66'],['analog_x_s8','ax',-128,127,'#34d399'],['analog_y_s8','ay',-128,127,'#f472b6']];
  tracks.forEach((t,fi)=>{{ const y0=fieldsTop+fi*62; ctx.fillStyle='#aaa'; ctx.fillText(t[0],10,y0+28); ctx.strokeStyle='#333'; ctx.strokeRect(leftPad,y0,cv.width-leftPad-20,50); ctx.strokeStyle=t[4]; ctx.beginPath(); frames.forEach((fr,i)=>{{ const val=fr[t[1]]; const x=xForFrame(i); const y=t[1]==='aux' ? y0+50-(val/65535)*50 : yForS8(y0,val); if(i===0)ctx.moveTo(x,y); else ctx.lineTo(x,y); }}); ctx.stroke(); }});
  const sx=xForFrame(selected); ctx.strokeStyle='#ff4444'; ctx.lineWidth=1; ctx.beginPath(); ctx.moveTo(sx,0); ctx.lineTo(sx,cv.height); ctx.stroke();
}}
function update() {{ const i=Number(slider.value); const fr=frames[i]; label.textContent=`frame ${{i}} / ${{frames.length-1}}`; details.textContent=JSON.stringify(fr,null,2); draw(i); }}
slider.addEventListener('input',update);
document.getElementById('prev').onclick=()=>{{ slider.value=Math.max(0,Number(slider.value)-1); update(); }};
document.getElementById('next').onclick=()=>{{ slider.value=Math.min(frames.length-1,Number(slider.value)+1); update(); }};
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
    ap = argparse.ArgumentParser(description="Unpack ENG .DEM demo playback/input files.")
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
