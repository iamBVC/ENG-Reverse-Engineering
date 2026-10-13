/* Selected Ghidra export at 00408970. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_408970(int param_1,int param_2,int param_3,int param_4,uint *param_5,int param_6,int param_7,
          int param_8,int param_9,int param_10,undefined4 param_11,undefined4 param_12,char param_13
          ,uint param_14)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  char *pcVar14;
  undefined1 *puVar15;
  uint *puVar16;
  undefined2 *puVar17;
  char *pcVar18;
  
  iVar6 = param_14;
  uVar2 = *(uint *)(param_14 + 0x14);
  uVar3 = *(uint *)(param_14 + 0x10);
  uVar4 = *(uint *)(param_14 + 0x18);
  uVar5 = *(uint *)(param_14 + 0x1c);
  uVar13 = uVar3 | uVar2 | uVar4;
  param_14 = 0;
  if (DAT_006d7c6e != '\0') {
    param_14 = -uVar2 & uVar2;
    fVar7 = ((float)(int)(-uVar3 & uVar3) / (float)uVar3) * _DAT_0056e138;
    fVar8 = ((float)param_14 / (float)uVar2) * _DAT_0056e134;
    if (fVar7 < fVar8) {
      param_14 = -uVar3 & uVar3;
      fVar8 = fVar7;
    }
    if (((float)(-uVar4 & uVar4) / (float)uVar4) * _DAT_0056e130 <= fVar8) {
      param_14 = -uVar4 & uVar4;
    }
  }
  iVar6 = *(int *)(iVar6 + 0xc);
  pcVar18 = (char *)(param_4 * param_8 + param_3 + param_7);
  if (iVar6 == 8) {
    puVar15 = (undefined1 *)(param_2 * param_6 + param_1 + (int)param_5);
    if (0 < param_10) {
      param_7 = param_10;
      do {
        if (0 < param_9) {
          param_8 = param_9;
          pcVar14 = pcVar18;
          param_5 = (uint *)puVar15;
          do {
            cVar1 = *pcVar14;
            pcVar14 = pcVar14 + 1;
            if (cVar1 == '\0') {
              *(undefined1 *)param_5 = 0;
            }
            else {
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if ((param_13 != '\0') && ((uVar13 & uVar9) == 0)) {
                uVar9 = ~uVar13 & uVar9 | param_14;
              }
              *(char *)param_5 = (char)uVar9;
            }
            param_5 = (uint *)((int)param_5 + 1);
            param_8 = param_8 + -1;
          } while (param_8 != 0);
        }
        pcVar18 = pcVar18 + param_4;
        puVar15 = puVar15 + param_2;
        param_7 = param_7 + -1;
      } while (param_7 != 0);
    }
  }
  else if (iVar6 == 0x10) {
    puVar17 = (undefined2 *)(param_1 + param_2 * param_6 + (int)param_5 * 2);
    if (0 < param_10) {
      param_7 = param_10;
      do {
        if (0 < param_9) {
          param_10 = param_9;
          pcVar14 = pcVar18;
          param_5 = (uint *)puVar17;
          do {
            cVar1 = *pcVar14;
            pcVar14 = pcVar14 + 1;
            if (cVar1 == '\0') {
              *(undefined2 *)param_5 = 0;
            }
            else {
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if ((param_13 != '\0') && ((uVar13 & uVar9) == 0)) {
                uVar9 = ~uVar13 & uVar9 | param_14;
              }
              *(short *)param_5 = (short)uVar9;
            }
            param_5 = (uint *)((int)param_5 + 2);
            param_10 = param_10 + -1;
          } while (param_10 != 0);
        }
        pcVar18 = pcVar18 + param_4;
        puVar17 = (undefined2 *)((int)puVar17 + param_2);
        param_7 = param_7 + -1;
      } while (param_7 != 0);
      return 1;
    }
  }
  else {
    if (iVar6 != 0x20) {
      return 0;
    }
    puVar16 = (uint *)(param_1 + param_2 * param_6 + (int)param_5 * 4);
    if (0 < param_10) {
      param_7 = param_10;
      do {
        if (0 < param_9) {
          param_10 = param_9;
          pcVar14 = pcVar18;
          param_5 = puVar16;
          do {
            cVar1 = *pcVar14;
            pcVar14 = pcVar14 + 1;
            if (cVar1 == '\0') {
              *param_5 = 0;
            }
            else {
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5;
              if ((param_13 != '\0') && ((uVar13 & uVar9) == 0)) {
                uVar9 = ~uVar13 & uVar9 | param_14;
              }
              *param_5 = uVar9;
            }
            param_5 = param_5 + 1;
            param_10 = param_10 + -1;
          } while (param_10 != 0);
        }
        pcVar18 = pcVar18 + param_4;
        puVar16 = (uint *)((int)puVar16 + param_2);
        param_7 = param_7 + -1;
      } while (param_7 != 0);
      return 1;
    }
  }
  return 1;
}

