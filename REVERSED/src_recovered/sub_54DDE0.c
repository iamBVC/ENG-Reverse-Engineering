/* Selected Ghidra export at 0054dde0. */

void sub_54DDE0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_006d9e1c != 0) {
    puVar2 = (undefined4 *)(DAT_006d9e1c + 0x20);
    puVar3 = (undefined4 *)(param_1 + 0x20);
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

