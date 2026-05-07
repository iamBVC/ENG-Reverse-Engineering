#!/usr/bin/env python3
"""Light visual WAD editor prototype.

This is intentionally conservative: it visualizes and edits draft copies of the
decoded extractor outputs, but it does not rewrite WAD files yet.
"""

from __future__ import annotations

import csv
import os
import subprocess
import sys
import threading
import tkinter as tk
from dataclasses import dataclass
from pathlib import Path
from tkinter import filedialog, messagebox, ttk

from eng_wad.wad import read_wad


SCRIPT_DIR = Path(__file__).resolve().parent
PYTHON = Path(sys.executable)


def read_csv(path: Path) -> list[dict[str, str]]:
    if not path.exists():
        return []
    with path.open("r", newline="", encoding="utf-8-sig") as f:
        return list(csv.DictReader(f))


def write_csv(path: Path, rows: list[dict[str, str]]) -> None:
    if not rows:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    fieldnames: list[str] = []
    for row in rows:
        for key in row:
            if key not in fieldnames:
                fieldnames.append(key)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        w.writerows(rows)


def to_float(value: object, default: float = 0.0) -> float:
    try:
        if value in ("", None):
            return default
        return float(value)  # type: ignore[arg-type]
    except (TypeError, ValueError):
        return default


def open_path(path: Path) -> None:
    if not path.exists():
        messagebox.showwarning("Missing file", str(path))
        return
    os.startfile(str(path))  # type: ignore[attr-defined]


@dataclass
class TableSpec:
    title: str
    relative_path: str
    columns: list[str]


TABLES = [
    TableSpec("MAP Objects", "world/map_object_instances.csv", [
        "object_index", "world_x", "world_y", "world_z", "rot_y_units",
        "stpc_def_offset_hex", "mesh_hit_count", "spawn_flags_hex",
    ]),
    TableSpec("STPC VM", "world/stpc_object_vm_diagnostics.csv", [
        "stpc_def_offset_hex", "object_count", "object_indices",
        "normalized_signature_sha1_12", "model_bind_ops", "child_spawn_ops",
        "movement_ops", "dispatch_550e60_call_names",
    ]),
    TableSpec("Mesh Binds", "world/stpc_mesh_reference_hits.csv", [
        "object_index", "mesh_index", "mesh_offset", "hit_relative_offset",
        "script_transform_source", "script_yaw_units",
    ]),
    TableSpec("Lights", "lights/lights.csv", [
        "idx", "kind", "runtime_type", "x", "y", "z_runtime",
        "r_intensity", "g_intensity", "b_intensity", "falloff_or_mode",
    ]),
    TableSpec("Dialogue", "lgpc/dialogue_lines.csv", [
        "column", "text", "voice_or_id",
    ]),
    TableSpec("Ambient", "ampc/ambient_records_40.csv", [
        "index", "pos_x", "pos_y", "pos_z", "near_distance_fixed12",
        "far_distance_fixed12", "sound_id", "sound_id_flags_18_hex",
    ]),
    TableSpec("Sounds", "sounds/smpc_manifest.csv", [
        "index", "resource_tag", "sample_rate", "channels", "audio_data_size",
    ]),
    TableSpec("Textures", "materials/texture_inventory.csv", [
        "texture_index", "filename", "width", "height", "flags_hex", "terrain_texture_hint",
    ]),
]


