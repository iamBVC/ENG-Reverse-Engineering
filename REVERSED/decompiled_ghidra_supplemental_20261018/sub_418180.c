/* Selected Ghidra export at 00418180. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_418180(void)

{
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    if (DAT_00573d3c < _DAT_0056e008) {
      sub_546170(0,0xffffff80,8);
      DAT_006da2fc = 0xf000;
    }
    DAT_00573d3c = DAT_00573d3c + _DAT_0056e204;
  }
  else {
    if (_DAT_0056e208 < DAT_00573d3c) {
      sub_546170(0,0xffffff80,8);
      DAT_006da2fc = 0xf000;
    }
    DAT_00573d3c = DAT_00573d3c - _DAT_0056e204;
  }
  if (_DAT_0056e208 <= DAT_00573d3c) {
    if (_DAT_0056e008 < DAT_00573d3c) {
      DAT_00573d3c = 1.0;
    }
  }
  else {
    DAT_00573d3c = 0.1;
  }
  sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
  return 0;
}

