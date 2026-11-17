"""Preserve sub_568430's x87 result and untouched integer registers."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class X87PowerHelper568430Tests(unittest.TestCase):
    def test_helper_keeps_original_x87_sequence_without_clobbering_eax_or_cl(self):
        source = ROOT / "src_recovered" / "sub_568430.c"
        self.assertTrue(source.is_file(), "FPU helper must replace the expression pseudo-C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) int sub_568430(void)",
            "fld st(0)",
            "frndint",
            "fsubr st(1), st(0)",
            "fxch st(1)",
            "fchs",
            "f2xm1",
            "fld1",
            "faddp st(1), st(0)",
            "fscale",
            "fstp st(1)",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)


if __name__ == "__main__":
    unittest.main()
