"""ABI tests for two 7-byte x86 indirect tail-dispatch functions."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class TailDispatchThunkTests(unittest.TestCase):
    def test_original_thunks_forward_ecx_and_stack_argument_to_target(self):
        paths = [ROOT / "src_recovered" / "sub_562F4C.c",
                 ROOT / "src_recovered" / "sub_562F53.c"]
        for path in paths:
            self.assertTrue(path.exists(), f"missing recovered thunk: {path.name}")
        fixture = r'''
#include "ghidra_shim.h"
static unsigned int seen_ecx;
static unsigned int seen_stack;
__declspec(naked) static int tail_target(void)
{
    __asm {
        mov dword ptr [seen_ecx], ecx
        mov eax, dword ptr [esp + 4]
        mov dword ptr [seen_stack], eax
        mov eax, 0x2468ace0
        ret 4
    }
}
'''
        main = r'''
static int invoke_one(void)
{
    int result;
    __asm {
        push 0x13579bdf
        push offset tail_target
        push 0x11223344
        call sub_562F4C
        add esp, 8
        mov dword ptr [result], eax
    }
    return result;
}
static int invoke_two(void)
{
    int result;
    __asm {
        push 0x13579bdf
        push offset tail_target
        push 0x55667788
        call sub_562F53
        add esp, 8
        mov dword ptr [result], eax
    }
    return result;
}
int main(void)
{
    if (invoke_one() != 0x2468ace0 || seen_ecx != 0x11223344 ||
        seen_stack != 0x13579bdf) return 1;
    if (invoke_two() != 0x2468ace0 || seen_ecx != 0x55667788 ||
        seen_stack != 0x13579bdf) return 2;
    return 0;
}
'''
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in paths)
        self.assertEqual(build_and_run(fixture + bodies + main,
                                       "abi56", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
