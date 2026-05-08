"""editor_config.py - shared WAD editor configuration helpers."""

from __future__ import annotations

import copy
import json
from pathlib import Path
from typing import Any

CONFIG_PATH = Path(__file__).resolve().parent.parent / "wad_editor_config.json"

DEFAULT_EDITOR_CONFIG: dict[str, Any] = {
    "colors": {
        "background": "#111317",
        "terrain": "#465a6e",
        "terrain_edge": "#283c50",
        "terrain_selected": "#e6d05c",
        "object_marker": "#f0b43c",
        "object_selected": "#ff5050",
        "object_mesh": "#b66cff",
        "object_mesh_selected": "#ff7ad9",
        "gizmo_x": "#ff4d4d",
        "gizmo_y": "#55d66b",
        "gizmo_z": "#4d8dff",
    },
    "viewport": {
        "object_radius": 6,
        "gizmo_axis_scale": 0.06,
        "gizmo_min_length": 1.0,
        "max_render_tris": 8000,
    },
}


def _hex_to_rgb(value: str, fallback: tuple[int, int, int]) -> tuple[int, int, int]:
    text = str(value).strip()
    if text.startswith("#") and len(text) == 7:
        try:
            return int(text[1:3], 16), int(text[3:5], 16), int(text[5:7], 16)
        except ValueError:
            pass
    return fallback


def _deep_update(dst: dict[str, Any], src: dict[str, Any]) -> dict[str, Any]:
    for key, value in src.items():
        if isinstance(value, dict) and isinstance(dst.get(key), dict):
            _deep_update(dst[key], value)
        else:
            dst[key] = value
    return dst


def load_editor_config() -> dict[str, Any]:
    """Load config from WAD/wad_editor_config.json, creating it on first run."""
    cfg = copy.deepcopy(DEFAULT_EDITOR_CONFIG)
    if CONFIG_PATH.exists():
        try:
            data = json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
            if isinstance(data, dict):
                _deep_update(cfg, data)
        except Exception:
            pass
    else:
        save_editor_config(cfg)
    return cfg


def save_editor_config(cfg: dict[str, Any]) -> None:
    CONFIG_PATH.write_text(json.dumps(cfg, indent=2), encoding="utf-8")


def cfg_color(
    cfg: dict[str, Any],
    name: str,
    fallback: tuple[int, int, int],
) -> tuple[int, int, int]:
    return _hex_to_rgb(cfg.get("colors", {}).get(name, ""), fallback)
