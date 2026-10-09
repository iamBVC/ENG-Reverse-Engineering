/* sub_4370C0 @ 004370c0   452 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4370C0(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  float *pfVar14;
  int iVar15;
  byte local_2a7;
  byte local_2a6;
  byte local_2a5;
  int local_2a4;
  int local_294 [33];
  int local_210 [33];
  int local_18c [33];
  int local_108 [33];
  float local_84 [33];
  
  uVar8 = 1;
  local_2a6 = 1;
  do {
    piVar13 = local_108;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar13 = 0;
      piVar13 = piVar13 + 1;
    }
    piVar13 = local_294;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar13 = 0;
      piVar13 = piVar13 + 1;
    }
    piVar13 = local_210;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar13 = 0;
      piVar13 = piVar13 + 1;
    }
    piVar13 = local_18c;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar13 = 0;
      piVar13 = piVar13 + 1;
    }
    pfVar14 = local_84;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar14 = 0.0;
      pfVar14 = pfVar14 + 1;
    }
    local_2a7 = 1;
    do {
      iVar12 = 0;
      uVar9 = 1;
      iVar10 = 0;
      iVar15 = 0;
      local_2a4 = 0;
      local_2a5 = 1;
      iVar7 = 0;
      fVar4 = _DAT_0056e00c;
      do {
        uVar9 = uVar9 + ((uint)local_2a7 + uVar8 * 0x21) * 0x21;
        uVar6 = uVar9 & 0xffff;
        uVar9 = uVar9 - 0x441 & 0xffff;
        iVar12 = iVar12 + (&DAT_006b4544)[uVar6];
        iVar15 = iVar15 + (&DAT_006913c0)[uVar6];
        iVar10 = iVar10 + (&DAT_0066e23c)[uVar6];
        local_2a4 = local_2a4 + (&DAT_0064b0b8)[uVar6];
        piVar13 = (int *)((int)local_210 + iVar7 + 4);
        *piVar13 = *piVar13 + iVar10;
        piVar13 = (int *)((int)local_294 + iVar7 + 4);
        *piVar13 = *piVar13 + iVar15;
        piVar13 = (int *)((int)local_18c + iVar7 + 4);
        *piVar13 = *piVar13 + local_2a4;
        iVar2 = (&DAT_006b4544)[uVar9];
        fVar4 = fVar4 + (float)(&DAT_00627f34)[uVar6];
        iVar11 = *(int *)((int)local_108 + iVar7 + 4) + iVar12;
        *(int *)((int)local_108 + iVar7 + 4) = iVar11;
        iVar3 = *(int *)((int)local_294 + iVar7 + 4);
        (&DAT_006b4544)[uVar6] = iVar2 + iVar11;
        fVar5 = fVar4 + *(float *)((int)local_84 + iVar7 + 4);
        iVar2 = *(int *)((int)local_210 + iVar7 + 4);
        (&DAT_006913c0)[uVar6] = (&DAT_006913c0)[uVar9] + iVar3;
        iVar3 = (&DAT_0066e23c)[uVar9];
        iVar11 = *(int *)((int)local_18c + iVar7 + 4);
        *(float *)((int)local_84 + iVar7 + 4) = fVar5;
        fVar1 = (float)(&DAT_00627f34)[uVar9];
        (&DAT_0066e23c)[uVar6] = iVar3 + iVar2;
        (&DAT_0064b0b8)[uVar6] = (&DAT_0064b0b8)[uVar9] + iVar11;
        (&DAT_00627f34)[uVar6] = fVar5 + fVar1;
        local_2a5 = local_2a5 + 1;
        uVar9 = (uint)local_2a5;
        iVar7 = iVar7 + 4;
      } while (local_2a5 < 0x21);
      local_2a7 = local_2a7 + 1;
    } while (local_2a7 < 0x21);
    local_2a6 = local_2a6 + 1;
    uVar8 = (uint)local_2a6;
  } while (local_2a6 < 0x21);
  return;
}

