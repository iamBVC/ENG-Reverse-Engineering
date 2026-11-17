/* sub_547970 @ 00547970   28 bytes */

void sub_547970(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 0x10;
    *(undefined4 *)(param_1 + 200) = param_2;
  }
  return;
}

