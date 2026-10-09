/* sub_54E4D0 @ 0054e4d0   485 bytes */

void sub_54E4D0(int param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  sub_54BC00(param_1);
  if (*(int *)(param_1 + 0x14) != 0) {
    sub_54BC30(param_1);
    iVar4 = __ftol();
    iVar5 = __ftol();
    iVar6 = __ftol();
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_1 + 0x70);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_1 + 0x7c);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_1 + 0x88);
    *(uint *)(param_1 + 0xd8) =
         ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
         ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
         ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_1 + 0x74);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_1 + 0x80);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_1 + 0x8c);
    *(uint *)(param_1 + 0xdc) =
         ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
         ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
         ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_1 + 0x78);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_1 + 0x84);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_1 + 0x90);
    *(uint *)(param_1 + 0xe0) =
         ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
         ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
         ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
    *(int *)(param_1 + 0xdc) = *(int *)(param_1 + 0xdc) + *(int *)(param_1 + 0x98);
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + *(int *)(param_1 + 0x94);
    *(int *)(param_1 + 0xe0) = *(int *)(param_1 + 0xe0) + *(int *)(param_1 + 0x9c);
  }
  return;
}

