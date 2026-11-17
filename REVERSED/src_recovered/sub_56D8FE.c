/* Original MSVC 6 unwind funclet thunk at 0x0056D8FE; EAX selects its metadata. */
__declspec(naked) int __cdecl sub_56D8FE(int param_1, int param_2,
                                       int param_3, int param_4)
{
    __asm {
        mov eax, offset DAT_0056F4F8
        jmp sub_562FA9
    }
}
