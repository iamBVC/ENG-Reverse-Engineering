/* sub_54EA80 @ 0054ea80   33 bytes */

void sub_54EA80(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(*(int *)(param_1 + 0x120) + 8) = iVar1 >> 0xc & 0xfff;
  return;
}

