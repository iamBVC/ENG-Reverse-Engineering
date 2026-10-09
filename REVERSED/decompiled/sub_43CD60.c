/* sub_43CD60 @ 0043cd60   24079 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_43CD60(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6,
               float *param_7,float *param_8,uint param_9)

{
  ushort uVar1;
  short sVar2;
  float fVar3;
  undefined4 uVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  undefined2 *puVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined2 *puVar15;
  uint uVar16;
  ushort *puVar17;
  int iVar18;
  uint uVar19;
  float fVar20;
  uint uVar21;
  float fVar22;
  int iVar23;
  ushort *local_148;
  ushort *local_144;
  ushort *local_140;
  float local_13c;
  uint local_138;
  float local_134;
  float local_130;
  uint local_12c;
  uint local_128;
  int local_124;
  short *local_120;
  uint local_11c;
  ushort local_118;
  int local_110;
  float local_10c [8];
  int local_ec;
  uint local_e8;
  float local_e4;
  float local_e0;
  uint local_dc;
  float local_d8 [8];
  uint local_b8;
  undefined4 uStack_b4;
  uint local_b0;
  uint local_ac;
  undefined4 uStack_a8;
  uint local_a4;
  float local_a0;
  float local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  int local_8c;
  float local_88 [8];
  int local_68;
  uint local_64;
  float afStack_60 [8];
  float afStack_40 [8];
  undefined4 auStack_20 [8];
  
  if ((param_3 == 0) || ((param_9 & 0x100) != 0)) {
    uVar19 = 100;
  }
  else {
    uVar19 = 0;
  }
  local_98 = param_9 & 0x18;
  local_64 = param_9 & 1;
  uVar13 = (-(uint)(((byte)param_9 & 0x60) != 0x20) & 0xfffffff0) + 0x10;
  uVar16 = param_9 >> 5 & 0x10;
  local_94 = -(uint)(local_98 != 0x18) & 8;
  uVar21 = -(uint)(param_3 != 0) & 3;
  uVar19 = uVar13 | uVar16 | local_94 | uVar21 | local_64 * 4 | uVar19;
  uVar11 = (int)param_9 >> 3;
  local_90 = uVar19;
  if ((param_9 & 0x2a0) == 0) {
    if (uVar21 != 0) {
      local_88[0] = param_6[6] * _DAT_0056e4c4;
      local_10c[0] = param_7[6] * _DAT_0056e4c4;
      local_d8[0] = param_8[6] * _DAT_0056e4c4;
      local_88[1] = param_6[7] * _DAT_0056e4c4;
      local_10c[1] = param_7[7] * _DAT_0056e4c4;
      local_d8[1] = param_8[7] * _DAT_0056e4c4;
    }
    if ((uVar19 & 0x60) != 0) {
      local_88[6] = (float)((uint)param_6[4] & 0xff0000) * _DAT_0056e4d4;
      local_10c[6] = (float)((uint)param_7[4] & 0xff0000) * _DAT_0056e4d4;
      local_d8[6] = (float)((uint)param_8[4] & 0xff0000) * _DAT_0056e4d4;
      local_88[5] = (float)((uint)param_6[4] & 0xff00) * _DAT_0056e118;
      uStack_b4 = 0;
      local_10c[5] = (float)((uint)param_7[4] & 0xff00) * _DAT_0056e118;
      local_b8 = (uint)param_8[4] & 0xff00;
      local_d8[5] = (float)local_b8 * _DAT_0056e118;
    }
    if ((uVar19 & 4) != 0) {
      local_88[2] = (float)((uint)param_6[4] & 0xff);
      uStack_b4 = 0;
      local_10c[2] = (float)((uint)param_7[4] & 0xff);
      local_b8 = (uint)param_8[4] & 0xff;
      local_d8[2] = (float)local_b8;
    }
    if ((uVar13 & 0x10) != 0 || uVar16 != 0) {
      local_88[4] = _DAT_0056e0c4 - (float)((uint)param_6[4] >> 0x18);
      uStack_b4 = 0;
      local_10c[4] = _DAT_0056e0c4 - (float)((uint)param_7[4] >> 0x18);
      local_b8 = (uint)param_8[4] >> 0x18;
      local_d8[4] = _DAT_0056e0c4 - (float)local_b8;
    }
    if (local_94 != 0) {
      local_88[3] = param_6[2] * _DAT_0056e1cc;
      local_10c[3] = param_7[2] * _DAT_0056e1cc;
      local_d8[3] = param_8[2] * _DAT_0056e1cc;
    }
    if (param_6[1] != param_8[1]) {
      fVar3 = (param_7[1] - param_6[1]) / (param_8[1] - param_6[1]);
      fVar20 = (*param_8 - *param_6) * fVar3 + *param_6;
      if (fVar20 != *param_7) {
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_60[iVar6] = (local_d8[iVar6] - local_88[iVar6]) * fVar3 + local_88[iVar6];
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        fVar3 = *param_7;
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_40[iVar6] =
                 (local_10c[iVar6] - afStack_60[iVar6]) * (_DAT_0056e008 / (fVar3 - fVar20));
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        fVar3 = param_8[1];
        fVar20 = param_6[1];
        local_9c = *param_6;
        local_a0 = *param_7;
        if (param_7[1] != param_6[1]) {
          local_144 = (ushort *)((*param_7 - *param_6) / (param_7[1] - param_6[1]));
        }
        if (param_8[1] != param_7[1]) {
          local_130 = (*param_8 - *param_7) / (param_8[1] - param_7[1]);
        }
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_60[iVar6] =
                 (local_d8[iVar6] - local_88[iVar6]) * (_DAT_0056e008 / (fVar3 - fVar20));
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        local_124 = __ftol();
        local_110 = __ftol();
        iVar6 = __ftol();
        if (iVar6 != local_124) {
          iVar7 = 0;
          fVar3 = (float)local_124 - (param_6[1] - _DAT_0056e158);
          do {
            if ((uVar19 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
              local_88[iVar7] = fVar3 * afStack_60[iVar7] + local_88[iVar7];
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 8);
          local_9c = fVar3 * (float)local_144 + local_9c + _DAT_0056e4d0;
          local_dc = param_2;
          local_a0 = ((float)local_110 - (param_7[1] - _DAT_0056e158)) * local_130 + local_a0 +
                     _DAT_0056e4d0;
          local_8c = iVar6;
          local_e8 = __ftol();
          local_68 = __ftol();
          local_12c = __ftol();
          local_ac = __ftol();
          iVar7 = 0;
          do {
            if ((uVar19 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
              fVar3 = (float)__ftol();
              local_10c[iVar7] = fVar3;
              fVar3 = (float)__ftol();
              local_d8[iVar7] = fVar3;
              uVar4 = __ftol();
              auStack_20[iVar7] = uVar4;
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 8);
          local_130 = (float)(param_1 + local_124 * param_4 * 2);
          if (local_94 != 0) {
            local_dc = param_2 + local_124 * param_5 * 2;
          }
          local_138 = 0;
          do {
            if (local_138 == 0) {
              local_ec = __ftol();
              local_148 = (ushort *)local_10c[0];
              local_144 = (ushort *)local_10c[1];
              fVar3 = local_10c[2];
              uVar19 = local_e8;
            }
            else {
              local_ec = __ftol();
              local_12c = local_ac;
              local_148 = (ushort *)local_10c[0];
              local_144 = (ushort *)local_10c[1];
              fVar3 = local_10c[2];
              uVar19 = local_e8;
              local_110 = iVar6;
            }
            for (; iVar6 = local_8c, local_10c[0] = (float)local_148,
                local_10c[1] = (float)local_144, local_10c[2] = fVar3, local_e8 = uVar19,
                local_8c = iVar6, local_124 < local_110; local_124 = local_124 + 1) {
              local_b8 = ((uVar19 & 0xffff0000) - uVar19) + 0xffff;
              uStack_b4 = 0;
              local_120 = (short *)0x0;
              do {
                if ((local_90 & 1 << ((byte)local_120 & 0x1f)) != 0) {
                  fVar3 = (float)__ftol();
                  local_10c[(int)local_120] = fVar3;
                  local_148 = (ushort *)local_10c[0];
                  fVar3 = local_10c[2];
                  local_144 = (ushort *)local_10c[1];
                }
                local_120 = (short *)((int)local_120 + 1);
              } while ((int)local_120 < 8);
              iVar7 = (int)uVar19 >> 0x10;
              iVar6 = local_ec >> 0x10;
              if (param_3 == 0) {
                switch(local_98) {
                case 0:
                  puVar9 = (ushort *)(local_dc + iVar7 * 2);
                  local_128 = iVar6 - iVar7;
                  iVar6 = (int)local_130 + iVar7 * 2;
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      iVar6 = iVar6 - (int)puVar9;
                      local_128 = -local_128;
                      fVar20 = local_10c[6];
                      fVar5 = local_10c[3];
                      fVar22 = local_10c[5];
                      do {
                        puVar9 = puVar9 + -1;
                        fVar22 = (float)((int)fVar22 - (int)local_d8[5]);
                        fVar5 = (float)((int)fVar5 - (int)local_d8[3]);
                        fVar20 = (float)((int)fVar20 - (int)local_d8[6]);
                        fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                        if (((int)fVar5 >> 0x10 & 0xffffU) <= (uint)*puVar9) {
                          *puVar9 = (ushort)((uint)fVar5 >> 0x10);
                          *(short *)(iVar6 + (int)puVar9) =
                               (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                  (uint)fVar22 & 0xf80000) >> 5 |
                                            (uint)fVar20 & 0xf80000) >> 9);
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    iVar6 = iVar6 - (int)puVar9;
                    fVar20 = local_10c[6];
                    fVar5 = local_10c[3];
                    fVar22 = local_10c[5];
                    do {
                      if (((int)fVar5 >> 0x10 & 0xffffU) <= (uint)*puVar9) {
                        local_118 = (ushort)((uint)fVar5 >> 0x10);
                        *puVar9 = local_118;
                        *(short *)((int)puVar9 + iVar6) =
                             (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                (uint)fVar22 & 0xf80000) >> 5 |
                                          (uint)fVar20 & 0xf80000) >> 9);
                      }
                      puVar9 = puVar9 + 1;
                      fVar20 = (float)((int)fVar20 + (int)local_d8[6]);
                      fVar22 = (float)((int)fVar22 + (int)local_d8[5]);
                      fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                      fVar5 = (float)((int)fVar5 + (int)local_d8[3]);
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                  break;
                case 8:
                  local_148 = (ushort *)local_10c[3];
                  local_128 = iVar6 - iVar7;
                  iVar6 = local_dc + iVar7 * 2;
                  puVar10 = (undefined2 *)((int)local_130 + iVar7 * 2);
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      local_128 = -local_128;
                      fVar20 = local_10c[6];
                      fVar5 = local_10c[5];
                      puVar15 = puVar10 + -1;
                      do {
                        fVar20 = (float)((int)fVar20 - (int)local_d8[6]);
                        fVar5 = (float)((int)fVar5 - (int)local_d8[5]);
                        fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                        local_148 = (ushort *)((int)local_148 - (int)local_d8[3]);
                        *(short *)((iVar6 - (int)puVar10) + 2 + (int)(puVar15 + -1)) =
                             (short)((uint)local_148 >> 0x10);
                        *puVar15 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                      (uint)fVar5 & 0xf80000) >> 5 |
                                                (uint)fVar20 & 0xf80000) >> 9);
                        local_128 = local_128 + -1;
                        puVar15 = puVar15 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    fVar20 = local_10c[6];
                    fVar5 = local_10c[5];
                    puVar15 = puVar10;
                    do {
                      *(short *)((int)puVar15 + (iVar6 - (int)puVar10)) =
                           (short)((uint)local_148 >> 0x10);
                      *puVar15 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                    (uint)fVar5 & 0xf80000) >> 5 |
                                              (uint)fVar20 & 0xf80000) >> 9);
                      fVar20 = (float)((int)fVar20 + (int)local_d8[6]);
                      fVar5 = (float)((int)fVar5 + (int)local_d8[5]);
                      fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                      local_148 = (ushort *)((int)local_148 + (int)local_d8[3]);
                      local_128 = local_128 - 1;
                      puVar15 = puVar15 + 1;
                    } while (local_128 != 0);
                  }
                  break;
                case 0x10:
                  iVar8 = local_dc + iVar7 * 2;
                  local_128 = iVar6 - iVar7;
                  puVar10 = (undefined2 *)((int)local_130 + iVar7 * 2);
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      iVar8 = iVar8 - (int)puVar10;
                      local_128 = -local_128;
                      fVar20 = local_10c[6];
                      fVar5 = local_10c[3];
                      fVar22 = local_10c[5];
                      do {
                        puVar10 = puVar10 + -1;
                        fVar20 = (float)((int)fVar20 - (int)local_d8[6]);
                        fVar22 = (float)((int)fVar22 - (int)local_d8[5]);
                        fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                        fVar5 = (float)((int)fVar5 - (int)local_d8[3]);
                        if (((int)fVar5 >> 0x10 & 0xffffU) <=
                            (uint)*(ushort *)((int)puVar10 + iVar8)) {
                          *puVar10 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                        (uint)fVar22 & 0xf80000) >> 5 |
                                                  (uint)fVar20 & 0xf80000) >> 9);
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    iVar8 = iVar8 - (int)puVar10;
                    fVar20 = local_10c[6];
                    fVar5 = local_10c[3];
                    fVar22 = local_10c[5];
                    do {
                      if (((int)fVar5 >> 0x10 & 0xffffU) <= (uint)*(ushort *)((int)puVar10 + iVar8))
                      {
                        *puVar10 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                      (uint)fVar22 & 0xf80000) >> 5 |
                                                (uint)fVar20 & 0xf80000) >> 9);
                      }
                      puVar10 = puVar10 + 1;
                      fVar20 = (float)((int)fVar20 + (int)local_d8[6]);
                      fVar22 = (float)((int)fVar22 + (int)local_d8[5]);
                      fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                      fVar5 = (float)((int)fVar5 + (int)local_d8[3]);
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                  break;
                case 0x18:
                  local_e0 = local_d8[2];
                  local_128 = iVar6 - iVar7;
                  puVar10 = (undefined2 *)((int)local_130 + iVar7 * 2);
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      iVar6 = -local_128;
                      fVar20 = local_10c[6];
                      fVar5 = local_10c[5];
                      do {
                        puVar10 = puVar10 + -1;
                        fVar20 = (float)((int)fVar20 - (int)local_d8[6]);
                        fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                        fVar5 = (float)((int)fVar5 - (int)local_d8[5]);
                        *puVar10 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                      (uint)fVar5 & 0xf80000) >> 5 |
                                                (uint)fVar20 & 0xf80000) >> 9);
                        iVar6 = iVar6 + -1;
                      } while (iVar6 != 0);
                    }
                  }
                  else {
                    fVar20 = local_10c[6];
                    fVar5 = local_10c[5];
                    if (0 < (int)local_128) {
                      do {
                        *puVar10 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                      (uint)fVar5 & 0xf80000) >> 5 |
                                                (uint)fVar20 & 0xf80000) >> 9);
                        fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                        local_128 = local_128 - 1;
                        fVar20 = (float)((int)fVar20 + (int)local_d8[6]);
                        fVar5 = (float)((int)fVar5 + (int)local_d8[5]);
                        puVar10 = puVar10 + 1;
                      } while (local_128 != 0);
                    }
                  }
                }
              }
              else if (local_64 == 0) {
                if (local_98 == 0x18) {
                  local_128 = iVar6 - iVar7;
                  local_120 = (short *)((int)local_130 + iVar7 * 2);
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      local_128 = -local_128;
                      do {
                        local_120 = local_120 + -1;
                        local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                        local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                        sVar2 = *(short *)(param_3 +
                                          ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                (uint)local_144 & 0xff0000) >> 8) * 2);
                        if (((param_9 & 4) == 0) || (sVar2 != 0)) {
                          *local_120 = sVar2;
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    do {
                      sVar2 = *(short *)(param_3 +
                                        ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                              (uint)local_144 & 0xff0000) >> 8) * 2);
                      if (((param_9 & 4) == 0) || (sVar2 != 0)) {
                        *local_120 = sVar2;
                      }
                      local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                      local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                      local_120 = local_120 + 1;
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                }
                else {
                  local_13c = local_10c[3];
                  local_e0 = local_d8[1];
                  local_128 = iVar6 - iVar7;
                  puVar9 = (ushort *)(local_dc + iVar7 * 2);
                  iVar6 = (int)local_130 + iVar7 * 2;
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      local_b0 = iVar6 - (int)puVar9;
                      local_128 = -local_128;
                      do {
                        puVar9 = puVar9 + -1;
                        local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                        local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                        if ((uVar11 & 3) != 3) {
                          local_13c = (float)((int)local_13c - (int)local_d8[3]);
                        }
                        if ((((uVar11 & 1) != 0) ||
                            (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*puVar9)) &&
                           ((sVar2 = *(short *)(param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)local_144 & 0xff0000) >> 8) * 2),
                            (param_9 & 4) == 0 || (sVar2 != 0)))) {
                          if ((uVar11 & 2) == 0) {
                            *puVar9 = (ushort)((uint)local_13c >> 0x10);
                          }
                          *(short *)(local_b0 + (int)puVar9) = sVar2;
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    local_b0 = iVar6 - (int)puVar9;
                    do {
                      if ((((uVar11 & 1) != 0) ||
                          (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*puVar9)) &&
                         ((sVar2 = *(short *)(param_3 +
                                             ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                   (uint)local_144 & 0xff0000) >> 8) * 2),
                          (param_9 & 4) == 0 || (sVar2 != 0)))) {
                        if ((uVar11 & 2) == 0) {
                          *puVar9 = (ushort)((uint)local_13c >> 0x10);
                        }
                        *(short *)(local_b0 + (int)puVar9) = sVar2;
                      }
                      local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                      local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                      if ((uVar11 & 3) != 3) {
                        local_13c = (float)((int)local_13c + (int)local_d8[3]);
                      }
                      puVar9 = puVar9 + 1;
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                }
              }
              else {
                iVar8 = (int)local_10c[6] >> 0x13;
                iVar12 = (int)local_10c[5] >> 0x13;
                if (local_98 == 0) {
                  if ((param_9 & 0x102) == 0x102) {
                    local_144 = (ushort *)local_10c[1];
                    local_148 = (ushort *)local_10c[0];
                    iVar7 = (int)local_e8 >> 0x10;
                    local_140 = (ushort *)local_10c[3];
                    puVar9 = (ushort *)(local_dc + iVar7 * 2);
                    local_128 = iVar6 - iVar7;
                    iVar6 = (int)local_130 + iVar7 * 2;
                    local_e0 = (float)(param_9 & 4);
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_b0 = iVar6 - (int)puVar9;
                        local_128 = -local_128;
                        do {
                          puVar9 = puVar9 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                          local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                          local_140 = (ushort *)((int)local_140 - (int)local_d8[3]);
                          if (((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar9) {
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                           (uint)local_144 & 0xff0000) >> 8) * 2);
                            uVar19 = (uint)uVar1;
                            if ((local_e0 == 0.0) || (uVar19 != 0)) {
                              local_120._0_2_ = (ushort)((uint)local_140 >> 0x10);
                              *puVar9 = (ushort)local_120;
                              *(short *)(local_b0 + (int)puVar9) =
                                   (short)(((uVar19 & 0x1f) * ((int)local_10c[2] >> 0x13) & 0x3e0 |
                                            (uVar19 & 0x3e0) * iVar12 & 0x7c00 |
                                           (uVar1 & 0x7c00) * iVar8 & 0xf8000) >> 5);
                            }
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      local_b0 = iVar6 - (int)puVar9;
                      do {
                        if (((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar9) {
                          uVar1 = *(ushort *)
                                   (param_3 +
                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                         (uint)local_144 & 0xff0000) >> 8) * 2);
                          uVar19 = (uint)uVar1;
                          if ((local_e0 == 0.0) || (uVar19 != 0)) {
                            local_120._0_2_ = (ushort)((uint)local_140 >> 0x10);
                            *puVar9 = (ushort)local_120;
                            *(short *)(local_b0 + (int)puVar9) =
                                 (short)(((uVar19 & 0x1f) * ((int)local_10c[2] >> 0x13) & 0x3e0 |
                                          (uVar19 & 0x3e0) * iVar12 & 0x7c00 |
                                         (uVar1 & 0x7c00) * iVar8 & 0xf8000) >> 5);
                          }
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                        local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                        puVar9 = puVar9 + 1;
                        local_140 = (ushort *)((int)local_140 + (int)local_d8[3]);
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                  else {
                    local_a4 = param_9 & 4;
                    local_140 = (ushort *)local_10c[3];
                    local_e0 = local_d8[1];
                    local_e4 = local_d8[3];
                    local_128 = iVar6 - iVar7;
                    puVar9 = (ushort *)(local_dc + iVar7 * 2);
                    iVar6 = (int)local_130 + iVar7 * 2;
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        iVar6 = iVar6 - (int)puVar9;
                        local_128 = -local_128;
                        do {
                          puVar9 = puVar9 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                          local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                          local_140 = (ushort *)((int)local_140 - (int)local_d8[3]);
                          fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                          if ((((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar9) &&
                             ((uVar19 = (uint)*(ushort *)
                                               (param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)local_144 & 0xff0000) >> 8) * 2),
                              local_a4 == 0 || (uVar19 != 0)))) {
                            *puVar9 = (ushort)((uint)local_140 >> 0x10);
                            uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                     ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                            *(short *)(iVar6 + (int)puVar9) =
                                 (short)((uVar19 >> 0x10 | uVar19) >> 5);
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      iVar6 = iVar6 - (int)puVar9;
                      do {
                        if ((((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar9) &&
                           ((uVar19 = (uint)*(ushort *)
                                             (param_3 +
                                             ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                   (uint)local_144 & 0xff0000) >> 8) * 2),
                            local_a4 == 0 || (uVar19 != 0)))) {
                          *puVar9 = (ushort)((uint)local_140 >> 0x10);
                          uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                   ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                          *(short *)(iVar6 + (int)puVar9) = (short)((uVar19 >> 0x10 | uVar19) >> 5);
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                        fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                        local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                        local_140 = (ushort *)((int)local_140 + (int)local_d8[3]);
                        puVar9 = puVar9 + 1;
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                }
                else if ((param_9 & 0x102) == 0x102) {
                  local_a4 = param_9 & 4;
                  local_13c = local_10c[3];
                  local_e0 = local_d8[1];
                  local_140 = (ushort *)(local_dc + iVar7 * 2);
                  local_128 = iVar6 - iVar7;
                  iVar6 = (int)local_130 + iVar7 * 2;
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      local_b0 = uVar11 & 1;
                      iVar6 = iVar6 - (int)local_140;
                      local_128 = -local_128;
                      do {
                        local_140 = local_140 + -1;
                        local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                        local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                        if ((uVar11 & 3) != 3) {
                          local_13c = (float)((int)local_13c - (int)local_d8[3]);
                        }
                        if ((local_b0 != 0) ||
                           (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*local_140)) {
                          uVar1 = *(ushort *)
                                   (param_3 +
                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                         (uint)local_144 & 0xff0000) >> 8) * 2);
                          uVar19 = (uint)uVar1;
                          if ((local_a4 == 0) || (uVar19 != 0)) {
                            if ((uVar11 & 2) == 0) {
                              *local_140 = (ushort)((uint)local_13c >> 0x10);
                            }
                            *(short *)(iVar6 + (int)local_140) =
                                 (short)(((uVar19 & 0x1f) * ((int)fVar3 >> 0x13) & 0x3e0 |
                                          (uVar19 & 0x3e0) * iVar12 & 0x7c00 |
                                         (uVar1 & 0x7c00) * iVar8 & 0xf8000) >> 5);
                          }
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    local_b0 = uVar11 & 1;
                    iVar6 = iVar6 - (int)local_140;
                    do {
                      if ((local_b0 != 0) ||
                         (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*local_140)) {
                        uVar1 = *(ushort *)
                                 (param_3 +
                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                       (uint)local_144 & 0xff0000) >> 8) * 2);
                        uVar19 = (uint)uVar1;
                        if ((local_a4 == 0) || (uVar19 != 0)) {
                          if ((uVar11 & 2) == 0) {
                            *local_140 = (ushort)((uint)local_13c >> 0x10);
                          }
                          *(short *)((int)local_140 + iVar6) =
                               (short)(((uVar19 & 0x1f) * ((int)fVar3 >> 0x13) & 0x3e0 |
                                        (uVar19 & 0x3e0) * iVar12 & 0x7c00 |
                                       (uVar1 & 0x7c00) * iVar8 & 0xf8000) >> 5);
                        }
                      }
                      local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                      local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                      if ((uVar11 & 3) != 3) {
                        local_13c = (float)((int)local_13c + (int)local_d8[3]);
                      }
                      local_140 = local_140 + 1;
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                }
                else {
                  local_a4 = param_9 & 4;
                  local_e4 = local_d8[3];
                  local_13c = local_10c[3];
                  local_e0 = local_d8[1];
                  local_128 = iVar6 - iVar7;
                  puVar9 = (ushort *)(local_dc + iVar7 * 2);
                  iVar6 = (int)local_130 + iVar7 * 2;
                  if ((int)local_128 < 0) {
                    if (0x7fffffff < local_128) {
                      local_b0 = iVar6 - (int)puVar9;
                      local_128 = -local_128;
                      do {
                        puVar9 = puVar9 + -1;
                        local_148 = (ushort *)((int)local_148 - (int)local_d8[0]);
                        local_144 = (ushort *)((int)local_144 - (int)local_d8[1]);
                        fVar3 = (float)((int)fVar3 - (int)local_d8[2]);
                        if ((uVar11 & 3) != 3) {
                          local_13c = (float)((int)local_13c - (int)local_d8[3]);
                        }
                        if ((((uVar11 & 1) != 0) ||
                            (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*puVar9)) &&
                           ((uVar19 = (uint)*(ushort *)
                                             (param_3 +
                                             ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                   (uint)local_144 & 0xff0000) >> 8) * 2),
                            local_a4 == 0 || (uVar19 != 0)))) {
                          uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                   ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                          if ((uVar11 & 2) == 0) {
                            *puVar9 = (ushort)((uint)local_13c >> 0x10);
                          }
                          *(short *)(local_b0 + (int)puVar9) =
                               (short)((uVar19 >> 0x10 | uVar19) >> 5);
                        }
                        local_128 = local_128 + -1;
                      } while (local_128 != 0);
                    }
                  }
                  else if (0 < (int)local_128) {
                    local_b0 = iVar6 - (int)puVar9;
                    do {
                      if ((((uVar11 & 1) != 0) ||
                          (((int)local_13c >> 0x10 & 0xffffU) <= (uint)*puVar9)) &&
                         ((uVar19 = (uint)*(ushort *)
                                           (param_3 +
                                           ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                 (uint)local_144 & 0xff0000) >> 8) * 2),
                          local_a4 == 0 || (uVar19 != 0)))) {
                        uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                 ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                        if ((uVar11 & 2) == 0) {
                          *puVar9 = (ushort)((uint)local_13c >> 0x10);
                        }
                        *(short *)(local_b0 + (int)puVar9) = (short)((uVar19 >> 0x10 | uVar19) >> 5)
                        ;
                      }
                      local_148 = (ushort *)((int)local_148 + (int)local_d8[0]);
                      local_144 = (ushort *)((int)local_144 + (int)local_d8[1]);
                      fVar3 = (float)((int)fVar3 + (int)local_d8[2]);
                      if ((uVar11 & 3) != 3) {
                        local_13c = (float)((int)local_13c + (int)local_d8[3]);
                      }
                      puVar9 = puVar9 + 1;
                      local_128 = local_128 - 1;
                    } while (local_128 != 0);
                  }
                }
              }
              local_ec = local_ec + local_12c;
              iVar6 = 0;
              do {
                if ((local_90 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
                  local_88[iVar6] = afStack_60[iVar6] + local_88[iVar6];
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < 8);
              local_130 = (float)((int)local_130 + param_4 * 2);
              if (local_94 != 0) {
                local_dc = local_dc + param_5 * 2;
              }
              local_148 = (ushort *)local_10c[0];
              local_144 = (ushort *)local_10c[1];
              fVar3 = local_10c[2];
              uVar19 = local_e8 + local_68;
            }
            local_138 = local_138 + 1;
          } while ((int)local_138 < 2);
          return;
        }
      }
    }
  }
  else {
    if (uVar21 != 0) {
      local_88[0] = param_6[6] * _DAT_0056e4c4;
      local_10c[0] = param_7[6] * _DAT_0056e4c4;
      local_d8[0] = param_8[6] * _DAT_0056e4c4;
      local_88[1] = param_6[7] * _DAT_0056e4c4;
      local_10c[1] = param_7[7] * _DAT_0056e4c4;
      local_d8[1] = param_8[7] * _DAT_0056e4c4;
    }
    if ((uVar19 & 0x60) != 0) {
      local_88[6] = (float)((uint)param_6[4] & 0xff0000) * _DAT_0056e4d4;
      local_10c[6] = (float)((uint)param_7[4] & 0xff0000) * _DAT_0056e4d4;
      local_d8[6] = (float)((uint)param_8[4] & 0xff0000) * _DAT_0056e4d4;
      local_88[5] = (float)((uint)param_6[4] & 0xff00) * _DAT_0056e118;
      uStack_a8 = 0;
      local_10c[5] = (float)((uint)param_7[4] & 0xff00) * _DAT_0056e118;
      local_ac = (uint)param_8[4] & 0xff00;
      local_d8[5] = (float)local_ac * _DAT_0056e118;
    }
    if ((uVar19 & 4) != 0) {
      local_88[2] = (float)((uint)param_6[4] & 0xff);
      uStack_a8 = 0;
      local_10c[2] = (float)((uint)param_7[4] & 0xff);
      local_ac = (uint)param_8[4] & 0xff;
      local_d8[2] = (float)local_ac;
    }
    if ((uVar13 & 0x10) != 0 || uVar16 != 0) {
      local_88[4] = _DAT_0056e0c4 - (float)((uint)param_6[4] >> 0x18);
      uStack_a8 = 0;
      local_10c[4] = _DAT_0056e0c4 - (float)((uint)param_7[4] >> 0x18);
      local_ac = (uint)param_8[4] >> 0x18;
      local_d8[4] = _DAT_0056e0c4 - (float)local_ac;
    }
    if (local_94 != 0) {
      local_88[3] = param_6[2] * _DAT_0056e1cc;
      local_10c[3] = param_7[2] * _DAT_0056e1cc;
      local_d8[3] = param_8[2] * _DAT_0056e1cc;
    }
    if (param_6[1] != param_8[1]) {
      fVar3 = (param_7[1] - param_6[1]) / (param_8[1] - param_6[1]);
      fVar20 = (*param_8 - *param_6) * fVar3 + *param_6;
      if (fVar20 != *param_7) {
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_60[iVar6] = (local_d8[iVar6] - local_88[iVar6]) * fVar3 + local_88[iVar6];
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        fVar3 = *param_7;
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_40[iVar6] =
                 (local_10c[iVar6] - afStack_60[iVar6]) * (_DAT_0056e008 / (fVar3 - fVar20));
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        fVar3 = param_8[1];
        fVar20 = param_6[1];
        local_9c = *param_6;
        local_a0 = *param_7;
        if (param_7[1] != param_6[1]) {
          local_144 = (ushort *)((*param_7 - *param_6) / (param_7[1] - param_6[1]));
        }
        if (param_8[1] != param_7[1]) {
          local_130 = (*param_8 - *param_7) / (param_8[1] - param_7[1]);
        }
        iVar6 = 0;
        do {
          if ((uVar19 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
            afStack_60[iVar6] =
                 (local_d8[iVar6] - local_88[iVar6]) * (_DAT_0056e008 / (fVar3 - fVar20));
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 8);
        iVar6 = __ftol();
        local_120 = (short *)__ftol();
        local_8c = __ftol();
        if (local_8c != iVar6) {
          iVar7 = 0;
          fVar3 = (float)iVar6 - (param_6[1] - _DAT_0056e158);
          do {
            if ((uVar19 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
              local_88[iVar7] = fVar3 * afStack_60[iVar7] + local_88[iVar7];
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 8);
          local_e8 = param_2;
          local_9c = fVar3 * (float)local_144 + local_9c + _DAT_0056e4d0;
          local_a0 = ((float)(int)local_120 - (param_7[1] - _DAT_0056e158)) * local_130 + local_a0 +
                     _DAT_0056e4d0;
          uVar13 = __ftol();
          local_dc = uVar13;
          local_ac = __ftol();
          local_a4 = __ftol();
          local_68 = __ftol();
          iVar7 = 0;
          do {
            if ((uVar19 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
              fVar3 = (float)__ftol();
              local_d8[iVar7] = fVar3;
              fVar3 = (float)__ftol();
              local_10c[iVar7] = fVar3;
              uVar4 = __ftol();
              auStack_20[iVar7] = uVar4;
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 8);
          if (local_94 != 0) {
            local_e8 = param_2 + iVar6 * param_5 * 2;
          }
          local_128 = 0;
          fVar3 = local_d8[0];
          fVar20 = local_d8[1];
          local_ec = param_1 + iVar6 * param_4 * 2;
          local_b0 = iVar6;
          do {
            if (local_128 == 0) {
              iVar6 = __ftol();
              iVar7 = local_ec;
              fVar5 = local_d8[3];
            }
            else {
              iVar6 = __ftol();
              local_120 = (short *)local_8c;
              iVar7 = local_ec;
              fVar5 = local_d8[3];
              local_a4 = local_68;
            }
            for (; local_ec = iVar7, local_d8[3] = fVar5, (int)local_b0 < (int)local_120;
                local_b0 = local_b0 + 1) {
              local_b8 = ((uVar13 & 0xffff0000) - uVar13) + 0xffff;
              uStack_b4 = 0;
              local_140 = (ushort *)0x0;
              do {
                if ((local_90 & 1 << ((byte)local_140 & 0x1f)) != 0) {
                  fVar3 = (float)__ftol();
                  local_d8[(int)local_140] = fVar3;
                  fVar5 = local_d8[3];
                  fVar3 = local_d8[0];
                  fVar20 = local_d8[1];
                }
                local_140 = (ushort *)((int)local_140 + 1);
              } while ((int)local_140 < 8);
              iVar8 = iVar6 >> 0x10;
              if (param_3 == 0) {
                if (local_98 < 0x19) {
                  iVar7 = (int)local_dc >> 0x10;
                  switch(local_98) {
                  case 0:
                    if ((param_9 & 0x80) == 0) {
                      local_13c = local_d8[4];
                      local_144 = (ushort *)local_d8[3];
                      local_134 = local_d8[2];
                      local_138 = iVar8 - iVar7;
                      iVar8 = local_e8 + iVar7 * 2;
                      puVar9 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          local_138 = -local_138;
                          fVar3 = local_d8[6];
                          fVar20 = local_d8[5];
                          do {
                            puVar9 = puVar9 + -1;
                            fVar20 = (float)((int)fVar20 - (int)local_10c[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[6]);
                            local_134 = (float)((int)local_134 - (int)local_10c[2]);
                            local_144 = (ushort *)((int)local_144 - (int)local_10c[3]);
                            local_13c = (float)((int)local_13c - (int)local_10c[4]);
                            if (((int)local_144 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar8 + (int)puVar9)) {
                              uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                       ((int)local_13c >> 0x13) & 0x7c0f83e0;
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_144 >> 0x10);
                              *puVar9 = (short)((int)((int)((int)local_134 >> 5 & 0x7c000U |
                                                           (uint)fVar20 & 0xf80000) >> 5 |
                                                     (uint)fVar3 & 0xf80000) >> 9) +
                                        (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)puVar9;
                        fVar3 = local_d8[6];
                        fVar20 = local_d8[5];
                        fVar5 = local_d8[3];
                        do {
                          if (((int)fVar5 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)puVar9 + iVar8)) {
                            uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                     ((int)local_13c >> 0x13) & 0x7c0f83e0;
                            *(short *)((int)puVar9 + iVar8) = (short)((uint)fVar5 >> 0x10);
                            *puVar9 = (short)((int)((int)((int)local_134 >> 5 & 0x7c000U |
                                                         (uint)fVar20 & 0xf80000) >> 5 |
                                                   (uint)fVar3 & 0xf80000) >> 9) +
                                      (short)((uVar19 >> 0x10 | uVar19) >> 5);
                          }
                          fVar20 = (float)((int)fVar20 + (int)local_10c[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[6]);
                          local_134 = (float)((int)local_134 + (int)local_10c[2]);
                          puVar9 = puVar9 + 1;
                          fVar5 = (float)((int)fVar5 + (int)local_10c[3]);
                          local_13c = (float)((int)local_13c + (int)local_10c[4]);
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                    else {
                      local_134 = local_d8[2];
                      local_13c = local_d8[5];
                      local_138 = iVar8 - iVar7;
                      iVar8 = local_e8 + iVar7 * 2;
                      local_144 = (ushort *)local_d8[3];
                      puVar9 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          local_138 = -local_138;
                          fVar3 = local_d8[6];
                          fVar20 = local_d8[3];
                          do {
                            puVar9 = puVar9 + -1;
                            local_13c = (float)((int)local_13c - (int)local_10c[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[6]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[3]);
                            local_134 = (float)((int)local_134 - (int)local_10c[2]);
                            if (((int)fVar20 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar8 + (int)puVar9)) {
                              uVar13 = (int)((int)((int)local_134 >> 5 & 0x7c000U |
                                                  (uint)local_13c & 0xf80000) >> 5 |
                                            (uint)fVar3 & 0xf80000) >> 9;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)fVar20 >> 0x10);
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)puVar9;
                        fVar3 = local_d8[6];
                        do {
                          if (((int)local_144 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)puVar9 + iVar8)) {
                            uVar13 = (int)((int)((int)local_134 >> 5 & 0x7c000U |
                                                (uint)local_13c & 0xf80000) >> 5 |
                                          (uint)fVar3 & 0xf80000) >> 9;
                            uVar19 = *puVar9 + uVar13;
                            uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *(short *)((int)puVar9 + iVar8) = (short)((uint)local_144 >> 0x10);
                            *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          }
                          fVar3 = (float)((int)fVar3 + (int)local_10c[6]);
                          local_13c = (float)((int)local_13c + (int)local_10c[5]);
                          local_144 = (ushort *)((int)local_144 + (int)local_10c[3]);
                          local_134 = (float)((int)local_134 + (int)local_10c[2]);
                          puVar9 = puVar9 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                    break;
                  case 8:
                    if ((param_9 & 0x80) == 0) {
                      local_13c = local_d8[4];
                      local_134 = local_d8[3];
                      local_138 = iVar8 - iVar7;
                      iVar8 = local_e8 + iVar7 * 2;
                      puVar9 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          local_138 = -local_138;
                          fVar3 = local_d8[2];
                          puVar17 = puVar9 + -1;
                          fVar20 = local_d8[6];
                          fVar5 = local_d8[5];
                          do {
                            fVar20 = (float)((int)fVar20 - (int)local_10c[6]);
                            fVar5 = (float)((int)fVar5 - (int)local_10c[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                            local_134 = (float)((int)local_134 - (int)local_10c[3]);
                            local_13c = (float)((int)local_13c - (int)local_10c[4]);
                            uVar19 = ((*puVar17 & 0x3e0) << 0x10 | *puVar17 & 0x3e07c1f) *
                                     ((int)local_13c >> 0x13) & 0x7c0f83e0;
                            *(short *)((iVar8 - (int)puVar9) + 2 + (int)(puVar17 + -1)) =
                                 (short)((uint)local_134 >> 0x10);
                            *puVar17 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                          (uint)fVar5 & 0xf80000) >> 5 |
                                                    (uint)fVar20 & 0xf80000) >> 9) +
                                       (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            local_138 = local_138 + -1;
                            puVar17 = puVar17 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        fVar3 = local_d8[2];
                        puVar17 = puVar9;
                        fVar20 = local_d8[6];
                        fVar5 = local_d8[5];
                        do {
                          uVar19 = ((*puVar17 & 0x3e0) << 0x10 | *puVar17 & 0x3e07c1f) *
                                   ((int)local_13c >> 0x13) & 0x7c0f83e0;
                          *(short *)((iVar8 - (int)puVar9) + -2 + (int)(puVar17 + 1)) =
                               (short)((uint)local_134 >> 0x10);
                          *puVar17 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                        (uint)fVar5 & 0xf80000) >> 5 |
                                                  (uint)fVar20 & 0xf80000) >> 9) +
                                     (short)((uVar19 >> 0x10 | uVar19) >> 5);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[6]);
                          fVar5 = (float)((int)fVar5 + (int)local_10c[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                          local_134 = (float)((int)local_134 + (int)local_10c[3]);
                          local_13c = (float)((int)local_13c + (int)local_10c[4]);
                          local_138 = local_138 - 1;
                          puVar17 = puVar17 + 1;
                        } while (local_138 != 0);
                      }
                    }
                    else {
                      local_134 = local_d8[3];
                      local_138 = iVar8 - iVar7;
                      iVar8 = local_e8 + iVar7 * 2;
                      local_140 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)local_140;
                          local_138 = -local_138;
                          fVar3 = local_d8[5];
                          fVar20 = local_d8[2];
                          fVar5 = local_d8[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar20 = (float)((int)fVar20 - (int)local_10c[2]);
                            local_134 = (float)((int)local_134 - (int)local_10c[3]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[5]);
                            fVar5 = (float)((int)fVar5 - (int)local_10c[6]);
                            uVar13 = (int)((int)((int)fVar20 >> 5 & 0x7c000U |
                                                (uint)fVar3 & 0xf80000) >> 5 |
                                          (uint)fVar5 & 0xf80000) >> 9;
                            uVar19 = *local_140 + uVar13;
                            uVar13 = (uVar19 ^ *local_140 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *(short *)(iVar8 + (int)local_140) = (short)((uint)local_134 >> 0x10);
                            *local_140 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)local_140;
                        fVar3 = local_d8[5];
                        fVar20 = local_d8[2];
                        fVar5 = local_d8[6];
                        do {
                          uVar13 = (int)((int)((int)fVar20 >> 5 & 0x7c000U | (uint)fVar3 & 0xf80000)
                                         >> 5 | (uint)fVar5 & 0xf80000) >> 9;
                          uVar19 = *local_140 + uVar13;
                          uVar13 = (uVar19 ^ *local_140 ^ uVar13) & 0x8420;
                          sVar2 = (short)uVar13;
                          *(short *)((int)local_140 + iVar8) = (short)((uint)local_134 >> 0x10);
                          *local_140 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          fVar5 = (float)((int)fVar5 + (int)local_10c[6]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[2]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[5]);
                          local_134 = (float)((int)local_134 + (int)local_10c[3]);
                          local_140 = local_140 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                    break;
                  case 0x10:
                    if ((param_9 & 0x80) == 0) {
                      local_134 = local_d8[3];
                      iVar12 = local_e8 + iVar7 * 2;
                      local_138 = iVar8 - iVar7;
                      local_148 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar12 = iVar12 - (int)local_148;
                          local_138 = -local_138;
                          fVar3 = local_d8[2];
                          fVar20 = local_d8[4];
                          fVar5 = local_d8[6];
                          fVar22 = local_d8[5];
                          do {
                            local_148 = local_148 + -1;
                            fVar5 = (float)((int)fVar5 - (int)local_10c[6]);
                            fVar22 = (float)((int)fVar22 - (int)local_10c[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                            local_134 = (float)((int)local_134 - (int)local_10c[3]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[4]);
                            if (((int)local_134 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar12 + (int)local_148)) {
                              uVar19 = ((*local_148 & 0x3e0) << 0x10 | *local_148 & 0x3e07c1f) *
                                       ((int)fVar20 >> 0x13) & 0x7c0f83e0;
                              *local_148 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                              (uint)fVar22 & 0xf80000) >> 5 |
                                                        (uint)fVar5 & 0xf80000) >> 9) +
                                           (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar12 = iVar12 - (int)local_148;
                        fVar3 = local_d8[2];
                        fVar20 = local_d8[4];
                        fVar5 = local_d8[6];
                        fVar22 = local_d8[5];
                        do {
                          if (((int)local_134 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)local_148 + iVar12)) {
                            uVar19 = ((*local_148 & 0x3e0) << 0x10 | *local_148 & 0x3e07c1f) *
                                     ((int)fVar20 >> 0x13) & 0x7c0f83e0;
                            *local_148 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                            (uint)fVar22 & 0xf80000) >> 5 |
                                                      (uint)fVar5 & 0xf80000) >> 9) +
                                         (short)((uVar19 >> 0x10 | uVar19) >> 5);
                          }
                          fVar5 = (float)((int)fVar5 + (int)local_10c[6]);
                          fVar22 = (float)((int)fVar22 + (int)local_10c[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                          local_134 = (float)((int)local_134 + (int)local_10c[3]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[4]);
                          local_148 = local_148 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                    else {
                      local_134 = local_d8[3];
                      local_138 = iVar8 - iVar7;
                      iVar8 = local_e8 + iVar7 * 2;
                      local_148 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)local_148;
                          local_138 = -local_138;
                          fVar3 = local_d8[3];
                          fVar20 = local_d8[5];
                          fVar5 = local_d8[2];
                          fVar22 = local_d8[6];
                          do {
                            local_148 = local_148 + -1;
                            fVar22 = (float)((int)fVar22 - (int)local_10c[6]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[5]);
                            fVar5 = (float)((int)fVar5 - (int)local_10c[2]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[3]);
                            if (((int)fVar3 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar8 + (int)local_148)) {
                              uVar13 = (int)((int)((int)fVar5 >> 5 & 0x7c000U |
                                                  (uint)fVar20 & 0xf80000) >> 5 |
                                            (uint)fVar22 & 0xf80000) >> 9;
                              uVar19 = *local_148 + uVar13;
                              uVar13 = (uVar19 ^ *local_148 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *local_148 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)local_148;
                        fVar3 = local_d8[5];
                        fVar20 = local_d8[2];
                        fVar5 = local_d8[6];
                        do {
                          if (((int)local_134 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)local_148 + iVar8)) {
                            uVar13 = (int)((int)((int)fVar20 >> 5 & 0x7c000U |
                                                (uint)fVar3 & 0xf80000) >> 5 |
                                          (uint)fVar5 & 0xf80000) >> 9;
                            uVar19 = *local_148 + uVar13;
                            uVar13 = (uVar19 ^ *local_148 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *local_148 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          }
                          fVar5 = (float)((int)fVar5 + (int)local_10c[6]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[2]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[5]);
                          local_134 = (float)((int)local_134 + (int)local_10c[3]);
                          local_148 = local_148 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                    break;
                  case 0x18:
                    if ((param_9 & 0x80) == 0) {
                      local_138 = iVar8 - iVar7;
                      local_140 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          local_138 = -local_138;
                          fVar3 = local_d8[2];
                          fVar20 = local_d8[5];
                          fVar5 = local_d8[4];
                          fVar22 = local_d8[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar22 = (float)((int)fVar22 - (int)local_10c[6]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                            fVar5 = (float)((int)fVar5 - (int)local_10c[4]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[5]);
                            uVar19 = ((*local_140 & 0x3e0) << 0x10 | *local_140 & 0x3e07c1f) *
                                     ((int)fVar5 >> 0x13) & 0x7c0f83e0;
                            *local_140 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                            (uint)fVar20 & 0xf80000) >> 5 |
                                                      (uint)fVar22 & 0xf80000) >> 9) +
                                         (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else {
                        fVar3 = local_d8[2];
                        fVar20 = local_d8[5];
                        fVar5 = local_d8[4];
                        fVar22 = local_d8[6];
                        if (0 < (int)local_138) {
                          do {
                            uVar19 = ((*local_140 & 0x3e0) << 0x10 | *local_140 & 0x3e07c1f) *
                                     ((int)fVar5 >> 0x13) & 0x7c0f83e0;
                            *local_140 = (short)((int)((int)((int)fVar3 >> 5 & 0x7c000U |
                                                            (uint)fVar20 & 0xf80000) >> 5 |
                                                      (uint)fVar22 & 0xf80000) >> 9) +
                                         (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            local_140 = local_140 + 1;
                            local_138 = local_138 - 1;
                            fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                            fVar20 = (float)((int)fVar20 + (int)local_10c[5]);
                            fVar5 = (float)((int)fVar5 + (int)local_10c[4]);
                            fVar22 = (float)((int)fVar22 + (int)local_10c[6]);
                          } while (local_138 != 0);
                        }
                      }
                    }
                    else {
                      local_138 = iVar8 - iVar7;
                      local_140 = (ushort *)(local_ec + iVar7 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          local_138 = -local_138;
                          fVar3 = local_d8[5];
                          fVar20 = local_d8[2];
                          fVar5 = local_d8[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar20 = (float)((int)fVar20 - (int)local_10c[2]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[5]);
                            fVar5 = (float)((int)fVar5 - (int)local_10c[6]);
                            uVar13 = (int)((int)((int)fVar20 >> 5 & 0x7c000U |
                                                (uint)fVar3 & 0xf80000) >> 5 |
                                          (uint)fVar5 & 0xf80000) >> 9;
                            uVar19 = *local_140 + uVar13;
                            uVar13 = (uVar19 ^ *local_140 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *local_140 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else {
                        fVar3 = local_d8[5];
                        fVar20 = local_d8[2];
                        fVar5 = local_d8[6];
                        if (0 < (int)local_138) {
                          do {
                            uVar13 = (int)((int)((int)fVar20 >> 5 & 0x7c000U |
                                                (uint)fVar3 & 0xf80000) >> 5 |
                                          (uint)fVar5 & 0xf80000) >> 9;
                            uVar19 = *local_140 + uVar13;
                            uVar13 = (uVar19 ^ *local_140 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *local_140 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            local_140 = local_140 + 1;
                            local_138 = local_138 - 1;
                            fVar3 = (float)((int)fVar3 + (int)local_10c[5]);
                            fVar20 = (float)((int)fVar20 + (int)local_10c[2]);
                            fVar5 = (float)((int)fVar5 + (int)local_10c[6]);
                          } while (local_138 != 0);
                        }
                      }
                    }
                  }
                }
              }
              else {
                iVar12 = (int)uVar13 >> 0x10;
                local_148 = (ushort *)fVar3;
                local_13c = fVar5;
                if (local_64 == 0) {
                  local_d8[2] = 2.3418052e-38;
                  local_10c[2] = 0.0;
                  if ((param_9 & 0x80) == 0) {
                    if ((param_9 & 0x200) == 0) {
                      local_e4 = local_10c[4];
                      local_144 = (ushort *)local_d8[4];
                      local_e0 = local_10c[1];
                      local_11c = iVar8 - iVar12;
                      iVar8 = local_e8 + iVar12 * 2;
                      puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                      if ((int)local_11c < 0) {
                        if (0x7fffffff < local_11c) {
                          iVar8 = iVar8 - (int)puVar9;
                          local_11c = -local_11c;
                          do {
                            puVar9 = puVar9 + -1;
                            local_148 = (ushort *)((int)local_148 - (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                            if ((uVar11 & 3) != 3) {
                              local_13c = (float)((int)local_13c - (int)local_10c[3]);
                            }
                            local_144 = (ushort *)((int)local_144 - (int)local_10c[4]);
                            if ((((uVar11 & 1) != 0) ||
                                (((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                               ((uVar19 = (uint)*(ushort *)
                                                 (param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar20 & 0xff0000) >> 8) * 2),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) * 0x1f &
                                       0x7c0f83e0;
                              uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                       ((int)local_144 >> 0x13) & 0x7c0f83e0;
                              if ((uVar11 & 2) == 0) {
                                *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                              }
                              *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                        (short)((uVar13 >> 0x10 | uVar13) >> 5);
                            }
                            local_11c = local_11c + -1;
                          } while (local_11c != 0);
                        }
                      }
                      else if (0 < (int)local_11c) {
                        iVar8 = iVar8 - (int)puVar9;
                        do {
                          if ((((uVar11 & 1) != 0) ||
                              (((int)local_13c >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                             ((uVar19 = (uint)*(ushort *)
                                               (param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)fVar20 & 0xff0000) >> 8) * 2),
                              (param_9 & 4) == 0 || (uVar19 != 0)))) {
                            uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) * 0x1f &
                                     0x7c0f83e0;
                            uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                     ((int)local_144 >> 0x13) & 0x7c0f83e0;
                            if ((uVar11 & 2) == 0) {
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                            }
                            *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                      (short)((uVar13 >> 0x10 | uVar13) >> 5);
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_10c[0]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                          if ((uVar11 & 3) != 3) {
                            local_13c = (float)((int)local_13c + (int)local_10c[3]);
                          }
                          local_144 = (ushort *)((int)local_144 + (int)local_10c[4]);
                          puVar9 = puVar9 + 1;
                          local_11c = local_11c - 1;
                        } while (local_11c != 0);
                      }
                    }
                    else {
                      local_130 = local_d8[4];
                      local_e0 = local_10c[3];
                      local_13c = local_d8[3];
                      local_11c = iVar8 - iVar12;
                      iVar7 = local_e8 + iVar12 * 2;
                      puVar9 = (ushort *)(local_ec + iVar12 * 2);
                      if ((int)local_11c < 0) {
                        if (0x7fffffff < local_11c) {
                          iVar7 = iVar7 - (int)puVar9;
                          iVar8 = -local_11c;
                          do {
                            puVar9 = puVar9 + -1;
                            local_148 = (ushort *)((int)local_148 - (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                            if ((uVar11 & 3) != 3) {
                              local_13c = (float)((int)local_13c - (int)local_10c[3]);
                            }
                            local_130 = (float)((int)local_130 - (int)local_10c[4]);
                            if ((((uVar11 & 1) != 0) ||
                                (((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar7 + (int)puVar9))) &&
                               ((uVar19 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar20 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar13 = (uVar19 & 0x3e07c1f) * 0x1f & 0x7c0f83e0;
                              uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                       (((uVar19 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0x7c0f83e0;
                              if ((uVar11 & 2) == 0) {
                                *(short *)(iVar7 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                              }
                              *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                        (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            }
                            iVar8 = iVar8 + -1;
                          } while (iVar8 != 0);
                        }
                      }
                      else if (0 < (int)local_11c) {
                        iVar7 = iVar7 - (int)puVar9;
                        do {
                          if ((((uVar11 & 1) != 0) ||
                              (((int)local_13c >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar7 + (int)puVar9))) &&
                             ((uVar19 = *(uint *)(param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar20 & 0xff0000) >> 8) * 4),
                              (param_9 & 4) == 0 || (uVar19 != 0)))) {
                            uVar13 = (uVar19 & 0x3e07c1f) * 0x1f & 0x7c0f83e0;
                            uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                     (((uVar19 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^ 0x1f000000)
                                     >> 0x18) & 0x7c0f83e0;
                            if ((uVar11 & 2) == 0) {
                              *(short *)(iVar7 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                            }
                            *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                      (short)((uVar19 >> 0x10 | uVar19) >> 5);
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_10c[0]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                          if ((uVar11 & 3) != 3) {
                            local_13c = (float)((int)local_13c + (int)local_10c[3]);
                          }
                          local_130 = (float)((int)local_130 + (int)local_10c[4]);
                          puVar9 = puVar9 + 1;
                          local_11c = local_11c - 1;
                        } while (local_11c != 0);
                      }
                    }
                  }
                  else {
                    local_e0 = local_10c[1];
                    local_12c = iVar8 - iVar12;
                    iVar8 = local_e8 + iVar12 * 2;
                    puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                    if ((int)local_12c < 0) {
                      if (0x7fffffff < local_12c) {
                        iVar8 = iVar8 - (int)puVar9;
                        local_11c = -local_12c;
                        do {
                          puVar9 = puVar9 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_10c[0]);
                          fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                          if ((uVar11 & 3) != 3) {
                            local_13c = (float)((int)local_13c - (int)local_10c[3]);
                          }
                          if ((((uVar11 & 1) != 0) ||
                              (((int)local_13c >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                             (uVar19 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar20 & 0xff0000) >> 8) * 2), uVar19 != 0
                             )) {
                            uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) * 0x1f &
                                     0x7c0f83e0;
                            uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                            uVar19 = *puVar9 + uVar13;
                            uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            if ((uVar11 & 2) == 0) {
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                            }
                            *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          }
                          local_11c = local_11c + -1;
                        } while (local_11c != 0);
                      }
                    }
                    else if (0 < (int)local_12c) {
                      iVar8 = iVar8 - (int)puVar9;
                      do {
                        if ((((uVar11 & 1) != 0) ||
                            (((int)local_13c >> 0x10 & 0xffffU) <=
                             (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                           (uVar19 = (uint)*(ushort *)
                                            (param_3 +
                                            ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                  (uint)fVar20 & 0xff0000) >> 8) * 2), uVar19 != 0))
                        {
                          uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) * 0x1f &
                                   0x7c0f83e0;
                          uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                          uVar19 = *puVar9 + uVar13;
                          uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                          sVar2 = (short)uVar13;
                          if ((uVar11 & 2) == 0) {
                            *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                          }
                          *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_10c[0]);
                        fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                        if ((uVar11 & 3) != 3) {
                          local_13c = (float)((int)local_13c + (int)local_10c[3]);
                        }
                        puVar9 = puVar9 + 1;
                        local_12c = local_12c - 1;
                      } while (local_12c != 0);
                    }
                  }
                }
                else {
                  local_144 = (ushort *)fVar3;
                  if (local_98 == 0) {
                    local_134 = fVar3;
                    if ((param_9 & 0x80) == 0) {
                      if ((param_9 & 0x200) == 0) {
                        local_130 = local_d8[2];
                        local_e4 = local_10c[1];
                        local_134 = local_d8[4];
                        local_138 = iVar8 - iVar12;
                        iVar8 = local_e8 + iVar12 * 2;
                        puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                        if ((int)local_138 < 0) {
                          if (0x7fffffff < local_138) {
                            iVar8 = iVar8 - (int)puVar9;
                            local_138 = -local_138;
                            do {
                              puVar9 = puVar9 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                              fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                              local_130 = (float)((int)local_130 - (int)local_10c[2]);
                              local_13c = (float)((int)local_13c - (int)local_10c[3]);
                              local_134 = (float)((int)local_134 - (int)local_10c[4]);
                              if ((((int)local_13c >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)((int)puVar9 + iVar8)) &&
                                 ((uVar19 = (uint)*(ushort *)
                                                   (param_3 +
                                                   ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar20 & 0xff0000) >> 8) * 2),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                         ((int)local_130 >> 0x13) & 0x7c0f83e0;
                                uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                         ((int)local_134 >> 0x13) & 0x7c0f83e0;
                                *(short *)((int)puVar9 + iVar8) = (short)((uint)local_13c >> 0x10);
                                *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                          (short)((uVar13 >> 0x10 | uVar13) >> 5);
                              }
                              local_138 = local_138 + -1;
                            } while (local_138 != 0);
                          }
                        }
                        else if (0 < (int)local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          do {
                            if ((((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)puVar9 + iVar8)) &&
                               ((uVar19 = (uint)*(ushort *)
                                                 (param_3 +
                                                 ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar20 & 0xff0000) >> 8) * 2),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                       ((int)local_130 >> 0x13) & 0x7c0f83e0;
                              uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                       ((int)local_134 >> 0x13) & 0x7c0f83e0;
                              *(short *)((int)puVar9 + iVar8) = (short)((uint)local_13c >> 0x10);
                              *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                        (short)((uVar13 >> 0x10 | uVar13) >> 5);
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                            local_130 = (float)((int)local_130 + (int)local_10c[2]);
                            local_134 = (float)((int)local_134 + (int)local_10c[4]);
                            local_13c = (float)((int)local_13c + (int)local_10c[3]);
                            puVar9 = puVar9 + 1;
                            local_138 = local_138 - 1;
                          } while (local_138 != 0);
                        }
                      }
                      else {
                        local_144 = (ushort *)local_d8[4];
                        local_e4 = local_10c[3];
                        local_130 = local_d8[2];
                        local_138 = iVar8 - iVar12;
                        iVar8 = local_e8 + iVar12 * 2;
                        puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                        local_13c = fVar20;
                        if ((int)local_138 < 0) {
                          if (0x7fffffff < local_138) {
                            iVar8 = iVar8 - (int)puVar9;
                            local_138 = -local_138;
                            do {
                              puVar9 = puVar9 + -1;
                              local_134 = (float)((int)local_134 - (int)local_10c[0]);
                              local_13c = (float)((int)local_13c - (int)local_10c[1]);
                              local_130 = (float)((int)local_130 - (int)local_10c[2]);
                              fVar5 = (float)((int)fVar5 - (int)local_10c[3]);
                              local_144 = (ushort *)((int)local_144 - (int)local_10c[4]);
                              if ((((int)fVar5 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                                 ((uVar19 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                           (uint)local_13c & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar13 = ((int)local_130 >> 0x13) * (uVar19 & 0x3e07c1f) &
                                         0x7c0f83e0;
                                uVar1 = *puVar9;
                                *(short *)(iVar8 + (int)puVar9) = (short)((uint)fVar5 >> 0x10);
                                uVar19 = ((uVar1 & 0x3e0) << 0x10 | uVar1 & 0x3e07c1f) *
                                         (((uVar19 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0x7c0f83e0;
                                *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                          (short)((uVar19 >> 0x10 | uVar19) >> 5);
                              }
                              local_138 = local_138 + -1;
                            } while (local_138 != 0);
                          }
                        }
                        else if (0 < (int)local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          do {
                            if ((((int)fVar5 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)puVar9 + iVar8)) &&
                               ((uVar19 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                         (uint)local_13c & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar13 = ((int)local_130 >> 0x13) * (uVar19 & 0x3e07c1f) & 0x7c0f83e0;
                              uVar1 = *puVar9;
                              *(short *)((int)puVar9 + iVar8) = (short)((uint)fVar5 >> 0x10);
                              uVar19 = ((uVar1 & 0x3e0) << 0x10 | uVar1 & 0x3e07c1f) *
                                       (((uVar19 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0x7c0f83e0;
                              *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                        (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            }
                            local_134 = (float)((int)local_134 + (int)local_10c[0]);
                            local_13c = (float)((int)local_13c + (int)local_10c[1]);
                            local_130 = (float)((int)local_130 + (int)local_10c[2]);
                            puVar9 = puVar9 + 1;
                            fVar5 = (float)((int)fVar5 + (int)local_10c[3]);
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[4]);
                            local_138 = local_138 - 1;
                          } while (local_138 != 0);
                        }
                      }
                    }
                    else {
                      local_138 = iVar8 - iVar12;
                      iVar8 = local_e8 + iVar12 * 2;
                      puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                      local_130 = fVar5;
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          local_138 = -local_138;
                          fVar3 = local_d8[2];
                          local_144 = (ushort *)fVar20;
                          do {
                            puVar9 = puVar9 + -1;
                            local_134 = (float)((int)local_134 - (int)local_10c[0]);
                            local_144 = (ushort *)((int)local_144 - (int)local_10c[1]);
                            local_130 = (float)((int)local_130 - (int)local_10c[3]);
                            fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                            if ((((int)local_130 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                               (uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                               (uint)local_144 & 0xff0000) >> 8) * 2), uVar1 != 0))
                            {
                              uVar19 = ((uint)(uVar1 & 0x3e0) << 0x10 | uVar1 & 0x3e07c1f) *
                                       ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                              uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_130 >> 0x10);
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)puVar9;
                        fVar3 = local_d8[2];
                        do {
                          if ((((int)local_130 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                             (uVar19 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar20 & 0xff0000) >> 8) * 2), uVar19 != 0
                             )) {
                            uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                     ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                            uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                            uVar19 = *puVar9 + uVar13;
                            uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_130 >> 0x10);
                            *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          }
                          local_134 = (float)((int)local_134 + (int)local_10c[0]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                          fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                          local_130 = (float)((int)local_130 + (int)local_10c[3]);
                          puVar9 = puVar9 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                  }
                  else {
                    iVar18 = (int)local_d8[6] >> 0x13;
                    iVar23 = (int)local_d8[5] >> 0x13;
                    iVar14 = (int)local_d8[2] >> 0x13;
                    local_130 = fVar20;
                    if (local_98 == 0x10) {
                      local_148 = (ushort *)fVar5;
                      if ((param_9 & 0x80) == 0) {
                        if ((param_9 & 0x200) == 0) {
                          if ((param_9 & 0x40) == 0) {
                            local_e4 = local_10c[1];
                            local_138 = iVar8 - iVar12;
                            iVar8 = local_e8 + iVar12 * 2;
                            puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                            if ((int)local_138 < 0) {
                              if (0x7fffffff < local_138) {
                                iVar8 = iVar8 - (int)puVar9;
                                local_138 = -local_138;
                                fVar3 = local_d8[2];
                                fVar5 = local_d8[4];
                                do {
                                  puVar9 = puVar9 + -1;
                                  local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                                  fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                                  fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                                  local_148 = (ushort *)((int)local_148 - (int)local_10c[3]);
                                  fVar5 = (float)((int)fVar5 - (int)local_10c[4]);
                                  if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                       (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                                     ((uVar19 = (uint)*(ushort *)
                                                       (param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar20 & 0xff0000) >> 8) * 2),
                                      (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                    uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                             ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                                    uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                             ((int)fVar5 >> 0x13) & 0x7c0f83e0;
                                    *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                              (short)((uVar13 >> 0x10 | uVar13) >> 5);
                                  }
                                  local_138 = local_138 + -1;
                                } while (local_138 != 0);
                              }
                            }
                            else if (0 < (int)local_138) {
                              iVar8 = iVar8 - (int)puVar9;
                              fVar3 = local_d8[2];
                              fVar5 = local_d8[4];
                              do {
                                if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                                   ((uVar19 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar20 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                  uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                           ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                                  uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                           ((int)fVar5 >> 0x13) & 0x7c0f83e0;
                                  *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                            (short)((uVar13 >> 0x10 | uVar13) >> 5);
                                }
                                local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                                fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                                fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                                fVar5 = (float)((int)fVar5 + (int)local_10c[4]);
                                local_148 = (ushort *)((int)local_148 + (int)local_10c[3]);
                                puVar9 = puVar9 + 1;
                                local_138 = local_138 - 1;
                              } while (local_138 != 0);
                            }
                          }
                          else {
                            local_e4 = local_10c[0];
                            local_138 = iVar8 - iVar12;
                            iVar8 = local_e8 + iVar12 * 2;
                            puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                            if ((int)local_138 < 0) {
                              if (0x7fffffff < local_138) {
                                iVar8 = iVar8 - (int)puVar9;
                                local_138 = -local_138;
                                fVar3 = local_d8[2];
                                do {
                                  puVar9 = puVar9 + -1;
                                  local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                                  fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                                  fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                                  local_148 = (ushort *)((int)local_148 - (int)local_10c[3]);
                                  if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                       (uint)*(ushort *)((int)puVar9 + iVar8)) &&
                                     ((uVar19 = (uint)*(ushort *)
                                                       (param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar20 & 0xff0000) >> 8) * 2),
                                      (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                    uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                             ((int)fVar3 >> 0x13) & 0x3c0781e0;
                                    *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                              (*puVar9 >> 1 & 0x3def);
                                  }
                                  local_138 = local_138 + -1;
                                } while (local_138 != 0);
                              }
                            }
                            else if (0 < (int)local_138) {
                              iVar8 = iVar8 - (int)puVar9;
                              fVar3 = local_d8[2];
                              do {
                                if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)((int)puVar9 + iVar8)) &&
                                   ((uVar19 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar20 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                  uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                           ((int)fVar3 >> 0x13) & 0x3c0781e0;
                                  *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                            (*puVar9 >> 1 & 0x3def);
                                }
                                local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                                fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                                fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                                local_148 = (ushort *)((int)local_148 + (int)local_10c[3]);
                                puVar9 = puVar9 + 1;
                                local_138 = local_138 - 1;
                              } while (local_138 != 0);
                            }
                          }
                        }
                        else {
                          local_130 = local_d8[2];
                          local_134 = local_d8[4];
                          local_e4 = local_10c[0];
                          iVar14 = local_e8 + iVar12 * 2;
                          local_138 = iVar8 - iVar12;
                          puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                          if ((int)local_138 < 0) {
                            if (0x7fffffff < local_138) {
                              iVar14 = iVar14 - (int)puVar9;
                              local_138 = -local_138;
                              do {
                                puVar9 = puVar9 + -1;
                                local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                                fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                                local_130 = (float)((int)local_130 - (int)local_10c[2]);
                                fVar5 = (float)((int)fVar5 - (int)local_10c[3]);
                                local_134 = (float)((int)local_134 - (int)local_10c[4]);
                                if ((((int)fVar5 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar14 + (int)puVar9)) &&
                                   ((uVar19 = *(uint *)(param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar20 & 0xff0000) >> 8) * 4),
                                    (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                  uVar13 = ((int)local_130 >> 0x13) * (uVar19 & 0x3e07c1f) &
                                           0x7c0f83e0;
                                  uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                           (((uVar19 >> 0x1b) * ((uint)local_134 ^ 0xffffff) ^
                                            0x1f000000) >> 0x18) & 0x7c0f83e0;
                                  *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                            (short)((uVar19 >> 0x10 | uVar19) >> 5);
                                }
                                local_138 = local_138 + -1;
                              } while (local_138 != 0);
                            }
                          }
                          else if (0 < (int)local_138) {
                            iVar14 = iVar14 - (int)puVar9;
                            do {
                              if ((((int)fVar5 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)((int)puVar9 + iVar14)) &&
                                 ((uVar19 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar20 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar13 = ((int)local_130 >> 0x13) * (uVar19 & 0x3e07c1f) &
                                         0x7c0f83e0;
                                uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                         (((uVar19 >> 0x1b) * ((uint)local_134 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0x7c0f83e0;
                                *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                          (short)((uVar19 >> 0x10 | uVar19) >> 5);
                              }
                              local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                              fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                              local_130 = (float)((int)local_130 + (int)local_10c[2]);
                              fVar5 = (float)((int)fVar5 + (int)local_10c[3]);
                              local_134 = (float)((int)local_134 + (int)local_10c[4]);
                              puVar9 = puVar9 + 1;
                              local_138 = local_138 - 1;
                            } while (local_138 != 0);
                          }
                        }
                      }
                      else if ((param_9 & 0x102) == 0x102) {
                        local_e4 = local_10c[1];
                        local_138 = iVar8 - iVar12;
                        iVar8 = local_e8 + iVar12 * 2;
                        local_148 = (ushort *)(iVar7 + iVar12 * 2);
                        local_134 = fVar5;
                        if ((int)local_138 < 0) {
                          if (0x7fffffff < local_138) {
                            iVar8 = iVar8 - (int)local_148;
                            local_138 = -local_138;
                            do {
                              local_148 = local_148 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                              local_130 = (float)((int)local_130 - (int)local_10c[1]);
                              local_134 = (float)((int)local_134 - (int)local_10c[3]);
                              if (((int)local_134 >> 0x10 & 0xffffU) <=
                                  (uint)*(ushort *)(iVar8 + (int)local_148)) {
                                uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                               (uint)local_130 & 0xff0000) >> 8) * 2);
                                uVar19 = (uint)uVar1;
                                if (uVar19 != 0) {
                                  uVar13 = ((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                            (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                           (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5;
                                  uVar19 = *local_148 + uVar13;
                                  uVar13 = (uVar19 ^ *local_148 ^ uVar13) & 0x8420;
                                  sVar2 = (short)uVar13;
                                  *local_148 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                                }
                              }
                              local_138 = local_138 + -1;
                            } while (local_138 != 0);
                          }
                        }
                        else if (0 < (int)local_138) {
                          iVar8 = iVar8 - (int)local_148;
                          do {
                            if (((int)local_134 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)((int)local_148 + iVar8)) {
                              uVar1 = *(ushort *)
                                       (param_3 +
                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                             (uint)local_130 & 0xff0000) >> 8) * 2);
                              uVar19 = (uint)uVar1;
                              if (uVar19 != 0) {
                                uVar13 = ((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                          (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                         (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5;
                                uVar19 = *local_148 + uVar13;
                                uVar13 = (uVar19 ^ *local_148 ^ uVar13) & 0x8420;
                                sVar2 = (short)uVar13;
                                *local_148 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                              }
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                            local_130 = (float)((int)local_130 + (int)local_10c[1]);
                            local_134 = (float)((int)local_134 + (int)local_10c[3]);
                            local_148 = local_148 + 1;
                            local_138 = local_138 - 1;
                          } while (local_138 != 0);
                        }
                      }
                      else {
                        local_e4 = local_10c[1];
                        local_138 = iVar8 - iVar12;
                        iVar8 = local_e8 + iVar12 * 2;
                        puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                        if ((int)local_138 < 0) {
                          if (0x7fffffff < local_138) {
                            iVar8 = iVar8 - (int)puVar9;
                            local_138 = -local_138;
                            fVar3 = local_d8[2];
                            do {
                              puVar9 = puVar9 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                              fVar3 = (float)((int)fVar3 - (int)local_10c[2]);
                              local_148 = (ushort *)((int)local_148 - (int)local_10c[3]);
                              fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                              if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                                 (uVar19 = (uint)*(ushort *)
                                                  (param_3 +
                                                  ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                        (uint)fVar20 & 0xff0000) >> 8) * 2),
                                 uVar19 != 0)) {
                                uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                         ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                                uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                                uVar19 = *puVar9 + uVar13;
                                uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                                sVar2 = (short)uVar13;
                                *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                              }
                              local_138 = local_138 + -1;
                            } while (local_138 != 0);
                          }
                        }
                        else if (0 < (int)local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          fVar3 = local_d8[2];
                          do {
                            if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar8 + (int)puVar9)) &&
                               (uVar19 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar20 & 0xff0000) >> 8) * 2),
                               uVar19 != 0)) {
                              uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                       ((int)fVar3 >> 0x13) & 0x7c0f83e0;
                              uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                            fVar3 = (float)((int)fVar3 + (int)local_10c[2]);
                            local_148 = (ushort *)((int)local_148 + (int)local_10c[3]);
                            puVar9 = puVar9 + 1;
                            local_138 = local_138 - 1;
                          } while (local_138 != 0);
                        }
                      }
                    }
                    else if ((param_9 & 0x19a) == 0x19a) {
                      local_e4 = local_10c[1];
                      local_138 = iVar8 - iVar12;
                      puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          local_138 = -local_138;
                          do {
                            puVar9 = puVar9 + -1;
                            local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                           (uint)fVar20 & 0xff0000) >> 8) * 2);
                            uVar19 = (uint)uVar1;
                            if (uVar19 != 0) {
                              uVar13 = ((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                        (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                       (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else {
                        local_148 = (ushort *)fVar20;
                        if (0 < (int)local_138) {
                          do {
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                           (uint)local_148 & 0xff0000) >> 8) * 2);
                            uVar19 = (uint)uVar1;
                            if (uVar19 != 0) {
                              uVar13 = ((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                        (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                       (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            puVar9 = puVar9 + 1;
                            local_138 = local_138 - 1;
                            local_148 = (ushort *)((int)local_148 + (int)local_10c[1]);
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                          } while (local_138 != 0);
                        }
                      }
                    }
                    else if ((param_9 & 0x80) == 0) {
                      if ((param_9 & 0x200) == 0) {
                        if ((param_9 & 0x102) == 0x102) {
                          local_13c = local_d8[3];
                          local_e0 = local_10c[1];
                          iVar7 = local_e8 + iVar12 * 2;
                          local_12c = iVar8 - iVar12;
                          local_148 = (ushort *)(local_ec + iVar12 * 2);
                          if ((int)local_12c < 0) {
                            if (0x7fffffff < local_12c) {
                              iVar7 = iVar7 - (int)local_148;
                              local_12c = -local_12c;
                              do {
                                local_148 = local_148 + -1;
                                local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                                local_130 = (float)((int)local_130 - (int)local_10c[1]);
                                if ((uVar11 & 3) != 3) {
                                  local_13c = (float)((int)local_13c - (int)local_10c[3]);
                                }
                                if (((uVar11 & 1) != 0) ||
                                   (((int)local_13c >> 0x10 & 0xffffU) <=
                                    (uint)*(ushort *)(iVar7 + (int)local_148))) {
                                  uVar1 = *(ushort *)
                                           (param_3 +
                                           ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                 (uint)local_130 & 0xff0000) >> 8) * 2);
                                  uVar19 = (uint)uVar1;
                                  if (((param_9 & 4) == 0) || (uVar19 != 0)) {
                                    uVar13 = ((*local_148 & 0x3e0) << 0x10 | *local_148 & 0x3e07c1f)
                                             * ((int)local_d8[4] >> 0x13) & 0x7c0f83e0;
                                    if ((uVar11 & 2) == 0) {
                                      *(short *)(iVar7 + (int)local_148) =
                                           (short)((uint)local_13c >> 0x10);
                                    }
                                    *local_148 = (short)(((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                                          (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                                         (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5)
                                                 + (short)((uVar13 >> 0x10 | uVar13) >> 5);
                                  }
                                }
                                local_12c = local_12c + -1;
                              } while (local_12c != 0);
                            }
                          }
                          else if (0 < (int)local_12c) {
                            iVar7 = iVar7 - (int)local_148;
                            do {
                              if (((uVar11 & 1) != 0) ||
                                 (((int)local_13c >> 0x10 & 0xffffU) <=
                                  (uint)*(ushort *)((int)local_148 + iVar7))) {
                                uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                               (uint)local_130 & 0xff0000) >> 8) * 2);
                                uVar19 = (uint)uVar1;
                                if (((param_9 & 4) == 0) || (uVar19 != 0)) {
                                  uVar13 = ((*local_148 & 0x3e0) << 0x10 | *local_148 & 0x3e07c1f) *
                                           ((int)local_d8[4] >> 0x13) & 0x7c0f83e0;
                                  if ((uVar11 & 2) == 0) {
                                    *(short *)((int)local_148 + iVar7) =
                                         (short)((uint)local_13c >> 0x10);
                                  }
                                  *local_148 = (short)(((uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                                        (uVar19 & 0x3e0) * iVar23 & 0x7c00 |
                                                       (uVar1 & 0x7c00) * iVar18 & 0xf8000) >> 5) +
                                               (short)((uVar13 >> 0x10 | uVar13) >> 5);
                                }
                              }
                              local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                              local_130 = (float)((int)local_130 + (int)local_10c[1]);
                              if ((uVar11 & 3) != 3) {
                                local_13c = (float)((int)local_13c + (int)local_10c[3]);
                              }
                              local_148 = local_148 + 1;
                              local_12c = local_12c - 1;
                            } while (local_12c != 0);
                          }
                        }
                        else {
                          local_130 = local_d8[4];
                          local_e0 = local_10c[1];
                          local_e4 = local_10c[3];
                          local_144 = (ushort *)local_d8[2];
                          local_12c = iVar8 - iVar12;
                          iVar8 = local_e8 + iVar12 * 2;
                          puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                          if ((int)local_12c < 0) {
                            if (0x7fffffff < local_12c) {
                              iVar8 = iVar8 - (int)puVar9;
                              local_12c = -local_12c;
                              do {
                                puVar9 = puVar9 + -1;
                                local_148 = (ushort *)((int)local_148 - (int)local_10c[0]);
                                fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                                local_144 = (ushort *)((int)local_144 - (int)local_10c[2]);
                                if ((uVar11 & 3) != 3) {
                                  local_13c = (float)((int)local_13c - (int)local_10c[3]);
                                }
                                local_130 = (float)((int)local_130 - (int)local_10c[4]);
                                if ((((uVar11 & 1) != 0) ||
                                    (((int)local_13c >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                                   ((uVar19 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar20 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                  uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                           ((int)local_144 >> 0x13) & 0x7c0f83e0;
                                  uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                           ((int)local_130 >> 0x13) & 0x7c0f83e0;
                                  if ((uVar11 & 2) == 0) {
                                    *(short *)(iVar8 + (int)puVar9) =
                                         (short)((uint)local_13c >> 0x10);
                                  }
                                  *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                            (short)((uVar13 >> 0x10 | uVar13) >> 5);
                                }
                                local_12c = local_12c + -1;
                              } while (local_12c != 0);
                            }
                          }
                          else if (0 < (int)local_12c) {
                            iVar8 = iVar8 - (int)puVar9;
                            do {
                              if ((((uVar11 & 1) != 0) ||
                                  (((int)local_13c >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                                 ((uVar19 = (uint)*(ushort *)
                                                   (param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar20 & 0xff0000) >> 8) * 2),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                         ((int)local_144 >> 0x13) & 0x7c0f83e0;
                                uVar13 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                         ((int)local_130 >> 0x13) & 0x7c0f83e0;
                                if ((uVar11 & 2) == 0) {
                                  *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10)
                                  ;
                                }
                                *puVar9 = (short)((uVar19 >> 0x10 | uVar19) >> 5) +
                                          (short)((uVar13 >> 0x10 | uVar13) >> 5);
                              }
                              local_148 = (ushort *)((int)local_148 + (int)local_10c[0]);
                              fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                              local_144 = (ushort *)((int)local_144 + (int)local_10c[2]);
                              if ((uVar11 & 3) != 3) {
                                local_13c = (float)((int)local_13c + (int)local_10c[3]);
                              }
                              local_130 = (float)((int)local_130 + (int)local_10c[4]);
                              puVar9 = puVar9 + 1;
                              local_12c = local_12c - 1;
                            } while (local_12c != 0);
                          }
                        }
                      }
                      else if ((param_9 & 0x100) == 0) {
                        local_130 = local_d8[4];
                        local_e4 = local_10c[3];
                        local_13c = local_d8[3];
                        local_144 = (ushort *)local_d8[2];
                        local_e0 = local_10c[1];
                        iVar7 = local_e8 + iVar12 * 2;
                        local_12c = iVar8 - iVar12;
                        puVar9 = (ushort *)(local_ec + iVar12 * 2);
                        if ((int)local_12c < 0) {
                          if (0x7fffffff < local_12c) {
                            iVar7 = iVar7 - (int)puVar9;
                            local_12c = -local_12c;
                            do {
                              puVar9 = puVar9 + -1;
                              local_148 = (ushort *)((int)local_148 - (int)local_10c[0]);
                              fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                              local_144 = (ushort *)((int)local_144 - (int)local_10c[2]);
                              if ((uVar11 & 3) != 3) {
                                local_13c = (float)((int)local_13c - (int)local_10c[3]);
                              }
                              local_130 = (float)((int)local_130 - (int)local_10c[4]);
                              if ((((uVar11 & 1) != 0) ||
                                  (((int)local_13c >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar7 + (int)puVar9))) &&
                                 ((uVar19 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar20 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar13 = ((int)local_144 >> 0x13) * (uVar19 & 0x3e07c1f) &
                                         0x7c0f83e0;
                                uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                         (((uVar19 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0x7c0f83e0;
                                if ((uVar11 & 2) == 0) {
                                  *(short *)(iVar7 + (int)puVar9) = (short)((uint)local_13c >> 0x10)
                                  ;
                                }
                                *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                          (short)((uVar19 >> 0x10 | uVar19) >> 5);
                              }
                              local_12c = local_12c + -1;
                            } while (local_12c != 0);
                          }
                        }
                        else if (0 < (int)local_12c) {
                          iVar7 = iVar7 - (int)puVar9;
                          do {
                            if ((((uVar11 & 1) != 0) ||
                                (((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar7 + (int)puVar9))) &&
                               ((uVar19 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar20 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar13 = ((int)local_144 >> 0x13) * (uVar19 & 0x3e07c1f) & 0x7c0f83e0;
                              uVar19 = ((*puVar9 & 0x3e0) << 0x10 | *puVar9 & 0x3e07c1f) *
                                       (((uVar19 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0x7c0f83e0;
                              if ((uVar11 & 2) == 0) {
                                *(short *)(iVar7 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                              }
                              *puVar9 = (short)((uVar13 >> 0x10 | uVar13) >> 5) +
                                        (short)((uVar19 >> 0x10 | uVar19) >> 5);
                            }
                            local_148 = (ushort *)((int)local_148 + (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                            local_144 = (ushort *)((int)local_144 + (int)local_10c[2]);
                            if ((uVar11 & 3) != 3) {
                              local_13c = (float)((int)local_13c + (int)local_10c[3]);
                            }
                            local_130 = (float)((int)local_130 + (int)local_10c[4]);
                            puVar9 = puVar9 + 1;
                            local_12c = local_12c - 1;
                          } while (local_12c != 0);
                        }
                      }
                      else {
                        local_148 = (ushort *)local_d8[4];
                        local_e0 = local_10c[3];
                        local_13c = local_d8[3];
                        local_e4 = local_10c[1];
                        iVar7 = local_e8 + iVar12 * 2;
                        local_138 = iVar8 - iVar12;
                        local_144 = (ushort *)(local_ec + iVar12 * 2);
                        local_134 = fVar20;
                        local_130 = fVar3;
                        if ((int)local_138 < 0) {
                          if (0x7fffffff < local_138) {
                            iVar7 = iVar7 - (int)local_144;
                            local_138 = -local_138;
                            do {
                              local_144 = local_144 + -1;
                              local_130 = (float)((int)local_130 - (int)local_10c[0]);
                              local_134 = (float)((int)local_134 - (int)local_10c[1]);
                              if ((uVar11 & 3) != 3) {
                                local_13c = (float)((int)local_13c - (int)local_10c[3]);
                              }
                              local_148 = (ushort *)((int)local_148 - (int)local_10c[4]);
                              if ((((uVar11 & 1) != 0) ||
                                  (((int)local_13c >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar7 + (int)local_144))) &&
                                 ((uVar19 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_130 >> 0x10 & 0xff) << 8 |
                                                           (uint)local_134 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar19 != 0)))) {
                                uVar13 = ((*local_144 & 0x3e0) << 0x10 | *local_144 & 0x3e07c1f) *
                                         (((uVar19 >> 0x1b) * ((uint)local_148 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0x7c0f83e0;
                                if ((uVar11 & 2) == 0) {
                                  *(short *)(iVar7 + (int)local_144) =
                                       (short)((uint)local_13c >> 0x10);
                                }
                                *local_144 = (short)(((uVar19 & 0x3e00000) * iVar23 >> 0x10 & 0x7c00
                                                      | (uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                                     (uVar19 & 0x7c00) * iVar18 & 0xf8000) >> 5) +
                                             (short)((uVar13 >> 0x10 | uVar13) >> 5);
                              }
                              local_138 = local_138 + -1;
                            } while (local_138 != 0);
                          }
                        }
                        else if (0 < (int)local_138) {
                          iVar7 = iVar7 - (int)local_144;
                          do {
                            if ((((uVar11 & 1) != 0) ||
                                (((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)local_144 + iVar7))) &&
                               ((uVar19 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_130 >> 0x10 & 0xff) << 8 |
                                                         (uint)local_134 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar19 != 0)))) {
                              uVar13 = ((*local_144 & 0x3e0) << 0x10 | *local_144 & 0x3e07c1f) *
                                       (((uVar19 >> 0x1b) * ((uint)local_148 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0x7c0f83e0;
                              if ((uVar11 & 2) == 0) {
                                *(short *)((int)local_144 + iVar7) =
                                     (short)((uint)local_13c >> 0x10);
                              }
                              *local_144 = (short)(((uVar19 & 0x3e00000) * iVar23 >> 0x10 & 0x7c00 |
                                                    (uVar19 & 0x1f) * iVar14 & 0x3e0 |
                                                   (uVar19 & 0x7c00) * iVar18 & 0xf8000) >> 5) +
                                           (short)((uVar13 >> 0x10 | uVar13) >> 5);
                            }
                            local_130 = (float)((int)local_130 + (int)local_10c[0]);
                            local_134 = (float)((int)local_134 + (int)local_10c[1]);
                            if ((uVar11 & 3) != 3) {
                              local_13c = (float)((int)local_13c + (int)local_10c[3]);
                            }
                            local_148 = (ushort *)((int)local_148 + (int)local_10c[4]);
                            local_144 = local_144 + 1;
                            local_138 = local_138 - 1;
                          } while (local_138 != 0);
                        }
                      }
                    }
                    else {
                      local_130 = local_d8[2];
                      local_e4 = local_10c[1];
                      local_138 = iVar8 - iVar12;
                      iVar8 = local_e8 + iVar12 * 2;
                      puVar9 = (ushort *)(iVar7 + iVar12 * 2);
                      if ((int)local_138 < 0) {
                        if (0x7fffffff < local_138) {
                          iVar8 = iVar8 - (int)puVar9;
                          local_138 = -local_138;
                          do {
                            puVar9 = puVar9 + -1;
                            local_144 = (ushort *)((int)local_144 - (int)local_10c[0]);
                            fVar20 = (float)((int)fVar20 - (int)local_10c[1]);
                            local_130 = (float)((int)local_130 - (int)local_10c[2]);
                            if ((uVar11 & 3) != 3) {
                              local_13c = (float)((int)local_13c - (int)local_10c[3]);
                            }
                            if ((((uVar11 & 1) != 0) ||
                                (((int)local_13c >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                               (uVar19 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar20 & 0xff0000) >> 8) * 2),
                               uVar19 != 0)) {
                              uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                       ((int)local_130 >> 0x13) & 0x7c0f83e0;
                              uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                              uVar19 = *puVar9 + uVar13;
                              uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                              sVar2 = (short)uVar13;
                              if ((uVar11 & 2) == 0) {
                                *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                              }
                              *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                            }
                            local_138 = local_138 + -1;
                          } while (local_138 != 0);
                        }
                      }
                      else if (0 < (int)local_138) {
                        iVar8 = iVar8 - (int)puVar9;
                        do {
                          if ((((uVar11 & 1) != 0) ||
                              (((int)local_13c >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar8 + (int)puVar9))) &&
                             (uVar19 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar20 & 0xff0000) >> 8) * 2), uVar19 != 0
                             )) {
                            uVar19 = ((uVar19 & 0x3e0) << 0x10 | uVar19 & 0x3e07c1f) *
                                     ((int)local_130 >> 0x13) & 0x7c0f83e0;
                            uVar13 = (uVar19 >> 0x10 | uVar19) >> 5;
                            uVar19 = *puVar9 + uVar13;
                            uVar13 = (uVar19 ^ *puVar9 ^ uVar13) & 0x8420;
                            sVar2 = (short)uVar13;
                            if ((uVar11 & 2) == 0) {
                              *(short *)(iVar8 + (int)puVar9) = (short)((uint)local_13c >> 0x10);
                            }
                            *puVar9 = sVar2 - (short)(uVar13 >> 5) | (short)uVar19 - sVar2;
                          }
                          local_144 = (ushort *)((int)local_144 + (int)local_10c[0]);
                          fVar20 = (float)((int)fVar20 + (int)local_10c[1]);
                          local_130 = (float)((int)local_130 + (int)local_10c[2]);
                          if ((uVar11 & 3) != 3) {
                            local_13c = (float)((int)local_13c + (int)local_10c[3]);
                          }
                          puVar9 = puVar9 + 1;
                          local_138 = local_138 - 1;
                        } while (local_138 != 0);
                      }
                    }
                  }
                }
              }
              uVar13 = local_dc + local_ac;
              iVar6 = iVar6 + local_a4;
              iVar7 = 0;
              do {
                if ((local_90 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
                  local_88[iVar7] = afStack_60[iVar7] + local_88[iVar7];
                }
                iVar7 = iVar7 + 1;
              } while (iVar7 < 8);
              if (local_94 != 0) {
                local_e8 = local_e8 + param_5 * 2;
              }
              fVar3 = local_d8[0];
              fVar20 = local_d8[1];
              iVar7 = local_ec + param_4 * 2;
              local_dc = uVar13;
              fVar5 = local_d8[3];
            }
            local_128 = local_128 + 1;
          } while ((int)local_128 < 2);
          return;
        }
      }
    }
  }
  return;
}

