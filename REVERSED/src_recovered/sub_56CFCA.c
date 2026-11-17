/*
 * Recovered x87 status probe at 0x0056cfca. Ghidra emitted an empty body,
 * but the original tests selected operations through the byte argument and
 * lets their x87 status effects stand. The embedded 80-bit constants are the
 * exact ten bytes at 0x0057d38c and 0x0057d398 in the original PE.
 */
static const unsigned char groove_x87_overflow_constant[10] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x44
};
static const unsigned char groove_x87_underflow_constant[10] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30
};

__declspec(naked) int sub_56CFCA(unsigned int flags)
{
    __asm {
        push ebp
        mov ebp, esp
        push ecx
        push ecx
        mov cl, byte ptr [ebp + 8]

        test cl, 1
        jz x87_probe_after_integer_overflow
        fld tbyte ptr [groove_x87_overflow_constant]
        fistp dword ptr [ebp + 8]
        fwait
x87_probe_after_integer_overflow:
        test cl, 8
        jz x87_probe_after_status_snapshot
        fwait
        fnstsw ax
        fld tbyte ptr [groove_x87_overflow_constant]
        fstp qword ptr [ebp - 8]
        fwait
        fwait
        fnstsw ax
x87_probe_after_status_snapshot:
        test cl, 10h
        jz x87_probe_after_underflow
        fld tbyte ptr [groove_x87_underflow_constant]
        fstp qword ptr [ebp - 8]
        fwait
x87_probe_after_underflow:
        test cl, 4
        jz x87_probe_after_divide_by_zero
        fldz
        fld1
        _emit 0deh
        _emit 0f1h
        fstp st(0)
        fwait
x87_probe_after_divide_by_zero:
        test cl, 20h
        jz x87_probe_done
        fldpi
        fstp qword ptr [ebp - 8]
        fwait
x87_probe_done:
        mov esp, ebp
        pop ebp
        ret
    }
}
