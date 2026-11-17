"""Tests for targeted render-queue corruption diagnostics in generated C."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import make_bulk


class RenderQueueDiagnosticTests(unittest.TestCase):
    def test_queue_head_stores_are_traced_but_queue_clears_are_not(self):
        source = (
            "  (&DAT_005f6ef8)[iVar21] = puVar17;\n"
            "  (&DAT_005f6ef8)[iVar7] = 0;\n"
        )
        instrument = getattr(make_bulk, "instrument_render_queue_writes", None)
        self.assertIsNotNone(instrument)
        observed = instrument(source, "sub_41FB30")
        self.assertIn("[queue-store] fn=sub_41FB30", observed)
        self.assertIn("(&DAT_005f6ef8)[iVar21] = puVar17;", observed)
        self.assertIn("(&DAT_005f6ef8)[iVar7] = 0;", observed)
        self.assertEqual(observed.count("[queue-store]"), 1)


if __name__ == "__main__":
    unittest.main()
