"""
instance_hunter.py — exploratory STPC placement / world-viewer probe.

This module does not claim to fully decode object placement yet.  It exists to
help reverse-engineer where STPC meshes are instanced in the level world.

Current working model
---------------------

    TRAK  = world/terrain/static sector surfaces.  Table A/B already exports as
            actual triangle geometry.

    STPC  = standalone mesh records.  The vertices are valid, but whether they
            are final world-space meshes or reusable object/prototype meshes is
            still being investigated.

    MAP   = likely contains at least some level-layout references.  MAP Section
            4 is currently the strongest candidate for an instance/object table,
            so this module exports it in several numeric views and searches for
            fields that look like:

                mesh id/reference + position + orientation/scale/flags

The output is intentionally verbose and diagnostic.  It is meant for comparing
against the game, TRAK terrain, and STPC meshes until the real instance format
is confirmed.
"""

from __future__ import annotations

import csv
import html
import json
import math
import struct
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable

from .map_chunk import MapChunk
from .stpc_chunk import MeshCandidate, STPCExportResult
from .trak_chunk import TrakFile

MAP_SECTION4_STRIDE = 48


@dataclass
class MapSection4Entry:
    """One raw 48-byte MAP Section 4 entry."""
    index: int
    file_offset: int
    raw: bytes

    @property
    def u16(self) -> tuple[int, ...]:
        return struct.unpack("<24H", self.raw)

    @property
    def u32(self) -> tuple[int, ...]:
        return struct.unpack("<12I", self.raw)

    @property
    def f32(self) -> tuple[float, ...]:
        return struct.unpack("<12f", self.raw)


@dataclass
class CandidateInstance:
    """One possible STPC placement candidate found inside a raw MAP entry."""
    source: str
    entry_index: int
    mesh_id: int
    mesh_field_kind: str
    mesh_field_index: int
    x: float
    y: float
    z: float
    coord_kind: str
    coord_start: int
    score: float
    notes: list[str] = field(default_factory=list)


@dataclass
class Section4ParseResult:
    entries: list[MapSection4Entry]
    offset: int
    count: int
    warnings: list[str]


@dataclass
class InstanceHuntResult:
    output_dir: Path
    section4: Section4ParseResult | None
    candidates: list[CandidateInstance]
    stpc_mesh_count: int
    trak_bounds: tuple[tuple[float, float, float], tuple[float, float, float]] | None
    map_bounds: tuple[tuple[float, float, float], tuple[float, float, float]] | None
    stpc_mesh_bounds: list[tuple[int, tuple[float, float, float], tuple[float, float, float]]]


# ---------------------------------------------------------------------------
# Geometry / numeric helpers
# ---------------------------------------------------------------------------

def _finite(v: float) -> bool:
    return math.isfinite(v) and not math.isnan(v)


def _bounds_from_points(points: Iterable[tuple[float, float, float]]) -> tuple[tuple[float, float, float], tuple[float, float, float]] | None:
    pts = [(x, y, z) for x, y, z in points if _finite(x) and _finite(y) and _finite(z)]
    if not pts:
        return None
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    zs = [p[2] for p in pts]
    return (min(xs), min(ys), min(zs)), (max(xs), max(ys), max(zs))


def _expand_bounds(bounds: tuple[tuple[float, float, float], tuple[float, float, float]], margin_ratio: float = 0.15, min_margin: float = 128.0):
    (mnx, mny, mnz), (mxx, mxy, mxz) = bounds
    dx = max(mxx - mnx, min_margin)
    dy = max(mxy - mny, min_margin)
    dz = max(mxz - mnz, min_margin)
    mx = max(dx * margin_ratio, min_margin)
    my = max(dy * margin_ratio, min_margin)
    mz = max(dz * margin_ratio, min_margin)
    return (mnx - mx, mny - my, mnz - mz), (mxx + mx, mxy + my, mxz + mz)


