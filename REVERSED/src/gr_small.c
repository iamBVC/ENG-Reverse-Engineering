/* gr_small.c - batch 1 of the small leaf game functions.
 *
 * Every entry here is a real function of the game (no ILT thunks, no CRT) that
 * is self-contained or only calls the CRT, so the whole batch links without
 * pulling in unfinished work.  Each one carries its original address and the
 * reasoning behind the C translation.
 *
 * Calling-convention notes:
 *   cdecl    arguments on the stack, caller cleans up (`retn`)
 *   thiscall `this` in ECX, remaining arguments on the stack, callee cleans up
 *            (`retn 4`).  MSVC accepts `__thiscall` on free functions in C.
 */
#include "groove.h"

#include <string.h>

/* 0x406E30  `mov dword_581158, 0 / retn`
 * Clears a global.  No argument, so the C is exact. */
void sub_406E30(void)
{
    dword_581158 = 0;
}

/* 0x408390  `mov eax, [esp+arg_C] / mov byte ptr [eax], 0FFh / retn`
 * Writes 0xFF through the 4th argument.  The first three arguments are never
 * touched, so they stay unnamed in the signature. */
void sub_408390(int arg_0, int arg_4, int arg_8, unsigned char *arg_C)
{
    (void)arg_0;
    (void)arg_4;
    (void)arg_8;
    *arg_C = 0xFF;
}

/* 0x40D900  clears byte_6D9858 */
void sub_40D900(void)
{
    byte_6D9858 = 0;
}

/* 0x40D910  clears byte_6D94E8 */
void sub_40D910(void)
{
    byte_6D94E8 = 0;
}

/* 0x40E020  `fld ds:flt_56E008 / fdiv ds:flt_56E1A0 / fstp flt_581970`
 * flt_56E008 is 1.0 and flt_56E1A0 is 0.01, so this stores 100.0. */
void sub_40E020(void)
{
    flt_581970 = flt_56E008 / flt_56E1A0;
}

/* 0x40E0A0  two `rep stosd` blocks: 0x100 dwords then 0x0F dwords.
 * `rep stosd` is how MSVC expands a memset with a constant size, so these were
 * almost certainly memset() calls in the original source. */
void sub_40E0A0(void)
{
    /* Written as loops on purpose.  MSVC 6 expanded these to inline `rep stosd`
     * (`mov ecx,0x100 / xor eax,eax / mov edi,offset dword_58226C / rep stosd`);
     * MSVC 2022 emits calls to memset() instead, so the bytes differ either way
     * - the loops document what the original really does. */
    unsigned int *p = dword_58226C;
    int n = 0x100;
    do {
        *p++ = 0;
    } while (--n);
    p = unk_5821E0;
    n = 0x0F;
    do {
        *p++ = 0;
    } while (--n);
}

/* 0x40E610  `sprintf(Buffer, "BUTTON %d", arg_0 + 1)`
 * Formats a button label; the +1 converts a zero-based index to a display
 * number. */
void sub_40E610(int index, char *Buffer)
{
    sprintf(Buffer, "BUTTON %d", index + 1);
}

/* 0x4136C0  `return a[3] - *b;`
 * Field at +0x0C of the first object minus the first dword of the second. */
int sub_4136C0(int *a, int *b)
{
    return a[3] - *b;
}

/* 0x413B10  `mov dword ptr [ecx], offset off_56E1C8 / retn`
 * thiscall setter: stores the address of a data label into the object's first
 * dword (a vtable/function-table pointer). */
void __fastcall sub_413B10(void *self)
{
    /* `offset off_56E1C8`: the address of the label, not its value. */
    *(void **)self = (void *)&off_56E1C8;
}

/* 0x4155E0  clears dword_583740 */
void sub_4155E0(void)
{
    dword_583740 = 0;
}

/* 0x41BCB0  thiscall: zero +0x24 then +0x20, return `this`
 * Note the store order (0x24 before 0x20) - it is reproduced deliberately. */
void *__fastcall sub_41BCB0(void *self)
{
    *(unsigned int *)((unsigned char *)self + 0x24) = 0;
    *(unsigned int *)((unsigned char *)self + 0x20) = 0;
    return self;
}

/* 0x41D330  clears two adjacent globals through eax */
void sub_41D330(void)
{
    dword_586408 = 0;
    dword_58640C = 0;
}

/* 0x41E1B0  `dword_586420 = dword_584644` */
void sub_41E1B0(void)
{
    dword_586420 = dword_584644;
}

/* 0x4255A0  `mov eax, 1 / retn` - a constant-true predicate. */
int sub_4255A0(void)
{
    return 1;
}

/* 0x426860  `xor eax, eax / retn` - a constant-false predicate.  Worth
 * remembering when tracing feature gates: this returns 0 unconditionally. */
int sub_426860(void)
{
    return 0;
}

/* 0x40FC90  thiscall with one stack argument and `retn 4`.
 *
 *   mov eax, ecx           ; return value = this
 *   mov ecx, [esp+arg_0]   ; source object
 *   mov edx, [ecx+4]
 *   mov [eax],   off_56E1C4
 *   mov [eax+4], edx
 *   retn 4
 *
 * MSVC cannot declare this convention on a free function, and __fastcall would
 * move the second argument into EDX, so the sequence is emitted verbatim.  This
 * is a C++ member function in the original: until the owning class is reversed,
 * callers cannot be regenerated with a matching convention, which is why
 * host_main.c does not call it (the byte check still covers it). */
void __declspec(naked) sub_40FC90(void *self, const void *src)
{
    (void)self;
    (void)src;
    __asm {
        mov     eax, ecx
        mov     ecx, [esp+4]
        mov     edx, [ecx+4]
        mov     dword ptr [eax], offset off_56E1C4
        mov     [eax+4], edx
        retn    4
    }
}
