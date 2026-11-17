/* Selected Ghidra export at 00554a10. */

void sub_554A10(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  iVar3 = sub_54BC00(param_1);
  if (iVar2 <= iVar3) {
    sub_54BBD0(param_1,iVar3);
    return;
  }
  if (iVar1 <= iVar2) {
    sub_54BBD0(param_1,iVar1);
    return;
  }
  sub_54BBD0(param_1,iVar2);
  return;
}

