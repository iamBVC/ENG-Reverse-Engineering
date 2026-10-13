"""Verify the recovered video factory's COM arguments and reference ownership."""
import re
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <wchar.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *methods[17];
static struct { void **methods; } stream = {methods};
static int references, initialized, video, audio, opened, fail_create, fail_init, fail_open;
static HRESULT WINAPI create(REFCLSID clsid, LPUNKNOWN outer, DWORD flags, REFIID iid, void **output)
{
    REQUIRE(clsid == (GUID *)DAT_0056e5ec && iid == (GUID *)DAT_0056e5fc && outer == NULL && flags == 1);
    *output = fail_create ? NULL : &stream; references = fail_create ? 0 : 1;
    return fail_create ? E_FAIL : S_OK;
}
static int WINAPI addref(UINT_PTR self) { REQUIRE(self == (UINT_PTR)&stream); return ++references; }
static int WINAPI release(UINT_PTR self) { REQUIRE(self == (UINT_PTR)&stream); return --references; }
static HRESULT WINAPI initialize(UINT_PTR self, UINT_PTR type, UINT_PTR flags, UINT_PTR graph)
{ REQUIRE(self == (UINT_PTR)&stream && type == 0 && flags == 1 && graph == 0); ++initialized; return fail_init ? E_FAIL : S_OK; }
static HRESULT WINAPI add_media(UINT_PTR self, UINT_PTR object, UINT_PTR purpose, UINT_PTR flags, UINT_PTR output)
{
    REQUIRE(self == (UINT_PTR)&stream && output == 0);
    if (purpose == (UINT_PTR)DAT_0056e5cc) { REQUIRE(object == 0x1234 && flags == 0); ++video; }
    else { REQUIRE(purpose == (UINT_PTR)DAT_0056e5bc && object == 0 && flags == 1); ++audio; }
    return S_OK;
}
static HRESULT WINAPI open_file(UINT_PTR self, UINT_PTR filename, UINT_PTR flags)
{
    REQUIRE(self == (UINT_PTR)&stream && flags == 0);
    REQUIRE(wcscmp((WCHAR *)filename, L"C:\\game\\intro.dat") == 0); ++opened;
    return fail_open ? E_FAIL : S_OK;
}
#define CoCreateInstance create
'''
MAIN = r'''
int main(void)
{
    struct { unsigned int pointer, sentinel; } output = {0, 0x12345678};
    unsigned int before, after;
    int i;
    methods[1] = addref; methods[2] = release; methods[12] = initialize;
    methods[15] = add_media; methods[16] = open_file;
    for (i = 0; i < 10; ++i) {
        __asm mov before, esp
        REQUIRE(sub_41EF70((int)"C:\\game\\intro.dat", 0x1234, &output.pointer) == S_OK);
        __asm mov after, esp
        REQUIRE(before == after && output.pointer == (unsigned int)&stream && references == 1);
        REQUIRE(DAT_005865e0 == NULL && output.sentinel == 0x12345678);
        release((UINT_PTR)&stream);
    }
    REQUIRE(initialized == 10 && video == 10 && audio == 10 && opened == 10);
    fail_open = 1;
    REQUIRE(sub_41EF70((int)"C:\\game\\intro.dat", 0x1234, &output.pointer) == E_FAIL);
    REQUIRE(output.pointer == 0 && references == 0);
    fail_init = 1;
    REQUIRE(sub_41EF70((int)"C:\\game\\intro.dat", 0x1234, &output.pointer) == E_FAIL && references == 0);
    fail_create = 1;
    REQUIRE(sub_41EF70((int)"C:\\game\\intro.dat", 0x1234, &output.pointer) == E_FAIL && output.pointer == 0);
    puts("video setup: original COM arguments, wide path, reference ownership, failure cleanup and stack balance passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    body = text.split('/* ==== sub_41EF70 ==== */', 1)[1].split('/* ====', 1)[0]
    symbols = set(re.findall(r'\bDAT_[A-Za-z0-9_]+\b', body))
    definitions = (ROOT / 'src_generated/ghidra_globals.c').read_text(encoding='utf-8').splitlines()
    selected = [line for line in definitions if any(re.search(r'\b' + s + r'\b', line) for s in symbols)]
    raise SystemExit(build_and_run(SOURCE + '\n'.join(selected) + body + MAIN,
                                  'video_com_test', bulk=False))
