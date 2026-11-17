#include "ghidra_shim.h"

/* Original catch funclet at 0x0040FB87. It runs inside its owner's frame, so
 * EBP and the cleanup state byte must remain the original registers/slots. */
__declspec(naked) undefined1 *Catch_0040fb87(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 48h]
        lea eax, dword ptr [ebp - 58h]
        push eax
        mov edx, dword ptr [ecx]
        call dword ptr [edx]
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 2
        test eax, eax
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push 0
        push 0
        push eax
        push 1
        call sub_40FBE0
        add esp, 10h
        lea ecx, dword ptr [ebp - 58h]
        mov byte ptr [ebp - 4], 1
        push 1
        call sub_413BF0
        call sub_40FC50
        mov eax, offset sub_40FBCA
        ret
    }
}
