/* Selected Ghidra export at 0054a8a0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_54A8A0(void)

{
  int iVar1;
  
  if (DAT_00584c30 == 1) {
    if (DAT_0058372c != 0) {
      if (DAT_005855bc == 0) {
        DAT_00584c30 = 2;
        return 0;
      }
      iVar1 = sub_414FB0();
      if (iVar1 == 0) {
        return 0;
      }
      sub_546CC0();
      DAT_00586430 = 0;
      sub_546990(DAT_006d94b4);
      sub_5464D0();
      DAT_005846e4 = DAT_00584700;
      return 1;
    }
    if (DAT_005855bc != 0) {
      DAT_005855b0 = 0;
      sub_415390(1);
      DAT_00584700 = 6;
      _DAT_005855ac = 1;
      sub_41C180();
      return 0;
    }
    if (DAT_005855a4 == '\0') {
      if ((DAT_006d9c18 == 0) && ((DAT_00584c1c == 0x10 || (DAT_00584c1c == 0x15)))) {
        DAT_005855a4 = 1;
        DAT_006da2f8 = 0x64000;
        return 0;
      }
      if ((DAT_005fcf08 & 0x1000) != 0) {
        sub_546170(0,0xffffff82,8);
        sub_415390(1);
        sub_54A870(1);
      }
      if ((DAT_005fcf08 & 0x4000) == 0) {
        return 0;
      }
      iVar1 = sub_41CC70();
      if (iVar1 == 1) {
        DAT_005855a4 = 1;
        DAT_006da2f8 = 0x64000;
        sub_546170(0,0xffffff81,8);
        return 0;
      }
      if (iVar1 != 2) {
        if (iVar1 != 3) {
          return 0;
        }
        sub_546170(0,0xffffff81,8);
        sub_415390(1);
        sub_54A870(0);
        return 0;
      }
      sub_546170(0,0xffffff81,8);
      sub_415390(1);
      sub_54A870(1);
      return 0;
    }
    if (DAT_006da2f8 != 0x64000) {
      return 0;
    }
    sub_415390(1);
    sub_54A870(0);
    return 0;
  }
  if (DAT_0058372c != 0) {
    iVar1 = sub_414FB0();
    if (iVar1 == 0) {
      return 0;
    }
    sub_546CC0();
    DAT_00586430 = 0;
    sub_546990(DAT_006d94b4);
    sub_43C940();
    DAT_005855b0 = 0;
    if ((DAT_0058500c == 8) && (DAT_00585010 == 6)) {
      DAT_005846e4 = 10;
      DAT_00584700 = 10;
      return 1;
    }
    DAT_005846e4 = DAT_00584700;
    return 1;
  }
  if ((DAT_005fcf30 & 0x1000) != 0) {
    if (DAT_006d9c08 != 0) goto LAB_0054aa8e;
    DAT_006d9c08 = 1;
    DAT_006d9c0c = 0;
    sub_546170(0,0xffffff81,8);
  }
  if (DAT_006d9c08 == 0) {
    if ((DAT_005fcf30 & 0x4000) == 0) {
      return 0;
    }
    sub_546170(0,0xffffff81,8);
    sub_41C620();
    sub_41C820();
    sub_41CBE0();
    DAT_00584c30 = 0;
    sub_546170(0,0xffffff81,8);
    sub_415390(1);
    sub_54A840();
    return 0;
  }
LAB_0054aa8e:
  if ((DAT_005fcf30 & 0xa0) != 0) {
    DAT_006d9c10 = DAT_006d9c10 ^ 1;
    sub_546170(0,0xffffff80,8);
  }
  if ((DAT_005fcf30 & 0x4000) != 0) {
    sub_546170(0,0xffffff81,8);
    if (DAT_006d9c10 == 0) {
      DAT_006d9c08 = 0;
      return 0;
    }
    if (DAT_006d9c0c == 0) {
      DAT_00584c30 = 0;
      sub_546170(0,0xffffff81,8);
      sub_415390(1);
      sub_54A840();
      return 0;
    }
    DAT_00584c30 = 1;
    if (DAT_005855bc == 0) {
      sub_41CDB0();
    }
    DAT_005fcf08 = 0;
    DAT_005fcf30 = 0;
  }
  return 0;
}