class CsvTab:
    def __init__(self, parent: ttk.Notebook, spec: TableSpec):
        self.spec = spec
        self.frame = ttk.Frame(parent)
        parent.add(self.frame, text=spec.title)

        self.path_var = tk.StringVar(value="No file loaded")
        ttk.Label(self.frame, textvariable=self.path_var).pack(anchor="w", padx=8, pady=(8, 2))

        wrap = ttk.Frame(self.frame)
        wrap.pack(fill="both", expand=True, padx=8, pady=8)

        self.tree = ttk.Treeview(wrap, show="headings")
        vsb = ttk.Scrollbar(wrap, orient="vertical", command=self.tree.yview)
        hsb = ttk.Scrollbar(wrap, orient="horizontal", command=self.tree.xview)
        self.tree.configure(yscrollcommand=vsb.set, xscrollcommand=hsb.set)
        self.tree.grid(row=0, column=0, sticky="nsew")
        vsb.grid(row=0, column=1, sticky="ns")
        hsb.grid(row=1, column=0, sticky="ew")
        wrap.rowconfigure(0, weight=1)
        wrap.columnconfigure(0, weight=1)

        btns = ttk.Frame(self.frame)
        btns.pack(fill="x", padx=8, pady=(0, 8))
        ttk.Button(btns, text="Open CSV", command=self.open_csv).pack(side="left")
        ttk.Button(btns, text="Open Folder", command=self.open_folder).pack(side="left", padx=(6, 0))

        self.path: Path | None = None
        self.rows: list[dict[str, str]] = []

    def load(self, out_dir: Path | None) -> None:
        self.rows = []
        self.path = out_dir / self.spec.relative_path if out_dir else None
        if self.path and self.path.exists():
            self.rows = read_csv(self.path)
            self.path_var.set(str(self.path))
        else:
            self.path_var.set(f"Missing: {self.spec.relative_path}")
        self.refresh()

    def refresh(self) -> None:
        self.tree.delete(*self.tree.get_children())
        columns = self.spec.columns[:]
        if self.rows:
            for key in self.rows[0]:
                if key not in columns:
                    columns.append(key)
        self.tree.configure(columns=columns)
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=max(90, min(260, len(col) * 9)), anchor="w")
        for idx, row in enumerate(self.rows[:2000]):
            self.tree.insert("", "end", iid=str(idx), values=[row.get(c, "") for c in columns])

    def open_csv(self) -> None:
        if self.path:
            open_path(self.path)

    def open_folder(self) -> None:
        if self.path:
            open_path(self.path.parent)


