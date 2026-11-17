#include "ghidra_shim.h"

/* ST(0), EAX, ECX, EDX and the caller's stack are this helper's real inputs. */
__declspec(naked) float10 sub_5683D0(void)
{
    __asm {
        push ebp
        mov ebp, esp
        add esp, -20h
        mov dword ptr [ebp - 20h], eax
        mov eax, dword ptr [ebp + 18h]
        mov dword ptr [ebp - 10h], eax
        mov eax, dword ptr [ebp + 1ch]
        mov dword ptr [ebp - 0ch], eax
        jmp common_entry

    common_entry:
        fstp qword ptr [ebp - 8]
        mov dword ptr [ebp - 1ch], ecx
        mov eax, dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ebp - 18h], eax
        mov dword ptr [ebp - 14h], ecx
        lea eax, dword ptr [ebp + 8]
        lea ecx, dword ptr [ebp - 20h]
        push eax
        push ecx
        push edx
        call sub_56B8FB
        add esp, 0ch
        fld qword ptr [ebp - 8]
        cmp word ptr [ebp + 8], 27fh
        je control_word_ready
        fldcw word ptr [ebp + 8]
    control_word_ready:
        leave
        ret
    }
}
