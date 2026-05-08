"""obj_mesh.py - lightweight OBJ mesh readers used by WAD tools."""

from __future__ import annotations

import re
from pathlib import Path


def parse_placed_object_obj(
    path: Path,
    *,
    existing_objects: set[int] | None = None,
) -> list[tuple[list, int, float]]:
    """Read placed OBJ triangles grouped by names like object_000_primary_mesh_000."""
    if not path.exists():
        return []

    verts: list[list[float]] = []
    tris: list[tuple[list, int, float]] = []
    current_obj = -1
    seen = existing_objects if existing_objects is not None else set()
    obj_re = re.compile(r"object_(\d+)_")

    try:
        for raw in path.read_text(encoding="utf-8", errors="replace").splitlines():
            line = raw.strip()
            if line.startswith("o "):
                m = obj_re.search(line)
                current_obj = int(m.group(1)) if m else -1
                if current_obj in seen:
                    current_obj = -1
            elif line.startswith("v "):
                parts = line.split()
                if len(parts) >= 4:
                    try:
                        verts.append([float(parts[1]), float(parts[2]), float(parts[3])])
                    except ValueError:
                        pass
            elif line.startswith("f ") and current_obj >= 0:
                idxs: list[int] = []
                for part in line.split()[1:]:
                    try:
                        idx = int(part.split("/")[0])
                    except ValueError:
                        continue
                    if idx < 0:
                        idx = len(verts) + idx + 1
                    idxs.append(idx - 1)
                if len(idxs) >= 3:
                    for i in range(1, len(idxs) - 1):
                        if all(0 <= j < len(verts) for j in (idxs[0], idxs[i], idxs[i + 1])):
                            tri = [verts[idxs[0]], verts[idxs[i]], verts[idxs[i + 1]]]
                            cy = (tri[0][1] + tri[1][1] + tri[2][1]) / 3.0
                            tris.append((tri, current_obj, cy))
                            seen.add(current_obj)
    except OSError:
        return []

    return tris
