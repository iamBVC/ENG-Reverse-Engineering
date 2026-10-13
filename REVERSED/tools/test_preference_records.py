"""Verify packed registry preference rows and both typed read/write paths."""
import re
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
static int cursor, reads, writes;
static int selected(int i)
{
    unsigned char *f = (unsigned char *)(DAT_00572ee0_storage + i * 4 + 3);
    return !(f[0] && !DAT_005833e0) && !(f[1] && DAT_005833e0);
}
static int next(const char *key)
{
    while (cursor < 39 && !selected(cursor)) ++cursor;
    REQUIRE(cursor < 39 && strcmp(key, (char *)DAT_00572ee0_storage[cursor * 4 + 2]) == 0);
    return cursor++;
}
float10 sub_4057C0(undefined4 raw, float fallback)
{
    int i = next((char *)raw), kind = DAT_00572ee0_storage[i * 4];
    REQUIRE(fallback == (kind == 0 ? 13.0f : kind == 1 ? -2.5f : 1.0f)); ++reads;
    return kind == 0 ? 7.9 : kind == 1 ? 0.625 : (i % 2);
}
bool sub_405870(undefined4 raw, undefined4 value)
{
    int i = next((char *)raw), kind = DAT_00572ee0_storage[i * 4];
    REQUIRE(kind != 1 && value == (kind == 0 ? 7 : i % 2)); ++writes; return 1;
}
bool sub_405830(undefined4 raw, float value)
{
    int i = next((char *)raw);
    REQUIRE(DAT_00572ee0_storage[i * 4] == 1 && value == 0.625f); ++writes; return 1;
}
void sub_545F90(int volume, int scale) { REQUIRE(scale == 128); }
'''
MAIN = r'''
int main(void)
{
    int caps, i;
    REQUIRE(sizeof DAT_00572ee0_storage == 39 * 16);
    for (i = 0; i < 39; ++i) {
        int *e = DAT_00572ee0_storage + i * 4;
        REQUIRE(e[0] == kinds[i] && e[3] == flags[i]);
        REQUIRE(strcmp((char *)e[2], keys[i]) == 0);
        REQUIRE(e[1] != 0 && e[1] != original_targets[i]);
    }
    for (caps = 0; caps < 2; ++caps) {
        DAT_005833e0 = caps; cursor = reads = writes = 0;
        for (i = 0; i < 39; ++i) if (selected(i)) {
            int *e = DAT_00572ee0_storage + i * 4;
            if (e[0] == 0) *(int *)e[1] = 13;
            else if (e[0] == 1) *(float *)e[1] = -2.5f;
            else *(unsigned char *)e[1] = 1;
        }
        sub_424590(); REQUIRE(reads == 21);
        cursor = 0; sub_424680(); REQUIRE(writes == 21);
        REQUIRE(DAT_005f6ec0 == 7 && DAT_005f6ec4 == 7 && DAT_005f6ec8 == 7);
    }
    puts("preferences: 39 original records, relocated targets/keys, both filters and integer/float/boolean read-write passed");
    return 0;
}
'''

def main():
    pe = PE(ROOT.parent / 'Game/groove.exe')
    rows = [struct.unpack('<4I', pe.read(0x572ee0 + i * 16, 16)) for i in range(39)]
    oracle = ''
    for name, column in [('kinds', 0), ('flags', 3), ('original_targets', 1)]:
        oracle += f'static const int {name}[39] = {{' + ','.join(hex(r[column]) for r in rows) + '};\n'
    oracle += 'static const char *keys[39] = {' + ','.join(
        '"' + pe.read(r[2], 100).split(b'\0')[0].decode('ascii') + '"' for r in rows) + '};\n'
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {n} ==== */', 1)[1].split('/* ====', 1)[0]
              for n in ['sub_424590', 'sub_424680']]
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    wanted = {'DAT_00572ee0_storage', 'DAT_005833e0_storage', 'DAT_00584ea0'}
    selected = []
    while True:
        new = [line for line in definitions if line not in selected and
               any(re.search(r'\b' + re.escape(s) + r'\b', line) for s in wanted)]
        if not new: break
        selected.extend(new)
        wanted.update(re.findall(r'\b(?:DAT|s|PTR)_[A-Za-z0-9_]+\b', '\n'.join(new)))
    return build_and_run(SOURCE + oracle + '\n'.join(selected) + '\n'.join(bodies) + MAIN,
                         'preference_records_test', bulk=False)

if __name__ == '__main__':
    raise SystemExit(main())
