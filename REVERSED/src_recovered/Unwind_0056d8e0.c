#include "ghidra_shim.h"

/* Original WinMain SEH cleanup at loc_56D8E0: delete lpCmdLine. */
__declspec(naked) void Unwind_0056d8e0(void)
{
    __asm {
        mov eax, dword ptr [ebp + 10h]
        push eax
        call sub_562941
        pop ecx
        ret
    }
}
