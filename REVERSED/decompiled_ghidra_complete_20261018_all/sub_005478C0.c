/* sub_5478C0 @ 005478c0   63 bytes */

void sub_5478C0(int param_1,undefined2 *param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 2;
    *(undefined2 *)(param_1 + 0x1c) = *param_2;
    *(undefined2 *)(param_1 + 0x1e) = param_2[1];
    *(uint *)(DAT_006d9490 + 0x2c) =
         *(uint *)(DAT_006d9490 + 0x2c) | 1 << (*(byte *)(param_1 + 0xc) & 0x1f);
  }
  return;
}

