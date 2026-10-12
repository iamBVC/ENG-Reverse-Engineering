/* crt_aliases.c - real implementations for the CRT calls the decompiled code names
 * the MSVC 6 way.
 *
 * These are not "missing game code": they are the C runtime.  A stub would be worse
 * than useless here - a stubbed `_malloc` returns NULL for every allocation and a
 * stubbed `_strlen` returns 0 - so they are mapped onto the modern CRT instead.
 *
 * Two of them cannot be expressed as a C function at all, because MSVC 6 gave them an
 * x87 calling convention (argument on the FPU stack, result in EAX / back on the FPU
 * stack).  Those are written with __asm, which is the only way to honour the contract
 * the call sites were generated against:
 *
 *   __ftol   ST(0) -> EAX (truncating, and it pops the FPU stack)
 *   __frnd   ST(0) -> ST(0), rounded to an integer
 *
 * Everything else is on the symbol list in src_generated/link_stubs.csv as a stub,
 * with the ones that would silently compute the wrong thing called out there.
 */
#include "ghidra_shim.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

/* ---- the portable default path ----------------------------------------
 * The 2001 game gets its data paths from the installer's registry keys
 * (`Software\Disney Interactive\Emperors New Groove\1.0`), and when a key is missing the
 * settings reader returns the caller's default - which every call site passes as 0.
 * `sprintf("%s")` on that 0 faults, in this CRT and in the 2001 one, so a machine without
 * the installer never starts the game (checked: the shipped exe does not start here
 * either).  A static recompilation should not need an installer at all, so the path-shaped
 * reads default to "." - the process working directory, which exe_main.c sets to the
 * executable's own folder.  Nothing machine-specific is required to run it. */
char groove_default_path[] = ".";

/* ---- allocation ------------------------------------------------------- */
void *_malloc(size_t n) { return malloc(n); }
void  _free(void *p) { free(p); }

/* `operator_new` belongs here as much as malloc does, but harness/io_substitutes.c
   defines its own copy (backed by malloc) for the two harness builds, and two
   definitions of one symbol is a link error - so the harness build defines the guard
   below on its command line and this file only supplies the exe's copy. */
#ifndef GROOVE_IO_SUBSTITUTES
void *operator_new(unsigned int n) { return malloc(n); }
#endif

/* ---- memory / string --------------------------------------------------- */
void *_memset(void *d, int c, size_t n) { return memset(d, c, n); }
void *_memcpy(void *d, const void *s, size_t n) { return memcpy(d, s, n); }
void *_memmove(void *d, const void *s, size_t n) { return memmove(d, s, n); }
size_t _strlen(const char *s) { return strlen(s); }
int _strcmp(const char *a, const char *b) { return strcmp(a, b); }
int _strncmp(const char *a, const char *b, size_t n) { return strncmp(a, b, n); }
char *_strncpy(char *d, const char *s, size_t n) { return strncpy(d, s, n); }
int _strcmpi(const char *a, const char *b) { return _stricmp(a, b); }
char *_strrchr(const char *s, int c) { return strrchr(s, c); }

/* ---- x87 math helpers -------------------------------------------------- */
/* Named `fcos`/`fsin`, not `_fcos`/`_fsin`: MSVC decorates a C name with one leading
   underscore, so the identifier that produces the symbol `_fcos` is `fcos` (the linker
   log is the evidence - it lists the decorated form). */
double fcos(double x) { return cos(x); }
double fsin(double x) { return sin(x); }

/* ---- the MSVC 6 stack probe -------------------------------------------
 * IDA's listing names the call: `sub_405960` calls `__alloca_probe` where the decompiled
 * body calls `sub_562840()`.  A rebuild does not need it - the modern compiler emits its
 * own probe for a frame that size, and the callers only ever call it for that - so the
 * faithful implementation here is a no-op.  It is the first of the Ghidra-only stubs in
 * the CRT region whose *name* can be recovered from the listing's call sites. */
void sub_562840(void) { }

/* ---- the reversed CRT bodies, mapped onto the modern CRT ---------------
 * IDA names these call targets `_fopen` / `_fwrite` / `_fclose`; Ghidra decompiled the
 * *bodies* as ordinary `sub_XXXX` functions.  They cannot work in a rebuild: they use the
 * MSVC 6 FILE layout (offset 0x0C is `_flag`, 0x10 `_file`) and the 2001 CRT's `_iob`
 * table and heap, none of which a modern `fopen` produces.  This is what faults on the
 * game's first save write (`sub_41C050`): the reversed `fclose` writing through a FILE the
 * rebuild's own fopen never made.
 *
 * Mapping the calls onto the modern CRT is the correct answer - the same decision already
 * taken for `_malloc`/`_strlen` and for the C++ runtime - and the bodies are excluded from
 * the build in harness/substituted.txt so there is exactly one definition of each. */
void  *sub_562AEE(const char *path, const char *mode) { return fopen(path, mode); }
size_t sub_562B75(void *buf, size_t size, size_t count, void *stream)
{
    return fwrite(buf, size, count, (FILE *)stream);
}
int    sub_5628EB(void *stream) { return fclose((FILE *)stream); }
/* The reversed `sprintf` body (IDA names the call `_sprintf`).  Same argument as above, and
 * the same fix - and it matters here because the format is "\\sking%d.ksv" with a string
 * straight out of the registry: the 2001 body walks that value itself. */
int    sub_562717(char *buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    return vsprintf(buf, fmt, ap);
}

/* ---- x87 conversions: their convention is the point -------------------- */
int __declspec(naked) __ftol()
{
    __asm {
        sub     esp, 8
        fistp   qword ptr [esp]     /* the operand is already on the FPU stack */
        mov     eax, dword ptr [esp]
        add     esp, 8
        ret
    }
}

float10 __declspec(naked) __frnd()
{
    __asm {
        fld     qword ptr [esp+4]   /* the operand, if the call site passed one */
        frndint                     /* round ST(0) in place */
        ret                         /* the result is already in ST(0) */
    }
}
