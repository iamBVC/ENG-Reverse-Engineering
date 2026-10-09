/* wrappers_bulk.c - the harness wrappers, over the *whole bulk*.
 *
 * `verify_subset.c` exists because the full decompiled program could not be linked:
 * it contains 13 functions plus their dependencies, and the drivers and the
 * differential harness run against that.  Now that the bulk compiles without an
 * error (968 of 968 functions, measured) the same wrappers can call into it, so the
 * tests exercise the rebuild instead of a curated sample of it - same drivers, same
 * verifier, different code under test.
 *
 * The names are identical to the ones `verify_subset.c` exports (that is what
 * harness\verify.c and the two drivers look up), and the bodies follow the same
 * rules: one explicit, cdecl signature per function, because the decompiled
 * prototypes are deliberately loose and some originals are __fastcall/__thiscall.
 *
 * Build with:  harness\build_dlls.bat bulk
 */
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"

#define WH_EXPORT __declspec(dllexport)

/* ---- primary / secondary bump allocators -------------------------------- */
WH_EXPORT void *wh_sub_41EF00(int size) { return (void *)sub_41EF00(size); }
WH_EXPORT void  wh_sub_41EEE0(void) { sub_41EEE0(); }
WH_EXPORT void *wh_sub_41ED90(int size) { return (void *)sub_41ED90(size); }

/* ---- pure helpers ------------------------------------------------------ */
WH_EXPORT int wh_sub_4136C0(int a, int b) { return sub_4136C0(a, b); }
WH_EXPORT int wh_sub_4255A0(void) { return sub_4255A0(); }
WH_EXPORT int wh_sub_426860(void) { return sub_426860(); }

/* ---- functions that only move globals --------------------------------- */
WH_EXPORT void wh_sub_406E30(void) { sub_406E30(); }
WH_EXPORT void wh_sub_4155E0(void) { sub_4155E0(); }
WH_EXPORT void wh_sub_41D330(void) { sub_41D330(); }
WH_EXPORT void wh_sub_41E1B0(void) { sub_41E1B0(); }
WH_EXPORT void wh_sub_40E0A0(void) { sub_40E0A0(); }

/* ---- the two real-data loaders ---------------------------------------- */
WH_EXPORT int wh_sub_5563F0(void *cursor_slot, int record_count, void *out_records)
{
    return sub_5563F0((int *)cursor_slot, record_count, (int *)out_records);
}

WH_EXPORT void wh_sub_42AC50(void *world, void *stream)
{
    sub_42AC50((uint *)world, (undefined4)(size_t)stream);
}
