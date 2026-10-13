"""Verify the recovered timer setter's eight-byte value and running-state behavior."""
from test_hardware_enumeration import ROOT, main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <stdlib.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static int samples;
static BOOL WINAPI mock_counter(LARGE_INTEGER *counter) { counter->QuadPart = 1000 + ++samples; return TRUE; }
#define QueryPerformanceCounter mock_counter
'''
MAIN = r'''
int main(void)
{
    struct { unsigned int before, timer[7], after; } object = {0x12345678, {0}, 0x87654321};
    sub_54B9F0(object.timer, 4294967300.0);
    REQUIRE(*(long long *)object.timer == 4294967300LL && samples == 0);
    object.timer[6] = 1;
    sub_54B9F0(object.timer, -17.5);
    REQUIRE(*(long long *)object.timer == -17 && samples == 2 && object.timer[6] == 1);
    REQUIRE(((LARGE_INTEGER *)(object.timer + 2))->QuadPart == 1002);
    REQUIRE(object.before == 0x12345678 && object.after == 0x87654321);
    puts("timer objects: double argument, 64-bit truncation, active restart and object bounds passed");
    return 0;
}
'''
if __name__ == '__main__':
    text = (ROOT / 'src_generated/clean_subset.c').read_text(encoding='utf-8')
    body = text.split('/* ==== sub_54B9F0 ==== */', 1)[1].split('/* ====', 1)[0]
    raise SystemExit(build_and_run(SOURCE + body + MAIN, 'timer_objects_test', bulk=False))
