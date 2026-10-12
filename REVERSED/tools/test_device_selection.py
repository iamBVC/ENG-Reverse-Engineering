"""Test generated selection and iterator code with deterministic adapter lists."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

PREAMBLE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static int adapters[2][10], devices[2][54], formats[2][15], modes[2][36];
static unsigned int identifiers[2][4] = {{1,2,3,4}, {5,6,7,8}};
static int attempted, configured, reject_mode, reject_adapter, selected;
static int sub_562717(char *buffer, const char *format, ...)
{
    int n; va_list args; va_start(args, format); n = vsprintf(buffer, format, args); va_end(args); return n;
}
int __strcmpi(const char *a, const char *b) { return _stricmp(a, b); }
void sub_40FE10(void) { }
void sub_4106C0(void) { }
void sub_410ED0(void) { }
void sub_411620(void) { }
void sub_4114F0(int adapter, int device, int format, int mode, int fallback) { selected = adapter; }
undefined4 sub_410550(int adapter)
{
    ++attempted; return !(reject_adapter && adapter == (int)adapters[0]);
}
undefined4 sub_410700(int format, int mode, int adapter, int device)
{
    ++configured;
    REQUIRE(format == (int)formats[adapter == (int)adapters[0] ? 0 : 1]);
    return !reject_mode;
}
undefined4 sub_411000(int device) { return 1; }
'''

MAIN = r'''
static void list_init(int *owner) { owner[0] = (int)(owner + 1); owner[1] = 0; owner[2] = (int)owner; }
static void list_add(int *owner, int *node)
{
    int *last = (int *)owner[2];
    node[0] = (int)(owner + 1); node[1] = (int)last;
    last[0] = (int)node; owner[2] = (int)node;
}
static void setup(void)
{
    int i;
    memset(adapters, 0, sizeof adapters); memset(devices, 0, sizeof devices);
    memset(formats, 0, sizeof formats); memset(modes, 0, sizeof modes);
    list_init(DAT_00583410);
    DAT_00582cc8 = 0;
    attempted = configured = selected = reject_mode = reject_adapter = 0;
    for (i = 0; i < 2; ++i) {
        adapters[i][3] = (int)identifiers[i]; devices[i][3] = (int)identifiers[i];
        formats[i][3] = 16; modes[i][3] = 640; modes[i][4] = 480;
        list_init(adapters[i] + 7); list_init(devices[i] + 11); list_init(formats[i] + 12);
        list_add(formats[i] + 12, modes[i]); list_add(devices[i] + 11, formats[i]);
        list_add(adapters[i] + 7, devices[i]); list_add(DAT_00583410, adapters[i]);
    }
}
int main(void)
{
    int size[2] = {640, 480}, missing_size[2] = {800, 600};
    const char *id;
    setup();
    REQUIRE(sizeof DAT_0057ee44 == 48);
    id = sub_405720(identifiers[0]);
    REQUIRE(strcmp(id, "{00000001-0002-0000-0300-000004000000}") == 0);
    REQUIRE(sub_4134C0((int)adapters[0], "{00000001-0002-0000-0300-000004000000}") == 0);
    REQUIRE(sub_4134C0((int)adapters[0], "unmatched") == -1);
    REQUIRE(sub_40FFD0("unmatched", "unmatched", 32, 32, size, size) == 1);
    REQUIRE(attempted == 1 && configured == 1 && selected == (int)adapters[0]);
    setup(); reject_adapter = 1;
    REQUIRE(sub_40FFD0("unmatched", "unmatched", 16, 16, missing_size, missing_size) == 1);
    REQUIRE(attempted == 2 && configured == 1 && selected == (int)adapters[1]);
    setup(); reject_mode = 1;
    REQUIRE(sub_40FFD0("unmatched", "unmatched", 32, 32, size, size) == 0);
    REQUIRE(attempted == 2 && configured == 2 && selected == 0);
    puts("device selection: GUID comparison, adapter fallback, format/mode fallback and exhausted lists passed");
    return 0;
}
'''

def main():
    text = (ROOT / "src_generated/clean_subset.c").read_text(encoding="utf-8")
    names = ['sub_405720', 'sub_4134C0', 'sub_4136C0', 'sub_4136D0', 'sub_4137B0',
             'sub_4137D0', 'sub_413510', 'sub_413820', 'sub_40FFD0']
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0] for name in names]
    symbols = set(re.findall(r'\b(?:_?DAT|s|PTR)_[A-Za-z0-9_]+\b', '\n'.join(bodies)))
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if any(re.search(r'\b' + re.escape(s) + r'\b', line) for s in symbols)]
    return build_and_run(PREAMBLE + '\n'.join(selected) + '\n'.join(bodies) + MAIN,
                         'selection_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
