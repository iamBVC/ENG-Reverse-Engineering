/* sub_547710 @ 00547710   58 bytes */

undefined4 sub_547710(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x1c);
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0xc);
    if (iVar1 == 0) {
      return 0;
    }
    *param_2 = iVar1;
  }
  else {
    *param_2 = iVar1;
  }
  sub_546E30(iVar1);
  sub_546E10(iVar1,param_1 + 0x14);
  return 0;
}

