/* sub_559A46 @ 00559a46   1702 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall sub_559A46(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int in_EAX;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  
  fVar4 = *(float *)(param_2 + 0x14) - *(float *)(in_EAX + 0x14);
  fVar7 = *(float *)(param_1 + 0x14) - *(float *)(in_EAX + 0x14);
  fVar8 = *(float *)(param_2 + 0x18) - *(float *)(in_EAX + 0x18);
  fVar6 = *(float *)(param_1 + 0x18) - *(float *)(in_EAX + 0x18);
  fVar5 = _DAT_0057c6a0 / (fVar7 * fVar8 - fVar4 * fVar6);
  uVar14 = ((uint)(*(uint *)(param_1 + 0x18) < *(uint *)(in_EAX + 0x18)) << 1 |
           (uint)(*(uint *)(param_2 + 0x18) < *(uint *)(in_EAX + 0x18))) << 1 |
           (uint)(*(uint *)(param_2 + 0x18) < *(uint *)(param_1 + 0x18));
  iVar1 = *(int *)((int)&DAT_0057c528 + *(int *)(&DAT_0057c6e4 + uVar14 * 4));
  iVar13 = *(int *)((int)&DAT_0057c528 + *(int *)(&DAT_0057c6f0 + uVar14 * 4));
  iVar2 = *(int *)((int)&DAT_0057c528 + *(int *)(&DAT_0057c6d8 + uVar14 * 4));
  DAT_0057c55c = *(uint *)(&DAT_0057c710 + uVar14 * 4);
  uVar15 = (*(uint *)(iVar1 + 0x18) & 0x7fffff | 0x800000) >>
           ((byte)(0x4b7fffff - *(uint *)(iVar1 + 0x18) >> 0x17) & 0x1f);
  uVar16 = (*(uint *)(iVar2 + 0x18) & 0x7fffff | 0x800000) >>
           ((byte)(0x4b7fffff - *(uint *)(iVar2 + 0x18) >> 0x17) & 0x1f);
  uVar17 = (*(uint *)(iVar13 + 0x18) & 0x7fffff | 0x800000) >>
           ((byte)(0x4b7fffff - *(uint *)(iVar13 + 0x18) >> 0x17) & 0x1f);
  if (uVar15 == uVar16) {
    if (uVar15 == uVar17) {
      DAT_0057c59c = 0xffffffff;
      DAT_0057c5a0 = 0xffffffff;
      return;
    }
    fVar10 = *(float *)(iVar13 + 0x18) - *(float *)(iVar2 + 0x18);
    fVar9 = _DAT_0057c6a0;
  }
  else if (uVar16 == uVar17) {
    fVar9 = *(float *)(iVar2 + 0x18) - *(float *)(iVar1 + 0x18);
    fVar10 = _DAT_0057c6a0;
  }
  else {
    fVar9 = *(float *)(iVar2 + 0x18) - *(float *)(iVar1 + 0x18);
    fVar10 = *(float *)(iVar13 + 0x18) - *(float *)(iVar2 + 0x18);
  }
  _DAT_0057c540 = fVar6 * fVar5;
  _DAT_0057c544 = fVar8 * fVar5;
  _DAT_0057c538 = fVar7 * fVar5;
  fVar7 = *(float *)(iVar13 + 0x18) - *(float *)(iVar1 + 0x18);
  _DAT_0057c53c = fVar4 * fVar5;
  DAT_0057c534 = fVar5;
  fVar6 = fVar7 * fVar10;
  fVar4 = _DAT_0057c6a0 / (fVar6 * fVar9);
  DAT_0057c558 = uVar15 + 1;
  DAT_0057c59c = uVar16 - DAT_0057c558;
  DAT_0057c5a0 = uVar17 - (uVar16 + 1);
  iVar3 = (int)(*(uint *)(&DAT_0057c710 + uVar14 * 4) ^ (uint)fVar5) >> 0x1f;
  DAT_0057c55c = -iVar3;
  fVar6 = (*(float *)(iVar2 + 0x14) - *(float *)(iVar1 + 0x14)) * fVar6 * fVar4;
  fVar4 = fVar4 * fVar9;
  fVar5 = (*(float *)(iVar13 + 0x14) - *(float *)(iVar1 + 0x14)) * fVar10 * fVar4;
  _DAT_0057c554 = (float)DAT_0057c558 - *(float *)(iVar1 + 0x18);
  fVar4 = fVar4 * (*(float *)(iVar13 + 0x14) - *(float *)(iVar2 + 0x14)) * fVar7;
  _DAT_0057c4a8 = (double)(fVar6 + _DAT_0057c6b4);
  _DAT_0057c4a0 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c4b0 = (double)(fVar4 + _DAT_0057c6b4);
  iVar13 = DAT_0057c4a0;
  uVar11 = DAT_0057c4a8;
  uVar12 = DAT_0057c4b0;
  _DAT_0057c4a0 =
       (double)(_DAT_0057c554 * fVar5 + *(float *)(iVar1 + 0x14) +
               (float)*(double *)(&DAT_0057c690 + iVar3 * -8));
  _DAT_0057c4a8 =
       (double)(_DAT_0057c554 * fVar6 + *(float *)(iVar1 + 0x14) +
               (float)*(double *)(&DAT_0057c688 + iVar3 * -8));
  _DAT_0057c4a0 = (double)CONCAT44(iVar13,DAT_0057c4a0);
  _DAT_0057c4a8 = (double)CONCAT44(uVar11,DAT_0057c4a8);
  iVar13 = iVar13 >> 0x10;
  _DAT_0057c550 = (float)(DAT_0057c4a0 >> 0x10) - *(float *)(iVar1 + 0x14);
  _DAT_0057c4b0 =
       (double)(((float)(int)(uVar16 + 1) - *(float *)(iVar2 + 0x18)) * fVar4 +
                *(float *)(iVar2 + 0x14) + (float)*(double *)(&DAT_0057c688 + iVar3 * -8));
  _DAT_0057c54c = (float)iVar13;
  _DAT_0057c548 = (float)(iVar13 + 1);
  _DAT_0057c4b0 = (double)CONCAT44(uVar12,DAT_0057c4b0);
  fVar4 = *(float *)(DAT_0057c530 + 0x1c) - *(float *)(DAT_0057c528 + 0x1c);
  fVar6 = *(float *)(DAT_0057c52c + 0x1c) - *(float *)(DAT_0057c528 + 0x1c);
  fVar5 = fVar6 * _DAT_0057c544 - fVar4 * _DAT_0057c540;
  fVar4 = fVar4 * _DAT_0057c538 - fVar6 * _DAT_0057c53c;
  _DAT_0057c4b8 = (double)(fVar5 * _DAT_0057c548 + fVar4 + _DAT_0057c6b4);
  _DAT_0057c4c0 = (double)(fVar5 * _DAT_0057c54c + fVar4 + _DAT_0057c6b4);
  uVar11 = DAT_0057c4b8;
  uVar12 = DAT_0057c4c0;
  _DAT_0057c4b8 =
       (double)(fVar4 * _DAT_0057c554 + *(float *)(iVar1 + 0x1c) + _DAT_0057c550 * fVar5 +
               _DAT_0057c6b4);
  _DAT_0057c4c0 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c4c0 = (double)CONCAT44(uVar12,DAT_0057c4c0);
  _DAT_0057c4b8 = (double)(CONCAT44(uVar11,DAT_0057c4b8) ^ 0x80000000);
  fVar4 = *(float *)(DAT_0057c530 + 0x20) - *(float *)(DAT_0057c528 + 0x20);
  fVar6 = *(float *)(DAT_0057c52c + 0x20) - *(float *)(DAT_0057c528 + 0x20);
  fVar5 = fVar6 * _DAT_0057c544 - fVar4 * _DAT_0057c540;
  fVar4 = fVar4 * _DAT_0057c538 - fVar6 * _DAT_0057c53c;
  _DAT_0057c4d8 = (double)(fVar5 * _DAT_0057c548 + fVar4 + _DAT_0057c6b4);
  _DAT_0057c4e0 = (double)(fVar5 * _DAT_0057c54c + fVar4 + _DAT_0057c6b4);
  uVar11 = DAT_0057c4d8;
  uVar12 = DAT_0057c4e0;
  _DAT_0057c4d8 =
       (double)(fVar4 * _DAT_0057c554 + *(float *)(iVar1 + 0x20) + _DAT_0057c550 * fVar5 +
               _DAT_0057c6b4);
  _DAT_0057c4e0 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c4d8 = (double)CONCAT44(uVar11,DAT_0057c4d8);
  _DAT_0057c4e0 = (double)CONCAT44(uVar12,DAT_0057c4e0);
  fVar4 = *(float *)(DAT_0057c530 + 0x24) - *(float *)(DAT_0057c528 + 0x24);
  fVar6 = *(float *)(DAT_0057c52c + 0x24) - *(float *)(DAT_0057c528 + 0x24);
  fVar5 = fVar6 * _DAT_0057c544 - fVar4 * _DAT_0057c540;
  fVar4 = fVar4 * _DAT_0057c538 - fVar6 * _DAT_0057c53c;
  _DAT_0057c4e8 = (double)(fVar5 * _DAT_0057c548 + fVar4 + _DAT_0057c6b4);
  _DAT_0057c4f0 = (double)(fVar5 * _DAT_0057c54c + fVar4 + _DAT_0057c6b4);
  uVar11 = DAT_0057c4e8;
  uVar12 = DAT_0057c4f0;
  _DAT_0057c4e8 =
       (double)(fVar4 * _DAT_0057c554 + *(float *)(iVar1 + 0x24) + _DAT_0057c550 * fVar5 +
               _DAT_0057c6b4);
  _DAT_0057c4f0 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c4e8 = (double)CONCAT44(uVar11,DAT_0057c4e8);
  _DAT_0057c4f0 = (double)CONCAT44(uVar12,DAT_0057c4f0);
  fVar4 = *(float *)(DAT_0057c530 + 0x28) - *(float *)(DAT_0057c528 + 0x28);
  fVar6 = *(float *)(DAT_0057c52c + 0x28) - *(float *)(DAT_0057c528 + 0x28);
  fVar5 = fVar6 * _DAT_0057c544 - fVar4 * _DAT_0057c540;
  fVar4 = fVar4 * _DAT_0057c538 - fVar6 * _DAT_0057c53c;
  _DAT_0057c4c8 = (double)(fVar5 * _DAT_0057c548 + fVar4 + _DAT_0057c6b4);
  _DAT_0057c4d0 = (double)(fVar5 * _DAT_0057c54c + fVar4 + _DAT_0057c6b4);
  uVar11 = DAT_0057c4c8;
  uVar12 = DAT_0057c4d0;
  _DAT_0057c4c8 =
       (double)(fVar4 * _DAT_0057c554 + *(float *)(iVar1 + 0x28) + _DAT_0057c550 * fVar5 +
               _DAT_0057c6b4);
  _DAT_0057c4d0 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c4c8 = (double)CONCAT44(uVar11,DAT_0057c4c8);
  _DAT_0057c4d0 = (double)CONCAT44(uVar12,DAT_0057c4d0);
  fVar4 = *(float *)(DAT_0057c530 + 0x2c) - *(float *)(DAT_0057c528 + 0x2c);
  fVar6 = *(float *)(DAT_0057c52c + 0x2c) - *(float *)(DAT_0057c528 + 0x2c);
  fVar5 = fVar6 * _DAT_0057c544 - fVar4 * _DAT_0057c540;
  fVar4 = fVar4 * _DAT_0057c538 - fVar6 * _DAT_0057c53c;
  _DAT_0057c508 = (double)(fVar5 * _DAT_0057c548 + fVar4 + _DAT_0057c6b4);
  _DAT_0057c510 = (double)(fVar5 * _DAT_0057c54c + fVar4 + _DAT_0057c6b4);
  uVar11 = DAT_0057c508;
  uVar12 = DAT_0057c510;
  _DAT_0057c508 =
       (double)(fVar4 * _DAT_0057c554 + *(float *)(iVar1 + 0x2c) + _DAT_0057c550 * fVar5 +
               _DAT_0057c6b4);
  _DAT_0057c510 = (double)(fVar5 + _DAT_0057c6b4);
  _DAT_0057c508 = (double)CONCAT44(uVar11,DAT_0057c508);
  _DAT_0057c510 = (double)CONCAT44(uVar12,DAT_0057c510);
  return;
}

