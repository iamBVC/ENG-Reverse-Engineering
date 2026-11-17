/* Selected Ghidra export at 00553c90. */

void sub_553C90(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) - iVar1 & 0xffffff;
  return;
}

