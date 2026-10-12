"""Verify asset lookup priority and bounded path construction using Win32 mocks."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int DAT_00583748[65];
const char s_HDPath_00571d94[] = "HDPath", s_CDPath_00571d8c[] = "CDPath";
char groove_default_path[] = ".\\";
static const char *hd = "H:\\installed", *cd = "C:\\disc\\", *wanted;
static int visited, drive_checks;
static DWORD WINAPI module_path(HMODULE module, LPSTR output, DWORD size)
{
    REQUIRE(size == 260); strcpy(output, "E:\\game\\groove.exe"); return strlen(output);
}
static UINT WINAPI drive_type(LPCSTR path)
{
    ++drive_checks; return path[0] == 'Z' ? DRIVE_CDROM : DRIVE_FIXED;
}
static DWORD WINAPI attributes(LPCSTR path)
{
    ++visited; REQUIRE(strlen(path) < 260);
    return wanted != NULL && strcmp(path, wanted) == 0 ? FILE_ATTRIBUTE_NORMAL : INVALID_FILE_ATTRIBUTES;
}
undefined *sub_405790(const char *key, undefined *fallback)
{
    return (undefined *)(strcmp(key, "HDPath") == 0 ? hd : cd);
}
#define GetModuleFileNameA module_path
#define GetDriveTypeA drive_type
#define GetFileAttributesA attributes
'''

MAIN = r'''
int main(void)
{
    char oversized[300];
    wanted = "E:\\game\\WAD\\FESOUND.WAD";
    REQUIRE(sub_415690("WAD", "FESOUND.WAD") != NULL && visited == 1);
    wanted = "H:\\installed\\WAD\\FESOUND.WAD"; visited = 0;
    REQUIRE(sub_415690("WAD", "FESOUND.WAD") != NULL && visited == 2);
    wanted = "C:\\disc\\movie.dat"; visited = 0;
    REQUIRE(sub_415690(NULL, "movie.dat") != NULL && visited == 3);
    wanted = "Z:\\movies\\logo.dat"; visited = drive_checks = 0;
    REQUIRE(sub_415690("movies", "logo.dat") != NULL && visited == 4 && drive_checks == 26);
    wanted = NULL; REQUIRE(sub_415690(NULL, "missing.dat") == NULL);
    REQUIRE(sub_415690(NULL, NULL) == NULL);
    memset(oversized, 'x', 299); oversized[299] = 0;
    visited = 0; REQUIRE(sub_415690(NULL, oversized) == NULL && visited == 0);
    puts("file resolver: executable/HD/CD/drive priority, separators, missing files and path bounds passed");
    return 0;
}
'''

if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    body = text.split('/* ==== sub_415690 ==== */', 1)[1].split('/* ====', 1)[0]
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'file_resolver_test', bulk=False))