def _inside_bounds(p: tuple[float, float, float], bounds: tuple[tuple[float, float, float], tuple[float, float, float]]) -> bool:
    (mnx, mny, mnz), (mxx, mxy, mxz) = bounds
    x, y, z = p
    return mnx <= x <= mxx and mny <= y <= mxy and mnz <= z <= mxz


def _trk_points(trak: TrakFile | None) -> list[tuple[float, float, float]]:
    if trak is None:
        return []
    pts: list[tuple[float, float, float]] = []
    for rec in trak.records:
        pts.extend((v.x, v.y, v.z) for v in rec.table_a)
    return pts


def _map_points(parsed_map: MapChunk | None) -> list[tuple[float, float, float]]:
    if parsed_map is None:
        return []
    return [(t.x, t.y, t.z) for t in parsed_map.tiles]


def _mesh_bounds(meshes: list[MeshCandidate]) -> list[tuple[int, tuple[float, float, float], tuple[float, float, float]]]:
    return [(m.index, m.bounds_min, m.bounds_max) for m in meshes]


def _mesh_centers(meshes: list[MeshCandidate]) -> list[tuple[int, tuple[float, float, float]]]:
    centers = []
    for m in meshes:
        mn, mx = m.bounds_min, m.bounds_max
        centers.append((m.index, ((mn[0] + mx[0]) * 0.5, (mn[1] + mx[1]) * 0.5, (mn[2] + mx[2]) * 0.5)))
    return centers


# ---------------------------------------------------------------------------
# MAP Section 4 extraction
# ---------------------------------------------------------------------------

def extract_map_section4(map_bytes: bytes) -> Section4ParseResult | None:
    """
    Extract MAP Section 4 using the current partial MAP layout.

    This mirrors parse_map_chunk's known section order, but keeps Section 4 raw
    instead of skipping it.  If the MAP has a different layout, the function
    returns None or emits warnings rather than crashing the whole extractor.
    """
    warnings: list[str] = []
    if len(map_bytes) < 12:
        return None

    def need(pos: int, n: int) -> bool:
        return 0 <= pos <= len(map_bytes) and pos + n <= len(map_bytes)

    def u32_at(pos: int) -> int:
        return struct.unpack_from("<I", map_bytes, pos)[0]

    pos = 0
    tile_count = u32_at(pos); pos += 4
    grid_width = u32_at(pos); pos += 4
    grid_height = u32_at(pos); pos += 4
    if tile_count > 1_000_000 or grid_width > 4096 or grid_height > 4096:
        return None

    tile_bytes = tile_count * 24
    if not need(pos, tile_bytes + 4):
        return None
    pos += tile_bytes

    s2_count = u32_at(pos); pos += 4
    if s2_count > 1_000_000 or not need(pos, s2_count * 4 + 4):
        return None
    pos += s2_count * 4

    s3_count = u32_at(pos); pos += 4
    s3_bytes = s3_count * 90
    if s3_count > 1_000_000 or not need(pos, s3_bytes + 4):
        return None
    pos += s3_bytes

    section4_offset = pos
    s4_count = u32_at(pos); pos += 4
    s4_bytes = s4_count * MAP_SECTION4_STRIDE
    if s4_count > 1_000_000 or not need(pos, s4_bytes):
        warnings.append(
            f"Section 4 does not fit with 48-byte stride: count={s4_count}, offset=0x{pos:X}, remaining={len(map_bytes)-pos}"
        )
        return Section4ParseResult(entries=[], offset=section4_offset, count=s4_count, warnings=warnings)

    entries = [
        MapSection4Entry(i, pos + i * MAP_SECTION4_STRIDE, map_bytes[pos + i * MAP_SECTION4_STRIDE:pos + (i + 1) * MAP_SECTION4_STRIDE])
        for i in range(s4_count)
    ]
    return Section4ParseResult(entries=entries, offset=section4_offset, count=s4_count, warnings=warnings)


