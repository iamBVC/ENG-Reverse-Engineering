"""Check both script-spawn handlers with their real argument decoder."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static uint actor[85];
static int expected_link, created;
void *sub_54BFC0(uint *context, uint *position, uint script, int extra, int nested)
{
    REQUIRE(context[0] == (UINT_PTR)actor && context[1] == 2 && context[2] == 3);
    REQUIRE(context[3] == 0x140 && context[4] == 12);
    REQUIRE(context[5] == expected_link && context[6] == 0);
    REQUIRE(position == actor+8 && position[0] == 100 && position[1] == 200 && position[2] == 300);
    REQUIRE(script == 0x12345678 && extra == 4 && nested == 1);
    ++created; return NULL;
}
'''
MAIN = r'''
int main(void)
{
    uint arguments[5] = {2,4,3,0x40,12}, stack[1] = {0x12345678};
    unsigned int before, after;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    actor[8] = 100; actor[9] = 200; actor[10] = 300; actor[0x4e] = 0x100;
    __asm mov before, esp
    for (expected_link = 0; expected_link < 2; ++expected_link) {
        actor[0] = (UINT_PTR)arguments;
        actor[0x41] = (UINT_PTR)(stack+1); actor[0x42] = 1;
        if (expected_link) sub_553230((int)actor); else sub_5531D0((int)actor);
        REQUIRE(actor[0] == (UINT_PTR)(arguments+5));
        REQUIRE(actor[0x41] == (UINT_PTR)stack && actor[0x42] == 0);
    }
    __asm mov after, esp
    REQUIRE(created == 2 && before == after);
    puts("script actor spawn: complete seven-word contexts, inherited flags, child linkage, argument consumption and stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    decoder = (ROOT / 'decompiled/sub_553170.c').read_text()
    pop = (ROOT / 'decompiled/sub_54BC00.c').read_text()
    handlers = '\n'.join((ROOT / f'src_recovered/sub_{name}.c').read_text()
                         for name in ('5531D0', '553230'))
    raise SystemExit(build_and_run(SOURCE + decoder + pop + handlers + MAIN, 'script_spawn_test', bulk=False))
