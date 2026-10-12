"""Compare preset selection and renderer records to original executable data."""
import struct
from pe_tools import PE
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_00572298, DAT_005848cc, DAT_00583400, DAT_00583404;
unsigned int *DAT_00583420, *DAT_00583424, *DAT_0058342c;
'''

MAIN = r'''
int main(void)
{
    unsigned int adapter[8] = {0}, device[64] = {0}, mode[32] = {0};
    int caps, preset, i;
    for (caps = 0; caps < 2; ++caps) {
        DAT_005833e0 = caps;
        REQUIRE((unsigned int **)&PTR_DAT_00573d68 == (unsigned int **)PTR_DAT_00573d68_storage);
        REQUIRE((unsigned int *)PTR_DAT_00573d68_storage[caps * 6] ==
                (unsigned int *)(caps ? DAT_00573d98_storage : DAT_00573e28_storage));
        for (preset = 0; preset < 5; ++preset) {
            PTR_DAT_00573d68_storage[caps * 6 + 3] = preset;
            sub_410430();
            REQUIRE(memcmp(&DAT_00573d28, expected[caps][preset], 28) == 0);
            REQUIRE(_DAT_00572298 == 0);
            REQUIRE(DAT_005848cc == (caps ? 0 : 0x3f800000));
            REQUIRE(&DAT_00573d36 == (unsigned char *)&DAT_00573d28 + 14);
            REQUIRE(DAT_00573d38 == (int)expected[caps][preset][4]);
        }
    }
    DAT_00583420 = adapter; DAT_00583424 = device; DAT_0058342c = mode;
    adapter[5] = 640; adapter[6] = 480;
    for (i = 0; i < 7; ++i) device[4 + i] = 0x01020300 + i;
    for (i = 0; i < 8; ++i) {
        mode[23 + i] = 0x11223300 + i;
        device[22 + i] = 0x22334400 + i;
        device[30 + i] = 0x33445500 + i;
        device[38 + i] = 0x44556600 + i;
        device[46 + i] = 0x55667700 + i;
    }
    sub_411620();
    REQUIRE(_DAT_00583400 == 640 && _DAT_00583404 == 480);
    REQUIRE(memcmp(&DAT_005833e0, device + 4, 28) == 0);
    REQUIRE(memcmp(&DAT_005833c0, mode + 23, 32) == 0);
    REQUIRE(memcmp(&DAT_00583490, device + 22, 32) == 0);
    REQUIRE(memcmp(&DAT_005834b0, device + 30, 32) == 0);
    REQUIRE(memcmp(&DAT_00583470, device + 38, 32) == 0);
    REQUIRE(memcmp(&DAT_00583450, device + 46, 32) == 0);
    puts("graphics preferences: both device classes, all ten presets, packed aliases and six renderer copies passed");
    return 0;
}
'''

def main():
    pe = PE(ROOT.parent / 'Game/groove.exe')
    expected = []
    for address in [0x573e28, 0x573d98]:
        words = struct.unpack('<35I', pe.read(address, 140))
        expected.append('{' + ','.join('{' + ','.join(hex(v) for v in words[i:i+7]) + '}'
                                      for i in range(0, 35, 7)) + '}')
    oracle = 'static const unsigned int expected[2][5][7] = {' + ','.join(expected) + '};\n'
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_410430', 'sub_411620']]
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8')
    tables = [line for line in definitions.splitlines() if '_storage[' in line]
    return build_and_run(SOURCE + oracle + '\n'.join(tables) + '\n'.join(bodies) + MAIN,
                         'graphics_preferences_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
