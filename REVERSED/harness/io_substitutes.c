/* io_substitutes.c - the four fread wrappers for the driver-side DLL.
 *
 * The decompiled bodies of these four call the binary's *own* copy of fread
 * (Ghidra named it sub_5629E6), which drags in the whole in-binary CRT.  They are
 * semantically trivial and already byte-verified on the hand-ported side, so the
 * harness compiles those implementations here instead:
 *
 *   sub_415A90(Stream, Buffer, ElementSize) -> fread(Buffer, ElementSize, 1, Stream)
 *   sub_415AD0(Stream, Buffer)              -> fread(Buffer, 1, 1, Stream)
 *   sub_415AB0(Stream, Buffer)              -> fread(Buffer, 4, 1, Stream)
 *   sub_415AF0(Stream, Buffer)              -> fread(Buffer, 2, 1, Stream)
 *
 * `sub_562941` is implemented here as the game's one-argument free wrapper.  The
 * MAP loader and exception cleanup paths pass allocations made by the compatible
 * allocator below, so release them through the matching CRT heap.
 *
 * This file is a *harness* device, like the import stubs: it substitutes I/O
 * primitives, not the logic under test.
 */
#include "ghidra_shim.h"

#include <stdio.h>
#include <stdlib.h>

void sub_5628BC(void *block);

int sub_415A90(void *Stream, void *Buffer, int ElementSize)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, (size_t)ElementSize, 1, (FILE *)Stream);
}

int sub_415AD0(void *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 1, 1, (FILE *)Stream);
}

int sub_415AB0(void *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 4, 1, (FILE *)Stream);
}

int sub_415AF0(void *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 2, 1, (FILE *)Stream);
}

void sub_562941(void *block)
{
    sub_5628BC(block);
}

/* The MAP loader allocates its scratch tile list with the C++ operator new, which
 * Ghidra prints by its demangled name. */
void *operator_new(unsigned int size)
{
    return malloc((size_t)size);
}

/* Ghidra kept the `call __ftol` sites of the *greyscale* colour path but lost the
 * x87 operands they consumed (see BODY_PATCHES in make_verify_subset.py).  Preserve
 * the original helper contract for callers that leave their value in ST(0): FISTP
 * uses the active x87 rounding mode and pops the converted value. */
int groove_ftol(void)
{
    int converted;
    __asm { fistp dword ptr [converted] }
    return converted;
}
