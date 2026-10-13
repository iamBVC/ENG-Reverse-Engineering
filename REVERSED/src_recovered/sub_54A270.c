/* Selected Ghidra export at 0054a270. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_54A270(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    if (DAT_005855a4 == '\0') {
      if ((DAT_006d9c18 == 0) && ((DAT_00584c1c == 0x10 || (DAT_00584c1c == 0x15)))) {
        DAT_005855a4 = 1;
        DAT_006da2f8 = 0x1000;
        return 0;
      }
      if ((DAT_005fcf08 & 0x8000) != 0) {
        iVar1 = sub_41CCC0();
        if (iVar1 != 0) {
          DAT_005855a4 = '\x01';
          DAT_006da2f8 = 0x1000;
          sub_546170(0,0xffffff81,8);
        }
      }
      if ((DAT_005fcf08 & 0x1000) != 0) {
        sub_546170(0,0xffffff82,8);
        sub_415390(1);
        sub_54A1E0(1);
      }
      if ((DAT_005fcf08 & 0x4000) != 0) {
        iVar1 = sub_41CC70();
        if (iVar1 == 1) {
          DAT_005855a4 = 1;
          DAT_006da2f8 = 0x1000;
          sub_546170(0,0xffffff81,8);
          return 0;
        }
        if (iVar1 == 2) {
          sub_546170(0,0xffffff81,8);
          sub_415390(1);
          sub_54A1E0(1);
          return 0;
        }
        if (iVar1 == 3) {
          sub_546170(0,0xffffff81,8);
          sub_415390(1);
          sub_54A1E0(0);
        }
      }
    }
    else if (DAT_006da2f8 == 0x64000) {
      sub_415390(1);
      sub_54A1E0(0);
      if (DAT_00584c1c == 0x16) {
        DAT_00584c28 = 0xffffffff;
        DAT_006da2fc = 0;
        _DAT_00584c18 = 0;
        return 0;
      }
    }
  }
  else {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      sub_546CC0();
      DAT_00586430 = 0;
      sub_546990(DAT_006d94b4);
      sub_5464D0();
      DAT_005846e4 = DAT_00584700;
      return 1;
    }
  }
  return 0;
}

