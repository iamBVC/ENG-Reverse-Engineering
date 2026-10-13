/* Selected Ghidra export at 00553630. */

void sub_553630(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(*param_1 + -4) = 0x45;
  piVar1 = (int *)*param_1;
  iVar2 = *piVar1;
  if (iVar2 < 0) {
    if (-1 - iVar2 < DAT_006da31c) {
      *piVar1 = *(int *)(DAT_006da324 + (-1 - iVar2) * 4);
    }
    else {
      *piVar1 = 0;
    }
  }
  else {
    *piVar1 = iVar2 + DAT_006d9dbc;
  }
  uVar3 = *(undefined4 *)*param_1;
  *param_1 = (int)((undefined4 *)*param_1 + 1);
  sub_54BBD0(param_1,uVar3);
  return;
}

