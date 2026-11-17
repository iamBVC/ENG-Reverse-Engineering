/* Selected Ghidra export at 0054a180. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_54A180(void)

{
  int iVar1;
  
  if (DAT_0058372c == 0) {
    iVar1 = sub_419280();
    if (iVar1 == 1) {
      sub_415390(1);
    }
    else if (iVar1 == 2) {
      return 1;
    }
  }
  else {
    iVar1 = sub_414FB0();
    if ((iVar1 != 0) && (DAT_00584700 == 1)) {
      DAT_005846e4 = 2;
      _DAT_005863f0 = 0;
      return 1;
    }
  }
  return 0;
}

