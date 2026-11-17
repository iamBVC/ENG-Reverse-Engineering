#include "ghidra_shim.h"

/* Exact in-frame helper at 0x005683B9. It must retain the caller's EBP. */
__declspec(naked) void sub_5683B9(void)
{
    __asm {
        mov byte ptr [ebp - 90h], 1
        or cl, cl
        ret
    }
}
