"""Regression test for x87-derived map-view bounds in sub_42BF40."""
from pathlib import Path
import re

from test_hardware_enumeration import main as build_and_run

ROOT = Path(__file__).resolve().parent.parent
global_header = (ROOT / "src_generated" / "ghidra_globals.h").read_text(encoding="utf-8")
for symbol in ("DAT_0057f90c", "DAT_006d8400", "DAT_006d8408"):
    if not re.search(rf"extern\s+float\s+{symbol}\s*;", global_header):
        raise RuntimeError(f"{symbol} must be a float global, matching its original dword use")
generated = (ROOT / "src_generated" / "clean_subset.c").read_text(encoding="utf-8")
start = generated.find("byte sub_42BF40(")
if start < 0:
    raise RuntimeError("sub_42BF40 was not found in generated C")
opening = generated.find("{", start)
depth = 0
end = -1
for offset in range(opening, len(generated)):
    if generated[offset] == "{":
        depth += 1
    elif generated[offset] == "}":
        depth -= 1
        if depth == 0:
            end = offset + 1
            break
if end < 0:
    raise RuntimeError("sub_42BF40 body is unbalanced")
function_source = generated[start:end]

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>

#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
float DAT_0057f90c;
float DAT_0056e180 = 2.0f;
float DAT_0056e018 = 1.0f, DAT_0056e020 = 1.0f;
float DAT_006d8400, DAT_006d8408;
unsigned int DAT_0058642c;
int DAT_005865cc, DAT_005865d4;
#define _DAT_0058642c DAT_0058642c
#define _DAT_006d8400 DAT_006d8400
#define _DAT_006d8408 DAT_006d8408
#define _DAT_0056e018 DAT_0056e018
#define _DAT_0056e020 DAT_0056e020
static unsigned int visible_geometry_calls;
undefined4 sub_556510();
undefined4 sub_41FB30();

int __declspec(naked) __ftol(void)
{
    __asm {
        sub esp, 4
        fistp dword ptr [esp]
        pop eax
        ret
    }
}

undefined4 sub_556510(int model, float *position, float *offset, unsigned int detail)
{
    REQUIRE(model != 0 && position != NULL && offset != NULL);
    ++visible_geometry_calls;
    return 1;
}

undefined4 sub_41FB30() { return 1; }

'''+function_source+r'''

int main(void)
{
    unsigned char map[0x60] = {0};
    int cell[2] = {0, 0};
    int *cell_heads[1] = {cell};
    unsigned int visibility[1] = {0};
    int model_index[1] = {0};
    unsigned int detail_table[1];
    unsigned char detail_record[8] = {0};
    unsigned int records[8] = {0};
    unsigned char actor[0x84] = {0};
    volatile float stale = 10.0f;
    unsigned int result;

    *(int *)(map + 0x14) = 1;
    *(int *)(map + 0x18) = 1;
    *(int *)(map + 0x3c) = (int)records;
    *(int *)(map + 0x40) = (int)cell_heads;
    *(int *)(map + 0x48) = (int)visibility;
    *(int *)(map + 0x4c) = (int)model_index;
    *(int *)(map + 0x58) = (int)detail_table;
    detail_table[0] = (unsigned int)detail_record;

    DAT_0057f90c = 0;
    DAT_005865cc = 3;
    DAT_005865d4 = 0;
    _DAT_0058642c = 1;
    _DAT_006d8400 = 0.0f;
    _DAT_006d8408 = 0.0f;

    /* Simulate arbitrary x87 leftovers: Ghidra's no-argument __ftol calls
       consume these instead of the missing bounds expressions. */
    __asm {
        fld dword ptr [stale]
        fld dword ptr [stale]
        fld dword ptr [stale]
        fld dword ptr [stale]
    }
    result = sub_42BF40((int)map, (int)actor);

    REQUIRE(result == 1);
    REQUIRE(visible_geometry_calls == 1);
    puts("scene clip bounds: one visible map cell is traversed using explicit camera bounds");
    return 0;
}
'''

if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "scene_clip_bounds_test", bulk=False))
