#include "ghidra_shim.h"

/* Original Ghidra disassembly at 0x0056D930: this is the EBP-10h exception. */
__declspec(naked) void Unwind_0056d930(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 10h]
        jmp sub_56D64F
    }
}
