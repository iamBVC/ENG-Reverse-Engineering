"""wfpc_chunk.py - WFPC WAD feature/capability flags.

The executable loader copies the 4-byte WFPC payload into global dword_6DA330.
Later chunk parsers test individual bits to decide whether optional fields are
present.  This module keeps the disk parser intentionally small and exports
flag diagnostics with confirmed consumers where they are known.
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class WfpcFlagInfo:
    bit: int
    mask: int
    name: str
    status: str
    consumer: str
    meaning: str


WFPC_FLAGS: dict[int, WfpcFlagInfo] = {
    0x00000010: WfpcFlagInfo(
        4, 0x00000010, "map_final_optional_dword", "confirmed",
        "sub_42AC50 / loc_42BECC",
        "MAP has final_optional_dword before final_u16; otherwise runtime defaults dword_6DA328 to 200.",
    ),
    0x00000100: WfpcFlagInfo(
        8, 0x00000100, "stpc_extra_tail_records", "confirmed_loader_unobserved",
        "sub_42AB50 / loc_42ABE8",
        "STPC loader reads an extra count and repeats 16-byte headers with variable 8-byte subrecords.",
    ),
    0x00000800: WfpcFlagInfo(
        11, 0x00000800, "render_init_option", "confirmed_runtime",
        "sub_419676 and nearby init paths",
        "Passed into sub_424B60/sub_424B90 during render/camera initialization.",
    ),
    0x00010000: WfpcFlagInfo(
        16, 0x00010000, "map_optional20", "confirmed",
        "sub_42AC50 / loc_42B273",
        "MAP includes optional 20-byte records and extra vertex-color blocks for marked tiles.",
    ),
    0x00080000: WfpcFlagInfo(
        19, 0x00080000, "script_dispatch_option_142", "confirmed_runtime",
        "sub_550E60 jump-table case 142",
        "Passed to sub_54BBD0 from a script/function dispatch path; semantic name still unknown.",
    ),
    0x00100000: WfpcFlagInfo(
        20, 0x00100000, "sprt_optional_table", "confirmed_loader_unobserved",
        "SPRT branch at loc_558AD1",
        "SPRT includes optional_count plus optional u32 table after material_base_index.",
    ),
    0x00200000: WfpcFlagInfo(
        21, 0x00200000, "map_chain_table", "confirmed_loader_unobserved",
        "sub_42AC50 / loc_42BBFB",
        "MAP includes a global chain/table structure at dword_6D9C90/dword_6D9CC0.",
    ),
    0x04000000: WfpcFlagInfo(
        26, 0x04000000, "map_chain_record_extra_dword", "confirmed_loader_unobserved",
        "sub_42AC50 / loc_42BD57",
        "When map_chain_table is present, each chain record includes an extra dword at runtime +0x14.",
    ),
    0x10000000: WfpcFlagInfo(
        28, 0x10000000, "map_extended_tile_vertex_lists", "confirmed",
        "sub_42AC50 / loc_42B335; sub_42C790; STPC/MAP placement checks",
        "MAP allocates wider per-tile vertex-list pointers and uses optional20 records in follow-up processing.",
    ),
}


@dataclass(frozen=True)
class WfpcChunk:
    flags: int
    raw_size: int

    def has(self, mask: int) -> bool:
        return bool(self.flags & mask)

    @property
    def active_masks(self) -> list[int]:
        return [1 << bit for bit in range(32) if self.flags & (1 << bit)]

    @property
    def unknown_active_masks(self) -> list[int]:
        return [mask for mask in self.active_masks if mask not in WFPC_FLAGS]


def parse_wfpc_chunk(data: bytes) -> WfpcChunk:
    if len(data) < 4:
        raise ValueError(f"WFPC chunk is too small: {len(data)} bytes")
    if len(data) != 4:
        raise ValueError(f"WFPC chunk has unsupported size: {len(data)} bytes")
    return WfpcChunk(flags=struct.unpack_from("<I", data, 0)[0], raw_size=len(data))


def _flag_row(mask: int, active: bool) -> dict:
    info = WFPC_FLAGS.get(mask)
    if info is None:
        bit = mask.bit_length() - 1
        return {
            "bit": bit,
            "mask_hex": f"0x{mask:08X}",
            "active": active,
            "name": "unknown_observed_flag",
            "status": "observed_only" if active else "unknown",
            "consumer": "",
            "meaning": "Active in at least one tested WAD, but no dword_6DA330 consumer has been confirmed yet." if active else "",
        }
    return {
        "bit": info.bit,
        "mask_hex": f"0x{info.mask:08X}",
        "active": active,
        "name": info.name,
        "status": info.status,
        "consumer": info.consumer,
        "meaning": info.meaning,
    }


def export_wfpc(wfpc: WfpcChunk, out_dir: Path) -> dict:
    out_dir.mkdir(parents=True, exist_ok=True)
    known_masks = set(WFPC_FLAGS)
    masks_to_write = sorted(known_masks | set(wfpc.active_masks))

    summary = {
        "raw_size": wfpc.raw_size,
        "flags": wfpc.flags,
        "flags_hex": f"0x{wfpc.flags:08X}",
        "active_masks": [f"0x{mask:08X}" for mask in wfpc.active_masks],
        "unknown_active_masks": [f"0x{mask:08X}" for mask in wfpc.unknown_active_masks],
        "confirmed_loader": "WFPC payload is copied directly into dword_6DA330; later chunk loaders test individual bits for optional structures.",
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    with (out_dir / "flags.csv").open("w", newline="", encoding="utf-8") as f:
        fieldnames = ["bit", "mask_hex", "active", "name", "status", "consumer", "meaning"]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for mask in masks_to_write:
            w.writerow(_flag_row(mask, wfpc.has(mask)))

    return summary
