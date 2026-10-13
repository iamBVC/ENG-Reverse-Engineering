"""Check camera calling conventions, tangent and contiguous float matrices."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    float camera[40] = {0};
    float *matrix;
    int i;
    camera[6] = 1.0f;
    camera[7] = 100.0f;
    /* Original coefficient is 5/11: this input gives tan(pi/4). */
    camera[8] = 1.72787595947f;
    DAT_00583384 = 4.0f / 3.0f;
    sub_402910((int)camera, 1.0f, 1.0f);
    REQUIRE(fabs(DAT_0057dc68 - 1.0f) < 0.00001f);
    REQUIRE(fabs(DAT_0057dbe4 - 0.75f) < 0.00001f);
    sub_402960(camera);
    REQUIRE(fabs(_DAT_0057d70c - 1.0f) < 0.00001f);
    REQUIRE(fabs(_DAT_0057d7fc - 100.0f) < 0.00001f);
    matrix = (float *)DAT_0057dbe8_storage;
    for (i = 0; i < 16; ++i)
        REQUIRE(fabs(matrix[i] - (i % 5 == 0 ? 1.0f : 0.0f)) < 0.00001f);
    matrix = (float *)DAT_0057db60_storage;
    REQUIRE(fabs(matrix[0] - 1.0f) < 0.00001f);
    REQUIRE(fabs(matrix[5] - 0.75f) < 0.00001f);
    REQUIRE(fabs(matrix[10] + 101.0f / 99.0f) < 0.00001f);
    REQUIRE(fabs(matrix[14] - 200.0f / 99.0f) < 0.00001f);
    /* Menu startup must write the camera's FOV at byte offset 0x20. */
    for (i = 11; i < 40; ++i) camera[i] = 1234.0f;
    DAT_00581168 = (unsigned int *)camera;
    sub_41A440(320);
    REQUIRE(fabs(camera[8] - 2.0 * atan2(DAT_0056e280 / 320.0, 1.0)) < 0.00001);
    REQUIRE(DAT_0057dc68 > 0.0f && DAT_0057dc68 < 10000.0f);
    for (i = 11; i < 40; ++i) REQUIRE(camera[i] == 1234.0f);
    REQUIRE(CARRY4(0xffffffffU, 1U) && !CARRY4(123U, 456U));
    puts("camera matrices: original angle scale, menu FOV, guarded camera layout, carry and near/far fields passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'camera_matrices_test'))
