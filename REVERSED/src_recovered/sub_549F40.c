/* Selected Ghidra export at 00549f40. */

undefined4 sub_549F40(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    if (DAT_00584638 == 1) {
      sub_415390(8);
      DAT_00584700 = 7;
    }
    if (DAT_00584638 == 10) {
      sub_415390(1);
      sub_549BD0();
    }
    if (DAT_00584638 == 2) {
      sub_415390(1);
      DAT_00584700 = 9;
    }
    if (DAT_00584638 == 8) {
      sub_415390(1);
      DAT_00584700 = 2;
    }
    if (DAT_00584638 == 4) {
      sub_415390(1);
      DAT_00584700 = 10;
    }
    if (DAT_00584638 == 3) {
      sub_415390(1);
      DAT_00584700 = 0xb;
    }
    if (DAT_00584638 == 5) {
      sub_415390(1);
      DAT_00584700 = 3;
    }
    if (DAT_00584638 == 9) {
      sub_415390(1);
      DAT_00584700 = 0xc;
    }
    if (((DAT_005fcf18 == 0) || (DAT_005fcf18 == 1)) || (((byte)DAT_005fcf44 & 9) != 9)) {
      DAT_005863f8 = 0;
      return 0;
    }
    DAT_005863f8 = DAT_005863f8 + 1;
    if (DAT_005863f8 == 0x1e) {
      sub_415390(1);
      DAT_00584700 = 2;
    }
  }
  else {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      sub_4155E0();
      if (DAT_00584638 == 10) {
        sub_549C00();
      }
      if (DAT_00584638 != 6) {
        sub_546CC0();
        DAT_00586430 = 0;
        sub_546990(DAT_006d94b4);
        sub_546300();
        sub_5464D0();
        DAT_005846e4 = DAT_00584700;
        return 1;
      }
    }
  }
  return 0;
}

