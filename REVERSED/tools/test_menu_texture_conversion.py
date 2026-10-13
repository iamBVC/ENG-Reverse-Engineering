"""Check the actual format callback used by menu texture uploads."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    unsigned int format[8] = {32, 0x40, 0, 32, 0xff0000, 0xff00, 0xff, 0xff000000};
    unsigned short image[9] = {0,0,0,0,0x001f,0x03e0,0,0x7c00,0};
    unsigned char output[64];
    code *convert;
    unsigned int before, after;
    int depth, bytes, pitch, offset;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    sub_438CD0(0);
    convert = *(code **)((unsigned char *)PTR_DAT_00570370_storage + 4);
    DAT_006d7c6e = 1;
    __asm mov before, esp
    for (depth = 8; depth <= 32; depth *= 2) {
        bytes = depth / 8; pitch = bytes * 4; offset = pitch + bytes;
        format[3] = depth;
        format[4] = depth == 8 ? 0xe0 : depth == 16 ? 0xf800 : 0xff0000;
        format[5] = depth == 8 ? 0x1c : depth == 16 ? 0x07e0 : 0xff00;
        format[6] = depth == 8 ? 0x03 : depth == 16 ? 0x001f : 0xff;
        format[7] = depth == 32 ? 0xff000000 : 0;
        memset(output, 0xcd, sizeof output);
        REQUIRE((*convert)((UINT_PTR)output, pitch, (UINT_PTR)image, 3, 1, 1, 2, 2, 0, 0, (UINT_PTR)format) == 1);
        if (depth == 32) {
            REQUIRE(*(unsigned int *)(output+offset) == 0xffff0000);
            REQUIRE(*(unsigned int *)(output+offset+bytes) == 0xff00ff00);
            REQUIRE(*(unsigned int *)(output+offset+pitch) == 0xff0000ff);
            REQUIRE(*(unsigned int *)(output+offset+pitch+bytes) == 0);
        } else if (depth == 16) {
            REQUIRE(*(unsigned short *)(output+offset) == 0xf800);
            REQUIRE(*(unsigned short *)(output+offset+bytes) == 0x07e0);
            REQUIRE(*(unsigned short *)(output+offset+pitch) == 0x001f);
            REQUIRE(*(unsigned short *)(output+offset+pitch+bytes) == 0);
        } else {
            REQUIRE(output[offset] == 0xe0 && output[offset+bytes] == 0x1c);
            REQUIRE(output[offset+pitch] == 3 && output[offset+pitch+bytes] == 0);
        }
        REQUIRE(output[0] == 0xcd && output[offset-bytes] == 0xcd && output[offset+2*bytes] == 0xcd);
    }
    image[4] = 0x8000;
    REQUIRE((*convert)((UINT_PTR)output, 16, (UINT_PTR)image, 3, 1, 1, 1, 1, 0, 1, (UINT_PTR)format) == 1);
    REQUIRE(*(unsigned int *)(output+20) == 0xff000001);
    image[4] = 0x801f;
    REQUIRE((*convert)((UINT_PTR)output, 16, (UINT_PTR)image, 3, 1, 1, 1, 1, 1, 0, (UINT_PTR)format) == 1);
    REQUIRE(*(unsigned int *)(output+20) == 0x7fff0000);
    format[3] = 24;
    REQUIRE((*convert)((UINT_PTR)output, 16, (UINT_PTR)image, 3, 1, 1, 1, 1, 0, 0, (UINT_PTR)format) == 0);
    __asm mov after, esp
    REQUIRE(before == after);
    puts("menu texture conversion: registered callback, RGB332/RGB565/RGBA32, cropping, row pitch, transparency and alpha passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'menu_texture_conversion_test'))
