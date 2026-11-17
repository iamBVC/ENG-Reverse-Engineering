/* sub_54BC30 @ 0054bc30   911 bytes */

void sub_54BC30(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  uint uVar8;
  uint uVar9;
  
  uVar8 = *(int *)(param_1 + 0x20) >> 0xc;
  iVar1 = (&DAT_00574318)[uVar8 & 0xfff];
  uVar9 = *(int *)(param_1 + 0x24) >> 0xc;
  iVar2 = (&DAT_00574318)[uVar8 + 0x400 & 0xfff];
  iVar3 = (&DAT_00574318)[uVar9 & 0xfff];
  uVar8 = *(int *)(param_1 + 0x28) >> 0xc;
  iVar4 = (&DAT_00574318)[uVar9 + 0x400 & 0xfff];
  iVar5 = (&DAT_00574318)[uVar8 & 0xfff];
  iVar6 = (&DAT_00574318)[uVar8 + 0x400 & 0xfff];
  lVar7 = (longlong)
          (int)((uint)((longlong)iVar1 * (longlong)iVar3) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar3) >> 0x20) << 0x14) *
          (longlong)iVar5;
  *(uint *)(param_1 + 0x70) =
       ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) +
       ((uint)((longlong)iVar4 * (longlong)iVar6) >> 0xc |
       (int)((ulonglong)((longlong)iVar4 * (longlong)iVar6) >> 0x20) << 0x14);
  *(uint *)(param_1 + 0x74) =
       (uint)((longlong)iVar2 * (longlong)iVar5) >> 0xc |
       (int)((ulonglong)((longlong)iVar2 * (longlong)iVar5) >> 0x20) << 0x14;
  lVar7 = (longlong)
          (int)((uint)((longlong)iVar1 * (longlong)iVar4) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar4) >> 0x20) << 0x14) *
          (longlong)iVar5;
  *(uint *)(param_1 + 0x78) =
       ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) -
       ((uint)((longlong)iVar3 * (longlong)iVar6) >> 0xc |
       (int)((ulonglong)((longlong)iVar3 * (longlong)iVar6) >> 0x20) << 0x14);
  lVar7 = (longlong)
          (int)((uint)((longlong)iVar1 * (longlong)iVar3) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar3) >> 0x20) << 0x14) *
          (longlong)iVar6;
  *(uint *)(param_1 + 0x7c) =
       ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14) -
       ((uint)((longlong)iVar4 * (longlong)iVar5) >> 0xc |
       (int)((ulonglong)((longlong)iVar4 * (longlong)iVar5) >> 0x20) << 0x14);
  *(uint *)(param_1 + 0x80) =
       (uint)((longlong)iVar2 * (longlong)iVar6) >> 0xc |
       (int)((ulonglong)((longlong)iVar2 * (longlong)iVar6) >> 0x20) << 0x14;
  lVar7 = (longlong)
          (int)((uint)((longlong)iVar1 * (longlong)iVar4) >> 0xc |
               (int)((ulonglong)((longlong)iVar1 * (longlong)iVar4) >> 0x20) << 0x14) *
          (longlong)iVar6;
  *(uint *)(param_1 + 0x84) =
       ((uint)((longlong)iVar3 * (longlong)iVar5) >> 0xc |
       (int)((ulonglong)((longlong)iVar3 * (longlong)iVar5) >> 0x20) << 0x14) +
       ((uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14);
  *(uint *)(param_1 + 0x88) =
       (uint)((longlong)iVar2 * (longlong)iVar3) >> 0xc |
       (int)((ulonglong)((longlong)iVar2 * (longlong)iVar3) >> 0x20) << 0x14;
  *(int *)(param_1 + 0x8c) = -iVar1;
  *(uint *)(param_1 + 0x90) =
       (uint)((longlong)iVar2 * (longlong)iVar4) >> 0xc |
       (int)((ulonglong)((longlong)iVar2 * (longlong)iVar4) >> 0x20) << 0x14;
  *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x34);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x38);
  lVar7 = (longlong)*(int *)(param_1 + 0x60) * (longlong)*(int *)(param_1 + 0x70);
  *(uint *)(param_1 + 0x70) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 0x60) * (longlong)*(int *)(param_1 + 0x74);
  *(uint *)(param_1 + 0x74) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 0x60) * (longlong)*(int *)(param_1 + 0x78);
  *(uint *)(param_1 + 0x78) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 100) * (longlong)*(int *)(param_1 + 0x7c);
  *(uint *)(param_1 + 0x7c) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 100) * (longlong)*(int *)(param_1 + 0x80);
  *(uint *)(param_1 + 0x80) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 100) * (longlong)*(int *)(param_1 + 0x84);
  *(uint *)(param_1 + 0x84) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 0x68) * (longlong)*(int *)(param_1 + 0x88);
  *(uint *)(param_1 + 0x88) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 0x68) * (longlong)*(int *)(param_1 + 0x8c);
  *(uint *)(param_1 + 0x8c) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  lVar7 = (longlong)*(int *)(param_1 + 0x68) * (longlong)*(int *)(param_1 + 0x90);
  *(uint *)(param_1 + 0x90) = (uint)lVar7 >> 0xc | (int)((ulonglong)lVar7 >> 0x20) << 0x14;
  return;
}

