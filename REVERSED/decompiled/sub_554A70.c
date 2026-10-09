/* sub_554A70 @ 00554a70   92 bytes */

void sub_554A70(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  iVar3 = sub_54BC00(param_1);
  if (iVar3 < iVar2) {
    iVar3 = iVar3 + iVar1;
    if (iVar2 <= iVar3) {
      sub_54BBD0(param_1,iVar2);
      return;
    }
  }
  else if ((iVar2 < iVar3) && (iVar3 = iVar3 - iVar1, iVar3 <= iVar2)) {
    sub_54BBD0(param_1,iVar2);
    return;
  }
  sub_54BBD0(param_1,iVar3);
  return;
}

