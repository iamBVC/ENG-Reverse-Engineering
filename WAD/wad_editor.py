#!/usr/bin/env python3
"""wad_editor.py — Full WAD editor with chunk splitting, 3D world view, and object editing.

Architecture:
  WorkFolder        — extracts every chunk to {wad_stem}_wadedit/*.bin + manifest.json
  Camera            — orbital (target + distance + yaw + pitch) with orbit/pan/zoom
  SceneData         — terrain + object geometry; pre-builds numpy arrays for fast rendering
  WorldCanvas       — PIL-backed 3D canvas; throttles redraws to one per event-loop tick
  ObjectEditDialog  — edit all MapObjectRecord fields; type combobox shows all level types
  AddObjectDialog   — pick type + position, optionally clone fields from selection
  WadEditorApp      — main window: Overview | World tabs + save button
"""

from __future__ import annotations

import math
import re
import struct
import sys
import tkinter as tk
from pathlib import Path
from tkinter import filedialog, messagebox, ttk
from typing import Any

# ── Optional deps ────────────────────────────────────────────────────────────
try:
    import numpy as np
    HAS_NUMPY = True
except ImportError:
    HAS_NUMPY = False

try:
    from PIL import Image, ImageDraw, ImageTk
    HAS_PIL = True
except ImportError:
    HAS_PIL = False
    Image = None      # type: ignore[assignment]
    ImageDraw = None  # type: ignore[assignment]
    ImageTk = None    # type: ignore[assignment]

# ── Project imports ───────────────────────────────────────────────────────────
from eng_wad.chunk_utils import quick_element_count as _quick_element_count
from eng_wad.editor_config import (
    CONFIG_PATH,
    DEFAULT_EDITOR_CONFIG,
    cfg_color,
    load_editor_config,
    save_editor_config,
)
from eng_wad.map_patch import (
    OBJ_RECORD_SIZE,
    add_object_to_map_chunk,
    build_type_registry,
    delete_object_from_map_chunk,
    make_object_copy,
    pack_map_object,
    patch_map_chunk_object,
)
from eng_wad.obj_mesh import parse_placed_object_obj
from eng_wad.stpc_names import build_stpc_name_map
from eng_wad.wad import read_wad
from eng_wad.work_folder import WorkFolder

try:
    from eng_wad.map_full_chunk import MapFullExe, MapObjectRecord, parse_map_full_exe
    HAS_MAP = True
except ImportError:
    HAS_MAP = False

try:
    from eng_wad.trak_chunk import TrakFile, parse_trak_chunk
    HAS_TRAK = True
except ImportError:
    HAS_TRAK = False

# ─────────────────────────────────────────────────────────────────────────────
# Constants
# ─────────────────────────────────────────────────────────────────────────────

MAX_RENDER_TRIS  = 8000   # painter's-algorithm budget per frame

BG_COLOR        = (17, 19, 23)
TERRAIN_COLOR   = (70, 90, 110)
TERRAIN_EDGE    = (40, 60, 80)
OBJ_COLOR       = (240, 180, 60)
OBJ_SEL_COLOR   = (255, 80, 80)
OBJ_RADIUS      = 6

_TC = TERRAIN_COLOR   # short alias inside hot path
_TE = TERRAIN_EDGE

# Scene geometry
# ─────────────────────────────────────────────────────────────────────────────

def _fixed12_signed(v: int) -> float:
    return struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0] / 4096.0

def _rotate_xz(x: float, z: float, a: float) -> tuple[float, float]:
    c, s = math.cos(a), math.sin(a)
    return x * c - z * s, x * s + z * c


class SceneData:
    """Terrain triangles + object markers, with pre-built numpy arrays for the renderer."""

    def __init__(self) -> None:
        self.terrain_tris: list[tuple[list, float]] = []
        self.terrain_meta: list[dict[str, int]] = []
        self.object_positions: list[list[float]]    = []
        self.object_tris: list[tuple[list, int, float]] = []
        self.bounds: tuple = (0, 0, 0, 1, 1, 1)
        # numpy fast path (populated in _build_numpy())
        self.verts_np:  "np.ndarray | None" = None   # (3*M, 3) float32
        self.shades_np: "np.ndarray | None" = None   # (M,) float32
        self.objs_np:   "np.ndarray | None" = None   # (K, 3) float32

    def build(self, mapx: "MapFullExe", trak: "TrakFile", *, terrain_yaw_sign: int = 1) -> None:  # type: ignore[name-defined]
        self.terrain_tris.clear()
        self.terrain_meta.clear()
        self.object_positions.clear()
        self.object_tris.clear()
        xs: list[float] = []
        ys: list[float] = []
        zs: list[float] = []

        for tile_i, tile in enumerate(mapx.tiles):
            if tile_i >= len(mapx.tile_trak_indices):
                continue
            rec_i = mapx.tile_trak_indices[tile_i]
            if rec_i < 0 or rec_i >= len(trak.records):
                continue
            rec = trak.records[rec_i]
            if not rec.table_a or not rec.table_b:
                continue

            if tile_i < len(mapx.tile_defs):
                td       = mapx.tile_defs[tile_i]
                tx       = _fixed12_signed(td.u32_12)
                ty       = _fixed12_signed(td.u32_16)
                tz       = -_fixed12_signed(td.u32_20)
                yaw_units = td.u32_04 & 0xFFFF
            else:
                tx, ty, tz = tile.x, tile.y, tile.z
                yaw_units  = 0

            yaw = terrain_yaw_sign * (yaw_units / 4096.0) * math.tau if yaw_units else 0.0
            placed: list[list[float]] = []
            for v in rec.table_a:
                rx, rz  = _rotate_xz(v.x, v.z, yaw) if yaw else (v.x, v.z)
                px, py, pz = tx + rx, ty + v.y, -(tz + rz)
                placed.append([px, py, pz])
                xs.append(px); ys.append(py); zs.append(pz)

            for tri in rec.table_b:
                if not (tri.i0 < len(placed) and tri.i1 < len(placed) and tri.i2 < len(placed)):
                    continue
                if len({tri.i0, tri.i1, tri.i2}) != 3:
                    continue
                verts = [placed[tri.i0], placed[tri.i1], placed[tri.i2]]
                cy = (verts[0][1] + verts[1][1] + verts[2][1]) / 3.0
                self.terrain_tris.append((verts, cy))
                self.terrain_meta.append({
                    "tile_index": tile_i,
                    "trak_index": rec_i,
                    "tri_index": len(self.terrain_tris) - 1,
                })

        for obj in mapx.objects:
            ox = obj.pos_x_fixed12 / 4096.0
            oy = obj.pos_y_fixed12 / 4096.0
            oz = obj.pos_z_fixed12 / 4096.0
            self.object_positions.append([ox, oy, oz])
            xs.append(ox); ys.append(oy); zs.append(oz)

        self.bounds = (min(xs), min(ys), min(zs), max(xs), max(ys), max(zs)) if xs else (0,0,0,1,1,1)
        self._build_numpy()

    def _build_numpy(self) -> None:
        """Pre-flatten terrain into (3*M, 3) + (M,) numpy arrays for batch projection."""
        self.verts_np = None
        self.shades_np = None
        self.objs_np = None
        if not HAS_NUMPY:
            return
        M = len(self.terrain_tris)
        if M:
            v = np.empty((M * 3, 3), dtype=np.float32)
            s = np.empty(M, dtype=np.float32)
            for i, (tri_verts, shade) in enumerate(self.terrain_tris):
                base = i * 3
                v[base]     = tri_verts[0]
                v[base + 1] = tri_verts[1]
                v[base + 2] = tri_verts[2]
                s[i]        = shade
            self.verts_np  = v
            self.shades_np = s
        if self.object_positions:
            self.objs_np = np.array(self.object_positions, dtype=np.float32)

    def rebuild_terrain_numpy(self) -> None:
        self._build_numpy()

    @property
    def center(self) -> tuple[float, float, float]:
        bx0, by0, bz0, bx1, by1, bz1 = self.bounds
        return (bx0+bx1)*0.5, (by0+by1)*0.5, (bz0+bz1)*0.5

    @property
    def span(self) -> float:
        bx0, by0, bz0, bx1, by1, bz1 = self.bounds
        return max(bx1-bx0, by1-by0, bz1-bz0, 1.0)


# ─────────────────────────────────────────────────────────────────────────────
# Camera
# ─────────────────────────────────────────────────────────────────────────────

class Camera:
    def __init__(self) -> None:
        self.cx = self.cy = self.cz = 0.0
        self.distance = 100.0
        self.yaw   = 0.5
        self.pitch = 0.4
        self.fov   = 60.0

    def reset_to_scene(self, scene: SceneData) -> None:
        self.cx, self.cy, self.cz = scene.center
        self.distance = scene.span * 1.5
        self.yaw, self.pitch = 0.5, 0.4

    def eye(self) -> tuple[float, float, float]:
        sp, cp = math.sin(self.pitch), math.cos(self.pitch)
        sy, cy = math.sin(self.yaw),   math.cos(self.yaw)
        return (self.cx + self.distance * cp * sy,
                self.cy + self.distance * sp,
                self.cz + self.distance * cp * cy)

    def orbit(self, dyaw: float, dpitch: float) -> None:
        self.yaw  += dyaw
        self.pitch = max(-1.4, min(1.4, self.pitch + dpitch))

    def pan(self, dx: float, dy: float) -> None:
        sy, cy = math.sin(self.yaw), math.cos(self.yaw)
        sp, cp = math.sin(self.pitch), math.cos(self.pitch)
        scale   = self.distance * 0.001
        rx, rz  = cy, -sy
        ux, uy, uz = -sy*sp, cp, -cy*sp
        self.cx -= (dx*rx - dy*ux) * scale
        self.cy -= dy*uy * scale
        self.cz -= (dx*rz - dy*uz) * scale

    def zoom(self, factor: float) -> None:
        self.distance = max(0.01, self.distance * factor)


# ─────────────────────────────────────────────────────────────────────────────
# Renderer — numpy batch projection
# ─────────────────────────────────────────────────────────────────────────────

