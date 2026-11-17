"""Behavioral checks for harness functions that replace original CRT helpers."""

from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
VS_CANDIDATES = [
    Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
    Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community"),
]


class IoSubstituteTests(unittest.TestCase):
    def test_free_wrapper_releases_owned_block_and_ftol_converts_st0(self):
        vcvars = next((p / "VC/Auxiliary/Build/vcvars32.bat" for p in VS_CANDIDATES
                       if (p / "VC/Auxiliary/Build/vcvars32.bat").exists()), None)
        self.assertIsNotNone(vcvars, "32-bit MSVC environment is required")

        source_text = f'''#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static uintptr_t freed_address;
static unsigned int free_calls;
static unsigned int recovered_free_calls;

static void *tracked_malloc(size_t size) {{ return malloc(size); }}
static void tracked_free(void *pointer)
{{
    if (pointer != NULL) {{
        freed_address = (uintptr_t)pointer;
        ++free_calls;
    }}
    free(pointer);
}}

void sub_5628BC(void *pointer)
{{
    ++recovered_free_calls;
    tracked_free(pointer);
}}

#define malloc tracked_malloc
#define free tracked_free
#include "{(ROOT / 'harness' / 'io_substitutes.c').as_posix()}"
#undef malloc
#undef free

static int convert_st0(double value)
{{
    int converted;
    __asm {{
        fld qword ptr [value]
        call groove_ftol
        mov dword ptr [converted], eax
    }}
    return converted;
}}

static unsigned short read_control_word(void)
{{
    unsigned short value;
    __asm {{ fnstcw word ptr [value] }}
    return value;
}}

static void write_control_word(unsigned short value)
{{
    __asm {{ fldcw word ptr [value] }}
}}

int main(void)
{{
    unsigned short original = read_control_word();
    unsigned short nearest = (unsigned short)(original & ~0x0c00u);
    uintptr_t block_address;
    void *block;
    int failures = 0;
    write_control_word(nearest);

    if (convert_st0(1.75) != 2 || convert_st0(2.5) != 2 ||
        convert_st0(-2.75) != -3) {{
        fprintf(stderr, "ftol failed: positive, ties-to-even, or negative conversion\\n");
        failures |= 1;
    }}

    block = operator_new(32);
    if (block == NULL) {{
        fprintf(stderr, "operator_new failed\\n");
        write_control_word(original);
        return 2;
    }}
    block_address = (uintptr_t)block;
    sub_562941(block);
    if (free_calls != 1 || freed_address != block_address) {{
        fprintf(stderr, "sub_562941 did not release its argument\\n");
        failures |= 2;
    }}
    if (recovered_free_calls != 1) {{
        fprintf(stderr, "sub_562941 bypassed the recovered free wrapper\\n");
        failures |= 8;
    }}
    sub_562941(NULL);
    if (free_calls != 1 || recovered_free_calls != 2) {{
        fprintf(stderr, "sub_562941 changed null-free behavior\\n");
        failures |= 4;
    }}

    write_control_word(original);
    return failures;
}}
'''

        with tempfile.TemporaryDirectory() as temporary:
            temp = Path(temporary)
            source = temp / "io_substitutes_test.c"
            executable = temp / "io_substitutes_test.exe"
            batch = temp / "build_test.bat"
            source.write_text(source_text, encoding="utf-8")
            batch.write_text(
                f'@echo off\ncall "{vcvars}" >nul\n'
                f'cl /nologo /TC /W0 /GS- /MT /I"{ROOT / "include"}" '
                f'"{source}" /Fe:"{executable}"\n'
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
