/* Selected Ghidra export at 0054e8e0. */

void sub_54E8E0(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x20;
    return;
  }
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) & 0xffffffdf;
  return;
}

