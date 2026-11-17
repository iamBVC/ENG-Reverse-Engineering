/* sub_563382 @ 00563382. The original routine is an x87 math-error path
 * entered by the adjacent wrapper with its operands in registers, stack slots,
 * and ST(0). Keep that mixed ABI and the helper tail transfers intact. */
extern const char groove_sub_563382_math_name[4];
extern const unsigned char groove_sub_563382_positive_infinity[10];
extern const unsigned char groove_sub_563382_negative_infinity[10];
extern uint __cdecl __fload_withFB(void);

undefined4 __declspec(naked) sub_563382(void)
{
    __asm {
        mov ecx, eax
        push eax
        wait
        fnstcw word ptr [esp]
        cmp word ptr [esp], 27fh
        je f382_check_exponent
        mov edx, dword ptr [esp]
        and edx, 300h
        or edx, 7fh
        mov word ptr [esp+2], dx
        fldcw word ptr [esp+2]

f382_check_exponent:
        and ecx, 7ff00000h
        lea edx, dword ptr [esp+8]
        cmp ecx, 7ff00000h
        je f382_nan_or_infinity

f382_finite:
        call __fload_withFB
        je f382_zero_result
        test eax, 7ff00000h
        je f382_special_operand
f382_sign_test:
        mov cl, byte ptr [esp+0fh]
        and cl, 80h
        jne f382_negative_argument
f382_logarithm:
        fyl2x
        call sub_568430
        cmp cl, 1
        jne f382_check_math_error
        fchs

f382_check_math_error:
        cmp dword ptr [DAT_006da358], 0
        jne f382_restore_cw_return
        lea ecx, dword ptr [groove_sub_563382_math_name]
        mov edx, 1dh
        jmp sub_568519

f382_error_return:
        cmp dword ptr [DAT_006da358], 0
        jne f382_restore_cw_return
        lea ecx, dword ptr [groove_sub_563382_math_name]
        mov edx, 1dh
        call sub_5683D0
        pop edx
        ret

f382_load_exception_operand:
        lea edx, dword ptr [esp+8]
        call __fload_withFB
        test byte ptr [esp+16h], 8
        jne f382_add_error_one
        inc ecx
        jmp f382_classify_remainder

f382_add_error_one:
        faddp st(1), st(0)
        mov eax, 1
        jmp f382_error_return

f382_zero_result:
        xor ecx, ecx
        jmp f382_classify_remainder

f382_nan_or_infinity:
        xor ecx, ecx
        and eax, 0fffffh
        or eax, dword ptr [esp+10h]
        jne f382_load_exception_operand
        lea edx, dword ptr [esp+8]
        call __fload_withFB
        jmp f382_classify_remainder

f382_classify_remainder:
        mov eax, dword ptr [esp+0ch]
        mov edx, eax
        and eax, 7ff00000h
        and edx, 0fffffh
        cmp eax, 7ff00000h
        jne f382_check_remainder_code
        or edx, dword ptr [esp+8]
        jne f382_invalid_remainder

f382_check_remainder_code:
        test ecx, ecx
        jne f382_domain_error
        sub esp, 74h
        mov ecx, esp
        push ecx
        sub esp, 10h
        fstp qword ptr [esp]
        fstp qword ptr [esp+8]
        wait
        fnsave [ecx+8]
        call sub_5685BC
        add esp, 10h
        pop ecx
        frstor [ecx+8]
        fld qword ptr [ecx]
        add esp, 74h
        test eax, eax
        je f382_restore_cw_return
        mov eax, 1
        jmp f382_error_return

f382_invalid_remainder:
        test byte ptr [esp+0eh], 8
        jne f382_add_error_one

f382_domain_error:
        faddp st(1), st(0)
        mov eax, 7
        jmp f382_error_return

f382_special_operand:
        mov eax, dword ptr [esp+0ch]
        and eax, 0fffffh
        or eax, dword ptr [esp+8]
        jne f382_sign_test
        fstp st(0)
        mov eax, dword ptr [esp+14h]
        test eax, 7ff00000h
        je f382_special_zero
        call sub_563555
        mov ch, byte ptr [esp+0fh]
        shr ch, 7
        test dword ptr [esp+17h], 80h
        je f382_infinite_result
        fld tbyte ptr [groove_sub_563382_positive_infinity]
        test ch, cl
        je f382_special_positive_infinity
        fchs

f382_special_positive_infinity:
        mov eax, 2
        jmp f382_error_return

f382_infinite_result:
        fldz
        test ch, cl
        je f382_restore_cw_return
        fchs
        jmp f382_restore_cw_return

f382_special_zero:
        fstp st(0)
        and eax, 0fffffh
        or eax, dword ptr [esp+10h]
        jne f382_special_nan
        fld1
        jmp f382_restore_cw_return

f382_special_nan:
        fldz
        jmp f382_restore_cw_return

f382_negative_argument:
        fld st(1)
        call sub_563555
        fchs
        test cl, cl
        jne f382_logarithm
        fstp st(0)
        fstp st(0)
        fld tbyte ptr [groove_sub_563382_negative_infinity]
        mov eax, 1
        jmp f382_error_return

f382_restore_cw_return:
        cmp word ptr [esp], 27fh
        je f382_pop_saved_control_word
        fldcw word ptr [esp]
f382_pop_saved_control_word:
        pop edx
        ret
    }
}
