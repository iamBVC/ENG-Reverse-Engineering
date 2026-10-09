/* sub_54E320 @ 0054e320   113 bytes */

void sub_54E320(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar2 = sub_54BC00(param_1);
  iVar3 = sub_54BC00(param_1);
  uVar4 = sub_54BC00(param_1);
  if ((DAT_005846e4 != 3) && (DAT_005846e4 != 4)) {
    sub_54BBD0(param_1,0xffffffff);
    return;
  }
  cVar1 = sub_546170(param_1,uVar4,0);
  iVar5 = (int)cVar1;
  sub_546360(param_1,iVar5,iVar3 >> 0xc);
  sub_546460(param_1,iVar5,iVar2 >> 0xc);
  sub_54BBD0(param_1,iVar5);
  return;
}

