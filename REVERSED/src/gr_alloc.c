/* gr_alloc.c - the two bump allocators and the primary block manager.
 *
 * Original addresses:
 *   sub_41ED90  secondary heap bump allocator   (cursor dword_58656C, remaining dword_586570)
 *   sub_41EEA0  primary heap: free + `operator new(0x1000000)`, then reset
 *   sub_41EEE0  primary heap: reset cursor to block base
 *   sub_41EF00  primary heap bump allocator     (cursor dword_586584, remaining dword_586588)
 *
 * Notes for matching:
 *   * the limits are compared with `jle`/`jge`, i.e. they are SIGNED ints
 *   * the original calls the MSVC C++ runtime `operator delete` (`??3@YAXPAX@Z`)
 *     and `operator new` (`??2@YAPAXI@Z`).  This C build uses free()/malloc(),
 *     which is behaviourally equivalent; see REVERSED/README.md for why a
 *     byte-identical call target would need the original toolchain/libraries.
 *   * neither allocator zeroes memory.
 */
#include "groove.h"

#include <stdlib.h>

/* ---- primary heap globals (definition site) ------------------------------ */
unsigned char *dword_586580 = 0;   /* block base */
unsigned char *dword_586584 = 0;   /* cursor     */
int            dword_586588 = 0;   /* remaining  */

/* ---- secondary heap globals ---------------------------------------------- */
unsigned char *dword_58656C = 0;   /* cursor     */
int            dword_586570 = 0;   /* remaining  */

#define GROOVE_BLOCK_SIZE 0x1000000   /* 16 MB, literal push 1000000h */

/* -------------------------------------------------------------------------- */
void *sub_41ED90(int size)
{
    if (size > dword_586570)
        return 0;
    {
        unsigned char *p = dword_58656C;
        dword_58656C = p + size;
        dword_586570 -= size;
        return p;
    }
}

/* -------------------------------------------------------------------------- */
void sub_41EEA0(void)
{
    if (dword_586580)
        free(dword_586580);
    dword_586580 = (unsigned char *)malloc(GROOVE_BLOCK_SIZE);
    if (!dword_586580)
        return;
    dword_586584 = dword_586580;
    dword_586588 = GROOVE_BLOCK_SIZE;
}

/* -------------------------------------------------------------------------- */
void sub_41EEE0(void)
{
    unsigned char *base = dword_586580;
    dword_586588 = GROOVE_BLOCK_SIZE;
    dword_586584 = base;
}

/* -------------------------------------------------------------------------- */
void *sub_41EF00(int size)
{
    if (size > dword_586588)
        return 0;
    {
        unsigned char *p = dword_586584;
        dword_586584 = p + size;
        dword_586588 -= size;
        return p;
    }
}
