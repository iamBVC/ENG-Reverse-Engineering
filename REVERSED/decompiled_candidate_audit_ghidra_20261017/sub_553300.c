/* Selected Ghidra export at 00553300. */

void sub_553300(int *param_1)

{
  int *piVar1;
  int *piVar2;
  
  if (DAT_006d9e1c == 0) {
    *param_1 = *param_1 + -4;
    param_1[0x3a] = param_1[0x3a] | 2;
    return;
  }
  piVar1 = (int *)param_1[1];
  piVar2 = piVar1;
  if (param_1[2] != 0) {
    *(int **)(param_1[2] + 4) = piVar1;
    piVar2 = DAT_006d9e38;
  }
  DAT_006d9e38 = piVar2;
  if (piVar1 != (int *)0x0) {
    piVar1[2] = param_1[2];
  }
  if (*(int *)(DAT_006d9e1c + 8) == 0) {
    DAT_006d9e38 = param_1;
  }
  else {
    *(int **)(*(int *)(DAT_006d9e1c + 8) + 4) = param_1;
  }
  param_1[2] = *(int *)(DAT_006d9e1c + 8);
  param_1[1] = DAT_006d9e1c;
  *(int **)(DAT_006d9e1c + 8) = param_1;
  return;
}