def _cam_basis(cam: Camera) -> tuple:
    """Return (eye_np, fwd, right, up, f_px) — numpy vectors for projection."""
    ex, ey, ez = cam.eye()
    eye = np.array([ex, ey, ez], dtype=np.float64)
    fwd = np.array([cam.cx - ex, cam.cy - ey, cam.cz - ez], dtype=np.float64)
    fn  = np.linalg.norm(fwd)
    fwd = fwd / fn if fn > 1e-9 else np.array([0, 0, -1.0])
    right = np.cross(fwd, [0.0, 1.0, 0.0])
    rn    = np.linalg.norm(right)
    right = right / rn if rn > 1e-9 else np.array([1.0, 0.0, 0.0])
    up    = np.cross(right, fwd)
    return eye, fwd, right, up


def _project_world_point(cam: Camera, p: list[float] | tuple[float, float, float],
                         w: int, h: int) -> tuple[float, float, float] | None:
    ex, ey, ez = cam.eye()
    fx, fy, fz = cam.cx - ex, cam.cy - ey, cam.cz - ez
    fl = math.sqrt(fx * fx + fy * fy + fz * fz)
    if fl <= 1e-9:
        return None
    fx, fy, fz = fx / fl, fy / fl, fz / fl
    rx, ry, rz = -fz, 0.0, fx
    rl = math.sqrt(rx * rx + rz * rz)
    if rl <= 1e-9:
        rx, ry, rz = 1.0, 0.0, 0.0
    else:
        rx, rz = rx / rl, rz / rl
    ux = ry * fz - rz * fy
    uy = rz * fx - rx * fz
    uz = rx * fy - ry * fx
    dx, dy, dz = p[0] - ex, p[1] - ey, p[2] - ez
    depth = dx * fx + dy * fy + dz * fz
    if depth <= 0.1:
        return None
    f_px = min(w, h) * 0.5 / math.tan(math.radians(cam.fov * 0.5))
    sx = w * 0.5 + (dx * rx + dy * ry + dz * rz) / depth * f_px
    sy = h * 0.5 - (dx * ux + dy * uy + dz * uz) / depth * f_px
    return sx, sy, depth


def _draw_object_meshes(draw: Any, scene: SceneData, cam: Camera, w: int, h: int,
                        selected_obj: int | None, cfg: dict[str, Any]) -> None:
    if not scene.object_tris:
        return
    obj_col = cfg_color(cfg, "object_mesh", (182, 108, 255))
    obj_sel = cfg_color(cfg, "object_mesh_selected", (255, 122, 217))
    edge = cfg_color(cfg, "terrain_edge", TERRAIN_EDGE)
    drawlist = []
    for verts, obj_i, _cy in scene.object_tris:
        projs = [_project_world_point(cam, p, w, h) for p in verts]
        if any(p is None for p in projs):
            continue
        pts = [(p[0], p[1]) for p in projs if p is not None]
        depth = sum(p[2] for p in projs if p is not None) / 3.0
        drawlist.append((depth, obj_i, pts))
    drawlist.sort(key=lambda x: -x[0])
    for _depth, obj_i, pts in drawlist:
        draw.polygon(pts, fill=obj_sel if obj_i == selected_obj else obj_col, outline=edge)


def render_scene(
    scene: SceneData,
    cam: Camera,
    w: int, h: int,
    selected_obj: int | None = None,
    selected_terrain: int | None = None,
    selected_tile: int | None = None,
    mode: str = "object",
    cfg: dict[str, Any] | None = None,
) -> "Image.Image":   # type: ignore[name-defined]
    if not HAS_PIL:
        raise RuntimeError("Pillow not installed")

    cfg = cfg or DEFAULT_EDITOR_CONFIG
    bg = cfg_color(cfg, "background", BG_COLOR)
    terrain_col = cfg_color(cfg, "terrain", TERRAIN_COLOR)
    terrain_edge = cfg_color(cfg, "terrain_edge", TERRAIN_EDGE)
    terrain_sel = cfg_color(cfg, "terrain_selected", (230, 208, 92))
    obj_col = cfg_color(cfg, "object_marker", OBJ_COLOR)
    obj_sel = cfg_color(cfg, "object_selected", OBJ_SEL_COLOR)
    obj_radius = int(cfg.get("viewport", {}).get("object_radius", OBJ_RADIUS))

    img  = Image.new("RGB", (w, h), bg)
    draw = ImageDraw.Draw(img)

    if scene.verts_np is None and not scene.object_positions:
        draw.text((10, 10), "No scene geometry", fill=(180, 180, 180))
        return img

    # ── numpy path ───────────────────────────────────────────────────────────
    if HAS_NUMPY and scene.verts_np is not None and scene.verts_np.shape[0] > 0:
        eye, fwd, right, up = _cam_basis(cam)
        f_px = min(w, h) * 0.5 / math.tan(math.radians(cam.fov * 0.5))
        hW, hH = w * 0.5, h * 0.5

        NEAR = 0.5   # world-unit near plane; tuned for ENG fixed-point scale

        V  = scene.verts_np.astype(np.float64)   # (3*M, 3)
        S  = scene.shades_np                      # (M,)
        M  = S.shape[0]

        d       = V - eye                         # (3*M, 3)
        dep     = d @ fwd                         # (3*M,)  signed depth

        # Clamp per-vertex depth to NEAR for projection.
        # Behind-camera vertices get a real finite projected position instead of
        # landing at screen-centre (which breaks frustum culling).
        safe_d  = dep.clip(NEAR, None)            # (3*M,)
        sx      = hW + (d @ right) / safe_d * f_px  # (3*M,)
        sy      = hH - (d @ up)    / safe_d * f_px  # (3*M,)

        # Per-face indices into the flat vertex array
        i0 = np.arange(0, M * 3, 3)
        i1 = i0 + 1
        i2 = i0 + 2

        fd  = (dep[i0] + dep[i1] + dep[i2]) / 3.0  # (M,) face-centre depth
        # Cull by face centre, not per-vertex.
        # This keeps large tris whose centre is in front even when one vertex
        # dips behind the near plane, eliminating the "vanishes too close" issue.
        vis = fd > NEAR

        # Frustum cull in screen space.
        # With correct (clamped) projections, behind-camera verts now produce
        # large off-screen coordinates, so the bounding-box test works properly.
        max_sx_f = np.maximum(np.maximum(sx[i0], sx[i1]), sx[i2])
        min_sx_f = np.minimum(np.minimum(sx[i0], sx[i1]), sx[i2])
        max_sy_f = np.maximum(np.maximum(sy[i0], sy[i1]), sy[i2])
        min_sy_f = np.minimum(np.minimum(sy[i0], sy[i1]), sy[i2])
        vis &= (max_sx_f >= 0) & (min_sx_f <= w) & (max_sy_f >= 0) & (min_sy_f <= h)

        vis_idx = np.where(vis)[0]
        if vis_idx.size:
            # Sort nearest-first so the budget keeps the closest triangles,
            # then reverse to farthest-first for painter's algorithm drawing.
            near_order = vis_idx[np.argsort(fd[vis_idx])]    # nearest → farthest
            max_tris = int(cfg.get("viewport", {}).get("max_render_tris", MAX_RENDER_TRIS))
            if near_order.size > max_tris:
                near_order = near_order[:max_tris]     # drop distant excess
            order = near_order[::-1]                          # draw far → near

            s_min   = float(S.min())
            s_range = max(float(S.max()) - s_min, 1.0)
            # Pre-compute per-face shade colours
            t       = (S - s_min) / s_range            # (M,)
            blend   = (0.4 + 0.6 * t).clip(0.0, 1.0)  # (M,)
            cr      = (terrain_col[0] * blend).astype(np.uint8)
            cg      = (terrain_col[1] * blend).astype(np.uint8)
            cb      = (terrain_col[2] * blend).astype(np.uint8)

            sx_f = sx.astype(np.float32)
            sy_f = sy.astype(np.float32)

            for fi in order:
                ia, ib, ic = i0[fi], i1[fi], i2[fi]
                ax  = sx_f[ib] - sx_f[ia];  ay = sy_f[ib] - sy_f[ia]
                bx_ = sx_f[ic] - sx_f[ia];  by_ = sy_f[ic] - sy_f[ia]
                if abs(float(ax * by_ - ay * bx_)) < 0.5:  # degenerate/sub-pixel
                    continue
                selected = mode == "terrain" and (
                    fi == selected_terrain
                    or (
                        selected_tile is not None
                        and fi < len(scene.terrain_meta)
                        and scene.terrain_meta[fi].get("tile_index") == selected_tile
                    )
                )
                fill = terrain_sel if selected else (int(cr[fi]), int(cg[fi]), int(cb[fi]))
                draw.polygon(
                    [(float(sx_f[ia]), float(sy_f[ia])),
                     (float(sx_f[ib]), float(sy_f[ib])),
                     (float(sx_f[ic]), float(sy_f[ic]))],
                    fill=fill, outline=terrain_edge)

        # ── Objects (also batched) ───────────────────────────────────────────
        mesh_object_ids = {obj_i for _verts, obj_i, _cy in scene.object_tris}
        if mode == "object" and scene.object_tris:
            _draw_object_meshes(draw, scene, cam, w, h, selected_obj, cfg)
        if mode == "object" and scene.objs_np is not None and scene.objs_np.shape[0]:
            Ov    = scene.objs_np.astype(np.float64)
            od    = Ov - eye
            odep  = od @ fwd
            ovis  = odep > NEAR
            osd   = odep.clip(NEAR, None)
            osx   = hW + (od @ right) / osd * f_px
            osy   = hH - (od @ up)    / osd * f_px
            # Sort far-to-near so selected marker is drawn on top if near
            valid = np.where(ovis)[0]
            valid = valid[np.argsort(-odep[valid])]
            for ki in valid:
                if int(ki) in mesh_object_ids:
                    continue
                px_, py_ = float(osx[ki]), float(osy[ki])
                color = obj_sel if ki == selected_obj else obj_col
                r = obj_radius + (2 if ki == selected_obj else 0)
                draw.ellipse((px_ - r, py_ - r, px_ + r, py_ + r),
                             fill=color, outline=(255, 255, 255))
                draw.text((px_ + r + 2, py_ - 6), str(int(ki)), fill=color)

    elif not HAS_NUMPY:
        # ── Pure-Python fallback (slow, same as before) ─────────────────────
        _render_scene_python(scene, cam, w, h, selected_obj, draw)

    return img


