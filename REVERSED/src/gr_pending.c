/* gr_pending.c - ports that reference callees which are not reversed yet.
 *
 * This file is compiled (so tools/bytecheck.py can still compare the machine
 * code against the original) but is deliberately NOT linked into
 * build/groove_rebuild.exe, because the undefined callee would break the link.
 * Move a function out of here and into the matching gr_*.c file once its
 * callees exist.
 *
 * Keeping these translations recorded matters: the body is already known, and
 * the verdict it gets today is a useful datum about the code generator.
 */
#include "groove.h"

/* ---- not reversed yet, declared only to keep the translation compiling ---- */
void sub_40D970(void *target);   /* 0x40D970, 512 bytes - TODO */

/* 0x40DB70  `push &byte_6D9858; call sub_40D970; push &byte_6D94E8; call
 *            sub_40D970; add esp, 8`
 *
 * Re-registers two per-object records by passing the address of the two globals
 * to the same setter.  Those globals are cleared by sub_40D900 / sub_40D910,
 * which are already ported. */
void sub_40DB70(void)
{
    sub_40D970(&byte_6D9858);
    sub_40D970(&byte_6D94E8);
}
