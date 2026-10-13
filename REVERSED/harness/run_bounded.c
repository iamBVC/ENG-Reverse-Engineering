/* Independent watchdog: the game is terminated after eight seconds even if
   the agent's tool call is interrupted. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>

/* Copy context and stack while paused, then resume before enumerating modules
   or writing diagnostics. The independent deadline still ends the game. */
static void sample_thread(const PROCESS_INFORMATION *process)
{
    CONTEXT context = {0};
    DWORD stack[64] = {0};
    SIZE_T bytes = 0;
    BOOL captured;
    HANDLE modules;
    MODULEENTRY32 entry = {sizeof entry};
    UINT_PTR base = 0;
    DWORD image_size = 0, i;
    if (SuspendThread(process->hThread) == (DWORD)-1) return;
    context.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
    captured = GetThreadContext(process->hThread, &context);
    if (captured)
        ReadProcessMemory(process->hProcess, (void *)context.Esp, stack, sizeof stack, &bytes);
    ResumeThread(process->hThread);
    if (!captured) return;
    printf("[sample] eip=%08lx esp=%08lx ebp=%08lx eax=%08lx ecx=%08lx edx=%08lx\n",
           context.Eip, context.Esp, context.Ebp, context.Eax, context.Ecx, context.Edx);
    modules = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process->dwProcessId);
    if (modules != INVALID_HANDLE_VALUE) {
        if (Module32First(modules, &entry)) {
            base = (UINT_PTR)entry.modBaseAddr;
            image_size = entry.modBaseSize;
            printf("[sample] image-base=%08lx\n", (DWORD)base);
            do {
                if (context.Eip >= (UINT_PTR)entry.modBaseAddr &&
                    context.Eip - (UINT_PTR)entry.modBaseAddr < entry.modBaseSize)
                    printf("[sample] module=%s offset=%08lx\n", entry.szModule,
                           context.Eip - (DWORD)entry.modBaseAddr);
            } while (Module32Next(modules, &entry));
        }
        CloseHandle(modules);
    }
    for (i = 0; i < bytes / sizeof stack[0]; ++i)
        if (stack[i] >= base && stack[i] - base < image_size)
            printf("[sample] stack[%lu]=%08lx rva=%08lx\n", i, stack[i], stack[i] - (DWORD)base);
    fflush(stdout);
}

int main(int argc, char **argv)
{
    STARTUPINFOA startup = {sizeof startup};
    PROCESS_INFORMATION process = {0};
    char command[32768];
    DWORD result, code, started, elapsed;
    int sample = argc == 3 && strcmp(argv[2], "--sample") == 0;
    if ((argc != 2 && !sample) || snprintf(command, sizeof command, "\"%s\"", argv[1]) < 0)
        return 2;
    startup.dwFlags = STARTF_USESHOWWINDOW;
    startup.wShowWindow = SW_SHOWNORMAL;
    if (!CreateProcessA(argv[1], command, NULL, NULL, FALSE, 0, NULL, NULL,
                        &startup, &process)) {
        fprintf(stderr, "launch failed: %lu\n", GetLastError());
        return 1;
    }
    started = GetTickCount();
    printf("Started PID %lu; maximum run time 8000 ms\n", process.dwProcessId);
    fflush(stdout);
    result = WaitForSingleObject(process.hProcess, sample ? 7000 : 8000);
    if (sample && result == WAIT_TIMEOUT) {
        sample_thread(&process);
        elapsed = GetTickCount() - started;
        result = WaitForSingleObject(process.hProcess, elapsed < 8000 ? 8000 - elapsed : 0);
    }
    if (result != WAIT_OBJECT_0) {
        if (!TerminateProcess(process.hProcess, 124)) {
            fprintf(stderr, "termination failed: %lu\n", GetLastError());
            return 1;
        }
        WaitForSingleObject(process.hProcess, INFINITE);
        puts("Stopped child at the eight-second limit");
    } else {
        GetExitCodeProcess(process.hProcess, &code);
        printf("Child exited: %08lx\n", code);
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return 0;
}
