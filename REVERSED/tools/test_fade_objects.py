"""Validate recovered color object construction and explicit this arguments."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <math.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
unsigned char DAT_006d7c61;
'''
MAIN = r'''
int main(void)
{
    struct { unsigned int before; float object[10]; unsigned int after; } data;
    float grey;
    data.before = 0x12345678; data.after = 0x87654321;
    REQUIRE(sub_41BCB0((int)data.object) == (int)data.object);
    REQUIRE(data.object[8] == 0 && data.object[9] == 0);
    DAT_006d7c61 = 1;
    sub_41BCF0((int)data.object, 255, 128, 0, 255);
    REQUIRE(fabs(data.object[0] - 1.0f) < 0.00001 && fabs(data.object[1] - 128.0f/255.0f) < 0.00001);
    REQUIRE(data.object[2] == 0 && fabs(data.object[3] - 1.0f) < 0.00001);
    DAT_006d7c61 = 0;
    sub_41BCF0((int)data.object, 255, 128, 0, 255);
    grey = data.object[4] * _DAT_0056e138 + data.object[6] * _DAT_0056e130 + data.object[5] * _DAT_0056e134;
    REQUIRE(fabs(data.object[0] - grey) < 0.00001 && data.object[0] == data.object[1] && data.object[1] == data.object[2]);
    REQUIRE(data.before == 0x12345678 && data.after == 0x87654321);
    puts("fade objects: returned constructor pointer, RGBA scaling, grayscale coefficients and bounds passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    bodies = [text.split(f'/* ==== {name} ==== */', 1)[1].split('/* ====', 1)[0]
              for name in ['sub_41BCB0', 'sub_41BEE0', 'sub_41BCF0']]
    globals_text = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8')
    selected = [line for line in globals_text.splitlines() if
                re.search(r'\bDAT_0056e(?:0c8|130|134|138)\b', line)]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(selected) + '\n'.join(bodies) + MAIN,
                                  'fade_objects_test', bulk=False))
