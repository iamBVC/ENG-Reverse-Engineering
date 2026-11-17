/* sub_425C00 @ 00425c00   67 bytes */

void sub_425C00(void)

{
  uint uVar1;
  
  uVar1 = DAT_005fcf38;
  DAT_005fcf38 = DAT_005fcf20;
  DAT_005fcf30 = ~uVar1 & DAT_005fcf20;
  DAT_005fcf34 = ~DAT_005fcf20 & uVar1;
  DAT_005fcf60 = ~DAT_005fcf40 & DAT_005fcf58;
  DAT_005fcf40 = DAT_005fcf58;
  return;
}

