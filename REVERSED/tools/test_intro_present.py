"""Exercise the real intro presentation path against native COM callbacks."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void *source_methods[40], *target_methods[40];
static struct { void **methods; } source = {source_methods}, target = {target_methods};
static int locks, unlocks, copies, polls, released;
static int WINAPI page_lock(UINT_PTR self, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&source && !flags); ++locks; return 0; }
static int WINAPI page_unlock(UINT_PTR self, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&source && !flags); ++unlocks; return 0; }
static int WINAPI blit(UINT_PTR self, UINT_PTR dest, UINT_PTR image, UINT_PTR rect, UINT_PTR flags, UINT_PTR fx)
{ REQUIRE(self == (UINT_PTR)&target && !dest && image == (UINT_PTR)&source && !rect && flags == 0x1000000 && !fx); ++copies; return 0; }
static int WINAPI status(UINT_PTR self, UINT_PTR flags)
{ REQUIRE(self == (UINT_PTR)&target && flags == 2); return (++polls % 2) ? 0x8876021c : 0; }
static int WINAPI release(UINT_PTR self)
{ REQUIRE(self == (UINT_PTR)&source); ++released; return 0; }
int main(void)
{
    unsigned int before, after;
    int i;
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    source_methods[2] = release; source_methods[37] = page_lock; source_methods[38] = page_unlock;
    target_methods[5] = blit; target_methods[13] = status;
    DAT_00582ce4 = (int *)&target;
    __asm mov before, esp
    for (i = 0; i < 100; ++i) {
        DAT_006d91b8 = (int *)&source;
        REQUIRE(sub_43B8A0() == 1);
        sub_43C940();
        REQUIRE(DAT_006d91b8 == NULL);
        sub_43C940();
        REQUIRE(sub_43B8A0() == 0);
    }
    __asm mov after, esp
    REQUIRE(before == after && locks == 100 && unlocks == 100 && copies == 100 && polls == 200 && released == 100);
    puts("intro presentation: blit completion, release, empty frame and native stack balance passed for 100 cycles");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'intro_present_test'))
