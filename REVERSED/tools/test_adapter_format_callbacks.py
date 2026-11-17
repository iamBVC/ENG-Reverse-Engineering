"""Verify DirectDraw-format enumeration callbacks recovered from code-label bodies."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class AdapterFormatCallbackTests(unittest.TestCase):
    def test_callbacks_select_matching_formats_and_preserve_capability_flags(self):
        paths = [ROOT / "src_recovered" / "sub_40ED80.c",
                 ROOT / "src_recovered" / "sub_40EE30.c"]
        for path in paths:
            self.assertTrue(path.exists(), f"missing callback body: {path.name}")
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in paths)
        fixture = r'''
#include "ghidra_shim.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static const unsigned char GUID_A[16] = {0xe0,2,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0,0};
static const unsigned char GUID_B[16] = {0xe1,2,0x6d,0xa3,0xf3,0xc9,0xcf,0x11,0xbf,0xc7,0x44,0x45,0x53,0x54,0,0};
static void put32(unsigned char *p, unsigned int v) { memcpy(p, &v, 4); }
static unsigned int get32(const unsigned char *p) { unsigned int v; memcpy(&v, p, 4); return v; }
'''
        main = r'''
int main(void)
{
    unsigned char desc[0x24] = {0};
    unsigned char context[0x70] = {0};
    put32(desc + 0x1c, 0x100);
    memcpy(desc + 4, GUID_A, 16);
    put32(desc + 0x14, 16);
    put32(context + 0x5c, 0x80000000u);
    put32(context + 0x64, 0x80000000u);
    REQUIRE(sub_40ED80(desc, context) == 1);
    REQUIRE(get32(context + 0x5c) == 16);

    memcpy(desc + 4, GUID_B, 16);
    put32(desc + 0x14, 32);
    put32(context + 0x60, 0x80000000u);
    put32(context + 0x68, 0x80000000u);
    REQUIRE(sub_40ED80(desc, context) == 1);
    REQUIRE(get32(context + 0x60) == 32);

    memset(context, 0, sizeof context);
    put32(context + 0x5c, 0x80000000u);
    memset(desc + 4, 0, 16);
    desc[0x20] = 'U';
    put32(desc + 0x14, 24);
    REQUIRE(sub_40EE30(desc, context) == 1);
    REQUIRE(get32(context + 0x5c) == (24u | 0x40000000u));

    memset(context, 0, sizeof context);
    put32(context + 0x68, 0x80000000u);
    memset(desc + 4, 0, 16);
    desc[0x20] = 'V';
    put32(desc + 0x14, 32);
    REQUIRE(sub_40EE30(desc, context) == 1);
    REQUIRE(get32(context + 0x68) == (32u | 0x40000000u));

    put32(desc + 0x1c, 0);
    REQUIRE(sub_40EE30(desc, context) == 1);
    REQUIRE(get32(context + 0x68) == (32u | 0x40000000u));
    return 0;
}
'''
        self.assertEqual(build_and_run(fixture + bodies + main, "adapter_format_callbacks_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
