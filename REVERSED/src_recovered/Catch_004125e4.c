#include "ghidra_shim.h"

extern void __cdecl groove_resume_sub_412320_epilogue(void);

/* Original catch funclet at 0x004125E4, using sub_412320's EBP frame. */
__declspec(naked) undefined4 Catch_004125e4(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 24h]
        lea edx, dword ptr [ebp - 34h]
        push edx
        mov eax, dword ptr [ecx]
        call dword ptr [eax]
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 4
        test eax, eax
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push eax
        call sub_426500
        mov eax, dword ptr [ebp - 30h]
        add esp, 4
        test eax, eax
        jz catch_done
        lea ecx, dword ptr [eax - 1]
        mov al, byte ptr [eax - 1]
        test al, al
        jz free_message
        cmp al, 0FFh
        jz free_message
        dec al
        mov byte ptr [ecx], al
        mov eax, offset groove_resume_sub_412320_epilogue
        ret
    free_message:
        push ecx
        call sub_562941
        add esp, 4
    catch_done:
        mov eax, offset groove_resume_sub_412320_epilogue
        ret
    }
}
