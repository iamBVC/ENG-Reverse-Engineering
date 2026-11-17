/* Original bytes at 0x00562F4C: pop eax; pop ecx; xchg [esp],eax; jmp eax.
 * This is an x86 thiscall tail-dispatch thunk, not a pair of CRT lock calls. */
#include "ghidra_shim.h"

__declspec(naked) int __cdecl sub_562F4C(
    undefined4 this_value, code *target, int target_argument)
{
    __asm {
        pop eax
        pop ecx
        xchg dword ptr [esp], eax
        jmp eax
    }
}
