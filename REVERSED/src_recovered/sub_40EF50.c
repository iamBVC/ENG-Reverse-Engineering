/* Selected Ghidra export at 0040ef50. */

undefined4 sub_40EF50(int param_1,int param_2)

{
  if ((*(uint *)(param_2 + 0x5c) & 0x80000000) != 0) {
    *(undefined4 *)(param_2 + 0x5c) = *(undefined4 *)(param_1 + 0x14);
    return 1;
  }
  if ((*(uint *)(param_2 + 0x60) & 0x80000000) != 0) {
    *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(param_1 + 0x14);
  }
  return 1;
}

