/* Exact x87 stack transform from the original bytes at 0x00568306. */
__declspec(naked) int sub_568306(void)
{
    __asm {
        fstp st(0)
        fldz
        ret
    }
}
