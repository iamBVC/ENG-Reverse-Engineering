#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"

const char groove_string_too_long[] = "string too long";
const char groove_string_invalid_position[] = "invalid string position";

/* ==== LAB_00427fa0 ==== */
/* Original bytes at 0x00427fa0: 8B C1 C3 (mov eax, ecx; ret).
 * sub_402810 invokes this callback with the element pointer in ECX and expects
 * the identity result in EAX.  Keep the exact register-level behavior. */
__declspec(naked) void LAB_00427fa0(void)
{
    __asm {
        mov eax, ecx
        ret
    }
}

/* Relocated equivalent of WinMain's loc_41D48C catch epilogue. The frame
 * handler calls this with WinMain's original EBP, saved registers and args. */
__declspec(naked) void __cdecl groove_resume_winemain_epilogue(void)
{
    __asm {
        xor eax, eax
        mov ecx, dword ptr [ebp - 0ch]
        mov dword ptr fs:[0], ecx
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 10h
    }
}

/* Relocated continuation at loc_411CBC, retaining Callback's frame ABI. */
__declspec(naked) void __cdecl groove_resume_callback_epilogue(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 0ch]
        pop edi
        pop esi
        mov eax, 1
        mov dword ptr fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret 14h
    }
}

/* Relocated continuation at loc_41229A in sub_411D60. */
__declspec(naked) void __cdecl groove_resume_sub_411d60_epilogue(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 0ch]
        pop edi
        pop esi
        mov eax, 1
        mov dword ptr fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret 18h
    }
}

/* Relocated continuation at loc_4125CC in sub_412320. */
__declspec(naked) void __cdecl groove_resume_sub_412320_epilogue(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 0ch]
        pop edi
        pop esi
        mov eax, 1
        mov dword ptr fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret 8
    }
}

/* Relocated continuation at loc_41145D in sub_411000. */
__declspec(naked) void __cdecl groove_resume_sub_411000_epilogue(void)
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

/* Relocated loc_413CBA continuation from sub_413C40. */
__declspec(naked) void __cdecl groove_resume_sub_413c40_continuation(void)
{
    __asm {
        mov ebx, dword ptr [ebp - 18h]
        mov esi, dword ptr [ebp - 14h]
    copy_segment:
        mov eax, dword ptr [ebx + 8]
        test eax, eax
        jbe finish_segment
        cmp eax, esi
        jbe copy_length_ready
        mov eax, esi
    copy_length_ready:
        mov esi, dword ptr [ebx + 4]
        mov ecx, eax
        mov eax, dword ptr [ebp + 8]
        mov edx, ecx
        shr ecx, 2
        lea edi, dword ptr [eax + 1]
        rep movsd
        mov ecx, edx
        and ecx, 3
        rep movsb
        mov esi, dword ptr [ebp - 14h]
    finish_segment:
        mov eax, dword ptr [ebx + 4]
        mov edi, dword ptr [ebx + 8]
        test eax, eax
        jz release_segment
        lea ecx, dword ptr [eax - 1]
        mov al, byte ptr [eax - 1]
        test al, al
        jz delete_segment
        cmp al, 0FFh
        jz delete_segment
        dec al
        mov byte ptr [ecx], al
        jmp release_segment
    delete_segment:
        push ecx
        call sub_562941
        add esp, 4
    release_segment:
        mov eax, dword ptr [ebp + 8]
        mov dword ptr [ebx + 8], 0
        inc eax
        cmp edi, esi
        mov dword ptr [ebx + 4], eax
        mov byte ptr [eax - 1], 0
        mov dword ptr [ebx + 0Ch], esi
        ja preserve_length
        mov esi, edi
    preserve_length:
        mov ecx, dword ptr [ebx + 4]
        mov dword ptr [ebx + 8], esi
        pop edi
        mov byte ptr [ecx + esi], 0
        mov ecx, dword ptr [ebp - 0Ch]
        pop esi
        mov dword ptr fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret 4
    }
}
