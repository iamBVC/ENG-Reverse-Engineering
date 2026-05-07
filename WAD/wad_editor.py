#!/usr/bin/env python3
"""wad_editor.py — Full WAD editor with chunk splitting, 3D world view, and object editing.

Architecture:
  WorkFolder        — extracts every chunk to {wad_stem}_wadedit/*.bin + manifest.json
  Camera            — orbital (target + distance + yaw + pitch) with orbit/pan/zoom
  SceneData         — terrain + object geometry built from MAP + TRAK data
  WorldCanvas       — PIL-backed 3D canvas inside a tkinter Frame
  ObjectEditDialog  — modal dialog: edit all MapObjectRecord fields in-place
  WadEditorApp      — main window: Overview | World tabs + save button
"""

from __future__ import annotations

import json
import math
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
from eng_wad.wad import read_wad, scan_chunks, WadChunk

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

WORK_SUFFIX = "_wadedit"
OBJ_RECORD_FMT = "<3H3i9I2H"   # 58 bytes exactly
OBJ_RECORD_SIZE = struct.calcsize(OBJ_RECORD_FMT)  # == 58

# Colour scheme for the 3D viewport
BG_COLOR        = (17, 19, 23)
TERRAIN_COLOR   = (70, 90, 110)
TERRAIN_EDGE    = (40, 60, 80)
OBJ_COLOR       = (240, 180, 60)
OBJ_SEL_COLOR   = (255, 80, 80)
OBJ_RADIUS      = 6


# ─────────────────────────────────────────────────────────────────────────────
# WAD work-folder
# ─────────────────────────────────────────────────────────────────────────────

class WorkFolder:
    """Manages a temp directory that mirrors a WAD's chunks as individual .bin files.

    Layout on disk:
        {wad_stem}_wadedit/
            manifest.json          — metadata
            chunk_000_INFO.bin     — chunk data (no 8-byte header)
            chunk_001_VERS.bin
            ...
    """

    def __init__(self, wad_path: Path) -> None:
        self.wad_path = wad_path
        self.work_dir = wad_path.parent / (wad_path.stem + WORK_SUFFIX)
        self.manifest_path = self.work_dir / "manifest.json"
        self.entries: list[dict] = []

    # ── extract ──────────────────────────────────────────────────────────────

    def extract(self, wad_data: bytes, chunks: list[WadChunk]) -> None:
        """Split WAD into per-chunk .bin files and write manifest.json."""
        self.work_dir.mkdir(parents=True, exist_ok=True)
        self.entries = []

        for i, chunk in enumerate(chunks):
            # Sanitise tag for use in filenames
            safe = "".join(c if (c.isalnum() or c in "_-") else "_" for c in chunk.tag).strip("_") or "UNK"
            bin_name = f"chunk_{i:03d}_{safe}.bin"
            # chunk.offset already points PAST the 8-byte (reversed-tag + size) header
            chunk_data = wad_data[chunk.offset: chunk.offset + chunk.size]
            (self.work_dir / bin_name).write_bytes(chunk_data)
            self.entries.append({
                "index": i,
                "tag": chunk.tag,
                "original_offset": chunk.offset,
                "original_size": chunk.size,
                "bin_file": bin_name,
            })

        self._save_manifest()

    def _save_manifest(self) -> None:
        manifest = {
            "wad_source": str(self.wad_path),
            "chunks": self.entries,
        }
        self.manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    # ── load ─────────────────────────────────────────────────────────────────

    def load(self) -> bool:
        """Load from an existing manifest (no WAD needed)."""
        if not self.manifest_path.exists():
            return False
        try:
            data = json.loads(self.manifest_path.read_text(encoding="utf-8"))
            self.entries = data.get("chunks", [])
            return bool(self.entries)
        except Exception:
            return False

    # ── access ───────────────────────────────────────────────────────────────

    def get_chunk_data(self, tag: str) -> bytes | None:
        """Return data of the first chunk with the given tag, or None."""
        for e in self.entries:
            if e["tag"] == tag:
                p = self.work_dir / e["bin_file"]
                return p.read_bytes() if p.exists() else None
        return None

    def save_chunk_data(self, tag: str, data: bytes) -> bool:
        """Overwrite the .bin for the first matching tag. Returns success."""
        for e in self.entries:
            if e["tag"] == tag:
                (self.work_dir / e["bin_file"]).write_bytes(data)
                return True
        return False

    def chunk_info(self) -> list[dict]:
        """Return entries augmented with current .bin file size."""
        out = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            size = p.stat().st_size if p.exists() else 0
            out.append({**e, "current_size": size})
        return out

    # ── pack ─────────────────────────────────────────────────────────────────

    def pack_wad(self, out_path: Path) -> None:
        """Re-assemble all chunk .bin files into a valid WAD at *out_path*."""
        # Build chunk payloads first so we know the total size
        chunk_blocks: list[tuple[str, bytes]] = []
        for e in self.entries:
            p = self.work_dir / e["bin_file"]
            cdata = p.read_bytes() if p.exists() else b""
            chunk_blocks.append((e["tag"], cdata))

        # WAD layout: u32(total_size-4) then chunks
        # tag is stored reversed (little-endian), then u32 size, then data
        total = 4  # the leading size word counts itself
        for _tag, cdata in chunk_blocks:
            total += 8 + len(cdata)

        out_path.parent.mkdir(parents=True, exist_ok=True)
        with out_path.open("wb") as f:
            f.write(struct.pack("<I", total - 4))
            for tag, cdata in chunk_blocks:
                tag_b = tag.encode("ascii", errors="replace")[:4].ljust(4, b"\x00")
                f.write(bytes(reversed(tag_b)))       # stored reversed
                f.write(struct.pack("<I", len(cdata)))
                f.write(cdata)

    @property
    def is_open(self) -> bool:
        return bool(self.entries)


