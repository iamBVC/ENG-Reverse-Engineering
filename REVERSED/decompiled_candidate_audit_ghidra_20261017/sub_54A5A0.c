/* Selected Ghidra export at 0054a5a0. */

undefined4 sub_54A5A0(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    if (DAT_006d9bd0 != 0) {
      sub_415390(1);
    }
  }
  else {
    iVar1 = sub_414FB0();
    if (iVar1 != 0) {
      sub_546CC0();
      DAT_00586430 = 0;
      sub_546990(DAT_006d94b4);
      sub_5464D0();
      sub_41F630(s_CREDITS_dat_00578f70,3000);
      if ((DAT_00584710 & 4) != 0) {
        DAT_00584700 = 2;
        DAT_005846e4 = 2;
        DAT_00584710 = DAT_00584710 & 0xfffffffb;
        return 1;
      }
      DAT_00584700 = 0xc;
      DAT_005846e4 = 0xc;
      return 1;
    }
  }
  return 0;
}

