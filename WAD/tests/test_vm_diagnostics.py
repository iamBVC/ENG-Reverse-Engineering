from __future__ import annotations

import struct
import unittest

from eng_wad.world_rebuild import _vm_stream_table_payload_size


class VmDiagnosticTests(unittest.TestCase):
    def test_stream_table_payload_size_handles_extended_entries(self) -> None:
        payload = (
            struct.pack("<I", 3)
            + struct.pack("<I", 0x0044)
            + struct.pack("<II", 0x0045, 0x12345678)
            + struct.pack("<II", 0x00EA, 0x90ABCDEF)
        )
        self.assertEqual(_vm_stream_table_payload_size(payload, 0), len(payload))

    def test_truncated_stream_table_is_bounded(self) -> None:
        payload = struct.pack("<II", 2, 0x0045)
        self.assertEqual(_vm_stream_table_payload_size(payload, 0), len(payload))


if __name__ == "__main__":
    unittest.main()
