/* Selected Ghidra export at 0054a650. */

undefined4 sub_54A650(void)

{
  int iVar1;
  
  if (DAT_005846e4 == 0xc) {
    if (DAT_0058372c == 0) {
      if (DAT_00584c04 == 0) {
        if ((DAT_00584c0e == 0) && (DAT_00584bf0 == 0)) {
          if (((DAT_005fcf08 & 0x1000) != 0) && (DAT_005849a8 == 0)) {
            sub_546170(0,0xffffff82,8);
            DAT_00584c04 = 1;
            DAT_00584c08 = 0;
          }
          if (((((&DAT_00584ece)[DAT_00584c0c * 6 + (int)DAT_0057235a] & 1) != 0) &&
              (((&DAT_00584ece)[DAT_00584c0c * 6 + (int)DAT_0057235a] & 2) != 0)) &&
             ((DAT_005fcf08 & 0x8000) != 0)) {
            sub_546170(0,0xffffff81,8);
            sub_415390(1);
            DAT_00584700 = 0x10;
          }
          if (((DAT_005fcf08 & 0x4000) != 0) && (DAT_00584eb8 < 99)) {
            sub_546170(0,0xffffff81,8);
            sub_415390(1);
            DAT_00584700 = (DAT_00584eb8 != 0) + 2;
            return 0;
          }
        }
      }
      else {
        if (((DAT_005fcf08 & 0x80) != 0) && (DAT_00584c08 == 0)) {
          sub_546170(0,0xffffff80,8);
          DAT_00584c08 = 1;
        }
        if (((DAT_005fcf08 & 0x20) != 0) && (DAT_00584c08 != 0)) {
          sub_546170(0,0xffffff80,8);
          DAT_00584c08 = 0;
        }
        if ((DAT_005fcf08 & 0x4000) != 0) {
          if (DAT_00584c08 == 0) {
            DAT_00584c04 = 0;
            return 0;
          }
          sub_546170(0,0xffffff81,8);
          sub_415390(1);
          DAT_005855b0 = 1;
          DAT_00584700 = 6;
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
        DAT_00584638 = 0;
        DAT_005846e4 = DAT_00584700;
        return 1;
      }
    }
  }
  return 0;
}

