"""Exercise four MSVC cleanup funclets with the frame shape they expect."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class EhEpilogueRecoveryTests(unittest.TestCase):
    def test_cleanup_epilogues_restore_fs_chain_registers_and_frame(self):
        labels = ["40FBCA", "41069E", "410EB7", "41145D"]
        paths = [ROOT / "src_recovered" / f"sub_{address}.c" for address in labels]
        for path in paths:
            self.assertTrue(path.exists(), f"missing recovered cleanup body: {path.name}")

        fixture = r'''
#include <stdint.h>
static unsigned saved_exception_head;
static unsigned read_exception_head(void)
{
    unsigned value;
    __asm {
        mov eax, dword ptr fs:[0]
        mov value, eax
    }
    return value;
}
int __cdecl invoke_cleanup(void *target);
__declspec(naked) int __cdecl invoke_cleanup(void *target)
{
    __asm {
        mov edx, dword ptr [esp + 4]
        push ebp
        mov ebp, esp
        sub esp, 0ch
        mov ecx, dword ptr fs:[0]
        mov saved_exception_head, ecx
        mov dword ptr [ebp - 0ch], ecx
        push ebx
        push esi
        push edi
        mov eax, 12345678h
        jmp edx
    }
}
'''
        main = "int main(void) {\n"
        for address in labels:
            main += (
                f"  if ((invoke_cleanup((void *)&sub_{address}) & 0xff) != 0) return 1;\n"
                "  if (read_exception_head() != saved_exception_head) return 2;\n"
            )
        main += "  return 0;\n}\n"
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in paths)
        self.assertEqual(build_and_run(fixture + bodies + main,
                                       "eh_cleanup_epilogues_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
