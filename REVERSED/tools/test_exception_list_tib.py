"""Prove the decompiler's ExceptionList lvalue is the actual x86 FS:[0] slot."""

import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
VS_CANDIDATES = [
    Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
    Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community"),
]


class ExceptionListTibTests(unittest.TestCase):
    def test_lvalue_reads_and_writes_the_current_thread_fs_chain_head(self):
        vcvars = next((p / "VC/Auxiliary/Build/vcvars32.bat" for p in VS_CANDIDATES
                       if (p / "VC/Auxiliary/Build/vcvars32.bat").exists()), None)
        self.assertIsNotNone(vcvars, "32-bit MSVC environment is required")

        with tempfile.TemporaryDirectory() as temporary:
            temp = Path(temporary)
            source = temp / "seh_tib_test.c"
            executable = temp / "seh_tib_test.exe"
            batch = temp / "build_test.bat"
            source.write_text(r'''#include "ghidra_shim.h"
int main(void) {
    void *saved = ExceptionList;
    void *fs_value;
    __asm {
        mov eax, dword ptr fs:[0]
        mov fs_value, eax
    }
    if (saved != fs_value) return 1;
    ExceptionList = (void *)(UINT_PTR)0x12345678;
    __asm {
        mov eax, dword ptr fs:[0]
        mov fs_value, eax
    }
    ExceptionList = saved;
    return fs_value == (void *)(UINT_PTR)0x12345678 ? 0 : 2;
}
''', encoding="utf-8")
            batch.write_text(
                f'@echo off\ncall "{vcvars}" >nul\n'
                f'cl /nologo /TC /W4 /MT /I"{ROOT / "include"}" '
                f'"{source}" /Fe:"{executable}" /Fo:"{temp / "seh_tib_test.obj"}"\n'
                'exit /b %errorlevel%\n',
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
