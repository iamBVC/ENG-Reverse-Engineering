/* sub_54DC40 @ 0054dc40   53 bytes */

void sub_54DC40(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  if (iVar2 < iVar1) {
    sub_54BBD0(param_1,iVar1);
    return;
  }
  sub_54BBD0(param_1,iVar2);
  return;
}

