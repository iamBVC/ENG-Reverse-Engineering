#include "ghidra_shim.h"

/* Original loc_56D740 cleanup for Callback: free the block at EBP+0x10. */
__declspec(naked) void Unwind_0056d740(void)
{
    __asm {
        mov eax, dword ptr [ebp + 10h]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
