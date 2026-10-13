/* Selected Ghidra export at 00554bf0. */

void sub_554BF0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = DAT_006d9e38;
  iVar2 = sub_54BC00(param_1);
  iVar2 = iVar2 >> 0xc;
  iVar3 = sub_54BC00(param_1);
  iVar3 = iVar3 >> 0xc;
  iVar4 = sub_54BC00(param_1);
  iVar4 = iVar4 >> 0xc;
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  else if (0xff < iVar4) {
    iVar4 = 0xff;
  }
  if (iVar3 < 0) {
    param_1 = 0;
  }
  else {
    param_1 = iVar3;
    if (0xff < iVar3) {
      param_1 = 0xff;
    }
  }
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  else if (0xff < iVar2) {
    iVar2 = 0xff;
  }
  DAT_006d9dc4 = 1;
  DAT_006d9e14 = (char)iVar4;
  DAT_006d9e15 = (char)param_1;
  DAT_006d9e16 = (char)iVar2;
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    if (*(char *)(iVar1 + 0x136) == '\0') {
      *(char *)(iVar1 + 0x133) = (char)iVar4;
      *(char *)(iVar1 + 0x134) = (char)param_1;
      *(char *)(iVar1 + 0x135) = (char)iVar2;
      *(undefined1 *)(iVar1 + 0x136) = 1;
    }
  }
  return;
}

