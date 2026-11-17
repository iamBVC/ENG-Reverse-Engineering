"""Exercise x87 helpers whose Ghidra C bodies lost stack/control-word effects."""

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402
VS_CANDIDATES = [
    Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
    Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community"),
]


class X87RecoveredHelperTests(unittest.TestCase):
    def test_sub_56b361_preserves_entry_eax_and_consumes_two_x87_values(self):
        source_path = ROOT / "src_recovered" / "sub_56B361.c"
        self.assertTrue(source_path.exists(), "missing recovered body for 0x0056B361")
        prototypes = (ROOT / "src_generated" / "ghidra_prototypes.h").read_text(encoding="utf-8")
        self.assertIn("undefined4 sub_56B361();", prototypes)
        self.assertNotIn("__declspec(naked) sub_56B361", prototypes)
        fixture = r'''#include "ghidra_shim.h"
void sub_56AB70(void);
__declspec(naked) void sub_56AB70(void) {
    __asm {
        mov eax, 0xdeadbeef
        ret
    }
}
'''
        main = r'''
int main(void) {
    unsigned int observed_eax = 0;
    unsigned short before_status = 0;
    unsigned short status = 0;
    __asm {
        fnstsw word ptr [before_status]
        fldpi
        fld1
        mov eax, 0x12345678
        call sub_56B361
        mov observed_eax, eax
        fnstsw word ptr [status]
    }
    if (observed_eax != 0x12345678u) return 1;
    if ((status & 0x3800u) != (before_status & 0x3800u)) return 2;
    return 0;
}
'''
        body = source_path.read_text(encoding="utf-8")
        self.assertEqual(build_and_run(fixture + body + main,
                                       "x87_eax_preservation_test", bulk=False), 0)

    def test_x87_stack_transformations_and_precision_control_match_machine_contract(self):
        vcvars = next((p / "VC/Auxiliary/Build/vcvars32.bat" for p in VS_CANDIDATES
                       if (p / "VC/Auxiliary/Build/vcvars32.bat").exists()), None)
        self.assertIsNotNone(vcvars, "32-bit MSVC environment is required")

        with tempfile.TemporaryDirectory() as temporary:
            temp = Path(temporary)
            source = temp / "x87_helper_test.c"
            executable = temp / "x87_helpers.exe"
            batch = temp / "build_test.bat"
            source.write_text(r'''#include <math.h>
#include <stdio.h>
extern int sub_5682F8(void);
extern int sub_568306(void);
extern int sub_568445(void);
extern int sub_5684CE(void);
extern int sub_56CFCA(unsigned int flags);

static float run_swap_and_pop(void) {
    float result;
    __asm {
        fld1
        fldpi
        call sub_5682F8
        fstp dword ptr [result]
    }
    return result;
}
static void run_pop_and_zero(float *result, float *preserved) {
    __asm {
        fld1
        fldpi
        call sub_568306
        mov eax, result
        fstp dword ptr [eax]
        mov eax, preserved
        fstp dword ptr [eax]
    }
}
static unsigned short read_cw(void) {
    unsigned short value;
    __asm { fnstcw word ptr [value] }
    return value;
}
static void set_cw(unsigned short value) { __asm { fldcw word ptr [value] } }
static unsigned short run_prepare_cw(unsigned int source) {
    unsigned short observed;
    __asm {
        push dword ptr [source]
        call sub_568445
        add esp, 4
        fnstcw word ptr [observed]
    }
    return observed;
}
static unsigned int run_restore_cw(unsigned int marker) {
    unsigned int result;
    __asm {
        mov eax, dword ptr [marker]
        call sub_5684CE
        mov dword ptr [result], eax
    }
    return result;
}

int main(void) {
    const unsigned short original = read_cw();
    float first = run_swap_and_pop();
    if (fabsf(first - 3.14159265f) > 0.0001f) {
        printf("swap_pop=%f expected=pi\n", first);
        return 1;
    }
    float result = -1.0f, preserved = -1.0f;
    run_pop_and_zero(&result, &preserved);
    if (result != 0.0f || fabsf(preserved - 1.0f) > 0.0001f) {
        printf("zero_result=%f preserved=%f\n", result, preserved);
        return 2;
    }
    set_cw(0x0b7fu);
    const unsigned int source = 0x00000300u;
    const unsigned short actual = run_prepare_cw(source);
    const unsigned short expected = 0x037fu;
    if (actual != expected) {
        set_cw(original);
        printf("prepared_cw=%04x expected=%04x\n", actual, expected);
        return 3;
    }
    const unsigned int marker = 0x5a17c0deu;
    const unsigned int preserved_eax = run_restore_cw(marker);
    const unsigned short restored = read_cw();
    set_cw(original);
    if (restored != 0x0b7fu || preserved_eax != marker) {
        printf("restored_cw=%04x eax=%08x expected_cw=0b7f eax=%08x\n",
               restored, preserved_eax, marker);
        return 3;
    }
    __asm { fnclex }
    sub_56CFCA(4);
    unsigned short status;
    __asm { fnstsw word ptr [status] }
    if ((status & 0x0004u) == 0) {
        printf("divide_by_zero_status=%04x expected bit 2\n", status);
        return 4;
    }
    return 0;
}
''', encoding="utf-8")
            batch.write_text(
                f'@echo off\ncall "{vcvars}" >nul\n'
                f'cl /nologo /TC /W0 /GS- /MT "{source}" '
                f'"{ROOT / "src_recovered" / "sub_5682F8.c"}" '
                f'"{ROOT / "src_recovered" / "sub_568306.c"}" '
                f'"{ROOT / "src_recovered" / "sub_568445.c"}" '
                f'"{ROOT / "src_recovered" / "sub_5684CE.c"}" '
                f'"{ROOT / "src_recovered" / "sub_56CFCA.c"}" '
                f'/Fe:"{executable}"\nexit /b %errorlevel%\n',
                encoding="utf-8",
            )
            build = subprocess.run(["cmd", "/c", str(batch)], cwd=temp,
                                   capture_output=True, text=True)
            self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
            run = subprocess.run([str(executable)], cwd=temp, capture_output=True,
                                 text=True)
            self.assertEqual(run.returncode, 0, run.stdout + run.stderr)


if __name__ == "__main__":
    unittest.main()
