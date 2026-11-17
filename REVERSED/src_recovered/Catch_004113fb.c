#include "ghidra_shim.h"

extern void __cdecl groove_resume_sub_411000_epilogue(void);

/* Original catch funclet at 0x004113FB. It executes against sub_411000's
 * frame and returns the address of that function's shared catch epilogue. */
__declspec(naked) undefined1 *Catch_004113fb(void)
{
    __asm {
        call sub_4114A0
        mov ecx, dword ptr [ebp - 98h]
        lea eax, dword ptr [ebp - 0B4h]
        push eax
        mov edx, dword ptr [ecx]
        call dword ptr [edx]
        mov eax, dword ptr [eax + 4]
        xor ebx, ebx
        cmp eax, ebx
        mov byte ptr [ebp - 4], 2
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push eax
        call sub_426500
        mov eax, dword ptr [ebp - 0B0h]
        add esp, 4
        cmp eax, ebx
        jz catch_done
        lea ecx, dword ptr [eax - 1]
        mov al, byte ptr [eax - 1]
        cmp al, bl
        jz free_message
        cmp al, 0FFh
        jz free_message
        dec al
        mov byte ptr [ecx], al
        mov eax, offset groove_resume_sub_411000_epilogue
        ret
    free_message:
        push ecx
        call sub_562941
        add esp, 4
    catch_done:
        mov eax, offset groove_resume_sub_411000_epilogue
        ret
    }
}
