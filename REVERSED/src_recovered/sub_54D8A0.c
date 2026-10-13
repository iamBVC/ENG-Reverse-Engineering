/* Selected Ghidra export at 0054d8a0. */

void sub_54D8A0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (iVar1 >> 0xc == 1) {
    sub_415390(2);
    DAT_00584638 = 0;
    return;
  }
  if (iVar1 >> 0xc != 3) {
    sub_415390(4);
    DAT_00584638 = 0;
    return;
  }
  sub_415390(10);
  DAT_00584638 = 0;
  return;
}

