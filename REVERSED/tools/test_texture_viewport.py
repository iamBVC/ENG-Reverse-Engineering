"""Drive the generated Direct3D setup through texture and viewport COM mocks."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *d3d_methods[9], *device_methods[13], *viewport_methods[18];
static struct { void **methods; } d3d, device, viewport;
static unsigned int record[54], guid[4] = {1,2,3,4};
static int textures, viewports;
static int WINAPI create_device(UINT_PTR self, UINT_PTR id, UINT_PTR target, UINT_PTR output, UINT_PTR outer)
{
    REQUIRE(id == (UINT_PTR)guid && outer == 0); *(void **)output = &device; return 0;
}
static int WINAPI enum_textures(UINT_PTR self, UINT_PTR callback, UINT_PTR opaque)
{
    unsigned int rgb[8] = {32, 0x40, 0, 16, 0xf800, 0x7e0, 0x1f, 0};
    unsigned int argb[8] = {32, 0x41, 0, 32, 0xff0000, 0xff00, 0xff, 0xff000000};
    unsigned int *context = (unsigned int *)opaque;
    int (WINAPI *visit)(unsigned int *, unsigned int *) = (void *)callback;
    REQUIRE(context[2] == (unsigned int)record);
    REQUIRE(visit(rgb, context) == 1 && visit(argb, context) == 1);
    ++textures; return 0;
}
static int WINAPI create_viewport(UINT_PTR self, UINT_PTR output, UINT_PTR outer)
{
    REQUIRE(outer == 0); *(void **)output = &viewport; return 0;
}
static int WINAPI select_viewport(UINT_PTR self, UINT_PTR selected)
{
    REQUIRE(selected == (UINT_PTR)&viewport); return 0;
}
static int WINAPI set_viewport(UINT_PTR self, UINT_PTR data)
{
    unsigned int *v = (unsigned int *)data;
    REQUIRE(v[0] == 44 && v[1] == 0 && v[2] == 0 && v[3] == 640 && v[4] == 480);
    REQUIRE(v[5] == 0xbf800000 && v[6] == 0xbf800000 && v[7] == 0x40000000 && v[8] == 0x40000000);
    REQUIRE(v[9] == 0 && v[10] == 0x3f800000); ++viewports; return 0;
}
int main(void)
{
    d3d.methods = d3d_methods; device.methods = device_methods; viewport.methods = viewport_methods;
    d3d_methods[8] = create_device; d3d_methods[6] = create_viewport;
    device_methods[8] = enum_textures; device_methods[5] = select_viewport; device_methods[12] = select_viewport;
    viewport_methods[17] = set_viewport;
    DAT_00582cd0 = (unsigned int *)&d3d; DAT_00583374 = 640; DAT_00583378 = 480; DAT_005834d4 = 0;
    record[3] = (unsigned int)guid;
    *((unsigned char *)record + 0x1b) = 1;
    REQUIRE(sub_411000((int)record) == 1 && textures == 1 && viewports == 1);
    REQUIRE(record[30] == 32);
    puts("texture/viewport setup: callback context, format selection and complete viewport descriptor passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "texture_test"))
