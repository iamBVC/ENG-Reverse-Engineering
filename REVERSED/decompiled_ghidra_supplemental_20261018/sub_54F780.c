/* Selected Ghidra export at 0054f780. */

void sub_54F780(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (iVar1 != 0) {
    param_1[0x3b] = param_1[0x3b] | 0x400000;
    return;
  }
  param_1[0x3b] = param_1[0x3b] & 0xffbfffff;
  return;
}

