#include "ghidra_shim.h"

static const unsigned char groove_x87_positive_infinity80[10] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x7f
};

/* This helper inherits the caller's EBP frame and may tail-return through it. */
__declspec(naked) undefined5 sub_56814E(void)
{
    __asm {
        fld st(0)
        fabs
        fld tbyte ptr [DAT_0057ccee]
        fcompp
        wait
        fnstsw word ptr [ebp - 0a0h]
        wait
        test byte ptr [ebp - 09fh], 41h
        jne large_argument

        fld st(0)
        frndint
        ftst
        wait
        fnstsw word ptr [ebp - 0a0h]
        wait
        mov dl, byte ptr [ebp - 09fh]
        fxch st(1)
        fsub st(0), st(1)
        ftst
        wait
        fnstsw word ptr [ebp - 0a0h]
        fabs
        f2xm1
        ret

    large_argument:
        pop eax
        ftst
        wait
        fnstsw word ptr [ebp - 0a0h]
        wait
        test byte ptr [ebp - 09fh], 1
        jne exceptional_argument
        fstp st(0)
        fld tbyte ptr [groove_x87_positive_infinity80]
        or ch, ch
        je large_argument_return
        fchs
    large_argument_return:
        ret

    exceptional_argument:
        mov byte ptr [ebp - 90h], 4
        jmp sub_568306
    }
}
