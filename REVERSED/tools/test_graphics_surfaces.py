"""Check generated surface setup with mock COM methods, without changing display mode."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *draw_methods[22], *surface_methods[32];
static void *gamma_methods[4];
static struct { void **methods; } gamma;
static struct { void **methods; } draw;
static struct surface { void **methods; int kind; } surfaces[4], back;
static int created, attached, modes, flip, depth;
static int gamma_failure, gamma_calls;

static int WINAPI query_gamma(UINT_PTR self, UINT_PTR iid, UINT_PTR output)
{
    REQUIRE(self == (UINT_PTR)&surfaces[0] && iid != 0);
    gamma.methods = gamma_methods; *(void **)output = &gamma; return 0;
}
static int WINAPI gamma_ramp(UINT_PTR self, UINT_PTR flags, UINT_PTR output)
{
    unsigned short *ramp = (unsigned short *)output;
    int i;
    REQUIRE(self == (UINT_PTR)&gamma && flags == 0 && output == (UINT_PTR)DAT_00582cf0);
    REQUIRE(sizeof DAT_00582cf0 == 1536);
    ++gamma_calls;
    for (i = 0; i < 768; ++i) ramp[i] = (unsigned short)(i * 13);
    return gamma_failure;
}

static int WINAPI cooperative(UINT_PTR self, UINT_PTR window, UINT_PTR flags)
{
    REQUIRE(self == (UINT_PTR)&draw && flags == 0x11); return 0;
}
static int WINAPI display_mode(UINT_PTR self, UINT_PTR width, UINT_PTR height, UINT_PTR bits, UINT_PTR refresh, UINT_PTR flags)
{
    REQUIRE(self == (UINT_PTR)&draw && width == 640 && height == 480 && bits == 16);
    REQUIRE(refresh == 60 && flags == 0); ++modes; return 0;
}
static int WINAPI create_surface(UINT_PTR self, UINT_PTR description, UINT_PTR result, UINT_PTR outer)
{
    unsigned int *desc = (unsigned int *)description;
    REQUIRE(self == (UINT_PTR)&draw && outer == 0 && created < 4);
    REQUIRE(desc[0] == 124);
    if (created == 0) REQUIRE(desc[1] == 0x21 && desc[5] == 1 && desc[26] == 0x2218);
    else {
        REQUIRE(desc[1] == 0x1007 && desc[2] == 480 && desc[3] == 640);
        REQUIRE(desc[18] == 32 && desc[21] == 16);
        if (flip && created == 1) REQUIRE(desc[26] == 0x2800);
        else REQUIRE(depth && desc[26] == (flip ? 0x22800 : 0x22000));
    }
    surfaces[created].methods = surface_methods; surfaces[created].kind = created;
    *(void **)result = &surfaces[created++]; return 0;
}
static int WINAPI caps(UINT_PTR self, UINT_PTR a, UINT_PTR b, UINT_PTR c, UINT_PTR flags, UINT_PTR output)
{
    unsigned int *out = (unsigned int *)output;
    REQUIRE(out[0] == 100 && flags == 0x400 && a == 0 && b == 0 && c == 0);
    /* Write the entire output, including the last dword: separate locals cannot satisfy this. */
    memset(out, 0, 100); out[0] = 100; out[24] = 0x1234; return 0;
}
static int WINAPI get_back(UINT_PTR self, UINT_PTR capabilities, UINT_PTR output)
{
    REQUIRE(self == (UINT_PTR)&surfaces[0] && *(unsigned int *)capabilities == 4);
    back.methods = surface_methods; back.kind = 4; *(void **)output = &back; return 0;
}
static int WINAPI attach(UINT_PTR self, UINT_PTR z)
{
    REQUIRE(self == (UINT_PTR)(flip ? &surfaces[1] : &back));
    REQUIRE(z == (UINT_PTR)&surfaces[created - 1]); ++attached; return 0;
}
static int WINAPI pixel_format(UINT_PTR self, UINT_PTR output)
{
    unsigned int format[8] = {32, 0x40, 0, 16, 0xf800, 0x7e0, 0x1f, 0};
    memcpy((void *)output, format, sizeof format); return 0;
}
static void run_case(int use_flip, int use_depth, int use_gamma, int fail_gamma)
{
    unsigned int format[15] = {0}, mode[36] = {0}, adapter[10] = {0};
    unsigned char device[216] = {0};
    int i;
    flip = use_flip; depth = use_depth; created = attached = modes = 0;
    gamma_calls = 0; gamma_failure = fail_gamma;
    format[3] = 16; format[4] = 32; format[5] = 0x400; format[7] = 16;
    mode[3] = 640; mode[4] = 480;
    mode[23] = 32; mode[24] = 0x40; mode[26] = 16;
    mode[27] = 0xf800; mode[28] = 0x7e0; mode[29] = 0x1f;
    device[0x10] = (unsigned char)flip; device[0x15] = (unsigned char)depth;
    *((unsigned char *)adapter + 0x16) = (unsigned char)use_gamma;
    DAT_00582ccc = (unsigned int *)&draw;
    REQUIRE(sub_410700((int)format, (int)mode, (int)adapter, (int)device) == 1);
    REQUIRE(modes == 1 && created == 1 + flip + depth && attached == depth);
    for (i = 0; i < created; ++i) REQUIRE(surfaces[i].methods == surface_methods);
    REQUIRE(gamma_calls == use_gamma);
    if (use_gamma) {
        unsigned short *ramp = (unsigned short *)DAT_00582cf0;
        for (i = 0; i < 768; ++i)
            REQUIRE(ramp[i] == (unsigned short)(fail_gamma ? (i % 256) * 257 : i * 13));
    }
}
int main(void)
{
    REQUIRE(__strcmpi("HAL", "hal") == 0);
    REQUIRE(__strcmpi("HAL", "RGB") != 0);
    draw.methods = draw_methods;
    draw_methods[20] = cooperative; draw_methods[21] = display_mode; draw_methods[6] = create_surface;
    surface_methods[5] = caps; surface_methods[12] = get_back;
    surface_methods[3] = attach; surface_methods[21] = pixel_format;
    surface_methods[0] = query_gamma; gamma_methods[3] = gamma_ramp;
    run_case(0, 0, 0, 0); run_case(0, 1, 0, 0);
    run_case(1, 0, 0, 0); run_case(1, 1, 0, 0);
    run_case(1, 1, 1, 0); run_case(1, 1, 1, 1);
    puts("surface setup: descriptors, output bounds and all three gamma channels passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "surface_test"))
