"""Check the original homogeneous polygon clipper without a graphics device."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    float input[24] = {0,-0.5f,0,1,0,0,0,0.2f, 0,0.5f,0,1,0,0,0,0.8f, 0.5f,0,0,1,0,0,1,1};
    float guarded[42] = {0}, *out = guarded+1;
    unsigned int color = 0xff123456, actual, before, after;
    int plane, i, count;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    for (i = 0; i < 3; ++i) memcpy(input+i*8+4, &color, 4);
    guarded[0] = guarded[41] = 1234.0f;
    __asm mov before, esp
    for (plane = 0; plane < 6; ++plane) {
        REQUIRE(sub_439BC0(plane, (int)input, 3, out) == 3);
        REQUIRE(!memcmp(input, out, sizeof input));
    }
    input[16] = 2.0f; color = 0xffffffff; memcpy(input+20, &color, 4);
    color = 0; memcpy(input+4, &color, 4); memcpy(input+12, &color, 4);
    count = sub_439BC0(1, (int)input, 3, out);
    REQUIRE(count == 4);
    REQUIRE(fabs(out[0]-1.0f) < 0.00001 && fabs(out[1]+0.25f) < 0.00001);
    REQUIRE(fabs(out[6]-0.5f) < 0.00001 && fabs(out[7]-0.6f) < 0.00001);
    memcpy(&actual, out+4, 4); REQUIRE(actual == 0x7f7f7f7f);
    REQUIRE(out[8] == 0 && out[16] == 0 && out[24] == 1);
    for (i = 0; i < 3; ++i) input[i*8] = 2;
    REQUIRE(sub_439BC0(1, (int)input, 3, out) == 0);
    for (i = 0; i < 3; ++i) input[i*8] = 1;
    REQUIRE(sub_439BC0(1, (int)input, 3, out) == 3);
    REQUIRE(sub_439BC0(1, 0, 0, out) == 0);
    __asm mov after, esp
    REQUIRE(before == after && guarded[0] == 1234.0f && guarded[41] == 1234.0f);
    puts("polygon clipping: six planes, inside/outside/boundary cases, intersections, UVs, packed colours and bounds passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'polygon_clip_test'))
