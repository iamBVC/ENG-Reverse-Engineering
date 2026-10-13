"""Exercise frame-file header reads without graphics or fullscreen access."""
from test_hardware_enumeration import ROOT, main as build_and_run
import sys

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
char DAT_00570350[] = "rb";
static FILE *opened;
static int closed, reads;
void *sub_562AEE(const char *path, const char *mode)
{ REQUIRE(opened == NULL); opened = fopen(path, mode); return opened; }
size_t sub_5629E6(void *buffer, size_t size, size_t count, void *stream)
{ REQUIRE(stream == opened); ++reads; return fread(buffer, size, count, (FILE *)stream); }
int sub_5628EB(void *stream)
{ REQUIRE(stream == opened); ++closed; opened = NULL; return fclose((FILE *)stream); }
void *_malloc(size_t size) { return malloc(size); }
void sub_5628BC(void *buffer) { free(buffer); }
'''
MAIN = r'''
int main(void)
{
    unsigned int header[5] = {0, 0x12d142fe, 0x77777777, 3, 4};
    unsigned char output[8] = {0}, packed[] = {3, 0x12, 0x34, 0x56};
    FILE *file;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    file = fopen("frame_file_raw.dat", "wb"); REQUIRE(file);
    REQUIRE(fwrite(header, sizeof header, 1, file) == 1); fclose(file);
    REQUIRE(sub_40D3B0((UINT_PTR)"frame_file_raw.dat", (UINT_PTR)output) == 0);
    REQUIRE(closed == 1 && reads == 1 && !opened);
    header[0] = 0x89af9817;
    file = fopen("frame_file_packed.dat", "wb"); REQUIRE(file);
    REQUIRE(fwrite(header, sizeof header, 1, file) == 1);
    REQUIRE(fwrite(packed, sizeof packed, 1, file) == 1); fclose(file);
    REQUIRE(sub_40D3B0((UINT_PTR)"frame_file_packed.dat", (UINT_PTR)output) == 3);
    REQUIRE(!memcmp(output, packed+1, 3) && output[3] == 0);
    /* The original successful decoder leaves its stream open. */
    REQUIRE(opened != NULL && reads == 3); sub_5628EB(opened);
    remove("frame_file_raw.dat"); remove("frame_file_packed.dat");
    puts("frame files: intact stream after 20-byte header, raw fallback and packed payload read passed");
    return 0;
}
'''
if __name__ == '__main__':
    path = ROOT / 'src_recovered/sub_40D3B0.c'
    if '--original-header' in sys.argv:
        # Supply the separately missing fread argument to isolate header storage.
        body = (ROOT / 'decompiled/sub_40D3B0.c').read_text().replace(
            'sub_5629E6(pvVar2,local_4,1);', 'sub_5629E6(pvVar2,local_4,1,iVar1);')
    else:
        body = path.read_text() if path.exists() else (ROOT / 'decompiled/sub_40D3B0.c').read_text()
    decoder = (ROOT / 'decompiled/sub_40D300.c').read_text()
    raise SystemExit(build_and_run(SOURCE + decoder + body + MAIN, 'frame_file_test', bulk=False))
