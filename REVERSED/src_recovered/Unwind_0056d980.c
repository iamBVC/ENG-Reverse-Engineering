#include "ghidra_shim.h"

/* Original Ghidra disassembly at 0x0056D980. */
__declspec(naked) void Unwind_0056d980(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 10h]
        jmp sub_56D64F
    }
}
