"""Exercise generated state clearing, binding initialization and key swaps."""
from test_hardware_enumeration import ROOT, main as build_and_run

PREAMBLE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_00582260[3];
static int reads, saves;
undefined4 sub_419BD0(int *device) { REQUIRE(device == NULL); ++reads; return 0; }
undefined4 sub_419A60(int *device) { REQUIRE(device == NULL); ++saves; return 1; }
void sub_40F290(int *device, int axis, int range, int value) { REQUIRE(0); }
void LAB_0040ed80() { REQUIRE(0); }
void LAB_0040ee30() { REQUIRE(0); }
void LAB_0040ef50() { REQUIRE(0); }
void LAB_0040ef90() { REQUIRE(0); }
'''

MAIN = r'''
int main(void)
{
    int i, head;
    const int keys[14] = {0xcb,0xcd,200,0xd0,0x1e,0x1f,0x39,0x2d,0x1c,0x19,0xc9,0xd1,0x2c,0x18};
    const int buttons[14] = {0x20,0x21,0x22,0x23,4,5,1,0,3,8,6,7,2,9};
    DAT_00582260[0] = (int)&DAT_00582260[1]; DAT_00582260[1] = 0;
    DAT_00582260[2] = (int)DAT_00582260; head = DAT_00582260[0];
    for (i = 0; i < 256; ++i) (&DAT_0058226c)[i] = 0xaaaaaaaa;
    for (i = 0; i < 15; ++i) (&DAT_005821e0)[i] = 0xaaaaaaaa;
    sub_40E0A0();
    REQUIRE(DAT_00582260[0] == head && DAT_00582260[1] == 0 && DAT_00582260[2] == (int)DAT_00582260);
    for (i = 0; i < 256; ++i) REQUIRE((&DAT_0058226c)[i] == 0);
    for (i = 0; i < 15; ++i) REQUIRE((&DAT_005821e0)[i] == 0);
    sub_419810();
    REQUIRE(reads == 1 && saves == 1 && DAT_00582260[0] == head);
    for (i = 0; i < 14; ++i) {
        int j, special = 0;
        REQUIRE((&DAT_00584758)[i] == keys[i]);
        REQUIRE((&DAT_005847c8)[i] == keys[i]);
        REQUIRE((&DAT_00584790)[i] == buttons[i]);
        for (j = 0; j < 6; ++j) if (keys[i] == (&DAT_005720e8)[j]) special = 1;
        REQUIRE((&DAT_00584800)[i] == special);
    }
    REQUIRE(&DAT_005847cc == &DAT_005847c8 + 1);
    REQUIRE(&_DAT_005847fc == &DAT_005847c8 + 13);
    REQUIRE(&DAT_00582270 == &DAT_0058226c + 1);
    sub_4199F0(0, 0, keys[1]);
    REQUIRE((&DAT_00584758)[0] == keys[1] && (&DAT_00584758)[1] == keys[0]);
    puts("input bindings: full clear bounds, empty list, 14 defaults, special keys and rebinding passed");
    return 0;
}
'''

def main():
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_40E0A0', 'sub_40ECD0', 'sub_419810', 'sub_4199F0']]
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8')
    tables = [line for line in definitions.splitlines() if '_storage[' in line and 'DAT_00572ee0_storage[' not in line]
    return build_and_run(PREAMBLE + '\n'.join(tables) + '\n'.join(bodies) + MAIN,
                         'bindings_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
