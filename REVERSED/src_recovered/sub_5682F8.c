/* Exact x87 stack transform from the original bytes at 0x005682f8. */
__declspec(naked) int sub_5682F8(void)
{
    __asm {
        fxch st(1)
        fstp st(0)
        ret
    }
}
