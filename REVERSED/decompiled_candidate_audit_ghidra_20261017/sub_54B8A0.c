/* Selected Ghidra export at 0054b8a0. */

void sub_54B8A0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_5c [19];
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_00584c30 == 0) {
    uStack_c = 0x54b8c1;
    sub_425BB0();
    uStack_c = 0x54b8c6;
    sub_425C00();
    uStack_c = 0;
    DAT_00584640 = 1;
    uStack_10 = 0x54b8d7;
    sub_40DD60();
  }
  else {
    uStack_c = 0x54b8b0;
    sub_41CDD0();
    uStack_c = 0x54b8b5;
    sub_425BB0();
    uStack_c = 0x54b8ba;
    sub_425C00();
  }
  uStack_c = 1;
  puVar2 = (undefined4 *)(PTR_DAT_005724dc + 0x118);
  puVar3 = auStack_5c;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  sub_40E0C0(PTR_DAT_005724dc + 0x18);
  uStack_c = 0x54b904;
  sub_41A220();
  return;
}

