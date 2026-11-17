#include "ghidra_shim.h"

/* Second original loc_56D78B cleanup path for the same Block argument. */
__declspec(naked) void Unwind_0056d78b(void)
{
    __asm {
        mov eax, dword ptr [ebp + 8]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
