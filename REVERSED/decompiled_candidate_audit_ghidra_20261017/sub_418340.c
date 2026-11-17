/* Selected Ghidra export at 00418340. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_418340(void)

{
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    if (DAT_00573d40 < _DAT_0056e210) {
      sub_546170(0,0xffffff80,8);
      DAT_006da2fc = 0xf000;
    }
    DAT_00573d40 = DAT_00573d40 + _DAT_0056e214;
  }
  else {
    if (_DAT_0056e218 < DAT_00573d40) {
      sub_546170(0,0xffffff80,8);
      DAT_006da2fc = 0xf000;
    }
    DAT_00573d40 = DAT_00573d40 - _DAT_0056e214;
  }
  if (_DAT_0056e218 <= DAT_00573d40) {
    if (_DAT_0056e210 < DAT_00573d40) {
      DAT_00573d40 = 1.8;
    }
  }
  else {
    DAT_00573d40 = 0.2;
  }
  sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
  return 0;
}

