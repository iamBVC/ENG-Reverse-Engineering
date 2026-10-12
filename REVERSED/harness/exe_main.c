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

/* Run from the executable's own directory, whatever folder it is launched from: the game
 * opens its assets by relative name ("111.cor", "Wads\..."), so this is what makes the
 * rebuild work from anywhere instead of only from the folder it was installed into. */
static void set_working_directory(void)
{
    char path[MAX_PATH];
    DWORD n = GetModuleFileNameA(NULL, path, sizeof path);
    if (n == 0 || n >= sizeof path)
        return;
    while (n > 0 && path[n - 1] != '\\' && path[n - 1] != '/')
        --n;
    if (n == 0)
        return;
    path[n] = '\0';
    SetCurrentDirectoryA(path);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)nCmdShow;
    set_working_directory();
    /* Keep the startup trace even when the exe is double-clicked: a GUI-subsystem image
       launched that way has no console, so stderr writes would go nowhere.  The log lands
       next to the executable (the working directory was set above), and it is the first
       thing to look at if the game does not start. */
    if (freopen("groove_trace.log", "w", stderr) == NULL) {
        /* no log available - carry on, the trace is a diagnostic, not a requirement */
    }
    /* Two lines of instrumentation, because "it crashes" is not a diagnosis: with them a
       run says whether the fault is inside the game's main or outside it. */
    fprintf(stderr, "[winmain] calling sub_41D350(hInst=%p, cmd=%.20s)\n",
            (void *)hInstance, lpCmdLine ? lpCmdLine : "(null)");
    fprintf(stderr, "[winmain] working directory = the executable's own folder\n");
    fflush(stderr);
    int rc = sub_41D350((int)hInstance, (int)hPrevInstance, lpCmdLine);
    fprintf(stderr, "[winmain] sub_41D350 returned %d\n", rc);
    return rc;
}
