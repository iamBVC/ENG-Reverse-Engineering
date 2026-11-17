/* sub_4058A0 @ 004058a0   178 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 sub_4058A0(char *param_1,undefined4 param_2,DWORD param_3,LPCSTR param_4)

{
  char cVar1;
  HKEY hKey;
  LSTATUS LVar2;
  uint uVar3;
  uint uVar4;
  undefined1 uVar5;
  char *pcVar6;
  char *pcVar7;
  DWORD local_4;
  
  local_4 = 0x800;
  uVar5 = 0;
  hKey = (HKEY)sub_405960(param_2,param_3,1);
  if (hKey != (HKEY)0x0) {
    LVar2 = RegQueryValueExA(hKey,param_4,(LPDWORD)0x0,&param_3,&DAT_0057ee74,&local_4);
    uVar5 = 0;
    if (LVar2 == 0) {
      if (param_3 == 4) {
        sub_562717(param_1,&DAT_00570300,_DAT_0057ee74);
        RegCloseKey(hKey);
        return 1;
      }
      uVar3 = 0xffffffff;
      uVar5 = 1;
      pcVar6 = &DAT_0057ee74;
      do {
        pcVar7 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar6 = pcVar7 + -uVar3;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)param_1 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        param_1 = param_1 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *param_1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        param_1 = param_1 + 1;
      }
    }
    RegCloseKey(hKey);
  }
  return uVar5;
}

