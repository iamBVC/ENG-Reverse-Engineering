#include "ghidra_shim.h"

/* Exact x87 ABI bridge from 0x00563360. On entry ST(0)/ST(1) are the two
 * extended-precision operands; the original shuffles them into cdecl slots. */
__declspec(naked) void sub_563360(void)
{
    __asm {
        sub esp, 10h
        fxch st(1)
        fstp qword ptr [esp]
        fst qword ptr [esp + 8]
        mov eax, dword ptr [esp + 0Ch]
        call sub_563382
        add esp, 10h
        ret
    }
}
