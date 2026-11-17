"""Exercise the RGB555 histogram and palette mapping used during texture upload."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

int main(void)
{
    unsigned short pixels[] = {0x0000, 0x7c00, 0x03e0, 0x001f, 0x7fff, 0x4210, 0x03e0};
    unsigned short palette[256] = {0};
    unsigned char indices[sizeof pixels / sizeof pixels[0]] = {0};
    unsigned int i;

    sub_436CC0(0);
    REQUIRE(DAT_0061fb34_storage[0] == 0);
    REQUIRE(DAT_0061fb34_storage[1] == 1);
    REQUIRE(DAT_0061fb34_storage[31] == 31 * 31);
    sub_436D40(pixels, sizeof pixels / sizeof pixels[0]);
    REQUIRE(DAT_006b4544_storage[0x463] == 1);
    REQUIRE(DAT_006b4544_storage[0x463 + 31] == 1);
    REQUIRE(sub_436E30(0, 256, palette) == 1);
    REQUIRE(DAT_005ff730 >= 4);

    sub_437AC0(0, pixels, (char *)indices, sizeof pixels / sizeof pixels[0]);
    for (i = 0; i < sizeof pixels / sizeof pixels[0]; ++i)
        REQUIRE(indices[i] < DAT_005ff730);
    REQUIRE(indices[1] != indices[2]);
    REQUIRE(indices[2] != indices[3]);
    REQUIRE(indices[1] != indices[3]);
    puts("palette histogram: square lookup, RGB555 buckets, palette build and texel remap passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "palette_histogram_layout_test", bulk=True))
