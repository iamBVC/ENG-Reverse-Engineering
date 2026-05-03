"""world_viewer.py — standalone HTML viewer generation for reconstructed world OBJ files."""

from __future__ import annotations

import json
from pathlib import Path


def _read_template(name: str) -> str:
    return (Path(__file__).with_name("templates") / name).read_text(encoding="utf-8")


def _collect_world_obj_assets(world_dir: Path) -> list[Path]:
    """Collect generated world OBJ files for the standalone viewer.

    The viewer must work when opened directly from file://, so it cannot fetch
    OBJ files.  We embed selected generated OBJ text directly into the HTML.
    Aggregate duplicates are loaded but hidden by default.
    """
    preferred = [
        world_dir / "terrain.obj",
        world_dir / "terrain_textured.obj",
        world_dir / "objects_all_candidates.obj",
        world_dir / "objects_primary.obj",
        world_dir / "map_object_markers.obj",
        world_dir / "combined.obj",
    ]
    assets: list[Path] = [p for p in preferred if p.exists()]
    by_hit = world_dir / "objects_by_hit"
    if by_hit.exists():
        assets.extend(sorted(by_hit.glob("*.obj")))
    seen: set[Path] = set()
    unique: list[Path] = []
    for a in assets:
        rp = a.resolve()
        if rp not in seen:
            seen.add(rp)
            unique.append(a)
    return unique


def write_world_viewer_html(path: Path, obj_assets: list[Path]) -> None:
    """Write a standalone WebGL OBJ viewer.

    No load button and no local server are required.  The generated OBJ contents
    are embedded directly in this HTML, so it works when opened by double-clicking
    the file in a browser.
    """
    world_dir = path.parent
    embedded = []
    for obj_path in obj_assets:
        try:
            rel = obj_path.relative_to(world_dir).as_posix()
        except ValueError:
            rel = obj_path.name
        try:
            text = obj_path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        default_visible = rel in {"terrain.obj", "objects_all_candidates.obj"}
        embedded.append({"name": rel, "text": text, "visible": default_visible})

    payload = json.dumps(embedded, separators=(",", ":"))
    html = _read_template("world_viewer.html").replace("__EMBEDDED_OBJS__", payload)
    path.write_text(html, encoding="utf-8")


# ---------------------------------------------------------------------------
# Public export API
# ---------------------------------------------------------------------------
