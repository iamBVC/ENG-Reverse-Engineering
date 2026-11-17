#include "ghidra_shim.h"

/* Exact MSVC 6 x86 EH registration prologue from groove.exe (0x0056d674).
 * EAX carries the function's handler thunk on entry; the helper installs the
 * registration record and returns into the caller while preserving that ABI. */
__declspec(naked) void sub_56D674(void)
{
    __asm {
        push -1
        push eax
        mov eax, dword ptr fs:[0]
        push eax
        mov eax, dword ptr [esp + 0ch]
        mov dword ptr fs:[0], esp
        mov dword ptr [esp + 0ch], ebp
        lea ebp, dword ptr [esp + 0ch]
        push eax
        ret
    }
}
