/* Selected Ghidra export at 0054e090. */

void sub_54E090(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) | 2;
    return;
  }
  *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) & 0xfffffffd;
  return;
}

