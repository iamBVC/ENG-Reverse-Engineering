"""Load the shipped menu's LGHT chunk through the reconstructed C loader."""
from test_hardware_enumeration import ROOT, main as build_and_run

wad_path = str(ROOT.parent / "Game/wads/t0i0m000.wad").replace("\\", "\\\\")
SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    FILE *stream;
    unsigned int tag, size, i;
    unsigned int *world, *lights, *node;
    float *light;
    float norm;
    DAT_00586580 = (int)malloc(0x1000000);
    REQUIRE(DAT_00586580 != 0);
    sub_41EEE0();
    DAT_0058115c = calloc(1, 0x28);
    world = (unsigned int *)sub_42AA60();
    REQUIRE(world != NULL && world[0x17] == 0 && world[0x18] == 0);
    DAT_006d7c61 = 1;
''' + f'    stream = fopen("{wad_path}", "rb");\n' + r'''
    REQUIRE(stream != NULL);
    REQUIRE(sub_5629E6(&size, 4, 1, stream) == 1);
    for (;;) {
        REQUIRE(sub_5629E6(&tag, 4, 1, stream) == 1);
        REQUIRE(sub_5629E6(&size, 4, 1, stream) == 1);
        if (tag == 0x4c474854) break;
        REQUIRE(sub_56294C(stream, size, SEEK_CUR) == 0);
    }
    REQUIRE(size == 52 && sub_5639C2(stream) == 735930);
    sub_42C180((unsigned int)world, stream);
    REQUIRE(sub_5639C2(stream) == 735982);
    REQUIRE(world[0x17] == 3 && DAT_0058115c[9] == 3);
    lights = (unsigned int *)world[0x18];
    node = (unsigned int *)DAT_0058115c[8];
    for (i = 0; i < 3; ++i) {
        light = (float *)lights[i];
        REQUIRE(light != NULL && ((unsigned int *)light)[0x1a] == 1);
        norm = light[11]*light[11] + light[12]*light[12] + light[13]*light[13];
        REQUIRE(fabs(norm - 1.0f) < 0.001f);
        REQUIRE(node && node[0] == lights[2-i]);
        node = (unsigned int *)node[1];
    }
    REQUIRE(node == NULL);
    REQUIRE(fabs(((float *)lights[0])[4] - 2.0f) < 0.0001f);
    fclose(stream);
    puts("light loading: original WAD read/seek, three lights, normalization and list registration passed");
    return 0;
}
'''
if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "light_loading_test"))
