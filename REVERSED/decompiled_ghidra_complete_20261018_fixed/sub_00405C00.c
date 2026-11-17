/* sub_405C00 @ 00405c00   71 bytes */

bool sub_405C00(undefined4 param_1,undefined4 param_2,LPCSTR param_3)

{
  HKEY hKey;
  LSTATUS LVar1;
  bool bVar2;
  
  bVar2 = false;
  hKey = (HKEY)sub_405960(param_1,param_2,2);
  if (hKey != (HKEY)0x0) {
    LVar1 = RegSetValueExA(hKey,param_3,0,4,&stack0x00000010,4);
    bVar2 = LVar1 == 0;
    RegCloseKey(hKey);
  }
  return bVar2;
}

