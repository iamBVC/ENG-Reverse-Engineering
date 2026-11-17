"""Preserve sub_563555's FPU comparison and CL classification result."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class X87Classifier563555Tests(unittest.TestCase):
    def test_classifier_keeps_original_fpu_flags_and_return_register(self):
        source = ROOT / "src_recovered" / "sub_563555.c"
        self.assertTrue(source.is_file(), "x87 helper must replace void pseudo-C")
        text = source.read_text(encoding="utf-8").lower()
        self.assertIn("static const double groove_round_half = 0.5", text)
        for fragment in (
            "__declspec(naked)",
            "fld st(0)",
            "frndint",
            "fcomp st(1)",
            "fnstsw ax",
            "sahf",
            "fmul qword ptr [groove_round_half]",
            "fcompp",
            "mov cl, 0",
            "inc cl",
            "fstp st(0)",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)


if __name__ == "__main__":
    unittest.main()
