"""Compile the generated registry helper against mocks; never touch the registry.

Run make_bulk.py first, then python tools/test_registry_handles.py.
"""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent

HARNESS = r'''
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
typedef unsigned int uint;
typedef unsigned int undefined4;
typedef unsigned char byte;
static int step, opens, creates, closes, formats, fail_open, fail_create;
static HKEY root;
static char s_HKEY_LOCAL_MACHINE_00570320[] = "HKEY_LOCAL_MACHINE";
static char s_HKEY_CURRENT_USER_0057030c[] = "HKEY_CURRENT_USER";
static char DAT_0057f834;
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static HKEY handle(int index) { return (HKEY)(UINT_PTR)(0x1000 + index); }
static LSTATUS WINAPI mock_open(HKEY key, LPCSTR name, DWORD options, REGSAM access, PHKEY result)
{
    static const char *parts[] = { "Software", "Disney", "Groove" };
    REQUIRE(step < 3);
    REQUIRE(key == (step == 0 ? root : handle(step)));
    REQUIRE(strcmp(name, parts[step]) == 0);
    REQUIRE(options == 0 && access == KEY_READ);
    ++opens;
    if (fail_open) return ERROR_FILE_NOT_FOUND;
    *result = handle(++step);
    return ERROR_SUCCESS;
}
static LSTATUS WINAPI mock_create(HKEY key, LPCSTR name, DWORD reserved, LPSTR cls,
    DWORD options, REGSAM access, LPSECURITY_ATTRIBUTES security, PHKEY result, LPDWORD disposition)
{
    REQUIRE(key == (step == 0 ? root : handle(step)));
    REQUIRE(reserved == 0 && options == 0 && access == KEY_READ && security == NULL);
    REQUIRE(cls != NULL && *cls == 0 && name != NULL);
    ++creates;
    if (fail_create) return ERROR_ACCESS_DENIED;
    *disposition = REG_CREATED_NEW_KEY;
    *result = handle(++step);
    return ERROR_SUCCESS;
}
static LSTATUS WINAPI mock_close(HKEY key)
{
    REQUIRE(key != root && key == handle(closes + 1));
    ++closes;
    return ERROR_SUCCESS;
}
#define RegOpenKeyExA mock_open
#define RegCreateKeyExA mock_create
#define RegCloseKey mock_close
static void sub_562840(void) { }
static char *sub_56279D(byte *text, byte *delimiter) { return strtok((char *)text, (char *)delimiter); }
static int sub_562717(char *buffer, const char *format, ...)
{
    int result;
    va_list args;
    REQUIRE(strcmp(format, "[08x%x]") == 0);
    ++formats;
    va_start(args, format);
    result = vsprintf(buffer, format, args);
    va_end(args);
    return result;
}
'''

MAIN = r'''
static void run_case(HKEY key, int missing, int denied, const char *path)
{
    unsigned int result;
    step = opens = creates = closes = formats = 0;
    root = key; fail_open = missing; fail_create = denied;
    result = sub_405960(key, (char *)path, KEY_READ);
    if (*path == 0) {
        REQUIRE(result == (unsigned int)(UINT_PTR)key && opens == 0 && closes == 0);
    } else if (denied) {
        REQUIRE(result == 0 && opens == 1 && creates == 1 && closes == 0);
    } else {
        REQUIRE(result == (unsigned int)(UINT_PTR)handle(3));
        REQUIRE(opens == 3 && closes == 2 && creates == (missing ? 3 : 0));
    }
    REQUIRE(formats == ((missing && key != HKEY_LOCAL_MACHINE && key != HKEY_CURRENT_USER) ? creates : 0));
}
int main(void)
{
    run_case(HKEY_CURRENT_USER, 0, 0, "Software\\Disney\\Groove");
    run_case(HKEY_CURRENT_USER, 1, 0, "Software\\Disney\\Groove");
    run_case(HKEY_LOCAL_MACHINE, 1, 0, "Software\\Disney\\Groove");
    run_case(handle(99), 1, 0, "Software\\Disney\\Groove");
    run_case(handle(99), 1, 1, "Software\\Disney\\Groove");
    run_case(HKEY_CURRENT_USER, 0, 0, "");
    puts("registry helper: 6 cases passed (mocked Win32 calls)");
    return 0;
}
'''

def main():
    text = (ROOT / "src_generated/clean_subset.c").read_text(encoding="utf-8")
    body = text.split("/* ==== sub_405960 ==== */", 1)[1].split("/* ====", 1)[0]
    build = ROOT / "build/registry_test"
    build.mkdir(parents=True, exist_ok=True)
    source = build / "registry_test.c"
    source.write_text(HARNESS + body + MAIN, encoding="utf-8")
    candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
                  Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
    vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
                  if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
    batch = build / "run.bat"
    batch.write_text(f'@echo off\ncall "{vcvars}" >nul\n'
                     'cl /nologo /TC /W3 /MT registry_test.c /Fe:registry_test.exe\n'
                     'if errorlevel 1 exit /b 1\nregistry_test.exe\nexit /b %errorlevel%\n',
                     encoding="ascii")
    return subprocess.run(["cmd", "/c", str(batch)], cwd=build).returncode

if __name__ == "__main__":
    raise SystemExit(main())
