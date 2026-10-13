/* Selected Ghidra export at 0054f750. */

void sub_54F750(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar1 != 0) {
    param_1[0x3b] = param_1[0x3b] | 0x80;
    return;
  }
  param_1[0x3b] = param_1[0x3b] & 0xffffff7f;
  return;
}

