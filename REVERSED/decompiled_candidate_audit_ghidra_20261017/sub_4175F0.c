/* Selected Ghidra export at 004175f0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_4175F0(void)

{
  if (((byte)DAT_005fcf08 & 0x80) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_005848cc = DAT_005848cc - _DAT_0056e158;
    DAT_006da2fc = 0xf000;
    if (DAT_005848cc < _DAT_0056e00c) {
      DAT_005848cc = 1.0;
    }
  }
  if (((byte)DAT_005fcf08 & 0x20) != 0) {
    sub_546170(0,0xffffff80,8);
    DAT_005848cc = DAT_005848cc + _DAT_0056e158;
    DAT_006da2fc = 0xf000;
    if (_DAT_0056e008 < DAT_005848cc) {
      DAT_005848cc = 0.0;
    }
  }
  sub_417260();
  return 0;
}

