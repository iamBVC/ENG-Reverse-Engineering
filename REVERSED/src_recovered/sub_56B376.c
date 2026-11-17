/* sub_56B376 @ 0056B376. Register, caller-stack, and x87 contract recovered
 * from the original image's complete instruction stream. */
extern const unsigned char groove_sub_56b_expclass_table[16];
extern const double groove_sub_56b_scale_down;
extern const double groove_sub_56b_half;
extern const unsigned char groove_sub_56b_remainder_limit[10];

undefined4 __declspec(naked) sub_56B376(void)
{
    __asm {
        push eax
        push ebx
        push ecx

        mov eax, dword ptr [esp+16h]
        xor eax, 700h
        test eax, 700h
        jne f376_fallback
        shr eax, 0bh
        and eax, 0fh
        cmp byte ptr [groove_sub_56b_expclass_table+eax], 0
        je f376_fallback

        mov eax, dword ptr [esp+16h]
        and eax, 7fff0000h
        cmp eax, 7fff0000h
        je f376_fallback
        mov eax, dword ptr [esp+2eh]
        and eax, 7fff0000h
        je f376_fallback
        cmp eax, 7fff0000h
        je f376_fallback
        mov eax, dword ptr [esp+2ch]
        add eax, eax
        jne f376_fallback
        mov eax, dword ptr [esp+14h]
        add eax, eax
        jne f376_fallback

        mov eax, dword ptr [esp+18h]
        and eax, 7fffh
        add eax, 3fh
        mov ebx, dword ptr [esp+30h]
        and ebx, 7fffh
        sub ebx, eax
        ja f376_large_gap

f376_reduce_loop:
        mov eax, dword ptr [esp+18h]
        and eax, 7fffh
        add eax, 0ah
        mov ebx, dword ptr [esp+30h]
        and ebx, 7fffh
        sub ebx, eax
        js f376_fallback
        fld tbyte ptr [esp+28h]
        mov eax, dword ptr [esp+18h]
        mov ebx, dword ptr [esp+30h]
        and ebx, 7fffh
        mov ecx, ebx
        sub ebx, eax
        and ebx, 7
        or ebx, 4
        sub ecx, ebx
        mov ebx, eax
        and ebx, 8000h
        or ecx, ebx
        mov dword ptr [esp+18h], ecx
        fld tbyte ptr [esp+10h]
        mov dword ptr [esp+18h], eax
        fxch st(1)
        fprem
        fstp tbyte ptr [esp+28h]
        fstp st(0)
        jmp f376_reduce_loop

f376_large_gap:
        test edx, 2
        jne f376_save_rounding
        fld tbyte ptr [esp+10h]
        fstp tbyte ptr [esp+1ch]

f376_save_rounding:
        fnstcw word ptr [esp+34h]
        mov eax, dword ptr [esp+34h]
        or eax, 33fh
        mov dword ptr [esp+38h], eax
        fldcw word ptr [esp+38h]

        mov eax, dword ptr [esp+18h]
        and eax, 7fffh
        mov ebx, dword ptr [esp+30h]
        and ebx, 7fffh
        sub ebx, eax
        and ebx, 3fh
        or ebx, 20h
        add ebx, 1
        mov ecx, ebx
        mov eax, dword ptr [esp+18h]
        mov ebx, dword ptr [esp+30h]
        and ebx, 7fffh
        and eax, 8000h
        or ebx, eax
        mov dword ptr [esp+18h], ebx

        fld tbyte ptr [esp+10h]
        fabs
        fld tbyte ptr [esp+28h]
        fabs
f376_halving_loop:
        fcom st(1)
        fnstsw ax
        and eax, 100h
        jne f376_skip_subtract
        fsub st(0), st(1)
f376_skip_subtract:
        fxch st(1)
        fmul qword ptr [groove_sub_56b_half]
        fxch st(1)
        sub ecx, 1
        jne f376_halving_loop

        mov ebx, dword ptr [esp+30h]
        fstp tbyte ptr [esp+28h]
        fstp st(0)
        fld tbyte ptr [esp+1ch]
        fld tbyte ptr [groove_sub_56b_remainder_limit]
        fprem
        fstp st(0)
        fld tbyte ptr [esp+28h]
        fldcw word ptr [esp+34h]
        and ebx, 8000h
        je f376_common_return
        fchs
        jmp f376_common_return

f376_fallback:
        fld tbyte ptr [esp+10h]
        fld tbyte ptr [esp+28h]
        fprem

f376_common_return:
        test edx, 3
        je f376_epilogue
        fnstsw word ptr [esp+3ch]
        test edx, 1
        je f376_merge_environment
        fnstcw word ptr [esp+34h]
        mov eax, dword ptr [esp+34h]
        or eax, 300h
        mov dword ptr [esp+38h], eax
        fldcw word ptr [esp+38h]
        fmul qword ptr [groove_sub_56b_scale_down]
        fldcw word ptr [esp+34h]

f376_merge_environment:
        mov eax, dword ptr [esp+3ch]
        fxch st(1)
        fstp st(0)
        fld tbyte ptr [esp+1ch]
        fxch st(1)
        and eax, 4300h
        sub esp, 1ch
        fnstenv [esp]
        and dword ptr [esp+4], 0ffffbcffh
        or dword ptr [esp+4], eax
        fldenv [esp]
        add esp, 1ch

f376_epilogue:
        pop ecx
        pop ebx
        pop eax
        ret
    }
}
