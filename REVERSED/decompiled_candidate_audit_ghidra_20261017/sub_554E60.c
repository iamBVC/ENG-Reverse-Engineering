/* Selected Ghidra export at 00554e60. */

void sub_554E60(int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (DAT_006d9e28 == 0) {
    *param_1 = *param_1 + -4;
    param_1[0x3a] = param_1[0x3a] | 2;
    return;
  }
  iVar1 = param_1[1];
  iVar2 = iVar1;
  if (param_1[2] != 0) {
    *(int *)(param_1[2] + 4) = iVar1;
    iVar2 = (int)DAT_006d9e38;
  }
  DAT_006d9e38 = (int *)iVar2;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 8) = param_1[2];
  }
  if (*(int *)(DAT_006d9e28 + 8) == 0) {
    DAT_006d9e38 = param_1;
    param_1[2] = 0;
    param_1[1] = DAT_006d9e28;
    *(int **)(DAT_006d9e28 + 8) = param_1;
    return;
  }
  *(int **)(*(int *)(DAT_006d9e28 + 8) + 4) = param_1;
  param_1[2] = *(int *)(DAT_006d9e28 + 8);
  *(int **)(DAT_006d9e28 + 8) = param_1;
  param_1[1] = DAT_006d9e28;
  return;
}

