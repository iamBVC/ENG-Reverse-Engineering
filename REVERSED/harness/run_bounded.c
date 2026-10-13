/* Independent watchdog: the game is terminated after eight seconds even if
   the agent's tool call is interrupted. */
#include <windows.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    STARTUPINFOA startup = {sizeof startup};
    PROCESS_INFORMATION process = {0};
    char command[32768];
    DWORD result, code;
    if (argc != 2 || snprintf(command, sizeof command, "\"%s\"", argv[1]) < 0)
        return 2;
    startup.dwFlags = STARTF_USESHOWWINDOW;
    startup.wShowWindow = SW_SHOWNORMAL;
    if (!CreateProcessA(argv[1], command, NULL, NULL, FALSE, 0, NULL, NULL,
                        &startup, &process)) {
        fprintf(stderr, "launch failed: %lu\n", GetLastError());
        return 1;
    }
    printf("Started PID %lu; maximum run time 8000 ms\n", process.dwProcessId);
    fflush(stdout);
    result = WaitForSingleObject(process.hProcess, 8000);
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
