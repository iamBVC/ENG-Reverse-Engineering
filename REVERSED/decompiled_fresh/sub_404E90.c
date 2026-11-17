/* sub_404E90 @ 00404e90   827 bytes */

void sub_404E90(int *param_1,int param_2,int param_3)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if ((param_3 != 0) && (*(int *)(param_2 + 0x14) != 0)) {
    iVar4 = __ftol();
    iVar5 = __ftol();
    iVar6 = __ftol();
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x70);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x7c);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x88);
    *param_1 = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
               ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
               ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x74);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x80);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x8c);
    param_1[1] = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
                 ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
                 ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
    lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x78);
    lVar2 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x84);
    lVar3 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x90);
    iVar4 = ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14) +
            ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
            ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14);
    param_1[2] = iVar4;
    *param_1 = *param_1 + *(int *)(param_2 + 0x30);
    param_1[1] = param_1[1] + *(int *)(param_2 + 0x34);
    param_1[2] = *(int *)(param_2 + 0x38) + iVar4;
    param_1[3] = (uint)*(ushort *)(*(int *)(param_2 + 200) + -2 + param_3 * 4);
    return;
  }
  iVar4 = (int)*(short *)(param_2 + 0xcc);
  iVar6 = (int)*(short *)(param_2 + 0xce);
  iVar5 = (int)*(short *)(param_2 + 0xd0);
  lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x70);
  lVar2 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x7c);
  lVar3 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x88);
  *param_1 = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
             ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
             ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
  lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x74);
  lVar2 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x80);
  lVar3 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x8c);
  param_1[1] = ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
               ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14) +
               ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14);
  lVar1 = (longlong)iVar4 * (longlong)*(int *)(param_2 + 0x78);
  lVar2 = (longlong)iVar6 * (longlong)*(int *)(param_2 + 0x84);
  lVar3 = (longlong)iVar5 * (longlong)*(int *)(param_2 + 0x90);
  iVar4 = ((uint)lVar1 >> 0xc | (int)((ulonglong)lVar1 >> 0x20) << 0x14) +
          ((uint)lVar3 >> 0xc | (int)((ulonglong)lVar3 >> 0x20) << 0x14) +
          ((uint)lVar2 >> 0xc | (int)((ulonglong)lVar2 >> 0x20) << 0x14);
  param_1[2] = iVar4;
  *param_1 = *param_1 + *(int *)(param_2 + 0x30);
  param_1[1] = param_1[1] + *(int *)(param_2 + 0x34);
  param_1[2] = *(int *)(param_2 + 0x38) + iVar4;
  param_1[3] = (int)*(short *)(param_2 + 0xd2);
  return;
}

