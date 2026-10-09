/* ghidra_shim.h - the typedefs and intrinsics Ghidra's decompiler output needs.
 *
 * Ghidra emits C that uses its own pseudo-types (`undefined4`, `uint`, ...) and
 * bit-manipulation macros (`CONCAT31`, `SUB87`, ...).  This header supplies them
 * so the decompiled sources can be fed to a real compiler.
 *
 * Two deliberate choices:
 *   * `code` is defined as an *unprototyped* function type (`void code();`).
 *     Ghidra uses it both as `code *` (function pointer) and as `(code *)` casts
 *     that are then called with arguments, which C rejects for a prototyped
 *     `void (void)`.  This is why the generated bulk translation unit is
 *     compiled as C, not C++.
 *   * CONCATxy concatenates an x-byte high part with a y-byte low part, and
 *     SUBxy extracts the y-byte piece of an x-byte value starting at byte b -
 *     the bit patterns have to match what the original instructions produced,
 *     so every macro masks before shifting.
 */
#ifndef GHIDRA_SHIM_H
#define GHIDRA_SHIM_H

#include <stddef.h>
#include <stdint.h>

/* The decompiled code calls Win32 APIs and uses their types (DWORD, PVOID,
 * HANDLE, RaiseException, RtlUnwind, ...).  Lean out windows.h and keep its
 * min/max macros out of the way. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

/* `NAN` is how the decompiler prints a NaN float constant, and the CRT internals
 * below are called by the binary's own string/float code.  Declaring them here is
 * cheaper than reversing them, and they are the last few C2065 names left. */
#ifndef __cplusplus
#include <math.h>
#endif
void __cfltcvt(void);
void __fassign(void);
struct type_info;

/* Ghidra models the SEH chain head (FS:[0]) as a plain global.  A plain global
 * is NOT faithful: the real slot lives in the TIB, so the decompiled
 * exception-registration sequences (34 functions, plus the `Catch@...`
 * handlers) will not work until this is replaced with a real FS:[0] accessor.
 * Everything else in those functions is fine.  See REVERSED/README.md. */
extern void *ExceptionList;

/* MSVC's internal SEH record, referenced by `_exception(exception *this)`. */
typedef struct exception exception;

/* `__thiscall` cannot be declared on a free function in MSVC (C3865).  Compiled
 * as C, the whole bulk translation unit agrees on the convention anyway, so the
 * keyword is simply dropped.  (C++ files of the hand-ported track never include
 * this header.) */
#ifndef __cplusplus
#define __thiscall
#endif

/* Windows structs Ghidra emitted with a leading underscore. */
typedef STARTUPINFOA        _STARTUPINFOA;
typedef OSVERSIONINFOA      _OSVERSIONINFOA;
typedef SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES;
typedef CPINFO              _cpinfo;
typedef EXCEPTION_POINTERS  _EXCEPTION_POINTERS;
/* Ghidra prefixes a type when it cannot name it; these are the Win32 ones the
 * decompiled code actually mentions (each aliased to the system definition). */
/* Ghidra's own layout for this one: it names the anonymous struct member `s`, which
 * the system LARGE_INTEGER does not, so aliasing it left `.s.LowPart` an error. */
typedef struct { unsigned int LowPart; int HighPart; } groove_lowhigh;
typedef struct { groove_lowhigh s; groove_lowhigh u; long long QuadPart; } _LARGE_INTEGER;
/* Ghidra models a handle as a struct with an `unused` member (it prints
 * `local_7c[0].unused = 0x7c`), so alias it to that shape rather than to HDC. */
typedef struct { int unused; } HDC__;
typedef HWND                HWND__;
typedef HINSTANCE           HINSTANCE__;
typedef struct tagMSG       tagMSG;
typedef struct tagPOINT     tagPOINT;
typedef struct tagRECT      tagRECT;
typedef void                *LPUNKNOWN;

/* Ghidra's packed-integer pseudo-types beyond the common ones. */
typedef unsigned int        unkuint10;
typedef unsigned int        unkbyte10;

/* Sub-field access for Ghidra's `value._<offset>_<size>_` idiom: the decompiler
 * names an unnamed field by its byte offset and size.  Sizes 1/2/4 map onto real
 * integer lvalues; a 3-byte field has no native type, so it is read/written as
 * three bytes (G_WR3 is statement-level, see tools/make_bulk.py). */
