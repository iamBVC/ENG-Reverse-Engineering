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
 * Also stubs `sub_562941`, which the MAP loader calls once at the end to release a
 * scratch block: a no-op is harmless for a one-shot driver, and it avoids pulling
 * in sub_5628BC's closure.
 *
 * This file is a *harness* device, like the import stubs: it substitutes I/O
 * primitives, not the logic under test.
 */
#include "ghidra_shim.h"

#include <stdio.h>
#include <stdlib.h>

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
    (void)block;   /* releasing a scratch list: a no-op here */
}

/* The MAP loader allocates its scratch tile list with the C++ operator new, which
 * Ghidra prints by its demangled name. */
void *operator_new(unsigned int size)
{
    return malloc((size_t)size);
}

/* Ghidra kept the `call __ftol` sites of the *greyscale* colour path but lost the
 * x87 operands they consumed (see BODY_PATCHES in make_verify_subset.py).  The
 * driver runs with the greyscale switch (0x6D7C61) set, so those paths are never
 * taken; this exists only so the code links.  The two x87 conversions that DO run
 * - the tile cell index - are patched back to real expressions instead. */
int groove_ftol(void)
{
    return 0;
}
