/* sub_42C4A0 @ 0042c4a0   478 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_42C4A0(float param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float local_10;
  
  iVar8 = (int)param_1;
  param_1 = -1.0;
  iVar9 = iVar8 * 0x1c;
  bVar1 = *(byte *)(iVar9 + 0xe + DAT_00586598);
  if ((bVar1 & 0x80) == 0) {
    param_1 = 1.0;
  }
  bVar2 = *(byte *)(iVar9 + 0xd + DAT_00586598);
  local_10 = -1.0;
  if ((bVar2 & 0x80) == 0) {
    local_10 = 1.0;
  }
  bVar3 = *(byte *)(iVar9 + 0xc + DAT_00586598);
  fVar5 = _DAT_0056e008;
  if ((bVar3 & 0x80) != 0) {
    fVar5 = _DAT_0056e418;
  }
  fVar10 = (float10)*(uint *)(iVar9 + 0x18 + DAT_00586598) * (float10)_DAT_0056e020;
  iVar4 = *(int *)(*(int *)(DAT_00584648 + 0x60) + (DAT_005865b8 + iVar8) * 4);
  *(float *)(iVar4 + 0x18) =
       (float)((float10)(bVar1 & 0x7f) * fVar10 * (float10)param_1 * (float10)_DAT_0056e414);
  *(float *)(iVar4 + 0x14) =
       (float)((float10)(bVar2 & 0x7f) * fVar10 * (float10)local_10 * (float10)_DAT_0056e414);
  *(float *)(iVar4 + 0x10) =
       (float)((float10)(bVar3 & 0x7f) * fVar10 * (float10)fVar5 * (float10)_DAT_0056e414);
  sub_41BEE0();
  fVar7 = -((float)*(int *)(iVar9 + 8 + DAT_00586598) * (float)_DAT_0056e020);
  fVar6 = (float)*(int *)(iVar9 + 4 + DAT_00586598) * (float)_DAT_0056e020;
  fVar5 = (float)*(int *)(iVar9 + DAT_00586598) * (float)_DAT_0056e020;
  iVar4 = *(int *)(*(int *)(DAT_00584648 + 0x60) + (DAT_005865b8 + iVar8) * 4);
  *(float *)(iVar4 + 0x38) = fVar5;
  *(float *)(iVar4 + 0x20) = fVar5;
  *(float *)(iVar4 + 0x3c) = fVar6;
  *(float *)(iVar4 + 0x24) = fVar6;
  *(float *)(iVar4 + 0x40) = fVar7;
  *(float *)(iVar4 + 0x28) = fVar7;
  fVar6 = (float)*(int *)(iVar9 + 0x14 + DAT_00586598) * (float)_DAT_0056e020;
  fVar5 = (float)*(int *)(iVar9 + 0x10 + DAT_00586598) * (float)_DAT_0056e020;
  iVar4 = *(int *)(*(int *)(DAT_00584648 + 0x60) + (DAT_005865b8 + iVar8) * 4);
  *(float *)(iVar4 + 0x5c) = fVar5;
  *(float *)(iVar4 + 0x58) = fVar6;
  *(float *)(iVar4 + 0x54) = fVar5 * fVar5;
  *(float *)(iVar4 + 0x50) = fVar6 * fVar6;
  if (fVar6 - fVar5 != _DAT_0056e00c) {
    *(float *)(iVar4 + 0x60) = _DAT_0056e008 / (fVar6 - fVar5);
  }
  *(uint *)(*(int *)(*(int *)(DAT_00584648 + 0x60) + (DAT_005865b8 + iVar8) * 4) + 100) =
       (uint)*(byte *)(iVar9 + 0xf + DAT_00586598);
  return;
}

