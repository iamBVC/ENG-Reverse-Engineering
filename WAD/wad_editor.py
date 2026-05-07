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

import json
import math
import re
import struct
import sys
import tkinter as tk
from collections import Counter
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
from eng_wad.wad import read_wad, WadChunk

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

WORK_SUFFIX      = "_wadedit"
OBJ_RECORD_FMT   = "<3H3i9I2H"
OBJ_RECORD_SIZE  = struct.calcsize(OBJ_RECORD_FMT)   # 58
MAX_RENDER_TRIS  = 8000   # painter's-algorithm budget per frame

BG_COLOR        = (17, 19, 23)
TERRAIN_COLOR   = (70, 90, 110)
TERRAIN_EDGE    = (40, 60, 80)
OBJ_COLOR       = (240, 180, 60)
OBJ_SEL_COLOR   = (255, 80, 80)
OBJ_RADIUS      = 6

_TC = TERRAIN_COLOR   # short alias inside hot path
_TE = TERRAIN_EDGE


# ─────────────────────────────────────────────────────────────────────────────
# WAD work-folder
# ─────────────────────────────────────────────────────────────────────────────

class WorkFolder:
    """Manages a temp directory that mirrors a WAD's chunks as individual .bin files."""

    def __init__(self, wad_path: Path) -> None:
        self.wad_path   = wad_path
        self.work_dir   = wad_path.parent / (wad_path.stem + WORK_SUFFIX)
        self.manifest_path = self.work_dir / "manifest.json"
        self.entries: list[dict] = []

    def extract(self, wad_data: bytes, chunks: list[WadChunk]) -> None:
        self.work_dir.mkdir(parents=True, exist_ok=True)
        self.entries = []
        for i, chunk in enumerate(chunks):
            safe = "".join(c if (c.isalnum() or c in "_-") else "_" for c in chunk.tag).strip("_") or "UNK"
            bin_name = f"chunk_{i:03d}_{safe}.bin"
            (self.work_dir / bin_name).write_bytes(wad_data[chunk.offset: chunk.offset + chunk.size])
            self.entries.append({"index": i, "tag": chunk.tag,
                                 "original_offset": chunk.offset, "original_size": chunk.size,
                                 "bin_file": bin_name})
        self._save_manifest()

    def _save_manifest(self) -> None:
        self.manifest_path.write_text(
            json.dumps({"wad_source": str(self.wad_path), "chunks": self.entries}, indent=2),
            encoding="utf-8")

    def load(self) -> bool:
        if not self.manifest_path.exists():
            return False
        try:
            data = json.loads(self.manifest_path.read_text(encoding="utf-8"))
            self.entries = data.get("chunks", [])
            return bool(self.entries)
        except Exception:
            return False

    def get_chunk_data(self, tag: str) -> bytes | None:
        for e in self.entries:
            if e["tag"] == tag:
                p = self.work_dir / e["bin_file"]
                return p.read_bytes() if p.exists() else None
        return None

    def save_chunk_data(self, tag: str, data: bytes) -> bool:
        for e in self.entries:
            if e["tag"] == tag:
                (self.work_dir / e["bin_file"]).write_bytes(data)
                return True
        return False

    def chunk_info(self) -> list[dict]:
        out = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            out.append({**e, "current_size": p.stat().st_size if p.exists() else 0})
        return out

    def pack_wad(self, out_path: Path) -> None:
        chunk_blocks = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            chunk_blocks.append((e["tag"], p.read_bytes() if p.exists() else b""))
        total = 4 + sum(8 + len(d) for _, d in chunk_blocks)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        with out_path.open("wb") as f:
            f.write(struct.pack("<I", total - 4))
            for tag, cdata in chunk_blocks:
                tag_b = tag.encode("ascii", errors="replace")[:4].ljust(4, b"\x00")
                f.write(bytes(reversed(tag_b)))
                f.write(struct.pack("<I", len(cdata)))
                f.write(cdata)

    @property
    def is_open(self) -> bool:
        return bool(self.entries)


# ─────────────────────────────────────────────────────────────────────────────
# MAP object patching
# ─────────────────────────────────────────────────────────────────────────────

