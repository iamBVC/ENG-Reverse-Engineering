#include "ghidra_shim.h"

/* Original cleanup at loc_56D91C. The frame's temporary exception is at EBP-14h. */
__declspec(naked) void Unwind_0056d91c(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 14h]
        jmp sub_56D64F
    }
}
