/* sub_54EAB0 @ 0054eab0   33 bytes */

void sub_54EAB0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(*(int *)(param_1 + 0x120) + 0xc) = iVar1 >> 0xc & 0xfff;
  return;
}

