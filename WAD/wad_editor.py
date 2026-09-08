#!/usr/bin/env python3
"""wad_editor.py — Full WAD editor with chunk splitting, 3D world view, and object editing.

Architecture:
  MemoryWad         - keeps editable chunks in RAM until Save WAD
  Camera            — orbital (target + distance + yaw + pitch) with orbit/pan/zoom
  SceneData         — terrain + object geometry; pre-builds numpy arrays for fast rendering
  WorldCanvas       — PIL-backed 3D canvas; throttles redraws to one per event-loop tick
  ObjectEditDialog  — edit all MapObjectRecord fields; type combobox shows all level types
  AddObjectDialog   — pick type + position, optionally clone fields from selection
  WadEditorApp      — main window: Overview | World tabs + save button
"""

from __future__ import annotations

import sys
import tkinter as tk
from pathlib import Path
from tkinter import filedialog, messagebox, ttk
from typing import Any

# ── Project imports ───────────────────────────────────────────────────────────
from eng_wad.chunk_utils import quick_element_count as _quick_element_count
from eng_wad.editor_config import (
    CONFIG_PATH,
    load_editor_config,
    save_editor_config,
)
from eng_wad.editor_dialogs import (
    AddObjectDialog,
    ObjectEditDialog,
    OffsetEditDialog,
    TerrainEditDialog,
)
from eng_wad.editor_terrain_patch import serialize_scene_terrain_edits
from eng_wad.editor_view import SceneData, WorldCanvas
from eng_wad.map_patch import (
    add_object_to_map_chunk,
    build_type_registry,
    delete_object_from_map_chunk,
    make_object_copy,
    pack_map_object,
    patch_map_chunk_object,
    patch_map_section2_locals,
)
from eng_wad.section2_semantics import section2_schema
from eng_wad.memory_wad import MemoryWad
from eng_wad.stpc_names import build_stpc_name_map
from eng_wad.stpc_chunk import parse_stpc_meshes_from_bytes
from eng_wad.wad import read_wad
from eng_wad.world_rebuild import build_primary_stpc_object_triangles

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
# Main application

