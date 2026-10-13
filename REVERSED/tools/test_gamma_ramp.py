"""Validate restored startup gamma control without physical graphics hardware."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[5];
static struct { void **methods; } control = {methods};
static unsigned short saved[3][256];
static int calls, failure;
static int WINAPI set_gamma(UINT_PTR self, UINT_PTR flags, UINT_PTR ramp)
{
    REQUIRE(self == (UINT_PTR)&control && !flags);
    memcpy(saved, (void *)ramp, sizeof saved); ++calls;
    return failure ? 0x80004005 : 0;
}
int main(void)
{
    unsigned int before, after;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    methods[4] = set_gamma;
    DAT_00582cec = NULL;
    REQUIRE(sub_410480(0.0f, 1.0f, 1.0f) == 0 && !calls);
    DAT_00582cec = (int *)&control;
    __asm mov before, esp
    REQUIRE(sub_410480(0.0f, 1.0f, 1.0f) == 1 && calls == 1);
    REQUIRE(saved[0][0] == 0 && saved[0][128] == 0x8080 && saved[0][255] == 65535);
    REQUIRE(!memcmp(saved[0], saved[1], sizeof saved[0]) && !memcmp(saved[0], saved[2], sizeof saved[0]));
    REQUIRE(sub_410480(0.0f, 1.0f, 2.0f) == 1 && saved[0][128] == 16512);
    REQUIRE(sub_410480(0.25f, 0.5f, 1.0f) == 1 && saved[0][0] == 16383 && saved[0][255] == 49151);
    for (i = 0; i < 100; ++i)
        REQUIRE(sub_410480(-0.5f, 2.0f, 1.0f) == 1 && saved[0][0] == 0 && saved[0][255] == 65535);
    failure = 1;
    REQUIRE(sub_410480(0.0f, 1.0f, 1.0f) == 0);
    __asm mov after, esp
    REQUIRE(before == after);
    puts("gamma ramp: identity, exponent, brightness, clipping, COM failure and stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'gamma_ramp_test'))
