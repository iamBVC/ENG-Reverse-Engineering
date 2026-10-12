"""Verify input-table clearing cannot destroy the DirectInput interface."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[5], *keyboard_methods[14];
static struct { void **methods; } input;
static struct { void **methods; } keyboard;
static int enumerated;
static int formats, released, acquired;
static int WINAPI create_keyboard(UINT_PTR self, UINT_PTR guid, UINT_PTR output, UINT_PTR outer)
{
    REQUIRE(guid == (UINT_PTR)DAT_0056e61c && outer == 0);
    keyboard.methods = keyboard_methods; *(void **)output = &keyboard; return 0;
}
static int WINAPI query_keyboard(UINT_PTR self, UINT_PTR iid, UINT_PTR output)
{
    REQUIRE(self == (UINT_PTR)&keyboard && iid == (UINT_PTR)DAT_0056e6bc);
    *(void **)output = &keyboard; return 0;
}
static int WINAPI release_keyboard(UINT_PTR self) { ++released; return 1; }
static int WINAPI set_keyboard_format(UINT_PTR self, UINT_PTR raw)
{
    const DIDATAFORMAT *format = (const DIDATAFORMAT *)raw;
    REQUIRE(format->dwSize == sizeof *format && format->dwDataSize == 256 && format->dwNumObjs == 256);
    REQUIRE(format->rgodf != NULL); ++formats; return 0;
}
static int WINAPI cooperative(UINT_PTR self, UINT_PTR window, UINT_PTR flags)
{
    REQUIRE(window == 0x12345678 && flags == 0x16); return 0;
}
static int WINAPI acquire_keyboard(UINT_PTR self) { ++acquired; return 0; }
static int WINAPI enumerate(UINT_PTR self, UINT_PTR type, UINT_PTR callback, UINT_PTR context, UINT_PTR flags)
{
    unsigned int i;
    REQUIRE(self == (UINT_PTR)&input && (type == 3 || type == 4) && callback != 0 && context == 0 && flags == 1);
    if (type == 3) {
        unsigned char instance[560] = {0};
        int (WINAPI *visit)(unsigned char *, void *) = (void *)callback;
        memcpy(instance + 0x12c, "fixture keyboard", 16);
        REQUIRE(visit(instance, NULL) == 0);
        REQUIRE(memcmp(DAT_00582b50, "fixture keyboard", 16) == 0);
        return 0;
    }
    REQUIRE(DAT_00582a74 == (unsigned int *)&input);
    REQUIRE(sizeof DAT_00582a88 == 200);
    for (i = 0; i < 50; ++i) REQUIRE(DAT_00582a88[i] == 0);
    ++enumerated;
    return 0; /* This fixture has no joystick devices. */
}
int main(void)
{
    unsigned int i;
    input.methods = methods; methods[4] = enumerate;
    methods[3] = create_keyboard;
    keyboard_methods[0] = query_keyboard; keyboard_methods[2] = release_keyboard;
    keyboard_methods[11] = set_keyboard_format; keyboard_methods[13] = cooperative;
    keyboard_methods[7] = acquire_keyboard;
    DAT_00582a74 = (unsigned int *)&input;
    DAT_00582a70 = 0x12345678;
    DAT_00582260[0] = (int)&DAT_00582260[1]; DAT_00582260[1] = 0; DAT_00582260[2] = (int)DAT_00582260;
    for (i = 0; i < 50; ++i) DAT_00582a88[i] = 0xaaaaaaaa;
    REQUIRE(sub_40E9A0() == 0 && enumerated == 1);
    REQUIRE(DAT_00582a74 == (unsigned int *)&input && DAT_00582a70 == 0x12345678);
    REQUIRE(sub_40E880() == 1 && formats == 1 && released == 1 && acquired == 1);
    puts("input setup: clear bounds, keyboard interfaces, SDK data format and name callback passed");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "input_table_test"))
