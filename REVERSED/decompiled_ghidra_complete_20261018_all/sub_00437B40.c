/* sub_437B40 @ 00437b40   323 bytes */

undefined4 sub_437B40(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  
  if (DAT_006d7acc != 0) {
    sub_437E90();
  }
  iVar3 = param_1;
  sub_415AB0(param_1,&DAT_006d7acc);
  if (DAT_006d7acc == 0) {
    return 0;
  }
  DAT_006d7ad0 = sub_41EF00(DAT_006d7acc * 0x14);
  if (DAT_006d7ad0 == 0) {
    return 0;
  }
  uVar5 = 0;
  if (DAT_006d7acc != 0) {
    iVar6 = 0;
    do {
      sub_415AB0(iVar3,iVar6 + DAT_006d7ad0);
      sub_415AB0(iVar3,iVar6 + 4 + DAT_006d7ad0);
      sub_415AF0(iVar3,iVar6 + 8 + DAT_006d7ad0);
      if ((*(byte *)(iVar6 + 8 + DAT_006d7ad0) & 0x80) == 0) {
        iVar2 = *(int *)(iVar6 + 4 + DAT_006d7ad0) * *(int *)(iVar6 + DAT_006d7ad0) * 2;
        uVar4 = sub_41EF00(iVar2);
        *(undefined4 *)(iVar6 + 0xc + DAT_006d7ad0) = uVar4;
        iVar1 = *(int *)(iVar6 + 0xc + DAT_006d7ad0);
      }
      else {
        sub_415AB0(iVar3,&param_1);
        uVar4 = sub_41EF00(param_1);
        *(undefined4 *)(iVar6 + 0xc + DAT_006d7ad0) = uVar4;
        iVar1 = *(int *)(iVar6 + 0xc + DAT_006d7ad0);
        iVar2 = param_1;
      }
      if (iVar1 == 0) {
        return 0;
      }
      sub_415A90(iVar3,iVar1,iVar2);
      uVar5 = uVar5 + 1;
      *(undefined4 *)(iVar6 + 0x10 + DAT_006d7ad0) = 0;
      iVar6 = iVar6 + 0x14;
    } while (uVar5 < DAT_006d7acc);
  }
  return 1;
}

