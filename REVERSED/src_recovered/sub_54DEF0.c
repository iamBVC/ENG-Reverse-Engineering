/* Selected Ghidra export at 0054def0. */

void sub_54DEF0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  DAT_00584644 = DAT_006da28c;
  if (DAT_006d9e1c != 0) {
    sub_54DE00(DAT_006d9e1c,DAT_006da28c);
    puVar2 = &DAT_006d9e48;
    puVar3 = (undefined4 *)(DAT_006d9e1c + 0x20);
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

