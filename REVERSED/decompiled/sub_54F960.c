/* sub_54F960 @ 0054f960   61 bytes */

void sub_54F960(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = sub_54BC00(param_1);
  iVar2 = sub_563C89();
  iVar3 = sub_563C89();
  uVar4 = 0;
  if (uVar1 != 0) {
    uVar4 = (uint)(iVar2 * 0x10000 + iVar3) % uVar1;
  }
  sub_54BBD0(param_1,uVar4);
  return;
}

