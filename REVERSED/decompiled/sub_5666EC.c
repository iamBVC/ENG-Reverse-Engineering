/* sub_5666EC @ 005666ec   179 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_5666EC(uint param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD DVar4;
  int iVar5;
  
  if (DAT_006da8e0 <= param_1) {
    DAT_006da368 = 0;
    _DAT_006da364 = 9;
    return 0xffffffff;
  }
  iVar5 = (param_1 & 0x1f) * 8;
  if ((*(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar5) & 1) == 0) {
    _DAT_006da364 = 9;
    DAT_006da368 = 0;
    return 0xffffffff;
  }
  iVar1 = sub_56A73D(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = sub_56A73D(2);
      iVar2 = sub_56A73D(1);
      if (iVar2 == iVar1) goto LAB_00566765;
    }
    hObject = (HANDLE)sub_56A73D(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      DVar4 = GetLastError();
      goto LAB_00566767;
    }
  }
LAB_00566765:
  DVar4 = 0;
LAB_00566767:
  sub_56A6C3(param_1);
  *(undefined1 *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + iVar5) = 0;
  if (DVar4 == 0) {
    return 0;
  }
  sub_568953(DVar4);
  return 0xffffffff;
}

