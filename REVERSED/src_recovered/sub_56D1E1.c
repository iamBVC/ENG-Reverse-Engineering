#include "ghidra_shim.h"

/* ECX is the destination object; [EBP+8] is the source and RET 4 is required. */
__declspec(naked) undefined4 * sub_56D1E1(void)
{
    __asm {
        mov eax, offset sub_56D94C
        call sub_56D674
        push ecx
        push ebx
        mov ebx, dword ptr [ebp + 8]
        push esi
        push edi
        mov esi, ecx
        push ebx
        mov dword ptr [ebp - 10h], esi
        call sub_56D605
        mov al, byte ptr [ebx + 0ch]
        and dword ptr [ebp - 4], 0
        add ebx, 0ch
        lea edi, dword ptr [esi + 0ch]
        push 0
        mov ecx, edi
        mov byte ptr [edi], al
        call sub_413BF0
        push dword ptr [DAT_0056E1E0]
        mov ecx, edi
        push 0
        push ebx
        call sub_414160
        mov ecx, dword ptr [ebp - 0ch]
        mov dword ptr [esi], offset PTR_sub_56D1C5_0056ed68
        mov eax, esi
        pop edi
        pop esi
        pop ebx
        mov dword ptr fs:[0], ecx
        leave
        ret 4
    }
}
