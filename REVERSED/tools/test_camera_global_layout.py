"""Verify Ghidra's camera globals retain their original byte offsets in C."""
from pathlib import Path

from test_hardware_enumeration import main as build_and_run

ROOT = Path(__file__).resolve().parent.parent
header = (ROOT / "src_generated" / "ghidra_globals.h").read_text(encoding="utf-8")
if "DAT_005790a0_storage[8]" in header:
    storage_definitions = "int DAT_005790a0_storage[8];"
else:
    storage_definitions = """
unsigned char DAT_005790a0;
int DAT_005790a4, DAT_005790b0, DAT_005790b4, DAT_005790b8;
unsigned char DAT_005790bc;
"""
if "DAT_006d9d70_storage[7]" in header:
    storage_definitions += "\nint DAT_006d9d70_storage[7];\n"
else:
    storage_definitions += """
unsigned char DAT_006d9d70;
int DAT_006d9d80, DAT_006d9d84, DAT_006d9d88;
"""


SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include <stdlib.h>

#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

/*TEST_STORAGE*/

int main(void)
{
    UINT_PTR base = (UINT_PTR)&DAT_005790a0;
    REQUIRE((UINT_PTR)&DAT_005790a4 == base + 0x04);
    REQUIRE((UINT_PTR)&DAT_005790b0 == base + 0x10);
    REQUIRE((UINT_PTR)&DAT_005790b4 == base + 0x14);
    REQUIRE((UINT_PTR)&DAT_005790b8 == base + 0x18);
    {
        UINT_PTR target = (UINT_PTR)&DAT_006d9d70;
        REQUIRE((UINT_PTR)&DAT_006d9d80 == target + 0x10);
        REQUIRE((UINT_PTR)&DAT_006d9d84 == target + 0x14);
        REQUIRE((UINT_PTR)&DAT_006d9d88 == target + 0x18);
    }
    puts("camera global layout: source and target fields retain original offsets");
    return 0;
}
'''.replace("/*TEST_STORAGE*/", storage_definitions)


if __name__ == "__main__":
    raise SystemExit(build_and_run(SOURCE, "camera_global_layout_test", bulk=False))
