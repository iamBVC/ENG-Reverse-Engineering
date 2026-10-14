"""Check original UI sprite dimensions, packed color and half-pixel placement."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <math.h>
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static union { uint align; byte bytes[64]; } record;
static union { uint align; byte bytes[60]; } sprites;
static uint textures[16], arena[256];
int main(void)
{
    float *uv = (float *)(sprites.bytes+44), *v;
    uint *node, color, before, after;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    record.bytes[0] = 255;
    *(int *)(record.bytes+12) = 1;
    *(int *)(record.bytes+20) = 100; *(int *)(record.bytes+24) = 30;
    sprites.bytes[42] = 1;
    uv[0] = uv[2] = 0.25f; uv[1] = uv[3] = 0.75f;
    textures[9] = 64; textures[10] = 32;
    DAT_0058114c = textures; DAT_00581154 = (UINT_PTR)sprites.bytes;
    DAT_005ff728 = 0;
    DAT_00583374 = 640; DAT_00583378 = 480;
    DAT_0058656c = (UINT_PTR)arena; DAT_00586570 = sizeof arena;
    DAT_005f6ef8 = 0;
    __asm mov before, esp
    sub_425D40(record.bytes,0);
    __asm mov after, esp
    node = (uint *)DAT_005f6ef8;
    REQUIRE(node && node[2] == 4 && node[5] == (UINT_PTR)(textures+8));
    v = (float *)node[1];
    REQUIRE(fabs(v[0]-125.5f) < 0.001f && fabs(v[1]-60.5f) < 0.001f);
    REQUIRE(fabs(v[16]-165.5f) < 0.001f && fabs(v[17]-76.5f) < 0.001f);
    memcpy(&color,v+4,4); REQUIRE(color == 0xffffffff);
    REQUIRE(v[6] == 0.25f && v[14] == 0.75f && v[7] == 0.25f && v[23] == 0.75f);
    REQUIRE(before == after && DAT_00586570 == sizeof arena-160);
    DAT_005f6ef8 = 0; record.bytes[35] = record.bytes[36] = 1;
    sub_425D40(record.bytes,4);
    node = (uint *)DAT_005f6ef8; v = (float *)node[1];
    REQUIRE(fabs(v[16]-205.5f) < 0.001f && fabs(v[17]-92.5f) < 0.001f);
    REQUIRE(v[6] == 0.75f && v[14] == 0.25f && v[7] == 0.75f && v[23] == 0.25f);
    puts("UI sprites: original texture dimensions, integer positions, scale mode, packed color, flipped UVs and stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'ui_sprite_test'))
