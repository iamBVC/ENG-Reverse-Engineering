/* Selected Ghidra export at 0054fef0. */

void sub_54FEF0(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = param_1;
  iVar5 = sub_54BC00(param_1);
  iVar6 = sub_54BC00(param_1);
  iVar7 = sub_54BC00(param_1);
  if (*(char *)(param_1 + 0x136) == '\0') {
    bVar1 = *(byte *)(DAT_00584644 + 0x4c);
    bVar2 = *(byte *)(DAT_00584644 + 0x4d);
    bVar3 = *(byte *)(DAT_00584644 + 0x4e);
  }
  else {
    bVar1 = *(byte *)(param_1 + 0x133);
    bVar2 = *(byte *)(param_1 + 0x134);
    bVar3 = *(byte *)(param_1 + 0x135);
  }
  param_1 = (iVar6 >> 0xc) + (uint)bVar2;
  iVar6 = (iVar5 >> 0xc) + (uint)bVar3;
  iVar5 = (iVar7 >> 0xc) + (uint)bVar1;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  else if (0xff < iVar5) {
    iVar5 = 0xff;
  }
  if (param_1 < 0) {
    param_1 = 0;
  }
  else if (0xff < param_1) {
    param_1 = 0xff;
  }
  if (iVar6 < 0) {
    iVar6 = 0;
  }
  else if (0xff < iVar6) {
    iVar6 = 0xff;
  }
  *(char *)(iVar4 + 0x133) = (char)iVar5;
  *(undefined1 *)(iVar4 + 0x134) = (undefined1)param_1;
  *(char *)(iVar4 + 0x135) = (char)iVar6;
  *(undefined1 *)(iVar4 + 0x136) = 1;
  return;
}

