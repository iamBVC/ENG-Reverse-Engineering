/* sub_54E270 @ 0054e270   86 bytes */

void sub_54E270(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = sub_54BC00(param_1);
  uVar3 = sub_54BC00(param_1);
  if (DAT_005846e4 == 3) {
    cVar1 = sub_546170(param_1,uVar3,0);
    sub_546360(param_1,(int)cVar1,iVar2 >> 0xc);
    sub_54BBD0(param_1,(int)cVar1);
    return;
  }
  sub_54BBD0(param_1,0xffffffff);
  return;
}

