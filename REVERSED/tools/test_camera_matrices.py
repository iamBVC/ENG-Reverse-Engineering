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
    float camera[11] = {0};
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
    puts("camera matrices: original angle scale, identity view and near/far fields passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'camera_matrices_test'))
