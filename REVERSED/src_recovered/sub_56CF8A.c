#include "ghidra_shim.h"

/* Exact x87 status read at 0x0056CF8A, including the pending-exception wait. */
__declspec(naked) int sub_56CF8A(void)
{
    __asm {
        push ebp
        mov ebp, esp
        push ecx
        wait
        fnstsw word ptr [ebp - 2]
        movsx eax, word ptr [ebp - 2]
        leave
        ret
    }
}
