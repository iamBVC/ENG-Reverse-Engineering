"""Preserve the 0x004125E4 exception catch's frame and resume address."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch004125E4Tests(unittest.TestCase):
    def test_catch_preserves_string_cleanup_and_owner_epilogue(self):
        source = ROOT / "src_recovered" / "Catch_004125e4.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp - 24h]",
            "[ebp - 34h]",
            "[ebp - 4], 4",
            "[ebp - 30h]",
            "call sub_562941",
            "offset groove_resume_sub_412320_epilogue",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)


if __name__ == "__main__":
    unittest.main()
