/* sub_546140 @ 00546140   39 bytes */

void sub_546140(int param_1)

{
  if ((DAT_006d9490 != 0) && (DAT_006d9498 != 0)) {
    if (param_1 < 0x2000) {
      param_1 = 0x2000;
    }
    *(int *)(DAT_006d9498 + 0x5c) = param_1;
  }
  return;
}

