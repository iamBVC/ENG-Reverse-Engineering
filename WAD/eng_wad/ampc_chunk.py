"""ampc_chunk.py - executable-confirmed AMPC ambient-audio table.

AMPC is dispatched only when the audio system is active.  The WAD loader
sub_558D70 reads the first u32 into the level/audio context at +0x24 and then
delegates to sub_545350(..., 4).  That case reads a small resource-bank table
followed by 40-byte ambient emitter descriptors.
"""

from __future__ import annotations

import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path


AMPC_RESOURCE_RECORD_SIZE = 12
AMPC_AMBIENT_RECORD_SIZE = 40


def _fixed12(v: int) -> float:
    return v / 4096.0


def _ascii_tag(data: bytes) -> str:
    text = "".join(chr(b) if 32 <= b < 127 else "." for b in data[:4])
    return text


@dataclass(frozen=True)
class AmpcResource:
    index: int
    file_offset: int
    resource_id_00: int
    magic_04: int
    payload_size_08: int
    payload_offset: int
    payload: bytes

    @property
    def magic_ascii(self) -> str:
        return self.magic_04.to_bytes(4, "little", signed=False).decode("latin-1", errors="replace")

    @property
    def payload_magic_ascii(self) -> str:
        return _ascii_tag(self.payload)


@dataclass(frozen=True)
class AmpcAmbientRecord:
    index: int
    file_offset: int
    raw: bytes
    pos_x_fixed12_00: int
    pos_y_fixed12_04: int
    pos_z_fixed12_08: int
    unknown_0C: int
    near_distance_10: int
    far_distance_14: int
    sound_id_flags_18: int
    target_volume_1C: int
    runtime_active_mask_20: int
    runtime_current_level_24: int

    @property
    def sound_id(self) -> int:
        return self.sound_id_flags_18 & 0xFFFF

    @property
    def special_global_volume_bit(self) -> bool:
        return bool(self.sound_id_flags_18 & 0x10000)


@dataclass(frozen=True)
class AmpcChunk:
    resource_count: int
    resources: list[AmpcResource]
    ambient_count: int
    ambient_records: list[AmpcAmbientRecord]
    raw_size: int
    parsed_size: int


def parse_ampc_chunk(data: bytes) -> AmpcChunk:
    if len(data) < 4:
        raise ValueError(f"AMPC chunk is too small: {len(data)} bytes")

    off = 0
    resource_count = struct.unpack_from("<I", data, off)[0]
    off += 4
    resources: list[AmpcResource] = []
    for i in range(resource_count):
        if off + AMPC_RESOURCE_RECORD_SIZE > len(data):
            raise ValueError(f"AMPC resource {i} header reads past end")
        file_offset = off
        resource_id_00, magic_04, payload_size_08 = struct.unpack_from("<III", data, off)
        off += AMPC_RESOURCE_RECORD_SIZE
        if off + payload_size_08 > len(data):
            raise ValueError(f"AMPC resource {i} payload needs {payload_size_08} bytes, chunk has {len(data) - off}")
        payload = data[off:off + payload_size_08]
        resources.append(AmpcResource(
            index=i,
            file_offset=file_offset,
            resource_id_00=resource_id_00,
            magic_04=magic_04,
            payload_size_08=payload_size_08,
            payload_offset=off,
            payload=payload,
        ))
        off += payload_size_08

    if off + 4 > len(data):
        raise ValueError("AMPC missing ambient descriptor count")
    ambient_count = struct.unpack_from("<I", data, off)[0]
    off += 4
    ambient_records: list[AmpcAmbientRecord] = []
    for i in range(ambient_count):
        if off + AMPC_AMBIENT_RECORD_SIZE > len(data):
            raise ValueError(f"AMPC ambient record {i} reads past end")
        raw = data[off:off + AMPC_AMBIENT_RECORD_SIZE]
        ambient_records.append(AmpcAmbientRecord(
            index=i,
            file_offset=off,
            raw=raw,
            pos_x_fixed12_00=struct.unpack_from("<i", raw, 0)[0],
            pos_y_fixed12_04=struct.unpack_from("<i", raw, 4)[0],
            pos_z_fixed12_08=struct.unpack_from("<i", raw, 8)[0],
            unknown_0C=struct.unpack_from("<I", raw, 12)[0],
            near_distance_10=struct.unpack_from("<I", raw, 16)[0],
            far_distance_14=struct.unpack_from("<I", raw, 20)[0],
            sound_id_flags_18=struct.unpack_from("<I", raw, 24)[0],
            target_volume_1C=struct.unpack_from("<I", raw, 28)[0],
            runtime_active_mask_20=struct.unpack_from("<I", raw, 32)[0],
            runtime_current_level_24=struct.unpack_from("<I", raw, 36)[0],
        ))
        off += AMPC_AMBIENT_RECORD_SIZE

    return AmpcChunk(
        resource_count=resource_count,
        resources=resources,
        ambient_count=ambient_count,
        ambient_records=ambient_records,
        raw_size=len(data),
        parsed_size=off,
    )


