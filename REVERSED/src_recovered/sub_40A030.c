/* Selected Ghidra export at 0040a030. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_40A030(float param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
          uint *param_7,byte *param_8,int param_9,float param_10,int param_11,int param_12,
          char param_13,byte *param_14)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  char cVar14;
  char cVar15;
  uint uVar16;
  byte *pbVar17;
  undefined1 *puVar18;
  uint *puVar19;
  undefined2 *puVar20;
  undefined1 *puVar21;
  uint uStack_38;
  int iStack_10;
  int iStack_8;
  
  uVar3 = *(uint *)((int)param_14 + 0x10);
  uVar4 = *(uint *)((int)param_14 + 0x14);
  uVar5 = *(uint *)((int)param_14 + 0x18);
  uVar6 = *(uint *)((int)param_14 + 0x1c);
  uVar16 = uVar3 | uVar4 | uVar5;
  if (DAT_006d7c6e == '\0') {
    uStack_38 = 0;
  }
  else {
    uStack_38 = -uVar4 & uVar4;
    fVar8 = ((float)(int)(-uVar3 & uVar3) / (float)uVar3) * _DAT_0056e138;
    fVar9 = ((float)uStack_38 / (float)uVar4) * _DAT_0056e134;
    if (fVar8 < fVar9) {
      uStack_38 = -uVar3 & uVar3;
      fVar9 = fVar8;
    }
    if (((float)(-uVar5 & uVar5) / (float)uVar5) * _DAT_0056e130 <= fVar9) {
      uStack_38 = -uVar5 & uVar5;
    }
  }
  iVar7 = *(int *)((int)param_14 + 0xc);
  pbVar17 = (byte *)(param_4 * (int)param_8 + param_3 + (int)param_7);
  if (iVar7 == 8) {
    puVar21 = (undefined1 *)(param_2 * (int)param_6 + (int)param_1 + (int)param_5);
    if (0 < (int)param_10) {
      param_7 = (uint *)param_10;
      do {
        param_14 = pbVar17;
        if (0 < param_9) {
          param_8 = (byte *)param_9;
          puVar18 = puVar21;
          do {
            bVar1 = *pbVar17;
            pbVar17 = pbVar17 + 1;
            param_3 = CONCAT31(param_3._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar18 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_1 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_5 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_10 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((uVar2 & 0x8000) == 0) || (param_12 == 0)) {
LAB_0040a914:
                param_6 = 1.0;
              }
              else {
                cVar15 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_12) {
                case 1:
                  param_6 = 0.5;
                  if (cVar15 != '\0') {
                    param_1 = param_1 * _DAT_0056e158;
                    param_5 = param_5 * _DAT_0056e158;
                    param_10 = param_10 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  param_6 = param_10 * _DAT_0056e130 +
                            param_5 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  if (cVar15 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                  if (_DAT_0056e008 < param_6) goto LAB_0040a914;
                  break;
                case 3:
                  param_6 = param_10 * _DAT_0056e150 +
                            param_5 * _DAT_0056e14c + param_1 * _DAT_0056e148;
                  if (_DAT_0056e008 < param_6) {
                    param_6 = 1.0;
                  }
                  param_1 = 0.0;
                  param_5 = 0.0;
                  param_10 = 0.0;
                  break;
                case 4:
                  param_6 = param_10 * _DAT_0056e144 +
                            param_5 * _DAT_0056e140 + param_1 * _DAT_0056e13c;
                  if (cVar15 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                }
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if ((param_13 != '\0') && ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | uStack_38;
              }
              *puVar18 = (char)uVar10;
            }
            puVar18 = puVar18 + 1;
            param_8 = (byte *)((int)param_8 + -1);
          } while (param_8 != (byte *)0x0);
        }
        pbVar17 = param_14 + param_4;
        puVar21 = puVar21 + param_2;
        param_7 = (uint *)((int)param_7 + -1);
      } while (param_7 != (uint *)0x0);
    }
  }
  else if (iVar7 == 0x10) {
    param_7 = (uint *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 2);
    if (0 < (int)param_10) {
      iStack_10 = (int)param_10;
      do {
        cVar15 = param_13;
        param_14 = pbVar17;
        if (0 < param_9) {
          iStack_8 = param_9;
          puVar20 = (undefined2 *)param_7;
          param_8 = pbVar17;
          do {
            bVar1 = *param_8;
            param_8 = param_8 + 1;
            param_3 = CONCAT31(param_3._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar20 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_1 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_5 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_10 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((short)uVar2 < 0) && (param_12 != 0)) {
                cVar14 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_12) {
                case 1:
                  param_6 = 0.5;
                  if (cVar14 != '\0') {
                    param_1 = param_1 * _DAT_0056e158;
                    param_5 = param_5 * _DAT_0056e158;
                    param_10 = param_10 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  param_6 = param_10 * _DAT_0056e130 +
                            param_5 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  if (cVar14 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                  if (_DAT_0056e008 < param_6) goto LAB_0040a63a;
                  break;
                case 3:
                  param_6 = param_10 * _DAT_0056e150 +
                            param_5 * _DAT_0056e14c + param_1 * _DAT_0056e148;
                  if (_DAT_0056e008 < param_6) {
                    param_6 = 1.0;
                  }
                  param_1 = 0.0;
                  param_5 = 0.0;
                  param_10 = 0.0;
                  break;
                case 4:
                  param_6 = param_10 * _DAT_0056e144 +
                            param_5 * _DAT_0056e140 + param_1 * _DAT_0056e13c;
                  if (cVar14 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                }
              }
              else {
LAB_0040a63a:
                param_6 = 1.0;
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if ((cVar15 != '\0') && ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | uStack_38;
              }
              *puVar20 = (short)uVar10;
            }
            puVar20 = puVar20 + 1;
            iStack_8 = iStack_8 + -1;
          } while (iStack_8 != 0);
        }
        param_7 = (uint *)((int)param_7 + param_2);
        pbVar17 = param_14 + param_4;
        iStack_10 = iStack_10 + -1;
        if (iStack_10 == 0) {
          return 1;
        }
      } while( true );
    }
  }
  else {
    if (iVar7 != 0x20) {
      return 0;
    }
    param_7 = (uint *)((int)param_1 + param_2 * (int)param_6 + (int)param_5 * 4);
    if (0 < (int)param_10) {
      iStack_8 = (int)param_10;
      do {
        cVar15 = param_13;
        param_14 = pbVar17;
        if (0 < param_9) {
          iStack_10 = param_9;
          puVar19 = param_7;
          param_8 = pbVar17;
          do {
            bVar1 = *param_8;
            param_8 = param_8 + 1;
            param_3 = CONCAT31(param_3._1_3_,bVar1);
            if (bVar1 == 0) {
              *puVar19 = 0;
            }
            else {
              uVar2 = *(ushort *)(param_11 + (uint)bVar1 * 2);
              param_1 = (float)((byte)uVar2 & 0x1f) * _DAT_0056e11c;
              param_5 = (float)(uVar2 & 0x3e0) * _DAT_0056e124;
              param_10 = (float)(uVar2 & 0x7c00) * _DAT_0056e12c;
              if (((uVar2 & 0x8000) == 0) || (param_12 == 0)) {
LAB_0040a33d:
                param_6 = 1.0;
              }
              else {
                cVar14 = (char)((uint)_DAT_006d7c6e >> 8);
                switch(param_12) {
                case 1:
                  param_6 = 0.5;
                  if (cVar14 != '\0') {
                    param_1 = param_1 * _DAT_0056e158;
                    param_5 = param_5 * _DAT_0056e158;
                    param_10 = param_10 * _DAT_0056e158;
                  }
                  break;
                case 2:
                  param_6 = param_10 * _DAT_0056e130 +
                            param_5 * _DAT_0056e134 + param_1 * _DAT_0056e138;
                  if (cVar14 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                  if (_DAT_0056e008 < param_6) goto LAB_0040a33d;
                  break;
                case 3:
                  param_6 = param_10 * _DAT_0056e150 +
                            param_5 * _DAT_0056e14c + param_1 * _DAT_0056e148;
                  if (_DAT_0056e008 < param_6) {
                    param_6 = 1.0;
                  }
                  param_1 = 0.0;
                  param_5 = 0.0;
                  param_10 = 0.0;
                  break;
                case 4:
                  param_6 = param_10 * _DAT_0056e144 +
                            param_5 * _DAT_0056e140 + param_1 * _DAT_0056e13c;
                  if (cVar14 == '\0') {
                    sub_409510(&param_1,&param_5,&param_10,param_6);
                  }
                }
              }
              uVar10 = __ftol();
              uVar11 = __ftol();
              uVar12 = __ftol();
              uVar13 = __ftol();
              uVar10 = uVar10 & uVar3 | uVar11 & uVar4 | uVar12 & uVar5 | uVar13 & uVar6;
              if ((cVar15 != '\0') && ((uVar16 & uVar10) == 0)) {
                uVar10 = ~uVar16 & uVar10 | uStack_38;
              }
              *puVar19 = uVar10;
            }
            puVar19 = puVar19 + 1;
            iStack_10 = iStack_10 + -1;
          } while (iStack_10 != 0);
        }
        param_7 = (uint *)((int)param_7 + param_2);
        pbVar17 = param_14 + param_4;
        iStack_8 = iStack_8 + -1;
        if (iStack_8 == 0) {
          return 1;
        }
      } while( true );
    }
  }
  return 1;
}

