/* sub_41AF00 @ 0041af00   60 bytes */

void sub_41AF00(undefined4 *param_1,undefined4 param_2)

{
  DAT_00584998 = param_2;
  DAT_0058499c = param_1;
  *param_1 = 0;
  DAT_0058499c[1] = 0;
  *(short *)(DAT_0058499c + 2) = (short)DAT_00584998 + -3;
  *(undefined2 *)((int)DAT_0058499c + 10) = 0;
  return;
}

