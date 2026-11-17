/* sub_438B40 @ 00438b40   55 bytes */

void sub_438B40(int param_1)

{
  *(undefined1 **)(&DAT_00570358 + param_1 * 4) = &LAB_00408ee0;
  (&DAT_00573eb8)[param_1 * 3] = 3;
  (&DAT_00573ebc)[param_1 * 3] = 1;
  *(undefined1 *)(&DAT_00573ec0 + param_1 * 3) = 1;
  *(undefined1 *)((int)&DAT_00573ec0 + param_1 * 0xc + 1) = 1;
  return;
}

