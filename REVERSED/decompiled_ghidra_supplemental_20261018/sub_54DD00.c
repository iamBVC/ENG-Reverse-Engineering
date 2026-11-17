/* Selected Ghidra export at 0054dd00. */

void sub_54DD00(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar1 != 0) {
    param_1[0x3b] = param_1[0x3b] | 0x200;
    return;
  }
  param_1[0x3b] = param_1[0x3b] & 0xfffffdff;
  return;
}

