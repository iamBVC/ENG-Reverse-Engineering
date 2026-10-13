/* Selected Ghidra export at 0054fcf0. */

void sub_54FCF0(int *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[0x3a] | *(uint *)*param_1;
  *param_1 = (int)((uint *)*param_1 + 1);
  param_1[0x3a] = uVar1;
  if ((uVar1 & 0x34000) != 0) {
    param_1[0x3b] = param_1[0x3b] | 0x4000;
  }
  return;
}

