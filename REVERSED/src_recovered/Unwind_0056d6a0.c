#include "ghidra_shim.h"

/* Exact owner-frame cleanup from Game/groove.exe.asm at loc_56D6A0.
 * The exception runtime enters this funclet with the protected function's EBP. */
__declspec(naked) void Unwind_0056d6a0(void)
{
    __asm {
        mov eax, dword ptr [ebp - 10h]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
