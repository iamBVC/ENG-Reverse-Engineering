#include "ghidra_shim.h"

/* Original WinMain catch funclet. EAX returns the address of a relocated copy
 * of loc_41D48C, whose epilogue consumes WinMain's original stack frame. */
extern void __cdecl groove_resume_winemain_epilogue(void);

__declspec(naked) undefined4 Catch_0041d923(void)
{
    __asm {
        mov ecx, dword ptr [ebp + 10h]
        lea eax, dword ptr [ebp - 28h]
        push eax
        mov edx, dword ptr [ecx]
        call dword ptr [edx]
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 2
        test eax, eax
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push eax
        call sub_426500
        mov eax, dword ptr [ebp - 24h]
        add esp, 4
        test eax, eax
        jz catch_done
        lea ecx, dword ptr [eax - 1]
        mov al, byte ptr [eax - 1]
        test al, al
        jz free_message
        cmp al, 0ffh
        jz free_message
        dec al
        mov byte ptr [ecx], al
        mov eax, offset groove_resume_winemain_epilogue
        ret
    free_message:
        push ecx
        call sub_562941
        add esp, 4
    catch_done:
        mov eax, offset groove_resume_winemain_epilogue
        ret
    }
}
