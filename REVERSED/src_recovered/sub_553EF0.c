/* Selected Ghidra export at 00553ef0. */

void sub_553EF0(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *param_1;
  piVar2 = (int *)(iVar3 + 4);
  *param_1 = (int)piVar2;
  iVar1 = *piVar2;
  iVar3 = iVar3 + 8;
  *param_1 = iVar3;
  param_1[6] = iVar3 + iVar1;
  return;
}

