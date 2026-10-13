"""Check the generated stream routine's resolver/AAL calls before playback."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static char filename[] = "Intro\\Intro.wav", path[] = "E:\\game\\Intro\\Intro.wav";
static int resolves, loads, expected_flags, missing;
undefined4 *sub_415690(char *directory, char *file)
{
    REQUIRE(directory == NULL && file == filename); ++resolves;
    return missing ? NULL : (undefined4 *)path;
}
int _AAL_LoadFile_8(char *file, int flags)
{
    REQUIRE(file == path && flags == expected_flags); ++loads; return 0;
}
int _AAL_GetDataSize_4(int handle) { REQUIRE(0); return 0; }
int _AAL_GetSampleRate_4(int handle) { REQUIRE(0); return 0; }
int sub_426500() { return 0; }
undefined4 sub_5487A0() { REQUIRE(0); return 0; }
int sub_5489C0() { REQUIRE(0); return 0; }
'''
MAIN = r'''
int main(void)
{
    int i;
    DAT_005834dc = 0;
    REQUIRE(sub_546A30((int)filename, 0, 1) == 0 && resolves == 0);
    DAT_005834dc = 1; expected_flags = 0x40;
    REQUIRE(sub_546A30((int)filename, 0, 1) == 0 && resolves == 1 && loads == 1);
    expected_flags = 0;
    REQUIRE(sub_546A30((int)filename, 1, 0) == 0 && resolves == 2 && loads == 2);
    for (i = 0; i < 12; ++i) REQUIRE(DAT_006d93f8_storage[i] == 0);
    missing = 1;
    REQUIRE(sub_546A30((int)filename, 0, 1) == 0 && resolves == 3 && loads == 2);
    DAT_006d946c_storage[1] = 1;
    REQUIRE(sub_546A30((int)filename, 1, 0) == 0 && resolves == 3);
    puts("music loading: filename arguments, both stream channels/flags and failure guards passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    body = text.split('/* ==== sub_546A30 ==== */', 1)[1].split('/* ====', 1)[0]
    symbols = {s.removeprefix('_') for s in re.findall(r'\b(?:_?DAT|s)_[A-Za-z0-9_]+\b', body)}
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if ('_storage[' in line and 'DAT_00572ee0_storage[' not in line) or
                any(re.search(r'\b' + re.escape(s) + r'\b', line) for s in symbols)]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(selected) + body + MAIN,
                                  'music_arguments_test', bulk=False))
