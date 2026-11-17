"""Behavioral checks for x87 operations Ghidra emitted as unresolved C calls."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class X87MathRecoveryTests(unittest.TestCase):
    def test_helpers_match_x87_math_and_extract_low_double_words(self):
        source = ROOT / "harness" / "x87_math_helpers.c"
        self.assertTrue(source.exists(), "missing x87 helper implementations")
        fixture = r'''
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "ghidra_shim.h"
'''
        main = r'''
int main(void)
{
    union { double d; unsigned long long u; } bits;
    if (ABS(-3.5) != 3.5 || ABS(0.0) != 0.0) return 1;
    if (ROUND(2.5) != 2.0 || ROUND(3.5) != 4.0 || ROUND(-1.5) != -2.0) return 2;
    if (SQRT(9.0) != 3.0 || SQRT(0.0) != 0.0) return 3;
    if (fabs(f2xm1(0.5) - (sqrt(2.0) - 1.0)) > 1e-14) return 4;
    if (f2xm1(-1.0) != -0.5 || f2xm1(1.0) != 1.0) return 5;
    if (fscale(1.5, 2.0) != 6.0 || fscale(1.5, -2.0) != 0.375) return 6;
    bits.u = 0x3ff0000000000001ULL;
    if (SUB104(bits.d, 0) != 1u || SUB104(bits.d, 4) != 0x3ff00000u) return 7;
    if (SUB104(bits.d, 5) != 0u) return 8;
    return 0;
}
'''
        body = source.read_text(encoding="utf-8")
        self.assertEqual(build_and_run(fixture + body + main,
                                       "x87_math_recovery_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
