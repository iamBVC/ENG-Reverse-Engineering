/* Selected Ghidra export at 0054d910. */

void sub_54D910(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sub_54BC00(param_1);
  iVar1 = iVar1 >> 0xc;
  if (iVar1 == 1) {
    uVar2 = 1;
  }
  else if (iVar1 == 2) {
    uVar2 = 5;
  }
  else if (iVar1 == 3) {
    uVar2 = 0xb;
  }
  else {
    uVar2 = 3;
  }
  sub_415390(uVar2);
  if ((DAT_00584638 != 7) && (DAT_00584638 != 10)) {
    DAT_00584638 = 6;
  }
  return;
}

