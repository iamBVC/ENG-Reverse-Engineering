/* sub_56A6C3 @ 0056a6c3   122 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_56A6C3(uint param_1)

{
  int *piVar1;
  int iVar2;
  DWORD nStdHandle;
  
  if (param_1 < DAT_006da8e0) {
    iVar2 = (param_1 & 0x1f) * 8;
    piVar1 = (int *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar2);
    if (((*(byte *)(piVar1 + 1) & 1) != 0) && (*piVar1 != -1)) {
      if (DAT_0057c7c4 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_0056a71c;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0056a71c:
      *(undefined4 *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar2) = 0xffffffff;
      return 0;
    }
  }
  DAT_006da368 = 0;
  _DAT_006da364 = 9;
  return 0xffffffff;
}

