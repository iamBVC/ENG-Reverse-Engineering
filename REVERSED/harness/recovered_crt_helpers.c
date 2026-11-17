/* Recovered MSVC runtime bodies from the fresh Ghidra export of groove.exe.
 * The original implementations live inside the EXE; they are not stubs supplied by
 * the Windows CRT.  The two naked helpers preserve the register/x87 contracts visible
 * in the original x86 instructions. */
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"
#include "legacy_exception_metadata.h"

#include <string.h>

__declspec(naked) void __cdecl __global_unwind2(PVOID target_frame)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        push ebp
        push 0
        push 0
        push offset global_unwind_resume
        push dword ptr [ebp + 8]
        call RtlUnwind
    global_unwind_resume:
        pop ebp
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}

/* Original handler at 0x0056321c, relocated into this image.  This compact
 * handler is installed in the x86 SEH registration record used during unwind. */
__declspec(naked) static int __cdecl groove_local_unwind_handler(void)
{
    __asm {
        mov ecx, dword ptr [esp + 4]
        test dword ptr [ecx + 4], 6
        mov eax, 1
        je handler_done
        mov eax, dword ptr [esp + 8]
        mov edx, dword ptr [esp + 10h]
        mov dword ptr [edx], eax
        mov eax, 3
    handler_done:
        ret
    }
}

/* Exact x86 frame/SEH layout from groove.exe at 0x0056323e.  A C translation
 * loses the registration record's stack offsets and breaks FS:[0] unwinding. */
__declspec(naked) void __cdecl __local_unwind2(int frame, int stop_index)
{
    __asm {
        push ebx
        push esi
        push edi
        mov eax, dword ptr [esp + 10h]
        push eax
        push -2
        push offset groove_local_unwind_handler
        push dword ptr fs:[0]
        mov dword ptr fs:[0], esp
    unwind_loop:
        mov eax, dword ptr [esp + 20h]
        mov ebx, dword ptr [eax + 8]
        mov esi, dword ptr [eax + 0ch]
        cmp esi, -1
        je unwind_done
        cmp esi, dword ptr [esp + 24h]
        je unwind_done
        lea esi, dword ptr [esi + esi*2]
        mov ecx, dword ptr [ebx + esi*4]
        mov dword ptr [esp + 8], ecx
        mov eax, dword ptr [esp + 20h]
        mov dword ptr [eax + 0ch], ecx
        cmp dword ptr [ebx + esi*4 + 4], 0
        jne unwind_next
        push 101h
        mov eax, dword ptr [ebx + esi*4 + 8]
        call sub_5632D2
        call dword ptr [ebx + esi*4 + 8]
    unwind_next:
        jmp unwind_loop
    unwind_done:
        pop dword ptr fs:[0]
        add esp, 0ch
        pop edi
        pop esi
        pop ebx
        ret
    }
}

__declspec(naked) int __cdecl __abnormal_termination(void)
{
    __asm {
        xor eax, eax
        mov ecx, dword ptr fs:[0]
        cmp dword ptr [ecx + 4], offset groove_local_unwind_handler
        jne abnormal_done
        mov edx, dword ptr [ecx + 0ch]
        mov edx, dword ptr [edx + 0ch]
        cmp dword ptr [ecx + 8], edx
        jne abnormal_done
        mov eax, 1
    abnormal_done:
        ret
    }
}

int __cdecl flsall(int mode)
{
    int index = 0;
    int successful_flushes = 0;
    int failed_flush = 0;

    while (index < DAT_006db900) {
        int stream = (int)DAT_006da8e4[index];
        if (stream != 0 && (*(unsigned int *)(stream + 0xc) & 0x83) != 0) {
            if (mode == 1) {
                if (sub_5638B5(stream) != -1)
                    ++successful_flushes;
            } else if (mode == 0 && (*(unsigned int *)(stream + 0xc) & 2) != 0) {
                if (sub_5638B5(stream) == -1)
                    failed_flush = -1;
            }
        }
        ++index;
    }
    return mode == 1 ? successful_flushes : failed_flush;
}

void __cdecl __exit(int code_value)
{
    sub_563BD6((unsigned int)code_value, 1, 0);
}

