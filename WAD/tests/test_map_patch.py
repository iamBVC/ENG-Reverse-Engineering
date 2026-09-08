from __future__ import annotations

import struct
import unittest
from types import SimpleNamespace

from eng_wad.map_patch import (
    OBJ_RECORD_SIZE,
    add_object_to_map_chunk,
    delete_object_from_map_chunk,
    patch_map_chunk_object,
    patch_map_section2_locals,
)


def _object(index: int, file_offset: int) -> SimpleNamespace:
    return SimpleNamespace(
        index=index,
        file_offset=file_offset,
        rot_x_units=0,
        rot_y_units=0,
        rot_z_units=0,
        pos_x_fixed12=index * 4096,
        pos_y_fixed12=0,
        pos_z_fixed12=0,
        script_offset=0x00420000 + index,
        local_count=0,
        section2_index_raw=0xFFFFFFFF,
        stack_word_count=9,
        stack_arg_count=0,
        spawn_flags=0x8000,
        extra_count=0,
        section4_index_raw=0xFFFFFFFF,
        spawn_aux_raw=0,
        flags=0,
        extra_u16=0,
    )


class MapPatchTests(unittest.TestCase):
    def setUp(self) -> None:
        self.first_offset = 16
        self.objects = [
            _object(0, self.first_offset),
            _object(1, self.first_offset + OBJ_RECORD_SIZE),
        ]
        records = bytes([0x11]) * OBJ_RECORD_SIZE + bytes([0x22]) * OBJ_RECORD_SIZE
        self.tail = b"TAIL"
        self.chunk = b"PREFIX00" + struct.pack("<II", 2, 2) + records + self.tail
        self.mapx = SimpleNamespace(objects=self.objects, object_count_unknown_b=2)

    def test_add_updates_both_counts_and_preserves_existing_data(self) -> None:
        new_record = bytes([0x33]) * OBJ_RECORD_SIZE
        result = add_object_to_map_chunk(self.chunk, self.mapx, new_record)

        self.assertEqual(struct.unpack_from("<II", result, 8), (3, 3))
        self.assertEqual(result[16:16 + 2 * OBJ_RECORD_SIZE],
                         self.chunk[16:16 + 2 * OBJ_RECORD_SIZE])
        self.assertEqual(result[16 + 2 * OBJ_RECORD_SIZE:
                                16 + 3 * OBJ_RECORD_SIZE], new_record)
        self.assertTrue(result.endswith(self.tail))

    def test_delete_updates_both_counts_and_preserves_tail(self) -> None:
        result = delete_object_from_map_chunk(self.chunk, self.mapx, self.objects[0])

        self.assertEqual(struct.unpack_from("<II", result, 8), (1, 1))
        self.assertEqual(result[16:16 + OBJ_RECORD_SIZE],
                         bytes([0x22]) * OBJ_RECORD_SIZE)
        self.assertTrue(result.endswith(self.tail))

    def test_add_rejects_wrong_record_size(self) -> None:
        with self.assertRaisesRegex(ValueError, "must be 58 bytes"):
            add_object_to_map_chunk(self.chunk, self.mapx, b"short")

    def test_patch_rejects_out_of_bounds_offset(self) -> None:
        obj = _object(0, len(self.chunk))
        with self.assertRaisesRegex(ValueError, "outside"):
            patch_map_chunk_object(self.chunk, obj)

    def test_patch_section2_locals_updates_only_selected_slice(self) -> None:
        # 12-byte header, one 24-byte tile, count, then four u32 locals.
        chunk = bytearray(80)
        struct.pack_into("<III", chunk, 0, 1, 0, 0)
        struct.pack_into("<I4I", chunk, 36, 4, 10, 20, 30, 40)
        obj = _object(0, 0)
        obj.local_count = 2
        obj.section2_index_raw = 1
        mapx = SimpleNamespace(tile_count=1, section2=[10, 20, 30, 40])

        result = patch_map_section2_locals(bytes(chunk), mapx, obj,
                                           [0xFFFFFFFF, 0x00001000])

        self.assertEqual(struct.unpack_from("<4I", result, 40),
                         (10, 0xFFFFFFFF, 0x1000, 40))

    def test_patch_section2_locals_rejects_invalid_slice(self) -> None:
        obj = _object(0, 0)
        obj.local_count = 2
        obj.section2_index_raw = 3
        mapx = SimpleNamespace(tile_count=0, section2=[1, 2, 3, 4])
        with self.assertRaisesRegex(ValueError, "outside"):
            patch_map_section2_locals(bytes(64), mapx, obj, [5, 6])


if __name__ == "__main__":
    unittest.main()
