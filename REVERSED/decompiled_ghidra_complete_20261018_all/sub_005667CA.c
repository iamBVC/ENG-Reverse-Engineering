/* sub_5667CA @ 005667ca   154 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DWORD sub_5667CA(uint param_1,LONG param_2,DWORD param_3)

{
  byte *pbVar1;
  HANDLE hFile;
  DWORD DVar2;
  DWORD DVar3;
  int iVar4;
  
  if (param_1 < DAT_006da8e0) {
    iVar4 = (param_1 & 0x1f) * 8;
    if ((*(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar4) & 1) != 0) {
      hFile = (HANDLE)sub_56A73D(param_1);
      if (hFile == (HANDLE)0xffffffff) {
        _DAT_006da364 = 9;
        return 0xffffffff;
      }
      DVar2 = SetFilePointer(hFile,param_2,(PLONG)0x0,param_3);
      if (DVar2 == 0xffffffff) {
        DVar3 = GetLastError();
      }
      else {
        DVar3 = 0;
      }
      if (DVar3 != 0) {
        sub_568953(DVar3);
        return 0xffffffff;
      }
      pbVar1 = (byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar4);
      *pbVar1 = *pbVar1 & 0xfd;
      return DVar2;
    }
  }
  DAT_006da368 = 0;
  _DAT_006da364 = 9;
  return 0xffffffff;
}