def pack_map_object(obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    return struct.pack(OBJ_RECORD_FMT,
        obj.rot_x_units, obj.rot_y_units, obj.rot_z_units,
        obj.pos_x_fixed12, obj.pos_y_fixed12, obj.pos_z_fixed12,
        obj.script_offset, obj.local_count, obj.section2_index_raw,
        obj.stack_word_count, obj.stack_arg_count, obj.spawn_flags,
        obj.extra_count, obj.section4_index_raw, obj.spawn_aux_raw,
        obj.flags, obj.extra_u16)


def patch_map_chunk_object(map_data: bytes, obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    data = bytearray(map_data)
    off  = obj.file_offset
    data[off: off + OBJ_RECORD_SIZE] = pack_map_object(obj)
    return bytes(data)


def add_object_to_map_chunk(
    map_data: bytes,
    mapx: "MapFullExe",       # type: ignore[name-defined]
    new_obj_raw: bytes,
    *,
    assume_final_dword: bool = True,
) -> bytes:
    """Insert a new 58-byte object record into the MAP chunk and update the count."""
    if not mapx.objects:
        return map_data  # cannot locate section without at least one existing object
    count_off   = mapx.objects[0].file_offset - 8   # 4-byte count + 4-byte unknown_b
    last_end    = mapx.objects[-1].file_offset + OBJ_RECORD_SIZE
    prefix      = map_data[:count_off]
    tail        = map_data[last_end:]
    new_count_b = struct.pack("<I", len(mapx.objects) + 1)
    unk_b_b     = struct.pack("<I", mapx.object_count_unknown_b)
    existing    = map_data[mapx.objects[0].file_offset: last_end]
    return prefix + new_count_b + unk_b_b + existing + new_obj_raw + tail


def delete_object_from_map_chunk(
    map_data: bytes,
    mapx: "MapFullExe",       # type: ignore[name-defined]
    obj: "MapObjectRecord",   # type: ignore[name-defined]
) -> bytes:
    """Remove one 58-byte object record from the MAP chunk and update the count."""
    if not mapx.objects or not any(o.file_offset == obj.file_offset for o in mapx.objects):
        return map_data
    if len(mapx.objects) <= 1:
        raise ValueError("Cannot delete the only MAP object; object table location would be ambiguous.")
    count_off = mapx.objects[0].file_offset - 8
    first_off = mapx.objects[0].file_offset
    last_end  = mapx.objects[-1].file_offset + OBJ_RECORD_SIZE
    prefix    = map_data[:count_off]
    tail      = map_data[last_end:]
    existing  = bytearray(map_data[first_off:last_end])
    rel       = obj.file_offset - first_off
    del existing[rel: rel + OBJ_RECORD_SIZE]
    return (
        prefix
        + struct.pack("<I", len(mapx.objects) - 1)
        + struct.pack("<I", mapx.object_count_unknown_b)
        + bytes(existing)
        + tail
    )


def make_object_copy(template: "MapObjectRecord", new_index: int) -> "MapObjectRecord":  # type: ignore[name-defined]
    """Return a shallow copy of *template* with a placeholder index/offset."""
    import copy
    obj = copy.copy(template)
    obj.index       = new_index
    obj.file_offset = 0   # will be assigned after patch
    return obj


# ─────────────────────────────────────────────────────────────────────────────
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
        self.object_positions: list[list[float]]    = []
        self.bounds: tuple = (0, 0, 0, 1, 1, 1)
        # numpy fast path (populated in _build_numpy())
        self.verts_np:  "np.ndarray | None" = None   # (3*M, 3) float32
        self.shades_np: "np.ndarray | None" = None   # (M,) float32
        self.objs_np:   "np.ndarray | None" = None   # (K, 3) float32

    def build(self, mapx: "MapFullExe", trak: "TrakFile", *, terrain_yaw_sign: int = 1) -> None:  # type: ignore[name-defined]
        self.terrain_tris.clear()
        self.object_positions.clear()
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


def render_scene(
    scene: SceneData,
    cam: Camera,
    w: int, h: int,
    selected_obj: int | None = None,
) -> "Image.Image":   # type: ignore[name-defined]
    if not HAS_PIL:
        raise RuntimeError("Pillow not installed")

    img  = Image.new("RGB", (w, h), BG_COLOR)
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
            if near_order.size > MAX_RENDER_TRIS:
                near_order = near_order[:MAX_RENDER_TRIS]     # drop distant excess
            order = near_order[::-1]                          # draw far → near

            s_min   = float(S.min())
            s_range = max(float(S.max()) - s_min, 1.0)
            # Pre-compute per-face shade colours
            t       = (S - s_min) / s_range            # (M,)
            blend   = (0.4 + 0.6 * t).clip(0.0, 1.0)  # (M,)
            cr      = (_TC[0] * blend).astype(np.uint8)
            cg      = (_TC[1] * blend).astype(np.uint8)
            cb      = (_TC[2] * blend).astype(np.uint8)

            sx_f = sx.astype(np.float32)
            sy_f = sy.astype(np.float32)

            for fi in order:
                ia, ib, ic = i0[fi], i1[fi], i2[fi]
                ax  = sx_f[ib] - sx_f[ia];  ay = sy_f[ib] - sy_f[ia]
                bx_ = sx_f[ic] - sx_f[ia];  by_ = sy_f[ic] - sy_f[ia]
                if abs(float(ax * by_ - ay * bx_)) < 0.5:  # degenerate/sub-pixel
                    continue
                fill = (int(cr[fi]), int(cg[fi]), int(cb[fi]))
                draw.polygon(
                    [(float(sx_f[ia]), float(sy_f[ia])),
                     (float(sx_f[ib]), float(sy_f[ib])),
                     (float(sx_f[ic]), float(sy_f[ic]))],
                    fill=fill, outline=_TE)

        # ── Objects (also batched) ───────────────────────────────────────────
        if scene.objs_np is not None and scene.objs_np.shape[0]:
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
                px_, py_ = float(osx[ki]), float(osy[ki])
                color = OBJ_SEL_COLOR if ki == selected_obj else OBJ_COLOR
                r = OBJ_RADIUS + (2 if ki == selected_obj else 0)
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

    def __init__(self, master: tk.Widget, on_select: Any = None) -> None:
        super().__init__(master)
        self._on_select    = on_select
        self._on_move      = None
        self.scene         = SceneData()
        self.cam           = Camera()
        self.selected_obj: int | None = None
        self._tk_img       = None
        self._drag_start: tuple[int, int] | None = None
        self._axis_handles: list[dict[str, Any]] = []
        self._axis_drag: dict[str, Any] | None = None
        self._redraw_pending = False    # throttle flag

        self._canvas = tk.Canvas(self, bg="#111317", highlightthickness=0, cursor="crosshair")
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

    def load_scene(self, scene: SceneData) -> None:
        self.scene = scene
        self.cam.reset_to_scene(scene)
        self.selected_obj = None
        self.redraw()

    def select_object(self, idx: int | None) -> None:
        self.selected_obj = idx
        self.redraw()

    def set_object_move_callback(self, callback: Any) -> None:
        self._on_move = callback

    def redraw(self) -> None:
        w = self._canvas.winfo_width()
        h = self._canvas.winfo_height()
        if w < 4 or h < 4:
            return
        self._canvas.delete("all")
        self._axis_handles = []
        if not HAS_PIL:
            self._canvas.create_text(w//2, h//2,
                text="Install Pillow for 3D view", fill="#ff8080", font=("Consolas", 12))
            self._draw_fallback_2d(w, h)
            self._draw_move_gizmo(w, h)
            return
        try:
            img = render_scene(self.scene, self.cam, w, h, self.selected_obj)
            self._tk_img = ImageTk.PhotoImage(img)
            self._canvas.create_image(0, 0, image=self._tk_img, anchor="nw")
            self._draw_move_gizmo(w, h)
        except Exception as exc:
            self._canvas.create_text(10, 10, text=f"Render error: {exc}",
                                     fill="red", anchor="nw")
            self._draw_fallback_2d(w, h)
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
        ex, ey, ez = self.cam.eye()
        fx, fy, fz = self.cam.cx - ex, self.cam.cy - ey, self.cam.cz - ez
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
        f_px = min(w, h) * 0.5 / math.tan(math.radians(self.cam.fov * 0.5))
        sx = w * 0.5 + (dx * rx + dy * ry + dz * rz) / depth * f_px
        sy = h * 0.5 - (dx * ux + dy * uy + dz * uz) / depth * f_px
        return sx, sy, depth

    def _draw_move_gizmo(self, w: int, h: int) -> None:
        if self.selected_obj is None or self.selected_obj >= len(self.scene.object_positions):
            return
        pos = self.scene.object_positions[self.selected_obj]
        center = self._project_point(pos, w, h)
        if not center:
            return
        axis_len = max(self.scene.span * 0.06, 1.0)
        axes = [
            ("X", (1.0, 0.0, 0.0), "#ff4d4d"),
            ("Y", (0.0, 1.0, 0.0), "#55d66b"),
            ("Z", (0.0, 0.0, 1.0), "#4d8dff"),
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

class ObjectEditDialog(tk.Toplevel):

    FIELDS = [
        # (attr,               label,                      kind)
        ("pos_x_fixed12",    "Pos X  (world = val/4096)", "f12"),
        ("pos_y_fixed12",    "Pos Y  (world = val/4096)", "f12"),
        ("pos_z_fixed12",    "Pos Z  (world = val/4096)", "f12"),
        ("rot_x_units",      "Rot X  (4096 = 360°)",     "deg"),
        ("rot_y_units",      "Rot Y  (4096 = 360°)",     "deg"),
        ("rot_z_units",      "Rot Z  (4096 = 360°)",     "deg"),
        ("script_offset",    "Type / Script offset",      "type"),
        ("local_count",      "Local count",               "u32"),
        ("section2_index_raw","Section2 index (raw)",     "u32"),
        ("stack_word_count", "Stack word count",           "u32"),
        ("stack_arg_count",  "Stack arg count",            "u32"),
        ("spawn_flags",      "Spawn flags",                "hex"),
        ("extra_count",      "Extra count",                "u32"),
        ("section4_index_raw","Section4 index (raw)",     "u32"),
        ("spawn_aux_raw",    "Spawn aux (raw)",            "u32"),
        ("flags",            "Flags (u16)",                "hex"),
        ("extra_u16",        "Extra u16",                  "u32"),
    ]

    def __init__(self, parent: tk.Widget, obj: "MapObjectRecord",  # type: ignore[name-defined]
                 on_save: Any = None,
                 known_types: list[tuple[int, str]] | None = None,
                 ground_y_provider: Any = None) -> None:
        super().__init__(parent)
        self.title(f"Edit Object #{obj.index}")
        self.resizable(True, False)
        self.grab_set()
        self._obj         = obj
        self._on_save     = on_save
        self._known_types = known_types or []
        self._ground_y_provider = ground_y_provider
        self._vars: dict[str, tk.StringVar] = {}
        self._type_combo: ttk.Combobox | None = None
        self._build(obj)

    # ── build ─────────────────────────────────────────────────────────────────

    def _build(self, obj: Any) -> None:
        frm = ttk.Frame(self, padding=10)
        frm.pack(fill="both", expand=True)

        ttk.Label(frm, text=f"Object #{obj.index}   file_offset=0x{obj.file_offset:X}",
                  font=("Consolas", 10, "bold")).grid(row=0, column=0, columnspan=3,
                                                      sticky="w", pady=(0, 8))

        type_labels = [lbl for _, lbl in self._known_types]  # labels for combobox

        for row, (fname, label, kind) in enumerate(self.FIELDS, start=1):
            raw_val = getattr(obj, fname)

            ttk.Label(frm, text=label, width=30, anchor="w").grid(
                row=row, column=0, sticky="w", padx=(0, 8))

            if kind == "type":
                # Combobox showing all known script offsets in the level
                cur_lbl = next((lbl for off, lbl in self._known_types if off == raw_val),
                               f"0x{raw_val:08X}")
                var = tk.StringVar(value=cur_lbl)
                self._vars[fname] = var
                cb = ttk.Combobox(frm, textvariable=var, values=type_labels,
                                  width=36, state="normal")
                cb.grid(row=row, column=1, sticky="ew")
                self._type_combo = cb
                ttk.Label(frm, text="select or type hex",
                          foreground="#888").grid(row=row, column=2, sticky="w", padx=(6, 0))
            else:
                if kind == "f12":
                    display = f"{raw_val / 4096.0:.6f}"
                elif kind == "hex":
                    display = f"0x{raw_val:08X}"
                else:
                    display = str(raw_val)
                var = tk.StringVar(value=display)
                self._vars[fname] = var
                ttk.Entry(frm, textvariable=var, width=20).grid(
                    row=row, column=1, sticky="ew")
                hint = {"f12": "float (world) or int (raw fixed12)",
                        "hex": "hex or decimal OK",
                        "deg": "0–4095 units",
                        "u32": "unsigned int"}.get(kind, "")
                ttk.Label(frm, text=hint, foreground="#888").grid(
                    row=row, column=2, sticky="w", padx=(6, 0))

        frm.columnconfigure(1, weight=1)
        btns = ttk.Frame(self, padding=(10, 0, 10, 10))
        btns.pack(fill="x")
        if self._ground_y_provider:
            ttk.Button(btns, text="Snap Y to Ground",
                       command=self._snap_y_to_ground).pack(side="left")
        ttk.Button(btns, text="Save & Close", command=self._save).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel",       command=self.destroy).pack(side="right")

    # ── parsing ───────────────────────────────────────────────────────────────

    def _parse_val(self, fname: str, kind: str, text: str) -> int | None:
        text = text.strip()
        if kind == "type":
            # First try to find by label match
            for off, lbl in self._known_types:
                if text == lbl:
                    return off
            # Otherwise parse as hex/dec
            try:
                return int(text, 0)
            except ValueError:
                # Try to extract hex from label like "0x0042310E  (×3)"
                import re
                m = re.search(r'0x([0-9A-Fa-f]+)', text)
                return int(m.group(1), 16) if m else None
        try:
            if kind == "f12":
                return int(round(float(text) * 4096))
            return int(text, 0)
        except ValueError:
            return None

    def _snap_y_to_ground(self) -> None:
        if not self._ground_y_provider:
            return
        x_raw = self._parse_val("pos_x_fixed12", "f12", self._vars["pos_x_fixed12"].get())
        z_raw = self._parse_val("pos_z_fixed12", "f12", self._vars["pos_z_fixed12"].get())
        if x_raw is None or z_raw is None:
            messagebox.showerror("Snap failed", "Cannot parse X/Z position.", parent=self)
            return
        y = self._ground_y_provider(x_raw / 4096.0, z_raw / 4096.0)
        if y is None:
            messagebox.showinfo("Snap failed", "No terrain triangle found under this object.", parent=self)
            return
        self._vars["pos_y_fixed12"].set(f"{y:.6f}")

    def _save(self) -> None:
        updates: dict[str, int] = {}
        for fname, label, kind in self.FIELDS:
            text = self._vars[fname].get()
            val  = self._parse_val(fname, kind, text)
            if val is None:
                messagebox.showerror("Parse error",
                    f"Cannot parse '{label}': {text!r}", parent=self)
                return
            updates[fname] = val
        for fname, val in updates.items():
            setattr(self._obj, fname, val)
        if self._on_save:
            self._on_save(self._obj)
        self.destroy()


# ─────────────────────────────────────────────────────────────────────────────
# Add-object dialog
# ─────────────────────────────────────────────────────────────────────────────

class AddObjectDialog(tk.Toplevel):
    """Pick type + world position, optionally cloning non-positional fields."""

    def __init__(self, parent: tk.Widget,
                 known_types: list[tuple[int, str]],
                 template: "MapObjectRecord | None",  # type: ignore[name-defined]
                 on_add: Any = None) -> None:
        super().__init__(parent)
        self.title("Add New Object")
        self.resizable(False, False)
        self.grab_set()
        self._known_types = known_types
        self._template    = template
        self._on_add      = on_add
        self._build()

    def _build(self) -> None:
        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)

        type_labels = [lbl for _, lbl in self._known_types]
        if self._template:
            default_lbl = next(
                (lbl for off, lbl in self._known_types if off == self._template.script_offset),
                f"0x{self._template.script_offset:08X}",
            )
        else:
            default_lbl = type_labels[0] if type_labels else "0x00000000"

        self._type_var = tk.StringVar(value=default_lbl)
        self._x_var    = tk.StringVar(value="0.0")
        self._y_var    = tk.StringVar(value="0.0")
        self._z_var    = tk.StringVar(value="0.0")
        self._clone_var= tk.BooleanVar(value=bool(self._template))

        rows = [
            ("Type / Script offset", self._type_var, "combo"),
            ("Pos X (world)",        self._x_var,    "entry"),
            ("Pos Y (world)",        self._y_var,    "entry"),
            ("Pos Z (world)",        self._z_var,    "entry"),
        ]
        for r, (lbl, var, kind) in enumerate(rows):
            ttk.Label(frm, text=lbl, width=24, anchor="w").grid(
                row=r, column=0, sticky="w", pady=3, padx=(0, 8))
            if kind == "combo":
                cb = ttk.Combobox(frm, textvariable=var, values=type_labels,
                                  width=34, state="normal")
                cb.grid(row=r, column=1, sticky="ew")
            else:
                ttk.Entry(frm, textvariable=var, width=20).grid(
                    row=r, column=1, sticky="ew")

        ttk.Checkbutton(frm, text="Clone non-positional fields from selected object",
                        variable=self._clone_var).grid(
            row=4, column=0, columnspan=2, sticky="w", pady=(8, 0))
        if self._template:
            ttk.Label(frm, text=f"  (selected: object #{self._template.index})",
                      foreground="#888").grid(row=5, column=0, columnspan=2, sticky="w")

        frm.columnconfigure(1, weight=1)

        # Fill from template button
        if self._template:
            ttk.Button(frm, text="Fill pos from selected",
                       command=self._fill_from_template).grid(
                row=6, column=0, columnspan=2, sticky="ew", pady=(8, 0))

        btns = ttk.Frame(self, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Add Object", command=self._add).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel",     command=self.destroy).pack(side="right")

    def _fill_from_template(self) -> None:
        if not self._template:
            return
        self._x_var.set(f"{self._template.pos_x_fixed12 / 4096.0:.6f}")
        self._y_var.set(f"{self._template.pos_y_fixed12 / 4096.0:.6f}")
        self._z_var.set(f"{self._template.pos_z_fixed12 / 4096.0:.6f}")

    def _parse_type(self, text: str) -> int | None:
        for off, lbl in self._known_types:
            if text.strip() == lbl:
                return off
        import re
        m = re.search(r'0x([0-9A-Fa-f]+)', text)
        if m:
            return int(m.group(1), 16)
        try:
            return int(text, 0)
        except ValueError:
            return None

    def _add(self) -> None:
        script_off = self._parse_type(self._type_var.get())
        if script_off is None:
            messagebox.showerror("Error", "Cannot parse type/script offset.", parent=self)
            return
        try:
            px = int(round(float(self._x_var.get()) * 4096))
            py = int(round(float(self._y_var.get()) * 4096))
            pz = int(round(float(self._z_var.get()) * 4096))
        except ValueError:
            messagebox.showerror("Error", "Invalid position value.", parent=self)
            return

        if self._clone_var.get() and self._template:
            new_obj = make_object_copy(self._template, new_index=-1)
            new_obj.script_offset  = script_off
            new_obj.pos_x_fixed12  = px
            new_obj.pos_y_fixed12  = py
            new_obj.pos_z_fixed12  = pz
        else:
            # Minimal safe defaults
            from eng_wad.map_full_chunk import MapObjectRecord
            new_obj = MapObjectRecord(
                index=-1, file_offset=0, raw=b"\x00" * OBJ_RECORD_SIZE,
                rot_x_units=0, rot_y_units=0, rot_z_units=0,
                pos_x_fixed12=px, pos_y_fixed12=py, pos_z_fixed12=pz,
                script_offset=script_off,
                local_count=0, section2_index_raw=0xFFFFFFFF,
                stack_word_count=0, stack_arg_count=0,
                spawn_flags=0x00020000,
                extra_count=0, section4_index_raw=0xFFFFFFFF,
                spawn_aux_raw=0, flags=0, extra_u16=0,
            )

        if self._on_add:
            self._on_add(new_obj)
        self.destroy()


# ─────────────────────────────────────────────────────────────────────────────
# Quick element-count helper
# ─────────────────────────────────────────────────────────────────────────────

def _quick_element_count(tag: str, data: bytes) -> str:
    try:
        n = struct.unpack_from("<I", data, 0)[0] if len(data) >= 4 else None
        labels = {"MAP ": "tiles", "TRAK": "records", "STPC": "defs",
                  "SMPC": "sounds", "AMPC": "ambients", "LGHT": "lights",
                  "TEXT": "textures", "LGPC": "lines"}
        if n is not None and tag in labels:
            return f"{n} {labels[tag]}"
    except Exception:
        pass
    return "—"


# ─────────────────────────────────────────────────────────────────────────────
# Script-offset type registry helpers
# ─────────────────────────────────────────────────────────────────────────────

def build_type_registry(
    objects: list,
    names: dict[int, str] | None = None,
) -> list[tuple[int, str]]:
    """Return [(script_offset, label)] sorted by instance count desc.

    When *names* is supplied, labels include the human-readable name:
        'KidOnLlama  0x0042310E  (×3)'
    otherwise:
        '0x0042310E  (×3 inst.)'
    """
    counts = Counter(o.script_offset for o in objects)
    result = []
    for off, cnt in sorted(counts.items(), key=lambda x: (-x[1], x[0])):
        name = (names or {}).get(off, "")
        if name:
            label = f"{name}  0x{off:08X}  (×{cnt})"
        else:
            label = f"0x{off:08X}  (×{cnt} inst.)"
        result.append((off, label))
    return result


# ── STPC name extraction ──────────────────────────────────────────────────────

_B4_OPCODE = b"\xB4\x00\x00\x00"   # VM opcode that precedes the object name

# CamelCase identifier: uppercase start, then alphanumeric, 3–30 chars total.
# This filters out error messages (spaces/colons) while matching all known names.
_NAME_RE = re.compile(r"^[A-Z][A-Za-z0-9]{2,29}$")

def _valid_stpc_name(raw: bytes) -> bool:
    try:
        text = raw.decode("ascii")
    except UnicodeDecodeError:
        return False
    if not _NAME_RE.match(text):
        return False
    # Reject common false positives from packed immediates and all-caps labels.
    if len(raw) < 3 or not any(97 <= b <= 122 for b in raw):
        return False
    return len(raw) >= 4 or not any(48 <= b <= 57 for b in raw)


def _b4_name_markers(stpc_data: bytes) -> list[tuple[int, str]]:
    """Return candidate debug/name markers from opcode B4 records.

    B4's inline payload is variable-width, so the name is not always at a fixed
    +20 byte position.  We scan the short payload window and keep the longest
    plausible CamelCase string, which picks object names like RisingColumns over
    helper labels like ColumnChild.
    """
    markers: list[tuple[int, str]] = []
    n = len(stpc_data)
    pos = stpc_data.find(_B4_OPCODE)
    while pos != -1:
        candidates: list[bytes] = []
        window_end = min(pos + 128, n)
        i = pos + 4
        while i < window_end:
            if ord("A") <= stpc_data[i] <= ord("Z"):
                j = i
                while j < window_end and stpc_data[j] != 0 and 32 <= stpc_data[j] <= 126:
                    j += 1
                raw = stpc_data[i:j]
                if j < n and stpc_data[j] == 0 and _valid_stpc_name(raw):
                    candidates.append(raw)
                i = max(j + 1, i + 1)
            else:
                i += 1
        if candidates:
            name = max(candidates, key=len).decode("ascii", errors="replace")
            markers.append((pos, name))
        pos = stpc_data.find(_B4_OPCODE, pos + 1)
    return markers


def _name_via_scan(stpc_data: bytes, start: int, end: int) -> str:
    """Fallback: find the first CamelCase identifier anywhere in [start, end).

    Scans byte-by-byte for null-terminated strings that start with an uppercase
    letter and contain only alphanumerics — this matches all ENG object names
    while rejecting error messages (spaces, punctuation).
    """
    n = len(stpc_data)
    i = start
    while i < min(end, n):
        b = stpc_data[i]
        if ord("A") <= b <= ord("Z"):   # potential identifier start
            j = i
            while j < n and stpc_data[j] != 0 and 32 <= stpc_data[j] <= 126:
                j += 1
            if j < n and stpc_data[j] == 0:
                name = stpc_data[i:j].decode("ascii", errors="replace")
                if _valid_stpc_name(name.encode("ascii", errors="ignore")):
                    return name
            i = j + 1
        else:
            i += 1
    return ""


def _marker_name_near(
    markers: list[tuple[int, str]],
    offset: int,
    *,
    before: int = 4096,
    after: int = 0,
) -> str:
    best_before: tuple[int, str] | None = None
    best_after: tuple[int, str] | None = None
    for pos, name in markers:
        if pos <= offset and offset - pos <= before:
            best_before = (pos, name)
        elif pos > offset:
            if pos - offset <= after:
                best_after = (pos, name)
            break
    if best_before:
        return best_before[1]
    if best_after:
        return best_after[1]
    return ""


def _referenced_script_name(stpc_data: bytes, start: int, markers: list[tuple[int, str]]) -> str:
    # B2 operands below the mesh table end are geometry refs. Large in-range
    # operands are usually script/DEFANIM pointers; the first named target is a
    # useful fallback for wrapper entrypoints.
    for pos in range(start, min(len(stpc_data) - 8, start + 768)):
        if stpc_data[pos:pos + 4] == b"\xB2\x00\x00\x00":
            target = int.from_bytes(stpc_data[pos + 4:pos + 8], "little", signed=False)
            if 0 <= target < len(stpc_data) and target >= 0x100000:
                name = _marker_name_near(markers, target, before=768, after=256)
                if name:
                    return name
    return ""


def build_stpc_name_map(stpc_data: bytes,
                        script_offsets: list[int]) -> dict[int, str]:
    """Return {script_offset: name} for every offset that has a readable name.

    MAP script offsets often point inside a larger STPC object block.  The B4
    debug/name marker can therefore appear before the entrypoint, while later
    B4 markers can be nested labels.  Prefer the nearest previous marker, then
    fall back to named script targets referenced by the entrypoint.
    """
    n = len(stpc_data)
    # Only consider offsets that fall within the STPC blob
    unique = sorted(so for so in set(script_offsets) if 0 <= so < n)
    if not unique:
        return {}

    result: dict[int, str] = {}
    markers = _b4_name_markers(stpc_data)
    for i, so in enumerate(unique):
        next_so = unique[i + 1] if i + 1 < len(unique) else n
        name = _marker_name_near(markers, so, before=4096, after=0)

        if not name:
            name = _referenced_script_name(stpc_data, so, markers)
        if not name:
            name = _marker_name_near(markers, so, before=0, after=1024)
        if not name:
            end = min(next_so, so + 2048)
            name = _name_via_scan(stpc_data, so, end)  # broader fallback
        if name:
            result[so] = name

    return result


# ─────────────────────────────────────────────────────────────────────────────
# Main application
# ─────────────────────────────────────────────────────────────────────────────

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
        self._stpc_names: dict[int, str] = {}
        self._type_registry: list[tuple[int, str]] = []

        self._build_ui()

    # ── UI construction ──────────────────────────────────────────────────────

    def _build_ui(self) -> None:
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
        self._nb.add(self._tab_world, text="World")
        self._build_world_tab()

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
        self._world_canvas = WorldCanvas(vp_frame)
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

        ttk.Label(right,
            text="Edit/Clone patches MAP .bin directly.\nSave WAD to write back.",
            foreground="#888", justify="left").pack(anchor="w", pady=(6, 0))

    # ── Open / Save ──────────────────────────────────────────────────────────

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
            self._world_canvas.load_scene(self._scene)
        self._populate_obj_tree()

    def _populate_obj_tree(self) -> None:
        self._obj_tree.delete(*self._obj_tree.get_children())
        for obj in self._objects:
            name = self._stpc_names.get(obj.script_offset, "")
            self._obj_tree.insert("", "end", iid=str(obj.index), values=(
                obj.index,
                f"0x{obj.script_offset:08X}",
                name,
                f"{obj.pos_x_fixed12/4096.0:.2f}",
                f"{obj.pos_y_fixed12/4096.0:.2f}",
                f"{obj.pos_z_fixed12/4096.0:.2f}",
                obj.rot_y_units,
            ))

    def _on_obj_tree_select(self, _e: tk.Event) -> None:
        sel = self._obj_tree.selection()
        if not sel: return
        obj_idx_field = int(sel[0])   # == obj.index (used as iid)
        self._selected_obj = obj_idx_field
        # The canvas renderer indexes objects by *position* in scene.objs_np,
        # not by obj.index.  Resolve the position so highlights are correct
        # even when indices are non-contiguous.
        pos_idx = next((i for i, o in enumerate(self._objects)
                        if o.index == obj_idx_field), None)
        self._world_canvas.select_object(pos_idx)

    # ── Object actions ────────────────────────────────────────────────────────

    def _get_selected_obj(self) -> "MapObjectRecord | None":  # type: ignore[name-defined]
        if self._selected_obj is None: return None
        return next((o for o in self._objects if o.index == self._selected_obj), None)

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
        iid = str(obj.index)
        if self._obj_tree.exists(iid):
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
                self._scene.object_positions[i] = [
                    obj.pos_x_fixed12 / 4096.0,
                    obj.pos_y_fixed12 / 4096.0,
                    obj.pos_z_fixed12 / 4096.0,
                ]
                if self._scene.objs_np is not None:
                    self._scene.objs_np[i] = self._scene.object_positions[i]
                break
        self._populate_obj_tree()
        # Restore tree selection so the row stays highlighted after the refresh
        if self._selected_obj is not None:
            try:
                iid = str(self._selected_obj)
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
