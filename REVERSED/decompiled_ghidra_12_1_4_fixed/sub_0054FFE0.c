/* sub_54FFE0 @ 0054ffe0   25 bytes */

void sub_54FFE0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = sub_54BC00(param_1);
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 100) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  return;
}

