/* sub_567502 @ 00567502   61 bytes */

void sub_567502(int param_1,undefined4 *param_2)

{
  if (param_1 == 0) {
    if ((*(byte *)((int)param_2 + 0xd) & 0x10) != 0) {
      sub_5638F0(param_2);
    }
  }
  else if ((*(byte *)((int)param_2 + 0xd) & 0x10) != 0) {
    sub_5638F0(param_2);
    *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) & 0xee;
    param_2[6] = 0;
    *param_2 = 0;
    param_2[2] = 0;
    return;
  }
  return;
}

