"""Round-trip recovered input settings through a private registry fixture."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_00582260[3], DAT_00582b50[4];
unsigned int *DAT_005fcf70;
static char stored_name[260], stored_value[128];
static int present, writes;
bool sub_405800(char *name, char *value)
{
    REQUIRE(strlen(name) < sizeof stored_name && strlen(value) < sizeof stored_value);
    strcpy(stored_name, name); strcpy(stored_value, value); present = 1; ++writes; return 1;
}
undefined *sub_405790(char *name, undefined *fallback)
{
    return present ? (undefined *)stored_value : fallback;
}
'''

MAIN = r'''
int main(void)
{
    unsigned char options[96];
    int device[72] = {0}, bindings[14], i, before;
    const int keys[14] = {0xcb,0xcd,200,0xd0,0x1e,0x1f,0x39,0x2d,0x1c,0x19,0xc9,0xd1,0x2c,0x18};
    DAT_005fcf70 = (unsigned int *)options;
    DAT_00582260[0] = (int)&DAT_00582260[1]; DAT_00582260[1] = 0;
    DAT_00582260[2] = (int)DAT_00582260;
    memcpy(DAT_00582b50, "fixture keyboard", 16); /* Deliberately no terminator. */
    memset(options, 0xaa, sizeof options); options[11] = 0x30;
    for (i = 0; i < 14; ++i) (&DAT_00584758)[i] = keys[i];
    REQUIRE(sub_419A60(NULL) == 1 && writes == 1);
    REQUIRE(strcmp(stored_name, "InputDevice fixture keyboard") == 0);
    REQUIRE(strcmp(stored_value, "00CB00CD00C800D0001E001F0039002D001C001900C900D1002C001830") == 0);
    memset(DAT_00584758_storage, 0, sizeof DAT_00584758_storage);
    memset(options, 0xaa, sizeof options);
    REQUIRE(sub_419BD0(NULL) == 1);
    for (i = 0; i < 14; ++i) REQUIRE((&DAT_00584758)[i] == keys[i]);
    for (i = 0; i < sizeof options; ++i) REQUIRE(options[i] == (i == 11 ? 0x30 : 0xaa));
    stored_value[56] = 0; REQUIRE(sub_419BD0(NULL) == 1 && options[11] == 0x7f);
    strcpy(stored_value, "00CB"); REQUIRE(sub_419BD0(NULL) == 0);
    present = 0; REQUIRE(sub_419BD0(NULL) == 0);

    device[0] = (int)&DAT_00582260[1]; device[1] = (int)DAT_00582260;
    DAT_00582260[0] = (int)device;
    strcpy((char *)(device + 0x34), "joystick product");
    strcpy((char *)(device + 0x20), "joystick instance");
    device[0x17] = 1; device[0x18] = 2; device[0x19] = 3; device[0x1a] = 4;
    device[0x1c] = (int)bindings;
    for (i = 0; i < 14; ++i) bindings[i] = i;
    options[23] = 0x55;
    REQUIRE(sub_419A60(device) == 1);
    REQUIRE(strcmp(stored_name, "InputDevice joystick product joystick instance") == 0);
    REQUIRE(strlen(stored_value) == 106 && strncmp(stored_value, "X1:00000001 Y1:00000002 X2:00000003 Y2:00000004 ", 48) == 0);
    memset(bindings, 0, sizeof bindings);
    device[0x17] = device[0x18] = device[0x19] = device[0x1a] = 0;
    memset(options, 0xaa, sizeof options);
    REQUIRE(sub_419BD0(device) == 1);
    for (i = 0; i < 14; ++i) REQUIRE(bindings[i] == i);
    for (i = 0; i < 4; ++i) REQUIRE(device[0x17 + i] == i + 1);
    for (i = 0; i < sizeof options; ++i) REQUIRE(options[i] == (i == 23 ? 0x55 : 0xaa));
    stored_value[104] = 'Z'; stored_value[105] = 'Z';
    REQUIRE(sub_419BD0(device) == 1 && options[23] == 0x7f);
    before = writes; bindings[2] = 0x10000;
    REQUIRE(sub_419A60(device) == 0 && writes == before);
    puts("input settings: keyboard/joystick layouts, round trips, byte offsets, truncated data and option fallback passed");
    return 0;
}
'''

def main():
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_419A60', 'sub_419BD0']]
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8')
    tables = [line for line in definitions.splitlines() if 'DAT_00584758_storage[' in line]
    return build_and_run(SOURCE + '\n'.join(tables) + '\n'.join(bodies) + MAIN,
                         'input_settings_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
