#include "ghidra_shim.h"

extern void __cdecl groove_resume_sub_413c40_continuation(void);

/* Original catch-all funclet at 0x00413C99. It allocates the destination
 * buffer, then resumes the owner's in-frame copy and cleanup sequence. */
__declspec(naked) undefined1 *Catch_00413c99(void)
{
    __asm {
        mov eax, dword ptr [ebp + 8]
        mov dword ptr [ebp - 14h], eax
        add eax, 2
        test eax, eax
        jge size_ready
        xor eax, eax
    size_ready:
        push eax
        call operator_new
        mov dword ptr [ebp + 8], eax
        add esp, 4
        mov eax, offset groove_resume_sub_413c40_continuation
        ret
    }
}
