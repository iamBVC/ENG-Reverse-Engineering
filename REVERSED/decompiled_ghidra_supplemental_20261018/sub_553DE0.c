/* Selected Ghidra export at 00553de0. */

void sub_553DE0(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  sub_54BBD0(param_1,iVar1 - **(int **)(param_1[0x41] + -4));
  return;
}

