/* Selected Ghidra export at 0054dc20. */

void sub_54DC20(int param_1,int param_2)

{
  *(uint *)(param_2 * 0x10 + *(int *)(param_1 + 0xf8)) =
       *(uint *)(param_2 * 0x10 + *(int *)(param_1 + 0xf8)) | 0x80000000;
  return;
}