class WadEditorApp(tk.Tk):
    def __init__(self) -> None:
        super().__init__()
        self.title("ENG WAD Editor Prototype")
        self.geometry("1280x820")
        self.minsize(1000, 650)

        self.wad_path: Path | None = None
        self.out_dir: Path | None = None
        self.chunks: list[tuple[str, int, int]] = []
        self.world_rows: list[dict[str, str]] = []
        self.selected_object_index: int | None = None
        self.texture_images: list[tk.PhotoImage] = []

        self._build_ui()

    def _build_ui(self) -> None:
        toolbar = ttk.Frame(self)
        toolbar.pack(fill="x", padx=8, pady=8)

        ttk.Button(toolbar, text="Open WAD", command=self.open_wad_dialog).pack(side="left")
        ttk.Button(toolbar, text="Run Extract", command=self.run_extract).pack(side="left", padx=(6, 0))
        ttk.Button(toolbar, text="Load Output Folder", command=self.load_output_dialog).pack(side="left", padx=(6, 0))
        ttk.Button(toolbar, text="Open Output", command=self.open_output).pack(side="left", padx=(6, 0))

        self.status_var = tk.StringVar(value="Open a WAD to begin.")
        ttk.Label(toolbar, textvariable=self.status_var).pack(side="left", padx=14)

        self.notebook = ttk.Notebook(self)
        self.notebook.pack(fill="both", expand=True)

        self.overview = ttk.Frame(self.notebook)
        self.notebook.add(self.overview, text="Overview")
        self._build_overview()

        self.world = ttk.Frame(self.notebook)
        self.notebook.add(self.world, text="World")
        self._build_world()

        self.csv_tabs = [CsvTab(self.notebook, spec) for spec in TABLES]

        self.textures = ttk.Frame(self.notebook)
        self.notebook.add(self.textures, text="Texture Browser")
        self._build_texture_browser()

        self.log_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.log_frame, text="Log")
        self.log = tk.Text(self.log_frame, wrap="word")
        self.log.pack(fill="both", expand=True, padx=8, pady=8)

    def _build_overview(self) -> None:
        left = ttk.Frame(self.overview)
        left.pack(side="left", fill="both", expand=True, padx=8, pady=8)
        right = ttk.Frame(self.overview)
        right.pack(side="right", fill="both", expand=True, padx=8, pady=8)

        self.info = tk.Text(left, wrap="word", height=12)
        self.info.pack(fill="both", expand=True)

        self.chunk_tree = ttk.Treeview(right, columns=("tag", "offset", "size"), show="headings")
        for col in ("tag", "offset", "size"):
            self.chunk_tree.heading(col, text=col)
            self.chunk_tree.column(col, width=120, anchor="w")
        self.chunk_tree.pack(fill="both", expand=True)

    def _build_world(self) -> None:
        top = ttk.Frame(self.world)
        top.pack(fill="x", padx=8, pady=8)
        ttk.Button(top, text="Save Object Draft CSV", command=self.save_object_draft).pack(side="left")
        ttk.Button(top, text="Open terrain_and_objects.obj", command=self.open_world_obj).pack(side="left", padx=(6, 0))
        ttk.Label(top, text="Object placement edits are draft CSV only.").pack(side="left", padx=12)

        paned = ttk.PanedWindow(self.world, orient="horizontal")
        paned.pack(fill="both", expand=True, padx=8, pady=(0, 8))

        left = ttk.Frame(paned)
        paned.add(left, weight=3)
        right = ttk.Frame(paned)
        paned.add(right, weight=2)

        self.canvas = tk.Canvas(left, bg="#111317", highlightthickness=0)
        self.canvas.pack(fill="both", expand=True)
        self.canvas.bind("<Configure>", lambda _e: self.draw_world())

        self.object_tree = ttk.Treeview(
            right,
            columns=("object_index", "world_x", "world_y", "world_z", "rot_y_units", "mesh_hit_count"),
            show="headings",
            height=14,
        )
        for col in self.object_tree["columns"]:
            self.object_tree.heading(col, text=col)
            self.object_tree.column(col, width=95, anchor="w")
        self.object_tree.pack(fill="both", expand=True)
        self.object_tree.bind("<<TreeviewSelect>>", self.on_object_selected)

        editor = ttk.LabelFrame(right, text="Selected Object")
        editor.pack(fill="x", pady=(8, 0))
        self.edit_vars: dict[str, tk.StringVar] = {}
        for row, key in enumerate(("world_x", "world_y", "world_z", "rot_y_units", "spawn_flags_hex", "stpc_def_offset_hex")):
            ttk.Label(editor, text=key).grid(row=row, column=0, sticky="w", padx=6, pady=3)
            var = tk.StringVar()
            ent = ttk.Entry(editor, textvariable=var)
            ent.grid(row=row, column=1, sticky="ew", padx=6, pady=3)
            self.edit_vars[key] = var
        editor.columnconfigure(1, weight=1)
        ttk.Button(editor, text="Apply Draft Edit", command=self.apply_object_edit).grid(
            row=7, column=0, columnspan=2, sticky="ew", padx=6, pady=8
        )

    def _build_texture_browser(self) -> None:
        top = ttk.Frame(self.textures)
        top.pack(fill="x", padx=8, pady=8)
        ttk.Button(top, text="Reload Textures", command=self.load_texture_browser).pack(side="left")
        ttk.Button(top, text="Open textures folder", command=self.open_textures_folder).pack(side="left", padx=(6, 0))

        wrap = ttk.Frame(self.textures)
        wrap.pack(fill="both", expand=True, padx=8, pady=(0, 8))
        self.texture_canvas = tk.Canvas(wrap, bg="#181a1f")
        scroll = ttk.Scrollbar(wrap, orient="vertical", command=self.texture_canvas.yview)
        self.texture_canvas.configure(yscrollcommand=scroll.set)
        self.texture_canvas.pack(side="left", fill="both", expand=True)
        scroll.pack(side="right", fill="y")

    def open_wad_dialog(self) -> None:
        path = filedialog.askopenfilename(
            title="Open WAD",
            initialdir=str(SCRIPT_DIR),
            filetypes=[("WAD files", "*.wad *.WAD"), ("All files", "*.*")],
        )
        if path:
            self.open_wad(Path(path))

    def open_wad(self, path: Path) -> None:
        self.wad_path = path
        try:
            data, chunks, _by_tag = read_wad(path)
        except Exception as exc:
            messagebox.showerror("Open failed", str(exc))
            return

        self.chunks = [(c.tag, c.offset, c.size) for c in chunks]
        self.status_var.set(f"{path.name}: {len(data):,} bytes, {len(chunks)} chunks")
        self.log_line(f"Opened {path}")
        self.refresh_overview(path, data)

        self.out_dir = self.detect_output_dir(path)
        self.load_outputs()

    def refresh_overview(self, path: Path, data: bytes) -> None:
        self.info.delete("1.0", "end")
        self.info.insert("end", f"Source: {path}\n")
        self.info.insert("end", f"Size: {len(data):,} bytes\n")
        self.info.insert("end", f"Chunks: {len(self.chunks)}\n\n")
        self.info.insert("end", "Prototype scope:\n")
        self.info.insert("end", "- Inspect decoded chunks and extractor outputs\n")
        self.info.insert("end", "- Visualize MAP object placement and lights\n")
        self.info.insert("end", "- Browse textures and STPC VM fingerprints\n")
        self.info.insert("end", "- Save draft object-placement CSV edits\n")
        self.info.insert("end", "- No WAD reserialization yet\n")

        self.chunk_tree.delete(*self.chunk_tree.get_children())
        for idx, (tag, off, size) in enumerate(self.chunks):
            self.chunk_tree.insert("", "end", iid=str(idx), values=(tag, off, f"{size:,}"))

    def detect_output_dir(self, wad_path: Path) -> Path | None:
        stem = wad_path.stem
        candidates = [
            SCRIPT_DIR / "editor_exports" / stem,
            SCRIPT_DIR / "extracted" / stem,
            wad_path.parent / "extracted" / stem,
        ]
        for path in candidates:
            if path.exists():
                return path
        return None

    def load_output_dialog(self) -> None:
        path = filedialog.askdirectory(title="Open extractor output folder", initialdir=str(SCRIPT_DIR))
        if path:
            self.out_dir = Path(path)
            self.load_outputs()

    def load_outputs(self) -> None:
        if self.out_dir and self.out_dir.exists():
            self.status_var.set(f"Output: {self.out_dir}")
            self.log_line(f"Loaded output folder {self.out_dir}")
        else:
            self.log_line("No extractor output folder found yet.")
        for tab in self.csv_tabs:
            tab.load(self.out_dir)
        self.load_world()
        self.load_texture_browser()

    def run_extract(self) -> None:
        if not self.wad_path:
            messagebox.showinfo("Open WAD", "Open a WAD first.")
            return
        out_root = SCRIPT_DIR / "editor_exports"
        self.out_dir = out_root / self.wad_path.stem
        cmd = [
            str(PYTHON),
            str(SCRIPT_DIR / "wad_extractor.py"),
            str(self.wad_path),
            "--out-dir",
            str(out_root),
            "--quiet",
        ]
        env = os.environ.copy()
        env["PYTHONIOENCODING"] = "utf-8"
        self.log_line("Running extractor...")

        def worker() -> None:
            try:
                proc = subprocess.run(
                    cmd,
                    cwd=str(SCRIPT_DIR),
                    env=env,
                    text=True,
                    encoding="utf-8",
                    errors="replace",
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                )
                self.after(0, lambda: self._extract_done(proc.returncode, proc.stdout))
            except Exception as exc:
                self.after(0, lambda: messagebox.showerror("Extract failed", str(exc)))

        threading.Thread(target=worker, daemon=True).start()

    def _extract_done(self, code: int, output: str) -> None:
        self.log_line(output)
        if code == 0:
            self.log_line("Extractor finished.")
            self.load_outputs()
        else:
            self.log_line(f"Extractor exited with code {code}.")

    def load_world(self) -> None:
        self.world_rows = []
        if self.out_dir:
            self.world_rows = read_csv(self.out_dir / "world" / "map_object_instances.csv")

        self.object_tree.delete(*self.object_tree.get_children())
        for idx, row in enumerate(self.world_rows):
            values = [row.get(c, "") for c in self.object_tree["columns"]]
            self.object_tree.insert("", "end", iid=str(idx), values=values)
        self.draw_world()

    def draw_world(self) -> None:
        self.canvas.delete("all")
        rows = self.world_rows
        if not rows:
            self.canvas.create_text(24, 24, text="Run extraction to view MAP/STPC object placement.", fill="#c8d0dc", anchor="nw")
            return

        w = max(200, self.canvas.winfo_width())
        h = max(200, self.canvas.winfo_height())
        xs = [to_float(r.get("world_x")) for r in rows]
        zs = [to_float(r.get("world_z")) for r in rows]
        min_x, max_x = min(xs), max(xs)
        min_z, max_z = min(zs), max(zs)
        span_x = max(max_x - min_x, 1.0)
        span_z = max(max_z - min_z, 1.0)
        pad = 36

        def project(x: float, z: float) -> tuple[float, float]:
            px = pad + (x - min_x) / span_x * (w - pad * 2)
            py = h - pad - (z - min_z) / span_z * (h - pad * 2)
            return px, py

        self.canvas.create_rectangle(pad, pad, w - pad, h - pad, outline="#2a3038")
        self.canvas.create_text(10, 10, text=f"{len(rows)} MAP objects", fill="#c8d0dc", anchor="nw")

        for idx, row in enumerate(rows):
            x = to_float(row.get("world_x"))
            z = to_float(row.get("world_z"))
            px, py = project(x, z)
            hits = int(to_float(row.get("mesh_hit_count"), 0))
            color = "#6ee7b7" if hits else "#f59e0b"
            r = 4 if hits else 3
            if idx == self.selected_object_index:
                self.canvas.create_oval(px - 9, py - 9, px + 9, py + 9, outline="#ffffff", width=2)
            self.canvas.create_oval(px - r, py - r, px + r, py + r, fill=color, outline="")
            self.canvas.create_text(px + 6, py - 6, text=row.get("object_index", str(idx)), fill="#8ea0b6", anchor="w")

        if self.out_dir:
            lights = read_csv(self.out_dir / "lights" / "lights.csv")
            for light in lights:
                lx = to_float(light.get("x"), None)  # type: ignore[arg-type]
                lz = to_float(light.get("z_runtime") or light.get("z"), None)  # type: ignore[arg-type]
                if lx is None or lz is None:
                    continue
                px, py = project(lx, lz)
                self.canvas.create_rectangle(px - 3, py - 3, px + 3, py + 3, outline="#fde047")

    def on_object_selected(self, _event: object) -> None:
        sel = self.object_tree.selection()
        if not sel:
            return
        idx = int(sel[0])
        self.selected_object_index = idx
        row = self.world_rows[idx]
        for key, var in self.edit_vars.items():
            var.set(row.get(key, ""))
        self.draw_world()

    def apply_object_edit(self) -> None:
        if self.selected_object_index is None:
            return
        row = self.world_rows[self.selected_object_index]
        for key, var in self.edit_vars.items():
            if key in row:
                row[key] = var.get()
        self.load_world_tree_only()
        self.draw_world()

    def load_world_tree_only(self) -> None:
        self.object_tree.delete(*self.object_tree.get_children())
        for idx, row in enumerate(self.world_rows):
            values = [row.get(c, "") for c in self.object_tree["columns"]]
            self.object_tree.insert("", "end", iid=str(idx), values=values)
        if self.selected_object_index is not None:
            self.object_tree.selection_set(str(self.selected_object_index))

    def save_object_draft(self) -> None:
        if not self.world_rows or not self.out_dir:
            return
        draft = self.out_dir / "editor_drafts" / "map_object_instances.edited.csv"
        write_csv(draft, self.world_rows)
        self.log_line(f"Saved draft object CSV: {draft}")
        messagebox.showinfo("Saved", str(draft))

    def load_texture_browser(self) -> None:
        self.texture_canvas.delete("all")
        self.texture_images.clear()
        if not self.out_dir:
            self.texture_canvas.create_text(16, 16, text="No output folder loaded.", fill="#d5dbe5", anchor="nw")
            return

        tex_dir = self.out_dir / "textures"
        files = sorted(tex_dir.glob("*.png"))
        if not files:
            self.texture_canvas.create_text(16, 16, text="No exported PNG textures found.", fill="#d5dbe5", anchor="nw")
            return

        x, y = 16, 16
        cell_w, cell_h = 150, 150
        max_cols = 6
        for idx, path in enumerate(files[:120]):
            try:
                img = tk.PhotoImage(file=str(path))
                scale = max(1, max(img.width() // 96, img.height() // 96))
                if scale > 1:
                    img = img.subsample(scale, scale)
                self.texture_images.append(img)
                col = idx % max_cols
                row = idx // max_cols
                x = 16 + col * cell_w
                y = 16 + row * cell_h
                self.texture_canvas.create_rectangle(x - 4, y - 4, x + 124, y + 124, outline="#2a3038")
                self.texture_canvas.create_image(x, y, image=img, anchor="nw")
                self.texture_canvas.create_text(x, y + 108, text=path.stem, fill="#d5dbe5", anchor="nw")
            except tk.TclError:
                continue
        self.texture_canvas.configure(scrollregion=(0, 0, max_cols * cell_w + 32, y + cell_h + 32))

    def open_textures_folder(self) -> None:
        if self.out_dir:
            open_path(self.out_dir / "textures")

    def open_world_obj(self) -> None:
        if self.out_dir:
            open_path(self.out_dir / "world" / "terrain_and_objects.obj")

    def open_output(self) -> None:
        if self.out_dir:
            open_path(self.out_dir)

    def log_line(self, text: str) -> None:
        self.log.insert("end", text.rstrip() + "\n")
        self.log.see("end")


def main(argv: list[str] | None = None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    app = WadEditorApp()
    if argv and argv[0]:
        path = Path(argv[0])
        if path.exists():
            app.open_wad(path)
    app.mainloop()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
