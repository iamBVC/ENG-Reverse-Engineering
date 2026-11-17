/* sub_54DC80 @ 0054dc80   53 bytes */

void sub_54DC80(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  if (iVar1 < iVar2) {
    sub_54BBD0(param_1,iVar1);
    return;
  }
  sub_54BBD0(param_1,iVar2);
  return;
}

