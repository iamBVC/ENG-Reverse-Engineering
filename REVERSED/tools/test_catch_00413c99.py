"""Preserve the catch-all allocation and continuation in sub_413C40."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Catch00413C99Tests(unittest.TestCase):
    def test_catch_allocates_from_original_length_and_resumes_copy_path(self):
        source = ROOT / "src_recovered" / "Catch_00413c99.c"
        self.assertTrue(source.is_file(), "catch-all must replace unaff_EBP C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp + 8]",
            "[ebp - 14h]",
            "add eax, 2",
            "jge size_ready",
            "call operator_new",
            "offset groove_resume_sub_413c40_continuation",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_ebp", text)

        labels = (ROOT / "harness" / "code_labels.c").read_text(encoding="utf-8").lower()
        for instruction in (
            "groove_resume_sub_413c40_continuation",
            "rep movsd",
            "rep movsb",
            "[ebx + 0ch]",
            "mov dword ptr fs:[0], ecx",
            "ret 4",
        ):
            with self.subTest(continuation=instruction):
                self.assertIn(instruction, labels)


if __name__ == "__main__":
    unittest.main()
