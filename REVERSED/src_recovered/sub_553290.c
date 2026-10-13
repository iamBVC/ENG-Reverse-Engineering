/* Selected Ghidra export at 00553290. */

void sub_553290(int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (DAT_006d9e24 == 0) {
    *param_1 = *param_1 + -4;
    param_1[0x3a] = param_1[0x3a] | 2;
    return;
  }
  iVar1 = param_1[1];
  iVar2 = iVar1;
  if (param_1[2] != 0) {
    *(int *)(param_1[2] + 4) = iVar1;
    iVar2 = DAT_006d9e38;
  }
  DAT_006d9e38 = iVar2;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 8) = param_1[2];
  }
  iVar1 = *(int *)(DAT_006d9e24 + 4);
  param_1[1] = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  param_1[2] = DAT_006d9e24;
  *(int **)(DAT_006d9e24 + 4) = param_1;
  return;
}

