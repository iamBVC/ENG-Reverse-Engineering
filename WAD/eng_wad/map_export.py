"""
map_export.py — exports for MAP chunk world-tile visualization.

The MAP parser gives us two kinds of level-layout data:

    1) The raw tile list: one parsed world-space XYZ coordinate per tile entry.
    2) The MAP grid: a 2D table of uint32 values, usually 96x96.

The exact relationship between grid values, tile-list entries, tile definitions,
TEXT palettes, and final rendered geometry is still being reverse-engineered.
For that reason the exports here are diagnostic: they create visible, simple
geometry and browser previews so the data can be inspected quickly.
"""

from __future__ import annotations

import csv
import json
import math
from pathlib import Path

from .map_chunk import MapChunk, MapTile


def _require_pillow():
    try:
        from PIL import Image
        return Image
    except ImportError as exc:  # pragma: no cover
        raise RuntimeError("Pillow is required for map PNG export. Install with: pip install Pillow") from exc


def estimate_map_tile_size(tiles: list[MapTile], fallback: float = 64.0) -> float:
    """Estimate a useful marker-quad size from repeated X/Z spacing."""
    if not tiles:
        return fallback

    def positive_steps(values: list[float]) -> list[float]:
        vals = sorted(set(round(v, 4) for v in values if math.isfinite(v)))
        return [abs(b - a) for a, b in zip(vals, vals[1:]) if abs(b - a) > 1e-4]

    steps = positive_steps([t.x for t in tiles]) + positive_steps([t.z for t in tiles])
    if not steps:
        return fallback

    steps.sort()
    pick = steps[min(max(len(steps) // 10, 0), len(steps) - 1)]
    return pick * 0.85 if math.isfinite(pick) and pick > 0 else fallback


def choose_grid_tile_index_base(grid: list[list[int]], tile_count: int) -> int:
    """Choose whether non-zero grid values look more like 0-based or 1-based indices."""
    values = [v for row in grid for v in row if v != 0]
    if not values or tile_count <= 0:
        return 0
    zero_based_hits = sum(1 for v in values if 0 <= v < tile_count)
    one_based_hits = sum(1 for v in values if 1 <= v <= tile_count)
    return 1 if one_based_hits > zero_based_hits else 0


def resolve_grid_tile(grid_value: int, tiles: list[MapTile], index_base: int) -> MapTile | None:
    if grid_value == 0:
        return None
    idx = grid_value - index_base
    if 0 <= idx < len(tiles):
        return tiles[idx]
    return None


def write_map_parse_log(parsed_map: MapChunk, out_dir: Path) -> None:
    with (out_dir / "map_parse_log.txt").open("w", encoding="utf-8") as f:
        f.write("MAP parse log\n")
        f.write("=============\n\n")
        f.write(f"tile_count: {parsed_map.tile_count}\n")
        f.write(f"grid_size: {parsed_map.grid_width}x{parsed_map.grid_height}\n")
        f.write(f"parsed_tiles: {len(parsed_map.tiles)}\n")
        f.write(f"parsed_grid_rows: {len(parsed_map.grid)}\n")
        f.write(f"parsed_tile_defs: {len(parsed_map.tile_defs)}\n")
        f.write(f"parse_stopped_at: 0x{parsed_map.parse_stopped_at:X}\n\n")
        if parsed_map.parse_warnings:
            f.write("Warnings:\n")
            for warning in parsed_map.parse_warnings:
                f.write(f"- {warning}\n")
        else:
            f.write("Warnings: none\n")


def write_map_grid_csv(parsed_map: MapChunk, out_dir: Path) -> None:
    if not parsed_map.grid:
        return
    with (out_dir / "map_grid.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([f"col_{c}" for c in range(parsed_map.grid_width)])
        w.writerows(parsed_map.grid)


def write_map_tiles_csv(parsed_map: MapChunk, out_dir: Path) -> None:
    with (out_dir / "map_tiles.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["tile_idx", "x", "y", "z", "unknown", "flags", "flags_hex", "type_idx"])
        for i, t in enumerate(parsed_map.tiles):
            w.writerow([i, f"{t.x:.9g}", f"{t.y:.9g}", f"{t.z:.9g}", f"{t.unknown:.9g}", t.flags, f"0x{t.flags:08X}", t.type_idx])


def write_map_tile_defs_csv(parsed_map: MapChunk, out_dir: Path) -> None:
    if not parsed_map.tile_defs:
        return
    with (out_dir / "map_tile_defs.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["tile_def_idx", "v0", "v1", "v2", "v4", "v5", "v6"])
        for i, td in enumerate(parsed_map.tile_defs):
            w.writerow([i, td.v0, td.v1, td.v2, td.v4, td.v5, td.v6])


def write_map_grid_png(parsed_map: MapChunk, out_dir: Path) -> None:
    if not parsed_map.grid:
        return
    Image = _require_pillow()
    import colorsys

    grid = parsed_map.grid
    flat = [v for row in grid for v in row]
    unique = sorted(set(v for v in flat if v != 0))
    n_u = max(len(unique), 1)
    colors: dict[int, tuple[int, int, int]] = {0: (30, 30, 30)}
    for idx, val in enumerate(unique):
        r, g, b = (int(x * 255) for x in colorsys.hsv_to_rgb(idx / n_u, 0.75, 0.90))
        colors[val] = (r, g, b)

    scale = 6
    img = Image.new("RGB", (parsed_map.grid_width * scale, parsed_map.grid_height * scale), (20, 20, 20))
    px = img.load()
    for row_i, row in enumerate(grid):
        for col_i, val in enumerate(row):
            col = colors.get(val, (200, 0, 200))
            for dy in range(scale):
                for dx in range(scale):
                    px[col_i * scale + dx, row_i * scale + dy] = col
    img.save(out_dir / "map_grid.png")


def write_map_world_tiles_csv(parsed_map: MapChunk, out_dir: Path) -> None:
    with (out_dir / "map_world_tiles.csv").open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow(["tile_idx", "x", "y", "z", "unknown", "flags", "flags_hex", "type_idx"])
        for i, t in enumerate(parsed_map.tiles):
            w.writerow([i, f"{t.x:.9g}", f"{t.y:.9g}", f"{t.z:.9g}", f"{t.unknown:.9g}", t.flags, f"0x{t.flags:08X}", t.type_idx])


def write_map_grid_world_csv(parsed_map: MapChunk, out_dir: Path) -> int:
    index_base = choose_grid_tile_index_base(parsed_map.grid, len(parsed_map.tiles))
    if not parsed_map.grid:
        return index_base
    with (out_dir / "map_grid_world.csv").open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow(["row", "col", "grid_value", "index_base", "tile_idx", "x", "y", "z", "unknown", "flags", "flags_hex", "type_idx"])
        for row_i, row in enumerate(parsed_map.grid):
            for col_i, grid_value in enumerate(row):
                if grid_value == 0:
                    continue
                tile = resolve_grid_tile(grid_value, parsed_map.tiles, index_base)
                if tile is None:
                    w.writerow([row_i, col_i, grid_value, index_base, "", "", "", "", "", "", "", ""])
                    continue
                tile_idx = grid_value - index_base
                w.writerow([row_i, col_i, grid_value, index_base, tile_idx, f"{tile.x:.9g}", f"{tile.y:.9g}", f"{tile.z:.9g}", f"{tile.unknown:.9g}", tile.flags, f"0x{tile.flags:08X}", tile.type_idx])
    return index_base


def _write_mtl(path: Path) -> None:
    import colorsys
    with path.open("w", encoding="utf-8", newline="\n") as f:
        f.write("# Diagnostic materials for MAP world-tile OBJ export\n")
        for i in range(16):
            r, g, b = colorsys.hsv_to_rgb(i / 16, 0.65, 0.95)
            f.write(f"newmtl tile_type_{i:02d}\n")
            f.write(f"Kd {r:.6f} {g:.6f} {b:.6f}\n\n")


def write_map_world_tiles_obj(parsed_map: MapChunk, out_dir: Path, *, tile_size: float | None = None) -> None:
    if not parsed_map.tiles:
        return
    if tile_size is None or tile_size <= 0:
        tile_size = estimate_map_tile_size(parsed_map.tiles)
    half = tile_size * 0.5
    _write_mtl(out_dir / "map_world_tiles.mtl")

    with (out_dir / "map_world_tiles.obj").open("w", encoding="utf-8", newline="\n") as f:
        f.write("# MAP world-tile diagnostic mesh\n")
        f.write("# Each tile-list entry is drawn as one small quad centered on its parsed XYZ position.\n")
        f.write("# This is for visualization/reverse-engineering, not final level geometry.\n")
        f.write(f"# tile_count={len(parsed_map.tiles)}\n")
        f.write(f"# visual_tile_size={tile_size:.9g}\n")
        f.write("mtllib map_world_tiles.mtl\n")
        f.write("o map_world_tiles\n")

        for t in parsed_map.tiles:
            f.write(f"v {t.x - half:.9g} {t.y:.9g} {t.z - half:.9g}\n")
            f.write(f"v {t.x + half:.9g} {t.y:.9g} {t.z - half:.9g}\n")
            f.write(f"v {t.x + half:.9g} {t.y:.9g} {t.z + half:.9g}\n")
            f.write(f"v {t.x - half:.9g} {t.y:.9g} {t.z + half:.9g}\n")

        current_mat = None
        for i, t in enumerate(parsed_map.tiles):
            mat = f"tile_type_{t.type_idx % 16:02d}"
            if mat != current_mat:
                current_mat = mat
                f.write(f"usemtl {mat}\n")
            a = i * 4 + 1
            f.write(f"f {a} {a + 1} {a + 2}\n")
            f.write(f"f {a} {a + 2} {a + 3}\n")


def write_map_grid_world_obj(parsed_map: MapChunk, out_dir: Path, *, tile_size: float | None = None) -> None:
    if not parsed_map.grid or not parsed_map.tiles:
        return
    if tile_size is None or tile_size <= 0:
        tile_size = estimate_map_tile_size(parsed_map.tiles)
    half = tile_size * 0.5
    index_base = choose_grid_tile_index_base(parsed_map.grid, len(parsed_map.tiles))

    with (out_dir / "map_grid_world.obj").open("w", encoding="utf-8", newline="\n") as f:
        f.write("# MAP grid resolved to tile-list XYZ positions\n")
        f.write("# Non-zero grid cells are looked up against the tile list using the best detected index base.\n")
        f.write(f"# detected_grid_index_base={index_base}\n")
        f.write(f"# visual_tile_size={tile_size:.9g}\n")
        f.write("o map_grid_world\n")

        faces: list[tuple[int, int, int, int]] = []
        for row in parsed_map.grid:
            for grid_value in row:
                tile = resolve_grid_tile(grid_value, parsed_map.tiles, index_base)
                if tile is None:
                    continue
                base = len(faces) * 4 + 1
                f.write(f"v {tile.x - half:.9g} {tile.y:.9g} {tile.z - half:.9g}\n")
                f.write(f"v {tile.x + half:.9g} {tile.y:.9g} {tile.z - half:.9g}\n")
                f.write(f"v {tile.x + half:.9g} {tile.y:.9g} {tile.z + half:.9g}\n")
                f.write(f"v {tile.x - half:.9g} {tile.y:.9g} {tile.z + half:.9g}\n")
                faces.append((base, base + 1, base + 2, base + 3))

        for a, b, c, d in faces:
            f.write(f"f {a} {b} {c}\n")
            f.write(f"f {a} {c} {d}\n")


def write_map_world_viewer_html(parsed_map: MapChunk, out_dir: Path) -> None:
    """Write an improved zero-dependency HTML viewer with height coloring and hover details."""
    if not parsed_map.tiles:
        return

    tiles = [[i, round(t.x, 4), round(t.y, 4), round(t.z, 4), int(t.flags), int(t.type_idx)] for i, t in enumerate(parsed_map.tiles)]
    xs = [p[1] for p in tiles]; ys = [p[2] for p in tiles]; zs = [p[3] for p in tiles]
    payload = json.dumps({
        "tiles": tiles,
        "bounds": {"min_x": min(xs), "max_x": max(xs), "min_y": min(ys), "max_y": max(ys), "min_z": min(zs), "max_z": max(zs)},
    })

    html = f'''<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>ENG MAP world tile preview</title>
<style>
html, body {{ margin:0; height:100%; overflow:hidden; background:#111; color:#eee; font-family:system-ui, sans-serif; }}
#bar {{ position:fixed; left:0; right:0; top:0; padding:8px 12px; background:rgba(0,0,0,.78); z-index:2; font-size:14px; }}
#c {{ display:block; width:100vw; height:100vh; }}
#tip {{ position:fixed; display:none; pointer-events:none; background:rgba(0,0,0,.88); border:1px solid #777; padding:6px 8px; border-radius:6px; font:12px/1.35 ui-monospace, SFMono-Regular, Menlo, Consolas, monospace; z-index:3; }}
button, select, input {{ vertical-align:middle; }}
</style>
</head>
<body>
<div id="bar">
  MAP world tile preview — drag to pan, wheel to zoom.
  <button onclick="mode='top'; draw()">Top X/Z</button>
  <button onclick="mode='iso'; draw()">Isometric</button>
  Color <select id="colorMode" onchange="draw()"><option value="height">height</option><option value="type">type_idx</option><option value="flags">flags</option></select>
  Point size <input id="ps" type="range" min="1" max="10" value="4" oninput="draw()">
  <span id="info"></span>
</div>
<canvas id="c"></canvas><div id="tip"></div>
<script>
const DATA = {payload};
const canvas = document.getElementById('c');
const ctx = canvas.getContext('2d');
const info = document.getElementById('info');
const tip = document.getElementById('tip');
let zoom = 0.08, ox = 0, oy = 35, mode = 'iso';
let dragging = false, lx = 0, ly = 0;
let projected = [];
function resize() {{ canvas.width = innerWidth; canvas.height = innerHeight; draw(); }}
addEventListener('resize', resize);
canvas.addEventListener('mousedown', e => {{ dragging = true; lx = e.clientX; ly = e.clientY; }});
addEventListener('mouseup', () => dragging = false);
addEventListener('mousemove', e => {{
  if (dragging) {{ ox += e.clientX-lx; oy += e.clientY-ly; lx=e.clientX; ly=e.clientY; draw(); return; }}
  const ps = Number(document.getElementById('ps').value) + 4;
  let best = null, bd = ps * ps;
  for (const p of projected) {{ const dx=e.clientX-p.sx, dy=e.clientY-p.sy, d=dx*dx+dy*dy; if (d < bd) {{ bd=d; best=p; }} }}
  if (!best) {{ tip.style.display='none'; return; }}
  const t = best.tile;
  tip.style.display='block'; tip.style.left=(e.clientX+12)+'px'; tip.style.top=(e.clientY+12)+'px';
  tip.innerHTML = `tile ${{t[0]}}<br>x=${{t[1]}} y=${{t[2]}} z=${{t[3]}}<br>flags=0x${{(t[4]>>>0).toString(16).padStart(8,'0')}}<br>type_idx=${{t[5]}}`;
}});
canvas.addEventListener('wheel', e => {{ e.preventDefault(); zoom *= Math.exp(-e.deltaY * 0.001); draw(); }}, {{passive:false}});
function project(t) {{
  const x=t[1], y=t[2], z=t[3];
  if (mode === 'top') return [x * zoom + canvas.width/2 + ox, z * zoom + canvas.height/2 + oy];
  return [(x - z) * zoom + canvas.width/2 + ox, ((x + z) * 0.42 - y * 1.2) * zoom + canvas.height/2 + oy];
}}
function colorFor(t) {{
  const cm = document.getElementById('colorMode').value;
  if (cm === 'height') {{ const b=DATA.bounds; const k=(t[2]-b.min_y)/Math.max(1e-6,b.max_y-b.min_y); return `hsl(${{240-240*k}} 90% 60%)`; }}
  if (cm === 'flags') {{ return `hsl(${{((t[4]>>>0)*31)%360}} 80% 60%)`; }}
  return `hsl(${{(t[5]*47)%360}} 80% 60%)`;
}}
function draw() {{
  ctx.fillStyle='#111'; ctx.fillRect(0,0,canvas.width,canvas.height);
  const ps = Number(document.getElementById('ps').value);
  projected = [];
  const sorted = mode === 'iso' ? [...DATA.tiles].sort((a,b)=>(a[1]+a[3])-(b[1]+b[3])) : DATA.tiles;
  for (const t of sorted) {{
    const [sx, sy] = project(t);
    if (sx < -20 || sy < -20 || sx > canvas.width + 20 || sy > canvas.height + 20) continue;
    ctx.fillStyle = colorFor(t); ctx.fillRect(sx-ps/2, sy-ps/2, ps, ps);
    projected.push({{sx, sy, tile:t}});
  }}
  const b=DATA.bounds;
  info.textContent = ` tiles=${{DATA.tiles.length}} bounds X[${{b.min_x}}, ${{b.max_x}}] Y[${{b.min_y}}, ${{b.max_y}}] Z[${{b.min_z}}, ${{b.max_z}}] zoom=${{zoom.toFixed(3)}}`;
}}
resize();
</script>
</body>
</html>
'''
    (out_dir / "map_world_viewer.html").write_text(html, encoding="utf-8")


def export_map_outputs(parsed_map: MapChunk, out_dir: Path, *, verbose: bool = True) -> None:
    """Write all MAP CSV/PNG/OBJ/HTML outputs to the clean map/ folder."""
    out_dir.mkdir(parents=True, exist_ok=True)
    write_map_parse_log(parsed_map, out_dir)
    write_map_tiles_csv(parsed_map, out_dir)
    write_map_tile_defs_csv(parsed_map, out_dir)
    write_map_grid_csv(parsed_map, out_dir)
    write_map_grid_png(parsed_map, out_dir)
    write_map_world_tiles_csv(parsed_map, out_dir)
    grid_base = write_map_grid_world_csv(parsed_map, out_dir)
    write_map_world_tiles_obj(parsed_map, out_dir)
    write_map_grid_world_obj(parsed_map, out_dir)
    write_map_world_viewer_html(parsed_map, out_dir)

    if verbose:
        print(f"  → map/map_tiles.csv ({len(parsed_map.tiles)} tile-list XYZ entries)")
        if parsed_map.grid:
            print(f"  → map/map_grid.csv and map_grid.png ({parsed_map.grid_width}×{parsed_map.grid_height})")
            print(f"  → map/map_grid_world.csv (grid IDs resolved as {'1-based' if grid_base == 1 else '0-based'} where possible)")
        print("  → map/map_world_tiles.obj, map_grid_world.obj, map_world_tiles.mtl")
        print("  → map/map_world_viewer.html (height/type/flag coloring + hover tooltip)")
