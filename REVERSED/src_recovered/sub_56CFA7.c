#include "ghidra_shim.h"

/* _controlfp-style helper at 0x0056CFA7. The decompiler dropped both stack
 * parameters; the original merges new_value through mask, loads the control
 * word, and returns the old control word. */
__declspec(naked) int __cdecl sub_56CFA7(unsigned int new_value, unsigned int mask)
{
    __asm {
        push ebp
        mov ebp, esp
        push ecx
        wait
        fnstcw word ptr [ebp - 4]
        mov eax, dword ptr [ebp + 0Ch]
        mov ecx, eax
        and eax, dword ptr [ebp + 8]
        not ecx
        and ecx, dword ptr [ebp - 4]
        or ecx, eax
        mov dword ptr [ebp + 0Ch], ecx
        fldcw word ptr [ebp + 0Ch]
        movsx eax, word ptr [ebp - 4]
        leave
        ret
    }
}
