"""Exercise real script handlers through both original dispatch tables."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    unsigned int actor[85] = {0};
    /* Set a primary-handler flag, register the menu actor, then yield. */
    unsigned int script[] = {(1U << 16) | 1U, 200U, 43U, 0xdeadbeef};
    unsigned int backward[] = {(0xffffU << 16) | 43U};
    unsigned int before, after;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    actor[0] = (UINT_PTR)script; DAT_006d9e28 = 0;
    __asm mov before, esp
    sub_54D180((int *)actor);
    __asm mov after, esp
    REQUIRE(before == after);
    REQUIRE(actor[0] == (UINT_PTR)(script+3));
    REQUIRE(actor[0x3a] == (0x1000000U | 0x8000000U | 2U));
    REQUIRE(DAT_006d9e28 == (UINT_PTR)actor);
    actor[0x3a] = 0; actor[0] = (UINT_PTR)backward;
    sub_54D180((int *)actor);
    REQUIRE(actor[0] == (UINT_PTR)backward && (actor[0x3a] & 2));
    actor[0] = 0;
    sub_54D180((int *)actor);
    REQUIRE(actor[0] == 0);
    puts("script dispatch: primary flag, secondary actor registration, yield, signed jump and stopped actor passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'script_vm_test'))
