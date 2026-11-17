/* Selected Ghidra export at 0054dd60. */

void sub_54DD60(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) | 0x200000;
    return;
  }
  *(uint *)(param_1 + 0xec) = *(uint *)(param_1 + 0xec) & 0xffdfffff;
  return;
}

