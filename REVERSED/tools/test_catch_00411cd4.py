"""Keep the 0x00411CD4 catch's interface and string cleanup intact."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch00411CD4Tests(unittest.TestCase):
    def test_catch_releases_frame_resources_and_returns_owner_cleanup(self):
        source = ROOT / "src_recovered" / "Catch_00411cd4.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp - 24h]",
            "[ebp - 28h]",
            "[ebp - 18h]",
            "[ebp - 1ch]",
            "call sub_413170",
            "call sub_562941",
            "[ebp - 80h]",
            "[ebp - 90h]",
            "[ebp - 4], 3",
            "call sub_413bf0",
            "call sub_40fbe0",
            "offset groove_resume_callback_epilogue",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)


if __name__ == "__main__":
    unittest.main()
