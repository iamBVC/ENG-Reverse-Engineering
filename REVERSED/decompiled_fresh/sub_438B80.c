/* sub_438B80 @ 00438b80   48 bytes */

void sub_438B80(int param_1)

{
  *(undefined1 **)(&DAT_00570358 + param_1 * 4) = &LAB_0040aab0;
  (&DAT_00573eb8)[param_1 * 3] = 0;
  (&DAT_00573ebc)[param_1 * 3] = 0;
  *(undefined1 *)(&DAT_00573ec0 + param_1 * 3) = 0;
  *(undefined1 *)((int)&DAT_00573ec0 + param_1 * 0xc + 1) = 0;
  return;
}

