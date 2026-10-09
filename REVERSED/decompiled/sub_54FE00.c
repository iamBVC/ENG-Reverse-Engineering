/* sub_54FE00 @ 0054fe00   58 bytes */

void sub_54FE00(int param_1)

{
  undefined2 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x36) = uVar1;
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x34) = uVar1;
  uVar1 = sub_54BC00(param_1);
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x32) = uVar1;
  return;
}

