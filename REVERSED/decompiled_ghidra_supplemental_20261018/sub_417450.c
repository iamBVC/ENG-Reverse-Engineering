/* Selected Ghidra export at 00417450. */

undefined4 sub_417450(void)

{
  if (((byte)DAT_005fcf08 & 0xa0) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_00573d35 = DAT_00573d35 ^ 1;
    DAT_006da2fc = 0xf000;
  }
  DAT_006d8731 = 1;
  sub_438180();
  sub_439600();
  sub_417260();
  return 0;
}

