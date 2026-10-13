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

/* The game's static initialisers, in the order the 2001 CRT ran them (see
 * tools/gen_crt_initialisers.py and harness/crt_initialisers.c, which is generated).
 *
 * This is the one piece of the original startup the modern CRT cannot supply.  The 2001
 * `entry` calls `_cinit` right before `WinMain`, and `_cinit` runs the compiler's
 * initialiser tables through `_initterm`; skipping it left every global object at its
 * load-time value, which for a `dd ?` slot means zero.  `DAT_00583410` - the head of the
 * DirectDraw object list - is exactly that, and the teardown `sub_40FD00` dereferenced it. */
extern void (*const groove_crt_initialisers[])(void);
extern const unsigned int groove_crt_initialiser_count;

static LONG WINAPI report_unhandled_exception(EXCEPTION_POINTERS *failure)
{
    EXCEPTION_RECORD *record = failure->ExceptionRecord;
    CONTEXT *context = failure->ContextRecord;
    UINT_PTR base = (UINT_PTR)GetModuleHandleA(NULL);
    UINT_PTR address = (UINT_PTR)record->ExceptionAddress;
    HMODULE fault_module = NULL;
    char fault_path[MAX_PATH];
    fprintf(stderr, "[crash] code=%08lx address=%p module=%p rva=%08lx\n",
            record->ExceptionCode, (void *)address, (void *)base,
            (unsigned long)(address - base));
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                          (LPCSTR)address, &fault_module) &&
        GetModuleFileNameA(fault_module, fault_path, sizeof fault_path))
        fprintf(stderr, "[crash] fault-module=%s base=%p offset=%08lx thread=%lu\n",
                fault_path, (void *)fault_module,
                (unsigned long)(address - (UINT_PTR)fault_module), GetCurrentThreadId());
    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2)
        fprintf(stderr, "[crash] access=%lu target=%p\n",
                (unsigned long)record->ExceptionInformation[0],
                (void *)record->ExceptionInformation[1]);
    fprintf(stderr, "[crash] eip=%08lx eax=%08lx ecx=%08lx edx=%08lx esp=%08lx ebp=%08lx\n",
            context->Eip, context->Eax, context->Ecx, context->Edx, context->Esp, context->Ebp);
    {
        DWORD stack[128];
        SIZE_T bytes = 0;
        IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)base;
        IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + dos->e_lfanew);
        unsigned int i;
        if (ReadProcessMemory(GetCurrentProcess(), (void *)context->Esp,
                              stack, sizeof stack, &bytes)) {
            for (i = 0; i < bytes / sizeof stack[0]; ++i)
                if (stack[i] >= base && stack[i] - base < nt->OptionalHeader.SizeOfImage)
                    fprintf(stderr, "[crash] stack[%u]=%08lx rva=%08lx\n",
                            i, stack[i], (unsigned long)(stack[i] - base));
        }
    }
    fflush(stderr);
    return EXCEPTION_EXECUTE_HANDLER;
}

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
    SetUnhandledExceptionFilter(report_unhandled_exception);
    /* The module handle comes first: tools/crash_report.py needs it to turn a fault
       address into a function name, and a fault inside the initialisers would otherwise
       happen before anything logged it. */
    fprintf(stderr, "[winmain] hInst=%p  running %u static initialiser(s)\n",
            (void *)hInstance, groove_crt_initialiser_count);
    fflush(stderr);

    /* Run the game's static initialisers, as the original CRT startup did.  Each one is
       named as it starts: the last line in the trace is then the initialiser a fault came
       from, which is otherwise invisible (they all run before anything else does). */
    {
        unsigned int i;
        for (i = 0; i < groove_crt_initialiser_count; ++i) {
            fprintf(stderr, "[winmain] init %u/%u\n", i + 1, groove_crt_initialiser_count);
            fflush(stderr);
            groove_crt_initialisers[i]();
        }
        fprintf(stderr, "[winmain] static initialisers done\n");
        fflush(stderr);
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
