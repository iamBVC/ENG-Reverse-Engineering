/* sub_553CB0 @ 00553cb0   29 bytes */

void sub_553CB0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x24) = iVar1 + *(int *)(param_1 + 0x24) & 0xffffff;
  return;
}

