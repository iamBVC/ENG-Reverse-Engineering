/* Selected Ghidra export at 0054f260. */

void sub_54F260(int param_1)

{
  int iVar1;
  
  iVar1 = **(int **)(param_1 + 0x120);
  *(int *)(param_1 + 0x120) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x118);
  }
  return;
}

