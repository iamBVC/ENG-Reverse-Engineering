"""Exercise recovered input callback funclets against their assembly-derived state changes."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class InputCallbackRecoveryTests(unittest.TestCase):
    def test_three_input_funclets_are_recovered_and_match_their_state_transitions(self):
        names = ("sub_4150E0", "sub_415160", "sub_4152E0")
        paths = [ROOT / "src_recovered" / f"{name}.c" for name in names]
        for path in paths:
            self.assertTrue(path.exists(), f"missing recovered callback body: {path.name}")
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in paths)
        fixture = r'''
#include "ghidra_shim.h"
#include <stdint.h>
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_0058370c, DAT_00583710, DAT_00583714, DAT_00583730;
int DAT_00583734, DAT_00583738, DAT_0058373c;
static int raster_arg, raster_calls, wrap_calls;
void sub_41A440(int value) { raster_arg = value; ++raster_calls; }
void sub_414FE0(void) { ++wrap_calls; }
void sub_414FC0(void) { ++wrap_calls; }
'''
        main = r'''
int main(void)
{
    DAT_0058370c = 300; DAT_00583710 = 10; raster_calls = wrap_calls = 0;
    sub_4150E0();
    REQUIRE(DAT_00583714 == 9 && DAT_00583734 == 1 && DAT_00583738 == 0);
    REQUIRE(DAT_0058373c == (int)0xff000000u && DAT_0058370c == 265);
    REQUIRE(raster_calls == 1 && raster_arg == 60 && wrap_calls == 0);

    DAT_0058370c = 126; DAT_00583710 = 4; DAT_00583730 = 0; raster_calls = 0;
    sub_415160();
    REQUIRE(DAT_0058373c == (int)0x7e000000u && DAT_0058370c == 130);
    REQUIRE(raster_calls == 1 && raster_arg == 127 && DAT_00583730 == 1);

    DAT_0058370c = 0; DAT_00583710 = -1; wrap_calls = 0;
    sub_4152E0();
    REQUIRE(DAT_0058370c == 1 && DAT_00583734 == 1 && DAT_00583738 == 0);
    REQUIRE(DAT_0058373c == 0 && wrap_calls == 1);
    return 0;
}
'''
        self.assertEqual(build_and_run(fixture + bodies + main, "input_callback_recovery_test", bulk=False), 0)

    def test_input_callback_dword_matches_original_memory_width(self):
        overrides = (ROOT / "src_generated" / "type_overrides.csv").read_text(encoding="utf-8")
        self.assertRegex(overrides, r"(?m)^DAT_00583714,int$")


if __name__ == "__main__":
    unittest.main()