def _render_scene_python(scene, cam, w, h, selected_obj, draw):
    """Fallback renderer when numpy is unavailable."""
    ex, ey, ez = cam.eye()
    fx = cam.cx - ex; fy = cam.cy - ey; fz = cam.cz - ez
    fl = math.sqrt(fx*fx + fy*fy + fz*fz) or 1e-9
    fx /= fl; fy /= fl; fz /= fl
    rx = -fz; rz = fx; rl = math.sqrt(rx*rx + rz*rz) or 1e-9
    rx /= rl; rz /= rl
    ux = -fz*fy/rl; uy = fl; uz = fx*fy/rl  # approx up
    f_px = min(w,h)*0.5 / math.tan(math.radians(cam.fov*0.5))
    if scene.terrain_tris:
        all_cy = [c for _,c in scene.terrain_tris]
        cy_min = min(all_cy); cy_range = max(max(all_cy)-cy_min, 1.0)
    else:
        cy_min = cy_range = 1.0
    drawlist = []
    for verts, cy in scene.terrain_tris:
        projs = []
        ok = True
        for p in verts:
            dx,dy,dz = p[0]-ex, p[1]-ey, p[2]-ez
            depth = dx*fx+dy*fy+dz*fz
            if depth < 0.01: ok = False; break
            projs.append((w*0.5+(dx*rx+dz*rz)/depth*f_px, h*0.5-(dx*ux+dy*uy+dz*uz)/depth*f_px, depth))
        if not ok: continue
        depth = sum(p[2] for p in projs)/3
        t = (cy-cy_min)/cy_range; bl = 0.4+0.6*t
        fill = (int(_TC[0]*bl), int(_TC[1]*bl), int(_TC[2]*bl))
        poly = [(p[0],p[1]) for p in projs]
        drawlist.append((depth, "t", (poly, fill)))
    for i,pos in enumerate(scene.object_positions):
        dx,dy,dz = pos[0]-ex, pos[1]-ey, pos[2]-ez
        depth = dx*fx+dy*fy+dz*fz
        if depth < 0.01: continue
        sx = w*0.5+(dx*rx+dz*rz)/depth*f_px
        sy = h*0.5-(dx*ux+dy*uy+dz*uz)/depth*f_px
        drawlist.append((depth, "o", (sx, sy, OBJ_SEL_COLOR if i==selected_obj else OBJ_COLOR, i)))
    drawlist.sort(key=lambda x: -x[0])
    for _, kind, payload in drawlist:
        if kind == "t":
            draw.polygon(payload[0], fill=payload[1], outline=_TE)
        else:
            sx,sy,color,idx = payload
            r = OBJ_RADIUS
            draw.ellipse((sx-r,sy-r,sx+r,sy+r), fill=color, outline=(255,255,255))
            draw.text((sx+r+2,sy-6), str(idx), fill=color)


# ─────────────────────────────────────────────────────────────────────────────
# WorldCanvas — throttled 3D viewport
# ─────────────────────────────────────────────────────────────────────────────

class WorldCanvas(ttk.Frame):

    def __init__(self, master: tk.Widget, on_select: Any = None,
                 *, mode: str = "object", cfg: dict[str, Any] | None = None,
                 on_terrain_select: Any = None) -> None:
        super().__init__(master)
        self._on_select    = on_select
        self._on_terrain_select = on_terrain_select
        self._on_move      = None
        self.mode          = mode
        self.cfg           = cfg or DEFAULT_EDITOR_CONFIG
        self.scene         = SceneData()
        self.cam           = Camera()
        self.selected_obj: int | None = None
        self.selected_terrain: int | None = None
        self.selected_tile: int | None = None
        self._tk_img       = None
        self._drag_start: tuple[int, int] | None = None
        self._axis_handles: list[dict[str, Any]] = []
        self._axis_drag: dict[str, Any] | None = None
        self._terrain_handles: list[tuple[int, list[tuple[float, float]]]] = []
        self._redraw_pending = False    # throttle flag

        bg = self.cfg.get("colors", {}).get("background", "#111317")
        self._canvas = tk.Canvas(self, bg=bg, highlightthickness=0, cursor="crosshair")
        self._canvas.pack(fill="both", expand=True)

        self._canvas.bind("<Configure>",      self._on_resize)
        self._canvas.bind("<ButtonPress-1>",  self._on_lbdown)
        self._canvas.bind("<B1-Motion>",      self._on_lbdrag)
        self._canvas.bind("<ButtonRelease-1>",self._on_lbup)
        self._canvas.bind("<ButtonPress-2>",  self._on_mbdown)
        self._canvas.bind("<B2-Motion>",      self._on_mbdrag)
        self._canvas.bind("<ButtonPress-3>",  self._on_rbdown)
        self._canvas.bind("<B3-Motion>",      self._on_rbdrag)
        self._canvas.bind("<MouseWheel>",     self._on_wheel)
        self._canvas.bind("<Button-4>",       lambda e: self._on_wheel(e, -1))
        self._canvas.bind("<Button-5>",       lambda e: self._on_wheel(e, 1))

    # ── public API ───────────────────────────────────────────────────────────

    def load_scene(self, scene: SceneData, *, redraw: bool = True) -> None:
        self.scene = scene
        self.cam.reset_to_scene(scene)
        self.selected_obj = None
        self.selected_terrain = None
        if redraw:
            self.redraw()

    def select_object(self, idx: int | None) -> None:
        self.selected_obj = idx
        self.redraw()

    def set_object_move_callback(self, callback: Any) -> None:
        self._on_move = callback

    def select_terrain(self, idx: int | None) -> None:
        self.selected_terrain = idx
        self.redraw()

    def select_tile(self, tile_idx: int | None) -> None:
        self.selected_tile = tile_idx
        self.redraw()

    def set_config(self, cfg: dict[str, Any]) -> None:
        self.cfg = cfg
        self._canvas.configure(bg=cfg.get("colors", {}).get("background", "#111317"))
        self.redraw()

    def redraw(self) -> None:
        w = self._canvas.winfo_width()
        h = self._canvas.winfo_height()
        if w < 4 or h < 4:
            return
        self._canvas.delete("all")
        self._axis_handles = []
        self._terrain_handles = []
        if not HAS_PIL:
            self._canvas.create_text(w//2, h//2,
                text="Install Pillow for 3D view", fill="#ff8080", font=("Consolas", 12))
            self._draw_fallback_2d(w, h)
            self._draw_move_gizmo(w, h)
            return
        try:
            img = render_scene(
                self.scene, self.cam, w, h, self.selected_obj,
                selected_terrain=self.selected_terrain,
                selected_tile=self.selected_tile,
                mode=self.mode,
                cfg=self.cfg,
            )
            self._tk_img = ImageTk.PhotoImage(img)
            self._canvas.create_image(0, 0, image=self._tk_img, anchor="nw")
            self._cache_terrain_handles(w, h)
            if self.mode == "object":
                self._draw_move_gizmo(w, h)
        except Exception as exc:
            self._canvas.create_text(10, 10, text=f"Render error: {exc}",
                                     fill="red", anchor="nw")
            self._draw_fallback_2d(w, h)
            self._cache_terrain_handles(w, h)
            if self.mode == "object":
                self._draw_move_gizmo(w, h)

    # ── throttle helper ───────────────────────────────────────────────────────

    def _schedule_redraw(self) -> None:
        """Coalesce rapid camera-change events into a single redraw per tk tick."""
        if not self._redraw_pending:
            self._redraw_pending = True
            self.after(0, self._flush_redraw)

    def _flush_redraw(self) -> None:
        self._redraw_pending = False
        self.redraw()

    # ── 2D fallback ──────────────────────────────────────────────────────────

    def _draw_fallback_2d(self, w: int, h: int) -> None:
        objs = self.scene.object_positions
        if not objs:
            return
        xs = [p[0] for p in objs]; zs = [p[2] for p in objs]
        sx = max(max(xs)-min(xs), 1.0); sz = max(max(zs)-min(zs), 1.0)
        pad = 20; mx, mz = min(xs), min(zs)
        for i, p in enumerate(objs):
            px = pad + (p[0]-mx)/sx*(w-pad*2)
            py = pad + (p[2]-mz)/sz*(h-pad*2)
            col = "#ff5050" if i == self.selected_obj else "#f0b440"
            self._canvas.create_oval(px-4, py-4, px+4, py+4, fill=col, outline="")

    # ── mouse handlers (update camera, schedule single redraw) ───────────────

    def _project_point(self, p: list[float] | tuple[float, float, float],
                       w: int, h: int) -> tuple[float, float, float] | None:
        return _project_world_point(self.cam, p, w, h)

    def _cache_terrain_handles(self, w: int, h: int) -> None:
        if self.mode != "terrain":
            return
        for i, (verts, _cy) in enumerate(self.scene.terrain_tris):
            projs = [self._project_point(p, w, h) for p in verts]
            if any(p is None for p in projs):
                continue
            pts = [(p[0], p[1]) for p in projs if p is not None]
            self._terrain_handles.append((i, pts))

    @staticmethod
    def _point_in_tri(px: float, py: float, pts: list[tuple[float, float]]) -> bool:
        (x1, y1), (x2, y2), (x3, y3) = pts
        den = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)
        if abs(den) <= 1e-9:
            return False
        a = ((y2 - y3) * (px - x3) + (x3 - x2) * (py - y3)) / den
        b = ((y3 - y1) * (px - x3) + (x1 - x3) * (py - y3)) / den
        c = 1.0 - a - b
        return a >= 0 and b >= 0 and c >= 0

    def _hit_terrain(self, x: int, y: int) -> int | None:
        for idx, pts in reversed(self._terrain_handles):
            if self._point_in_tri(x, y, pts):
                return idx
        return None

    def _draw_move_gizmo(self, w: int, h: int) -> None:
        if self.selected_obj is None or self.selected_obj >= len(self.scene.object_positions):
            return
        pos = self.scene.object_positions[self.selected_obj]
        center = self._project_point(pos, w, h)
        if not center:
            return
        vp_cfg = self.cfg.get("viewport", {})
        axis_len = max(
            self.scene.span * float(vp_cfg.get("gizmo_axis_scale", 0.06)),
            float(vp_cfg.get("gizmo_min_length", 1.0)),
        )
        axes = [
            ("X", (1.0, 0.0, 0.0), self.cfg.get("colors", {}).get("gizmo_x", "#ff4d4d")),
            ("Y", (0.0, 1.0, 0.0), self.cfg.get("colors", {}).get("gizmo_y", "#55d66b")),
            ("Z", (0.0, 0.0, 1.0), self.cfg.get("colors", {}).get("gizmo_z", "#4d8dff")),
        ]
        cx, cy, _ = center
        self._canvas.create_oval(cx - 5, cy - 5, cx + 5, cy + 5,
                                 fill="#ffffff", outline="#111317")
        for axis, vec, color in axes:
            end = [pos[0] + vec[0] * axis_len,
                   pos[1] + vec[1] * axis_len,
                   pos[2] + vec[2] * axis_len]
            proj = self._project_point(end, w, h)
            if not proj:
                continue
            ex, ey, _ = proj
            self._canvas.create_line(cx, cy, ex, ey, fill="#101010", width=6, arrow=tk.LAST)
            self._canvas.create_line(cx, cy, ex, ey, fill=color, width=3, arrow=tk.LAST)
            self._canvas.create_text(ex, ey, text=axis, fill=color, font=("Consolas", 10, "bold"))
            self._axis_handles.append({
                "axis": axis, "vec": vec, "start": (cx, cy), "end": (ex, ey),
                "origin": tuple(pos), "axis_len": axis_len,
            })

    @staticmethod
    def _dist_to_segment(px: float, py: float,
                         ax: float, ay: float, bx: float, by: float) -> float:
        vx, vy = bx - ax, by - ay
        denom = vx * vx + vy * vy
        if denom <= 1e-9:
            return math.hypot(px - ax, py - ay)
        t = max(0.0, min(1.0, ((px - ax) * vx + (py - ay) * vy) / denom))
        qx, qy = ax + t * vx, ay + t * vy
        return math.hypot(px - qx, py - qy)

    def _hit_axis(self, x: int, y: int) -> dict[str, Any] | None:
        best = None
        best_dist = 12.0
        for handle in self._axis_handles:
            ax, ay = handle["start"]
            bx, by = handle["end"]
            dist = self._dist_to_segment(x, y, ax, ay, bx, by)
            if dist < best_dist:
                best = handle
                best_dist = dist
        return best

    @staticmethod
    def _axis_drag_position(handle: dict[str, Any], x: int, y: int,
                            start_x: int, start_y: int) -> list[float]:
        sx, sy = handle["start"]
        ex, ey = handle["end"]
        vx, vy = ex - sx, ey - sy
        denom = max(vx * vx + vy * vy, 1e-9)
        pixels = ((x - start_x) * vx + (y - start_y) * vy) / denom
        delta = pixels * handle["axis_len"]
        origin = handle["origin"]
        vec = handle["vec"]
        return [
            origin[0] + vec[0] * delta,
            origin[1] + vec[1] * delta,
            origin[2] + vec[2] * delta,
        ]

    def _on_resize(self, _e: tk.Event) -> None: self._schedule_redraw()

    def _on_lbdown(self, e: tk.Event) -> None:
        if self.mode == "terrain":
            tri_idx = self._hit_terrain(e.x, e.y)
            if tri_idx is not None:
                self.selected_terrain = tri_idx
                if self._on_terrain_select:
                    self._on_terrain_select(tri_idx)
                self.redraw()
                return
        hit = self._hit_axis(e.x, e.y)
        if hit and self.selected_obj is not None and self._on_move:
            self._axis_drag = {"handle": hit, "start": (e.x, e.y)}
            self._drag_start = None
            return
        self._drag_start = (e.x, e.y)

    def _on_lbdrag(self, e: tk.Event) -> None:
        if self._axis_drag and self.selected_obj is not None and self._on_move:
            sx, sy = self._axis_drag["start"]
            pos = self._axis_drag_position(self._axis_drag["handle"], e.x, e.y, sx, sy)
            self._on_move(self.selected_obj, pos, False)
            self._schedule_redraw()
            return
        if not self._drag_start: return
        dx = e.x - self._drag_start[0]; dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.orbit(dx * 0.008, -dy * 0.008)
        self._schedule_redraw()

    def _on_lbup(self, e: tk.Event) -> None:
        if self._axis_drag and self.selected_obj is not None and self._on_move:
            sx, sy = self._axis_drag["start"]
            pos = self._axis_drag_position(self._axis_drag["handle"], e.x, e.y, sx, sy)
            self._on_move(self.selected_obj, pos, True)
            self._axis_drag = None
            return
        self._drag_start = None

    def _on_mbdown(self, e: tk.Event) -> None:
        self._drag_start = (e.x, e.y)

    def _on_mbdrag(self, e: tk.Event) -> None:
        if not self._drag_start: return
        dx = e.x - self._drag_start[0]; dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.pan(dx, dy)
        self._schedule_redraw()

    def _on_rbdown(self, e: tk.Event) -> None:
        self._drag_start = (e.x, e.y)

    def _on_rbdrag(self, e: tk.Event) -> None:
        if not self._drag_start: return
        dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.zoom(1.0 + dy * 0.01)
        self._schedule_redraw()

    def _on_wheel(self, e: tk.Event, direction: int = 0) -> None:
        delta = direction or (1 if e.delta < 0 else -1)
        self.cam.zoom(1.12 if delta > 0 else 0.88)
        self._schedule_redraw()


