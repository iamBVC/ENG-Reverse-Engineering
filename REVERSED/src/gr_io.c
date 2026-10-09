/* gr_io.c - the tiny fread wrappers every chunk loader uses.
 *
 * Original addresses:
 *   sub_415A90  fread(Buffer, ElementSize, 1, Stream)
 *   sub_415AD0  fread(Buffer, 1, 1, Stream)
 *   sub_415AB0  fread(Buffer, 4, 1, Stream)
 *   sub_415AF0  fread(Buffer, 2, 1, Stream)
 *
 * All four share one shape in the original: load Stream, `test eax,eax`/
 * `jz`, read the remaining arguments, push (Stream, 1, size, Buffer) and
 * tail into _fread, returning its result.  A NULL stream returns 0 because
 * eax still holds the NULL Stream at the shared `retn`.
 */
#include "groove.h"

int sub_415A90(FILE *Stream, void *Buffer, int ElementSize)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, (size_t)ElementSize, 1, Stream);
}

int sub_415AD0(FILE *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 1, 1, Stream);
}

int sub_415AB0(FILE *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 4, 1, Stream);
}

int sub_415AF0(FILE *Stream, void *Buffer)
{
    if (!Stream)
        return 0;
    return (int)fread(Buffer, 2, 1, Stream);
}
