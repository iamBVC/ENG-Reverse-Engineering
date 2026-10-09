/* sub_425BB0 @ 00425bb0   67 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_425BB0(void)

{
  uint uVar1;
  
  uVar1 = DAT_005fcf50;
  DAT_005fcf50 = DAT_005fcf44;
  DAT_005fcf08 = ~uVar1 & DAT_005fcf44;
  _DAT_005fcf10 = ~DAT_005fcf44 & uVar1;
  DAT_005fcf1c = ~DAT_005fcf1c;
  DAT_005fcf2c = ~DAT_005fcf2c;
  return;
}

