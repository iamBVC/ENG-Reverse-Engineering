#include "ghidra_shim.h"

/* Original WinMain cleanup at loc_56D8EB for four unwind states. */
__declspec(naked) void Unwind_0056d8eb(void)
{
    __asm {
        mov eax, dword ptr [ebp + 10h]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
