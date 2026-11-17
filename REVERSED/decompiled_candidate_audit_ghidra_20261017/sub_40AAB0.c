/* Selected Ghidra export at 0040aab0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_40AAB0(byte *param_1,byte *param_2,byte *param_3,undefined1 *param_4,int param_5)

{
  byte bVar1;
  undefined1 uVar2;
  
  if (param_5 == 0) goto switchD_0040ab13_caseD_1;
  switch(param_5) {
  case 2:
  case 4:
    if ((float)*param_1 * _DAT_0056e15c * _DAT_0056e138 +
        (float)*param_2 * _DAT_0056e15c * _DAT_0056e134 +
        (float)*param_3 * _DAT_0056e15c * _DAT_0056e130 == _DAT_0056e00c) break;
  case 1:
switchD_0040ab13_caseD_1:
    break;
  case 3:
  }
  bVar1 = __ftol();
  *param_1 = bVar1;
  bVar1 = __ftol();
  *param_2 = bVar1;
  bVar1 = __ftol();
  *param_3 = bVar1;
  uVar2 = __ftol();
  *param_4 = uVar2;
  return;
}

