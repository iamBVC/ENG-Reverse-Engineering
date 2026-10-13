/* Selected Ghidra export at 00554e20. */

void sub_554E20(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(*(int *)(param_1 + 8) + 4) = iVar1;
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(param_1 + 8);
    }
    *(undefined4 *)(param_1 + 8) = 0;
    *(int *)(param_1 + 4) = DAT_006d9e38;
    *(int *)(DAT_006d9e38 + 8) = param_1;
    DAT_006d9e38 = param_1;
  }
  return;
}

