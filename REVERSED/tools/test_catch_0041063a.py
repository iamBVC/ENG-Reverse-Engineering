"""Protect the DirectDraw catch funclet's EBP and COM cleanup contract."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch0041063ATests(unittest.TestCase):
    def test_catch_preserves_frame_offsets_and_relocated_epilogue(self):
        source = ROOT / "src_recovered" / "Catch_0041063a.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "call sub_4106c0",
            "[ebp - 14h]",
            "[ebp - 18h]",
            "[ebp - 4ch]",
            "call dword ptr [edx + 8]",
            "call sub_426500",
            "[ebp - 48h]",
            "offset sub_41069e",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("0x41069e", text)


if __name__ == "__main__":
    unittest.main()
