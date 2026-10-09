/* sub_427D90 @ 00427d90   98 bytes */

void sub_427D90(int param_1)

{
  bool bVar1;
  
  if (param_1 == 0) {
    bVar1 = true;
    if (DAT_005fd08c == 0) goto LAB_00427db5;
    DAT_005fd08c = DAT_005fd08c - 4;
  }
  else if (DAT_005fd08c < 0x20) {
    DAT_005fd08c = DAT_005fd08c + 4;
  }
  bVar1 = DAT_005fd08c == 0;
LAB_00427db5:
  if (!bVar1) {
    sub_426510(0,0xf0,0x200,DAT_005fd08c * 2,0,0,0,1);
    sub_426510(0,DAT_005fd08c,0x200,DAT_005fd08c,0,0,0,1);
  }
  return;
}

