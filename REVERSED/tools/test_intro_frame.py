"""Exercise the real intro-frame caller without fullscreen or hardware access."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *draw_methods[10], *surface_methods[10];
static struct { void **methods; } draw = {draw_methods}, surface = {surface_methods};
int *DAT_00582ccc = (int *)&draw;
int *DAT_006d91b8;
static groove_surface_desc *created_descriptor;
static int released, created, uploaded, freed;
static int WINAPI release(UINT_PTR self)
{ REQUIRE(self == (UINT_PTR)&surface); ++released; return 0; }
static int WINAPI create_surface(UINT_PTR self, UINT_PTR descriptor, UINT_PTR output, UINT_PTR outer)
{
    groove_surface_desc *desc = (groove_surface_desc *)descriptor;
    REQUIRE(self == (UINT_PTR)&draw && outer == 0);
    REQUIRE(sizeof *desc == 124 && desc->dwSize == 124 && desc->dwFlags == 7);
    REQUIRE(desc->dwWidth == 640 && desc->dwHeight == 480 && desc->ddsCaps == 0x40);
    created_descriptor = desc;
    *(UINT_PTR *)output = (UINT_PTR)&surface;
    ++created; return 0;
}
void *sub_415690(int directory, const char *filename)
{ REQUIRE(directory == 0 && !strcmp(filename, "englogo.cor")); return (void *)filename; }
int sub_40D3B0(const char *path, void *buffer)
{ REQUIRE(!strcmp(path, "englogo.cor")); memset(buffer, 0x5a, 640*480*3); return 1; }
void sub_43B080(int *target, void *descriptor, const unsigned char *buffer, int a, int channels)
{
    REQUIRE(target == (int *)&surface);
    REQUIRE(descriptor == created_descriptor);
    REQUIRE(a == 0 && channels == 3 && buffer[0] == 0x5a && buffer[640*480*3-1] == 0x5a);
    /* A real Lock call writes the whole descriptor, not just one stack word. */
    memset(descriptor, 0, 124);
    ++uploaded;
}
void sub_5628BC(void *memory) { free(memory); ++freed; }
'''
MAIN = r'''
int main(void)
{
    unsigned int before, after;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    draw_methods[6] = create_surface;
    surface_methods[2] = release;
    __asm mov before, esp
    for (i = 0; i < 10; ++i)
        sub_43B790((unsigned int)"englogo.cor");
    __asm mov after, esp
    REQUIRE(before == after && created == 10 && uploaded == 10 && freed == 10 && released == 9);
    puts("intro frames: complete descriptor, decoded pixels, repeated surface replacement and balanced stack passed");
    return 0;
}
'''
if __name__ == '__main__':
    body = (ROOT / 'src_recovered/sub_43B790.c').read_text()
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'intro_frame_test', bulk=False))
