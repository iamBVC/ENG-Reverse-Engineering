/* Selected Ghidra export at 00553cf0. */

void sub_553CF0(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) - iVar1 & 0xffffff;
  return;
}

