/* sub_438B00 @ 00438b00   53 bytes */

void sub_438B00(int param_1)

{
  *(code **)(&DAT_00570358 + param_1 * 4) = sub_408390;
  (&DAT_00573eb8)[param_1 * 3] = 2;
  (&DAT_00573ebc)[param_1 * 3] = 0;
  *(undefined1 *)(&DAT_00573ec0 + param_1 * 3) = 0;
  *(undefined1 *)((int)&DAT_00573ec0 + param_1 * 0xc + 1) = 1;
  return;
}

