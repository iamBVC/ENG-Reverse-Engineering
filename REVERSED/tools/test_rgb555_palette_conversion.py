"""Verify the recovered RGB555-to-ARGB conversion used by texture uploads."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned int undefined4;
#include "../src_recovered/sub_4083A0.c"
#define REQUIRE_PIXEL(index, expected) do { unsigned int actual = output[index]; if (actual != (expected)) { fprintf(stderr, "pixel %d: expected %08x, got %08x\n", index, (unsigned int)(expected), actual); exit(1); } } while (0)
int main(void)
{
    unsigned short source[32];
    unsigned int output[32] = {0};
    unsigned int component;
    unsigned int scaled;

    for (component = 0; component < 32; ++component) source[component] = (unsigned short)component;
    sub_4083A0(output, source, 0, 32, 0);
    for (component = 0; component < 32; ++component) {
        scaled = component == 31 ? 254 : (component * 255) / 31;
        REQUIRE_PIXEL(component, 0xff000000 | scaled);
    }

    for (component = 0; component < 32; ++component) source[component] = (unsigned short)(component << 5);
    sub_4083A0(output, source, 0, 32, 0);
    for (component = 0; component < 32; ++component) {
        scaled = component == 31 ? 254 : (component * 255) / 31;
        REQUIRE_PIXEL(component, 0xff000000 | (scaled << 8));
    }

    for (component = 0; component < 32; ++component) source[component] = (unsigned short)(component << 10);
    sub_4083A0(output, source, 0, 32, 0);
    for (component = 0; component < 32; ++component) {
        scaled = component == 31 ? 254 : (component * 255) / 31;
        REQUIRE_PIXEL(component, 0xff000000 | (scaled << 16));
    }

    source[0] = 0x8000;
    sub_4083A0(output, source, 0, 1, 1);
    REQUIRE_PIXEL(0, 0xff000001);
    source[0] = 0x801f;
    sub_4083A0(output, source, 0, 1, 1);
    REQUIRE_PIXEL(0, 0xff0000fe);
    puts("RGB555 palette conversion: all channel levels, truncation, and transparency passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "rgb555_palette_conversion_test", bulk=False))
