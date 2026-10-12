"""Compile recovered callbacks against mocks and exercise their x86 ABI."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent
PREAMBLE = r'''
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
typedef unsigned int undefined4;
static unsigned int DAT_00586418;
static unsigned int *DAT_00582ccc, *DAT_00582ce4;
static int DAT_005846e4;
static unsigned int quit_object[32];
static unsigned int *PTR_DAT_00571f54 = quit_object;
static int shutdowns, activations, defaults, allow = 1, handled, capture_calls, files;
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static int sub_4065D0(unsigned char *handled_out, undefined4 *result, HWND window,
    unsigned int message, WPARAM wparam, LPRECT rect)
{
    *handled_out = (unsigned char)handled;
    *result = 42;
    return allow;
}
static void sub_41DF60(void) { ++shutdowns; }
static void sub_40F170(char inactive) { activations = inactive ? 1 : 2; }
static int sub_562717(char *buffer, const char *format, ...)
{
    int n; va_list args; va_start(args, format);
    n = vsprintf(buffer, format, args); va_end(args); return n;
}
static void *sub_562AEE(const char *path, const char *mode)
{
    REQUIRE(strcmp(mode, "r") == 0);
    return files++ < 2 ? (void *)1 : NULL;
}
static void sub_5628EB(void *stream) { REQUIRE(stream == (void *)1); }
static int sub_40CAB0(const char *path, void *a, void *b)
{
    REQUIRE(strcmp(path, "capture2.tga") == 0); ++capture_calls; return 1;
}
static void sub_414600(const char *format, ...) { REQUIRE(0); }
static LRESULT WINAPI mock_default(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    ++defaults; return 123;
}
#define DefWindowProcA mock_default
static BOOL __stdcall sub_4116D0(GUID *guid, LPSTR description, LPSTR name, LPVOID context, HMONITOR monitor)
{
    REQUIRE(context == (void *)7 && monitor == NULL); return 1;
}
'''
MAIN = r'''
int main(void)
{
    WNDPROC callback = sub_41DDA0;
    BOOL (WINAPI *adapter)(GUID *, LPSTR, LPSTR, LPVOID) = sub_4116B0;
    unsigned int left[5] = {0}, right[5] = {0};
    unsigned char a[32] = {0}, b[32] = {0};
    int i;
    for (i = 0; i < 10000; ++i) REQUIRE(callback(NULL, 0x81, 0, 0) == 123);
    REQUIRE(defaults == 10000);
    handled = 1; REQUIRE(callback(NULL, 0x81, 0, 0) == 42); handled = 0;
    allow = 0; REQUIRE(callback(NULL, 0x81, 0, 0) == 0 && shutdowns == 1); allow = 1;
    REQUIRE(callback(NULL, 0x104, 1, 0) == 0);
    REQUIRE(callback(NULL, 0x105, 0x73, 0) == 123);
    callback(NULL, 0x400, 0, 0); REQUIRE(activations == 1);
    callback(NULL, 0x400, 1, 0); REQUIRE(activations == 2);
    REQUIRE(callback(NULL, 0x111, 0x10002, 0) == 0);
    REQUIRE(shutdowns == 2 && DAT_005846e4 == 17 && *((unsigned char *)quit_object + 0x54) == 1);
    callback(NULL, 2, 0, 0); REQUIRE(shutdowns == 3);
    callback(NULL, 0x100, 0x75, 0); REQUIRE(capture_calls == 1 && DAT_00586418 == 3);
    for (i = 0; i < 10000; ++i) REQUIRE(adapter(NULL, NULL, NULL, (void *)7) == 1);
    a[0x10] = 1; REQUIRE(sub_413480(a, b) == -1 && sub_413480(b, a) == 1);
    b[0x10] = 1; a[0x11] = 1; REQUIRE(sub_413480(a, b) == 1);
    b[0x11] = 1; REQUIRE(sub_413480(a, b) == 0);
    left[3] = 640; right[3] = 320; REQUIRE(sub_4136A0(left, right) == 320);
    right[3] = 640; left[4] = 480; right[4] = 240;
    REQUIRE(sub_413790(left, right) == 240);
    puts("recovered callbacks: dispatch, capture, comparators and 20,000 ABI calls passed");
    return 0;
}
'''

def main():
    text = (ROOT / "src_generated/clean_subset.c").read_text(encoding="utf-8")
    names = ["sub_41DDA0", "sub_4116B0", "sub_413480", "sub_4136A0", "sub_413790"]
    bodies = [text.split(f"/* ==== {name} ==== */", 1)[1].split("/* ====", 1)[0]
              for name in names]
    build = ROOT / "build/callback_test"
    build.mkdir(parents=True, exist_ok=True)
    (build / "callbacks.c").write_text(PREAMBLE + "\n".join(bodies) + MAIN, encoding="utf-8")
    candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
                  Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
    vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
                  if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
    batch = build / "run.bat"
    batch.write_text(f'@echo off\ncall "{vcvars}" >nul\n'
                     'cl /nologo /TC /W3 /MT callbacks.c /Fe:callbacks.exe\n'
                     'if errorlevel 1 exit /b 1\ncallbacks.exe\nexit /b %errorlevel%\n', encoding="ascii")
    return subprocess.run(["cmd", "/c", str(batch)], cwd=build).returncode

if __name__ == "__main__":
    raise SystemExit(main())
