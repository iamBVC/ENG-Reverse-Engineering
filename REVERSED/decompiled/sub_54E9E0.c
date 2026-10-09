/* sub_54E9E0 @ 0054e9e0   30 bytes */

void sub_54E9E0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) - iVar1 & 0xffffff;
  return;
}

