"""Check original intro RGB packing and native surface stack handling offline."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[40];
static struct { void **methods; } surface = {methods};
static unsigned char pixels[32];
static int locks, unlocks, depth;
static int WINAPI lock_surface(UINT_PTR self, UINT_PTR rect, UINT_PTR descriptor, UINT_PTR flags, UINT_PTR event)
{
    unsigned int *desc = (unsigned int *)descriptor;
    REQUIRE(self == (UINT_PTR)&surface && !rect && flags == 1 && !event);
    REQUIRE(desc[0] == 124);
    desc[2] = 2; desc[3] = 2; desc[4] = 12;
    desc[9] = (UINT_PTR)pixels; desc[21] = depth;
    desc[22] = depth == 16 ? 0xf800 : 0xff0000;
    desc[23] = depth == 16 ? 0x07e0 : 0x00ff00;
    desc[24] = depth == 16 ? 0x001f : 0x0000ff;
    desc[25] = depth == 32 ? 0xff000000 : 0;
    ++locks; return 0;
}
static int WINAPI unlock_surface(UINT_PTR self, UINT_PTR rect)
{ REQUIRE(self == (UINT_PTR)&surface && !rect); ++unlocks; return 0; }
'''
MAIN = r'''
int main(void)
{
    unsigned int desc[31] = {124}, before, after;
    unsigned char rgb[] = {255,0,0, 0,255,0, 0,0,255, 0,0,0};
    unsigned char rgba[] = {255,0,0,128, 0,255,0,64, 0,0,255,255, 0,0,0,0};
    int channels;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    methods[25] = lock_surface; methods[32] = unlock_surface;
    for (depth = 16; depth <= 32; depth += 16) {
        for (channels = 3; channels <= 4; ++channels) {
            memset(pixels, 0xa5, sizeof pixels);
            __asm mov before, esp
            sub_43B080((int *)&surface, (int)desc, channels == 3 ? rgb : rgba, 1, channels);
            __asm mov after, esp
            REQUIRE(before == after);
            if (depth == 32) {
                REQUIRE(*(unsigned int *)pixels == (channels == 4 ? 0x80ff0000 : 0x00ff0000));
                REQUIRE(*(unsigned int *)(pixels+4) == (channels == 4 ? 0x4000ff00 : 0x0000ff00));
                REQUIRE(*(unsigned int *)(pixels+12) == (channels == 4 ? 0xff0000ff : 0x000000ff));
                REQUIRE(*(unsigned int *)(pixels+16) == 1);
                REQUIRE(pixels[8] == 0xa5 && pixels[20] == 0xa5);
            } else {
                REQUIRE(*(unsigned short *)pixels == 0xf800);
                REQUIRE(*(unsigned short *)(pixels+2) == 0x07e0);
                REQUIRE(*(unsigned short *)(pixels+12) == 0x001f);
                REQUIRE(*(unsigned short *)(pixels+14) == 1);
                REQUIRE(pixels[4] == 0xa5 && pixels[16] == 0xa5);
            }
        }
    }
    REQUIRE(locks == 8 && unlocks == 8);
    puts("intro uploader: RGB/RGBA, RGB565/32-bit, row pitch, black replacement and native stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    path = ROOT / 'src_recovered/sub_43B080.c'
    body = path.read_text() if path.exists() else (ROOT / 'decompiled/sub_43B080.c').read_text().replace(
        'void sub_43B080(int *param_1,int param_2)',
        'void sub_43B080(int *param_1,int param_2,byte *param_3,uint param_4,int param_5)')
    helpers = '\n'.join((ROOT / f'decompiled/sub_{address}.c').read_text()
                        for address in ('43B010', '43B030', '43B060'))
    raise SystemExit(build_and_run(SOURCE + helpers + body + MAIN, 'intro_upload_test', bulk=False))
