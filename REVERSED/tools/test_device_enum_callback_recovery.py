import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src_recovered" / "sub_40EA40.c"


class DeviceEnumCallbackRecoveryTests(unittest.TestCase):
    def test_callback_registers_and_seh_state_are_recovered_from_ghidra_listing(self):
        self.assertTrue(SOURCE.is_file(), "device enumeration callback needs a recovered override")
        source = SOURCE.read_text(encoding="utf-8")

        self.assertRegex(
            source,
            r"undefined4\s+__stdcall\s+sub_40EA40\s*\(\s*int\s*\*\s*param_1\s*,\s*"
            r"(?:undefined4|int)\s+param_2\s*\)",
        )
        self.assertNotRegex(source, r"\bunaff_(?:EBP|EDI)\b")
        self.assertIn("ExceptionList = piStack_c;", source)
        self.assertGreaterEqual(source.count("uStack_4 ="), 3)
        self.assertIn("enumerator = (int *)auStack_14[0]", source)
        self.assertIn("(**(code **)*enumerator)(enumerator", source)
        self.assertNotRegex(source, r"auStack_14\[0\]\s*=\s*(?:1|0xffffffff)")


if __name__ == "__main__":
    unittest.main()
