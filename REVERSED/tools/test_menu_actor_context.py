"""Check the scene actor constructor's original contiguous input context."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
uint DAT_006d9dc8;
uint DAT_006d9e28, DAT_006d9e38;
static uint records[2][18];
static int created, finished;
void *sub_54BFC0(uint *context, uint *position, uint kind, int extra, int nested)
{
    uint *actor = (uint *)context[0];
    REQUIRE(context[1] == 2 && context[2] == 3 && context[3] == 0x40 && context[4] == 12);
    REQUIRE(context[5] == 0 && context[6] == (UINT_PTR)records[0]);
    REQUIRE(position[0] == 4096 && position[1] == (uint)-8192 && position[2] == 12288);
    REQUIRE(position[4] == 10 && position[5] == 20 && position[6] == 30 && position[7] == 40);
    REQUIRE(actor[65] == 0x12340008 && actor[70] == 0x56780000 && actor[71] == 7 && actor[72] == 0x56780000);
    REQUIRE(kind == 9 && extra == 16 && nested == 0);
    ++created; return NULL;
}
void sub_41E1B0(void) { ++finished; }
'''
MAIN = r'''
int main(void)
{
    uint scene[15] = {0};
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    records[0][0] = 1; records[0][1] = -2; records[0][2] = 3;
    records[0][4] = 10; records[0][5] = 20; records[0][6] = 30; records[0][7] = 40;
    records[0][8] = 9; records[0][9] = 2; records[0][10] = 0x12340000;
    records[0][11] = 16; records[0][12] = 3; records[0][13] = 0x40; records[0][14] = 12;
    records[0][15] = 0x56780000; records[0][16] = 7;
    records[1][17] = 2;
    scene[1] = 2; scene[14] = (UINT_PTR)records;
    DAT_006d9dc8 = 99;
    sub_54CFC0((int)scene);
    REQUIRE(created == 1 && finished == 1 && DAT_006d9dc8 == 0);
    scene[1] = 0;
    sub_54CFC0((int)scene);
    REQUIRE(created == 1 && finished == 2);
    puts("menu actor context: contiguous metadata, position, attributes, script fields and excluded records passed");
    return 0;
}
'''
if __name__ == '__main__':
    path = ROOT / 'src_recovered/sub_54CFC0.c'
    body = path.read_text() if path.exists() else (ROOT / 'decompiled/sub_54CFC0.c').read_text()
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'menu_actor_context_test', bulk=False))
