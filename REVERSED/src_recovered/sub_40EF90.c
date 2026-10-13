/* Selected Ghidra export at 0040ef90. */

undefined4 sub_40EF90(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + 0x20;
  iVar1 = sub_56D440(iVar2,s_start_0057151c,5);
  if (iVar1 == 0) {
    sub_4199F0(param_2,9,*(int *)(param_1 + 0x14) + -0x30);
  }
  iVar1 = sub_56D440(iVar2,s_select_00571514,6);
  if (iVar1 != 0) {
    iVar1 = sub_56D440(iVar2,s_shift_0057150c,5);
    if (iVar1 != 0) goto LAB_0040effe;
  }
  sub_4199F0(param_2,0xd,*(int *)(param_1 + 0x14) + -0x30);
LAB_0040effe:
  iVar1 = sub_56D440(iVar2,s_button_l_00571500,8);
  if (iVar1 == 0) {
    sub_4199F0(param_2,4,*(int *)(param_1 + 0x14) + -0x30);
  }
  iVar2 = sub_56D440(iVar2,s_button_r_005714f4,8);
  if (iVar2 == 0) {
    sub_4199F0(param_2,5,*(int *)(param_1 + 0x14) + -0x30);
  }
  return 1;
}

