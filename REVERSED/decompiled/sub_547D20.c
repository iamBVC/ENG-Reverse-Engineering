/* sub_547D20 @ 00547d20   76 bytes */

undefined4 sub_547D20(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    sub_546E30(iVar1);
    *param_2 = *(undefined4 *)(iVar1 + 0xc);
    param_2[1] = *(undefined4 *)(iVar1 + 0x10);
    param_2[2] = *(undefined4 *)(iVar1 + 0x14);
    param_2[3] = *(undefined4 *)(iVar1 + 0x18);
    sub_546E10(iVar1,param_1);
    uVar2 = *(undefined4 *)(iVar1 + 8);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
    return uVar2;
  }
  return 0;
}

