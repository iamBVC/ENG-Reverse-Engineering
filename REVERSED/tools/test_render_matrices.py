"""Exercise real model/view calculations using the restored global matrices."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    unsigned int model[35] = {0};
    float transform[6] = {0,0,0,3,4,5};
    float *view = (float *)DAT_0057db20_storage;
    float *matrix = (float *)DAT_006d7b68_storage;
    float *combined = (float *)DAT_006d7be8_storage;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    for (i = 0; i < 16; ++i) view[i] = i % 5 == 0 ? 1.0f : 0.0f;
    DAT_006d7c34 = 123;
    REQUIRE(sub_401820((int)model, (int)transform) == 1);
    for (i = 0; i < 16; ++i) {
        float expected = i == 12 ? 3 : i == 13 ? 4 : i == 14 ? 5 : i == 15 ? 1 : i % 5 == 0 ? 2 : 0;
        REQUIRE(fabs(matrix[i] - expected) < 0.00001);
        REQUIRE(fabs(combined[i] - expected) < 0.00001);
    }
    REQUIRE(DAT_006d7c34 == 123);
    REQUIRE(sizeof DAT_006d7b68_storage == 64 && sizeof DAT_006d7be8_storage == 64);
    REQUIRE(sizeof DAT_006d84b0_storage == 640);
    puts("render matrices: real model/view composition, scale, translation, complete storage and adjacent state passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'render_matrices_test'))
