"""Keep the 0x004122B2 cleanup sequence attached to its parent frame."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch004122B2Tests(unittest.TestCase):
    def test_catch_preserves_cleanup_calls_state_and_resume_target(self):
        source = ROOT / "src_recovered" / "Catch_004122b2.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp - 20h]",
            "call sub_413390",
            "call sub_562941",
            "[ebp + 0ch]",
            "[ebp - 50h]",
            "[ebp - 4], 3",
            "call sub_413bf0",
            "call sub_40fbe0",
            "offset groove_resume_sub_411d60_epilogue",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)


if __name__ == "__main__":
    unittest.main()
