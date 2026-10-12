"""Validate recovered sound configuration and object arguments with AAL mocks."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static int init_error, device_error, constructed, pools, quit_calls, driver_calls;
void *operator_new(unsigned int size) { return calloc(1, size); }
int sub_545270(void) { return 0; }
float10 sub_4057C0(undefined4 name, float fallback) { REQUIRE(name != 0); return fallback; }
int _AAL_Init_0(void) { return init_error; }
int _AAL_InitDriver_4(unsigned int *driver)
{
    REQUIRE(driver[1] == 0 && driver[2] == 0 && driver[3] == 0 && driver[4] == 24);
    REQUIRE(driver[5] == 0x20001 && driver[6] == 44100 && driver[7] == 176400 && driver[8] == 0x100004);
    ++driver_calls; return 0;
}
int _AAL_GetDeviceId_4(int index) { REQUIRE(index == 1); return device_error ? -1 : 0; }
int _AAL_Quit_0(void) { ++quit_calls; return 0; }
int _AAL_SetSpeakerMode_4(int mode) { REQUIRE(mode == 4); return mode; }
int _AAL_Open3DProvider_4(int handle) { REQUIRE(0); return 0; }
int _AAL_Get3DAttributes_8(int handle, int object) { REQUIRE(0); return 0; }
int sub_546E50(void) { return 0; }
void sub_547470(unsigned int *object, unsigned int *settings)
{
    static const unsigned int expected[8] = {0, 24, 0, 5, 3, 0, 0, 30};
    REQUIRE((int)object == DAT_006d9494 && DAT_006d9490 == DAT_006d9494);
    REQUIRE(memcmp(settings, expected, sizeof expected) == 0);
    REQUIRE(object[0x100/4] == 0x1000 && object[0xf4/4] == 0x1000);
    REQUIRE(object[0xf8/4] == 0 && object[0xfc/4] == 0);
    ++constructed;
}
void sub_548650(unsigned int *object, unsigned int *pool)
{
    REQUIRE((int)object == DAT_006d9498);
    REQUIRE(pool[0] == 64 && pool[1] == 256 && pool[2] == 30 && pool[3] == 0x4000); ++pools;
}
void sub_548CF0(unsigned int *object, unsigned int *pool)
{
    REQUIRE((int)object == DAT_006d949c);
    REQUIRE(pool[0] == 16 && pool[1] == 48 && pool[2] == 30 && pool[3] == 16); ++pools;
}
void sub_545F90(int volume, int scale) { REQUIRE(volume == 127 && scale == 128); }
void sub_546000(int volume, int scale) { REQUIRE(volume == 96 && scale == 128); }
void sub_545140(void) {}
'''

MAIN = r'''
int main(void)
{
    REQUIRE(sub_545030() == 1 && constructed == 1 && pools == 2 && driver_calls == 1);
    sub_546EA0(DAT_006d9494, 0);
    REQUIRE(constructed == 1 && driver_calls == 1); /* Already initialized. */
    DAT_006d9490 = 0; init_error = 1;
    REQUIRE(sub_545030() == 0 && DAT_005834dc == 0 && constructed == 1 && pools == 2);
    init_error = 0; device_error = 1;
    REQUIRE(sub_545030() == 0 && DAT_006d9490 == 0 && DAT_005834dc == 0 && quit_calls == 1);
    puts("sound initialization: allocated object, PCM structure, settings/pools, volumes and failure paths passed");
    return 0;
}
'''

def main():
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_545030', 'sub_546EA0']]
    symbols = {s.removeprefix('_') for s in re.findall(r'\b(?:_?DAT|s)_[A-Za-z0-9_]+\b', '\n'.join(bodies))}
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if any(re.search(r'\b' + re.escape(s) + r'\b', line) for s in symbols)]
    return build_and_run(SOURCE + '\n'.join(selected) + '\n'.join(bodies) + MAIN,
                         'sound_initialization_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