# ─────────────────────────────────────────────────────────────────────────────
# Object edit dialog — with script-offset type picker
# ─────────────────────────────────────────────────────────────────────────────

class TerrainEditDialog(tk.Toplevel):
    def __init__(self, parent: tk.Widget, tri_idx: int, verts: list[list[float]],
                 on_save: Any = None) -> None:
        super().__init__(parent)
        self.title(f"Edit Terrain Triangle #{tri_idx}")
        self.resizable(False, False)
        self.grab_set()
        self._tri_idx = tri_idx
        self._on_save = on_save
        self._vars: list[list[tk.StringVar]] = []

        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)
        ttk.Label(frm, text="Vertex").grid(row=0, column=0, sticky="w")
        for c, name in enumerate(("X", "Y", "Z"), start=1):
            ttk.Label(frm, text=name).grid(row=0, column=c, padx=4)
        for r, v in enumerate(verts, start=1):
            ttk.Label(frm, text=str(r - 1)).grid(row=r, column=0, sticky="e", padx=(0, 8))
            row_vars = []
            for c in range(3):
                var = tk.StringVar(value=f"{v[c]:.6f}")
                row_vars.append(var)
                ttk.Entry(frm, textvariable=var, width=14).grid(row=r, column=c + 1, padx=3, pady=3)
            self._vars.append(row_vars)

        btns = ttk.Frame(self, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Apply", command=self._save).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel", command=self.destroy).pack(side="right")

    def _save(self) -> None:
        verts: list[list[float]] = []
        try:
            for row in self._vars:
                verts.append([float(v.get()) for v in row])
        except ValueError:
            messagebox.showerror("Parse error", "All vertex values must be numbers.", parent=self)
            return
        if self._on_save:
            self._on_save(self._tri_idx, verts)
        self.destroy()

# Main application

