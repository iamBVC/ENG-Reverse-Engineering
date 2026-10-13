"""Exercise real 64-bit helpers and the generated frame limiter against Win32 time."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    DWORD start = timeGetTime();
    int i, previous;
    REQUIRE(groove_multiply_parts(5, 1, 3, 0) == 12884901903ULL);
    REQUIRE(groove_divide_parts(12884901903ULL, 3, 0) == 4294967301LL);
    REQUIRE(groove_divide_parts((uint64_t)-125LL, 10, 0) == -12);
    DAT_00586408 = DAT_0058640c = DAT_005863c8 = 0;
    for (i = 0; i < 3; ++i) {
        previous = DAT_00584650;
        sub_41CEE0(30);
        REQUIRE(DAT_005724d4 > 0 && DAT_005724d4 <= 30);
        REQUIRE(DAT_00584650 == previous + DAT_005724d4 * 2);
    }
    REQUIRE(timeGetTime() - start >= 30 && timeGetTime() - start < 2000);
    puts("frame timing: wide arithmetic, signed division and three advancing 30-FPS frames passed");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'frame_timing_test'))
