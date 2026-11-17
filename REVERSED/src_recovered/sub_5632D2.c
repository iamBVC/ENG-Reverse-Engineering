/* Original x86 notification thunk at 0x005632d2.  It consumes its notification
 * argument and records live EAX/EBP state; an ordinary C body cannot reproduce it. */
#include "ghidra_shim.h"
#include "ghidra_globals.h"

__declspec(naked) int sub_5632D2(void)
{
    __asm {
        push ebx
        push ecx
        mov ecx, dword ptr [ebp + 8]
        mov dword ptr [DAT_0057c778], ecx
        mov dword ptr [DAT_0057c774], eax
        mov dword ptr [DAT_0057c77c], ebp
        pop ecx
        pop ebx
        ret 4
    }
}
