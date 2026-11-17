/* sub_547950 @ 00547950   25 bytes */

void sub_547950(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1;
    *(undefined4 *)(param_1 + 0x18) = param_2;
  }
  return;
}

