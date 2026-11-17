#include "ghidra_shim.h"

/* This is an x86 thiscall constructor: ECX is the destination object, the
 * source string is at [EBP+8], and RET 4 releases that one stack argument. */
__declspec(naked) undefined4 * sub_56D0FA(int param_1)
{
    __asm {
        mov eax, offset sub_56D924
        call sub_56D674
        push ecx
        push ecx
        push ebx
        push esi
        lea eax, dword ptr [ebp - 10h]
        push edi
        mov esi, ecx
        push eax
        mov dword ptr [ebp - 14h], esi
        mov dword ptr [ebp - 10h], offset DAT_0057F834
        call sub_56D5C8
        mov ebx, dword ptr [ebp + 8]
        and dword ptr [ebp - 4], 0
        lea edi, dword ptr [esi + 0ch]
        push 0
        mov al, byte ptr [ebx]
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
