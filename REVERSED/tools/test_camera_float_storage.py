"""Regression test for float stores through the camera-vector pointer."""
from pathlib import Path
import re

from test_hardware_enumeration import main as build_and_run

ROOT = Path(__file__).resolve().parent.parent
generated = (ROOT / "src_generated" / "clean_subset.c").read_text(encoding="utf-8")
match = re.search(r"\b(?:void|int)\s+sub_41A920\s*\(", generated)
if match is None:
    raise RuntimeError("sub_41A920 was not found in generated C")
start = match.start()
opening = generated.find("{", start)
depth = 0
end = -1
for offset in range(opening, len(generated)):
    if generated[offset] == "{":
        depth += 1
    elif generated[offset] == "}":
        depth -= 1
        if depth == 0:
            end = offset + 1
            break
if end < 0:
    raise RuntimeError("sub_41A920 body is unbalanced")
function_source = generated[start:end]

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>

#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
unsigned int *DAT_00581168;
float _DAT_0056e020 = 0.5f;
float _DAT_0056e018 = 1.0f;
float _DAT_0056e180;
float DAT_0057f90c;
int DAT_005846e4;
uint _DAT_005848b8;
int _DAT_005848bc, _DAT_005848c0, _DAT_005848c4;
float DAT_006d8400, DAT_006d8404, DAT_006d8408;
#define _DAT_006d8400 DAT_006d8400
#define _DAT_006d8404 DAT_006d8404
#define _DAT_006d8408 DAT_006d8408
int DAT_006d9e28;

int __ftol(void) { return 0; }
double fpatan(double numerator, double denominator) { return 0.0; }
void sub_402960(float *values)
{
    REQUIRE(values[3] == 2.5f);
    REQUIRE(values[4] == 3.5f);
    REQUIRE(values[5] == -4.5f);
}

'''+function_source+r'''

int main(void)
{
    unsigned int camera_storage[8] = {0};
    int camera[8] = {0};
    int target[7] = {0};
    DAT_00581168 = camera_storage;
    camera[1] = 4;
    camera[4] = 5;
    camera[5] = 7;
    camera[6] = 9;
    sub_41A920(camera, (int)target, 0);
    REQUIRE(DAT_006d8400 == 2.5f);
    REQUIRE(DAT_006d8404 == 3.5f);
    REQUIRE(DAT_006d8408 == -4.5f);
    puts("camera float storage: three transformed float components preserved bit-exactly");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "camera_float_storage_test", bulk=False))