# ---------------------------------------------------------------------------
# Candidate search
# ---------------------------------------------------------------------------

def _coords_from_u16_triplets(vals: tuple[int, ...]) -> list[tuple[str, int, float, float, float]]:
    """Try several fixed-point interpretations for adjacent u16 triplets."""
    out = []
    for start in range(0, len(vals) - 2):
        a, b, c = vals[start], vals[start + 1], vals[start + 2]
        # Unsigned fixed-point candidates.  The MAP Section 4 values strongly
        # contain 2048/4096-like units, so include common binary scales.
        for div in (1.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0):
            out.append((f"u16/{int(div)}", start, a / div, b / div, c / div))
        # Signed u16 candidates; many game formats store fixed-point coordinates
        # as signed 16-bit values.
        sa, sb, sc = ((v - 65536) if v >= 32768 else v for v in (a, b, c))
        for div in (1.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0):
            out.append((f"s16/{int(div)}", start, sa / div, sb / div, sc / div))
    return out


def _coords_from_f32_triplets(vals: tuple[float, ...]) -> list[tuple[str, int, float, float, float]]:
    out = []
    for start in range(0, len(vals) - 2):
        x, y, z = vals[start], vals[start + 1], vals[start + 2]
        if all(_finite(v) and abs(v) < 1_000_000 for v in (x, y, z)):
            out.append(("f32", start, x, y, z))
    return out


def hunt_section4_candidates(
    section4: Section4ParseResult | None,
    *,
    mesh_count: int,
    world_bounds: tuple[tuple[float, float, float], tuple[float, float, float]] | None,
    max_candidates_per_entry: int = 12,
) -> list[CandidateInstance]:
    """Search MAP Section 4 entries for mesh-id + coordinate-like field combos."""
    if section4 is None or not section4.entries or mesh_count <= 0:
        return []

    expanded_bounds = _expand_bounds(world_bounds) if world_bounds else None
    candidates: list[CandidateInstance] = []

    for entry in section4.entries:
        u16_vals = entry.u16
        u32_vals = entry.u32
        f32_vals = entry.f32

        mesh_fields: list[tuple[str, int, int]] = []
        for i, v in enumerate(u16_vals):
            if v < mesh_count:
                mesh_fields.append(("u16", i, v))
        for i, v in enumerate(u32_vals):
            if v < mesh_count:
                mesh_fields.append(("u32", i, v))

        coord_fields = _coords_from_f32_triplets(f32_vals) + _coords_from_u16_triplets(u16_vals)
        scored: list[CandidateInstance] = []

        for kind, field_idx, mesh_id in mesh_fields:
            for coord_kind, coord_start, x, y, z in coord_fields:
                if not all(_finite(v) for v in (x, y, z)):
                    continue

                notes: list[str] = []
                score = 0.0
                p = (x, y, z)

                # Prefer coordinate triples that fit the actual TRAK/MAP world.
                if expanded_bounds and _inside_bounds(p, expanded_bounds):
                    score += 8.0
                    notes.append("inside expanded TRAK/MAP bounds")
                elif world_bounds and _inside_bounds(p, world_bounds):
                    score += 10.0
                    notes.append("inside exact TRAK/MAP bounds")
                else:
                    # Keep a few out-of-bounds rows because the candidate table
                    # may encode local positions, not final world positions.
                    score -= 5.0

                # Mesh ids are more plausible when the field is not just the
                # very common zero.  Zero is still valid but low-confidence.
                if mesh_id != 0:
                    score += 1.5
                else:
                    score -= 0.5

                # Avoid using the exact same bytes for mesh id and coordinate
                # start when possible.  Overlap is allowed but lower confidence.
                if kind == "u16" and coord_kind.startswith(("u16", "s16")):
                    if coord_start <= field_idx <= coord_start + 2:
                        score -= 2.0
                        notes.append("mesh field overlaps coordinate triplet")
                if kind == "u32" and coord_kind == "f32" and coord_start == field_idx:
                    score -= 2.0
                    notes.append("mesh field overlaps f32 coordinate triplet")

                # Many zero/near-zero triples are likely flags/padding, not XYZ.
                if abs(x) + abs(y) + abs(z) < 0.0001:
                    score -= 4.0
                    notes.append("zero coordinate triple")

                if score >= 2.0:
                    scored.append(CandidateInstance(
                        source="MAP Section 4",
                        entry_index=entry.index,
                        mesh_id=mesh_id,
                        mesh_field_kind=kind,
                        mesh_field_index=field_idx,
                        x=x,
                        y=y,
                        z=z,
                        coord_kind=coord_kind,
                        coord_start=coord_start,
                        score=score,
                        notes=notes,
                    ))

        scored.sort(key=lambda c: c.score, reverse=True)
        candidates.extend(scored[:max_candidates_per_entry])

    candidates.sort(key=lambda c: (c.entry_index, -c.score, c.mesh_id, c.coord_kind, c.coord_start))
    return candidates


