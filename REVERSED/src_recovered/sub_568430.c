#include "ghidra_shim.h"

/* Exact x87 helper at 0x00568430. Its floating result stays in ST(0); EAX,
 * CL, and the caller's existing stack frame pass through unchanged. */
__declspec(naked) int sub_568430(void)
{
    __asm {
        fld st(0)
        frndint
        fsubr st(1), st(0)
        fxch st(1)
        fchs
        f2xm1
        fld1
        faddp st(1), st(0)
        fscale
        fstp st(1)
        ret
    }
}