# ─────────────────────────────────────────────────────────────────────────────
# MAP object patching
# ─────────────────────────────────────────────────────────────────────────────

def pack_map_object(obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    """Serialise a MapObjectRecord back to its 58-byte on-disk form."""
    return struct.pack(
        OBJ_RECORD_FMT,
        obj.rot_x_units, obj.rot_y_units, obj.rot_z_units,
        obj.pos_x_fixed12, obj.pos_y_fixed12, obj.pos_z_fixed12,
        obj.script_offset, obj.local_count, obj.section2_index_raw,
        obj.stack_word_count, obj.stack_arg_count, obj.spawn_flags,
        obj.extra_count, obj.section4_index_raw, obj.spawn_aux_raw,
        obj.flags, obj.extra_u16,
    )


def patch_map_chunk_object(map_data: bytes, obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    """Return a new MAP chunk bytes with *obj* written back at its file_offset."""
    packed = pack_map_object(obj)
    data = bytearray(map_data)
    off = obj.file_offset
    data[off: off + OBJ_RECORD_SIZE] = packed
    return bytes(data)


# ─────────────────────────────────────────────────────────────────────────────
# Scene geometry
# ─────────────────────────────────────────────────────────────────────────────

def _fixed12_signed(v: int) -> float:
    iv = struct.unpack("<i", struct.pack("<I", v & 0xFFFFFFFF))[0]
    return iv / 4096.0


def _rotate_xz(x: float, z: float, a: float) -> tuple[float, float]:
    c, s = math.cos(a), math.sin(a)
    return x * c - z * s, x * s + z * c


class SceneData:
    """Holds terrain triangles and object positions for 3D rendering."""

    def __init__(self) -> None:
        # terrain: list of (tri_verts_3x3, shade)  where tri_verts = [[x,y,z],[x,y,z],[x,y,z]]
        self.terrain_tris: list[tuple[list, float]] = []
        # objects: list of [x, y, z]
        self.object_positions: list[list[float]] = []
        self.bounds: tuple[float, float, float, float, float, float] = (0, 0, 0, 1, 1, 1)

    def build(self, mapx: "MapFullExe", trak: "TrakFile", *, terrain_yaw_sign: int = 1) -> None:  # type: ignore[name-defined]
        """Build geometry from parsed MAP + TRAK data."""
        self.terrain_tris.clear()
        self.object_positions.clear()

        xs: list[float] = []
        ys: list[float] = []
        zs: list[float] = []

        # ── terrain ──────────────────────────────────────────────────────────
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
                td = mapx.tile_defs[tile_i]
                tx = _fixed12_signed(td.u32_12)
                ty = _fixed12_signed(td.u32_16)
                tz = -_fixed12_signed(td.u32_20)
                yaw_units = td.u32_04 & 0xFFFF
            else:
                tx, ty, tz = tile.x, tile.y, tile.z
                yaw_units = 0

            yaw = terrain_yaw_sign * (yaw_units / 4096.0) * math.tau if yaw_units else 0.0

            placed: list[list[float]] = []
            for v in rec.table_a:
                rx, rz = _rotate_xz(v.x, v.z, yaw) if yaw else (v.x, v.z)
                raw_z = tz + rz
                px, py, pz = tx + rx, ty + v.y, -raw_z  # flip_z=True matches world_rebuild default
                placed.append([px, py, pz])
                xs.append(px); ys.append(py); zs.append(pz)

            for tri in rec.table_b:
                if not (tri.i0 < len(placed) and tri.i1 < len(placed) and tri.i2 < len(placed)):
                    continue
                if len({tri.i0, tri.i1, tri.i2}) != 3:
                    continue
                verts = [placed[tri.i0], placed[tri.i1], placed[tri.i2]]
                # Shade by y-centroid for simple lighting
                cy = (verts[0][1] + verts[1][1] + verts[2][1]) / 3.0
                self.terrain_tris.append((verts, cy))

        # ── objects ──────────────────────────────────────────────────────────
        for obj in mapx.objects:
            ox = obj.pos_x_fixed12 / 4096.0
            oy = obj.pos_y_fixed12 / 4096.0
            oz = obj.pos_z_fixed12 / 4096.0
            self.object_positions.append([ox, oy, oz])
            xs.append(ox); ys.append(oy); zs.append(oz)

        if xs:
            self.bounds = (min(xs), min(ys), min(zs), max(xs), max(ys), max(zs))
        else:
            self.bounds = (0, 0, 0, 1, 1, 1)

    @property
    def center(self) -> tuple[float, float, float]:
        bx0, by0, bz0, bx1, by1, bz1 = self.bounds
        return (bx0 + bx1) * 0.5, (by0 + by1) * 0.5, (bz0 + bz1) * 0.5

    @property
    def span(self) -> float:
        bx0, by0, bz0, bx1, by1, bz1 = self.bounds
        return max(bx1 - bx0, by1 - by0, bz1 - bz0, 1.0)


# ─────────────────────────────────────────────────────────────────────────────
# Camera
# ─────────────────────────────────────────────────────────────────────────────

class Camera:
    """Spherical/orbital camera: centre + distance + yaw + pitch."""

    def __init__(self) -> None:
        self.cx: float = 0.0
        self.cy: float = 0.0
        self.cz: float = 0.0
        self.distance: float = 100.0
        self.yaw: float = 0.5         # radians
        self.pitch: float = 0.4       # radians (positive = look down)
        self.fov: float = 60.0        # degrees

    def reset_to_scene(self, scene: SceneData) -> None:
        self.cx, self.cy, self.cz = scene.center
        self.distance = scene.span * 1.5
        self.yaw = 0.5
        self.pitch = 0.4

    def eye(self) -> tuple[float, float, float]:
        """Return camera eye position in world space."""
        sp, cp = math.sin(self.pitch), math.cos(self.pitch)
        sy, cy = math.sin(self.yaw), math.cos(self.yaw)
        ex = self.cx + self.distance * cp * sy
        ey = self.cy + self.distance * sp
        ez = self.cz + self.distance * cp * cy
        return ex, ey, ez

    def orbit(self, dyaw: float, dpitch: float) -> None:
        self.yaw += dyaw
        self.pitch = max(-1.4, min(1.4, self.pitch + dpitch))

    def pan(self, dx: float, dy: float) -> None:
        """Pan in the camera's horizontal + vertical plane."""
        sy, cy = math.sin(self.yaw), math.cos(self.yaw)
        # right vector (perp to view dir in XZ)
        rx, rz = cy, -sy
        # up vector (approx world-Y corrected)
        sp, cp = math.sin(self.pitch), math.cos(self.pitch)
        ux, uy, uz = -sy * sp, cp, -cy * sp
        scale = self.distance * 0.001
        self.cx -= (dx * rx - dy * ux) * scale
        self.cy -= dy * uy * scale
        self.cz -= (dx * rz - dy * uz) * scale

    def zoom(self, factor: float) -> None:
        self.distance = max(0.01, self.distance * factor)


# ─────────────────────────────────────────────────────────────────────────────
# Renderer
# ─────────────────────────────────────────────────────────────────────────────

def _project_points(
    points: list[list[float]],
    cam: Camera,
    w: int, h: int,
) -> list[tuple[float, float, float]] | None:
    """Project world-space [x,y,z] → (screen_x, screen_y, depth).

    Returns None if any point is behind the camera.
    """
    ex, ey, ez = cam.eye()
    fx, fy, fz = cam.cx - ex, cam.cy - ey, cam.cz - ez
    fl = math.sqrt(fx * fx + fy * fy + fz * fz)
    if fl < 1e-9:
        return None
    fx /= fl; fy /= fl; fz /= fl

    # right = forward × world_up
    rx = fy * 0 - fz * 1
    ry = fz * 0 - fx * 0
    rz = fx * 1 - fy * 0
    rl = math.sqrt(rx * rx + rz * rz) or 1e-9
    rx /= rl; rz /= rl
    # up = right × forward
    ux = ry * fz - rz * fy
    uy = rz * fx - rx * fz
    uz = rx * fy - ry * fx

    half_fov = math.tan(math.radians(cam.fov * 0.5))
    aspect = w / max(h, 1)
    f = min(w, h) * 0.5 / half_fov

    results = []
    for p in points:
        dx, dy, dz = p[0] - ex, p[1] - ey, p[2] - ez
        depth = dx * fx + dy * fy + dz * fz
        if depth < 0.001:
            return None
        px2 = (dx * rx + dy * ry + dz * rz) / depth
        py2 = (dx * ux + dy * uy + dz * uz) / depth
        sx = w * 0.5 + px2 * f
        sy = h * 0.5 - py2 * f
        results.append((sx, sy, depth))
    return results


def render_scene(
    scene: SceneData,
    cam: Camera,
    w: int, h: int,
    selected_obj: int | None = None,
) -> "Image.Image":  # type: ignore[name-defined]
    """Render scene to a PIL Image using painter's algorithm."""
    if not HAS_PIL:
        raise RuntimeError("Pillow not installed")

    img = Image.new("RGB", (w, h), BG_COLOR)
    draw = ImageDraw.Draw(img)

    if not scene.terrain_tris and not scene.object_positions:
        draw.text((10, 10), "No scene geometry", fill=(180, 180, 180))
        return img

    # Normalise shade by y-centroid
    if scene.terrain_tris:
        all_cy = [cy for _, cy in scene.terrain_tris]
        cy_min, cy_range = min(all_cy), max(max(all_cy) - min(all_cy), 1.0)
    else:
        cy_min, cy_range = 0.0, 1.0

    # ── collect draw commands sorted by depth ────────────────────────────────
    drawlist: list[tuple[float, str, Any]] = []   # (depth, kind, payload)

    for verts, cy in scene.terrain_tris:
        proj = _project_points(verts, cam, w, h)
        if proj is None:
            continue
        depth = (proj[0][2] + proj[1][2] + proj[2][2]) / 3.0
        poly = [(proj[i][0], proj[i][1]) for i in range(3)]
        t = (cy - cy_min) / cy_range          # 0..1
        r = int(TERRAIN_COLOR[0] * (0.4 + 0.6 * t))
        g = int(TERRAIN_COLOR[1] * (0.4 + 0.6 * t))
        b = int(TERRAIN_COLOR[2] * (0.4 + 0.6 * t))
        drawlist.append((depth, "tri", (poly, (r, g, b))))

    for i, pos in enumerate(scene.object_positions):
        proj = _project_points([pos], cam, w, h)
        if proj is None:
            continue
        sx, sy, depth = proj[0]
        color = OBJ_SEL_COLOR if i == selected_obj else OBJ_COLOR
        drawlist.append((depth, "obj", (sx, sy, color, i)))

    # Painter's: farthest first
    drawlist.sort(key=lambda x: -x[0])

    for _, kind, payload in drawlist:
        if kind == "tri":
            poly, fill = payload
            try:
                draw.polygon(poly, fill=fill, outline=TERRAIN_EDGE)
            except Exception:
                pass
        elif kind == "obj":
            sx, sy, color, idx = payload
            r = OBJ_RADIUS
            draw.ellipse((sx - r, sy - r, sx + r, sy + r), fill=color, outline=(255, 255, 255))
            draw.text((sx + r + 2, sy - 6), str(idx), fill=color)

    return img


# ─────────────────────────────────────────────────────────────────────────────
# WorldCanvas — 3D viewport widget
# ─────────────────────────────────────────────────────────────────────────────

class WorldCanvas(ttk.Frame):
    """tkinter Frame that hosts a PIL-rendered 3D viewport."""

    def __init__(self, master: tk.Widget, on_select: Any = None) -> None:
        super().__init__(master)
        self._on_select = on_select
        self.scene = SceneData()
        self.cam = Camera()
        self.selected_obj: int | None = None
        self._tk_img: tk.PhotoImage | None = None
        self._drag_start: tuple[int, int] | None = None
        self._drag_mode: str = "orbit"     # "orbit" | "pan"
        self._no_pil_warned = False

        self._canvas = tk.Canvas(self, bg="#111317", highlightthickness=0, cursor="crosshair")
        self._canvas.pack(fill="both", expand=True)

        self._canvas.bind("<Configure>", self._on_resize)
        self._canvas.bind("<ButtonPress-1>",   self._on_lbdown)
        self._canvas.bind("<B1-Motion>",       self._on_lbdrag)
        self._canvas.bind("<ButtonRelease-1>", self._on_lbup)
        self._canvas.bind("<ButtonPress-2>",   self._on_mbdown)
        self._canvas.bind("<B2-Motion>",       self._on_mbdrag)
        self._canvas.bind("<ButtonPress-3>",   self._on_rbdown)
        self._canvas.bind("<B3-Motion>",       self._on_rbdrag)
        self._canvas.bind("<MouseWheel>",       self._on_wheel)
        self._canvas.bind("<Button-4>",         lambda e: self._on_wheel(e, -1))
        self._canvas.bind("<Button-5>",         lambda e: self._on_wheel(e, 1))

    def load_scene(self, scene: SceneData) -> None:
        self.scene = scene
        self.cam.reset_to_scene(scene)
        self.selected_obj = None
        self.redraw()

    def select_object(self, idx: int | None) -> None:
        self.selected_obj = idx
        self.redraw()

    def redraw(self) -> None:
        w = self._canvas.winfo_width()
        h = self._canvas.winfo_height()
        if w < 4 or h < 4:
            return
        self._canvas.delete("all")

        if not HAS_PIL:
            if not self._no_pil_warned:
                self._no_pil_warned = True
            self._canvas.create_text(w // 2, h // 2,
                text="Install Pillow (pip install Pillow) for 3D view",
                fill="#ff8080", font=("Consolas", 12))
            self._draw_fallback_2d(w, h)
            return

        try:
            img = render_scene(self.scene, self.cam, w, h, self.selected_obj)
            # Keep a reference to prevent GC — important for tkinter
            self._tk_img = ImageTk.PhotoImage(img)
            self._canvas.create_image(0, 0, image=self._tk_img, anchor="nw")
        except Exception as exc:
            self._canvas.create_text(10, 10, text=f"Render error: {exc}", fill="red", anchor="nw")
            self._draw_fallback_2d(w, h)

    def _draw_fallback_2d(self, w: int, h: int) -> None:
        """Simple 2D top-down fallback when PIL is unavailable."""
        objs = self.scene.object_positions
        if not objs:
            return
        xs = [p[0] for p in objs]
        zs = [p[2] for p in objs]
        mn_x, mx_x = min(xs), max(xs)
        mn_z, mx_z = min(zs), max(zs)
        span_x = max(mx_x - mn_x, 1.0)
        span_z = max(mx_z - mn_z, 1.0)
        pad = 20
        for i, p in enumerate(objs):
            sx = pad + (p[0] - mn_x) / span_x * (w - pad * 2)
            sy = pad + (p[2] - mn_z) / span_z * (h - pad * 2)
            color = "#ff5050" if i == self.selected_obj else "#f0b440"
            self._canvas.create_oval(sx - 4, sy - 4, sx + 4, sy + 4, fill=color, outline="")

    # ── mouse event helpers ───────────────────────────────────────────────────

    def _on_resize(self, _e: tk.Event) -> None:
        self.redraw()

    def _on_lbdown(self, e: tk.Event) -> None:
        self._drag_start = (e.x, e.y)
        self._drag_mode = "orbit"

    def _on_lbdrag(self, e: tk.Event) -> None:
        if self._drag_start is None:
            return
        dx = e.x - self._drag_start[0]
        dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.orbit(dx * 0.008, -dy * 0.008)
        self.redraw()

    def _on_lbup(self, e: tk.Event) -> None:
        self._drag_start = None

    def _on_mbdown(self, e: tk.Event) -> None:
        self._drag_start = (e.x, e.y)
        self._drag_mode = "pan"

    def _on_mbdrag(self, e: tk.Event) -> None:
        if self._drag_start is None:
            return
        dx = e.x - self._drag_start[0]
        dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.pan(dx, dy)
        self.redraw()

    def _on_rbdown(self, e: tk.Event) -> None:
        self._drag_start = (e.x, e.y)

    def _on_rbdrag(self, e: tk.Event) -> None:
        if self._drag_start is None:
            return
        dy = e.y - self._drag_start[1]
        self._drag_start = (e.x, e.y)
        self.cam.zoom(1.0 + dy * 0.01)
        self.redraw()

    def _on_wheel(self, e: tk.Event, direction: int = 0) -> None:
        delta = direction or (1 if e.delta < 0 else -1)
        self.cam.zoom(1.12 if delta > 0 else 0.88)
        self.redraw()


# ─────────────────────────────────────────────────────────────────────────────
# Object edit dialog
# ─────────────────────────────────────────────────────────────────────────────

class ObjectEditDialog(tk.Toplevel):
    """Modal dialog to view and edit a single MapObjectRecord."""

    FIELDS = [
        # (field_name, label,              kind)
        # kind: "f12"=fixed12 float, "deg4096"=angle, "hex"=hex u32, "u32"=unsigned, "i32"=signed
        ("pos_x_fixed12",    "Pos X (fixed12 → world)",  "f12"),
        ("pos_y_fixed12",    "Pos Y (fixed12 → world)",  "f12"),
        ("pos_z_fixed12",    "Pos Z (fixed12 → world)",  "f12"),
        ("rot_x_units",      "Rot X (4096=full)",        "deg4096"),
        ("rot_y_units",      "Rot Y (4096=full)",        "deg4096"),
        ("rot_z_units",      "Rot Z (4096=full)",        "deg4096"),
        ("script_offset",    "Script offset (u32 hex)",  "hex"),
        ("local_count",      "Local count",              "u32"),
        ("section2_index_raw","Section2 index (raw)",    "u32"),
        ("stack_word_count", "Stack word count",         "u32"),
        ("stack_arg_count",  "Stack arg count",          "u32"),
        ("spawn_flags",      "Spawn flags (hex)",        "hex"),
        ("extra_count",      "Extra count",              "u32"),
        ("section4_index_raw","Section4 index (raw)",    "u32"),
        ("spawn_aux_raw",    "Spawn aux (raw u32)",      "u32"),
        ("flags",            "Flags (u16 hex)",          "hex"),
        ("extra_u16",        "Extra u16",                "u32"),
    ]

    def __init__(self, parent: tk.Widget, obj: "MapObjectRecord", on_save: Any = None) -> None:  # type: ignore[name-defined]
        super().__init__(parent)
        self.title(f"Edit Object #{obj.index}")
        self.resizable(False, False)
        self.grab_set()
        self._obj = obj
        self._on_save = on_save
        self._vars: dict[str, tk.StringVar] = {}
        self._build(obj)

    def _build(self, obj: Any) -> None:
        frm = ttk.Frame(self, padding=10)
        frm.pack(fill="both", expand=True)

        ttk.Label(frm, text=f"Object #{obj.index}  file_offset=0x{obj.file_offset:X}",
                  font=("Consolas", 10, "bold")).grid(row=0, column=0, columnspan=3, sticky="w", pady=(0, 8))

        for row, (fname, label, kind) in enumerate(self.FIELDS, start=1):
            raw_val = getattr(obj, fname)
            if kind == "f12":
                display = f"{raw_val / 4096.0:.6f}"
            elif kind == "deg4096":
                display = str(raw_val)
            elif kind == "hex":
                display = f"0x{raw_val:08X}"
            else:
                display = str(raw_val)

            ttk.Label(frm, text=label, width=28, anchor="w").grid(row=row, column=0, sticky="w", padx=(0, 8))
            var = tk.StringVar(value=display)
            self._vars[fname] = var
            ttk.Entry(frm, textvariable=var, width=20).grid(row=row, column=1, sticky="ew")

            hint = {"f12": "world = value/4096", "deg4096": "360°=4096 units",
                    "hex": "hex or decimal OK", "u32": "unsigned int"}.get(kind, "")
            ttk.Label(frm, text=hint, foreground="#888").grid(row=row, column=2, sticky="w", padx=(6, 0))

        frm.columnconfigure(1, weight=1)

        btns = ttk.Frame(self, padding=(10, 0, 10, 10))
        btns.pack(fill="x")
        ttk.Button(btns, text="Save & Close", command=self._save).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel",       command=self.destroy).pack(side="right")

    def _parse_val(self, fname: str, kind: str, text: str) -> int | None:
        text = text.strip()
        try:
            if kind == "f12":
                # Accept either a float (world coords) or plain int (raw fixed12)
                f = float(text)
                return int(round(f * 4096))
            elif kind == "hex":
                return int(text, 0)
            else:
                return int(text, 0)
        except ValueError:
            return None

    def _save(self) -> None:
        updates: dict[str, int] = {}
        for fname, label, kind in self.FIELDS:
            text = self._vars[fname].get()
            val = self._parse_val(fname, kind, text)
            if val is None:
                messagebox.showerror("Parse error", f"Cannot parse '{label}': {text!r}", parent=self)
                return
            updates[fname] = val

        # Apply all updates to the object (dataclass is mutable, setattr works)
        for fname, val in updates.items():
            setattr(self._obj, fname, val)

        if self._on_save:
            self._on_save(self._obj)
        self.destroy()


# ─────────────────────────────────────────────────────────────────────────────
# Chunk overview panel
# ─────────────────────────────────────────────────────────────────────────────

def _quick_element_count(tag: str, data: bytes) -> str:
    """Best-effort element count from chunk header bytes."""
    try:
        if tag == "MAP " and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} tiles"
        if tag == "TRAK" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} records"
        if tag == "STPC" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} defs"
        if tag == "SMPC" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} sounds"
        if tag == "AMPC" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} ambients"
        if tag == "LGHT" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} lights"
        if tag == "TEXT" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} textures"
        if tag == "LGPC" and len(data) >= 4:
            n = struct.unpack_from("<I", data, 0)[0]
            return f"{n} lines"
    except Exception:
        pass
    return "—"


