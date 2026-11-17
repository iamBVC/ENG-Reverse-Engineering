#include "ghidra_shim.h"

extern void __cdecl groove_resume_callback_epilogue(void);

/* Original DirectDraw catch funclet at 0x00411CD4. EBP and the saved
 * registers belong to Callback; the returned address resumes its cleanup. */
__declspec(naked) undefined4 Catch_00411cd4(void)
{
    __asm {
        mov eax, dword ptr [ebp - 24h]
        test eax, eax
        jz release_second
        mov ecx, dword ptr [eax]
        push eax
        call dword ptr [ecx + 8]
    release_second:
        mov eax, dword ptr [ebp - 28h]
        test eax, eax
        jz release_ddraw
        mov edx, dword ptr [eax]
        push eax
        call dword ptr [edx + 8]
    release_ddraw:
        mov eax, dword ptr [ebp - 18h]
        test eax, eax
        jz release_block
        mov ecx, dword ptr [eax]
        push eax
        call dword ptr [ecx + 8]
    release_block:
        mov ecx, dword ptr [ebp - 1Ch]
        test ecx, ecx
        jz acquire_error_message
        mov esi, ecx
        call sub_413170
        push esi
        call sub_562941
        add esp, 4
    acquire_error_message:
        mov ecx, dword ptr [ebp - 80h]
        lea eax, dword ptr [ebp - 90h]
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
        lea ecx, dword ptr [ebp - 90h]
        mov byte ptr [ebp - 4], 2
        push 1
        call sub_413BF0
        push 0
        push 0
        push 0
        push 3
        call sub_40FBE0
        add esp, 10h
        mov eax, offset groove_resume_callback_epilogue
        ret
    }
}
