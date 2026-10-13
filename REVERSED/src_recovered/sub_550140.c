/* Selected Ghidra export at 00550140. */

void sub_550140(int param_1)

{
  DAT_006d9e1c = param_1;
  *(uint *)(param_1 + 0xe8) = *(uint *)(param_1 + 0xe8) | 0x800;
  return;
}

