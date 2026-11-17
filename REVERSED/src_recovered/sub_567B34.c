/* Exact inherited-frame helper at 0x00567B34. The caller at 0x00567AF3 has
 * already established EBP/EBX/ESI/EDI; this routine is an ordinary CALL target
 * but reads that caller's frame and must not manufacture a new one. */
__declspec(naked) void sub_567B34(void)
{
    __asm {
        mov eax, dword ptr [ebp - 28h]
        mov dword ptr [esi - 4], eax
        mov eax, dword ptr [ebp - 1ch]
        mov dword ptr [DAT_006da420], eax
        mov eax, dword ptr [ebp - 20h]
        mov dword ptr [DAT_006da424], eax

        cmp dword ptr [edi], 0e06d7363h
        jne exception_done
        cmp dword ptr [edi + 10h], 3
        jne exception_done
        cmp dword ptr [edi + 14h], 19930520h
        jne exception_done
        cmp dword ptr [ebp - 24h], ebx
        jne exception_done
        cmp dword ptr [ebp - 2ch], ebx
        je exception_done

        call __abnormal_termination
        push eax
        push edi
        call sub_567D68
        pop ecx
        pop ecx

    exception_done:
        ret
    }
}
