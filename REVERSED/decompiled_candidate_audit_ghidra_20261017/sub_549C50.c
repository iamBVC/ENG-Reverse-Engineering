/* Selected Ghidra export at 00549c50. */

undefined4 sub_549C50(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    if (DAT_006d9c1c == 0) {
      if (((DAT_005fcf08 & 0x4000) != 0) && (DAT_005863f4 = DAT_00584650, DAT_0058463c == 2)) {
        sub_546170(0,0xffffff81,8);
        DAT_006d9c20 = 0;
        DAT_006d9c1c = 1;
        return 0;
      }
      if ((uint)(DAT_00584650 - DAT_005863f4) < 0x709) {
        if ((DAT_005fcf08 & 0x4000) == 0) goto LAB_00549cfb;
        DAT_005863f4 = DAT_00584650;
LAB_00549e17:
        sub_546170(0,0xffffff81,8);
        sub_415390(1);
        DAT_00584700 = 3;
      }
      else {
        DAT_005863f4 = DAT_00584650;
        sub_415390(1);
        DAT_00584eb4 = 1;
        DAT_00584eb8 = 1;
        DAT_00584ebc = 1;
        DAT_00584700 = 4;
      }
    }
    else {
      DAT_005863f4 = DAT_00584650;
      if (((DAT_005fcf08 & 0x80) != 0) && (DAT_006d9c20 == 0)) {
        DAT_006d9c20 = 1;
        sub_546170(0,0xffffff80,8);
      }
      if (((DAT_005fcf08 & 0x20) != 0) && (DAT_006d9c20 != 0)) {
        DAT_006d9c20 = 0;
        sub_546170(0,0xffffff80,8);
      }
      if ((DAT_005fcf08 & 0x4000) != 0) {
        if (DAT_006d9c20 != 0) goto LAB_00549e17;
        DAT_006d9c1c = 0;
        sub_546170(0,0xffffff81,8);
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
      if (DAT_00584700 == 4) {
        DAT_005846e4 = DAT_00584700;
        iVar1 = DAT_006d9bf8 * 0x10;
        DAT_006d9bf8 = DAT_006d9bf8 + 1;
        DAT_00584eb4 = *(undefined4 *)(&DAT_00578efc + iVar1);
        DAT_00584eb8 = *(undefined4 *)(&DAT_00578f00 + iVar1);
        DAT_00584ebc = *(undefined4 *)(&DAT_00578f04 + iVar1);
        DAT_00584ec0 = *(undefined4 *)(&DAT_00578ef8 + iVar1);
        if (DAT_006d9bf8 == 3) {
          DAT_006d9bf8 = 0;
        }
        return 1;
      }
      if (DAT_00584700 == 0xc) {
        DAT_005846e4 = DAT_00584700;
        return 1;
      }
      if (DAT_00584700 == 10) {
        DAT_005846e4 = DAT_00584700;
        return 1;
      }
      if (DAT_0058463c == 0) {
        DAT_005855b0 = 1;
        DAT_005846e4 = 6;
      }
      else {
        if (DAT_0058463c == 1) {
          DAT_005846e4 = 5;
          return 1;
        }
        if (DAT_0058463c == 2) {
          DAT_005846e4 = 0x11;
          return 1;
        }
      }
      return 1;
    }
  }
  if (DAT_0058372c != 0) {
    return 0;
  }
  if (DAT_006d9c1c != 0) {
    return 0;
  }
LAB_00549cfb:
  if (((DAT_005fcf08 & 0x10) != 0) && (DAT_0058463c != 0)) {
    sub_546170(0,0xffffff80,8);
    DAT_005863f4 = DAT_00584650;
    DAT_0058463c = DAT_0058463c - 1;
  }
  if (((DAT_005fcf08 & 0x40) != 0) && (DAT_0058463c < 2)) {
    sub_546170(0,0xffffff80,8);
    DAT_005863f4 = DAT_00584650;
    DAT_0058463c = DAT_0058463c + 1;
  }
  return 0;
}

