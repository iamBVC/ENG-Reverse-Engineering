"""Check the original static state pointer is relocated despite field writes."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
'''
MAIN = r'''
int main(void)
{
    REQUIRE(PTR_DAT_00571f54 == (unsigned char *)DAT_00584660_storage);
    PTR_DAT_00571f54[0x54] = 1;
    REQUIRE(DAT_005846b4 == 1);
    _DAT_00584660 = 12.5f;
    _DAT_00584664 = 8.25f;
    REQUIRE(*(float *)(PTR_DAT_00571f54 + 0) == 12.5f);
    REQUIRE(*(float *)(PTR_DAT_00571f54 + 4) == 8.25f);
    puts("global state: relocated original pointer, byte field offsets and float aliases passed");
    return 0;
}
'''
if __name__ == '__main__':
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if 'DAT_00584660_storage[' in line or
                line.startswith('unsigned char *PTR_DAT_00571f54 ')]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(selected) + MAIN,
                                  'state_pointer_test', bulk=False))
