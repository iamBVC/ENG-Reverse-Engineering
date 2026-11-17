"""Ensure the recovered catch entry shares the already verified exact handler."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch00410E52Tests(unittest.TestCase):
    def test_catch_entry_tail_dispatches_without_changing_owner_frame(self):
        source = ROOT / "src_recovered" / "Catch_00410e52.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        self.assertIn("__declspec(naked)", text)
        self.assertIn("jmp groove_catch_handler_impl", text)
        self.assertIn("extern int __cdecl groove_catch_handler_impl(void)", text)


if __name__ == "__main__":
    unittest.main()
