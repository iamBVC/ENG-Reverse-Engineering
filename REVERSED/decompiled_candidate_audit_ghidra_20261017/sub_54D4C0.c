/* Selected Ghidra export at 0054d4c0. */

void sub_54D4C0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  iVar1 = iVar1 >> 0xc;
  if (DAT_00586430 != iVar1) {
    sub_546B70(iVar1,0);
    DAT_00586430 = iVar1;
  }
  return;
}