# ---------------------------------------------------------------------------
# File exporters
# ---------------------------------------------------------------------------

def _write_section4_csv(section4: Section4ParseResult | None, out_dir: Path) -> Path | None:
    if section4 is None:
        return None
    path = out_dir / "map_section4_entries.csv"
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        header = ["entry", "file_offset", "raw_hex"]
        header += [f"u16_{i:02d}" for i in range(24)]
        header += [f"u32_{i:02d}" for i in range(12)]
        header += [f"f32_{i:02d}" for i in range(12)]
        writer.writerow(header)
        for e in section4.entries:
            writer.writerow([e.index, f"0x{e.file_offset:X}", e.raw.hex()] + list(e.u16) + list(e.u32) + [f"{v:.9g}" for v in e.f32])
    return path


def _write_candidates_csv(candidates: list[CandidateInstance], out_dir: Path) -> Path:
    path = out_dir / "map_section4_instance_candidates.csv"
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            "entry", "mesh_id", "score", "x", "y", "z", "coord_kind", "coord_start",
            "mesh_field_kind", "mesh_field_index", "source", "notes",
        ])
        for c in candidates:
            writer.writerow([
                c.entry_index, c.mesh_id, f"{c.score:.3f}", f"{c.x:.6f}", f"{c.y:.6f}", f"{c.z:.6f}",
                c.coord_kind, c.coord_start, c.mesh_field_kind, c.mesh_field_index, c.source, "; ".join(c.notes),
            ])
    return path


def _write_stpc_bounds_csv(bounds: list[tuple[int, tuple[float, float, float], tuple[float, float, float]]], out_dir: Path) -> Path:
    path = out_dir / "stpc_mesh_bounds.csv"
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["mesh_id", "min_x", "min_y", "min_z", "max_x", "max_y", "max_z", "size_x", "size_y", "size_z"])
        for idx, mn, mx in bounds:
            writer.writerow([idx, *[f"{v:.6f}" for v in mn], *[f"{v:.6f}" for v in mx], f"{mx[0]-mn[0]:.6f}", f"{mx[1]-mn[1]:.6f}", f"{mx[2]-mn[2]:.6f}"])
    return path


def _write_candidate_points_obj(candidates: list[CandidateInstance], out_dir: Path, *, limit: int = 500) -> Path:
    path = out_dir / "candidate_points.obj"
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Candidate STPC instance/world-position points. Diagnostic only.\n")
        f.write("# Each candidate is a small cross marker.\n")
        v = 1
        for c in sorted(candidates, key=lambda x: -x.score)[:limit]:
            s = 24.0
            f.write(f"o candidate_entry_{c.entry_index:04d}_mesh_{c.mesh_id:03d}_score_{c.score:.1f}\n")
            x, y, z = c.x, c.y, c.z
            f.write(f"v {x-s:.6f} {y:.6f} {z:.6f}\n")
            f.write(f"v {x+s:.6f} {y:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y-s:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y+s:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y:.6f} {z-s:.6f}\n")
            f.write(f"v {x:.6f} {y:.6f} {z+s:.6f}\n")
            f.write(f"l {v} {v+1}\n")
            f.write(f"l {v+2} {v+3}\n")
            f.write(f"l {v+4} {v+5}\n")
            v += 6
    return path


