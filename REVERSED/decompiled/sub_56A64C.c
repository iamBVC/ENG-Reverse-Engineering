/* sub_56A64C @ 0056a64c   119 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_56A64C(uint param_1,HANDLE param_2)

{
  int iVar1;
  DWORD nStdHandle;
  
  if (param_1 < DAT_006da8e0) {
    iVar1 = (param_1 & 0x1f) * 8;
    if (*(int *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar1) == -1) {
      if (DAT_0057c7c4 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_0056a6a2;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,param_2);
      }
LAB_0056a6a2:
      *(HANDLE *)((&DAT_006da7e0)[(int)param_1 >> 5] + iVar1) = param_2;
      return 0;
    }
  }
  DAT_006da368 = 0;
  _DAT_006da364 = 9;
  return 0xffffffff;
}

