/* Selected Ghidra export at 0054d830. */

void sub_54D830(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_006d9e28 != 0) {
    puVar2 = (undefined4 *)(param_1 + 0x20);
    puVar3 = (undefined4 *)(DAT_006d9e28 + 0x20);
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    DAT_006d9d20 = *(undefined4 *)(param_1 + 0x30);
    DAT_006d9d24 = *(undefined4 *)(param_1 + 0x34);
    DAT_006d9d28 = *(undefined4 *)(param_1 + 0x38);
    DAT_006d9d2c = *(undefined4 *)(param_1 + 0x3c);
  }
  return;
}

