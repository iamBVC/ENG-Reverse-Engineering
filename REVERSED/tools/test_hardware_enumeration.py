"""Exercise generated hardware enumeration with deterministic COM callbacks.

Build the bulk DLL objects first. No physical GPU is required for this fixture.
"""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent
SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *draw_methods[9], *d3d_methods[11];
static struct { void **methods; } draw, d3d;
static unsigned int caps[63], draw_caps[95];
static groove_ddraw_enum_context parent;
static int depth_calls, mode_calls;

static int WINAPI enumerate_depth(UINT_PTR object, UINT_PTR guid, UINT_PTR callback, UINT_PTR opaque)
{
    unsigned int format[8] = {32, 0x400, 0, 16, 0, 0, 0, 0};
    groove_d3d_enum_context *context = (groove_d3d_enum_context *)opaque;
    int (WINAPI *visit)(unsigned int *, unsigned int *) = (void *)callback;
    REQUIRE(object == (UINT_PTR)&d3d && guid != 0);
    REQUIRE(context->parent == &parent && context->caps == (int)caps);
    REQUIRE(context->record != NULL && context->record[0xe] == 0);
    ++depth_calls;
    REQUIRE(visit(format, (unsigned int *)context) == 1);
    REQUIRE(context->record[0xe] == 32 && context->record[0x11] == 16);
    return 0;
}

static int WINAPI enumerate_modes(UINT_PTR object, UINT_PTR flags, UINT_PTR filter, UINT_PTR opaque, UINT_PTR callback)
{
    unsigned int surface[31] = {124, 0x1006, 480, 640};
    groove_d3d_enum_context *context = (groove_d3d_enum_context *)opaque;
    int (WINAPI *visit)(void *, int *) = (void *)callback;
    REQUIRE(object == (UINT_PTR)&draw && flags == 0 && filter == 0);
    REQUIRE(context->parent == &parent && context->caps == (int)caps);
    surface[0x4c / 4] = 0x40;
    surface[0x54 / 4] = 16;
    surface[0x58 / 4] = 0xf800;
    surface[0x5c / 4] = 0x7e0;
    surface[0x60 / 4] = 0x1f;
    ++mode_calls;
    /* Repeating a mode also verifies lookup/reuse rather than duplicate nodes. */
    REQUIRE(visit(surface, (int *)context) == 1);
    REQUIRE(visit(surface, (int *)context) == 1);
    return 0;
}

int main(void)
{
    unsigned int guid[4] = {1, 2, 3, 4};
    int *record, *format, *mode;
    draw_methods[8] = enumerate_modes;
    d3d_methods[10] = enumerate_depth;
    draw.methods = draw_methods; d3d.methods = d3d_methods;
    caps[0] = sizeof caps; caps[1] = 0x1ff; caps[2] = 2;
    caps[0x68 / 4] = 0x10;
    caps[0x70 / 4] = 8;
    caps[0x80 / 4] = 0x100;
    caps[0x9c / 4] = 0x400; caps[0xa0 / 4] = 0x400;
    caps[0xf4 / 4] = 3; caps[0xf8 / 4] = 8;
    draw_caps[0x9c / 4] = 0x400;
    parent.draw = (int *)&draw; parent.d3d = (int *)&d3d; parent.caps = draw_caps;
    parent.record = (int *)sub_4130B0(operator_new(40), "fixture adapter", NULL, 0);
    DAT_005834d4 = 0;
    REQUIRE(sub_411D60((int)guid, "fixture", "fixture HAL", caps, 0, (unsigned int *)&parent) == 1);
    REQUIRE(depth_calls == 1 && mode_calls == 1);
    record = (int *)parent.record[7];
    REQUIRE(record != parent.record + 8);
    REQUIRE(record[0xe] == 32 && record[0x11] == 16);
    format = (int *)record[0xb];
    REQUIRE(format != record + 0xc && format[3] == 16);
    REQUIRE((int *)*format == record + 0xc);
    mode = (int *)format[0xc];
    REQUIRE(mode != format + 0xd && mode[3] == 640 && mode[4] == 480);
    REQUIRE((int *)*mode == format + 0xd);
    /* The real interface setup is independent of HAL rendering capabilities. */
    REQUIRE(sub_410550((int)parent.record) == 1);
    REQUIRE(DAT_00582ccc != NULL && DAT_00582cd0 != NULL);
    sub_4106C0();
    REQUIRE(DAT_00582ccc == NULL && DAT_00582cd0 == NULL);
    puts("hardware enumeration: depth selection, mode creation/reuse and adapter insertion passed");
    return 0;
}
'''

def main(source_text=SOURCE, name="hardware_test"):
    build = ROOT / "build"
    source = build / f"{name}.c"
    source.write_text(source_text, encoding="utf-8")
    candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
                  Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
    vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
                  if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
    batch = build / f"{name}.bat"
    batch.write_text(f'@echo off\ncall "{vcvars}" >nul\n'
        f'cl /nologo /TC /W3 /MD /GS- /I"{ROOT / "include"}" /I"{ROOT / "src_generated"}" '
        f'{name}.c /Fe:{name}.exe /link chunk_*.obj ghidra_globals.obj '
        'link_stubs.obj crt_aliases.obj io_substitutes.obj directdraw_imports.obj '
        'Kernel32.lib User32.lib Gdi32.lib AdvAPI32.lib Ole32.lib OleAut32.lib '
        'WinMM.lib Shell32.lib ComCtl32.lib Version.lib ddraw.lib\n'
        f'if errorlevel 1 exit /b 1\n{name}.exe\nexit /b %errorlevel%\n', encoding="ascii")
    return subprocess.run(["cmd", "/c", str(batch)], cwd=build).returncode

if __name__ == "__main__":
    raise SystemExit(main())
