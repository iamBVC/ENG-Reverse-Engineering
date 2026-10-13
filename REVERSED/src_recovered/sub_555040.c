/* Selected Ghidra export at 00555040. */

void sub_555040(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 >> 0xc == 0) {
    DAT_005ff034 = (code *)&LAB_004284d0;
    DAT_005ff038 = &LAB_004321e0;
  }
  else if (iVar1 >> 0xc == 1) {
    DAT_005ff034 = sub_426500;
    DAT_005ff038 = &DAT_00434ad0;
    DAT_006d94d0 = 0;
    return;
  }
  return;
}