#define G_BYTE(x,n)  (*(unsigned char  *)((char *)&(x) + (n)))
#define G_WORD(x,n)  (*(unsigned short *)((char *)&(x) + (n)))
#define G_DWORD(x,n) (*(unsigned int   *)((char *)&(x) + (n)))
#define G_RD3(x,n)   ((unsigned int)(G_BYTE(x,n) | ((unsigned int)G_BYTE(x,n+1) << 8) \
                                    | ((unsigned int)G_BYTE(x,n+2) << 16)))
#define G_WR3(x,n,v) do { unsigned int groove_v_ = (unsigned int)(v); \
                          G_BYTE(x,n)     = (unsigned char)groove_v_; \
                          G_BYTE(x,n+1)   = (unsigned char)(groove_v_ >> 8); \
                          G_BYTE(x,n+2)   = (unsigned char)(groove_v_ >> 16); } while (0)

/* ---- pseudo-types -------------------------------------------------------- */
typedef unsigned char      undefined;
typedef unsigned char      undefined1;
typedef unsigned short     undefined2;
typedef unsigned int       undefined3;   /* packed 3/5/6-byte values: held in a register */
typedef unsigned int       undefined4;
typedef unsigned int       undefined5;
typedef unsigned int       undefined6;
typedef unsigned long long undefined8;
typedef unsigned int       uint3;
typedef unsigned int       uint5;
typedef unsigned int       uint6;
typedef int                int3;
typedef int                int5;
typedef long double        float10;      /* x87 80-bit value */

typedef unsigned char      byte;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ulonglong;
typedef long long          longlong;

/* `code` returns int, not void: the decompiler assigns the result of indirect
 * calls through `code *` (e.g. vtable slots), which is a C2186 error if the
 * type returns void.  The value is discarded where the callee really returns
 * void, so the looser type is harmless. */
typedef int                code();

/* The binary's own `FILE`.  `<stdio.h>` cannot supply it: the installed CRT declares
 * `FILE` as an opaque `struct { void *_Placeholder; }`, so the member accesses inside
 * `sub_5628EB` (the body of `fclose`, 0x5628EB) do not compile against it - and
 * defining `_CRT_INTERNAL_NONSTDC_NAMES` does not bring `_file`/`_tmpfname` back in
 * this SDK release either (measured: `_file` and `_tmpfname` are still not members).
 *
 * So the struct below is the *binary's* layout (MSVC 6), taken from the code itself:
 *     8b 46 0c a8 40      mov eax,[esi+0Ch]; test al,40h     -> _flag  at 0x0C
 *     ff 76 10            push dword ptr [esi+10h]          -> _file  at 0x10
 * (sub_5628EB offsets +10 and +38/42, read out of groove.exe). */
typedef struct groove_FILE {
    char *_ptr;         /* +0x00 */
    int   _cnt;         /* +0x04 */
    char *_base;        /* +0x08 */
    int   _flag;        /* +0x0C */
    int   _file;        /* +0x10 */
    int   _charbuf;     /* +0x14 */
    int   _bufsiz;      /* +0x18 */
    char *_tmpfname;    /* +0x1C */
} groove_FILE;

/* ... and the layout is asserted, so a later edit cannot silently shift a field and
 * have the decompiled code read the wrong slot (negative array size = error). */
typedef char groove_FILE_layout_check[
    (offsetof(groove_FILE, _ptr) == 0x00 && offsetof(groove_FILE, _cnt) == 0x04 &&
     offsetof(groove_FILE, _base) == 0x08 && offsetof(groove_FILE, _flag) == 0x0C &&
     offsetof(groove_FILE, _file) == 0x10 && offsetof(groove_FILE, _bufsiz) == 0x18 &&
     offsetof(groove_FILE, _tmpfname) == 0x1C) ? 1 : -1];

typedef int                bool32;

