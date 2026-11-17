/* Selected Ghidra export at 0054dc00. */

void sub_54DC00(int param_1,int param_2)

{
  *(uint *)(param_2 * 0x10 + *(int *)(param_1 + 0xf8)) =
       *(uint *)(param_2 * 0x10 + *(int *)(param_1 + 0xf8)) & 0x7fffffff;
  return;
}

