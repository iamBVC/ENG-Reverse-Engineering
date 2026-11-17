/* sub_550160 @ 00550160   70 bytes */

void sub_550160(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(int *)(param_1 + 0x14) = iVar1;
  *(undefined4 *)(param_1 + 0x110) = 0;
  *(undefined2 *)(param_1 + 0x116) = 0;
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 8;
  if (*(int *)(iVar1 + 0x10) != 0) {
    sub_41FA30(*(undefined4 *)(param_1 + 0x10),iVar1,0);
  }
  return;
}

