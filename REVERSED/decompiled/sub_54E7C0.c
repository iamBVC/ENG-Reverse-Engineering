/* sub_54E7C0 @ 0054e7c0   65 bytes */

void sub_54E7C0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  if (0 < iVar1) {
    sub_54BBD0(param_1,0x1000);
    return;
  }
  if (iVar1 < 0) {
    sub_54BBD0(param_1,0xfffff000);
    return;
  }
  sub_54BBD0(param_1,0);
  return;
}

