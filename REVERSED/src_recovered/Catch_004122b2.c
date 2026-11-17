#include "ghidra_shim.h"

extern void __cdecl groove_resume_sub_411d60_epilogue(void);

/* Original catch funclet at 0x004122B2, using sub_411D60's EBP frame. */
__declspec(naked) undefined4 Catch_004122b2(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 20h]
        test ecx, ecx
        jz block_done
        mov esi, ecx
        call sub_413390
        push esi
        call sub_562941
        add esp, 4
    block_done:
        mov ecx, dword ptr [ebp + 0Ch]
        lea eax, dword ptr [ebp - 50h]
        push eax
        mov edx, dword ptr [ecx]
        call dword ptr [edx]
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 3
        test eax, eax
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push eax
        call sub_426500
        add esp, 4
        lea ecx, dword ptr [ebp - 50h]
        mov byte ptr [ebp - 4], 2
        push 1
        call sub_413BF0
        push 0
        push 0
        push 0
        push 3
        call sub_40FBE0
        add esp, 10h
        mov eax, offset groove_resume_sub_411d60_epilogue
        ret
    }
}
