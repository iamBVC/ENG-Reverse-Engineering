#include "ghidra_shim.h"

/* Original loc_56D780 cleanup for sub_412320: free the Block argument. */
__declspec(naked) void Unwind_0056d780(void)
{
    __asm {
        mov eax, dword ptr [ebp + 8]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
