/* Selected Ghidra export at 0040af10. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_40AF10(float param_1,int param_2,undefined2 *param_3,int param_4,uint *param_5,float param_6,
          int param_7,float param_8,int param_9,int param_10,float param_11)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  ushort *puVar16;
  ushort *puVar17;
  undefined1 *puVar18;
  uint *puVar19;
  undefined2 *puVar20;
  undefined1 *puVar21;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  uint uStack_38;
  int iStack_8;
  
  uVar2 = *(uint *)((int)param_11 + 0x10);
  uVar3 = *(uint *)((int)param_11 + 0x14);
  uVar4 = *(uint *)((int)param_11 + 0x18);
  uVar5 = *(uint *)((int)param_11 + 0x1c);
  uVar15 = uVar2 | uVar3 | uVar4;
  if (DAT_006d7c6e == '\0') {
    uStack_38 = 0;
  }
  else {
    uStack_38 = -uVar3 & uVar3;
    fVar6 = ((float)(int)(-uVar2 & uVar2) / (float)uVar2) * _DAT_0056e138;
    fVar7 = ((float)uStack_38 / (float)uVar3) * _DAT_0056e134;
    if (fVar6 < fVar7) {
      uStack_38 = -uVar2 & uVar2;
      fVar7 = fVar6;
    }
    if (((float)(-uVar4 & uVar4) / (float)uVar4) * _DAT_0056e130 <= fVar7) {
      uStack_38 = -uVar4 & uVar4;
    }
  }
  iVar13 = *(int *)((int)param_11 + 0xc);
  puVar16 = (ushort *)((int)param_3 + (param_4 * (int)param_6 + (int)param_5) * 2);
  if (iVar13 == 8) {
    puVar18 = (undefined1 *)(param_2 * (int)param_6 + (int)param_1 + (int)param_5);
    if (0 < (int)param_8) {
      iStack_8 = (int)param_8;
      iVar13 = param_7;
      iVar14 = param_9;
      do {
        puVar17 = puVar16;
        puVar21 = puVar18;
        param_3 = (undefined2 *)iVar13;
        param_5 = (uint *)puVar16;
        if (0 < iVar13) {
          do {
            uVar1 = *puVar17;
            if (uVar1 == 0) {
              *puVar21 = 0;
            }
            else {
              param_1 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_8 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_11 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) == 0) || (iVar14 == 0)) {
switchD_0040b592_caseD_1:
              }
              else {
                switch(iVar14) {
                case 1:
                  goto switchD_0040b592_caseD_1;
                case 2:
                case 4:
                  param_6 = param_11 * _DAT_0056e130 +
                            param_8 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  sub_409510(&param_1,&param_8,&param_11,param_6);
                  if (param_6 != _DAT_0056e00c) goto switchD_0040b592_caseD_1;
                  break;
                case 3:
                  param_1 = 0.0;
                  param_8 = 0.0;
                  param_11 = 0.0;
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if ((((char)param_10 != '\0') && (extraout_ST0_01 != (float10)_DAT_0056e00c)) &&
                 ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar21 = (char)uVar9;
              iVar14 = param_9;
              puVar16 = (ushort *)param_5;
            }
            param_3 = (undefined2 *)((int)param_3 + -1);
            iVar13 = param_7;
            puVar17 = puVar17 + 1;
            puVar21 = puVar21 + 1;
          } while (param_3 != (undefined2 *)0x0);
        }
        puVar18 = puVar18 + param_2;
        puVar16 = puVar16 + param_4;
        iStack_8 = iStack_8 + -1;
      } while (iStack_8 != 0);
    }
  }
  else if (iVar13 == 0x10) {
    param_3 = (undefined2 *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 2);
    if (0 < (int)param_8) {
      cVar8 = (char)param_10;
      iStack_8 = (int)param_8;
      iVar13 = param_7;
      iVar14 = param_9;
      param_5 = (uint *)puVar16;
      do {
        puVar16 = (ushort *)param_5;
        puVar20 = param_3;
        param_10 = iVar13;
        if (0 < iVar13) {
          do {
            uVar1 = *puVar16;
            if (uVar1 == 0) {
              *puVar20 = 0;
            }
            else {
              param_1 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_8 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_11 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) == 0) || (iVar14 == 0)) {
switchD_0040b35d_caseD_1:
              }
              else {
                switch(iVar14) {
                case 1:
                  goto switchD_0040b35d_caseD_1;
                case 2:
                case 4:
                  param_6 = param_11 * _DAT_0056e130 +
                            param_8 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  sub_409510(&param_1,&param_8,&param_11,param_6);
                  if (param_6 != _DAT_0056e00c) goto switchD_0040b35d_caseD_1;
                  break;
                case 3:
                  param_1 = 0.0;
                  param_8 = 0.0;
                  param_11 = 0.0;
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if (((cVar8 != '\0') && (extraout_ST0_00 != (float10)_DAT_0056e00c)) &&
                 ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar20 = (short)uVar9;
              iVar14 = param_9;
            }
            param_10 = param_10 + -1;
            iVar13 = param_7;
            puVar16 = puVar16 + 1;
            puVar20 = puVar20 + 1;
          } while (param_10 != 0);
        }
        param_5 = (uint *)((int)param_5 + param_4 * 2);
        param_3 = (undefined2 *)((int)param_3 + param_2);
        iStack_8 = iStack_8 + -1;
        if (iStack_8 == 0) {
          return 1;
        }
      } while( true );
    }
  }
  else {
    if (iVar13 != 0x20) {
      return 0;
    }
    param_5 = (uint *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 4);
    if (0 < (int)param_8) {
      iStack_8 = (int)param_8;
      do {
        if (0 < param_7) {
          param_3 = (undefined2 *)param_7;
          puVar17 = puVar16;
          puVar19 = param_5;
          do {
            uVar1 = *puVar17;
            puVar17 = puVar17 + 1;
            if (uVar1 == 0) {
              *puVar19 = 0;
            }
            else {
              param_1 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_8 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_11 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) == 0) || (param_9 == 0)) {
switchD_0040b125_caseD_1:
              }
              else {
                switch(param_9) {
                case 1:
                  goto switchD_0040b125_caseD_1;
                case 2:
                case 4:
                  param_6 = param_11 * _DAT_0056e130 +
                            param_8 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  sub_409510(&param_1,&param_8,&param_11,param_6);
                  if (param_6 != _DAT_0056e00c) goto switchD_0040b125_caseD_1;
                  break;
                case 3:
                  param_1 = 0.0;
                  param_8 = 0.0;
                  param_11 = 0.0;
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if ((((char)param_10 != '\0') && (extraout_ST0 != (float10)_DAT_0056e00c)) &&
                 ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar19 = uVar9;
            }
            puVar19 = puVar19 + 1;
            param_3 = (undefined2 *)((int)param_3 + -1);
          } while (param_3 != (undefined2 *)0x0);
        }
        puVar16 = puVar16 + param_4;
        param_5 = (uint *)((int)param_5 + param_2);
        iStack_8 = iStack_8 + -1;
        if (iStack_8 == 0) {
          return 1;
        }
      } while( true );
    }
  }
  return 1;
}