def _write_stpc_centers_obj(meshes: list[MeshCandidate], out_dir: Path) -> Path:
    path = out_dir / "stpc_mesh_local_centers.obj"
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Local centers of decoded STPC meshes. Diagnostic only.\n")
        v = 1
        for idx, (x, y, z) in _mesh_centers(meshes):
            s = 10.0
            f.write(f"o stpc_mesh_{idx:03d}_local_center\n")
            f.write(f"v {x-s:.6f} {y:.6f} {z:.6f}\n")
            f.write(f"v {x+s:.6f} {y:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y-s:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y+s:.6f} {z:.6f}\n")
            f.write(f"v {x:.6f} {y:.6f} {z-s:.6f}\n")
            f.write(f"v {x:.6f} {y:.6f} {z+s:.6f}\n")
            f.write(f"l {v} {v+1}\n")
            f.write(f"l {v+2} {v+3}\n")
            f.write(f"l {v+4} {v+5}\n")
            v += 6
    return path


def _write_probe_html(candidates: list[CandidateInstance], bounds, out_dir: Path, *, limit: int = 2000) -> Path:
    path = out_dir / "world_probe_viewer.html"
    rows = [
        {
            "entry": c.entry_index,
            "mesh": c.mesh_id,
            "score": round(c.score, 3),
            "x": c.x,
            "y": c.y,
            "z": c.z,
            "coord": c.coord_kind,
            "coord_start": c.coord_start,
            "mesh_field": f"{c.mesh_field_kind}[{c.mesh_field_index}]",
            "notes": "; ".join(c.notes),
        }
        for c in sorted(candidates, key=lambda x: -x.score)[:limit]
    ]
    json_rows = json.dumps(rows)
    bounds_json = json.dumps(bounds) if bounds else "null"
    html_text = f"""<!doctype html>
<html>
<head>
<meta charset=\"utf-8\">
<title>WAD World Instance Probe</title>
<style>
body {{ margin:0; font-family:system-ui, sans-serif; background:#141414; color:#eee; overflow:hidden; }}
#bar {{ position:absolute; left:0; right:0; top:0; height:56px; background:#202020; display:flex; gap:12px; align-items:center; padding:0 14px; box-sizing:border-box; z-index:2; }}
#canvas {{ position:absolute; left:0; right:0; top:56px; bottom:0; }}
button, select {{ background:#333; color:#eee; border:1px solid #555; padding:6px 9px; border-radius:6px; }}
#tip {{ position:absolute; pointer-events:none; background:rgba(0,0,0,.85); color:#fff; padding:8px 10px; border-radius:6px; font-size:12px; display:none; max-width:360px; z-index:3; }}
#legend {{ margin-left:auto; color:#ccc; font-size:13px; }}
</style>
</head>
<body>
<div id=\"bar\">
  <strong>World instance probe</strong>
  <button id=\"fit\">Fit</button>
  <label>Projection <select id=\"proj\"><option value=\"top\">top-down X/Z</option><option value=\"iso\">isometric</option></select></label>
  <label>Min score <select id=\"score\"><option>2</option><option>4</option><option selected>6</option><option>8</option><option>10</option></select></label>
  <span id=\"legend\">diagnostic MAP Section 4 candidates; not confirmed instances yet</span>
</div>
<canvas id=\"canvas\"></canvas>
<div id=\"tip\"></div>
<script>
const points = {json_rows};
const bounds = {bounds_json};
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const tip = document.getElementById('tip');
let scale = 1, ox = 0, oy = 0, dragging=false, last=null;
function resize() {{ canvas.width = innerWidth; canvas.height = innerHeight - 56; draw(); }}
addEventListener('resize', resize);
function project(p) {{
  if (document.getElementById('proj').value === 'iso') {{ return {{x:(p.x-p.z)*0.7071, y:-p.y*0.55 + (p.x+p.z)*0.35}}; }}
  return {{x:p.x, y:p.z}};
}}
function visible() {{ const minScore = Number(document.getElementById('score').value); return points.filter(p => p.score >= minScore); }}
function fit() {{
  const pts = visible(); if (!pts.length) return;
  let minx=Infinity,miny=Infinity,maxx=-Infinity,maxy=-Infinity;
  for (const p of pts) {{ const q=project(p); minx=Math.min(minx,q.x); miny=Math.min(miny,q.y); maxx=Math.max(maxx,q.x); maxy=Math.max(maxy,q.y); }}
  const w=Math.max(1,maxx-minx), h=Math.max(1,maxy-miny);
  scale = Math.min(canvas.width/(w*1.15), canvas.height/(h*1.15));
  ox = canvas.width/2 - (minx+maxx)/2*scale;
  oy = canvas.height/2 - (miny+maxy)/2*scale;
  draw();
}}
function screen(p) {{ const q=project(p); return {{x:q.x*scale+ox, y:q.y*scale+oy}}; }}
function color(p) {{ const h = (p.mesh * 47) % 360; return `hsl(${{h}},75%,60%)`; }}
function draw() {{
  ctx.clearRect(0,0,canvas.width,canvas.height);
  ctx.fillStyle='#141414'; ctx.fillRect(0,0,canvas.width,canvas.height);
  const pts = visible();
  ctx.lineWidth=1;
  for (const p of pts) {{
    const s=screen(p); if (s.x<-20||s.y<-20||s.x>canvas.width+20||s.y>canvas.height+20) continue;
    const r=Math.max(2, Math.min(7, p.score*0.55));
    ctx.fillStyle=color(p); ctx.globalAlpha=0.75;
    ctx.beginPath(); ctx.arc(s.x,s.y,r,0,Math.PI*2); ctx.fill();
  }}
  ctx.globalAlpha=1; ctx.fillStyle='#ccc'; ctx.fillText(`${{pts.length}} candidates shown`, 12, 20);
}}
function nearest(mx,my) {{
  let best=null,bd=14;
  for (const p of visible()) {{ const s=screen(p); const d=Math.hypot(s.x-mx,s.y-my); if (d<bd) {{bd=d; best=p;}} }}
  return best;
}}
canvas.addEventListener('mousemove', e => {{
  if (dragging) {{ ox += e.clientX-last.x; oy += e.clientY-last.y; last={{x:e.clientX,y:e.clientY}}; draw(); return; }}
  const p=nearest(e.offsetX,e.offsetY); if (!p) {{ tip.style.display='none'; return; }}
  tip.style.display='block'; tip.style.left=(e.clientX+14)+'px'; tip.style.top=(e.clientY+14)+'px';
  tip.innerHTML=`entry <b>${{p.entry}}</b> mesh <b>${{p.mesh}}</b> score <b>${{p.score}}</b><br>`+
    `XYZ: ${{p.x.toFixed(2)}}, ${{p.y.toFixed(2)}}, ${{p.z.toFixed(2)}}<br>`+
    `coord: ${{p.coord}} @ ${{p.coord_start}} | mesh field: ${{p.mesh_field}}<br>${{p.notes}}`;
}});
canvas.addEventListener('mousedown', e => {{ dragging=true; last={{x:e.clientX,y:e.clientY}}; }});
addEventListener('mouseup', e => {{ dragging=false; }});
canvas.addEventListener('wheel', e => {{ e.preventDefault(); const k=e.deltaY<0?1.12:0.89; scale*=k; draw(); }}, {{passive:false}});
document.getElementById('fit').onclick=fit;
document.getElementById('proj').onchange=fit;
document.getElementById('score').onchange=draw;
resize(); fit();
</script>
</body>
</html>"""
    path.write_text(html_text, encoding="utf-8")
    return path


