/* sub_54EA00 @ 0054ea00   29 bytes */

void sub_54EA00(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x28) = iVar1 + *(int *)(param_1 + 0x28) & 0xffffff;
  return;
}

