#include "ghidra_shim.h"

/* The out_of_range constructor uses the caller's EBP-based EH3 frame. */
__declspec(naked) void sub_56D326(void)
{
    __asm {
        mov eax, offset sub_56D988
        call sub_56D674
        push ecx
        push esi
        mov esi, ecx
        mov dword ptr [ebp - 10h], esi
        mov dword ptr [esi], offset PTR_sub_56D1C5_0056ed68
        and dword ptr [ebp - 4], 0
        push 1
        lea ecx, dword ptr [esi + 0ch]
        call sub_413BF0
        or dword ptr [ebp - 4], 0ffffffffh
        mov ecx, esi
        call sub_56D64F
        mov ecx, dword ptr [ebp - 0ch]
        pop esi
        mov dword ptr fs:[0], ecx
        leave
        ret
    }
}
