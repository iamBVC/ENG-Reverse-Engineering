"""editor_dialogs.py - reusable Tk dialogs for the WAD editor."""

from __future__ import annotations

import re
import struct
import tkinter as tk
from tkinter import messagebox, simpledialog, ttk
from typing import Any

from .map_patch import OBJ_RECORD_SIZE, make_object_copy
from .section2_semantics import Section2FieldSemantic

def _parse_int_text(text: str) -> int:
    text = text.strip()
    return int(text, 16) if text.lower().startswith("0x") else int(text, 10)


def _fmt_u32(v: int) -> str:
    return f"0x{v & 0xFFFFFFFF:08X}"


def _fmt_u16(v: int) -> str:
    return f"0x{v & 0xFFFF:04X}"


class ObjectEditDialog(tk.Toplevel):
    def __init__(self, parent: tk.Widget, obj: Any, *, on_save: Any = None,
                 known_types: list[tuple[int, str]] | None = None,
                 ground_y_provider: Any = None,
                 section2_values: list[int] | None = None,
                 section2_schema: tuple[Section2FieldSemantic, ...] | None = None) -> None:
        super().__init__(parent)
        self.title(f"Edit Object #{obj.index}")
        self.resizable(False, False)
        self.grab_set()
        self._obj = obj
        self._on_save = on_save
        self._ground_y_provider = ground_y_provider
        self._section2_values = None if section2_values is None else list(section2_values)
        self._section2_schema = section2_schema
        self._type_by_label = {label: off for off, label in (known_types or [])}
        self._vars: dict[str, tk.StringVar] = {}

        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)
        type_values = [label for _off, label in (known_types or [])]
        type_label = next((label for off, label in (known_types or []) if off == obj.script_offset), f"0x{obj.script_offset:08X}")
        self._type_var = tk.StringVar(value=type_label)
        ttk.Label(frm, text="Type").grid(row=0, column=0, sticky="e", padx=(0, 8), pady=3)
        ttk.Combobox(frm, textvariable=self._type_var, values=type_values, width=42).grid(row=0, column=1, columnspan=3, sticky="we", pady=3)

        rows = [
            ("x", "X", f"{obj.pos_x_fixed12 / 4096.0:.6f}"),
            ("y", "Y", f"{obj.pos_y_fixed12 / 4096.0:.6f}"),
            ("z", "Z", f"{obj.pos_z_fixed12 / 4096.0:.6f}"),
            ("rot_x_units", "Rot X", str(obj.rot_x_units)),
            ("rot_y_units", "Rot Y", str(obj.rot_y_units)),
            ("rot_z_units", "Rot Z", str(obj.rot_z_units)),
            ("local_count", "Local count", str(obj.local_count)),
            ("section2_index_raw", "Section2", _fmt_u32(obj.section2_index_raw)),
            ("stack_word_count", "Stack words", str(obj.stack_word_count)),
            ("stack_arg_count", "Stack args", str(obj.stack_arg_count)),
            ("spawn_flags", "Spawn flags", _fmt_u32(obj.spawn_flags)),
            ("extra_count", "Extra count", str(obj.extra_count)),
            ("section4_index_raw", "Section4", _fmt_u32(obj.section4_index_raw)),
            ("spawn_aux_raw", "Spawn aux", _fmt_u32(obj.spawn_aux_raw)),
            ("flags", "Flags", _fmt_u16(obj.flags)),
            ("extra_u16", "Extra u16", _fmt_u16(obj.extra_u16)),
        ]
        for i, (key, label, value) in enumerate(rows, start=1):
            var = tk.StringVar(value=value)
            self._vars[key] = var
            col = 0 if i <= 8 else 2
            row = i if i <= 8 else i - 8
            ttk.Label(frm, text=label).grid(row=row, column=col, sticky="e", padx=(0, 8), pady=3)
            state = "readonly" if key in {"local_count", "section2_index_raw"} else "normal"
            ttk.Entry(frm, textvariable=var, width=16, state=state).grid(row=row, column=col + 1, sticky="w", pady=3)
        ttk.Button(frm, text="Snap Y to Ground", command=self._snap_y).grid(row=9, column=0, columnspan=2, sticky="w", pady=(8, 0))

        locals_text = "Edit Section2 locals"
        if self._section2_values is not None:
            locals_text += f" ({len(self._section2_values)})"
        locals_button = ttk.Button(frm, text=locals_text, command=self._edit_section2_locals)
        locals_button.grid(row=9, column=2, columnspan=2, sticky="e", pady=(8, 0))
        if self._section2_values is None:
            locals_button.state(["disabled"])

        btns = ttk.Frame(self, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Apply", command=self._save).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel", command=self.destroy).pack(side="right")

    def _parse_type(self) -> int:
        text = self._type_var.get().strip()
        if text in self._type_by_label:
            return self._type_by_label[text]
        m = re.search(r"0x([0-9A-Fa-f]+)", text)
        return int(m.group(1), 16) if m else _parse_int_text(text)

    def _snap_y(self) -> None:
        if not self._ground_y_provider:
            return
        try:
            y = self._ground_y_provider(float(self._vars["x"].get()), float(self._vars["z"].get()))
        except ValueError:
            return
        if y is not None:
            self._vars["y"].set(f"{y:.6f}")

    def _edit_section2_locals(self) -> None:
        if self._section2_values is None:
            return
        Section2LocalsDialog(self, self._section2_values, self._section2_schema)

    def _save(self) -> None:
        try:
            self._obj.script_offset = self._parse_type()
            self._obj.pos_x_fixed12 = int(round(float(self._vars["x"].get()) * 4096))
            self._obj.pos_y_fixed12 = int(round(float(self._vars["y"].get()) * 4096))
            self._obj.pos_z_fixed12 = int(round(float(self._vars["z"].get()) * 4096))
            for key in ("rot_x_units", "rot_y_units", "rot_z_units", "flags", "extra_u16"):
                setattr(self._obj, key, _parse_int_text(self._vars[key].get()) & 0xFFFF)
            for key in ("local_count", "section2_index_raw", "stack_word_count", "stack_arg_count",
                        "spawn_flags", "extra_count", "section4_index_raw", "spawn_aux_raw"):
                setattr(self._obj, key, _parse_int_text(self._vars[key].get()) & 0xFFFFFFFF)
        except Exception as exc:
            messagebox.showerror("Parse error", str(exc), parent=self)
            return
        if self._on_save:
            self._on_save(self._obj, self._section2_values)
        self.destroy()


