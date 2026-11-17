/* sub_555040 @ 00555040 76 bytes */
/* Selected Ghidra export at 00555040. */

void sub_555040(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 >> 0xc == 0) {
    DAT_005ff034 = sub_4284D0;
    DAT_005ff038 = sub_4321E0;
  }
  else if (iVar1 >> 0xc == 1) {
    DAT_005ff034 = sub_426500;
    DAT_005ff038 = sub_434AD0;
    DAT_006d94d0 = 0;
    return;
  }
  return;
}

