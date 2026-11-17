/* sub_563BD6 @ 00563bd6   153 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_563BD6(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  UINT uExitCode;
  
  if (DAT_006da3ac == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_006da3a8 = 1;
  DAT_006da3a4 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_006db930 != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(DAT_006db92c - 4), DAT_006db930 <= puVar1)) {
      do {
        if ((code *)*puVar1 != (code *)0x0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (DAT_006db930 <= puVar1);
    }
    sub_563C6F(&DAT_0057027c,&DAT_00570284);
  }
  sub_563C6F(&DAT_00570288,&DAT_00570290);
  if (param_3 != 0) {
    return;
  }
  DAT_006da3ac = 1;
                    /* WARNING: Subroutine does not return */
  ExitProcess(param_1);
}

