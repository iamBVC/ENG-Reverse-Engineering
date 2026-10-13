/* Selected Ghidra export at 0054fa80. */

void sub_54FA80(int *param_1,int param_2)

{
  if (DAT_006d9e1c == 0) {
    *param_1 = *param_1 + -4;
    param_1[0x3a] = param_1[0x3a] | 2;
    return;
  }
  if (param_2 != 0) {
    param_1[0x3b] = param_1[0x3b] | 0x4000;
    return;
  }
  param_1[0x3b] = param_1[0x3b] & 0xffffbfff;
  return;
}

