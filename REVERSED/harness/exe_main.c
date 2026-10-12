/* exe_main.c - the image's entry point: the modern CRT's startup calling the game's main.
 *
 * The original PE's entry point is `entry` (0x563EE0, the name Ghidra gave the PE
 * AddressOfEntryPoint), and it is the **MSVC 6 CRT startup**: disassembling it shows
 * `call 0x41D350` among its initialisation calls, and 0x41D350 is the game's own
 * `WinMain` - the listing's `_WinMain@16`.  (IDA merged 0x41D350 into sub_41D340, but the
 * startup's call is proof of where the function starts.)
 *
 * A rebuild does not need the 2001 CRT startup at all: the modern CRT supplies its own
 * (`WinMainCRTStartup`, because the image is /SUBSYSTEM:WINDOWS) and all it asks for is
 * this WinMain.  This is also why linking the exe used to fail with 14 unresolved
 * symbols: `/ENTRY:entry` replaced the CRT startup with a *stub* of the game's, so the
 * runtime's own entry points - `_memcpy`, `_cos`, `_malloc`, `_log2`, ... - had nowhere
 * to come from.
 *
 * Three arguments: Ghidra recovered `sub_41D350` with three and the callers pass three;
 * the fourth WinMain parameter (`nCmdShow`) is not read by it.
 */
#include <windows.h>
#include <stdio.h>

extern int sub_41D350(int hInstance, int hPrevInstance, char *lpCmdLine);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)nCmdShow;
    /* Two lines of instrumentation, because "it crashes" is not a diagnosis: with them a
       run says whether the fault is inside the game's main or outside it. */
    fprintf(stderr, "[winmain] calling sub_41D350(hInst=%p, cmd=%.20s)\n",
            (void *)hInstance, lpCmdLine ? lpCmdLine : "(null)");
    fflush(stderr);
    int rc = sub_41D350((int)hInstance, (int)hPrevInstance, lpCmdLine);
    fprintf(stderr, "[winmain] sub_41D350 returned %d\n", rc);
    return rc;
}
