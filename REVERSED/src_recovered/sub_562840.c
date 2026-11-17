/*
 * Exact x86 stack-probe helper recovered from groove.exe at 0x00562840.
 * EAX carries the requested stack allocation size; this routine probes each
 * crossed page, moves ESP, restores the caller's return address, and returns
 * without using the ordinary C calling convention.
 */
__declspec(naked) void sub_562840(void)
{
    __asm {
        push ecx
        cmp eax, 1000h
        lea ecx, [esp + 8]
        jb  probe_done

    probe_pages:
        sub ecx, 1000h
        sub eax, 1000h
        test dword ptr [ecx], eax
        cmp eax, 1000h
        jae probe_pages

    probe_done:
        sub ecx, eax
        mov eax, esp
        test dword ptr [ecx], eax
        mov esp, ecx
        mov ecx, dword ptr [eax]
        mov eax, dword ptr [eax + 4]
        push eax
        ret
    }
}
