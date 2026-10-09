/* sub_5501D0 @ 005501d0   948 bytes */

void sub_5501D0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  
  uVar13 = *(int *)(param_1 + 0x24) >> 0xc;
  uVar10 = *(int *)(param_1 + 0x20) >> 0xc;
  iVar12 = (&DAT_00574318)[uVar13 & 0xfff];
  uVar14 = *(int *)(param_1 + 0x28) >> 0xc;
  iVar1 = (&DAT_00574318)[uVar13 + 0x400 & 0xfff];
  iVar2 = (&DAT_00574318)[uVar10 + 0x400 & 0xfff];
  iVar11 = (&DAT_00574318)[uVar10 & 0xfff];
  iVar3 = (&DAT_00574318)[uVar14 & 0xfff];
  iVar4 = (&DAT_00574318)[uVar14 + 0x400 & 0xfff];
  lVar5 = (longlong)
          (int)((uint)((longlong)iVar11 * (longlong)iVar12) >> 0xc |
               (int)((ulonglong)((longlong)iVar11 * (longlong)iVar12) >> 0x20) << 0x14) *
          (longlong)iVar3;
  lVar6 = (longlong)
          (int)((uint)((longlong)iVar11 * (longlong)iVar1) >> 0xc |
               (int)((ulonglong)((longlong)iVar11 * (longlong)iVar1) >> 0x20) << 0x14) *
          (longlong)iVar3;
  lVar7 = (longlong)
          (int)((uint)((longlong)iVar11 * (longlong)iVar12) >> 0xc |
               (int)((ulonglong)((longlong)iVar11 * (longlong)iVar12) >> 0x20) << 0x14) *
          (longlong)iVar4;
  lVar8 = (longlong)
          (int)((uint)((longlong)iVar11 * (longlong)iVar1) >> 0xc |
               (int)((ulonglong)((longlong)iVar11 * (longlong)iVar1) >> 0x20) << 0x14) *
          (longlong)iVar4;
  iVar15 = *param_2;
  param_2[1] = param_2[1] << 1;
  *param_2 = iVar15 << 1;
  param_2[2] = param_2[2] << 1;
  lVar5 = (longlong)(iVar15 << 1) *
          (longlong)
          (int)(((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14) +
               ((uint)((longlong)iVar1 * (longlong)iVar4) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar4) >> 0x20) << 0x14));
  lVar7 = (longlong)param_2[1] *
          (longlong)
          (int)(((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) -
               ((uint)((longlong)iVar1 * (longlong)iVar3) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar3) >> 0x20) << 0x14));
  lVar9 = (longlong)param_2[2] *
          (longlong)
          (int)((uint)((longlong)iVar2 * (longlong)iVar12) >> 0xc |
               (int)((ulonglong)((longlong)iVar2 * (longlong)iVar12) >> 0x20) << 0x14);
  iVar15 = ((uint)lVar9 >> 0xc | (int)((ulonglong)lVar9 >> 0x20) << 0x14) +
           ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) +
           ((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14);
  lVar5 = (longlong)*param_2 *
          (longlong)
          (int)((uint)((longlong)iVar2 * (longlong)iVar3) >> 0xc |
               (int)((ulonglong)((longlong)iVar2 * (longlong)iVar3) >> 0x20) << 0x14);
  lVar7 = (longlong)param_2[1] *
          (longlong)
          (int)((uint)((longlong)iVar2 * (longlong)iVar4) >> 0xc |
               (int)((ulonglong)((longlong)iVar2 * (longlong)iVar4) >> 0x20) << 0x14);
  iVar11 = ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) +
           ((uint)((longlong)param_2[2] * (longlong)-iVar11) >> 0xc |
           (int)((ulonglong)((longlong)param_2[2] * (longlong)-iVar11) >> 0x20) << 0x14) +
           ((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14);
  lVar5 = (longlong)*param_2 *
          (longlong)
          (int)(((uint)lVar6 >> 0xc | (int)((ulonglong)lVar6 >> 0x20) << 0x14) -
               ((uint)((longlong)iVar12 * (longlong)iVar4) >> 0xc |
               (int)((ulonglong)((longlong)iVar12 * (longlong)iVar4) >> 0x20) << 0x14));
  lVar6 = (longlong)param_2[1] *
          (longlong)
          (int)(((uint)((longlong)iVar12 * (longlong)iVar3) >> 0xc |
                (int)((ulonglong)((longlong)iVar12 * (longlong)iVar3) >> 0x20) << 0x14) +
               ((uint)lVar8 >> 0xc | (int)((ulonglong)lVar8 >> 0x20) << 0x14));
  lVar7 = (longlong)param_2[2] *
          (longlong)
          (int)((uint)((longlong)iVar2 * (longlong)iVar1) >> 0xc |
               (int)((ulonglong)((longlong)iVar2 * (longlong)iVar1) >> 0x20) << 0x14);
  iVar12 = ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) +
           ((uint)lVar6 >> 0xc | (int)((ulonglong)lVar6 >> 0x20) << 0x14) +
           ((uint)lVar5 >> 0xc | (int)((ulonglong)lVar5 >> 0x20) << 0x14);
  *param_2 = *param_2 >> 1;
  param_2[1] = param_2[1] >> 1;
  param_2[2] = param_2[2] >> 1;
  if (iVar15 < 0) {
    iVar15 = -(-iVar15 >> 1);
  }
  else {
    iVar15 = iVar15 >> 1;
  }
  if (iVar11 < 0) {
    iVar11 = -(-iVar11 >> 1);
  }
  else {
    iVar11 = iVar11 >> 1;
  }
  if (iVar12 < 0) {
    iVar12 = -(-iVar12 >> 1);
  }
  else {
    iVar12 = iVar12 >> 1;
  }
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + iVar15;
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + iVar11;
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + iVar12;
  return;
}

