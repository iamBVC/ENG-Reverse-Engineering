/* sub_405BA0 @ 00405ba0   82 bytes */

bool sub_405BA0(undefined4 param_1,undefined4 param_2,LPCSTR param_3,BYTE *param_4)

{
  BYTE BVar1;
  HKEY hKey;
  LSTATUS LVar2;
  uint uVar3;
  BYTE *pBVar4;
  bool bVar5;
  
  bVar5 = false;
  hKey = (HKEY)sub_405960(param_1,param_2,2);
  if (hKey != (HKEY)0x0) {
    uVar3 = 0xffffffff;
    pBVar4 = param_4;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      BVar1 = *pBVar4;
      pBVar4 = pBVar4 + 1;
    } while (BVar1 != '\0');
    LVar2 = RegSetValueExA(hKey,param_3,0,1,param_4,~uVar3);
    bVar5 = LVar2 == 0;
    RegCloseKey(hKey);
  }
  return bVar5;
}

