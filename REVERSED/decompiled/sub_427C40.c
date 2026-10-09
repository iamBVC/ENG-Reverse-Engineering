/* sub_427C40 @ 00427c40   375 bytes */

void sub_427C40(void)

{
  undefined4 uVar1;
  
  if ((DAT_005846e4 != 3) && (DAT_005846e4 != 0xd)) {
    if (DAT_005846e4 == 2) {
      sub_425CB0(0,0,0,0x7f,1,1);
      sub_425CB0(0x80,0,1,0x7f,1,1);
      sub_425CB0(0x100,0,2,0x7f,1,1);
      sub_425CB0(0x180,0,3,0x7f,1,1);
      sub_425CB0(0,0x5f,4,0x7f,1,1);
      sub_425CB0(0x80,0x5f,5,0x7f,1,1);
      sub_425CB0(0x100,0x5f,6,0x7f,1,1);
      sub_425CB0(0x180,0x5f,7,0x7f,1,1);
    }
    return;
  }
  if ((DAT_005fd090 == 0) && (DAT_006d94e8 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  sub_427D90(uVar1);
  if ((DAT_005fd090 == 0) && (DAT_006d94e8 == '\0')) {
    if (DAT_00584640 != 0) {
      if (DAT_0058464c == 0) {
        sub_419280();
        sub_426890();
        sub_426BF0();
        sub_4277B0();
      }
      if ((DAT_00585000 != 0) && (DAT_00573404 != 0)) {
        DAT_00573404 = 0;
      }
      if (DAT_0058464c == 0) {
        sub_4146B0(0x60);
      }
      return;
    }
    DAT_00573400 = 0;
    sub_426BF0();
    sub_4277B0();
    return;
  }
  DAT_005fd0b4 = DAT_005fd0b4 + 1 & 0x1f;
  sub_4277B0();
  return;
}

