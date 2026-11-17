/*
 * Recovered from the original x86 wrapper at 0x00562FA9.  The first four
 * parameters are stack arguments; EAX carries the fifth argument implicitly.
 * The three trailing zero arguments are required by sub_5675F8's 8-argument
 * ABI and are not represented in Ghidra's four-parameter pseudo-code.
 */
__declspec(naked) int __cdecl sub_562FA9(int param_1, int param_2,
                                         int param_3, int param_4)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 4
        push ebx
        push esi
        push edi
        cld
        push eax
        call groove_resolve_legacy_func_info
        add esp, 4
        mov dword ptr [ebp - 4], eax
        xor eax, eax
        push eax
        push eax
        push eax
        push dword ptr [ebp - 4]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        push dword ptr [ebp + 8]
        call sub_5675F8
        add esp, 20h
        mov dword ptr [ebp + 14h], eax
        pop edi
        pop esi
        pop ebx
        mov eax, dword ptr [ebp + 14h]
        mov esp, ebp
        pop ebp
        ret
    }
}
