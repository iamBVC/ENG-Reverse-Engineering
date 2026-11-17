#include "ghidra_shim.h"

/* MSVC 6 string-too-long path. EBP belongs to the caller's protected frame;
 * sub_56D674 installs the relocated handler before the frame locals are used. */
__declspec(naked) void sub_56D0A0(void)
{
    __asm {
        mov eax, offset sub_56D910
        call sub_56D674
        sub esp, 30h
        mov al, byte ptr [ebp - 0dh]
        push esi
        push 0
        lea ecx, dword ptr [ebp - 20h]
        mov byte ptr [ebp - 20h], al
        call sub_413BF0
        mov esi, offset groove_string_too_long
        push esi
        call strlen
        pop ecx
        push eax
        push esi
        lea ecx, dword ptr [ebp - 20h]
        call sub_56D3B4
        and dword ptr [ebp - 4], 0
        lea eax, dword ptr [ebp - 20h]
        push eax
        lea ecx, dword ptr [ebp - 3ch]
        call sub_56D0FA
        lea eax, dword ptr [ebp - 3ch]
        push offset DAT_0056F5D8
        push eax
        mov dword ptr [ebp - 3ch], offset PTR_LAB_0056ed48
        call __CxxThrowException_8
        pop esi
        ret
    }
}
