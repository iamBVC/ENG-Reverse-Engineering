"""Protect the original EBP-based heap cleanup thunk at 0x0056d6a0."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class UnwindThunkTests(unittest.TestCase):
    def test_56d6a0_uses_the_owner_frame_and_operator_delete(self):
        source = ROOT / "src_recovered" / "Unwind_0056d6a0.c"
        self.assertTrue(source.is_file(), "cleanup thunk must override the unaff_EBP translation")
        text = source.read_text(encoding="utf-8").lower()
        for instruction in (
            "__declspec(naked)",
            "mov eax, dword ptr [ebp - 10h]",
            "push eax",
            "call sub_562941",
            "pop ecx",
            "ret",
        ):
            with self.subTest(instruction=instruction):
                self.assertIn(instruction, text)


if __name__ == "__main__":
    unittest.main()
