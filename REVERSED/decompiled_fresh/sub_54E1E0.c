/* sub_54E1E0 @ 0054e1e0   67 bytes */

void sub_54E1E0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = sub_54BC00(param_1);
  if ((DAT_005846e4 != 3) && (DAT_005846e4 != 4)) {
    sub_54BBD0(param_1,0xffffffff);
    return;
  }
  cVar1 = sub_546170(param_1,uVar2,0);
  sub_54BBD0(param_1,(int)cVar1);
  return;
}

