/* sub_428700 @ 00428700   179 bytes */

undefined4 sub_428700(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = DAT_00586590 + 0x800;
  if (DAT_006d9e28 != 0) {
    iVar5 = *param_1 - *(int *)(DAT_006d9e28 + 0x30);
    iVar4 = param_1[1] - *(int *)(DAT_006d9e28 + 0x34);
    iVar6 = param_1[2] - *(int *)(DAT_006d9e28 + 0x38);
    fpatan((float10)(iVar5 >> 6),(float10)(iVar6 >> 6));
    iVar2 = __ftol();
    uVar3 = -iVar2 - DAT_005790a4 & 0xfff;
    if ((0x280 < uVar3) && (uVar3 < 0xd80)) {
      return 1;
    }
    if (((iVar1 < iVar5) ||
        (((iVar2 = -iVar1, iVar5 < iVar2 || (iVar1 < iVar4)) || (iVar4 < iVar2)))) ||
       ((iVar1 < iVar6 || (iVar6 < iVar2)))) {
      return 1;
    }
  }
  return 0;
}

