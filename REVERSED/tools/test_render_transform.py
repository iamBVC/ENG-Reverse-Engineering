"""Check the complete transform passed to the model renderer."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
uint DAT_0057d834;
float _DAT_0056e020 = 1.0f/4096.0f, _DAT_0056e018 = 1.0f/4096.0f;
static int called;
void sub_401820(int model, float *transform)
{
    REQUIRE(model == 123);
    REQUIRE(transform[0] == 0 && transform[1] == -0.125f && transform[2] == 0);
    REQUIRE(transform[3] == 1 && transform[4] == 2 && transform[5] == -3);
    ++called;
}
'''
MAIN = r'''
int main(void)
{
    int object[16] = {0}, camera[8] = {0};
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    object[10] = 123; object[11] = 512; object[12] = 512;
    camera[4] = 4096; camera[5] = 8192; camera[6] = 12288;
    sub_401780((int)object, (int)camera);
    REQUIRE(called == 1);
    object[10] = 0;
    sub_401780((int)object, (int)camera);
    REQUIRE(called == 1);
    puts("render transform: complete six-float block, angle, translation and absent model passed");
    return 0;
}
'''
if __name__ == '__main__':
    path = ROOT / 'src_recovered/sub_401780.c'
    body = path.read_text() if path.exists() else (ROOT / 'decompiled/sub_401780.c').read_text()
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'render_transform_test', bulk=False))
