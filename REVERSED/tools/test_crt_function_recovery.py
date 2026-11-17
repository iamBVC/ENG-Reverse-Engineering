"""Verify recovered CRT bridge behavior and inclusion of the locale initializer."""
from pathlib import Path
import sys
import unittest
import re

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402
from make_dll_source import substituted  # noqa: E402


class RemainingCrtFunctionTests(unittest.TestCase):
    def test_alloca_probe_keeps_its_original_eax_and_stack_abi(self):
        crt_bodies = (ROOT / "harness" / "crt_bodies.txt").read_text(encoding="utf-8")
        aliases = (ROOT / "harness" / "crt_aliases.c").read_text(encoding="utf-8")
        recovered = (ROOT / "src_recovered" / "sub_562840.c").read_text(encoding="utf-8")
        generated = (ROOT / "src_generated" / "bulk_all.c").read_text(encoding="utf-8")
        self.assertNotRegex(crt_bodies, r"(?m)^\s*sub_562840\b")
        self.assertNotIn("void sub_562840(void) { }", aliases)
        self.assertNotIn("sub_562840", substituted())
        self.assertIn("test dword ptr [ecx], eax", recovered.lower())
        self.assertIn("test dword ptr [ecx], eax", generated.lower())

    def test_onexit_bridge_registers_callback_with_the_process_crt(self):
        source_path = ROOT / "src_recovered" / "sub_5626AD.c"
        self.assertTrue(source_path.exists(), "missing recovered sub_5626AD bridge")
        main = r'''
#include <stdlib.h>
int sub_5626AD(void *);
static int called;
static void callback(void) { called = 1; }
static void verify(void) { if (!called) _exit(9); }
int main(void)
{
    atexit(verify);
    if (sub_5626AD((void *)callback) != 0) return 2;
    return 0;
}
'''
        source = source_path.read_text(encoding="utf-8") + main
        self.assertEqual(build_and_run(source, "crt_onexit_bridge_test", bulk=False), 0)

    def test_locale_initializer_is_not_filtered_from_the_executable(self):
        crt_bodies = (ROOT / "harness" / "crt_bodies.txt").read_text(encoding="utf-8")
        bulk = (ROOT / "src_generated" / "bulk_all.c").read_text(encoding="utf-8")
        self.assertNotRegex(crt_bodies, r"(?m)^\s*sub_56C06A\b")
        self.assertIsNotNone(re.search(
            r"int sub_56C06A\(void\).*?sub_56BCA6\(0xfffffffd\).*?DAT_006db928 = 1",
            bulk,
            re.S,
        ))


if __name__ == "__main__":
    unittest.main()
