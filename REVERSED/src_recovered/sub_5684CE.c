/* C-callable restore half of the x87 control-word pair at 0x005684ce. */
extern void groove_restore_x87_control_word(void);

__declspec(naked) int sub_5684CE(void)
{
    __asm {
        push eax
        call groove_restore_x87_control_word
        pop eax
        ret
    }
}
