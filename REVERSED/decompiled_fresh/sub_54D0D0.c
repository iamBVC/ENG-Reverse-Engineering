/* sub_54D0D0 @ 0054d0d0   176 bytes */

void sub_54D0D0(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  DAT_006d9e40 = 0;
  DAT_006d9dc4 = 0;
  DAT_006d9e1c = 0;
  DAT_006d9e20 = 0;
  DAT_006d9e28 = 0;
  DAT_006d9e38 = 0;
  DAT_006d9e3c = 0;
  DAT_006d9e24 = 0;
  DAT_006d9e2c = 0;
  DAT_006d9e30 = 0;
  DAT_006d9e34 = 0;
  sub_41EE60();
  iVar1 = *(int *)(param_1 + 8) + 0x1e;
  *(int *)(param_1 + 8) = iVar1;
  DAT_006d9dc0 = sub_41EE40(iVar1 * 0x154);
  iVar1 = DAT_006d9dc0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      iVar2 = iVar1;
      sub_54CEF0(iVar2);
      *(int *)(iVar2 + 4) = DAT_006d9e3c;
      uVar3 = uVar3 + 1;
      iVar1 = iVar2 + 0x154;
      DAT_006d9e3c = iVar2;
    } while (uVar3 < *(uint *)(param_1 + 8));
  }
  sub_54CFC0(param_1);
  return;
}

