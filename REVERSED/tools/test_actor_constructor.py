"""Check the real actor constructor's capacity and list ownership rules."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
uint *DAT_00584648, *DAT_006d9e3c, *DAT_006d9e38, *DAT_006d9e18;
uint DAT_006d9dc8, DAT_006d9dc4;
byte DAT_006d9e14, DAT_006d9e15, DAT_006d9e16;
char s_Blank_005790d0[] = "Blank";
static uint allocation[22];
static int initialized;
void *sub_41AE20(uint words)
{ REQUIRE(words == 20); allocation[20] = allocation[21] = 0xfeedface; return allocation; }
uint sub_54BC00(int actor) { REQUIRE(0); return 0; }
void sub_54BC30(uint *actor) { REQUIRE(actor != NULL); ++initialized; }
'''
MAIN = r'''
int main(void)
{
    uint scene[32] = {0}, storage[87] = {0}, temporary[85] = {0};
    uint context[7] = {0}, position[8] = {1,2,3,4,5,6,7,8};
    uint *actor = storage + 1;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    scene[2] = 1; DAT_00584648 = scene;
    storage[0] = storage[86] = 0xcafebabe;
    DAT_006d9e3c = actor;
    temporary[70] = 0x12345678; temporary[71] = 0x98765432; temporary[72] = 0x12345678;
    context[0] = (UINT_PTR)temporary; context[6] = 0x76543210;
    REQUIRE(sub_54BFC0((int *)context, position, 99, 0, 0) == actor);
    REQUIRE(DAT_006d9dc8 == 1 && initialized == 1);
    REQUIRE(DAT_006d9e3c == NULL && DAT_006d9e38 == actor && actor[1] == 0);
    REQUIRE(actor[0] == 99 && actor[0x3c] == context[6]);
    REQUIRE(!memcmp(actor+8, position, sizeof position));
    REQUIRE(actor[0x46] == 0x12345678 && actor[0x47] == 0x98765432 && actor[0x48] == 0x12345678);
    REQUIRE(storage[0] == 0xcafebabe && storage[86] == 0xcafebabe);
    REQUIRE(allocation[20] == 0xfeedface && allocation[21] == 0xfeedface);
    REQUIRE(sub_54BFC0((int *)context, position, 100, 0, 0) == NULL);
    REQUIRE(DAT_006d9dc8 == 1 && initialized == 1);
    puts("actor constructor: byte-offset capacity, free/active lists, position, metadata, bounds and exhaustion passed");
    return 0;
}
'''
if __name__ == '__main__':
    path = ROOT / 'src_recovered/sub_54BFC0.c'
    body = path.read_text() if path.exists() else (ROOT / 'decompiled/sub_54BFC0.c').read_text()
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'actor_constructor_test', bulk=False))
