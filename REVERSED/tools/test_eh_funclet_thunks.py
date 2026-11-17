"""Verify original x86 MSVC unwind thunks preserve their metadata in EAX."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


METADATA = {
    "56D6B3": "0056EF40", "56D6C8": "0056F010", "56D6E8": "0056F070",
    "56D716": "0056F0D0", "56D72B": "0056F178", "56D756": "0056F1D8",
    "56D773": "0056F240", "56D79E": "0056F2A8", "56D7C3": "0056F318",
    "56D7E3": "0056F348", "56D803": "0056F378", "56D823": "0056F3A8",
    "56D843": "0056F3D8", "56D850": "0056F408", "56D878": "0056F460",
    "56D898": "0056F498", "56D8C8": "0056F4C0", "56D8FE": "0056F4F8",
}


class EhFuncletThunkTests(unittest.TestCase):
    def test_every_unwind_thunk_loads_its_own_metadata_and_tail_jumps(self):
        sources = [ROOT / "src_recovered" / f"sub_{address}.c" for address in METADATA]
        for path in sources:
            self.assertTrue(path.exists(), f"missing recovered thunk {path.name}")

        fixture = r'''
#include <stdint.h>
int DAT_0056EF40, DAT_0056F010, DAT_0056F070, DAT_0056F0D0;
int DAT_0056F178, DAT_0056F1D8, DAT_0056F240, DAT_0056F2A8;
int DAT_0056F318, DAT_0056F348, DAT_0056F378, DAT_0056F3A8;
int DAT_0056F3D8, DAT_0056F408, DAT_0056F460, DAT_0056F498;
int DAT_0056F4C0, DAT_0056F4F8;
static int observed_eax;
__declspec(naked) int __cdecl sub_562FA9(int a, int b, int c, int d)
{
    __asm {
        mov observed_eax, eax
        mov eax, 0x24681357
        ret
    }
}
'''
        main = "int main(void) {\n"
        for address, data in METADATA.items():
            main += (
                f"  observed_eax = 0; if (sub_{address}(1,2,3,4) != 0x24681357) return 1;\n"
                f"  if ((unsigned)observed_eax != (unsigned)(uintptr_t)&DAT_{data}) return 2;\n"
            )
        main += "  return 0;\n}\n"
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in sources)
        self.assertEqual(build_and_run(fixture + bodies + main,
                                       "eh_funclet_thunks_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
