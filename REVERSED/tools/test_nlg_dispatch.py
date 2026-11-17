"""Exercise sub_5632D2's non-C EAX/EBP/stack contract on x86 MSVC."""

import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
VS_CANDIDATES = [
    Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
    Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community"),
]


class NlgDispatchTests(unittest.TestCase):
    def test_register_inputs_frame_value_and_stdcall_pop_are_preserved(self):
        vcvars = next((p / "VC/Auxiliary/Build/vcvars32.bat" for p in VS_CANDIDATES
                       if (p / "VC/Auxiliary/Build/vcvars32.bat").exists()), None)
        self.assertIsNotNone(vcvars, "32-bit MSVC environment is required")

        with tempfile.TemporaryDirectory() as temporary:
            temp = Path(temporary)
            source = temp / "nlg_dispatch_test.c"
            executable = temp / "abi57.exe"
            batch = temp / "build_test.bat"
            source.write_text(r'''#include "ghidra_shim.h"
#include <stdio.h>
int DAT_0057c774, DAT_0057c778, DAT_0057c77c;
extern int sub_5632D2(void);
typedef struct { unsigned int reserved[2]; unsigned int notification; } fake_frame;
__declspec(naked) static void invoke(fake_frame *frame, unsigned int callback)
{
    __asm {
        push ebp
        mov ebp, esp
        push esi
        mov esi, ebp
        mov eax, dword ptr [esi + 0ch]
        mov ebp, dword ptr [esi + 8]
        push 101h
        call sub_5632D2
        mov ebp, esi
        pop esi
        pop ebp
        ret
    }
}
int main(void) {
    fake_frame frame = {{0, 0}, 0x2468};
    invoke(&frame, 0x13579bdf);
    if (DAT_0057c774 != (int)0x13579bdf) { printf("eax=%08x\n", DAT_0057c774); return 1; }
    if (DAT_0057c778 != (int)0x2468) { printf("code=%08x\n", DAT_0057c778); return 2; }
    if (DAT_0057c77c != (int)(UINT_PTR)&frame) { printf("ebp=%08x expected=%08x\n", DAT_0057c77c, (unsigned int)(UINT_PTR)&frame); return 3; }
    return 0;
}
''', encoding="utf-8")
            batch.write_text(
                f'@echo off\ncall "{vcvars}" >nul\n'
                f'cl /nologo /TC /W0 /GS- /MT /I"{ROOT / "include"}" '
                f'/I"{ROOT / "src_generated"}" "{source}" '
                f'"{ROOT / "src_recovered" / "sub_5632D2.c"}" '
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
