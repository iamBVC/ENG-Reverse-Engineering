#include "ghidra_shim.h"

/* Original loc_56D760 cleanup for sub_411D60: free the block at EBP+0x14. */
__declspec(naked) void Unwind_0056d760(void)
{
    __asm {
        mov eax, dword ptr [ebp + 14h]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
