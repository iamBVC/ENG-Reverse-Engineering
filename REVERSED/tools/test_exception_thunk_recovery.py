"""Validate the implicit EAX argument preserved by MSVC 6 EH forwarding code."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class ExceptionThunkRecoveryTests(unittest.TestCase):
    def test_562fa9_forwards_four_stack_arguments_eax_and_three_zero_slots(self):
        source = ROOT / "src_recovered" / "sub_562FA9.c"
        self.assertTrue(source.exists(), "missing recovered MSVC EH wrapper at 0x00562FA9")
        fixture = r'''
#include <stdint.h>
static unsigned call_count;
void *__cdecl groove_resolve_legacy_func_info(void *legacy)
{
    if ((uintptr_t)legacy == 0x13572468) return (void *)0x24681357;
    return legacy;
}
int __cdecl sub_5675F8(int a1, int a2, int a3, int a4,
                       int a5, int a6, int a7, int a8)
{
    ++call_count;
    if (a1 != 11 || a2 != 22 || a3 != 33 || a4 != 44 ||
        a5 != 0x24681357 || a6 != 0 || a7 != 0 || a8 != 0)
        return -1;
    return 0x24681357;
}
'''
        main = r'''
int main(void)
{
    int result = 0;
    __asm {
        mov eax, 013572468h
        push 44
        push 33
        push 22
        push 11
        call sub_562FA9
        add esp, 16
        mov result, eax
    }
    if (call_count != 1) return 1;
    if (result != 0x24681357) return 2;
    return 0;
}
'''
        body = source.read_text(encoding="utf-8")
        self.assertEqual(build_and_run(fixture + body + main,
                                       "eh_wrapper_562fa9_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
