"""Verify real queued drawing against native COM argument and stack boundaries."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[41];
static struct { void **methods; } device = {methods};
static float vertices[24];
static unsigned short indices[3] = {0,1,2};
static int indexed, plain;
static int WINAPI state(UINT_PTR self, UINT_PTR key, UINT_PTR value)
{ REQUIRE(self == (UINT_PTR)&device); return 0; }
static int WINAPI stage(UINT_PTR self, UINT_PTR unit, UINT_PTR key, UINT_PTR value)
{ REQUIRE(self == (UINT_PTR)&device); return 0; }
static int WINAPI draw(UINT_PTR self, UINT_PTR mode, UINT_PTR format, UINT_PTR data, UINT_PTR count, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&device && mode == 4 && format == 0x1c4 && data == (UINT_PTR)vertices && count == 3 && flags == 0x1c); ++plain; return 0; }
static int WINAPI draw_indexed(UINT_PTR self, UINT_PTR mode, UINT_PTR format, UINT_PTR data, UINT_PTR count, UINT_PTR list, UINT_PTR length, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&device && mode == 4 && format == 0x1c4 && data == (UINT_PTR)vertices && count == 3 && list == (UINT_PTR)indices && length == 3 && flags == 0x1c); ++indexed; return 0; }
int main(void)
{
    unsigned int node[8] = {0};
    unsigned int before, after;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    methods[0x58/4] = state; methods[0xa0/4] = stage;
    methods[0x70/4] = draw; methods[0x74/4] = draw_indexed;
    DAT_00582cd4 = (int *)&device; DAT_005833e1 = 0;
    node[1] = (UINT_PTR)vertices; node[2] = 3; node[4] = 3;
    __asm mov before, esp
    for (i = 0; i < 100; ++i) {
        node[3] = i % 2 ? (UINT_PTR)indices : 0;
        (&DAT_005f6ef8)[0] = (UINT_PTR)node;
        sub_424BE0();
        REQUIRE((&DAT_005f6ef8)[0] == 0);
    }
    __asm mov after, esp
    REQUIRE(before == after && indexed == 50 && plain == 50);
    puts("scene submission: indexed and plain drawing arguments, flags, queue clearing and native stack balance passed for 100 cycles");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'scene_submission_test'))
