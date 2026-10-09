/* sub_545DE0 @ 00545de0   74 bytes */

void sub_545DE0(uint param_1,short param_2)

{
  if (DAT_006d9490 != 0) {
    if (*(uint *)(DAT_006d9490 + 0xf4) != (param_1 & 0x1fff)) {
      *(uint *)(DAT_006d9490 + 0xf4) = param_1 & 0x1fff;
      *(uint *)(DAT_006d9490 + 0xf8) = param_1 & 0xe000;
      *(int *)(DAT_006d9490 + 0xfc) = (int)param_2;
    }
  }
  return;
}