void __cdecl __fassign(int flag, char *argument, char *number)
{
    undefined4 local_low;
    undefined4 local_high;

    if (flag != 0) {
        sub_569934(&local_low);
        *(undefined4 *)argument = local_low;
        *(undefined4 *)(argument + 4) = local_high;
    } else {
        sub_569961(&number, number);
        *(char **)argument = number;
    }
}

int __cdecl __cfltcvt(double *argument, char *buffer, size_t format,
                      int style, int precision, int caps)
{
    (void)caps;
    if (format == 'e' || format == 'E')
        return sub_564196(argument, buffer, style, precision);
    if (format == 'f')
        return sub_56429A(argument, buffer, style);
    return sub_564378(argument, buffer, style, precision);
}

void __cdecl __amsg_exit(int message_id)
{
    if (DAT_006da3b8 == 1)
        sub_5691E5();
    sub_56921E(message_id);
    __exit(0xff);
}

void ___add_12(undefined4 *destination, undefined4 *source)
{
    int carry = sub_56C10F(destination[0], source[0], destination);
    if (carry != 0) {
        carry = sub_56C10F(destination[1], 1, destination + 1);
        if (carry != 0)
            ++destination[2];
    }
    carry = sub_56C10F(destination[1], source[1], destination + 1);
    if (carry != 0)
        ++destination[2];
    sub_56C10F(destination[2], source[2], destination + 2);
}

void __cdecl __CxxThrowException_8(void *object, void *throw_info)
{
    DWORD words[8] = {
        0xe06d7363, 1, 0, 0, 3, 0x19930520, 0, 0
    };
    words[6] = (DWORD)(ULONG_PTR)object;
    words[7] = (DWORD)(ULONG_PTR)throw_info;
    {
        const GrooveLegacyThrowInfo *resolved =
            groove_resolve_legacy_throw_info(throw_info);
        if (resolved != NULL)
            words[7] = (DWORD)(ULONG_PTR)resolved;
    }
    RaiseException(words[0], words[1], words[4], (ULONG_PTR *)&words[5]);
}

void *__cdecl groove_resolve_legacy_func_info(void *legacy_info)
{
    const GrooveLegacyFuncInfo *resolved = groove_find_legacy_func_info(legacy_info);
    return resolved != NULL ? (void *)resolved : legacy_info;
}

/* MSVC 6 cleanup funclets use the owning function's EBP and local offsets. */
__declspec(naked) void __cdecl groove_unwind_410700_state1(void)
{
    __asm {
        lea ecx, dword ptr [ebp - 15ch]
        jmp sub_413B10
    }
}

__declspec(naked) void __cdecl groove_unwind_410700_state2(void)
{
    __asm {
        lea ecx, dword ptr [ebp - 154h]
        jmp sub_413A20
    }
}

/* Relocated copies of the original EH3 unwind actions for the string-error
 * constructors. These run with the protected function's EBP still active. */
__declspec(naked) void __cdecl groove_unwind_56d0a0_state1(void)
{
    __asm {
        lea ecx, dword ptr [ebp - 20h]
        jmp sub_413A20
    }
}

__declspec(naked) void __cdecl groove_unwind_56d0fa_state1(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 14h]
        jmp sub_56D64F
    }
}

__declspec(naked) void __cdecl groove_unwind_56d2cc_state1(void)
{
    __asm {
        lea ecx, dword ptr [ebp - 20h]
        jmp sub_413A20
    }
}

/* Original cleanup thunks at 0x0056D930, 0x0056D944, 0x0056D958 and
 * 0x0056D980 all destroy the exception base object at EBP-0x10. */
__declspec(naked) void __cdecl groove_unwind_56d_exception_base_state1(void)
{
    __asm {
        mov ecx, dword ptr [ebp - 10h]
        jmp sub_56D64F
    }
}

/* Catch block for the DirectDraw exception in sub_410700, transplanted from
 * original bytes 0x00410e52-0x00410eb6.  The old frame handler enters with the
 * protected function's EBP and returns the original cleanup epilogue in EAX.
 */
