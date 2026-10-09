/* sub_419280 @ 00419280   344 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_419280(void)

{
  int iVar1;
  
  if (DAT_00583b70 == (undefined *)0x0) {
    sub_4191C0();
  }
  if (DAT_00584640 == 0) {
    DAT_00584370 = DAT_00584370 & 0xffffffef;
    _DAT_00571da8 = 8;
    _DAT_00571da4 = 0x14;
  }
  else {
    DAT_00584370 = DAT_00584370 | 0x10;
    _DAT_00571da8 = 10;
    _DAT_00571da4 = 0x12;
  }
  _DAT_00584364 = (uint)(DAT_00584640 == 0);
  iVar1 = sub_418EE0(DAT_00583b70);
  if ((iVar1 == 1) && (DAT_00583b70 == &DAT_00571da0)) {
    if (DAT_00584640 != 0) {
      DAT_005fcf38 = 0x1000;
      DAT_005fcf20 = 0x1000;
      sub_425C00();
      sub_425BB0();
      DAT_00584640 = 0;
      sub_545EB0();
    }
    return 1;
  }
  sub_418D80(DAT_00583b70);
  if (DAT_00583b78 == 1) {
    return 2;
  }
  if (((DAT_005fcf08 & 0x1000) != 0) && (DAT_00583a68 == -1)) {
    sub_4170E0();
    sub_546170(0,0xffffff80,8);
    sub_424680();
    if (DAT_00583b70 == &DAT_00571da0) {
      DAT_00584700 = 1;
      if (DAT_00584640 != 0) {
        if (DAT_00573400 != '\x10') {
          DAT_00573400 = '\x0f';
        }
        DAT_00584640 = 0;
        sub_545EB0();
      }
      return 1;
    }
    DAT_00583b70 = (undefined *)sub_4170C0();
  }
  return 0;
}

