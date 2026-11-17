/* Selected Ghidra export at 0054fd40. */

void sub_54FD40(int *param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)*param_1;
  *param_1 = (int)((uint *)*param_1 + 1);
  param_1[0x3a] = param_1[0x3a] & ~uVar1;
  return;
}

