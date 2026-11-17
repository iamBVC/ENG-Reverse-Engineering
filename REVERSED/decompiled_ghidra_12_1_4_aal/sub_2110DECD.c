/* sub_2110DECD @ 2110decd   153 bytes */

void __cdecl sub_2110DECD(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  UINT uExitCode;
  
  if (DAT_21115668 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  DAT_21115664 = 1;
  DAT_21115660 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_21115b54 != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(DAT_21115b50 - 4), DAT_21115b54 <= puVar1)) {
      do {
        if ((code *)*puVar1 != (code *)0x0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (DAT_21115b54 <= puVar1);
    }
    sub_2110DF66((undefined4 *)&DAT_21114014,(undefined4 *)&DAT_21114018);
  }
  sub_2110DF66((undefined4 *)&DAT_2111401c,(undefined4 *)&DAT_21114020);
  if (param_3 != 0) {
    return;
  }
  DAT_21115668 = 1;
                    /* WARNING: Subroutine does not return */
  ExitProcess(param_1);
}

