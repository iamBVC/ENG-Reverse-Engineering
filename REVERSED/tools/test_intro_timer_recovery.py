"""Protect original 32-bit timer and message-buffer layout during regeneration."""

import csv
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class IntroTimerRecoveryTests(unittest.TestCase):
    def test_timer_and_text_buffer_match_original_storage_widths(self):
        with (ROOT / "src_generated" / "type_overrides.csv").open(newline="", encoding="utf-8") as stream:
            overrides = {row["name"]: row["type"] for row in csv.DictReader(stream)}
        self.assertEqual(overrides.get("DAT_005839d0"), "int")
        self.assertEqual(overrides.get("DAT_00583988"), "array:0x8")
        self.assertEqual(overrides.get("DAT_00571e30"), "record:0x18:file")
        self.assertEqual(overrides.get("DAT_00571e3c"), "int")
        self.assertEqual(overrides.get("DAT_00571e40"), "pointer")
        self.assertEqual(overrides.get("DAT_00571e44"), "pointer")

        globals_c = (ROOT / "src_generated" / "ghidra_globals.c").read_text(encoding="utf-8")
        self.assertIn("int DAT_005839d0;", globals_c)
        self.assertIn("int DAT_00583988[2];", globals_c)
        record_line = next(line for line in globals_c.splitlines()
                           if line.startswith("int DAT_00571e30_storage[6]"))
        self.assertIn("(int)&DAT_00571DE8", record_line)
        self.assertIn("(int)&sub_417FA0", record_line)

    def test_intro_timeout_body_has_no_unresolved_decompiler_artifacts(self):
        source = (ROOT / "src_recovered" / "sub_417FA0.c").read_text(encoding="utf-8")
        self.assertIn("DAT_00571DE8", source)
        self.assertIn("DAT_00583988", source)
        self.assertIn("sub_418050()", source)
        self.assertNotIn("uRam00571de8", source)
        self.assertNotIn("func_0x00418050", source)

        chunks = ROOT / "build" / "exe_chunks"
        self.assertTrue(any("/* ==== sub_417FA0 ==== */" in path.read_text(encoding="utf-8")
                            for path in chunks.glob("*.c")))
        stubs = (ROOT / "src_generated" / "link_stubs.csv").read_text(encoding="utf-8")
        self.assertNotIn(",sub_417FA0,", stubs)


if __name__ == "__main__":
    unittest.main()
