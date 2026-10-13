/* Selected Ghidra export at 004174a0. */

undefined4 sub_4174A0(void)

{
  if (((byte)DAT_005fcf08 & 0xa0) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_00573d34 = DAT_00573d34 ^ 1;
    DAT_006da2fc = 0xf000;
  }
  DAT_006d8731 = 1;
  sub_438180();
  sub_439600();
  sub_417260();
  sub_408300();
  sub_4071D0();
  sub_437D00();
  return 0;
}