def _write_summary(result: InstanceHuntResult, out_dir: Path) -> Path:
    path = out_dir / "summary.txt"
    lines = []
    lines.append("World / STPC instance-hunting probe")
    lines.append("==================================")
    lines.append("")
    lines.append("This folder is diagnostic. It does not yet prove final object placement.")
    lines.append("The goal is to locate candidate tables containing STPC mesh references plus world XYZ/orientation fields.")
    lines.append("")
    lines.append(f"STPC mesh count: {result.stpc_mesh_count}")
    if result.map_bounds:
        lines.append(f"MAP tile bounds: {result.map_bounds}")
    if result.trak_bounds:
        lines.append(f"TRAK surface bounds: {result.trak_bounds}")
    if result.section4:
        lines.append(f"MAP Section 4: offset=0x{result.section4.offset:X}, count={result.section4.count}, exported_entries={len(result.section4.entries)}")
        for w in result.section4.warnings:
            lines.append(f"  warning: {w}")
    else:
        lines.append("MAP Section 4: not available / could not parse")
    lines.append(f"Candidate rows kept: {len(result.candidates)}")
    lines.append("")
    lines.append("Most important files:")
    lines.append("  map_section4_entries.csv              raw Section 4 rows as u16/u32/f32")
    lines.append("  map_section4_instance_candidates.csv  possible mesh-id + XYZ combinations")
    lines.append("  candidate_points.obj                  marker points for highest-score candidates")
    lines.append("  world_probe_viewer.html               browser viewer for candidates")
    lines.append("  stpc_mesh_bounds.csv                  local bounds for every decoded STPC mesh")
    lines.append("")
    lines.append("Next validation step:")
    lines.append("  Open candidate_points.obj or world_probe_viewer.html and compare high-score points against")
    lines.append("  TRAK terrain/table_b_surfaces.obj plus known in-game prop/object locations.")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return path


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------