class Section2LocalsDialog(tk.Toplevel):
    """Fixed-layout editor for one object's initial script-local values."""

    def __init__(self, parent: tk.Widget, values: list[int],
                 schema: tuple[Section2FieldSemantic, ...] | None = None) -> None:
        super().__init__(parent)
        self.title("Section2 Initial Locals")
        self.geometry("580x360")
        self.transient(parent)
        self.grab_set()
        self._values = values
        self._schema = schema if schema is not None and len(schema) == len(values) else None

        ttk.Label(
            self,
            text=("Named fields below are backed by traced STPC control flow. "
                  "Unidentified object variants remain in diagnostic form."),
            wraplength=550,
        ).pack(fill="x", padx=10, pady=(10, 6))

        self._tree = ttk.Treeview(
            self, columns=("slot", "field", "value", "confidence"),
            show="headings", selectmode="browse")
        for key, label, width, anchor in (
            ("slot", "Local", 55, "center"),
            ("field", "Field", 245, "w"),
            ("value", "Value", 120, "center"),
            ("confidence", "Evidence", 95, "center"),
        ):
            self._tree.heading(key, text=label)
            self._tree.column(key, width=width, anchor=anchor)
        scroll = ttk.Scrollbar(self, orient="vertical", command=self._tree.yview)
        self._tree.configure(yscrollcommand=scroll.set)
        self._tree.pack(side="left", fill="both", expand=True, padx=(10, 0), pady=(0, 10))
        scroll.pack(side="left", fill="y", pady=(0, 10))
        self._tree.bind("<Double-1>", lambda _event: self._edit_selected())

        buttons = ttk.Frame(self, padding=(8, 0, 10, 10))
        buttons.pack(side="right", fill="y")
        ttk.Button(buttons, text="Edit…", command=self._edit_selected).pack(fill="x", pady=(0, 6))
        ttk.Button(buttons, text="Close", command=self.destroy).pack(fill="x")
        self._refresh()

    @staticmethod
    def _signed(value: int) -> int:
        return struct.unpack("<i", struct.pack("<I", value))[0]

    def _refresh(self, selected: int | None = None) -> None:
        self._tree.delete(*self._tree.get_children())
        for slot, value in enumerate(self._values):
            signed = self._signed(value)
            semantic = self._schema[slot] if self._schema else None
            if semantic and semantic.value_type == "fixed12_bool":
                display_value = ("Enabled" if value != 0 else "Disabled")
                if value not in {0, 0x1000}:
                    display_value += f" (noncanonical {_fmt_u32(value)})"
                field_name = semantic.name
                confidence = semantic.confidence.title()
            else:
                display_value = f"{signed / 4096.0:.6f} / {_fmt_u32(value)}"
                field_name = "Unidentified"
                confidence = "Unknown"
            self._tree.insert("", "end", iid=str(slot), values=(
                slot, field_name, display_value, confidence))
        if selected is not None and self._tree.exists(str(selected)):
            self._tree.selection_set(str(selected))
            self._tree.see(str(selected))

    def _edit_selected(self) -> None:
        selection = self._tree.selection()
        if not selection:
            return
        slot = int(selection[0])
        semantic = self._schema[slot] if self._schema else None
        if semantic and semantic.value_type == "fixed12_bool":
            answer = messagebox.askyesnocancel(
                semantic.name,
                semantic.description + "\n\nEnable this field?",
                parent=self)
            if answer is None:
                return
            self._values[slot] = 0x1000 if answer else 0
            self._refresh(slot)
            return
        text = simpledialog.askstring(
            f"Edit local {slot}",
            "Raw u32 value (decimal or 0x-prefixed hexadecimal):",
            initialvalue=_fmt_u32(self._values[slot]), parent=self)
        if text is None:
            return
        try:
            value = _parse_int_text(text)
            if value < 0:
                value &= 0xFFFFFFFF
            if not 0 <= value <= 0xFFFFFFFF:
                raise ValueError("value is outside the u32 range")
        except ValueError as exc:
            messagebox.showerror("Invalid local value", str(exc), parent=self)
            return
        self._values[slot] = value
        self._refresh(slot)


