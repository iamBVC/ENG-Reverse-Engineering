/* sub_405B00 @ 00405b00   157 bytes */

undefined4 sub_405B00(float *param_1,undefined4 param_2,DWORD param_3,LPCSTR param_4)

{
  HKEY hKey;
  LSTATUS LVar1;
  undefined4 uVar2;
  float10 fVar3;
  DWORD local_c;
  uint local_8;
  undefined4 uStack_4;
  
  local_c = 0x800;
  uVar2 = 0;
  hKey = (HKEY)sub_405960(param_2,param_3,1);
  if (hKey != (HKEY)0x0) {
    LVar1 = RegQueryValueExA(hKey,param_4,(LPDWORD)0x0,&param_3,(LPBYTE)&DAT_0057e5c4,&local_c);
    if (LVar1 == 0) {
      if (param_3 == 4) {
        local_8 = DAT_0057e5c4;
        uStack_4 = 0;
        *param_1 = (float)DAT_0057e5c4;
        RegCloseKey(hKey);
        return 1;
      }
      fVar3 = (float10)sub_56286F(&DAT_0057e5c4);
      uVar2 = 1;
      *param_1 = (float)fVar3;
    }
    RegCloseKey(hKey);
  }
  return uVar2;
}

