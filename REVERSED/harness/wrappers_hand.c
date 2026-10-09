/* wrappers_hand.c - the same shims as wrappers_ghidra.c, but over the
 * hand-ported track in src/.  The exported names must match exactly, because
 * tools/verify.py treats the two DLLs interchangeably.
 */
#include "groove.h"

/* The TRAK header base (0x5846EC) is not part of the hand-ported set yet; the
 * harness supplies it in hand_extras.c so the loader test can run on both sides. */
extern unsigned int *dword_5846EC;

#define WH_EXPORT __declspec(dllexport)

WH_EXPORT void *wh_sub_41EF00(int size) { return sub_41EF00(size); }
WH_EXPORT void  wh_sub_41EEA0(void) { sub_41EEA0(); }
WH_EXPORT void  wh_sub_41EEE0(void) { sub_41EEE0(); }
WH_EXPORT void *wh_sub_41ED90(int size) { return sub_41ED90(size); }

WH_EXPORT int wh_sub_415A90(void *stream, void *buffer, int size)
{
    return sub_415A90((FILE *)stream, buffer, size);
}
WH_EXPORT int wh_sub_415AD0(void *stream, void *buffer) { return sub_415AD0((FILE *)stream, buffer); }
WH_EXPORT int wh_sub_415AB0(void *stream, void *buffer) { return sub_415AB0((FILE *)stream, buffer); }
WH_EXPORT int wh_sub_415AF0(void *stream, void *buffer) { return sub_415AF0((FILE *)stream, buffer); }

WH_EXPORT int wh_sub_4136C0(int a, int b) { return sub_4136C0((int *)a, (int *)b); }
WH_EXPORT int wh_sub_4255A0(void) { return sub_4255A0(); }
WH_EXPORT int wh_sub_426860(void) { return sub_426860(); }
WH_EXPORT void wh_sub_40E610(int index, char *buffer) { sub_40E610(index, buffer); }

/* address-keyed accessors, matching harness/getters_ghidra.c */
WH_EXPORT unsigned int **wh_get_005846EC(void) { return &dword_5846EC; }
WH_EXPORT unsigned char *wh_get_006D9858(void) { return &byte_6D9858; }
WH_EXPORT unsigned char *wh_get_006D94E8(void) { return &byte_6D94E8; }
WH_EXPORT int *wh_get_00581158(void) { return &dword_581158; }
WH_EXPORT int *wh_get_00586408(void) { return &dword_586408; }
WH_EXPORT int *wh_get_0058640C(void) { return &dword_58640C; }
WH_EXPORT int *wh_get_00584644(void) { return &dword_584644; }
WH_EXPORT int *wh_get_00586420(void) { return &dword_586420; }
WH_EXPORT int *wh_get_00583740(void) { return &dword_583740; }
WH_EXPORT float *wh_get_00581970(void) { return &flt_581970; }
WH_EXPORT unsigned int *wh_get_0058226C(void) { return dword_58226C; }
WH_EXPORT unsigned int *wh_get_00586584(void) { return (unsigned int *)&dword_586584; }
WH_EXPORT int *wh_get_00586588(void) { return &dword_586588; }
WH_EXPORT unsigned int *wh_get_0058656C(void) { return (unsigned int *)&dword_58656C; }
WH_EXPORT int *wh_get_00586570(void) { return &dword_586570; }
WH_EXPORT unsigned int *wh_get_005821E0(void) { return unk_5821E0; }

WH_EXPORT void wh_sub_406E30(void) { sub_406E30(); }
WH_EXPORT void wh_sub_40D900(void) { sub_40D900(); }
WH_EXPORT void wh_sub_40D910(void) { sub_40D910(); }
WH_EXPORT void wh_sub_4155E0(void) { sub_4155E0(); }
WH_EXPORT void wh_sub_41D330(void) { sub_41D330(); }
WH_EXPORT void wh_sub_41E1B0(void) { sub_41E1B0(); }
WH_EXPORT void wh_sub_40E020(void) { sub_40E020(); }
WH_EXPORT void wh_sub_40E0A0(void) { sub_40E0A0(); }
