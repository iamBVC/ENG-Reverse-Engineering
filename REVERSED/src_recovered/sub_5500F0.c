/* Selected Ghidra export at 005500f0. */

void sub_5500F0(int param_1)

{
  DAT_006d9e28 = param_1;
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x8000000;
  return;
}

