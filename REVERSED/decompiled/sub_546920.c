/* sub_546920 @ 00546920   56 bytes */

void sub_546920(undefined4 param_1,undefined4 *param_2)

{
  if (DAT_006d94a0 != 0) {
    *(undefined4 *)(DAT_006d94a0 + 0x20) = 0;
    *(undefined4 *)(DAT_006d94a0 + 0x24) = *param_2;
    *(undefined4 *)(DAT_006d94a0 + 0x28) = param_2[1];
    *(undefined4 *)(DAT_006d94a0 + 0x2c) = param_2[2];
  }
  return;
}

