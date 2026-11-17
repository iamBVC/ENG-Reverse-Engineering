#include "ghidra_shim.h"

/* Exact x87 status read and clear at 0x0056CF98. The status is captured
 * before FNCLEX clears the pending exception flags, as in the original. */
__declspec(naked) int sub_56CF98(void)
{
    __asm {
        push ebp
        mov ebp, esp
        push ecx
        fnstsw word ptr [ebp - 2]
        fnclex
        movsx eax, word ptr [ebp - 2]
        leave
        ret
    }
}
