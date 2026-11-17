/* Selected Ghidra export at 0054ddc0. */

void sub_54DDC0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(DAT_006d9e24 + 0x20);
  puVar3 = (undefined4 *)(param_1 + 0x20);
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}

