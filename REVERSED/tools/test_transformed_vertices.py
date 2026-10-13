"""Check the renderer's real vertex writer and clip-mask reader together."""
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
    float transform[6] = {0};
    float vertices[12] = {0.25f,-0.125f,0,0,0,0, 2,0,0,0,0,0};
    float *view = (float *)DAT_0057db20_storage;
    unsigned int word;
    float value;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    for (i = 0; i < 16; ++i) view[i] = i % 5 == 0 ? 1.0f : 0.0f;
    model[27] = 2; model[28] = (UINT_PTR)vertices;
    REQUIRE(sub_401820((int)model, (int)transform) == 1);
    word = (&DAT_0058b0f0)[0]; memcpy(&value, &word, 4); REQUIRE(value == 0.5f);
    word = (&DAT_0058b0f4)[0]; memcpy(&value, &word, 4); REQUIRE(value == -0.25f);
    word = (&DAT_0058b0fc)[0]; memcpy(&value, &word, 4); REQUIRE(value == 1.0f);
    REQUIRE((&DAT_0058b110)[0] == 0);
    word = (&DAT_0058b0f0)[9]; memcpy(&value, &word, 4); REQUIRE(value == 4.0f);
    REQUIRE((&DAT_0058b110)[9] == 2);
    puts("transformed vertices: shared 36-byte records, homogeneous coordinates and integer clipping masks passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'transformed_vertices_test'))
