"""Keep the EBP-based exception catch at 0x0040FB87 in original x86 form."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch0040FB87Tests(unittest.TestCase):
    def test_catch_uses_owner_frame_and_relocated_resume_target(self):
        source = ROOT / "src_recovered" / "Catch_0040fb87.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp - 48h]",
            "[ebp - 58h]",
            "[ebp - 4]",
            "call sub_40fbe0",
            "call sub_40fc50",
            "offset sub_40fbca",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("0x40fbca", text)


if __name__ == "__main__":
    unittest.main()
