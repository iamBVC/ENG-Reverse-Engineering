/* sub_547900 @ 00547900   69 bytes */

void sub_547900(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 4;
    *(int *)(param_1 + 0xcc) = param_2 * 0xac44 >> 0xc;
    *(uint *)(DAT_006d9490 + 0x2c) =
         *(uint *)(DAT_006d9490 + 0x2c) | 1 << (*(byte *)(param_1 + 0xc) & 0x1f);
  }
  return;
}

