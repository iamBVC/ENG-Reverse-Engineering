#include "ghidra_shim.h"

/* This original catch body is byte-for-byte covered by the recovered handler
 * for sub_410700; tail-dispatch keeps the incoming owner's EBP and stack. */
extern int __cdecl groove_catch_handler_impl(void);

__declspec(naked) undefined1 *Catch_00410e52(void)
{
    __asm {
        jmp groove_catch_handler_impl
    }
}
