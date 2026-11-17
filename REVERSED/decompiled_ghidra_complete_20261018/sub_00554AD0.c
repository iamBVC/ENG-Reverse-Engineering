/* sub_554AD0 @ 00554ad0   109 bytes */

void sub_554AD0(undefined4 param_1)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = sub_54BC00(param_1);
  iVar4 = sub_54BC00(param_1);
  iVar5 = sub_54BC00(param_1);
  iVar6 = sub_54BC00(param_1);
  lVar1 = (longlong)(iVar4 - iVar6) * (longlong)(iVar4 - iVar6);
  lVar2 = (longlong)(iVar3 - iVar5) * (longlong)(iVar3 - iVar5);
  sub_54BBD0(param_1,((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
                     ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14));
  return;
}

