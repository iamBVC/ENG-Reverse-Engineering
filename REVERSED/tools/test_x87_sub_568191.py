"""Preserve the x87 integer/half-integer classifier in sub_568191."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class X87Classifier568191Tests(unittest.TestCase):
    def test_classifier_preserves_st0_and_returns_original_eax_codes(self):
        source = ROOT / "src_recovered" / "sub_568191.c"
        self.assertTrue(source.is_file(), "classifier must replace FPU pseudo-register C")
        text = source.read_text(encoding="utf-8").lower()
        self.assertIn("static const double groove_half = 0.5", text)
        for fragment in (
            "__declspec(naked) int sub_568191(void)",
            "fld st(0)",
            "frndint",
            "fcomp st(1)",
            "fnstsw ax",
            "sahf",
            "fmul qword ptr [groove_half]",
            "fcompp",
            "mov eax, 0",
            "mov eax, 1",
            "mov eax, 2",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)


if __name__ == "__main__":
    unittest.main()
