"""Verify packed RGB555 texels are expanded using the destination masks."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

int main(void)
{
    unsigned int format[8] = {0};
    unsigned short source[5] = {0x001f, 0x03e0, 0x7c00, 0x7fff, 0};
    unsigned int destination[5] = {0};
    unsigned short destination16[6] = {0};
    unsigned char destination8[8];
    unsigned int i;

    format[3] = 32;
    format[4] = 0x00ff0000;
    format[5] = 0x0000ff00;
    format[6] = 0x000000ff;
    format[7] = 0xff000000;
    DAT_006d7c6e = 0;
    REQUIRE(sub_408470((int)destination, sizeof destination, (int)source,
                       5, 0, 0, 5, 1, 0, 0, (short *)format) == 1);
    REQUIRE(destination[0] == 0xffff0000); /* low RGB555 field maps to red */
    REQUIRE(destination[1] == 0xff00ff00); /* middle field maps to green */
    REQUIRE(destination[2] == 0xff0000ff); /* high field maps to blue */
    REQUIRE(destination[3] == 0xffffffff);
    REQUIRE(destination[4] == 0);

    format[3] = 16;
    format[4] = 0xf800;
    format[5] = 0x07e0;
    format[6] = 0x001f;
    format[7] = 0;
    destination16[5] = 0xdead;
    REQUIRE(sub_408470((int)destination16, 12, (int)source, 5,
                       0, 0, 5, 1, 0, 0, (short *)format) == 1);
    REQUIRE(destination16[0] == 0xf800);
    REQUIRE(destination16[1] == 0x07e0);
    REQUIRE(destination16[2] == 0x001f);
    REQUIRE(destination16[3] == 0xffff);
    REQUIRE(destination16[4] == 0);
    REQUIRE(destination16[5] == 0xdead); /* destination pitch padding */

    format[3] = 8;
    format[4] = 0xe0;
    format[5] = 0x1c;
    format[6] = 0x03;
    for (i = 0; i < sizeof destination8; ++i)
        destination8[i] = 0xcd;
    REQUIRE(sub_408470((int)destination8, 8, (int)source, 5,
                       0, 0, 5, 1, 0, 0, (short *)format) == 1);
    REQUIRE(destination8[0] == 0xe0);
    REQUIRE(destination8[1] == 0x1c);
    REQUIRE(destination8[2] == 0x03);
    REQUIRE(destination8[3] == 0xff);
    REQUIRE(destination8[4] == 0);
    REQUIRE(destination8[5] == 0xcd); /* destination pitch padding */
    puts("RGB555 surface conversion: channel masks, alpha, pitch and zero transparency passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "rgb555_surface_conversion_test", bulk=True))
