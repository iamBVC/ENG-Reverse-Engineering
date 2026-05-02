"""
material_diagnostics.py — executable-informed material/table diagnostics.

The game loader stores the TEXT/TXET trailing 8-byte table as a runtime table at
``dword_581154`` with a 20-byte stride.  TRAK and STPC triangle records store a
compact u16 material index; the executable rewrites that index to:

    dword_581154 + 20 * material_index

This module does not guess final UV/texture binding yet.  Instead it exports the
confirmed material table, counts how terrain/STPC triangles use it, and highlights
terrain-priority textures for the next texturing pass.
"""

from __future__ import annotations

import csv
import json
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Iterable

from .text_chunk import TextChunk
from .trak_chunk import TrakFile
from .stpc_chunk import STPCExportResult


@dataclass
class RuntimeMaterial20:
    """Runtime representation inferred from sub_406D30.

    Disk table entry is 8 bytes.  The loader expands it into sparse fields in a
    20-byte runtime struct:

        +0x00 u16 disk bytes 0..1
        +0x02 u8  disk byte 2
        +0x03 u8  disk byte 3
        +0x04 u8  disk byte 4
        +0x08 u8  disk byte 5
        +0x0C u8  disk byte 6
        +0x10 u8  disk byte 7

    For observed WADs, bytes 4..6 form an RGB color and byte 3 is usually 0xFF.
    """

    index: int
    disk_b0: int
    disk_b1: int
    disk_b2: int
    disk_b3: int
    disk_b4: int
    disk_b5: int
    disk_b6: int
    disk_b7: int
    runtime_u16_00: int
    runtime_i8_02: int
    runtime_u8_03: int
    runtime_u8_04_r: int
    runtime_u8_08_g: int
    runtime_u8_0c_b: int
    runtime_u8_10_extra: int


def _i8(v: int) -> int:
    v &= 0xFF
    return v - 256 if v >= 128 else v


def build_runtime_material_table(text: TextChunk) -> list[RuntimeMaterial20]:
    rows: list[RuntimeMaterial20] = []
    for i in range(text.pal_count):
        e = text.pal_raw[i * 8:(i + 1) * 8]
        if len(e) < 8:
            continue
        rows.append(RuntimeMaterial20(
            index=i,
            disk_b0=e[0],
            disk_b1=e[1],
            disk_b2=e[2],
            disk_b3=e[3],
            disk_b4=e[4],
            disk_b5=e[5],
            disk_b6=e[6],
            disk_b7=e[7],
            runtime_u16_00=e[0] | (e[1] << 8),
            runtime_i8_02=_i8(e[2]),
            runtime_u8_03=e[3],
            runtime_u8_04_r=e[4],
            runtime_u8_08_g=e[5],
            runtime_u8_0c_b=e[6],
            runtime_u8_10_extra=e[7],
        ))
    return rows


