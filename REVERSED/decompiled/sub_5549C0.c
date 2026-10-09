/* sub_5549C0 @ 005549c0   77 bytes */

void sub_5549C0(undefined4 param_1)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = sub_54BC00(param_1);
  iVar3 = sub_54BC00(param_1);
  iVar4 = sub_54BC00(param_1);
  lVar1 = (longlong)(iVar4 - iVar3) * (longlong)iVar2;
  sub_54BBD0(param_1,((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14) + iVar3);
  return;
}

