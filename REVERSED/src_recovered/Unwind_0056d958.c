#include "ghidra_shim.h"

/* Original Ghidra disassembly at 0x0056D958. */
__declspec(naked) void Unwind_0056d958(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 10h]
        jmp sub_56D64F
    }
}
