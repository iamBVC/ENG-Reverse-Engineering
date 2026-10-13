"""Exercise repeated frame clearing/flipping with COM ABI and descriptor checks."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *draw_methods[40], *surface_methods[40], *viewport_methods[40];
static struct { void **methods; } draw = {draw_methods}, surface = {surface_methods}, viewport = {viewport_methods};
static int clears, flips, depth_clears;
static int WINAPI cooperative(UINT_PTR self)
{ REQUIRE(self == (UINT_PTR)&draw); return 0; }
static int WINAPI clear(UINT_PTR self, UINT_PTR a, UINT_PTR b, UINT_PTR c, UINT_PTR flags, UINT_PTR descriptor)
{
    unsigned int *fx = (unsigned int *)descriptor;
    REQUIRE(self == (UINT_PTR)&surface && !a && !b && !c && flags == 0x1000400);
    REQUIRE(fx[0] == 100 && fx[20] == 0 && fx[24] == 0);
    ++clears; return 0;
}
static int WINAPI depth(UINT_PTR self, UINT_PTR count, UINT_PTR rectangles, UINT_PTR flags,
                       UINT_PTR color, UINT_PTR z, UINT_PTR stencil)
{
    unsigned int *rect = (unsigned int *)rectangles;
    REQUIRE(self == (UINT_PTR)&viewport && count == 1 && flags == 2);
    REQUIRE(rect[0] == 0 && rect[1] == 0 && rect[2] == 640 && rect[3] == 480);
    REQUIRE(color == 0 && z == 0x3f800000 && stencil == 0);
    ++depth_clears; return 0;
}
static int WINAPI flip(UINT_PTR self, UINT_PTR target, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&surface && target == self && flags == 1); ++flips; return 0; }
int main(void)
{
    unsigned int before, after;
    int i;
    draw_methods[25] = cooperative;
    surface_methods[5] = clear;
    surface_methods[11] = flip;
    viewport_methods[20] = depth;
    DAT_00582ccc = (void *)&draw;
    DAT_00582cdc = DAT_00582ce4 = (void *)&surface;
    DAT_00582cd8 = (void *)&viewport;
    DAT_00583374 = 640; DAT_00583378 = 480;
    DAT_005833e0 = DAT_005833e1 = 0;
    G_BYTE(DAT_005833e4, 1) = 1;
    __asm mov before, esp
    for (i = 0; i < 100; ++i) {
        REQUIRE(sub_41DD80());
        sub_439280();
        sub_439490();
    }
    __asm mov after, esp
    REQUIRE(before == after && clears == 100 && flips == 100 && depth_clears == 100);
    puts("frame presentation: 100 clears/flips, full descriptors, depth rectangles and balanced stack passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'frame_present_test'))
