/* Selected Ghidra export at 0054f720. */

void sub_54F720(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) | 0x10000;
    return;
  }
  *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) & 0xfffeffff;
  return;
}

