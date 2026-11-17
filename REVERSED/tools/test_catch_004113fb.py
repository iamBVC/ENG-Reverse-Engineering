"""Keep the 0x004113FB catch funclet bound to its owning EBP frame."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch004113FBTests(unittest.TestCase):
    def test_catch_preserves_cleanup_state_and_parent_epilogue(self):
        source = ROOT / "src_recovered" / "Catch_004113fb.c"
        self.assertTrue(source.is_file(), "catch funclet must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "call sub_4114a0",
            "[ebp - 98h]",
            "[ebp - 0b4h]",
            "[ebp - 4]",
            "[ebp - 0b0h]",
            "xor ebx, ebx",
            "call sub_426500",
            "call sub_562941",
            "offset groove_resume_sub_411000_epilogue",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)
        labels = (ROOT / "harness" / "code_labels.c").read_text(encoding="utf-8").lower()
        for instruction in (
            "groove_resume_sub_411000_epilogue",
            "mov ecx, dword ptr [ebp - 0ch]",
            "xor al, al",
            "mov dword ptr fs:[0], ecx",
            "ret",
        ):
            with self.subTest(epilogue=instruction):
                self.assertIn(instruction, labels)


if __name__ == "__main__":
    unittest.main()
