"""Exercise the scene's menu callback and a real projected sprite quad."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[41];
static struct { void **methods; } device = {methods};
static int callbacks, draws;
static void menu(void) { ++callbacks; }
static int WINAPI state(UINT_PTR self, UINT_PTR key, UINT_PTR value)
{ REQUIRE(self == (UINT_PTR)&device); return 0; }
static int WINAPI stage(UINT_PTR self, UINT_PTR unit, UINT_PTR key, UINT_PTR value)
{ REQUIRE(self == (UINT_PTR)&device); return 0; }
static int WINAPI draw(UINT_PTR self, UINT_PTR mode, UINT_PTR format, UINT_PTR data, UINT_PTR count, UINT_PTR flags)
{
    float *v = (float *)data;
    unsigned int color;
    REQUIRE(self == (UINT_PTR)&device && mode == 6 && format == 0x1c4 && count == 4 && flags == 0x1c);
    REQUIRE(fabs(v[0]-304) < 0.001f && fabs(v[1]-224) < 0.001f);
    REQUIRE(fabs(v[8]-336) < 0.001f && fabs(v[9]-224) < 0.001f);
    REQUIRE(fabs(v[16]-336) < 0.001f && fabs(v[17]-256) < 0.001f);
    REQUIRE(fabs(v[24]-304) < 0.001f && fabs(v[25]-256) < 0.001f);
    memcpy(&color, v+4, 4); REQUIRE((color & 0xffffff) == 0x204080);
    REQUIRE(v[3] == 0.5f && v[11] == 0.5f && v[19] == 0.5f && v[27] == 0.5f);
    ++draws; return 0;
}
int main(void)
{
    unsigned int sprite[18] = {0};
    float *camera = (float *)DAT_0057dc28_storage;
    float model_matrix[16] = {0};
    unsigned int before, after;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    sub_41ECE0(3.0f,4.0f,5.0f,0.0f,2.0f,2.0f,2.0f,model_matrix);
    REQUIRE(model_matrix[0] == 2.0f && model_matrix[5] == 2.0f && model_matrix[10] == 2.0f && model_matrix[15] == 1.0f);
    REQUIRE(model_matrix[12] == 3.0f && model_matrix[13] == 4.0f && model_matrix[14] == 5.0f);
    methods[0x58/4] = state; methods[0xa0/4] = stage; methods[0x70/4] = draw;
    DAT_00582cd4 = (int *)&device; DAT_005833e1 = 0;
    DAT_005833e4 = 0x01000000;
    DAT_00583374 = 640; DAT_00583378 = 480;
    _DAT_00583388 = 320; _DAT_0058338c = 240;
    _DAT_0057d70c = 1; _DAT_0057d7fc = 100; _DAT_0057f914 = 1;
    for (i = 0; i < 16; ++i) camera[i] = i % 5 == 0 ? 1.0f : 0.0f;
    sprite[4] = -8192; sprite[13] = 4; sprite[14] = 0x402010; sprite[15] = 32 << 12;
    DAT_006d9be4 = 1; DAT_005ff038 = menu;
    DAT_006d9bdc = sprite;
    __asm mov before, esp
    sub_42C8C0();
    __asm mov after, esp
    fprintf(stderr, "callbacks=%d draws=%d stack=%08x/%08x near=%g far=%g\n", callbacks, draws, before, after, (double)_DAT_0057d70c, (double)_DAT_0057d7fc);
    REQUIRE(callbacks == 1 && draws == 1 && before == after);
    puts("sprite scene: menu callback, projected quad, packed color, contiguous vertices and native stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'sprite_scene_test'))
