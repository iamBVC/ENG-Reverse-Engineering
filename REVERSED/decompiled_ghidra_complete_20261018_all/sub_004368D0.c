/* sub_4368D0 @ 004368d0   326 bytes */

void sub_4368D0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5,
               undefined4 param_6)

{
  if (param_3 != param_4) {
    if (param_4 != -1) {
      sub_436550(param_1,param_2,0x40,0x40,0x40,0x200,(param_5 & 1) + 2,param_6);
      return;
    }
    sub_436550(param_1,param_2,0x20,0x20,0x20,0x200,(param_5 & 1) + 2,param_6);
    return;
  }
  if ((param_5 & 4) != 0) {
    sub_436550(param_1,param_2,0x80,0x80,0x80,0x200,(param_5 & 1) + 2,param_6);
    return;
  }
  if (DAT_00573d20 != 0) {
    if (DAT_005ff72c == 0) {
      DAT_00573d24 = DAT_00573d24 - 3;
      if (DAT_00573d24 < 0x70) {
        DAT_005ff72c = 1;
        DAT_00573d24 = 0x70;
        DAT_00573d20 = 0;
        goto LAB_0043698a;
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
LAB_0043698a:
  sub_436550(param_1,param_2,DAT_00573d24,DAT_00573d24 & 0xff,DAT_00573d24 & 0xff,0x200,
             (param_5 & 1) + 2,param_6);
  return;
}

