/* Selected Ghidra export at 00415070. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_415070(void)

{
  uint uVar1;
  
  if (DAT_00583710 * 2 + 0x100 < (int)DAT_0058370c) {
    sub_414FE0();
  }
  _DAT_00583714 = 9;
  DAT_00583734 = 1;
  DAT_00583738 = 0;
  if ((int)DAT_0058370c < 0xff) {
    uVar1 = ((int)DAT_0058370c < 1) - 1 & DAT_0058370c;
  }
  else {
    uVar1 = 0xff;
  }
  DAT_0058373c = uVar1 << 0x18;
  DAT_0058370c = DAT_0058370c + DAT_00583710;
  return;
}

