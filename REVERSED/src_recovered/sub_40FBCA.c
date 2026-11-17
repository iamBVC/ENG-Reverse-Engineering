/* Exact MSVC 6 SEH cleanup epilogue from original code label 0x0040FBCA. */
__declspec(naked) int __cdecl sub_40FBCA(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 0ch]
        pop edi
        pop esi
        xor al, al
        mov dword ptr fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}
