/* Selected Ghidra export at 0054fa50. */

void sub_54FA50(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x1000000;
    return;
  }
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) & 0xfeffffff;
  return;
}

