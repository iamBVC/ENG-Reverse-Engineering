/*
 * C-callable adaptation of the original x87 precision setup at 0x00568445.
 * In the original caller this code reads a CW saved in an ad-hoc stack slot;
 * the Ghidra C caller cannot preserve that stack shape, so capture/restore the
 * same per-thread FPU state explicitly across the paired helper calls.
 */
static __declspec(thread) unsigned short groove_saved_x87_cw;
static __declspec(thread) unsigned char groove_saved_x87_cw_pending;

void groove_prepare_x87_control_word(void)
{
    unsigned short original;
    unsigned short prepared;

    __asm { fnstcw word ptr [original] }
    groove_saved_x87_cw = original;
    groove_saved_x87_cw_pending = 1;
    prepared = (unsigned short)((original & 0x0300u) | 0x007fu);
    __asm { fldcw word ptr [prepared] }
}

void groove_restore_x87_control_word(void)
{
    if (groove_saved_x87_cw_pending) {
        const unsigned short original = groove_saved_x87_cw;
        __asm { fldcw word ptr [original] }
        groove_saved_x87_cw_pending = 0;
    }
}

__declspec(naked) int sub_568445(void)
{
    __asm {
        push eax
        push ecx
        push edx
        call groove_prepare_x87_control_word
        pop edx
        pop ecx
        pop eax
        ret
    }
}