def _write_csv(path: Path, fieldnames: list[str], rows: Iterable[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            w.writerow(row)


def _material_row(mat: RuntimeMaterial20 | None) -> dict[str, int | str]:
    if mat is None:
        return {
            "mat_runtime_u16_00": "",
            "mat_i8_02_texture_page_candidate": "",
            "mat_u8_03": "",
            "mat_rgb_r": "",
            "mat_rgb_g": "",
            "mat_rgb_b": "",
            "mat_extra": "",
        }
    return {
        "mat_runtime_u16_00": mat.runtime_u16_00,
        "mat_i8_02_texture_page_candidate": mat.runtime_i8_02,
        "mat_u8_03": mat.runtime_u8_03,
        "mat_rgb_r": mat.runtime_u8_04_r,
        "mat_rgb_g": mat.runtime_u8_08_g,
        "mat_rgb_b": mat.runtime_u8_0c_b,
        "mat_extra": mat.runtime_u8_10_extra,
    }


def export_material_diagnostics(
    *,
    text: TextChunk | None,
    trak: TrakFile | None,
    stpc: STPCExportResult | None,
    out_dir: Path,
    terrain_texture_indices: tuple[int, ...] = (5, 6, 7, 8, 9),
) -> None:
    """Write material-use diagnostics into ``materials/``.

    This is deliberately factual/conservative: it reports the decoded runtime
    material table and which triangle material indices reference it.  It does
    not yet write textured OBJ UVs, because UV binding is still unresolved.
    """
    out_dir.mkdir(parents=True, exist_ok=True)

    materials = build_runtime_material_table(text) if text is not None else []
    mat_by_idx = {m.index: m for m in materials}

    if text is not None:
        rows = [asdict(m) for m in materials]
        if rows:
            _write_csv(out_dir / "runtime_material_table_20.csv", list(rows[0].keys()), rows)
        else:
            (out_dir / "runtime_material_table_20.csv").write_text("index\n", encoding="utf-8")

        tex_rows = []
        for tex in text.textures:
            tex_rows.append({
                "texture_index": tex.index,
                "terrain_priority_hint": int(tex.index in terrain_texture_indices),
                "flags_hex": f"0x{tex.flags:04X}",
                "width": tex.width,
                "height": tex.height,
                "compressed_size": tex.comp_size,
                "png_path": f"../textures/texture_{tex.index:02d}.png",
            })
        _write_csv(out_dir / "texture_inventory.csv", list(tex_rows[0].keys()) if tex_rows else ["texture_index"], tex_rows)

    trak_counter: Counter[int] = Counter()
    trak_by_record: dict[int, Counter[int]] = defaultdict(Counter)
    if trak is not None:
        for rec in trak.records:
            for tri in rec.table_b:
                trak_counter[tri.material_index] += 1
                trak_by_record[rec.index][tri.material_index] += 1

        rows = []
        for mat_idx, count in trak_counter.most_common():
            mat = mat_by_idx.get(mat_idx)
            rows.append({
                "material_index": mat_idx,
                "triangle_count": count,
                "material_in_runtime_table": int(mat is not None),
                **_material_row(mat),
            })
        _write_csv(out_dir / "trak_terrain_material_usage.csv", [
            "material_index", "triangle_count", "material_in_runtime_table",
            "mat_runtime_u16_00", "mat_i8_02_texture_page_candidate", "mat_u8_03",
            "mat_rgb_r", "mat_rgb_g", "mat_rgb_b", "mat_extra",
        ], rows)

        rec_rows = []
        for rec_idx in sorted(trak_by_record):
            top = trak_by_record[rec_idx].most_common(6)
            rec_rows.append({
                "trak_record": rec_idx,
                "unique_materials": len(trak_by_record[rec_idx]),
                "top_materials": " ".join(f"{m}:{c}" for m, c in top),
            })
        _write_csv(out_dir / "trak_materials_by_record.csv", ["trak_record", "unique_materials", "top_materials"], rec_rows)

    stpc_counter: Counter[int] = Counter()
    stpc_by_mesh: dict[int, Counter[int]] = defaultdict(Counter)
    if stpc is not None:
        for mesh in stpc.meshes:
            for tri in mesh.triangles:
                stpc_counter[tri.material] += 1
                stpc_by_mesh[mesh.index][tri.material] += 1

        rows = []
        for mat_idx, count in stpc_counter.most_common():
            mat = mat_by_idx.get(mat_idx)
            rows.append({
                "material_index": mat_idx,
                "triangle_count": count,
                "material_in_runtime_table": int(mat is not None),
                **_material_row(mat),
            })
        _write_csv(out_dir / "stpc_material_usage.csv", [
            "material_index", "triangle_count", "material_in_runtime_table",
            "mat_runtime_u16_00", "mat_i8_02_texture_page_candidate", "mat_u8_03",
            "mat_rgb_r", "mat_rgb_g", "mat_rgb_b", "mat_extra",
        ], rows)

        mesh_rows = []
        for mesh_idx in sorted(stpc_by_mesh):
            top = stpc_by_mesh[mesh_idx].most_common(6)
            mesh_rows.append({
                "stpc_mesh": mesh_idx,
                "unique_materials": len(stpc_by_mesh[mesh_idx]),
                "top_materials": " ".join(f"{m}:{c}" for m, c in top),
            })
        _write_csv(out_dir / "stpc_materials_by_mesh.csv", ["stpc_mesh", "unique_materials", "top_materials"], mesh_rows)

    summary = {
        "material_table_entries": len(materials),
        "terrain_texture_indices_hint": list(terrain_texture_indices),
        "trak_unique_material_indices": len(trak_counter),
        "stpc_unique_material_indices": len(stpc_counter),
        "notes": [
            "dword_581154 is a 20-byte runtime table expanded from the trailing TEXT table.",
            "TRAK/STPC triangle material u16 values are compact indices into this table.",
            "Texture/UV binding is not yet confirmed; texture_05..texture_09 are marked as terrain-priority hints from visual validation.",
        ],
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    (out_dir / "README_materials.txt").write_text(
        "Material diagnostics\n"
        "====================\n\n"
        "Confirmed from the executable:\n"
        "  face.material_index -> dword_581154 + 20 * material_index\n\n"
        "dword_581154 is built from the trailing 8-byte table in TEXT/TXET.\n"
        "This folder reports material usage, but does not claim final UV/texture binding yet.\n"
        "User visual hint: texture_05 through texture_09 are primarily terrain textures.\n",
        encoding="utf-8",
    )
