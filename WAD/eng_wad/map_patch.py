"""map_patch.py — MAP chunk object-record patching utilities.

All functions operate on the raw MAP chunk bytes and the parsed MapFullExe
structure; they are format-agnostic helpers that any tool can import.

On-disk object record layout (58 bytes, little-endian):
    3H   rot_x_units, rot_y_units, rot_z_units
    3i   pos_x_fixed12, pos_y_fixed12, pos_z_fixed12  (world = val / 4096.0)
    9I   script_offset, local_count, section2_index_raw,
         stack_word_count, stack_arg_count, spawn_flags,
         extra_count, section4_index_raw, spawn_aux_raw
    2H   flags, extra_u16
"""

from __future__ import annotations

import copy
import struct
from collections import Counter

OBJ_RECORD_FMT  = "<3H3i9I2H"
OBJ_RECORD_SIZE = struct.calcsize(OBJ_RECORD_FMT)   # 58 bytes


def pack_map_object(obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    """Serialise a MapObjectRecord back to its 58-byte on-disk representation."""
    return struct.pack(OBJ_RECORD_FMT,
        obj.rot_x_units, obj.rot_y_units, obj.rot_z_units,
        obj.pos_x_fixed12, obj.pos_y_fixed12, obj.pos_z_fixed12,
        obj.script_offset, obj.local_count, obj.section2_index_raw,
        obj.stack_word_count, obj.stack_arg_count, obj.spawn_flags,
        obj.extra_count, obj.section4_index_raw, obj.spawn_aux_raw,
        obj.flags, obj.extra_u16)


def patch_map_chunk_object(map_data: bytes,
                           obj: "MapObjectRecord") -> bytes:  # type: ignore[name-defined]
    """Overwrite the on-disk record for *obj* with its current field values."""
    data = bytearray(map_data)
    off  = obj.file_offset
    data[off: off + OBJ_RECORD_SIZE] = pack_map_object(obj)
    return bytes(data)


def add_object_to_map_chunk(
    map_data: bytes,
    mapx: "MapFullExe",       # type: ignore[name-defined]
    new_obj_raw: bytes,
    *,
    assume_final_dword: bool = True,
) -> bytes:
    """Insert a new 58-byte object record into the MAP chunk and update the count.

    The record is appended after the last existing object.  The 4-byte count
    field (located 8 bytes before the first record) is incremented.
    """
    if not mapx.objects:
        return map_data  # cannot locate section without at least one existing object
    count_off = mapx.objects[0].file_offset - 8   # 4-byte count + 4-byte unknown_b
    last_end  = mapx.objects[-1].file_offset + OBJ_RECORD_SIZE
    prefix    = map_data[:count_off]
    tail      = map_data[last_end:]
    existing  = map_data[mapx.objects[0].file_offset: last_end]
    return (prefix
            + struct.pack("<I", len(mapx.objects) + 1)
            + struct.pack("<I", mapx.object_count_unknown_b)
            + existing + new_obj_raw + tail)


def delete_object_from_map_chunk(
    map_data: bytes,
    mapx: "MapFullExe",       # type: ignore[name-defined]
    obj: "MapObjectRecord",   # type: ignore[name-defined]
) -> bytes:
    """Remove one 58-byte object record from the MAP chunk and update the count."""
    if not mapx.objects or not any(o.file_offset == obj.file_offset
                                   for o in mapx.objects):
        return map_data
    if len(mapx.objects) <= 1:
        raise ValueError(
            "Cannot delete the only MAP object; "
            "object table location would be ambiguous.")
    count_off = mapx.objects[0].file_offset - 8
    first_off = mapx.objects[0].file_offset
    last_end  = mapx.objects[-1].file_offset + OBJ_RECORD_SIZE
    prefix    = map_data[:count_off]
    tail      = map_data[last_end:]
    existing  = bytearray(map_data[first_off:last_end])
    rel       = obj.file_offset - first_off
    del existing[rel: rel + OBJ_RECORD_SIZE]
    return (prefix
            + struct.pack("<I", len(mapx.objects) - 1)
            + struct.pack("<I", mapx.object_count_unknown_b)
            + bytes(existing) + tail)


def make_object_copy(template: "MapObjectRecord",  # type: ignore[name-defined]
                     new_index: int) -> "MapObjectRecord":  # type: ignore[name-defined]
    """Return a shallow copy of *template* with a placeholder index/offset."""
    obj = copy.copy(template)
    obj.index       = new_index
    obj.file_offset = 0   # will be assigned after patch
    return obj


def build_type_registry(
    objects: list,
    names: dict[int, str] | None = None,
) -> list[tuple[int, str]]:
    """Return [(script_offset, label)] sorted by instance count desc.

    When *names* is supplied, labels include the human-readable name:
        'KidOnLlama  0x0042310E  (×3)'
    otherwise:
        '0x0042310E  (×3 inst.)'
    """
    counts = Counter(o.script_offset for o in objects)
    result = []
    for off, cnt in sorted(counts.items(), key=lambda x: (-x[1], x[0])):
        name = (names or {}).get(off, "")
        label = (f"{name}  0x{off:08X}  (×{cnt})" if name
                 else f"0x{off:08X}  (×{cnt} inst.)")
        result.append((off, label))
    return result