/* ---- CONCATxy(high, low) ------------------------------------------------- */
#define CONCAT11(a,b) ((unsigned short)((((unsigned int)(a) & 0xffu) << 8)  | ((unsigned int)(b) & 0xffu)))
#define CONCAT12(a,b) ((unsigned int)((((unsigned int)(a) & 0xffu) << 16) | ((unsigned int)(b) & 0xffffu)))
#define CONCAT13(a,b) ((unsigned int)((((unsigned int)(a) & 0xffu) << 24) | ((unsigned int)(b) & 0xffffffu)))
#define CONCAT14(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffull) << 32) | ((unsigned long long)(b) & 0xffffffffull)))
#define CONCAT15(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffull) << 40) | ((unsigned long long)(b) & 0xffffffffffull)))
#define CONCAT16(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffull) << 48) | ((unsigned long long)(b) & 0xffffffffffffull)))
#define CONCAT17(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffull) << 56) | ((unsigned long long)(b) & 0xffffffffffffffull)))
#define CONCAT21(a,b) ((unsigned int)((((unsigned int)(a) & 0xffffu) << 8)  | ((unsigned int)(b) & 0xffu)))
#define CONCAT22(a,b) ((unsigned int)((((unsigned int)(a) & 0xffffu) << 16) | ((unsigned int)(b) & 0xffffu)))
#define CONCAT23(a,b) ((unsigned int)((((unsigned int)(a) & 0xffffu) << 24) | ((unsigned int)(b) & 0xffffffu)))
#define CONCAT24(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffull) << 32) | ((unsigned long long)(b) & 0xffffffffull)))
#define CONCAT25(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffull) << 40) | ((unsigned long long)(b) & 0xffffffffffull)))
#define CONCAT26(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffull) << 48) | ((unsigned long long)(b) & 0xffffffffffffull)))
#define CONCAT27(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffull) << 56) | ((unsigned long long)(b) & 0xffffffffffffffull)))
#define CONCAT28(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffull) << 56) | ((unsigned long long)(b) & 0xffffffffffffffull)))
#define CONCAT31(a,b) ((unsigned int)((((unsigned int)(a) & 0xffffffu) << 8)  | ((unsigned int)(b) & 0xffu)))
#define CONCAT32(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffull) << 16) | ((unsigned long long)(b) & 0xffffull)))
#define CONCAT33(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffull) << 24) | ((unsigned long long)(b) & 0xffffffull)))
#define CONCAT34(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffull) << 32) | ((unsigned long long)(b) & 0xffffffffull)))
#define CONCAT41(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffffull) << 8)  | ((unsigned long long)(b) & 0xffull)))
#define CONCAT42(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffffull) << 16) | ((unsigned long long)(b) & 0xffffull)))
#define CONCAT43(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffffull) << 24) | ((unsigned long long)(b) & 0xffffffull)))
#define CONCAT44(a,b) ((unsigned long long)((((unsigned long long)(a) & 0xffffffffull) << 32) | ((unsigned long long)(b) & 0xffffffffull)))
#define CONCAT51(a,b) CONCAT41(a,b)
#define CONCAT61(a,b) CONCAT41(a,b)
#define CONCAT81(a,b) CONCAT41(a,b)

/* ---- SUBxy(value, byteIndex) -------------------------------------------- */
#define SUB10(a,b)    ((unsigned char)(((unsigned short)(a) >> ((b) * 8)) & 0xffu))
#define SUB20(a,b)    ((unsigned short)(((unsigned int)(a) >> ((b) * 8)) & 0xffffu))
#define SUB41(a,b)    ((unsigned char)(((unsigned int)(a) >> ((b) * 8)) & 0xffu))
#define SUB42(a,b)    ((unsigned short)(((unsigned int)(a) >> ((b) * 8)) & 0xffffu))
#define SUB84(a,b)    ((unsigned int)(((unsigned long long)(a) >> ((b) * 8)) & 0xffffffffull))
#define SUB87(a,b)    ((unsigned int)(((unsigned long long)(a) >> ((b) * 8)) & 0xffffffffull))

/* ---- ZEXT / SEXT -------------------------------------------------------- */
#define ZEXT14(a)     ((unsigned int)((unsigned char)(a)))
#define ZEXT24(a)     ((unsigned int)((unsigned short)(a)))
#define ZEXT12(a)     ((unsigned short)((unsigned char)(a)))
#define SEXT14(a)     ((int)((char)(a)))
#define SEXT24(a)     ((int)((short)(a)))
#define SEXT12(a)     ((short)((char)(a)))
#define SEXT18(a)     ((long long)((char)(a)))

/* ---- carry / overflow helpers ------------------------------------------- */
#define __CFADD__(a,b)  (((unsigned int)(a) + (unsigned int)(b)) < (unsigned int)(a))
#define __CFSUB__(a,b)  ((unsigned int)(a) < (unsigned int)(b))
#define __OFADD__(a,b)  (0)
#define __OFSUB__(a,b)  (0)
#define __PAIR64__(hi,lo) (((unsigned long long)(hi) << 32) | (unsigned int)(lo))

#endif /* GHIDRA_SHIM_H */
