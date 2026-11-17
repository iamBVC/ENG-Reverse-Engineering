/* sub_56B57C @ 0056B57C. This bridge transfers the caller's ST(0)/ST(1)
 * operands into the original helper frame and returns its x87 result. */
extern const double groove_sub_56b_scale_up;

float10 __declspec(naked) sub_56B57C(void)
{
    __asm {
        push edx
        sub esp, 30h
        fstp tbyte ptr [esp+18h]
        fstp tbyte ptr [esp]
        xor edx, edx
        mov eax, dword ptr [esp+6]
        test eax, 7fff0000h
        je f57c_simple
        call sub_56B376
        add esp, 30h
        pop edx
        ret

f57c_simple:
        fld tbyte ptr [esp]
        fld tbyte ptr [esp+18h]
        mov eax, dword ptr [esp]
        or eax, dword ptr [esp+4]
        je f57c_direct_remainder
        fxch st(1)
        fstp tbyte ptr [esp+0ch]
        fld tbyte ptr [esp]
        fxch st(1)
        or edx, 2
        fnstcw word ptr [esp+24h]
        mov eax, dword ptr [esp+24h]
        or eax, 33fh
        mov dword ptr [esp+28h], eax
        fldcw word ptr [esp+28h]
        mov eax, dword ptr [esp+20h]
        and eax, 7fffh
        cmp eax, 7fbeh
        ja f57c_large_operand
        or edx, 1
        fmul qword ptr [groove_sub_56b_scale_up]
        fstp tbyte ptr [esp+18h]
        fmul qword ptr [groove_sub_56b_scale_up]
        fstp tbyte ptr [esp]
        jmp f57c_call_helper

f57c_large_operand:
        fnstcw word ptr [esp+24h]
        mov eax, dword ptr [esp+24h]
        or eax, 300h
        mov dword ptr [esp+28h], eax
        fldcw word ptr [esp+28h]
        fstp st(0)
        fmul qword ptr [groove_sub_56b_scale_up]
        fstp tbyte ptr [esp]

f57c_call_helper:
        fldcw word ptr [esp+24h]
        call sub_56B376
        add esp, 30h
        pop edx
        ret

f57c_direct_remainder:
        fprem
        add esp, 30h
        pop edx
        ret
    }
}
