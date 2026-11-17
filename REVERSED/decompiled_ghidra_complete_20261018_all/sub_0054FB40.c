/* sub_54FB40 @ 0054fb40   40 bytes */

void sub_54FB40(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(short *)(param_1 + 0xfe) = (short)(iVar1 >> 0xc);
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 2;
  return;
}

