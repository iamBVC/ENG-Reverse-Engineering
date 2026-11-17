#include "ghidra_shim.h"

static const double groove_half = 0.5;

/* Exact x87 classifier at 0x00568191. It returns the class in EAX while
 * preserving the caller's original value in ST(0). */
__declspec(naked) int sub_568191(void)
{
    __asm {
        fld st(0)
        frndint
        fcomp st(1)
        wait
        fnstsw ax
        sahf
        jne not_integral
        fld st(0)
        fmul qword ptr [groove_half]
        fld st(0)
        frndint
        fcompp
        wait
        fnstsw ax
        sahf
        je half_integral
        mov eax, 1
        ret
    not_integral:
        mov eax, 0
        ret
    half_integral:
        mov eax, 2
        ret
    }
}
