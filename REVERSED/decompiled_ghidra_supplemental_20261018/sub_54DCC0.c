/* Selected Ghidra export at 0054dcc0. */

void sub_54DCC0(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = sub_54BC00(param_1);
  uVar2 = sub_54BC00(param_1);
  iVar3 = (uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f);
  if (iVar1 <= iVar3) {
    iVar3 = iVar1;
  }
  if ((int)uVar2 < 0) {
    iVar3 = -iVar3;
  }
  sub_54BBD0(param_1,iVar3);
  return;
}

