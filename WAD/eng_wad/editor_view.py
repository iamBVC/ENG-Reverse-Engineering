"""editor_view.py - reusable scene, renderer, and Tk viewport widgets for WAD tools."""

from __future__ import annotations

import math
import struct
import tkinter as tk
from tkinter import ttk
from typing import Any

from .editor_config import DEFAULT_EDITOR_CONFIG, cfg_color

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
        self.object_indices: list[int] = []
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
        self.object_indices.clear()
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

            for rec_tri_i, tri in enumerate(rec.table_b):
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
                    "record_tri_index": rec_tri_i,
                    "i0": tri.i0,
                    "i1": tri.i1,
                    "i2": tri.i2,
                })

        for obj in mapx.objects:
            ox = obj.pos_x_fixed12 / 4096.0
            oy = obj.pos_y_fixed12 / 4096.0
            oz = obj.pos_z_fixed12 / 4096.0
            self.object_positions.append([ox, oy, oz])
            self.object_indices.append(obj.index)
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
    obj_to_pos = {obj_i: i for i, obj_i in enumerate(getattr(scene, "object_indices", []))}
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
        pos_i = obj_to_pos.get(obj_i, obj_i)
        draw.polygon(pts, fill=obj_sel if pos_i == selected_obj else obj_col, outline=edge)


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
        obj_to_pos = {obj_i: i for i, obj_i in enumerate(getattr(scene, "object_indices", []))}
        mesh_object_ids = {obj_to_pos.get(obj_i, obj_i) for _verts, obj_i, _cy in scene.object_tris}
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
        self._on_terrain_move = None
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
        self._object_handles: list[dict[str, Any]] = []
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
        self.selected_tile = None
        if redraw:
            self.redraw()

    def select_object(self, idx: int | None) -> None:
        self.selected_obj = idx
        self.redraw()

    def set_object_move_callback(self, callback: Any) -> None:
        self._on_move = callback

    def set_terrain_move_callback(self, callback: Any) -> None:
        self._on_terrain_move = callback

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
        self._object_handles = []
        if not HAS_PIL:
            self._canvas.create_text(w//2, h//2,
                text="Install Pillow for 3D view", fill="#ff8080", font=("Consolas", 12))
            self._draw_fallback_2d(w, h)
            self._cache_object_handles(w, h)
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
            self._cache_object_handles(w, h)
            if self.mode in ("object", "terrain"):
                self._draw_move_gizmo(w, h)
        except Exception as exc:
            self._canvas.create_text(10, 10, text=f"Render error: {exc}",
                                     fill="red", anchor="nw")
            self._draw_fallback_2d(w, h)
            self._cache_terrain_handles(w, h)
            self._cache_object_handles(w, h)
            if self.mode in ("object", "terrain"):
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

    def _cache_object_handles(self, w: int, h: int) -> None:
        if self.mode != "object":
            return
        obj_to_pos = {obj_i: i for i, obj_i in enumerate(getattr(self.scene, "object_indices", []))}
        mesh_object_ids = {obj_to_pos.get(obj_i, obj_i) for _verts, obj_i, _cy in self.scene.object_tris}
        for verts, obj_i, _cy in self.scene.object_tris:
            projs = [self._project_point(p, w, h) for p in verts]
            if any(p is None for p in projs):
                continue
            pts = [(p[0], p[1]) for p in projs if p is not None]
            depth = sum(p[2] for p in projs if p is not None) / 3.0
            self._object_handles.append({
                "kind": "mesh",
                "obj": obj_to_pos.get(obj_i, obj_i),
                "pts": pts,
                "depth": depth,
            })
        radius = int(self.cfg.get("viewport", {}).get("object_radius", OBJ_RADIUS)) + 5
        for i, pos in enumerate(self.scene.object_positions):
            if i in mesh_object_ids:
                continue
            proj = self._project_point(pos, w, h)
            if not proj:
                continue
            self._object_handles.append({
                "kind": "marker",
                "obj": i,
                "center": (proj[0], proj[1]),
                "depth": proj[2],
                "radius": radius,
            })

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

    def _hit_object(self, x: int, y: int) -> int | None:
        mesh_hits = [
            h for h in self._object_handles
            if h["kind"] == "mesh" and self._point_in_tri(x, y, h["pts"])
        ]
        if mesh_hits:
            return int(min(mesh_hits, key=lambda h: h["depth"])["obj"])
        marker_hits = []
        for h in self._object_handles:
            if h["kind"] != "marker":
                continue
            cx, cy = h["center"]
            if math.hypot(x - cx, y - cy) <= h["radius"]:
                marker_hits.append(h)
        if marker_hits:
            return int(min(marker_hits, key=lambda h: h["depth"])["obj"])
        return None

    def _selected_terrain_move_target(self) -> tuple[tuple[str, int], list[float]] | None:
        if self.selected_tile is not None:
            tri_indices = [
                i for i, meta in enumerate(self.scene.terrain_meta)
                if meta.get("tile_index") == self.selected_tile
            ]
            if not tri_indices:
                return None
            verts = [v for i in tri_indices for v in self.scene.terrain_tris[i][0]]
            center = [
                sum(v[0] for v in verts) / len(verts),
                sum(v[1] for v in verts) / len(verts),
                sum(v[2] for v in verts) / len(verts),
            ]
            return ("tile", self.selected_tile), center
        if self.selected_terrain is not None and self.selected_terrain < len(self.scene.terrain_tris):
            verts = self.scene.terrain_tris[self.selected_terrain][0]
            center = [
                sum(v[0] for v in verts) / 3.0,
                sum(v[1] for v in verts) / 3.0,
                sum(v[2] for v in verts) / 3.0,
            ]
            return ("tri", self.selected_terrain), center
        return None

    def _draw_move_gizmo(self, w: int, h: int) -> None:
        if self.mode == "object":
            if self.selected_obj is None or self.selected_obj >= len(self.scene.object_positions):
                return
            target: Any = self.selected_obj
            pos = self.scene.object_positions[self.selected_obj]
        elif self.mode == "terrain":
            terrain_target = self._selected_terrain_move_target()
            if terrain_target is None:
                return
            target, pos = terrain_target
        else:
            return
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
                "origin": tuple(pos), "axis_len": axis_len, "target": target,
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
        hit = self._hit_axis(e.x, e.y)
        if hit and (
            (self.mode == "object" and self.selected_obj is not None and self._on_move)
            or (self.mode == "terrain" and self._on_terrain_move)
        ):
            self._axis_drag = {"handle": hit, "start": (e.x, e.y)}
            self._drag_start = None
            return
        if self.mode == "terrain":
            tri_idx = self._hit_terrain(e.x, e.y)
            if tri_idx is not None:
                self.selected_terrain = tri_idx
                if self._on_terrain_select:
                    self._on_terrain_select(tri_idx)
                self.redraw()
                return
        if self.mode == "object":
            obj_idx = self._hit_object(e.x, e.y)
            if obj_idx is not None:
                self.select_object(obj_idx)
                if self._on_select:
                    self._on_select(obj_idx)
                self._drag_start = None
                return
        self._drag_start = (e.x, e.y)

    def _dispatch_axis_drag(self, x: int, y: int, *, commit: bool) -> bool:
        if not self._axis_drag:
            return False
        sx, sy = self._axis_drag["start"]
        handle = self._axis_drag["handle"]
        pos = self._axis_drag_position(handle, x, y, sx, sy)
        target = handle.get("target")
        if isinstance(target, tuple) and self._on_terrain_move:
            self._on_terrain_move(target, pos, commit)
        elif self.selected_obj is not None and self._on_move:
            self._on_move(self.selected_obj, pos, commit)
        else:
            return False
        if not commit:
            self._schedule_redraw()
        return True

    def _on_lbdrag(self, e: tk.Event) -> None:
        if self._dispatch_axis_drag(e.x, e.y, commit=False):
            return
        if not self._drag_start: return
        dx = e.x - self._drag_start[0]; dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.orbit(dx * 0.008, -dy * 0.008)
        self._schedule_redraw()

    def _on_lbup(self, e: tk.Event) -> None:
        if self._dispatch_axis_drag(e.x, e.y, commit=True):
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

