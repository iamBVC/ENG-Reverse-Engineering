/* sub_41CD10 @ 0041cd10   96 bytes */

void sub_41CD10(void)

{
  int iVar1;
  
  if (DAT_00573401 == '\0') {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      if ((2 < DAT_005724bc) && (DAT_005724bc < 5)) {
        DAT_00573401 = 2;
        DAT_005fcf30 = 0;
        return;
      }
      sub_41C1C0();
      return;
    }
  }
  else if (DAT_00573401 == '\x02') {
    iVar1 = sub_41CBE0();
    if (iVar1 != 0) {
      sub_41C1C0();
      return;
    }
    DAT_00573401 = '\x03';
  }
  DAT_005fcf30 = 0;
  return;
}

