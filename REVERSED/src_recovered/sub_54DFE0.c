/* Selected Ghidra export at 0054dfe0. */

void sub_54DFE0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x120);
  *(int *)(param_1 + 0x20) = *(int *)(iVar1 + 8) << 0xc;
  *(int *)(param_1 + 0x24) = *(int *)(iVar1 + 0xc) << 0xc;
  *(int *)(param_1 + 0x28) = *(int *)(iVar1 + 0x10) << 0xc;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(iVar1 + 0x18);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(iVar1 + 0x1c);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar1 + 0x20);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar1 + 0x24);
  return;
}

