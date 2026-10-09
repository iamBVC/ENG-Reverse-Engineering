/* sub_41CDD0 @ 0041cdd0   89 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41CDD0(void)

{
  int iVar1;
  
  iVar1 = sub_414FB0();
  if (iVar1 == 0) {
    DAT_005fcf30 = 0;
    DAT_005fcf08 = 0;
  }
  if (DAT_00584c1c != 0) {
    if (DAT_00584c1c == 0xf) {
      _DAT_005855c4 = 1;
      sub_41C620();
      sub_41C820();
      DAT_00584c1c = 0x10;
    }
    else if ((DAT_00584c1c == 0x10) && (DAT_006d9c18 != 0)) {
      sub_41CD10();
      return;
    }
    return;
  }
  sub_41C1A0();
  return;
}

