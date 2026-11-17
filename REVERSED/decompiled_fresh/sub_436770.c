/* sub_436770 @ 00436770   207 bytes */

void sub_436770(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != param_4) {
    if (param_4 != -1) {
      sub_436740(param_1,param_2,0x40,0x40,0x40);
      return;
    }
    sub_436740(param_1,param_2,0x20,0x20,0x20);
    return;
  }
  if (DAT_00573d20 != 0) {
    if (DAT_005ff72c == 0) {
      DAT_00573d24 = DAT_00573d24 - 3;
      if (DAT_00573d24 < 0x70) {
        DAT_005ff72c = 1;
        DAT_00573d24 = 0x70;
        DAT_00573d20 = 0;
        goto LAB_004367ee;
      }
    }
    else {
      DAT_00573d24 = DAT_00573d24 + 3;
      if (0xc0 < DAT_00573d24) {
        DAT_005ff72c = 0;
        DAT_00573d24 = 0xc0;
      }
    }
    DAT_00573d20 = 0;
  }
LAB_004367ee:
  sub_436740(param_1,param_2,DAT_00573d24,DAT_00573d24 & 0xff,DAT_00573d24 & 0xff);
  return;
}

