"""Preserve sub_5683B9's owner-frame state write and CL flag contract."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Sub5683B9Tests(unittest.TestCase):
    def test_helper_uses_incoming_ebp_and_updates_flags_from_cl(self):
        source = ROOT / "src_recovered" / "sub_5683B9.c"
        self.assertTrue(source.is_file(), "helper must replace unaff_EBP pseudo-C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "mov byte ptr [ebp - 90h], 1",
            "or cl, cl",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)


if __name__ == "__main__":
    unittest.main()
