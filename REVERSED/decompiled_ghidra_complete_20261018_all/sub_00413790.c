/* sub_413790 @ 00413790 29 bytes */
/* Selected Ghidra export at 00413790. */

int sub_413790(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar2 = *(int *)(param_2 + 0xc);
  if (iVar1 == iVar2) {
    iVar1 = *(int *)(param_1 + 0x10);
    iVar2 = *(int *)(param_2 + 0x10);
  }
  return iVar1 - iVar2;
}

