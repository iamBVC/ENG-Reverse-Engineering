/* Selected Ghidra export at 0040b750. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_40B750(float param_1,int param_2,uint *param_3,int param_4,float param_5,float param_6,
          undefined2 *param_7,int param_8,int param_9,float param_10,int param_11,int param_12,
          int param_13,uint param_14)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  char cVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  byte *pbVar17;
  byte *pbVar18;
  undefined1 *puVar19;
  uint *puVar20;
  undefined2 *puVar21;
  undefined1 *puVar22;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float fStack_10;
  
  iVar14 = param_14;
  uVar3 = *(uint *)(param_14 + 0x10);
  uVar4 = *(uint *)(param_14 + 0x14);
  uVar5 = *(uint *)(param_14 + 0x18);
  uVar6 = *(uint *)(param_14 + 0x1c);
  uVar16 = uVar3 | uVar4 | uVar5;
  if (DAT_006d7c6e == '\0') {
    param_14 = 0;
  }
  else {
    param_14 = -uVar4 & uVar4;
    fVar7 = ((float)(int)(-uVar3 & uVar3) / (float)uVar3) * _DAT_0056e138;
    fVar8 = ((float)param_14 / (float)uVar4) * _DAT_0056e134;
    if (fVar7 < fVar8) {
      param_14 = -uVar3 & uVar3;
      fVar8 = fVar7;
    }
    if (((float)(-uVar5 & uVar5) / (float)uVar5) * _DAT_0056e130 <= fVar8) {
      param_14 = -uVar5 & uVar5;
    }
  }
  iVar14 = *(int *)(iVar14 + 0xc);
  pbVar17 = (byte *)(param_4 * param_8 + (int)param_3 + (int)param_7);
  if (iVar14 == 8) {
    puVar22 = (undefined1 *)(param_2 * (int)param_6 + (int)param_1 + (int)param_5);
    if (0 < (int)param_10) {
      fStack_10 = param_10;
      iVar14 = param_9;
      iVar15 = param_12;
      do {
        pbVar18 = pbVar17;
        puVar19 = puVar22;
        param_3 = (uint *)pbVar17;
        param_7 = (undefined2 *)iVar14;
        if (0 < iVar14) {
          do {
            bVar1 = *pbVar18;
            param_8 = CONCAT31(param_8._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar19 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_6 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_1 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_5 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((short)uVar2 < 0) && (iVar15 != 0)) {
                switch(iVar15) {
                case 1:
                  goto switchD_0040be40_caseD_1;
                case 2:
                case 4:
                  param_10 = param_5 * _DAT_0056e130 +
                             param_1 * _DAT_0056e134 + param_6 * _DAT_0056e138;
                  sub_409510(&param_6,&param_1,&param_5,param_10);
                  if (param_10 != _DAT_0056e00c) goto switchD_0040be40_caseD_1;
                  break;
                case 3:
                  param_6 = 0.0;
                  param_1 = 0.0;
                  param_5 = 0.0;
                }
              }
              else {
switchD_0040be40_caseD_1:
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if ((((char)param_13 != '\0') && (extraout_ST0_01 != (float10)_DAT_0056e00c)) &&
                 ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | param_14;
              }
              *puVar19 = (char)uVar10;
              iVar15 = param_12;
              pbVar17 = (byte *)param_3;
            }
            param_7 = (undefined2 *)((int)param_7 + -1);
            iVar14 = param_9;
            pbVar18 = pbVar18 + 1;
            puVar19 = puVar19 + 1;
          } while (param_7 != (undefined2 *)0x0);
        }
        pbVar17 = pbVar17 + param_4;
        puVar22 = puVar22 + param_2;
        fStack_10 = (float)((int)fStack_10 + -1);
      } while (fStack_10 != 0.0);
    }
  }
  else if (iVar14 == 0x10) {
    param_7 = (undefined2 *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 2);
    if (0 < (int)param_10) {
      cVar9 = (char)param_13;
      fStack_10 = param_10;
      iVar14 = param_9;
      iVar15 = param_12;
      param_3 = (uint *)pbVar17;
      do {
        pbVar17 = (byte *)param_3;
        puVar21 = param_7;
        param_13 = iVar14;
        if (0 < iVar14) {
          do {
            bVar1 = *pbVar17;
            param_8 = CONCAT31(param_8._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar21 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_6 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_1 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_5 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((uVar2 & 0x8000) == 0) || (iVar15 == 0)) {
switchD_0040bbef_caseD_1:
              }
              else {
                switch(iVar15) {
                case 1:
                  goto switchD_0040bbef_caseD_1;
                case 2:
                case 4:
                  param_10 = param_5 * _DAT_0056e130 +
                             param_1 * _DAT_0056e134 + param_6 * _DAT_0056e138;
                  sub_409510(&param_6,&param_1,&param_5,param_10);
                  if (param_10 != _DAT_0056e00c) goto switchD_0040bbef_caseD_1;
                  break;
                case 3:
                  param_6 = 0.0;
                  param_1 = 0.0;
                  param_5 = 0.0;
                }
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if (((cVar9 != '\0') && (extraout_ST0_00 != (float10)_DAT_0056e00c)) &&
                 ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | param_14;
              }
              *puVar21 = (short)uVar10;
              iVar15 = param_12;
            }
            param_13 = param_13 + -1;
            iVar14 = param_9;
            pbVar17 = pbVar17 + 1;
            puVar21 = puVar21 + 1;
          } while (param_13 != 0);
        }
        param_3 = (uint *)((int)param_3 + param_4);
        param_7 = (undefined2 *)((int)param_7 + param_2);
        fStack_10 = (float)((int)fStack_10 + -1);
        if (fStack_10 == 0.0) {
          return 1;
        }
      } while( true );
    }
  }
  else {
    if (iVar14 != 0x20) {
      return 0;
    }
    param_3 = (uint *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 4);
    if (0 < (int)param_10) {
      fStack_10 = param_10;
      do {
        if (0 < param_9) {
          param_7 = (undefined2 *)param_9;
          pbVar18 = pbVar17;
          puVar20 = param_3;
          do {
            bVar1 = *pbVar18;
            pbVar18 = pbVar18 + 1;
            param_8 = CONCAT31(param_8._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar20 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_6 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_1 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_5 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((uVar2 & 0x8000) == 0) || (param_12 == 0)) {
switchD_0040b998_caseD_1:
              }
              else {
                switch(param_12) {
                case 1:
                  goto switchD_0040b998_caseD_1;
                case 2:
                case 4:
                  param_10 = param_5 * _DAT_0056e130 +
                             param_1 * _DAT_0056e134 + param_6 * _DAT_0056e138;
                  sub_409510(&param_6,&param_1,&param_5,param_10);
                  if (param_10 != _DAT_0056e00c) goto switchD_0040b998_caseD_1;
                  break;
                case 3:
                  param_6 = 0.0;
                  param_1 = 0.0;
                  param_5 = 0.0;
                }
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if ((((char)param_13 != '\0') && (extraout_ST0 != (float10)_DAT_0056e00c)) &&
                 ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | param_14;
              }
              *puVar20 = uVar10;
            }
            puVar20 = puVar20 + 1;
            param_7 = (undefined2 *)((int)param_7 + -1);
          } while (param_7 != (undefined2 *)0x0);
        }
        param_3 = (uint *)((int)param_3 + param_2);
        pbVar17 = pbVar17 + param_4;
        fStack_10 = (float)((int)fStack_10 + -1);
        if (fStack_10 == 0.0) {
          return 1;
        }
      } while( true );
    }
  }
  return 1;
}

