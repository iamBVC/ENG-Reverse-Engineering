#include "ghidra_shim.h"

/* Original DirectDraw catch funclet at 0x0041063A. Ghidra's C lost the owning
 * frame's EBP; the handler also returns an epilogue address in EAX. */
__declspec(naked) undefined1 *Catch_0041063a(void)
{
    __asm {
        call sub_4106C0
        mov eax, dword ptr [ebp - 14h]
        test eax, eax
        jz no_ddraw
        mov edx, dword ptr [eax]
        push eax
        call dword ptr [edx + 8]
    no_ddraw:
        mov ecx, dword ptr [ebp - 18h]
        lea edx, dword ptr [ebp - 4ch]
        push edx
        mov eax, dword ptr [ecx]
        call dword ptr [eax]
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 2
        test eax, eax
        jnz have_message
        mov eax, offset DAT_0056e1bc
    have_message:
        push eax
        call sub_426500
        mov eax, dword ptr [ebp - 48h]
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
        mov eax, offset sub_41069E
        ret
    free_message:
        push ecx
        call sub_562941
        add esp, 4
    catch_done:
        mov eax, offset sub_41069E
        ret
    }
}
