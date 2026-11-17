/* sub_5479B0 @ 005479b0   47 bytes */

void sub_5479B0(int param_1,int param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 0x200;
    if (param_2 != 0) {
      *(undefined4 *)(param_1 + 0xdc) = 0x3f800000;
      return;
    }
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}