__declspec(naked) int __cdecl groove_catch_handler_impl(void)
{
    __asm {
        mov byte ptr [ebp - 4], 2
        call sub_410ED0
        lea eax, dword ptr [ebp - 154h]
        lea ecx, dword ptr [ebp - 15ch]
        push eax
        call sub_413B20
        mov eax, dword ptr [eax + 4]
        mov byte ptr [ebp - 4], 3
        test eax, eax
        jne have_error_text
        mov eax, offset DAT_0056e1bc
have_error_text:
        push eax
        call sub_426500
        mov eax, dword ptr [ebp - 150h]
        add esp, 4
        test eax, eax
        je catch_done
        lea ecx, dword ptr [eax - 1]
        mov al, byte ptr [eax - 1]
        test al, al
        je free_error_text
        cmp al, 0ffh
        je free_error_text
        dec al
        mov byte ptr [ecx], al
        mov eax, offset sub_410EB7
        ret
free_error_text:
        push ecx
        call sub_562941
        add esp, 4
catch_done:
        mov eax, offset sub_410EB7
        ret
    }
}

/* The old handler trampoline uses EAX as the callback address, ECX as its context,
 * and EBP as the caller's frame.  C cannot express that contract. */
__declspec(naked) static void __cdecl groove_nlg_notify1(void)
{
    __asm {
        push ecx
        mov dword ptr [DAT_0057c778], ecx
        mov dword ptr [DAT_0057c774], eax
        mov dword ptr [DAT_0057c77c], ebp
        pop ecx
        ret 4
    }
}

__declspec(naked) int __cdecl __CallSettingFrame_12(
    undefined4 callback, undefined4 frame, int notification)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 4
        push ebx
        push ecx
        mov eax, dword ptr [ebp + 0ch]
        add eax, 0ch
        mov dword ptr [ebp - 4], eax
        mov eax, dword ptr [ebp + 8]
        push ebp
        push dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 10h]
        mov ebp, dword ptr [ebp - 4]
        call groove_nlg_notify1
        push esi
        push edi
        call eax
        pop edi
        pop esi
        mov ebx, ebp
        pop ebp
        mov ecx, dword ptr [ebp + 10h]
        push ebp
        mov ebp, ebx
        cmp ecx, 100h
        jne notification_ready
        mov ecx, 2
notification_ready:
        push ecx
        call groove_nlg_notify1
        pop ebp
        pop ecx
        pop ebx
        leave
        ret 0ch
    }
}

/* Original x87 helper at 0x00568475.  EDX points to an IEEE double; finite values
 * are loaded directly, while NaN/Inf are normalized into the x87 extended format. */
__declspec(naked) uint __cdecl __fload_withFB(void)
{
    __asm {
        mov eax, dword ptr [edx + 4]
        and eax, 7ff00000h
        cmp eax, 7ff00000h
        je load_special
        fld qword ptr [edx]
        ret
    load_special:
        mov eax, dword ptr [edx + 4]
        sub esp, 0ah
        or eax, 7fff0000h
        mov dword ptr [esp + 6], eax
        mov eax, dword ptr [edx + 4]
        mov ecx, dword ptr [edx]
        shld eax, ecx, 0bh
        shl ecx, 0bh
        mov dword ptr [esp + 4], eax
        mov dword ptr [esp], ecx
        fld tbyte ptr [esp]
        add esp, 0ah
        test eax, 0
        mov eax, dword ptr [edx + 4]
        ret
    }
}

/* Original x87/fastcall prologue at 0x005683E7.  It spills ST(0), stages the
 * implicit ECX/EDX arguments and restores the caller's control word/result. */
__declspec(naked) float10 __cdecl __startOneArgErrorHandling(void)
{
    __asm {
        push ebp
        mov ebp, esp
        add esp, -20h
        mov dword ptr [ebp - 20h], eax
        fstp qword ptr [ebp - 8]
        mov dword ptr [ebp - 1ch], ecx
        mov eax, dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ebp - 18h], eax
        mov dword ptr [ebp - 14h], ecx
        lea eax, dword ptr [ebp + 8]
        lea ecx, dword ptr [ebp - 20h]
        push eax
        push ecx
        push edx
        call sub_56B8FB
        add esp, 0ch
        fld qword ptr [ebp - 8]
        cmp word ptr [ebp + 8], 27fh
        je control_word_ready
        fldcw word ptr [ebp + 8]
    control_word_ready:
        leave
        ret
    }
}
