#include "ghidra_shim.h"

/* MSVC EH3 frame handler. The filter/state helper at sub_5632D2 returns its
 * selected state in ECX; keep the whole control-flow path in assembly so that
 * value survives into the table lookup below. */
__declspec(naked) undefined4 sub_563E08(int param_1, int param_2, undefined4 param_3)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        push ebx
        push esi
        push edi
        push ebp
        cld
        mov ebx, dword ptr [ebp + 0ch]
        mov eax, dword ptr [ebp + 8]
        test dword ptr [eax + 4], 6
        jne eh3_local_unwind

        mov dword ptr [ebp - 8], eax
        mov eax, dword ptr [ebp + 10h]
        mov dword ptr [ebp - 4], eax
        lea eax, dword ptr [ebp - 8]
        mov dword ptr [ebx - 4], eax
        mov esi, dword ptr [ebx + 0ch]
        mov edi, dword ptr [ebx + 8]

    eh3_handler_loop:
        cmp esi, -1
        je eh3_handled
        lea ecx, dword ptr [esi + esi*2]
        cmp dword ptr [edi + ecx*4 + 4], 0
        je eh3_next_state
        push esi
        push ebp
        lea ebp, dword ptr [ebx + 10h]
        call dword ptr [edi + ecx*4 + 4]
        pop ebp
        pop esi
        mov ebx, dword ptr [ebp + 0ch]
        or eax, eax
        je eh3_next_state
        js eh3_continue_search

        mov edi, dword ptr [ebx + 8]
        push ebx
        call __global_unwind2
        add esp, 4
        lea ebp, dword ptr [ebx + 10h]
        push esi
        push ebx
        call __local_unwind2
        add esp, 8
        lea ecx, dword ptr [esi + esi*2]
        push 1
        mov eax, dword ptr [edi + ecx*4 + 8]
        call sub_5632D2
        mov eax, dword ptr [edi + ecx*4]
        mov dword ptr [ebx + 0ch], eax
        call dword ptr [edi + ecx*4 + 8]

    eh3_next_state:
        mov edi, dword ptr [ebx + 8]
        lea ecx, dword ptr [esi + esi*2]
        mov esi, dword ptr [edi + ecx*4]
        jmp eh3_handler_loop

    eh3_continue_search:
        mov eax, 0
        jmp eh3_return

    eh3_handled:
        mov eax, 1
        jmp eh3_return

    eh3_local_unwind:
        push ebp
        lea ebp, dword ptr [ebx + 10h]
        push -1
        push ebx
        call __local_unwind2
        add esp, 8
        pop ebp
        mov eax, 1

    eh3_return:
        pop ebp
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}