class WadEditorApp(tk.Tk):

    def __init__(self) -> None:
        super().__init__()
        self.title("ENG WAD Editor")
        self.geometry("1400x860")
        self.minsize(1050, 680)

        self.work: MemoryWad | None = None
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
        self._stpc_mesh_result: Any = None
        self._stpc_mesh_source: bytes | None = None
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
        self.bind("<Escape>", self._on_escape)

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
        cols = ("tag", "size", "elements", "storage")
        self._chunk_tree = ttk.Treeview(right, columns=cols, show="headings")
        widths = {"tag": 70, "size": 100, "elements": 120, "storage": 260}
        for c in cols:
            self._chunk_tree.heading(c, text=c)
            self._chunk_tree.column(c, width=widths[c], anchor="w")
        vsb = ttk.Scrollbar(right, orient="vertical", command=self._chunk_tree.yview)
        self._chunk_tree.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        self._chunk_tree.pack(fill="both", expand=True)
        btns = ttk.Frame(right); btns.pack(fill="x", pady=(4, 0))
        ttk.Button(btns, text="Storage Info", command=self._open_chunk_folder).pack(side="left")
        ttk.Button(btns, text="Reload Original WAD", command=self._reload_selected_chunk).pack(
            side="left", padx=(6, 0))

    def _build_world_tab(self) -> None:
        pane = ttk.PanedWindow(self._tab_world, orient="horizontal")
        pane.pack(fill="both", expand=True, padx=8, pady=8)

        vp_frame = ttk.LabelFrame(pane, text="3D View  (LMB orbit · MMB pan · RMB/wheel zoom)")
        pane.add(vp_frame, weight=3)
        self._world_canvas = WorldCanvas(
            vp_frame,
            on_select=self._on_canvas_object_select,
            mode="object",
            cfg=self._editor_config,
        )
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
        ttk.Button(btns, text="Rebuild Meshes",
                   command=self._start_object_mesh_export).pack(side="left", padx=(4,0))

        ttk.Label(right,
            text="Edits patch the MAP chunk in RAM.\nSave WAD to write back.",
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
        self._terrain_canvas.set_terrain_move_callback(self._on_canvas_terrain_moved)
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
            text="Terrain edits patch MAP/TRAK in RAM. Save WAD to write back.",
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
        work = MemoryWad(path)
        work.extract(data, chunks)
        self.work = work
        self._stpc_mesh_result = None
        self._stpc_mesh_source = None
        self._log_line(f"Loaded {len(chunks)} chunks into RAM (no temp files created)")
        self._status.set(f"{path.name}  ({len(data):,} B - {len(chunks)} chunks) - RAM mode")
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
            self._serialize_world_edits()
            self.work.pack_wad(out_path)
            self._log_line(f"Saved WAD → {out_path}")
            messagebox.showinfo("Saved", str(out_path))
        except Exception as exc:
            messagebox.showerror("Save failed", str(exc))

    def _serialize_world_edits(self) -> None:
        if not (self.work and self._mapx and self._trak):
            return
        map_data = self.work.get_chunk_data("MAP ")
        trak_data = self.work.get_chunk_data("TRAK")
        if map_data is None or trak_data is None:
            return
        result = serialize_scene_terrain_edits(
            self._scene, self._mapx, self._trak, map_data, trak_data)
        if result.map_changed:
            self.work.save_chunk_data("MAP ", result.map_data)
        if result.trak_changed:
            self.work.save_chunk_data("TRAK", result.trak_data)
        if result.changed:
            self._populate_terrain_tree()
            self._terrain_canvas.redraw()
            self._world_canvas.redraw()
            self._log_line(
                "Serialized terrain edits: "
                f"{result.moved_tiles} chunks, "
                f"{result.patched_vertices} vertices, "
                f"{result.patched_planes} planes")

    # ── Overview ─────────────────────────────────────────────────────────────

    def _refresh_overview(self) -> None:
        if not self.work: return
        self._info_text.config(state="normal")
        self._info_text.delete("1.0", "end")
        self._info_text.insert("end", "\n".join([
            f"Source     : {self._wad_path}",
            f"File size  : {len(self._wad_data):,} bytes",
            f"Chunks     : {len(self.work.entries)}",
            "Storage    : RAM only (no chunk files/extracted folder)",
            "", "Tips:",
            "  - Double-click a chunk row to preview its bytes",
            "  - Edits stay in memory until Save WAD / Save As",
        ]))
        self._info_text.config(state="disabled")
        self._chunk_tree.delete(*self._chunk_tree.get_children())
        for info_dict in self.work.chunk_info():
            tag  = info_dict["tag"]
            size = info_dict["current_size"]
            data = self.work.get_chunk_data_by_index(info_dict["index"]) or b""
            self._chunk_tree.insert("", "end", iid=str(info_dict["index"]),
                values=(tag, f"{size:,} B", _quick_element_count(tag, data), info_dict["bin_file"]))
        self._chunk_tree.bind("<Double-1>", self._on_chunk_dclick)

    def _open_chunk_folder(self) -> None:
        messagebox.showinfo(
            "RAM storage",
            "The editor keeps WAD chunks in memory and does not create a chunk folder.",
            parent=self,
        )

    def _reload_selected_chunk(self) -> None:
        if not self._wad_path:
            return
        if not messagebox.askyesno(
            "Reload original WAD",
            "Reloading discards in-memory edits and reads the original WAD again.",
            parent=self,
        ):
            return
        self._open_wad(self._wad_path)

    def _on_chunk_dclick(self, _e: tk.Event) -> None:
        sel = self._chunk_tree.selection()
        if not sel or not self.work: return
        entry = self.work.entries[int(sel[0])]
        data = self.work.get_chunk_data_by_index(entry["index"]) or b""
        preview = " ".join(f"{b:02X}" for b in data[:2048])
        dlg = tk.Toplevel(self)
        dlg.title(f"{entry['tag']} chunk preview")
        dlg.geometry("760x420")
        txt = tk.Text(dlg, wrap="word", font=("Consolas", 9))
        txt.pack(fill="both", expand=True, padx=8, pady=8)
        txt.insert("end", f"{entry['tag']}  {len(data):,} bytes in RAM\n\n{preview}")
        txt.config(state="disabled")

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
        if not (self._mapx and self._trak and self.work):
            return
        stpc_data = self.work.get_chunk_data("STPC")
        if not stpc_data:
            self._scene.object_tris = []
            self._log_line("Object mesh viewport: no STPC chunk; using markers")
            if redraw:
                self._world_canvas.redraw()
            return
        try:
            if self._stpc_mesh_source != stpc_data or self._stpc_mesh_result is None:
                self._stpc_mesh_result = parse_stpc_meshes_from_bytes(stpc_data)
                self._stpc_mesh_source = stpc_data
                self._log_line(
                    f"STPC meshes: decoded {len(self._stpc_mesh_result.meshes)} meshes "
                    f"in RAM ({self._stpc_mesh_result.parse_mode})"
                )
            tris, seen_objects, hits = build_primary_stpc_object_triangles(
                mapx=self._mapx,
                stpc_bytes=stpc_data,
                meshes=self._stpc_mesh_result.meshes,
            )
            self._scene.object_tris = tris
            cloned = self._fill_missing_object_meshes_by_type(seen_objects)
            self._log_line(
                f"Object mesh viewport: built {len(self._scene.object_tris)} triangles "
                f"for {len(seen_objects)} objects from {len(hits)} STPC mesh-reference hits in RAM"
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

    def _start_object_mesh_export(self) -> None:
        """Rebuild object viewport meshes directly from in-memory STPC/MAP data."""
        if not self.work:
            messagebox.showinfo("No WAD", "Open a WAD first."); return
        self._stpc_mesh_result = None
        self._stpc_mesh_source = None
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

    def _on_canvas_object_select(self, pos_idx: int | None) -> None:
        if pos_idx is None:
            self._clear_object_selection()
            return
        canvas_idx = pos_idx
        if 0 <= pos_idx < len(self._objects):
            obj_index = self._objects[pos_idx].index
        else:
            obj_index = pos_idx
            canvas_idx = next((i for i, o in enumerate(self._objects)
                               if o.index == obj_index), pos_idx)
        self._selected_obj = obj_index
        self._world_canvas.select_object(canvas_idx)
        iid = self._object_row_iid_for_index(obj_index)
        if iid and self._obj_tree.exists(iid):
            self._obj_tree.selection_set(iid)
            self._obj_tree.see(iid)

    def _clear_object_selection(self) -> None:
        self._selected_obj = None
        if hasattr(self, "_world_canvas"):
            self._world_canvas.select_object(None)
        if hasattr(self, "_obj_tree"):
            self._obj_tree.selection_remove(self._obj_tree.selection())

    def _on_escape(self, _e: tk.Event | None = None) -> str:
        self._clear_object_selection()
        return "break"

    # ── Object actions ────────────────────────────────────────────────────────

    def _on_terrain_canvas_select(self, tri_idx: int) -> None:
        self._selected_terrain = tri_idx
        tile_idx = None
        if tri_idx < len(self._scene.terrain_meta):
            tile_idx = self._scene.terrain_meta[tri_idx].get("tile_index")
        if getattr(self, "_terrain_mode_var", None) and self._terrain_mode_var.get() == "Chunks" and tile_idx is not None:
            self._selected_tile = tile_idx
            self._terrain_canvas.select_terrain(None)
            self._terrain_canvas.select_tile(tile_idx)
            iid = f"tile_{tile_idx}"
            if self._terrain_tree.exists(iid):
                self._terrain_tree.selection_set(iid)
                self._terrain_tree.see(iid)
            return
        self._selected_tile = None
        self._terrain_canvas.select_tile(None)
        self._terrain_canvas.select_terrain(tri_idx)
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
            self._terrain_canvas.select_terrain(None)
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

    def _terrain_target_tri_indices(self, target: tuple[str, int]) -> list[int]:
        kind, idx = target
        if kind == "tile":
            return [
                i for i, meta in enumerate(self._scene.terrain_meta)
                if meta.get("tile_index") == idx
            ]
        if kind == "tri" and 0 <= idx < len(self._scene.terrain_tris):
            return [idx]
        return []

    def _terrain_target_center(self, target: tuple[str, int]) -> list[float] | None:
        tri_indices = self._terrain_target_tri_indices(target)
        if not tri_indices:
            return None
        verts = [v for i in tri_indices for v in self._scene.terrain_tris[i][0]]
        if not verts:
            return None
        return [
            sum(v[0] for v in verts) / len(verts),
            sum(v[1] for v in verts) / len(verts),
            sum(v[2] for v in verts) / len(verts),
        ]

    def _offset_terrain_tris(self, tri_indices: list[int], dx: float, dy: float, dz: float) -> None:
        for i in tri_indices:
            verts, cy = self._scene.terrain_tris[i]
            self._scene.terrain_tris[i] = (
                [[v[0] + dx, v[1] + dy, v[2] + dz] for v in verts],
                cy + dy,
            )
        self._scene.rebuild_terrain_numpy()

    def _move_selected_chunk(self) -> None:
        if self._selected_tile is None:
            messagebox.showinfo("No chunk", "Select a terrain chunk first."); return
        OffsetEditDialog(self, f"Move Terrain Chunk #{self._selected_tile}",
                         on_apply=self._apply_selected_chunk_offset)

    def _apply_selected_chunk_offset(self, dx: float, dy: float, dz: float) -> None:
        tri_indices = self._selected_chunk_tri_indices()
        if not tri_indices:
            return
        self._offset_terrain_tris(tri_indices, dx, dy, dz)
        self._populate_terrain_tree()
        self._terrain_canvas.select_tile(self._selected_tile)
        self._terrain_canvas.redraw()
        self._world_canvas.redraw()
        self._log_line(f"Moved terrain chunk #{self._selected_tile} by ({dx:.3f}, {dy:.3f}, {dz:.3f}) in memory")

    def _on_canvas_terrain_moved(self, target: tuple[str, int], pos: list[float], commit: bool = False) -> None:
        center = self._terrain_target_center(target)
        if center is None:
            return
        dx, dy, dz = pos[0] - center[0], pos[1] - center[1], pos[2] - center[2]
        tri_indices = self._terrain_target_tri_indices(target)
        if not tri_indices:
            return
        moved = abs(dx) > 1e-9 or abs(dy) > 1e-9 or abs(dz) > 1e-9
        if moved:
            self._offset_terrain_tris(tri_indices, dx, dy, dz)
        kind, idx = target
        if kind == "tile":
            self._selected_tile = idx
            self._selected_terrain = tri_indices[0]
            self._terrain_canvas.select_tile(idx)
        else:
            self._selected_terrain = idx
            self._selected_tile = None
            self._terrain_canvas.select_tile(None)
            self._terrain_canvas.select_terrain(idx)
        self._terrain_canvas.redraw()
        self._world_canvas.redraw()
        if commit:
            self._populate_terrain_tree()
            if kind == "tile":
                iid = f"tile_{idx}"
                if self._terrain_tree.exists(iid):
                    self._terrain_tree.selection_set(iid)
                    self._terrain_tree.see(iid)
                label = f"chunk #{idx}"
            else:
                iid = f"tri_{idx}"
                if self._terrain_tree.exists(iid):
                    self._terrain_tree.selection_set(iid)
                    self._terrain_tree.see(iid)
                label = f"triangle #{idx}"
            if moved:
                self._log_line(f"Moved terrain {label} by ({dx:.3f}, {dy:.3f}, {dz:.3f}) in memory")

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
                         ground_y_provider=self._ground_y_at,
                         section2_values=(
                             list(obj.initial_local_values(self._mapx.section2))
                             if self._mapx is not None and (
                                 obj.local_count == 0 or
                                 len(obj.initial_local_values(self._mapx.section2)) == obj.local_count)
                             else None),
                         section2_schema=section2_schema(
                             self._stpc_names.get(obj.script_offset, ""),
                             obj.local_count))
        # Schema matching is intentionally name + local-count specific so an
        # unrelated STPC program with the same debug name is not mislabeled.

    def _clone_selected_obj(self) -> None:
        obj = self._get_selected_obj()
        if obj is None:
            messagebox.showinfo("No selection", "Select an object first."); return
        new_idx = max((o.index for o in self._objects), default=-1) + 1
        clone   = make_object_copy(obj, new_idx)
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

    def _on_obj_saved(self, obj: Any, section2_values: list[int] | None = None) -> None:
        if not self.work:
            return
        map_data = self.work.get_chunk_data("MAP ")
        if map_data is None:
            return
        try:
            patched = patch_map_chunk_object(map_data, obj)
            if section2_values is not None and self._mapx is not None:
                patched = patch_map_section2_locals(
                    patched, self._mapx, obj, section2_values)
            self.work.save_chunk_data("MAP ", patched)
            if self._mapx is not None and section2_values is not None:
                start = obj.section2_index_raw
                self._mapx.section2[start:start + len(section2_values)] = section2_values
        except Exception as exc:
            messagebox.showerror("Object save failed", str(exc), parent=self)
            return
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
            new_index = max((o.index for o in self._objects), default=None)
            if new_index is not None:
                self._selected_obj = new_index
                iid = self._object_row_iid_for_index(new_index)
                if iid:
                    self._obj_tree.selection_set(iid)
                    self._obj_tree.see(iid)
                pos_idx = next((i for i, o in enumerate(self._objects)
                                if o.index == new_index), None)
                self._world_canvas.select_object(pos_idx)
                self.after_idle(self._focus_selected_obj)
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
