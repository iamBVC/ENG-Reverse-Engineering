/* sub_408470 @ 00408470   1277 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_408470(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
          int param_8,undefined4 param_9,char param_10,short *param_11)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  short *psVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint *puVar14;
  undefined2 *puVar15;
  uint uVar16;
  undefined1 *puVar17;
  uint *puVar18;
  undefined2 *puVar19;
  undefined1 *puVar20;
  uint local_30;
  
  uVar13 = 0;
  uVar2 = *(uint *)((int)param_11 + 0x10);
  uVar3 = *(uint *)((int)param_11 + 0x14);
  uVar4 = *(uint *)((int)param_11 + 0x18);
  uVar5 = *(uint *)((int)param_11 + 0x1c);
  uVar16 = uVar2 | uVar3 | uVar4;
  if (DAT_006d7c6e != '\0') {
    local_30 = -uVar3 & uVar3;
    uVar13 = -uVar4 & uVar4;
    fVar6 = ((float)(int)(-uVar2 & uVar2) / (float)uVar2) * _DAT_0056e138;
    fVar7 = ((float)local_30 / (float)uVar3) * _DAT_0056e134;
    if (fVar6 < fVar7) {
      local_30 = -uVar2 & uVar2;
      fVar7 = fVar6;
    }
    if (fVar7 < ((float)uVar13 / (float)uVar4) * _DAT_0056e130) goto LAB_0040858a;
  }
  local_30 = uVar13;
LAB_0040858a:
  iVar12 = *(int *)((int)param_11 + 0xc);
  param_11 = (short *)(param_3 + (param_4 * param_6 + param_5) * 2);
  if (iVar12 == 8) {
    puVar17 = (undefined1 *)(param_2 * param_6 + param_1 + param_5);
    if (0 < param_8) {
      param_5 = param_8;
      do {
        iVar12 = param_7;
        psVar8 = param_11;
        puVar20 = puVar17;
        if (0 < param_7) {
          do {
            if (*psVar8 == 0) {
              *puVar20 = 0;
            }
            else {
              uVar13 = __ftol();
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar13 = uVar13 & uVar3 | uVar9 & uVar2 | uVar10 & uVar4 | uVar11 & uVar5;
              if ((param_10 != '\0') && ((uVar16 & uVar13) == 0)) {
                uVar13 = ~uVar16 & uVar13 | local_30;
              }
              *puVar20 = (char)uVar13;
            }
            iVar12 = iVar12 + -1;
            psVar8 = psVar8 + 1;
            puVar20 = puVar20 + 1;
          } while (iVar12 != 0);
        }
        param_11 = param_11 + param_4;
        puVar17 = puVar17 + param_2;
        param_5 = param_5 + -1;
      } while (param_5 != 0);
    }
  }
  else if (iVar12 == 0x10) {
    puVar15 = (undefined2 *)(param_1 + param_2 * param_6 + param_5 * 2);
    if (0 < param_8) {
      param_5 = param_8;
      do {
        if (0 < param_7) {
          param_8 = param_7;
          psVar8 = param_11;
          puVar19 = puVar15;
          do {
            sVar1 = *psVar8;
            psVar8 = psVar8 + 1;
            if (sVar1 == 0) {
              *puVar19 = 0;
            }
            else {
              uVar13 = __ftol();
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar13 = uVar13 & uVar3 | uVar9 & uVar2 | uVar10 & uVar4 | uVar11 & uVar5;
              if ((param_10 != '\0') && ((uVar16 & uVar13) == 0)) {
                uVar13 = ~uVar16 & uVar13 | local_30;
              }
              *puVar19 = (short)uVar13;
            }
            puVar19 = puVar19 + 1;
            param_8 = param_8 + -1;
          } while (param_8 != 0);
        }
        param_11 = param_11 + param_4;
        puVar15 = (undefined2 *)((int)puVar15 + param_2);
        param_5 = param_5 + -1;
      } while (param_5 != 0);
      return 1;
    }
  }
  else {
    if (iVar12 != 0x20) {
      return 0;
    }
    puVar14 = (uint *)(param_1 + param_2 * param_6 + param_5 * 4);
    if (0 < param_8) {
      param_5 = param_8;
      do {
        if (0 < param_7) {
          param_8 = param_7;
          psVar8 = param_11;
          puVar18 = puVar14;
          do {
            sVar1 = *psVar8;
            psVar8 = psVar8 + 1;
            if (sVar1 == 0) {
              *puVar18 = 0;
            }
            else {
              uVar13 = __ftol();
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar13 = uVar13 & uVar3 | uVar9 & uVar2 | uVar10 & uVar4 | uVar11 & uVar5;
              if ((param_10 != '\0') && ((uVar16 & uVar13) == 0)) {
                uVar13 = ~uVar16 & uVar13 | local_30;
              }
              *puVar18 = uVar13;
            }
            puVar18 = puVar18 + 1;
            param_8 = param_8 + -1;
          } while (param_8 != 0);
        }
        param_11 = param_11 + param_4;
        puVar14 = (uint *)((int)puVar14 + param_2);
        param_5 = param_5 + -1;
      } while (param_5 != 0);
      return 1;
    }
  }
  return 1;
}