def export_ampc(ampc: AmpcChunk, out_dir: Path, *, export_payloads: bool = True) -> dict:
    out_dir.mkdir(parents=True, exist_ok=True)

    summary = {
        "raw_size": ampc.raw_size,
        "parsed_size": ampc.parsed_size,
        "parsed_all_bytes": ampc.raw_size == ampc.parsed_size,
        "resource_count": ampc.resource_count,
        "ambient_record_count": ampc.ambient_count,
        "confirmed_loader": "AMPC reads a u32 resource count into context+0x24, then sub_545350(..., 4) parses resource blobs and 40-byte ambient records.",
        "confirmed_consumers": "Ambient evaluation uses record +0x00/+0x08 as horizontal position, +0x10/+0x14 as near/far distance gates, +0x18 as sound id/flags, +0x1C as target volume, and +0x20/+0x24 as runtime state.",
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    (out_dir / "summary.txt").write_text("\n".join(f"{k}: {v}" for k, v in summary.items()) + "\n", encoding="utf-8")

    with (out_dir / "resources.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=[
            "index", "file_offset", "resource_id_00", "resource_id_00_hex",
            "magic_04", "magic_04_hex", "payload_size_08", "payload_offset",
            "payload_magic_ascii", "payload_file",
        ])
        w.writeheader()
        for r in ampc.resources:
            payload_name = f"resource_{r.index:02d}_{r.payload_magic_ascii.strip() or 'bin'}.bin"
            if export_payloads:
                (out_dir / "resource_payloads").mkdir(parents=True, exist_ok=True)
                (out_dir / "resource_payloads" / payload_name).write_bytes(r.payload)
            w.writerow({
                "index": r.index,
                "file_offset": r.file_offset,
                "resource_id_00": r.resource_id_00,
                "resource_id_00_hex": f"0x{r.resource_id_00:08X}",
                "magic_04": r.magic_ascii,
                "magic_04_hex": f"0x{r.magic_04:08X}",
                "payload_size_08": r.payload_size_08,
                "payload_offset": r.payload_offset,
                "payload_magic_ascii": r.payload_magic_ascii,
                "payload_file": f"resource_payloads/{payload_name}" if export_payloads else "",
            })

    with (out_dir / "ambient_records_40.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=[
            "index", "file_offset", "raw_hex",
            "pos_x_fixed12_00", "pos_x", "pos_y_fixed12_04", "pos_y", "pos_z_fixed12_08", "pos_z",
            "unknown_0C",
            "near_distance_10", "near_distance_fixed12",
            "far_distance_14", "far_distance_fixed12",
            "sound_id_flags_18", "sound_id_flags_18_hex", "sound_id", "special_global_volume_bit",
            "target_volume_1C", "runtime_active_mask_20", "runtime_current_level_24",
        ])
        w.writeheader()
        for r in ampc.ambient_records:
            w.writerow({
                "index": r.index,
                "file_offset": r.file_offset,
                "raw_hex": r.raw.hex(" "),
                "pos_x_fixed12_00": r.pos_x_fixed12_00,
                "pos_x": _fixed12(r.pos_x_fixed12_00),
                "pos_y_fixed12_04": r.pos_y_fixed12_04,
                "pos_y": _fixed12(r.pos_y_fixed12_04),
                "pos_z_fixed12_08": r.pos_z_fixed12_08,
                "pos_z": _fixed12(r.pos_z_fixed12_08),
                "unknown_0C": r.unknown_0C,
                "near_distance_10": r.near_distance_10,
                "near_distance_fixed12": _fixed12(r.near_distance_10),
                "far_distance_14": r.far_distance_14,
                "far_distance_fixed12": _fixed12(r.far_distance_14),
                "sound_id_flags_18": r.sound_id_flags_18,
                "sound_id_flags_18_hex": f"0x{r.sound_id_flags_18:08X}",
                "sound_id": r.sound_id,
                "special_global_volume_bit": r.special_global_volume_bit,
                "target_volume_1C": r.target_volume_1C,
                "runtime_active_mask_20": r.runtime_active_mask_20,
                "runtime_current_level_24": r.runtime_current_level_24,
            })

    return summary
