/* sub_54F9A0 @ 0054f9a0   72 bytes */

void sub_54F9A0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_563C89();
  iVar3 = sub_563C89();
  iVar4 = sub_563C89();
  iVar5 = sub_563C89();
  sub_54BBD0(param_1,((iVar2 * 0x10000 + iVar3) - (iVar4 * 0x10000 + iVar5)) % iVar1);
  return;
}

