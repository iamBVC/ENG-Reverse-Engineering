"""Smoke-test the real DirectDraw/DirectInput bridges with SDK interfaces."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent
SOURCE = r'''
#define DIRECTDRAW_VERSION 0x0700
#define DIRECTINPUT_VERSION 0x0700
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <stdio.h>
extern HRESULT groove_DirectDrawCreate(GUID *, void **, void *);
extern HRESULT groove_DirectDrawEnumerateA(LPDDENUMCALLBACKA, void *);
extern HRESULT groove_DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA, void *, DWORD);
extern HRESULT groove_DirectInputCreateA(HINSTANCE, DWORD, void **, void *);
static BOOL WINAPI callback(GUID *guid, LPSTR description, LPSTR name, LPVOID context)
{
    ++*(int *)context; return TRUE;
}
static BOOL WINAPI callback_ex(GUID *guid, LPSTR description, LPSTR name, LPVOID context, HMONITOR monitor)
{
    ++*(int *)context; return TRUE;
}
int main(void)
{
    LPDIRECTDRAW draw = NULL;
    LPDIRECTINPUTA input = NULL;
    HRESULT hr;
    int count = 0, count_ex = 0;
    hr = groove_DirectDrawCreate(NULL, (void **)&draw, NULL);
    if (FAILED(hr) || draw == NULL) { printf("DirectDrawCreate: %08lx\n", hr); return 1; }
    draw->lpVtbl->Release(draw);
    hr = groove_DirectDrawEnumerateA(callback, &count);
    if (FAILED(hr) || count == 0) { printf("DirectDrawEnumerateA: %08lx\n", hr); return 1; }
    hr = groove_DirectDrawEnumerateExA(callback_ex, &count_ex, 7);
    if (FAILED(hr) || count_ex == 0) { printf("DirectDrawEnumerateExA: %08lx\n", hr); return 1; }
    hr = groove_DirectInputCreateA(GetModuleHandleA(NULL), 0x700, (void **)&input, NULL);
    if (FAILED(hr) || input == NULL) { printf("DirectInputCreateA: %08lx\n", hr); return 1; }
    input->lpVtbl->Release(input);
    printf("legacy imports: interface creation/release and %d/%d callbacks passed\n", count, count_ex);
    return 0;
}
'''

def main():
    build = ROOT / "build/import_test"
    build.mkdir(parents=True, exist_ok=True)
    (build / "imports.c").write_text(SOURCE, encoding="utf-8")
    candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
                  Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
    vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
                  if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
    batch = build / "run.bat"
    batch.write_text(f'@echo off\ncall "{vcvars}" >nul\n'
                     f'cl /nologo /TC /W3 /MT imports.c "{ROOT / "harness/directdraw_imports.c"}" '
                     '/Fe:imports.exe /link ddraw.lib\n'
                     'if errorlevel 1 exit /b 1\nimports.exe\nexit /b %errorlevel%\n', encoding="ascii")
    return subprocess.run(["cmd", "/c", str(batch)], cwd=build).returncode

if __name__ == "__main__":
    raise SystemExit(main())
