/* Selected Ghidra export at 0054dec0. */

void sub_54DEC0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  DAT_006da28c = DAT_00584644;
  if (DAT_006d9e1c != 0) {
    puVar2 = (undefined4 *)(DAT_006d9e1c + 0x20);
    puVar3 = &DAT_006d9e48;
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

