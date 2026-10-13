/* Selected Ghidra export at 0054fdd0. */

void sub_54FDD0(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar1 != 0) {
    param_1[0x3a] = param_1[0x3a] | 0x1000;
    return;
  }
  param_1[0x3a] = param_1[0x3a] & 0xffffefff;
  return;
}

