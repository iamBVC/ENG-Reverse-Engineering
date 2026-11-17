/* sub_550600 @ 00550600   139 bytes */

void sub_550600(int param_1)

{
  longlong lVar1;
  int iVar2;
  
  iVar2 = sub_54BC00(param_1);
  lVar1 = (longlong)-iVar2 * (longlong)(int)(&DAT_00574318)[*(int *)(param_1 + 0x24) >> 0xc & 0xfff]
  ;
  *(uint *)(param_1 + 0x30) =
       *(int *)(param_1 + 0x30) + ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
  lVar1 = (longlong)-iVar2 *
          (longlong)(int)(&DAT_00574318)[(*(int *)(param_1 + 0x24) >> 0xc) + 0x400U & 0xfff];
  *(uint *)(param_1 + 0x38) =
       *(int *)(param_1 + 0x38) + ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
  return;
}

