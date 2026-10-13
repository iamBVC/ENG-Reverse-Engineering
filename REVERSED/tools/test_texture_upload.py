"""Verify a real indexed texture upload with mocked native COM boundaries."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *draw_methods[40], *surface_methods[40], *device_methods[40], *d3d_methods[40];
static struct { void **methods; } draw = {draw_methods}, surface = {surface_methods},
    device = {device_methods}, d3d = {d3d_methods};
static unsigned int format[8] = {32, 0x20, 0, 8, 0, 0, 0, 0};
static unsigned char pixels[8], source[4] = {1, 2, 3, 4};
static unsigned int texture[8];
static int created, locked, unlocked, selected, evicted;
static int WINAPI evict(UINT_PTR self) { REQUIRE(self == (UINT_PTR)&d3d); ++evicted; return 0; }
static int WINAPI create_surface(UINT_PTR self, UINT_PTR descriptor, UINT_PTR output, UINT_PTR outer)
{
    unsigned int *desc = (unsigned int *)descriptor;
    REQUIRE(self == (UINT_PTR)&draw && outer == 0);
    REQUIRE(desc[0] == 124 && desc[1] == 0x1007 && desc[2] == 2 && desc[3] == 2);
    REQUIRE(!memcmp(desc + 18, format, sizeof format));
    REQUIRE(desc[26] == 0x1000 && desc[27] == 16 && desc[28] == 0 && desc[29] == 0);
    *(UINT_PTR *)output = (UINT_PTR)&surface;
    ++created; return 0;
}
static int WINAPI query(UINT_PTR self, UINT_PTR iid, UINT_PTR output)
{ REQUIRE(self == (UINT_PTR)&surface && iid == (UINT_PTR)&DAT_0056e6dc); *(UINT_PTR *)output = self; return 0; }
static int WINAPI color_key(UINT_PTR self, UINT_PTR flags, UINT_PTR key)
{ REQUIRE(self == (UINT_PTR)&surface && flags == 8 && ((unsigned int *)key)[0] == 0 && ((unsigned int *)key)[1] == 0); return 0; }
static int WINAPI lock(UINT_PTR self, UINT_PTR rectangle, UINT_PTR descriptor, UINT_PTR flags, UINT_PTR event)
{
    unsigned int *desc = (unsigned int *)descriptor;
    REQUIRE(self == (UINT_PTR)&surface && !rectangle && !event && flags == 0x821);
    desc[4] = 4; desc[9] = (UINT_PTR)pixels;
    ++locked; return 0;
}
static int WINAPI unlock(UINT_PTR self, UINT_PTR rectangle)
{ REQUIRE(self == (UINT_PTR)&surface && !rectangle); ++unlocked; return 0; }
static int WINAPI select_texture(UINT_PTR self, UINT_PTR stage, UINT_PTR value)
{ REQUIRE(self == (UINT_PTR)&device && stage == 0 && value == (UINT_PTR)&surface); ++selected; return 0; }
int main(void)
{
    unsigned int before, after;
    draw_methods[6] = create_surface;
    surface_methods[0] = query; surface_methods[29] = color_key;
    surface_methods[25] = lock; surface_methods[32] = unlock;
    device_methods[38] = select_texture; d3d_methods[11] = evict;
    DAT_00582ccc = (void *)&draw; DAT_00582cd0 = (void *)&d3d; DAT_00582cd4 = (void *)&device;
    PTR_DAT_00570370 = format;
    DAT_00581148 = 0; DAT_00581150 = 1; DAT_0058114c = texture;
    DAT_00583374 = 640; DAT_00583378 = 480;
    DAT_00583400 = DAT_005833e9 = 1;
    DAT_005833e0 = DAT_005833e1 = 0;
    texture[1] = texture[2] = 2; texture[6] = (UINT_PTR)source;
    memset(pixels, 0xcd, sizeof pixels);
    __asm mov before, esp
    REQUIRE(sub_407240() == 1);
    __asm mov after, esp
    REQUIRE(before == after && created == 1 && locked == 1 && unlocked == 1 && selected == 1 && evicted == 1);
    REQUIRE(pixels[0] == 1 && pixels[1] == 2 && pixels[4] == 3 && pixels[5] == 4);
    REQUIRE(pixels[2] == 0xcd && pixels[3] == 0xcd && pixels[6] == 0xcd && pixels[7] == 0xcd);
    REQUIRE(texture[3] == (UINT_PTR)&surface && texture[4] == (UINT_PTR)&surface && texture[6] == 0);
    puts("texture upload: native calls, 124-byte descriptor, color key, pitched pixels and balanced stack passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'texture_upload_test'))
