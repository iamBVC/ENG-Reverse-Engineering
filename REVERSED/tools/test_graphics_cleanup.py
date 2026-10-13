"""Exercise generated COM cleanup, descriptor bounds and x86 stack balance."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[40];
static struct { void **vtable; } object = {methods};
static int releases, blits, gamma_calls, restored, cooperative_calls, removed;
static int WINAPI release(UINT_PTR self) { REQUIRE(self == (UINT_PTR)&object); ++releases; return 1; }
static int WINAPI gamma(UINT_PTR self, UINT_PTR flags, UINT_PTR ramp)
{ REQUIRE(self == (UINT_PTR)&object && flags == 0 && ramp == (UINT_PTR)DAT_00582cf0); ++gamma_calls; return 0; }
static int WINAPI blit(UINT_PTR self, UINT_PTR a, UINT_PTR b, UINT_PTR c, UINT_PTR flags, UINT_PTR descriptor)
{
    unsigned int *fx = (unsigned int *)descriptor;
    REQUIRE(self == (UINT_PTR)&object && a == 0 && b == 0 && c == 0 && flags == 0x400);
    REQUIRE(fx[0] == 100 && fx[20] == 0 && fx[24] == 0); ++blits; return 0;
}
static int WINAPI remove_viewport(UINT_PTR self, UINT_PTR viewport)
{ REQUIRE(self == (UINT_PTR)&object && viewport == self); ++removed; return 0; }
static int WINAPI restore(UINT_PTR self) { ++restored; return 0; }
static int WINAPI cooperative(UINT_PTR self, UINT_PTR window, UINT_PTR flags)
{ REQUIRE(flags == 8); ++cooperative_calls; return 0; }
int sub_5628BC(void *memory) { REQUIRE(0); return 0; }
'''
MAIN = r'''
int main(void)
{
    unsigned int before, after;
    int i;
    methods[2] = release; methods[4] = gamma; methods[5] = blit;
    methods[6] = remove_viewport; methods[19] = restore; methods[20] = cooperative;
    for (i = 0; i < 100; ++i) {
        DAT_00582cd4 = DAT_00582cd8 = (int *)&object;
        __asm mov before, esp
        sub_4114A0();
        __asm mov after, esp
        REQUIRE(before == after && DAT_00582cd4 == NULL && DAT_00582cd8 == NULL);
        DAT_00582cec = DAT_00582ce8 = DAT_00582ce4 = DAT_00582ce0 = DAT_00582cdc = DAT_005832f4 = DAT_00582ccc = (int *)&object;
        __asm mov before, esp
        sub_410ED0();
        __asm mov after, esp
        REQUIRE(before == after && DAT_00582cec == NULL && DAT_00582cdc == NULL && DAT_00582ce4 == NULL);
    }
    REQUIRE(releases == 800 && blits == 300 && gamma_calls == 100 && removed == 100);
    REQUIRE(restored == 100 && cooperative_calls == 100);
    puts("graphics cleanup: 100 COM teardown cycles, 100-byte descriptors and stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_4114A0', 'sub_410ED0']]
    symbols = set(re.findall(r'\bDAT_[A-Za-z0-9_]+\b', '\n'.join(bodies)))
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if any(re.search(r'\b' + s + r'\b', line) for s in symbols)]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(selected) + '\n'.join(bodies) + MAIN,
                                  'graphics_cleanup_test', bulk=False))