class AddObjectDialog(tk.Toplevel):
    def __init__(self, parent: tk.Widget, known_types: list[tuple[int, str]],
                 *, template: Any = None, on_add: Any = None) -> None:
        super().__init__(parent)
        self.title("Add Object")
        self.resizable(False, False)
        self.grab_set()
        self._template = template
        self._on_add = on_add
        self._type_by_label = {label: off for off, label in known_types}
        values = [label for _off, label in known_types]
        default = values[0] if values else ""
        if template is not None:
            default = next((label for off, label in known_types if off == template.script_offset), f"0x{template.script_offset:08X}")

        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)
        self._type_var = tk.StringVar(value=default)
        self._clone_var = tk.BooleanVar(value=template is not None)
        self._x_var = tk.StringVar(value=f"{(template.pos_x_fixed12 / 4096.0) if template is not None else 0.0:.6f}")
        self._y_var = tk.StringVar(value=f"{(template.pos_y_fixed12 / 4096.0) if template is not None else 0.0:.6f}")
        self._z_var = tk.StringVar(value=f"{(template.pos_z_fixed12 / 4096.0) if template is not None else 0.0:.6f}")

        ttk.Label(frm, text="Type").grid(row=0, column=0, sticky="e", padx=(0, 8), pady=3)
        ttk.Combobox(frm, textvariable=self._type_var, values=values, width=44).grid(row=0, column=1, columnspan=2, sticky="we", pady=3)
        ttk.Checkbutton(frm, text="Clone selected fields", variable=self._clone_var).grid(row=1, column=1, sticky="w", pady=3)
        for row, (label, var) in enumerate((("X", self._x_var), ("Y", self._y_var), ("Z", self._z_var)), start=2):
            ttk.Label(frm, text=label).grid(row=row, column=0, sticky="e", padx=(0, 8), pady=3)
            ttk.Entry(frm, textvariable=var, width=16).grid(row=row, column=1, sticky="w", pady=3)

        btns = ttk.Frame(self, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Add", command=self._add).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel", command=self.destroy).pack(side="right")

    def _parse_type(self) -> int:
        text = self._type_var.get().strip()
        if text in self._type_by_label:
            return self._type_by_label[text]
        m = re.search(r"0x([0-9A-Fa-f]+)", text)
        return int(m.group(1), 16) if m else _parse_int_text(text)

    def _add(self) -> None:
        try:
            script_off = self._parse_type()
            px = int(round(float(self._x_var.get()) * 4096))
            py = int(round(float(self._y_var.get()) * 4096))
            pz = int(round(float(self._z_var.get()) * 4096))
        except Exception as exc:
            messagebox.showerror("Parse error", str(exc), parent=self)
            return

        if self._clone_var.get() and self._template is not None:
            new_obj = make_object_copy(self._template, new_index=-1)
            new_obj.script_offset = script_off
            new_obj.pos_x_fixed12 = px
            new_obj.pos_y_fixed12 = py
            new_obj.pos_z_fixed12 = pz
        else:
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


class OffsetEditDialog(tk.Toplevel):
    def __init__(self, parent: tk.Widget, title: str, *, on_apply: Any = None) -> None:
        super().__init__(parent)
        self.title(title)
        self.resizable(False, False)
        self.grab_set()
        self._on_apply = on_apply
        self._vars = {
            "dx": tk.StringVar(value="0.0"),
            "dy": tk.StringVar(value="0.0"),
            "dz": tk.StringVar(value="0.0"),
        }
        frm = ttk.Frame(self, padding=12)
        frm.pack(fill="both", expand=True)
        for row, key in enumerate(("dx", "dy", "dz")):
            ttk.Label(frm, text=key.upper()).grid(row=row, column=0, sticky="e", padx=(0, 8), pady=3)
            ttk.Entry(frm, textvariable=self._vars[key], width=16).grid(row=row, column=1, sticky="w", pady=3)
        btns = ttk.Frame(self, padding=(12, 0, 12, 12))
        btns.pack(fill="x")
        ttk.Button(btns, text="Apply", command=self._apply).pack(side="right", padx=4)
        ttk.Button(btns, text="Cancel", command=self.destroy).pack(side="right")

    def _apply(self) -> None:
        try:
            dx = float(self._vars["dx"].get())
            dy = float(self._vars["dy"].get())
            dz = float(self._vars["dz"].get())
        except ValueError:
            messagebox.showerror("Parse error", "Offsets must be numbers.", parent=self)
            return
        if self._on_apply:
            self._on_apply(dx, dy, dz)
        self.destroy()


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

