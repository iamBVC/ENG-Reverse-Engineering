/* Selected Ghidra export at 0054f550. */

void sub_54F550(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x120) + 4);
  *(int *)(param_1 + 0x120) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x11c);
  }
  return;
}

