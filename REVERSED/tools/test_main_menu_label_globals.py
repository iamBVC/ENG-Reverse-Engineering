"""Guard the main-menu Exit string against Ghidra's one-byte data typing."""

import csv
import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class MainMenuLabelGlobalTests(unittest.TestCase):
    def test_exit_label_is_exported_as_a_nul_terminated_string(self):
        with (ROOT / "src_generated" / "type_overrides.csv").open(
            newline="", encoding="utf-8"
        ) as source:
            overrides = {row["name"]: row["type"] for row in csv.DictReader(source)}

        self.assertEqual(overrides.get("DAT_0057a70c"), "string:0x5")

        globals_source = (ROOT / "src_generated" / "ghidra_globals.c").read_text(
            encoding="utf-8"
        )
        self.assertRegex(
            globals_source,
            r"const char DAT_0057a70c\[\] = \{69,115,99,105,0\};",
        )
        self.assertNotRegex(globals_source, r"unsigned char DAT_0057a70c\s*=")
        self.assertRegex(
            globals_source,
            r"PTR_DAT_0057bba0\s*=\s*\(unsigned int \*\)&DAT_0057a70c;",
        )


if __name__ == "__main__":
    unittest.main()
