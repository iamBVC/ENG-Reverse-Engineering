/* Selected Ghidra export at 0054b860. */

void sub_54B860(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_5c [20];
  undefined4 uStack_c;
  
  uStack_c = 1;
  puVar2 = (undefined4 *)(PTR_DAT_005724dc + 0x118);
  puVar3 = auStack_5c;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  sub_40E0C0(PTR_DAT_005724dc + 0x18);
  uStack_c = 0x54b88c;
  sub_41A220();
  uStack_c = 0x54b891;
  sub_425BB0();
  uStack_c = 0x54b896;
  sub_425C00();
  return;
}

