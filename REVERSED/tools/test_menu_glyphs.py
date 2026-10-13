"""Check a real menu label through font lookup, glyph geometry and the draw queue."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static unsigned short font[256][4];
static unsigned char textures[64];
static union { unsigned int align; unsigned char bytes[40]; } sprites;
static union { unsigned int align; unsigned char bytes[512]; } arena;
int main(void)
{
    unsigned int *node, color;
    float *v, *uv = (float *)(sprites.bytes+24);
    unsigned int before, after;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    font['A'][0] = 1; font['A'][1] = 20; font['A'][2] = 10; font['A'][3] = 20;
    sprites.bytes[22] = 1;
    uv[0] = uv[2] = 0; uv[1] = uv[3] = 1;
    DAT_006da354 = (UINT_PTR)font; DAT_00581154 = (UINT_PTR)sprites.bytes;
    DAT_0058114c = (void *)textures;
    DAT_0058656c = (UINT_PTR)arena.bytes; DAT_00586570 = sizeof arena.bytes;
    DAT_005f6ef8 = 0; DAT_005833f0 = 1;
    DAT_00583374 = 640; DAT_00583378 = 480;
    DAT_00583390 = 640; DAT_00583394 = 480;
    sub_435CE0();
    __asm mov before, esp
    sub_436840("A",160,0,0,0x112);
    __asm mov after, esp
    REQUIRE(before == after);
    node = (unsigned int *)DAT_005f6ef8;
    REQUIRE(node != NULL && node[0] == 0 && node[2] == 4 && node[5] == (UINT_PTR)(textures+32));
    v = (float *)node[1];
    REQUIRE(fabs(v[0]-462.5f) < 0.001f && fabs(v[1]-300) < 0.001f);
    REQUIRE(fabs(v[8]-475) < 0.001f && fabs(v[9]-300) < 0.001f);
    REQUIRE(fabs(v[16]-475) < 0.001f && fabs(v[17]-320) < 0.001f);
    REQUIRE(fabs(v[24]-462.5f) < 0.001f && fabs(v[25]-320) < 0.001f);
    memcpy(&color,v+4,4); REQUIRE(color == 0xffffffff);
    REQUIRE(v[6] == 0 && v[7] == 0 && v[14] == 1 && v[15] == 0 && v[22] == 1 && v[23] == 1);
    REQUIRE(DAT_00586570 == sizeof arena.bytes-160);
    sub_435D10(-1,0,0,10,20,0xffffffff,1,0,0);
    REQUIRE((unsigned int *)DAT_005f6ef8 == node);
    DAT_005ff718 = 50; DAT_005ff71c = 75; DAT_005ff720 = 25; _DAT_005ff724 = 75;
    sub_435D10(1,0,0,100,100,0xff112233,0,1,0);
    node = (unsigned int *)DAT_005f6ef8; v = (float *)node[1];
    REQUIRE(v[0] == 50 && v[1] == 25 && v[16] == 75 && v[17] == 75);
    REQUIRE(fabs(v[6]-0.4f) < 0.001f && fabs(v[14]-0.6f) < 0.001f);
    REQUIRE(fabs(v[7]-0.25f) < 0.001f && fabs(v[23]-0.75f) < 0.001f);
    REQUIRE((node[7] & 0x2000) == 0 && (((unsigned int *)node[0])[7] & 0x2000) != 0);
    REQUIRE(((unsigned int *)node[0])[1] == node[1]);
    memcpy(&color,v+4,4); REQUIRE(color == 0xff112233);
    sub_435D10(1,1000,1000,10,20,0xffffffff,1,0,0);
    REQUIRE((unsigned int *)DAT_005f6ef8 == node);
    puts("menu glyphs: actual label, pixel coordinates, packed colors, clipping, UVs, optional pass, draw queue and sentinel passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'menu_glyphs_test'))