# ─────────────────────────────────────────────────────────────────────────────
# Main application
# ─────────────────────────────────────────────────────────────────────────────

class WadEditorApp(tk.Tk):

    def __init__(self) -> None:
        super().__init__()
        self.title("ENG WAD Editor")
        self.geometry("1400x860")
        self.minsize(1050, 680)

        # State
        self.work: WorkFolder | None = None
        self._wad_path: Path | None = None
        self._wad_data: bytes = b""
        self._mapx: "MapFullExe | None" = None  # type: ignore[name-defined]
        self._trak: "TrakFile | None" = None     # type: ignore[name-defined]
        self._scene = SceneData()
        self._objects: list["MapObjectRecord"] = []  # type: ignore[name-defined]
        self._selected_obj: int | None = None

        self._build_ui()

    # ── UI construction ──────────────────────────────────────────────────────

    def _build_ui(self) -> None:
        # ── toolbar ──────────────────────────────────────────────────────────
        tb = ttk.Frame(self, padding=(8, 6))
        tb.pack(fill="x")

        ttk.Button(tb, text="📂 Open WAD",  command=self._open_wad_dialog).pack(side="left")
        ttk.Button(tb, text="💾 Save WAD",  command=self._save_wad_dialog).pack(side="left", padx=(6, 0))
        ttk.Button(tb, text="Save As…",     command=self._save_wad_as_dialog).pack(side="left", padx=(6, 0))
        ttk.Separator(tb, orient="vertical").pack(side="left", fill="y", padx=8)
        ttk.Button(tb, text="Reload Scene", command=self._reload_scene).pack(side="left")

        self._status = tk.StringVar(value="Open a WAD file to begin.")
        ttk.Label(tb, textvariable=self._status, anchor="w").pack(side="left", padx=14, fill="x", expand=True)

        # ── notebook ─────────────────────────────────────────────────────────
        self._nb = ttk.Notebook(self)
        self._nb.pack(fill="both", expand=True, padx=8, pady=(0, 8))

        # tab 0 — Overview
        self._tab_overview = ttk.Frame(self._nb)
        self._nb.add(self._tab_overview, text="Overview")
        self._build_overview_tab()

        # tab 1 — World (3D + object list)
        self._tab_world = ttk.Frame(self._nb)
        self._nb.add(self._tab_world, text="World")
        self._build_world_tab()

        # tab 2 — Log
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

        # Left: info text
        left = ttk.Frame(pane)
        pane.add(left, weight=2)
        self._info_text = tk.Text(left, wrap="word", height=8, font=("Consolas", 9))
        self._info_text.pack(fill="both", expand=True)
        self._info_text.insert("end", "No WAD loaded.\n")
        self._info_text.config(state="disabled")

        # Right: chunk Treeview
        right = ttk.Frame(pane)
        pane.add(right, weight=3)

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

        btns = ttk.Frame(right)
        btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Open chunk folder", command=self._open_chunk_folder).pack(side="left")
        ttk.Button(btns, text="Reload chunk file", command=self._reload_selected_chunk).pack(side="left", padx=(6, 0))

    def _build_world_tab(self) -> None:
        pane = ttk.PanedWindow(self._tab_world, orient="horizontal")
        pane.pack(fill="both", expand=True, padx=8, pady=8)

        # Left: 3D viewport
        vp_frame = ttk.LabelFrame(pane, text="3D View  (LMB orbit · MMB pan · RMB/wheel zoom)")
        pane.add(vp_frame, weight=3)
        self._world_canvas = WorldCanvas(vp_frame, on_select=self._on_viewport_obj_click)
        self._world_canvas.pack(fill="both", expand=True)

        # Right: object list + edit
        right = ttk.Frame(pane)
        pane.add(right, weight=1)

        ttk.Label(right, text="MAP Objects", font=("", 10, "bold")).pack(anchor="w")

        obj_cols = ("idx", "x", "y", "z", "rot_y", "s2_idx")
        self._obj_tree = ttk.Treeview(right, columns=obj_cols, show="headings", height=24)
        hdrs = {"idx": "#", "x": "X", "y": "Y", "z": "Z", "rot_y": "Rot Y", "s2_idx": "Sec2"}
        ws = {"idx": 36, "x": 80, "y": 80, "z": 80, "rot_y": 60, "s2_idx": 60}
        for c in obj_cols:
            self._obj_tree.heading(c, text=hdrs[c])
            self._obj_tree.column(c, width=ws[c], anchor="e")
        self._obj_tree.bind("<<TreeviewSelect>>", self._on_obj_tree_select)

        vsb2 = ttk.Scrollbar(right, orient="vertical", command=self._obj_tree.yview)
        self._obj_tree.configure(yscrollcommand=vsb2.set)
        vsb2.pack(side="right", fill="y")
        self._obj_tree.pack(fill="both", expand=True)

        btns = ttk.Frame(right)
        btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Edit Selected",  command=self._edit_selected_obj).pack(side="left")
        ttk.Button(btns, text="Focus Camera",   command=self._focus_selected_obj).pack(side="left", padx=(6, 0))

        hints = ttk.Label(right,
            text="Edit saves directly to MAP .bin\n(use Save WAD to write back to file)",
            foreground="#888", justify="left")
        hints.pack(anchor="w", pady=(6, 0))

    # ── Open / Save ──────────────────────────────────────────────────────────

    def _open_wad_dialog(self) -> None:
        path = filedialog.askopenfilename(
            title="Open WAD",
            filetypes=[("WAD files", "*.wad *.WAD"), ("All files", "*.*")],
        )
        if path:
            self._open_wad(Path(path))

    def _open_wad(self, path: Path) -> None:
        self._log_line(f"Opening {path} …")
        try:
            data, chunks, _ = read_wad(path)
        except Exception as exc:
            messagebox.showerror("Open failed", str(exc))
            return

        self._wad_path = path
        self._wad_data = data

        # Extract to work folder
        work = WorkFolder(path)
        work.extract(data, chunks)
        self.work = work
        self._log_line(f"Extracted {len(chunks)} chunks to {work.work_dir}")

        self._status.set(f"{path.name}  ({len(data):,} B  ·  {len(chunks)} chunks)  — work folder: {work.work_dir.name}")
        self.title(f"ENG WAD Editor — {path.name}")

        self._refresh_overview()
        self._load_game_data()
        self._reload_scene()

    def _save_wad_dialog(self) -> None:
        if not self.work or not self._wad_path:
            messagebox.showinfo("No WAD open", "Open a WAD file first.")
            return
        if messagebox.askyesno("Overwrite?", f"Overwrite original file?\n{self._wad_path}"):
            self._do_save(self._wad_path)

    def _save_wad_as_dialog(self) -> None:
        if not self.work:
            messagebox.showinfo("No WAD open", "Open a WAD file first.")
            return
        path = filedialog.asksaveasfilename(
            title="Save WAD as…",
            defaultextension=".wad",
            filetypes=[("WAD files", "*.wad"), ("All files", "*.*")],
            initialfile=self._wad_path.name if self._wad_path else "output.wad",
        )
        if path:
            self._do_save(Path(path))

    def _do_save(self, out_path: Path) -> None:
        try:
            self.work.pack_wad(out_path)
            self._log_line(f"Saved WAD → {out_path}")
            messagebox.showinfo("Saved", str(out_path))
        except Exception as exc:
            messagebox.showerror("Save failed", str(exc))

    # ── Overview tab helpers ─────────────────────────────────────────────────

    def _refresh_overview(self) -> None:
        if not self.work:
            return

        # Update info text
        self._info_text.config(state="normal")
        self._info_text.delete("1.0", "end")
        info = [
            f"Source     : {self._wad_path}",
            f"File size  : {len(self._wad_data):,} bytes",
            f"Chunks     : {len(self.work.entries)}",
            f"Work folder: {self.work.work_dir}",
            "",
            "Controls:",
            "  • Double-click a chunk row to open its .bin in the default editor",
            "  • Edit .bin files externally, then click 'Reload chunk file'",
            "  • Save WAD repacks all .bin files into a new WAD",
        ]
        self._info_text.insert("end", "\n".join(info))
        self._info_text.config(state="disabled")

        # Update chunk tree
        self._chunk_tree.delete(*self._chunk_tree.get_children())
        for info_dict in self.work.chunk_info():
            tag = info_dict["tag"]
            size = info_dict["current_size"]
            p = self.work.work_dir / info_dict["bin_file"]
            data = p.read_bytes() if p.exists() else b""
            elems = _quick_element_count(tag, data)
            self._chunk_tree.insert("", "end", iid=str(info_dict["index"]),
                values=(tag, f"{size:,} B", elems, info_dict["bin_file"]))

        self._chunk_tree.bind("<Double-1>", self._on_chunk_dclick)

    def _open_chunk_folder(self) -> None:
        if self.work:
            import os; os.startfile(str(self.work.work_dir))  # type: ignore[attr-defined]

    def _reload_selected_chunk(self) -> None:
        sel = self._chunk_tree.selection()
        if not sel or not self.work:
            return
        idx = int(sel[0])
        entry = self.work.entries[idx]
        self._log_line(f"Reloaded chunk #{idx} {entry['tag']} from disk.")
        self._refresh_overview()
        # Re-parse if it was MAP or TRAK
        if entry["tag"] in ("MAP ", "TRAK"):
            self._load_game_data()
            self._reload_scene()

    def _on_chunk_dclick(self, _e: tk.Event) -> None:
        sel = self._chunk_tree.selection()
        if not sel or not self.work:
            return
        idx = int(sel[0])
        entry = self.work.entries[idx]
        bin_path = self.work.work_dir / entry["bin_file"]
        import os; os.startfile(str(bin_path))  # type: ignore[attr-defined]

    # ── Game data loading ────────────────────────────────────────────────────

    def _load_game_data(self) -> None:
        """Parse MAP + TRAK from work folder bin files."""
        if not self.work:
            return

        self._mapx = None
        self._trak = None

        if not HAS_TRAK or not HAS_MAP:
            self._log_line("Warning: map_full_chunk / trak_chunk not available.")
            return

        trak_data = self.work.get_chunk_data("TRAK")
        if trak_data is None:
            self._log_line("No TRAK chunk found.")
            return
        try:
            self._trak = parse_trak_chunk(trak_data)
            self._log_line(f"Parsed TRAK: {self._trak.record_count} records")
        except Exception as exc:
            self._log_line(f"TRAK parse error: {exc}")
            return

        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None:
            self._log_line("No MAP chunk found.")
            return

        # Try all four combinations of the two optional-section flags
        parse_ok = False
        for opt20, final_dw in [(True, True), (True, False), (False, True), (False, False)]:
            try:
                self._mapx = parse_map_full_exe(
                    map_data, self._trak,
                    assume_optional20=opt20,
                    assume_final_dword=final_dw,
                )
                parse_ok = True
                self._log_line(
                    f"Parsed MAP: {self._mapx.tile_count} tiles, "
                    f"{len(self._mapx.objects)} objects, "
                    f"{self._mapx.grid_width}×{self._mapx.grid_height} grid  "
                    f"(opt20={opt20}, final_dw={final_dw})"
                )
                break
            except Exception:
                continue

        if not parse_ok:
            self._log_line("MAP parse failed for all flag combinations.")
            return

        self._objects = list(self._mapx.objects)
        if self._mapx.warnings:
            for w in self._mapx.warnings[:5]:
                self._log_line(f"  MAP warning: {w}")

    # ── Scene / viewport ─────────────────────────────────────────────────────

    def _reload_scene(self) -> None:
        if self._mapx and self._trak:
            self._scene.build(self._mapx, self._trak)
            self._world_canvas.load_scene(self._scene)
            self._populate_obj_tree()
        else:
            self._populate_obj_tree()

    def _populate_obj_tree(self) -> None:
        self._obj_tree.delete(*self._obj_tree.get_children())
        for obj in self._objects:
            self._obj_tree.insert("", "end", iid=str(obj.index), values=(
                obj.index,
                f"{obj.pos_x_fixed12 / 4096.0:.2f}",
                f"{obj.pos_y_fixed12 / 4096.0:.2f}",
                f"{obj.pos_z_fixed12 / 4096.0:.2f}",
                obj.rot_y_units,
                obj.section2_index_raw,
            ))

    def _on_obj_tree_select(self, _e: tk.Event) -> None:
        sel = self._obj_tree.selection()
        if not sel:
            return
        idx = int(sel[0])
        self._selected_obj = idx
        self._world_canvas.select_object(idx)

    def _on_viewport_obj_click(self, idx: int) -> None:
        self._selected_obj = idx
        self._obj_tree.selection_set(str(idx))
        self._obj_tree.see(str(idx))

    def _edit_selected_obj(self) -> None:
        if self._selected_obj is None or not self._objects:
            return
        # Find object with that index
        obj = next((o for o in self._objects if o.index == self._selected_obj), None)
        if obj is None:
            return
        ObjectEditDialog(self, obj, on_save=self._on_obj_saved)

    def _focus_selected_obj(self) -> None:
        if self._selected_obj is None or self._selected_obj >= len(self._scene.object_positions):
            return
        pos = self._scene.object_positions[self._selected_obj]
        cam = self._world_canvas.cam
        cam.cx, cam.cy, cam.cz = pos[0], pos[1], pos[2]
        cam.distance = max(cam.distance, self._scene.span * 0.1)
        self._world_canvas.redraw()

    def _on_obj_saved(self, obj: "MapObjectRecord") -> None:  # type: ignore[name-defined]
        """Called by ObjectEditDialog after user saves changes."""
        self._write_obj_to_map_bin(obj)
        self._populate_obj_tree()
        # Rebuild scene so position markers move
        if self._mapx and self._trak:
            # Update in-memory position list too
            pos = self._scene.object_positions
            if obj.index < len(pos):
                pos[obj.index] = [
                    obj.pos_x_fixed12 / 4096.0,
                    obj.pos_y_fixed12 / 4096.0,
                    obj.pos_z_fixed12 / 4096.0,
                ]
        self._world_canvas.redraw()
        self._log_line(f"Object #{obj.index} saved to MAP .bin  "
                       f"pos=({obj.pos_x}, {obj.pos_y}, {obj.pos_z})")

    def _write_obj_to_map_bin(self, obj: "MapObjectRecord") -> None:  # type: ignore[name-defined]
        """Patch the MAP .bin in the work folder with the updated object record."""
        if not self.work:
            return
        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None:
            self._log_line("Cannot patch MAP: chunk not found in work folder.")
            return
        try:
            new_data = patch_map_chunk_object(map_data, obj)
            self.work.save_chunk_data("MAP ", new_data)
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
    app = WadEditorApp()
    if argv and Path(argv[0]).exists():
        app._open_wad(Path(argv[0]))
    app.mainloop()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
