"""Validate the child-script reference resolver's byte offsets and rewriting."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int *DAT_006d9dbc;
int DAT_006da31c, DAT_006da324;
'''
MAIN = r'''
int main(void)
{
    int actor[85] = {0}, scripts[16] = {0}, words[3], stack[3] = {0};
    int external[1] = {(int)(scripts+7)};
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    DAT_006d9dbc = scripts; DAT_006da31c = 1; DAT_006da324 = (int)external;
    actor[0x41] = (int)stack;
    words[0] = 99; words[1] = 20; words[2] = 0x12345678;
    actor[0] = (int)(words+1);
    sub_553630(actor);
    REQUIRE(words[0] == 69 && words[1] == (int)((byte *)scripts+20));
    REQUIRE(stack[0] == words[1] && actor[0] == (int)(words+2) && actor[0x42] == 1);
    words[0] = 99; words[1] = -1; actor[0] = (int)(words+1);
    sub_553630(actor);
    REQUIRE(words[1] == external[0] && stack[1] == external[0] && actor[0x42] == 2);
    words[0] = 99; words[1] = -2; actor[0] = (int)(words+1);
    sub_553630(actor);
    REQUIRE(words[1] == 0 && stack[2] == 0 && actor[0x42] == 3);
    REQUIRE(words[2] == 0x12345678);
    puts("script references: byte relocation, external lookup, unresolved lookup, opcode rewriting and stack writes passed");
    return 0;
}
'''
if __name__ == '__main__':
    body = (ROOT / 'src_recovered/sub_553630.c').read_text()
    push = (ROOT / 'decompiled/sub_54BBD0.c').read_text()
    raise SystemExit(build_and_run(SOURCE + push + body + MAIN, 'script_reference_test', bulk=False))
