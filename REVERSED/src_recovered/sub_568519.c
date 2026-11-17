#include "ghidra_shim.h"

extern float10 __cdecl __startOneArgErrorHandling(void);

static const unsigned __int64 groove_x87_max_finite = 0x7fefffffffffffffui64;
static const unsigned __int64 groove_x87_min_normal = 0x0010000000000000ui64;
static const unsigned __int64 groove_x87_negative_1536 = 0xc098000000000000ui64;
static const unsigned __int64 groove_x87_positive_1536 = 0x4098000000000000ui64;
static const unsigned __int64 groove_x87_infinity = 0x7ff0000000000000ui64;
static const unsigned __int64 groove_x87_zero = 0;

/* Tail-entered runtime error path. It consumes the inherited stack word and
 * uses ST(0), EDX, and the original floating-point control/status words. */
__declspec(naked) void sub_568519(void)
{
    __asm {
        sub esp, 8
        fst qword ptr [esp]
        mov eax, dword ptr [esp + 4]
        add esp, 8
        and eax, 7ff00000h
        je subnormal_or_zero
        cmp eax, 7ff00000h
        je infinity_or_nan
        mov ax, word ptr [esp]
        cmp ax, 27fh
        je restore_control_word
        and ax, 20h
        jne return_without_restore
        wait
        fnstsw ax
        and ax, 20h
        je return_without_restore
        mov eax, 8
        jmp dispatch_error

    return_without_restore:
        pop edx
        ret

    restore_control_word:
        fldcw word ptr [esp]
        pop edx
        ret

    subnormal_or_zero:
        fld qword ptr [groove_x87_positive_1536]
        fxch st(1)
        fscale
        fstp st(1)
        fld st(0)
        fabs
        fcomp qword ptr [groove_x87_min_normal]
        wait
        fnstsw ax
        sahf
        mov eax, 4
        jae dispatch_error
        fmul qword ptr [groove_x87_zero]
        jmp dispatch_error

    infinity_or_nan:
        fld qword ptr [groove_x87_negative_1536]
        fxch st(1)
        fscale
        fstp st(1)
        fld st(0)
        fabs
        fcomp qword ptr [groove_x87_max_finite]
        wait
        fnstsw ax
        sahf
        mov eax, 3
        jbe dispatch_error
        fmul qword ptr [groove_x87_infinity]
        jmp dispatch_error

    dispatch_error:
        cmp edx, 1dh
        je error_type_1d
        call __startOneArgErrorHandling
        pop edx
        ret

    error_type_1d:
        call sub_5683D0
        pop edx
        ret
    }
}
