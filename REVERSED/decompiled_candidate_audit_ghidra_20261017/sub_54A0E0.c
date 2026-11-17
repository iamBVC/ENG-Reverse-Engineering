/* Selected Ghidra export at 0054a0e0. */

undefined4 sub_54A0E0(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    if ((0x1d < DAT_005fcf54) && (iVar1 = sub_40E630(), iVar1 == 0)) {
      return 0;
    }
    sub_415390(1);
    if (DAT_005fcf44 != 0) {
      sub_546170(0,0xffffff81,8);
    }
  }
  else {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      sub_5464D0();
      sub_546CC0();
      DAT_00586430 = 0;
      sub_546990(DAT_006d94b4);
      DAT_00584eb4 = 1;
      DAT_00584eb8 = 1;
      DAT_00584ebc = 1;
      DAT_00584ec0 = 0;
      DAT_005846e4 = 2;
      DAT_00584700 = 2;
      return 1;
    }
  }
  return 0;
}

