"""Check the actual intro-call argument without dereferencing an invalid address."""
from test_hardware_enumeration import main as build_and_run

SOURCE = r'''
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include <string.h>
int main(void)
{
    UINT_PTR argument = (UINT_PTR)(s__englogo_cor_005724e3 + 1);
    char filename[12];
    SIZE_T copied = 0;
    if (!ReadProcessMemory(GetCurrentProcess(), (void *)argument,
                           filename, sizeof filename, &copied)) {
        fprintf(stderr, "intro filename argument is unreadable: %p\n", (void *)argument);
        return 1;
    }
    if (copied != sizeof filename || memcmp(filename, "englogo.cor", sizeof filename)) {
        fprintf(stderr, "intro filename argument does not contain englogo.cor\n");
        return 1;
    }
    puts("intro filename: the real call argument points to englogo.cor with its terminator");
    return 0;
}
'''
if __name__ == '__main__':
    raise SystemExit(build_and_run(SOURCE, 'intro_filename_test'))
