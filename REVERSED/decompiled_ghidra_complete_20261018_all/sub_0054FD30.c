/* sub_54FD30 @ 0054FD30 15 bytes */
/* Selected Ghidra export at 0054fd30. */

void sub_54FD30(int param_1)

{
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) & 0xfff81fff;
  return;
}

