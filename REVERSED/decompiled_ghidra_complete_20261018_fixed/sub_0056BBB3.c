/* sub_56BBB3 @ 0056bbb3   177 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 sub_56BBB3(uint param_1,LONG param_2,LONG param_3,DWORD param_4)

{
  byte *pbVar1;
  HANDLE hFile;
  DWORD DVar2;
  DWORD DVar3;
  int iVar4;
  LONG local_8;
  
  if (param_1 < DAT_006da8e0) {
    iVar4 = (param_1 & 0x1f) * 8;
    if ((*(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar4) & 1) == 0) goto LAB_0056bc49;
    local_8 = param_3;
    hFile = (HANDLE)sub_56A73D(param_1);
    if (hFile != (HANDLE)0xffffffff) {
      DVar3 = SetFilePointer(hFile,param_2,&local_8,param_4);
      if (DVar3 == 0xffffffff) {
        DVar2 = GetLastError();
        if (DVar2 != 0) {
          sub_568953(DVar2);
          goto LAB_0056bc5a;
        }
      }
      pbVar1 = (byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar4);
      *pbVar1 = *pbVar1 & 0xfd;
      goto LAB_0056bc60;
    }
    _DAT_006da364 = 9;
  }
  else {
LAB_0056bc49:
    DAT_006da368 = 0;
    _DAT_006da364 = 9;
  }
LAB_0056bc5a:
  DVar3 = 0xffffffff;
  local_8 = -1;
LAB_0056bc60:
  return CONCAT44(local_8,DVar3);
}

