import csv
import re
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from pe_tools import PE  # noqa: E402


class CameraSineTableTests(unittest.TestCase):
    def test_generated_camera_lookup_matches_original_executable(self):
        overrides = ROOT / "src_generated" / "type_overrides.csv"
        with overrides.open(newline="", encoding="utf-8") as stream:
            types = {row["name"]: row["type"] for row in csv.DictReader(stream)}
        self.assertEqual(types.get("DAT_00574318"), "dwords:0x4000:file")

        globals_source = (ROOT / "src_generated" / "ghidra_globals.c").read_text(
            encoding="utf-8"
        )
        match = re.search(
            r"int DAT_00574318_storage\[4096\] = \{([^}]*)\};", globals_source
        )
        self.assertIsNotNone(match, "regeneration must emit the full lookup table")
        generated = [int(value, 0) & 0xFFFFFFFF for value in match.group(1).split(",")]

        original = PE(ROOT.parent / "Game" / "groove.exe").read(0x00574318, 0x4000)
        expected = [int.from_bytes(original[i : i + 4], "little") for i in range(0, 0x4000, 4)]
        self.assertEqual(len(generated), 4096)
        self.assertEqual(generated, expected)


if __name__ == "__main__":
    unittest.main()