def export_instance_hunt(
    *,
    out_dir: Path,
    map_bytes: bytes | None = None,
    parsed_map: MapChunk | None = None,
    trak: TrakFile | None = None,
    stpc_result: STPCExportResult | None = None,
    max_candidates_per_entry: int = 12,
) -> InstanceHuntResult:
    """Write diagnostic instance-hunting files into a dedicated world_probe folder."""
    out_dir.mkdir(parents=True, exist_ok=True)

    meshes = stpc_result.meshes if stpc_result else []
    stpc_bounds = _mesh_bounds(meshes)
    map_bounds = _bounds_from_points(_map_points(parsed_map))
    trak_bounds = _bounds_from_points(_trk_points(trak))

    # Prefer TRAK bounds because TRAK is now confirmed as actual world terrain.
    world_bounds = trak_bounds or map_bounds

    section4 = extract_map_section4(map_bytes) if map_bytes else None
    candidates = hunt_section4_candidates(
        section4,
        mesh_count=len(meshes),
        world_bounds=world_bounds,
        max_candidates_per_entry=max_candidates_per_entry,
    )

    result = InstanceHuntResult(
        output_dir=out_dir,
        section4=section4,
        candidates=candidates,
        stpc_mesh_count=len(meshes),
        trak_bounds=trak_bounds,
        map_bounds=map_bounds,
        stpc_mesh_bounds=stpc_bounds,
    )

    _write_summary(result, out_dir)
    _write_section4_csv(section4, out_dir)
    _write_candidates_csv(candidates, out_dir)
    _write_stpc_bounds_csv(stpc_bounds, out_dir)
    _write_candidate_points_obj(candidates, out_dir)
    _write_stpc_centers_obj(meshes, out_dir)
    _write_probe_html(candidates, world_bounds, out_dir)

    return result
