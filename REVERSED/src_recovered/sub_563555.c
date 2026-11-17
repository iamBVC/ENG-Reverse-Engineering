#include "ghidra_shim.h"

static const double groove_round_half = 0.5;

/* Exact FPU classifier at 0x00563555. The meaningful result is in CL even
 * though the decompiler lost that register output and emitted a void C body. */
__declspec(naked) void sub_563555(void)
{
    __asm {
        fld st(0)
        frndint
        fcomp st(1)
        mov cl, 0
        wait
        fnstsw ax
        sahf
        jne non_integral
        fmul qword ptr [groove_round_half]
        inc cl
        fld st(0)
        frndint
        fcompp
        wait
        fnstsw ax
        sahf
        jne return_classification
        inc cl
    return_classification:
        ret
    non_integral:
        fstp st(0)
        ret
    }
}
