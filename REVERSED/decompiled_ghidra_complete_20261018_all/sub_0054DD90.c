/* sub_54DD90 @ 0054DD90 44 bytes */
/* Selected Ghidra export at 0054dd90. */

void sub_54DD90(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x80000000;
    return;
  }
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) & 0x7fffffff;
  return;
}