class WadEditorApp(tk.Tk):

    def __init__(self) -> None:
        super().__init__()
        self.title("ENG WAD Editor")
        self.geometry("1400x860")
        self.minsize(1050, 680)

        self.work: WorkFolder | None = None
        self._wad_path:  Path | None = None
        self._wad_data:  bytes = b""
        self._mapx:      Any   = None
        self._trak:      Any   = None
        self._map_flags: tuple[bool, bool] = (False, True)   # (opt20, final_dw)
        self._scene      = SceneData()
        self._objects:   list  = []
        self._selected_obj: int | None = None
        self._selected_terrain: int | None = None
        self._stpc_names: dict[int, str] = {}
        self._type_registry: list[tuple[int, str]] = []
        self._editor_config = load_editor_config()

        self._build_ui()

    # ── UI construction ──────────────────────────────────────────────────────

    def _build_ui(self) -> None:
        menubar = tk.Menu(self)
        options = tk.Menu(menubar, tearoff=False)
        options.add_command(label="Editor Settings...", command=self._open_settings_dialog)
        options.add_command(label="Reload Settings", command=self._reload_editor_settings)
        menubar.add_cascade(label="Options", menu=options)
        self.config(menu=menubar)

        tb = ttk.Frame(self, padding=(8, 6))
        tb.pack(fill="x")
        ttk.Button(tb, text="📂 Open WAD",  command=self._open_wad_dialog).pack(side="left")
        ttk.Button(tb, text="💾 Save WAD",  command=self._save_wad_dialog).pack(side="left", padx=(6,0))
        ttk.Button(tb, text="Save As…",     command=self._save_wad_as_dialog).pack(side="left", padx=(6,0))
        ttk.Separator(tb, orient="vertical").pack(side="left", fill="y", padx=8)
        ttk.Button(tb, text="Reload Scene", command=self._reload_scene).pack(side="left")
        self._status = tk.StringVar(value="Open a WAD file to begin.")
        ttk.Label(tb, textvariable=self._status, anchor="w").pack(
            side="left", padx=14, fill="x", expand=True)

        self._nb = ttk.Notebook(self)
        self._nb.pack(fill="both", expand=True, padx=8, pady=(0, 8))

        self._tab_overview = ttk.Frame(self._nb)
        self._nb.add(self._tab_overview, text="Overview")
        self._build_overview_tab()

        self._tab_world = ttk.Frame(self._nb)
        self._nb.add(self._tab_world, text="Object Editor")
        self._build_world_tab()

        self._tab_terrain = ttk.Frame(self._nb)
        self._nb.add(self._tab_terrain, text="World Editor")
        self._build_terrain_tab()

        self._tab_log = ttk.Frame(self._nb)
        self._nb.add(self._tab_log, text="Log")
        self._log = tk.Text(self._tab_log, wrap="word", font=("Consolas", 9))
        _sb = ttk.Scrollbar(self._tab_log, command=self._log.yview)
        self._log.configure(yscrollcommand=_sb.set)
        _sb.pack(side="right", fill="y")
        self._log.pack(fill="both", expand=True, padx=4, pady=4)

    def _build_overview_tab(self) -> None:
        pane = ttk.PanedWindow(self._tab_overview, orient="horizontal")
        pane.pack(fill="both", expand=True, padx=8, pady=8)

        left = ttk.Frame(pane); pane.add(left, weight=2)
        self._info_text = tk.Text(left, wrap="word", height=8, font=("Consolas", 9))
        self._info_text.pack(fill="both", expand=True)
        self._info_text.insert("end", "No WAD loaded.\n")
        self._info_text.config(state="disabled")

        right = ttk.Frame(pane); pane.add(right, weight=3)
        ttk.Label(right, text="Chunks", font=("", 10, "bold")).pack(anchor="w")
        cols = ("tag", "size", "elements", "work_file")
        self._chunk_tree = ttk.Treeview(right, columns=cols, show="headings")
        widths = {"tag": 70, "size": 100, "elements": 120, "work_file": 260}
        for c in cols:
            self._chunk_tree.heading(c, text=c)
            self._chunk_tree.column(c, width=widths[c], anchor="w")
        vsb = ttk.Scrollbar(right, orient="vertical", command=self._chunk_tree.yview)
        self._chunk_tree.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        self._chunk_tree.pack(fill="both", expand=True)
        btns = ttk.Frame(right); btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Open chunk folder", command=self._open_chunk_folder).pack(side="left")
        ttk.Button(btns, text="Reload chunk file", command=self._reload_selected_chunk).pack(
            side="left", padx=(6, 0))

    def _build_world_tab(self) -> None:
        pane = ttk.PanedWindow(self._tab_world, orient="horizontal")
        pane.pack(fill="both", expand=True, padx=8, pady=8)

        vp_frame = ttk.LabelFrame(pane, text="3D View  (LMB orbit · MMB pan · RMB/wheel zoom)")
        pane.add(vp_frame, weight=3)
        self._world_canvas = WorldCanvas(vp_frame, mode="object", cfg=self._editor_config)
        self._world_canvas.set_object_move_callback(self._on_canvas_object_moved)
        self._world_canvas.pack(fill="both", expand=True)

        right = ttk.Frame(pane); pane.add(right, weight=1)
        ttk.Label(right, text="MAP Objects", font=("", 10, "bold")).pack(anchor="w")

        obj_cols = ("idx", "type_hex", "name", "x", "y", "z", "rot_y")
        self._obj_tree = ttk.Treeview(right, columns=obj_cols, show="headings", height=22)
        hdrs = {"idx": "#", "type_hex": "Script offset", "name": "Name",
                "x": "X", "y": "Y", "z": "Z", "rot_y": "Rot Y"}
        ws   = {"idx": 32, "type_hex": 100, "name": 130, "x": 68, "y": 68, "z": 68, "rot_y": 48}
        for c in obj_cols:
            self._obj_tree.heading(c, text=hdrs[c])
            anchor = "w" if c in ("type_hex", "name") else "e"
            self._obj_tree.column(c, width=ws[c], anchor=anchor)
        self._obj_tree.bind("<<TreeviewSelect>>", self._on_obj_tree_select)
        vsb2 = ttk.Scrollbar(right, orient="vertical", command=self._obj_tree.yview)
        self._obj_tree.configure(yscrollcommand=vsb2.set)
        vsb2.pack(side="right", fill="y")
        self._obj_tree.pack(fill="both", expand=True)

        btns = ttk.Frame(right); btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Edit",   command=self._edit_selected_obj).pack(side="left")
        ttk.Button(btns, text="Clone",  command=self._clone_selected_obj).pack(side="left", padx=(4,0))
        ttk.Button(btns, text="Delete", command=self._delete_selected_obj).pack(side="left", padx=(4,0))
        ttk.Button(btns, text="Add New",command=self._add_new_obj_dialog).pack(side="left", padx=(4,0))
        ttk.Button(btns, text="Focus",  command=self._focus_selected_obj).pack(side="left", padx=(4,0))
        ttk.Button(btns, text="Build/Load Meshes",
                   command=self._start_object_mesh_export).pack(side="left", padx=(4,0))

        ttk.Label(right,
            text="Edit/Clone patches MAP .bin directly.\nSave WAD to write back.",
            foreground="#888", justify="left").pack(anchor="w", pady=(6, 0))

    # ── Open / Save ──────────────────────────────────────────────────────────

    def _build_terrain_tab(self) -> None:
        pane = ttk.PanedWindow(self._tab_terrain, orient="horizontal")
        pane.pack(fill="both", expand=True, padx=8, pady=8)

        vp_frame = ttk.LabelFrame(pane, text="Terrain View  (select terrain triangles; objects locked)")
        pane.add(vp_frame, weight=3)
        self._terrain_canvas = WorldCanvas(
            vp_frame, mode="terrain", cfg=self._editor_config,
            on_terrain_select=self._on_terrain_canvas_select,
        )
        self._terrain_canvas.pack(fill="both", expand=True)

        right = ttk.Frame(pane); pane.add(right, weight=1)
        ttk.Label(right, text="Terrain Meshes", font=("", 10, "bold")).pack(anchor="w")
        mode_row = ttk.Frame(right)
        mode_row.pack(fill="x", pady=(0, 4))
        ttk.Label(mode_row, text="Mode").pack(side="left")
        self._terrain_mode_var = tk.StringVar(value="Chunks")
        self._terrain_mode_combo = ttk.Combobox(
            mode_row, textvariable=self._terrain_mode_var,
            values=("Chunks", "Triangles"), state="readonly", width=12,
        )
        self._terrain_mode_combo.pack(side="left", padx=(6, 0))
        self._terrain_mode_combo.bind("<<ComboboxSelected>>", self._on_terrain_mode_changed)
        cols = ("idx", "tile", "trak", "cy")
        self._terrain_tree = ttk.Treeview(right, columns=cols, show="headings", height=22)
        hdrs = {"idx": "#", "tile": "MAP tile", "trak": "TRAK", "cy": "Center Y"}
        widths = {"idx": 52, "tile": 72, "trak": 62, "cy": 86}
        for c in cols:
            self._terrain_tree.heading(c, text=hdrs[c])
            self._terrain_tree.column(c, width=widths[c], anchor="e")
        self._terrain_tree.bind("<<TreeviewSelect>>", self._on_terrain_tree_select)
        vsb = ttk.Scrollbar(right, orient="vertical", command=self._terrain_tree.yview)
        self._terrain_tree.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        self._terrain_tree.pack(fill="both", expand=True)

        btns = ttk.Frame(right); btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Edit Vertices", command=self._edit_selected_terrain).pack(side="left")
        ttk.Button(btns, text="Move Chunk", command=self._move_selected_chunk).pack(side="left", padx=(4, 0))
        ttk.Button(btns, text="Focus", command=self._focus_selected_terrain).pack(side="left", padx=(4, 0))
        ttk.Label(right,
            text="Terrain edits are viewport/in-memory only until TRAK reserialization is implemented.",
            foreground="#888", justify="left", wraplength=280).pack(anchor="w", pady=(6, 0))

    def _reload_editor_settings(self) -> None:
        self._editor_config = load_editor_config()
        for canvas_name in ("_world_canvas", "_terrain_canvas"):
            canvas = getattr(self, canvas_name, None)
            if canvas:
                canvas.set_config(self._editor_config)
        self._log_line(f"Reloaded editor settings from {CONFIG_PATH}")

    def _open_settings_dialog(self) -> None:
        dlg = tk.Toplevel(self)
        dlg.title("Editor Settings")
        dlg.resizable(False, True)
        dlg.grab_set()
        frm = ttk.Frame(dlg, padding=12)
        frm.pack(fill="both", expand=True)
        vars_by_path: dict[tuple[str, str], tk.StringVar] = {}

        row = 0
        ttk.Label(frm, text=f"Config: {CONFIG_PATH}", foreground="#666").grid(
            row=row, column=0, columnspan=2, sticky="w", pady=(0, 8))
        row += 1
        ttk.Label(frm, text="Colors", font=("", 10, "bold")).grid(row=row, column=0, sticky="w")
        row += 1
        for key, value in self._editor_config.get("colors", {}).items():
            ttk.Label(frm, text=key).grid(row=row, column=0, sticky="w", padx=(0, 8), pady=2)
            var = tk.StringVar(value=str(value))
            vars_by_path[("colors", key)] = var
            ttk.Entry(frm, textvariable=var, width=18).grid(row=row, column=1, sticky="ew")
            row += 1

        ttk.Label(frm, text="Viewport", font=("", 10, "bold")).grid(row=row, column=0, sticky="w", pady=(8, 0))
        row += 1
        for key, value in self._editor_config.get("viewport", {}).items():
            ttk.Label(frm, text=key).grid(row=row, column=0, sticky="w", padx=(0, 8), pady=2)
            var = tk.StringVar(value=str(value))
            vars_by_path[("viewport", key)] = var
            ttk.Entry(frm, textvariable=var, width=18).grid(row=row, column=1, sticky="ew")
            row += 1

        def apply_settings() -> None:
            for (section, key), var in vars_by_path.items():
                raw = var.get().strip()
                old = self._editor_config[section][key]
                if isinstance(old, int):
                    try:
                        self._editor_config[section][key] = int(raw)
                    except ValueError:
                        messagebox.showerror("Settings", f"{key} must be an integer.", parent=dlg); return
                elif isinstance(old, float):
                    try:
                        self._editor_config[section][key] = float(raw)
                    except ValueError:
                        messagebox.showerror("Settings", f"{key} must be a number.", parent=dlg); return
                else:
                    self._editor_config[section][key] = raw
            save_editor_config(self._editor_config)
            self._reload_editor_settings()
            dlg.destroy()

        btns = ttk.Frame(dlg, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Save", command=apply_settings).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel", command=dlg.destroy).pack(side="right")

    def _open_wad_dialog(self) -> None:
        path = filedialog.askopenfilename(
            title="Open WAD",
            filetypes=[("WAD files", "*.wad *.WAD"), ("All files", "*.*")])
        if path:
            self._open_wad(Path(path))

    def _open_wad(self, path: Path) -> None:
        self._log_line(f"Opening {path} …")
        try:
            data, chunks, _ = read_wad(path)
        except Exception as exc:
            messagebox.showerror("Open failed", str(exc)); return

        self._wad_path = path
        self._wad_data = data
        work = WorkFolder(path)
        work.extract(data, chunks)
        self.work = work
        self._log_line(f"Extracted {len(chunks)} chunks → {work.work_dir}")
        self._status.set(f"{path.name}  ({len(data):,} B · {len(chunks)} chunks)  "
                         f"— {work.work_dir.name}")
        self.title(f"ENG WAD Editor — {path.name}")
        self._refresh_overview()
        self._load_game_data()
        self._reload_scene()

    def _save_wad_dialog(self) -> None:
        if not self.work or not self._wad_path:
            messagebox.showinfo("No WAD open", "Open a WAD file first."); return
        if messagebox.askyesno("Overwrite?", f"Overwrite original?\n{self._wad_path}"):
            self._do_save(self._wad_path)

    def _save_wad_as_dialog(self) -> None:
        if not self.work:
            messagebox.showinfo("No WAD open", "Open a WAD file first."); return
        path = filedialog.asksaveasfilename(
            title="Save WAD as…", defaultextension=".wad",
            filetypes=[("WAD files", "*.wad"), ("All files", "*.*")],
            initialfile=self._wad_path.name if self._wad_path else "output.wad")
        if path:
            self._do_save(Path(path))

    def _do_save(self, out_path: Path) -> None:
        try:
            self.work.pack_wad(out_path)
            self._log_line(f"Saved WAD → {out_path}")
            messagebox.showinfo("Saved", str(out_path))
        except Exception as exc:
            messagebox.showerror("Save failed", str(exc))

    # ── Overview ─────────────────────────────────────────────────────────────

    def _refresh_overview(self) -> None:
        if not self.work: return
        self._info_text.config(state="normal")
        self._info_text.delete("1.0", "end")
        self._info_text.insert("end", "\n".join([
            f"Source     : {self._wad_path}",
            f"File size  : {len(self._wad_data):,} bytes",
            f"Chunks     : {len(self.work.entries)}",
            f"Work folder: {self.work.work_dir}",
            "", "Tips:",
            "  • Double-click a chunk row to open the .bin",
            "  • Edit externally → Reload chunk file → Save WAD",
        ]))
        self._info_text.config(state="disabled")
        self._chunk_tree.delete(*self._chunk_tree.get_children())
        for info_dict in self.work.chunk_info():
            tag  = info_dict["tag"]
            size = info_dict["current_size"]
            p    = self.work.work_dir / info_dict["bin_file"]
            data = p.read_bytes() if p.exists() else b""
            self._chunk_tree.insert("", "end", iid=str(info_dict["index"]),
                values=(tag, f"{size:,} B", _quick_element_count(tag, data), info_dict["bin_file"]))
        self._chunk_tree.bind("<Double-1>", self._on_chunk_dclick)

    def _open_chunk_folder(self) -> None:
        if self.work:
            import os; os.startfile(str(self.work.work_dir))  # type: ignore[attr-defined]

    def _reload_selected_chunk(self) -> None:
        sel = self._chunk_tree.selection()
        if not sel or not self.work: return
        entry = self.work.entries[int(sel[0])]
        self._log_line(f"Reloaded chunk {entry['tag']}")
        self._refresh_overview()
        if entry["tag"] in ("MAP ", "TRAK"):
            self._load_game_data(); self._reload_scene()

    def _on_chunk_dclick(self, _e: tk.Event) -> None:
        sel = self._chunk_tree.selection()
        if not sel or not self.work: return
        entry = self.work.entries[int(sel[0])]
        import os; os.startfile(str(self.work.work_dir / entry["bin_file"]))  # type: ignore[attr-defined]

    # ── Game data ────────────────────────────────────────────────────────────

    def _load_game_data(self) -> None:
        if not self.work: return
        self._mapx = self._trak = None
        if not (HAS_TRAK and HAS_MAP): return

        trak_data = self.work.get_chunk_data("TRAK")
        if not trak_data:
            self._log_line("No TRAK chunk."); return
        try:
            self._trak = parse_trak_chunk(trak_data)
            self._log_line(f"TRAK: {self._trak.record_count} records")
        except Exception as exc:
            self._log_line(f"TRAK error: {exc}"); return

        map_data = self.work.get_chunk_data("MAP ")
        if not map_data:
            self._log_line("No MAP chunk."); return

        for opt20, final_dw in [(True,True),(True,False),(False,True),(False,False)]:
            try:
                self._mapx = parse_map_full_exe(
                    map_data, self._trak,
                    assume_optional20=opt20, assume_final_dword=final_dw)
                self._map_flags = (opt20, final_dw)
                self._log_line(
                    f"MAP: {self._mapx.tile_count} tiles, "
                    f"{len(self._mapx.objects)} objects  "
                    f"(opt20={opt20}, final_dw={final_dw})")
                break
            except Exception:
                continue

        if self._mapx is None:
            self._log_line("MAP parse failed."); return

        self._objects = list(self._mapx.objects)

        # ── STPC name lookup ──────────────────────────────────────────────
        self._stpc_names = {}
        stpc_data = self.work.get_chunk_data("STPC")
        if stpc_data:
            try:
                so_list = [o.script_offset for o in self._objects]
                self._stpc_names = build_stpc_name_map(stpc_data, so_list)
                named = len(self._stpc_names)
                total = len(set(so_list))
                self._log_line(f"STPC names: {named}/{total} object types identified")
            except Exception as exc:
                self._log_line(f"STPC name scan warning: {exc}")

        self._type_registry = build_type_registry(self._objects, self._stpc_names)
        self._log_line(f"Found {len(self._type_registry)} unique object types")
        for off, lbl in self._type_registry:
            self._log_line(f"  {lbl}")
        for w in (self._mapx.warnings or [])[:5]:
            self._log_line(f"  MAP warning: {w}")

    # ── Scene ─────────────────────────────────────────────────────────────────

    def _reload_scene(self) -> None:
        if self._mapx and self._trak:
            self._scene.build(self._mapx, self._trak)
            self._load_object_meshes_for_scene(redraw=False)
            self._world_canvas.load_scene(self._scene, redraw=False)
            self._terrain_canvas.load_scene(self._scene, redraw=False)
        self._populate_obj_tree()
        self._populate_terrain_tree()
        self._log_line(
            f"Editor lists: {len(self._objects)} objects, "
            f"{len(self._scene.terrain_tris)} terrain triangles"
        )
        self.after_idle(self._world_canvas.redraw)
        self.after_idle(self._terrain_canvas.redraw)

    def _load_object_meshes_for_scene(self, *, redraw: bool = True) -> None:
        if not (self._mapx and self._trak):
            return
        obj_paths = self._find_world_assets([
            "objects_primary.obj",
            "objects_all_candidates.obj",
        ])
        if not obj_paths:
            self._scene.object_tris = []
            self._log_line("Object mesh viewport: objects_primary.obj not found, using markers")
            if getattr(self, "_auto_mesh_export_for", None) != self._wad_path:
                self._auto_mesh_export_for = self._wad_path
                self._start_object_mesh_export()
            if redraw:
                self._world_canvas.redraw()
            return
        try:
            seen_objects: set[int] = set()
            tris: list[tuple[list, int, float]] = []
            used: list[str] = []
            for obj_path in obj_paths:
                before = len(tris)
                tris.extend(parse_placed_object_obj(obj_path, existing_objects=seen_objects))
                added = len(tris) - before
                if added:
                    used.append(f"{obj_path.name}:{added}")
            self._scene.object_tris = tris
            cloned = self._fill_missing_object_meshes_by_type(seen_objects)
            self._log_line(
                f"Object mesh viewport: loaded {len(self._scene.object_tris)} triangles "
                f"for {len(seen_objects)} objects from {', '.join(used) if used else 'no usable OBJ groups'}"
            )
            if cloned:
                self._log_line(f"Object mesh viewport: cloned same-type mesh fallback for {cloned} objects")
            missing = max(len(self._objects) - len(seen_objects), 0)
            if missing:
                self._log_line(f"Object mesh viewport: {missing} objects still have no decoded mesh; using markers for them")
        except Exception as exc:
            self._scene.object_tris = []
            self._log_line(f"Object mesh viewport disabled: {exc}")
        if redraw:
            self._world_canvas.redraw()

    def _fill_missing_object_meshes_by_type(self, seen_objects: set[int]) -> int:
        if not self._scene.object_tris or not self._objects:
            return 0
        obj_by_index = {o.index: o for o in self._objects}
        tris_by_obj: dict[int, list[tuple[list, int, float]]] = {}
        for tri in self._scene.object_tris:
            tris_by_obj.setdefault(tri[1], []).append(tri)

        source_by_type: dict[int, int] = {}
        for obj_i in sorted(seen_objects):
            obj = obj_by_index.get(obj_i)
            if obj is not None and obj.script_offset not in source_by_type:
                source_by_type[obj.script_offset] = obj_i

        cloned = 0
        additions: list[tuple[list, int, float]] = []
        for obj in self._objects:
            if obj.index in seen_objects:
                continue
            src_i = source_by_type.get(obj.script_offset)
            if src_i is None or src_i not in tris_by_obj:
                continue
            src = obj_by_index.get(src_i)
            if src is None:
                continue
            dx = (obj.pos_x_fixed12 - src.pos_x_fixed12) / 4096.0
            dy = (obj.pos_y_fixed12 - src.pos_y_fixed12) / 4096.0
            dz = (obj.pos_z_fixed12 - src.pos_z_fixed12) / 4096.0
            for verts, _old_i, cy in tris_by_obj[src_i]:
                additions.append((
                    [[v[0] + dx, v[1] + dy, v[2] + dz] for v in verts],
                    obj.index,
                    cy + dy,
                ))
            seen_objects.add(obj.index)
            cloned += 1
        self._scene.object_tris.extend(additions)
        return cloned

    def _find_world_asset(self, name: str) -> Path | None:
        assets = self._find_world_assets([name])
        return assets[0] if assets else None

    def _find_world_assets(self, names: list[str]) -> list[Path]:
        if not self._wad_path:
            return []
        bases = [
            self._wad_path.parent / "extracted" / self._wad_path.stem / "world",
            self._wad_path.parent / self._wad_path.stem / "world",
            Path(__file__).parent / "extracted" / self._wad_path.stem / "world",
            Path.cwd() / "WAD" / "extracted" / self._wad_path.stem / "world",
            Path.cwd() / "extracted" / self._wad_path.stem / "world",
        ]
        if self.work:
            bases.append(self.work.work_dir / "world")
        found: list[Path] = []
        seen: set[Path] = set()
        for base in bases:
            for name in names:
                p = base / name
                if p.exists() and p not in seen:
                    found.append(p)
                    seen.add(p)
        return found

    def _start_object_mesh_export(self) -> None:
        if not self._wad_path:
            messagebox.showinfo("No WAD", "Open a WAD first."); return
        if getattr(self, "_mesh_export_running", False):
            self._log_line("Object mesh export already running.")
            return
        import queue
        import os
        import subprocess
        import threading

        self._mesh_export_running = True
        self._mesh_export_queue = queue.Queue()
        script_path = Path(__file__).with_name("wad_extractor.py").resolve()
        out_dir = script_path.parent / "extracted"
        cmd = [
            sys.executable,
            str(script_path),
            str(self._wad_path),
            "--out-dir", str(out_dir),
            "--no-sounds",
            "--no-srpc",
            "--no-lights",
            "--no-raw",
            "--no-texture-fields",
            "--quiet",
        ]
        self._log_line(f"Building object meshes with exporter -> {out_dir}")

        def worker() -> None:
            try:
                env = os.environ.copy()
                env["PYTHONIOENCODING"] = "utf-8"
                env["PYTHONUTF8"] = "1"
                proc = subprocess.run(
                    cmd,
                    cwd=str(script_path.parent),
                    capture_output=True,
                    text=True,
                    encoding="utf-8",
                    errors="replace",
                    env=env,
                    timeout=600,
                )
                self._mesh_export_queue.put((proc.returncode, proc.stdout, proc.stderr))
            except Exception as exc:
                self._mesh_export_queue.put((-1, "", str(exc)))

        threading.Thread(target=worker, daemon=True).start()
        self.after(250, self._poll_object_mesh_export)

    def _poll_object_mesh_export(self) -> None:
        q = getattr(self, "_mesh_export_queue", None)
        if q is None:
            self._mesh_export_running = False
            return
        try:
            code, out, err = q.get_nowait()
        except Exception:
            self.after(250, self._poll_object_mesh_export)
            return
        self._mesh_export_running = False
        if code != 0:
            tail = (err or out or "unknown exporter error").strip().splitlines()[-5:]
            self._log_line("Object mesh export failed:")
            for line in tail:
                self._log_line(f"  {line}")
            return
        self._log_line("Object mesh export finished.")
        self._load_object_meshes_for_scene(redraw=True)

    def _populate_obj_tree(self) -> None:
        self._obj_tree.delete(*self._obj_tree.get_children())
        objects = self._objects or (list(self._mapx.objects) if self._mapx is not None else [])
        inserted = 0
        for row_i, obj in enumerate(objects):
            try:
                name = self._stpc_names.get(obj.script_offset, "")
                self._obj_tree.insert("", "end", iid=f"obj_{row_i}", values=(
                    obj.index,
                    f"0x{obj.script_offset:08X}",
                    name,
                    f"{obj.pos_x_fixed12/4096.0:.2f}",
                    f"{obj.pos_y_fixed12/4096.0:.2f}",
                    f"{obj.pos_z_fixed12/4096.0:.2f}",
                    obj.rot_y_units,
                ))
                inserted += 1
            except Exception as exc:
                self._log_line(f"Object list insert failed at row {row_i}: {exc}")
                break
        self._log_line(f"Object list rows inserted: {inserted}")

    def _populate_terrain_tree(self) -> None:
        self._terrain_tree.delete(*self._terrain_tree.get_children())
        if getattr(self, "_terrain_mode_var", None) and self._terrain_mode_var.get() == "Chunks":
            self._populate_chunk_tree()
            return
        self._terrain_populate_generation = getattr(self, "_terrain_populate_generation", 0) + 1
        self._terrain_populate_index = 0
        self._populate_terrain_tree_batch(self._terrain_populate_generation)

    def _populate_chunk_tree(self) -> None:
        chunks: dict[int, dict[str, Any]] = {}
        for i, (_verts, cy) in enumerate(self._scene.terrain_tris):
            meta = self._scene.terrain_meta[i] if i < len(self._scene.terrain_meta) else {}
            tile_i = int(meta.get("tile_index", -1))
            if tile_i < 0:
                continue
            info = chunks.setdefault(tile_i, {
                "count": 0, "trak": meta.get("trak_index", ""), "cy_sum": 0.0,
            })
            info["count"] += 1
            info["cy_sum"] += cy
        for tile_i in sorted(chunks):
            info = chunks[tile_i]
            avg_y = info["cy_sum"] / max(info["count"], 1)
            self._terrain_tree.insert("", "end", iid=f"tile_{tile_i}", values=(
                tile_i,
                tile_i,
                info["trak"],
                f"{avg_y:.3f}",
            ))
        self._log_line(f"Chunk list rows inserted: {len(chunks)}")

    def _populate_terrain_tree_batch(self, generation: int | None = None) -> None:
        if generation is not None and generation != getattr(self, "_terrain_populate_generation", 0):
            return
        start = getattr(self, "_terrain_populate_index", 0)
        end = min(start + 1000, len(self._scene.terrain_tris))
        for i in range(start, end):
            _verts, cy = self._scene.terrain_tris[i]
            meta = self._scene.terrain_meta[i] if i < len(self._scene.terrain_meta) else {}
            try:
                self._terrain_tree.insert("", "end", iid=f"tri_{i}", values=(
                    i,
                    meta.get("tile_index", ""),
                    meta.get("trak_index", ""),
                    f"{cy:.3f}",
                ))
            except Exception as exc:
                self._log_line(f"Terrain list insert failed at row {i}: {exc}")
                return
        self._terrain_populate_index = end
        if end < len(self._scene.terrain_tris):
            self.after(1, lambda gen=generation: self._populate_terrain_tree_batch(gen))
        elif start != end:
            self._log_line(f"Terrain list rows inserted: {end}")

    def _on_obj_tree_select(self, _e: tk.Event) -> None:
        sel = self._obj_tree.selection()
        if not sel: return
        vals = self._obj_tree.item(sel[0], "values")
        if not vals:
            return
        obj_idx_field = int(vals[0])
        self._selected_obj = obj_idx_field
        # The canvas renderer indexes objects by *position* in scene.objs_np,
        # not by obj.index.  Resolve the position so highlights are correct
        # even when indices are non-contiguous.
        pos_idx = next((i for i, o in enumerate(self._objects)
                        if o.index == obj_idx_field), None)
        self._world_canvas.select_object(pos_idx)

    # ── Object actions ────────────────────────────────────────────────────────

    def _on_terrain_canvas_select(self, tri_idx: int) -> None:
        self._selected_terrain = tri_idx
        tile_idx = None
        if tri_idx < len(self._scene.terrain_meta):
            tile_idx = self._scene.terrain_meta[tri_idx].get("tile_index")
        self._selected_tile = tile_idx
        self._terrain_canvas.select_tile(tile_idx)
        if getattr(self, "_terrain_mode_var", None) and self._terrain_mode_var.get() == "Chunks" and tile_idx is not None:
            iid = f"tile_{tile_idx}"
            if self._terrain_tree.exists(iid):
                self._terrain_tree.selection_set(iid)
                self._terrain_tree.see(iid)
            return
        iid = f"tri_{tri_idx}"
        if self._terrain_tree.exists(iid):
            self._terrain_tree.selection_set(iid)
            self._terrain_tree.see(iid)

    def _on_terrain_tree_select(self, _e: tk.Event) -> None:
        sel = self._terrain_tree.selection()
        if not sel:
            return
        vals = self._terrain_tree.item(sel[0], "values")
        if not vals:
            return
        idx = int(vals[0])
        if getattr(self, "_terrain_mode_var", None) and self._terrain_mode_var.get() == "Chunks":
            self._selected_tile = idx
            self._selected_terrain = next(
                (i for i, meta in enumerate(self._scene.terrain_meta)
                 if meta.get("tile_index") == idx),
                None,
            )
            self._terrain_canvas.select_tile(idx)
            return
        self._selected_terrain = idx
        self._selected_tile = self._scene.terrain_meta[idx].get("tile_index") if idx < len(self._scene.terrain_meta) else None
        self._terrain_canvas.select_tile(None)
        self._terrain_canvas.select_terrain(idx)

    def _on_terrain_mode_changed(self, _e: tk.Event | None = None) -> None:
        self._selected_terrain = None
        self._selected_tile = None
        self._terrain_canvas.select_terrain(None)
        self._terrain_canvas.select_tile(None)
        self._populate_terrain_tree()

    def _focus_selected_terrain(self) -> None:
        tri_indices = self._selected_chunk_tri_indices()
        if tri_indices:
            verts_all = [v for i in tri_indices for v in self._scene.terrain_tris[i][0]]
            cx = sum(v[0] for v in verts_all) / len(verts_all)
            cy = sum(v[1] for v in verts_all) / len(verts_all)
            cz = sum(v[2] for v in verts_all) / len(verts_all)
        elif self._selected_terrain is not None and self._selected_terrain < len(self._scene.terrain_tris):
            verts, _cy = self._scene.terrain_tris[self._selected_terrain]
            cx = sum(v[0] for v in verts) / 3.0
            cy = sum(v[1] for v in verts) / 3.0
            cz = sum(v[2] for v in verts) / 3.0
        else:
            return
        cam = self._terrain_canvas.cam
        cam.cx, cam.cy, cam.cz = cx, cy, cz
        cam.distance = max(self._scene.span * 0.03, 1.0)
        self._terrain_canvas.redraw()

    def _edit_selected_terrain(self) -> None:
        if self._selected_terrain is None or self._selected_terrain >= len(self._scene.terrain_tris):
            messagebox.showinfo("No selection", "Select a terrain triangle first."); return
        TerrainEditDialog(self, self._selected_terrain, self._scene.terrain_tris[self._selected_terrain][0],
                          on_save=self._on_terrain_saved)

    def _selected_chunk_tri_indices(self) -> list[int]:
        if self._selected_tile is None:
            return []
        return [
            i for i, meta in enumerate(self._scene.terrain_meta)
            if meta.get("tile_index") == self._selected_tile
        ]

    def _move_selected_chunk(self) -> None:
        if self._selected_tile is None:
            messagebox.showinfo("No chunk", "Select a terrain chunk first."); return
        OffsetEditDialog(self, f"Move Terrain Chunk #{self._selected_tile}",
                         on_apply=self._apply_selected_chunk_offset)

    def _apply_selected_chunk_offset(self, dx: float, dy: float, dz: float) -> None:
        tri_indices = self._selected_chunk_tri_indices()
        if not tri_indices:
            return
        for i in tri_indices:
            verts, cy = self._scene.terrain_tris[i]
            self._scene.terrain_tris[i] = (
                [[v[0] + dx, v[1] + dy, v[2] + dz] for v in verts],
                cy + dy,
            )
        self._scene.rebuild_terrain_numpy()
        self._populate_terrain_tree()
        self._terrain_canvas.select_tile(self._selected_tile)
        self._terrain_canvas.redraw()
        self._world_canvas.redraw()
        self._log_line(f"Moved terrain chunk #{self._selected_tile} by ({dx:.3f}, {dy:.3f}, {dz:.3f}) in memory")

    def _on_terrain_saved(self, tri_idx: int, verts: list[list[float]]) -> None:
        if tri_idx < 0 or tri_idx >= len(self._scene.terrain_tris):
            return
        cy = sum(v[1] for v in verts) / 3.0
        self._scene.terrain_tris[tri_idx] = (verts, cy)
        self._scene.rebuild_terrain_numpy()
        self._populate_terrain_tree()
        self._selected_terrain = tri_idx
        self._selected_tile = self._scene.terrain_meta[tri_idx].get("tile_index") if tri_idx < len(self._scene.terrain_meta) else None
        iid = f"tri_{tri_idx}"
        if self._terrain_tree.exists(iid):
            self._terrain_tree.selection_set(iid)
        self._terrain_canvas.select_terrain(tri_idx)
        self._world_canvas.redraw()
        self._log_line(f"Edited terrain triangle #{tri_idx} in memory")

    def _get_selected_obj(self) -> "MapObjectRecord | None":  # type: ignore[name-defined]
        if self._selected_obj is None: return None
        return next((o for o in self._objects if o.index == self._selected_obj), None)

    def _object_row_iid_for_index(self, obj_index: int) -> str | None:
        for iid in self._obj_tree.get_children():
            vals = self._obj_tree.item(iid, "values")
            if vals and int(vals[0]) == obj_index:
                return iid
        return None

    def _edit_selected_obj(self) -> None:
        obj = self._get_selected_obj()
        if obj is None: return
        ObjectEditDialog(self, obj, on_save=self._on_obj_saved,
                         known_types=self._type_registry,
                         ground_y_provider=self._ground_y_at)

    def _clone_selected_obj(self) -> None:
        obj = self._get_selected_obj()
        if obj is None:
            messagebox.showinfo("No selection", "Select an object first."); return
        new_idx = max((o.index for o in self._objects), default=-1) + 1
        clone   = make_object_copy(obj, new_idx)
        clone.pos_x_fixed12 += 512   # nudge +0.125 units so it's not on top
        AddObjectDialog(self, self._type_registry, template=clone,
                        on_add=self._do_add_object)

    def _add_new_obj_dialog(self) -> None:
        if not self._type_registry:
            messagebox.showinfo("No types", "Open a WAD with MAP objects first."); return
        template = self._get_selected_obj()
        AddObjectDialog(self, self._type_registry, template=template,
                        on_add=self._do_add_object)

    def _focus_selected_obj(self) -> None:
        if self._selected_obj is None: return
        # object_positions is indexed by list position, not .index field
        pos_list = self._scene.object_positions
        obj_idx = next((i for i, o in enumerate(self._objects)
                        if o.index == self._selected_obj), None)
        if obj_idx is None or obj_idx >= len(pos_list): return
        pos = pos_list[obj_idx]
        cam = self._world_canvas.cam
        cam.cx, cam.cy, cam.cz = pos[0], pos[1], pos[2]
        # Zoom to a sensible close-up: 5 % of the overall scene span, min 2 units
        cam.distance = max(self._scene.span * 0.05, 2.0)
        self._world_canvas.redraw()

    # ── Obj save / add callbacks ──────────────────────────────────────────────

    def _delete_selected_obj(self) -> None:
        obj = self._get_selected_obj()
        if obj is None:
            messagebox.showinfo("No selection", "Select an object first."); return
        name = self._stpc_names.get(obj.script_offset, f"0x{obj.script_offset:08X}")
        if not messagebox.askyesno("Delete object",
                                   f"Delete object #{obj.index} ({name})?",
                                   parent=self):
            return
        if not self.work or self._mapx is None:
            return
        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None:
            return
        try:
            new_map = delete_object_from_map_chunk(map_data, self._mapx, obj)
            self.work.save_chunk_data("MAP ", new_map)
            self._log_line(f"Deleted object #{obj.index} ({name})")
            self._selected_obj = None
            self._load_game_data()
            self._reload_scene()
        except Exception as exc:
            messagebox.showerror("Delete failed", str(exc), parent=self)

    def _ground_y_at(self, x: float, z: float) -> float | None:
        best: float | None = None
        eps = 1e-5
        for verts, _cy in self._scene.terrain_tris:
            (x1, y1, z1), (x2, y2, z2), (x3, y3, z3) = verts
            denom = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3)
            if abs(denom) <= 1e-9:
                continue
            a = ((z2 - z3) * (x - x3) + (x3 - x2) * (z - z3)) / denom
            b = ((z3 - z1) * (x - x3) + (x1 - x3) * (z - z3)) / denom
            c = 1.0 - a - b
            if a >= -eps and b >= -eps and c >= -eps:
                y = a * y1 + b * y2 + c * y3
                if best is None or y > best:
                    best = y
        return best

    def _on_canvas_object_moved(self, pos_idx: int, pos: list[float], commit: bool = False) -> None:
        if pos_idx < 0 or pos_idx >= len(self._objects):
            return
        obj = self._objects[pos_idx]
        old = self._scene.object_positions[pos_idx] if pos_idx < len(self._scene.object_positions) else [
            obj.pos_x_fixed12 / 4096.0,
            obj.pos_y_fixed12 / 4096.0,
            obj.pos_z_fixed12 / 4096.0,
        ]
        obj.pos_x_fixed12 = int(round(pos[0] * 4096))
        obj.pos_y_fixed12 = int(round(pos[1] * 4096))
        obj.pos_z_fixed12 = int(round(pos[2] * 4096))
        snapped = [
            obj.pos_x_fixed12 / 4096.0,
            obj.pos_y_fixed12 / 4096.0,
            obj.pos_z_fixed12 / 4096.0,
        ]
        if pos_idx < len(self._scene.object_positions):
            self._scene.object_positions[pos_idx] = snapped
            if self._scene.objs_np is not None:
                self._scene.objs_np[pos_idx] = snapped
        dx, dy, dz = snapped[0] - old[0], snapped[1] - old[1], snapped[2] - old[2]
        if dx or dy or dz:
            mesh_ids = {obj.index, pos_idx}
            moved = []
            for verts, obj_i, cy in self._scene.object_tris:
                if obj_i in mesh_ids:
                    nverts = [[v[0] + dx, v[1] + dy, v[2] + dz] for v in verts]
                    moved.append((nverts, obj_i, cy + dy))
                else:
                    moved.append((verts, obj_i, cy))
            self._scene.object_tris = moved
        iid = self._object_row_iid_for_index(obj.index)
        if iid and self._obj_tree.exists(iid):
            values = list(self._obj_tree.item(iid, "values"))
            values[3] = f"{snapped[0]:.2f}"
            values[4] = f"{snapped[1]:.2f}"
            values[5] = f"{snapped[2]:.2f}"
            self._obj_tree.item(iid, values=values)
            self._obj_tree.selection_set(iid)
        self._selected_obj = obj.index
        if commit:
            self._write_obj_to_map_bin(obj)
            self._log_line(f"Moved object #{obj.index}  pos=({snapped[0]:.3f}, {snapped[1]:.3f}, {snapped[2]:.3f})")

    def _on_obj_saved(self, obj: Any) -> None:
        self._write_obj_to_map_bin(obj)
        # Update in-memory position for viewport
        for i, o in enumerate(self._objects):
            if o.index == obj.index and i < len(self._scene.object_positions):
                old = self._scene.object_positions[i]
                new_pos = [
                    obj.pos_x_fixed12 / 4096.0,
                    obj.pos_y_fixed12 / 4096.0,
                    obj.pos_z_fixed12 / 4096.0,
                ]
                self._scene.object_positions[i] = new_pos
                if self._scene.objs_np is not None:
                    self._scene.objs_np[i] = new_pos
                dx, dy, dz = new_pos[0] - old[0], new_pos[1] - old[1], new_pos[2] - old[2]
                if dx or dy or dz:
                    mesh_ids = {obj.index, i}
                    self._scene.object_tris = [
                        ([[v[0] + dx, v[1] + dy, v[2] + dz] for v in verts], obj_i, cy + dy)
                        if obj_i in mesh_ids else (verts, obj_i, cy)
                        for verts, obj_i, cy in self._scene.object_tris
                    ]
                break
        self._populate_obj_tree()
        # Restore tree selection so the row stays highlighted after the refresh
        if self._selected_obj is not None:
            try:
                iid = self._object_row_iid_for_index(self._selected_obj)
                if iid:
                    self._obj_tree.selection_set(iid)
                    self._obj_tree.see(iid)
            except Exception:
                pass
        self._world_canvas.redraw()
        self._log_line(f"Object #{obj.index} saved  pos=({obj.pos_x:.3f}, {obj.pos_y:.3f}, {obj.pos_z:.3f})")

    def _do_add_object(self, new_obj: Any) -> None:
        if not self.work or self._mapx is None: return
        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None: return
        raw = pack_map_object(new_obj)
        _, final_dw = self._map_flags
        try:
            new_map = add_object_to_map_chunk(map_data, self._mapx, raw,
                                              assume_final_dword=final_dw)
            self.work.save_chunk_data("MAP ", new_map)
            self._log_line(f"Added object (type 0x{new_obj.script_offset:08X}  "
                           f"pos={new_obj.pos_x_fixed12/4096.0:.2f},"
                           f"{new_obj.pos_y_fixed12/4096.0:.2f},"
                           f"{new_obj.pos_z_fixed12/4096.0:.2f})")
            # Full re-parse so indices and file_offsets are consistent
            self._load_game_data()
            self._reload_scene()
        except Exception as exc:
            messagebox.showerror("Add failed", str(exc))

    def _write_obj_to_map_bin(self, obj: Any) -> None:
        if not self.work: return
        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None: return
        try:
            self.work.save_chunk_data("MAP ", patch_map_chunk_object(map_data, obj))
        except Exception as exc:
            self._log_line(f"MAP patch error: {exc}")

    # ── Log ──────────────────────────────────────────────────────────────────

    def _log_line(self, text: str) -> None:
        self._log.insert("end", text.rstrip() + "\n")
        self._log.see("end")


# ─────────────────────────────────────────────────────────────────────────────
# Entry point
# ─────────────────────────────────────────────────────────────────────────────

def main(argv: list[str] | None = None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    app  = WadEditorApp()
    if argv and Path(argv[0]).exists():
        app._open_wad(Path(argv[0]))
    app.mainloop()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
