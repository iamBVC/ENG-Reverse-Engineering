/* Selected Ghidra export at 00409640. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_409640(int param_1,int param_2,uint *param_3,int param_4,ushort *param_5,float param_6,
          int param_7,float param_8,int param_9,char param_10,float param_11)

{
  ushort uVar1;
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
  char cVar13;
  char cVar14;
  uint uVar15;
  ushort *puVar16;
  undefined1 *puVar17;
  uint *puVar18;
  undefined2 *puVar19;
  undefined1 *puVar20;
  uint uStack_38;
  int iStack_10;
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
    fVar7 = ((float)(int)(-uVar2 & uVar2) / (float)uVar2) * _DAT_0056e138;
    fVar8 = ((float)uStack_38 / (float)uVar3) * _DAT_0056e134;
    if (fVar7 < fVar8) {
      uStack_38 = -uVar2 & uVar2;
      fVar8 = fVar7;
    }
    if (((float)(-uVar4 & uVar4) / (float)uVar4) * _DAT_0056e130 <= fVar8) {
      uStack_38 = -uVar4 & uVar4;
    }
  }
  iVar6 = *(int *)((int)param_11 + 0xc);
  puVar16 = (ushort *)((int)param_3 + (param_4 * (int)param_6 + (int)param_5) * 2);
  if (iVar6 == 8) {
    puVar17 = (undefined1 *)(param_2 * (int)param_6 + param_1 + (int)param_5);
    if (0 < (int)param_8) {
      iStack_8 = (int)param_8;
      param_5 = puVar16;
      do {
        if (0 < param_7) {
          param_3 = (uint *)param_7;
          puVar16 = param_5;
          puVar20 = puVar17;
          do {
            uVar1 = *puVar16;
            puVar16 = puVar16 + 1;
            if (uVar1 == 0) {
              *puVar20 = 0;
            }
            else {
              param_8 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_11 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_6 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) != 0) && (param_9 != 0)) {
                cVar14 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_9) {
                case 1:
                  if (cVar14 != '\0') {
                    param_8 = param_8 * _DAT_0056e158;
                    param_11 = param_11 * _DAT_0056e158;
                    param_6 = param_6 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  if (cVar14 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e130 +
                               param_11 * _DAT_0056e134 + param_8 * _DAT_0056e138);
                  }
                  break;
                case 3:
                  param_8 = 0.0;
                  param_11 = 0.0;
                  param_6 = 0.0;
                  break;
                case 4:
                  if (cVar14 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e144 +
                               param_11 * _DAT_0056e140 + param_8 * _DAT_0056e13c);
                  }
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar5 | uVar11 & uVar3 | uVar12 & uVar4;
              if ((param_10 != '\0') && ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar20 = (char)uVar9;
            }
            puVar20 = puVar20 + 1;
            param_3 = (uint *)((int)param_3 + -1);
          } while (param_3 != (uint *)0x0);
        }
        param_5 = param_5 + param_4;
        puVar17 = puVar17 + param_2;
        iStack_8 = iStack_8 + -1;
      } while (iStack_8 != 0);
    }
  }
  else if (iVar6 == 0x10) {
    param_3 = (uint *)(param_1 + param_2 * (int)param_6 + (int)param_5 * 2);
    if (0 < (int)param_8) {
      iStack_10 = (int)param_8;
      param_5 = puVar16;
      do {
        cVar14 = param_10;
        if (0 < param_7) {
          iStack_8 = param_7;
          puVar16 = param_5;
          puVar19 = (undefined2 *)param_3;
          do {
            uVar1 = *puVar16;
            puVar16 = puVar16 + 1;
            if (uVar1 == 0) {
              *puVar19 = 0;
            }
            else {
              param_8 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_11 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_6 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) != 0) && (param_9 != 0)) {
                cVar13 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_9) {
                case 1:
                  if (cVar13 != '\0') {
                    param_8 = param_8 * _DAT_0056e158;
                    param_11 = param_11 * _DAT_0056e158;
                    param_6 = param_6 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  if (cVar13 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e130 +
                               param_11 * _DAT_0056e134 + param_8 * _DAT_0056e138);
                  }
                  break;
                case 3:
                  param_8 = 0.0;
                  param_11 = 0.0;
                  param_6 = 0.0;
                  break;
                case 4:
                  if (cVar13 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e144 +
                               param_11 * _DAT_0056e140 + param_8 * _DAT_0056e13c);
                  }
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar5 | uVar11 & uVar3 | uVar12 & uVar4;
              if ((cVar14 != '\0') && ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar19 = (short)uVar9;
            }
            puVar19 = puVar19 + 1;
            iStack_8 = iStack_8 + -1;
          } while (iStack_8 != 0);
        }
        param_5 = param_5 + param_4;
        param_3 = (uint *)((int)param_3 + param_2);
        iStack_10 = iStack_10 + -1;
      } while (iStack_10 != 0);
      return 1;
    }
  }
  else {
    if (iVar6 != 0x20) {
      return 0;
    }
    param_3 = (uint *)(param_1 + param_2 * (int)param_6 + (int)param_5 * 4);
    if (0 < (int)param_8) {
      iStack_8 = (int)param_8;
      param_5 = puVar16;
      do {
        cVar14 = param_10;
        if (0 < param_7) {
          iStack_10 = param_7;
          puVar16 = param_5;
          puVar18 = param_3;
          do {
            uVar1 = *puVar16;
            puVar16 = puVar16 + 1;
            if (uVar1 == 0) {
              *puVar18 = 0;
            }
            else {
              param_8 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
              param_11 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;
              param_6 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
              if (((uVar1 & 0x8000) != 0) && (param_9 != 0)) {
                cVar13 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_9) {
                case 1:
                  if (cVar13 != '\0') {
                    param_8 = param_8 * _DAT_0056e158;
                    param_11 = param_11 * _DAT_0056e158;
                    param_6 = param_6 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  if (cVar13 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e130 +
                               param_11 * _DAT_0056e134 + param_8 * _DAT_0056e138);
                  }
                  break;
                case 3:
                  param_8 = 0.0;
                  param_11 = 0.0;
                  param_6 = 0.0;
                  break;
                case 4:
                  if (cVar13 == '\0') {
                    sub_409510(&param_8,&param_11,&param_6,
                               param_6 * _DAT_0056e144 +
                               param_11 * _DAT_0056e140 + param_8 * _DAT_0056e13c);
                  }
                }
              }
              uVar9 = __ftol();
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar9 = uVar9 & uVar2 | uVar10 & uVar5 | uVar11 & uVar3 | uVar12 & uVar4;
              if ((cVar14 != '\0') && ((uVar15 & uVar9) == 0)) {
                uVar9 = ~uVar15 & uVar9 | uStack_38;
              }
              *puVar18 = uVar9;
            }
            puVar18 = puVar18 + 1;
            iStack_10 = iStack_10 + -1;
          } while (iStack_10 != 0);
        }
        param_5 = param_5 + param_4;
        param_3 = (uint *)((int)param_3 + param_2);
        iStack_8 = iStack_8 + -1;
      } while (iStack_8 != 0);
      return 1;
    }
  }
  return 1;
}

