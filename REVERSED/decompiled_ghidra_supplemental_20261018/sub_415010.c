/* Selected Ghidra export at 00415010. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_415010(void)

{
  _DAT_00583714 = 9;
  DAT_00583734 = 1;
  DAT_00583738 = 0;
  if ((int)DAT_0058370c < 0xff) {
    DAT_00583730 = 1;
    DAT_0058373c = (DAT_0058370c & ((int)DAT_0058370c < 1) - 1) << 0x18;
    return;
  }
  DAT_00583730 = 1;
  DAT_0058373c = 0xff000000;
  return;
}

