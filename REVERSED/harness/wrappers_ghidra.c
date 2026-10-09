/* wrappers_ghidra.c - cdecl shims over the *Ghidra-decompiled* functions.
 *
 * A script (tools/verify.py) loads this DLL and the hand-ported one and compares
 * their behaviour, so the exported wrapper names must be identical in both.
 *
 * Two reasons the wrappers exist:
 *   - some originals are __fastcall / __thiscall (ECX-passed `this`), which
 *     ctypes cannot express;
 *   - the decompiled prototypes are deliberately loose (see make_bulk.py), so a
 *     wrapper gives the harness one stable, explicit signature per function.
 *
 * Only functions whose behaviour is observable through arguments and return
 * values are wrapped here.  Functions that only touch a global cannot be
 * compared this way; those are covered by the byte comparison instead.
 */
#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include "ghidra_prototypes.h"

#define WH_EXPORT __declspec(dllexport)

/* ---- primary/secondary bump allocators ---------------------------------- */
WH_EXPORT void *wh_sub_41EF00(int size) { return (void *)sub_41EF00(size); }
WH_EXPORT void  wh_sub_41EEA0(void) { sub_41EEA0(); }
WH_EXPORT void  wh_sub_41EEE0(void) { sub_41EEE0(); }
WH_EXPORT void *wh_sub_41ED90(int size) { return (void *)sub_41ED90(size); }

/* ---- fread wrappers ---------------------------------------------------- */
/* Ghidra decompiled these four as returning void: it did not track that the
   original leaves fread()'s result in eax.  They therefore report 0 here, and
   verify.py compares their *effect* (bytes consumed from the stream) instead of
   the return value.  The hand-ported side does return the real value - that gap is
   one of the things the harness is supposed to surface. */
WH_EXPORT int wh_sub_415A90(void *stream, void *buffer, int size)
{ sub_415A90(stream, buffer, size); return 0; }
WH_EXPORT int wh_sub_415AD0(void *stream, void *buffer) { sub_415AD0(stream, buffer); return 0; }
WH_EXPORT int wh_sub_415AB0(void *stream, void *buffer) { sub_415AB0(stream, buffer); return 0; }
WH_EXPORT int wh_sub_415AF0(void *stream, void *buffer) { sub_415AF0(stream, buffer); return 0; }

/* ---- pure helpers ------------------------------------------------------ */
WH_EXPORT int wh_sub_4136C0(int a, int b) { return sub_4136C0(a, b); }
WH_EXPORT int wh_sub_4255A0(void) { return sub_4255A0(); }
WH_EXPORT int wh_sub_426860(void) { return sub_426860(); }
WH_EXPORT void wh_sub_40E610(int index, char *buffer) { sub_40E610(index, buffer); }

/* ---- TRAK header relocation (sub_5563F0) ------------------------------- */
/* void sub_5563F0(int *cursor, int record_count, unsigned int *out_records) */
WH_EXPORT void wh_sub_5563F0(void *cursor_slot, int record_count, void *out_records)
{
    sub_5563F0(cursor_slot, record_count, out_records);
}

/* The observable globals are exposed by harness/getters_ghidra.c, which is
   generated with address-keyed names (wh_get_006D9858) so both DLLs agree. */

/* ---- the global-only functions, called through the wrappers ------------- */
WH_EXPORT void wh_sub_406E30(void) { sub_406E30(); }
WH_EXPORT void wh_sub_40D900(void) { sub_40D900(); }
WH_EXPORT void wh_sub_40D910(void) { sub_40D910(); }
WH_EXPORT void wh_sub_4155E0(void) { sub_4155E0(); }
WH_EXPORT void wh_sub_41D330(void) { sub_41D330(); }
WH_EXPORT void wh_sub_41E1B0(void) { sub_41E1B0(); }
WH_EXPORT void wh_sub_40E020(void) { sub_40E020(); }
WH_EXPORT void wh_sub_40E0A0(void) { sub_40E0A0(); }
