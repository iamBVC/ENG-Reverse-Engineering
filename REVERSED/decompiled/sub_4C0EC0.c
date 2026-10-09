/* sub_4C0EC0 @ 004c0ec0   23969 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4C0EC0(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6,
               float *param_7,float *param_8,uint param_9)

{
  ushort uVar1;
  short sVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  float fVar12;
  ushort *puVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  float fVar17;
  uint uVar18;
  float fVar19;
  int iVar20;
  ushort *local_148;
  ushort *local_144;
  ushort *local_140;
  uint local_13c;
  float local_138;
  float local_134;
  float local_130;
  uint local_12c;
  uint local_128;
  uint local_120;
  short *local_11c;
  ushort local_114;
  float local_110 [8];
  int local_f0;
  int local_ec;
  float local_e8;
  uint local_e4;
  int local_e0;
  float local_dc [8];
  uint local_bc;
  undefined4 uStack_b8;
  uint local_b4;
  float local_b0;
  uint local_ac;
  undefined4 uStack_a8;
  float local_a4;
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
    uVar16 = 100;
  }
  else {
    uVar16 = 0;
  }
  local_98 = param_9 & 0x18;
  local_64 = param_9 & 1;
  uVar11 = (-(uint)(((byte)param_9 & 0x60) != 0x20) & 0xfffffff0) + 0x10;
  uVar14 = param_9 >> 5 & 0x10;
  local_94 = -(uint)(local_98 != 0x18) & 8;
  uVar18 = -(uint)(param_3 != 0) & 3;
  uVar16 = uVar11 | uVar14 | local_94 | uVar18 | local_64 * 4 | uVar16;
  uVar9 = (int)param_9 >> 3;
  local_90 = uVar16;
  if ((param_9 & 0x2a0) == 0) {
    if (uVar18 != 0) {
      local_88[0] = param_6[6] * _DAT_0056e4c4;
      local_110[0] = param_7[6] * _DAT_0056e4c4;
      local_dc[0] = param_8[6] * _DAT_0056e4c4;
      local_88[1] = param_6[7] * _DAT_0056e4c4;
      local_110[1] = param_7[7] * _DAT_0056e4c4;
      local_dc[1] = param_8[7] * _DAT_0056e4c4;
    }
    if ((uVar16 & 0x60) != 0) {
      local_88[6] = (float)((uint)param_6[4] & 0xff0000) * _DAT_0056e4d4;
      local_110[6] = (float)((uint)param_7[4] & 0xff0000) * _DAT_0056e4d4;
      local_dc[6] = (float)((uint)param_8[4] & 0xff0000) * _DAT_0056e4d4;
      local_88[5] = (float)((uint)param_6[4] & 0xff00) * _DAT_0056e118;
      uStack_b8 = 0;
      local_110[5] = (float)((uint)param_7[4] & 0xff00) * _DAT_0056e118;
      local_bc = (uint)param_8[4] & 0xff00;
      local_dc[5] = (float)local_bc * _DAT_0056e118;
    }
    if ((uVar16 & 4) != 0) {
      local_88[2] = (float)((uint)param_6[4] & 0xff);
      uStack_b8 = 0;
      local_110[2] = (float)((uint)param_7[4] & 0xff);
      local_bc = (uint)param_8[4] & 0xff;
      local_dc[2] = (float)local_bc;
    }
    if ((uVar11 & 0x10) != 0 || uVar14 != 0) {
      local_88[4] = _DAT_0056e0c4 - (float)((uint)param_6[4] >> 0x18);
      uStack_b8 = 0;
      local_110[4] = _DAT_0056e0c4 - (float)((uint)param_7[4] >> 0x18);
      local_bc = (uint)param_8[4] >> 0x18;
      local_dc[4] = _DAT_0056e0c4 - (float)local_bc;
    }
    if (local_94 != 0) {
      local_88[3] = param_6[2] * _DAT_0056e1cc;
      local_110[3] = param_7[2] * _DAT_0056e1cc;
      local_dc[3] = param_8[2] * _DAT_0056e1cc;
    }
    if (param_6[1] != param_8[1]) {
      fVar3 = (param_7[1] - param_6[1]) / (param_8[1] - param_6[1]);
      fVar17 = (*param_8 - *param_6) * fVar3 + *param_6;
      if (fVar17 != *param_7) {
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_60[iVar5] = (local_dc[iVar5] - local_88[iVar5]) * fVar3 + local_88[iVar5];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        fVar3 = *param_7;
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_40[iVar5] =
                 (local_110[iVar5] - afStack_60[iVar5]) * (_DAT_0056e008 / (fVar3 - fVar17));
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        fVar3 = param_8[1];
        fVar17 = param_6[1];
        local_9c = *param_6;
        local_a0 = *param_7;
        if (param_7[1] != param_6[1]) {
          local_144 = (ushort *)((*param_7 - *param_6) / (param_7[1] - param_6[1]));
        }
        if (param_8[1] != param_7[1]) {
          local_130 = (*param_8 - *param_7) / (param_8[1] - param_7[1]);
        }
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_60[iVar5] =
                 (local_dc[iVar5] - local_88[iVar5]) * (_DAT_0056e008 / (fVar3 - fVar17));
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        iVar5 = __ftol();
        iVar6 = __ftol();
        local_8c = __ftol();
        if (local_8c != iVar5) {
          iVar7 = 0;
          fVar3 = (float)iVar5 - (param_6[1] - _DAT_0056e158);
          do {
            if ((uVar16 & 1 << ((byte)iVar7 & 0x1f)) != 0) {
              local_88[iVar7] = fVar3 * afStack_60[iVar7] + local_88[iVar7];
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 8);
          local_e4 = param_2;
          local_9c = fVar3 * (float)local_144 + local_9c + _DAT_0056e4d0;
          local_a0 = ((float)iVar6 - (param_7[1] - _DAT_0056e158)) * local_130 + local_a0 +
                     _DAT_0056e4d0;
          local_ec = iVar6;
          uVar11 = __ftol();
          local_68 = __ftol();
          local_120 = __ftol();
          local_ac = __ftol();
          iVar6 = 0;
          do {
            if ((uVar16 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
              fVar3 = (float)__ftol();
              local_110[iVar6] = fVar3;
              fVar3 = (float)__ftol();
              local_dc[iVar6] = fVar3;
              uVar4 = __ftol();
              auStack_20[iVar6] = uVar4;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < 8);
          param_1 = param_1 + iVar5 * param_4 * 2;
          if (local_94 != 0) {
            local_e4 = param_2 + iVar5 * param_5 * 2;
          }
          local_13c = 0;
          local_134 = (float)uVar11;
          local_130 = (float)param_1;
          local_e0 = iVar5;
          do {
            if (local_13c == 0) {
              local_f0 = __ftol();
            }
            else {
              local_f0 = __ftol();
              local_120 = local_ac;
              local_ec = local_8c;
            }
            if (local_e0 < local_ec) {
              do {
                local_bc = ((uVar11 & 0xffff0000) - uVar11) + 0xffff;
                iVar5 = 0;
                uStack_b8 = 0;
                local_148 = (ushort *)local_110[0];
                fVar3 = local_110[1];
                do {
                  if ((local_90 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
                    fVar3 = (float)__ftol();
                    local_110[iVar5] = fVar3;
                    local_148 = (ushort *)local_110[0];
                    fVar3 = local_110[1];
                  }
                  iVar5 = iVar5 + 1;
                } while (iVar5 < 8);
                iVar6 = (int)uVar11 >> 0x10;
                iVar5 = local_f0 >> 0x10;
                if (param_3 == 0) {
                  switch(local_98) {
                  case 0:
                    puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                    local_128 = iVar5 - iVar6;
                    iVar5 = (int)local_130 + iVar6 * 2;
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        iVar5 = iVar5 - (int)puVar8;
                        local_128 = -local_128;
                        fVar3 = local_110[6];
                        fVar17 = local_110[3];
                        fVar12 = local_110[5];
                        fVar19 = local_110[2];
                        do {
                          puVar8 = puVar8 + -1;
                          fVar12 = (float)((int)fVar12 - (int)local_dc[5]);
                          fVar17 = (float)((int)fVar17 - (int)local_dc[3]);
                          fVar3 = (float)((int)fVar3 - (int)local_dc[6]);
                          fVar19 = (float)((int)fVar19 - (int)local_dc[2]);
                          if (((int)fVar17 >> 0x10 & 0xffffU) <= (uint)*puVar8) {
                            *puVar8 = (ushort)((uint)fVar17 >> 0x10);
                            *(ushort *)(iVar5 + (int)puVar8) =
                                 (ushort)((uint)((int)((int)fVar19 >> 6 & 0x3e000U |
                                                      (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                                 (ushort)((uint)fVar3 >> 8) & 0xf800;
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      iVar5 = iVar5 - (int)puVar8;
                      fVar3 = local_110[6];
                      fVar17 = local_110[3];
                      fVar12 = local_110[5];
                      fVar19 = local_110[2];
                      do {
                        if (((int)fVar17 >> 0x10 & 0xffffU) <= (uint)*puVar8) {
                          local_114 = (ushort)((uint)fVar17 >> 0x10);
                          *puVar8 = local_114;
                          *(ushort *)((int)puVar8 + iVar5) =
                               (ushort)((uint)((int)((int)fVar19 >> 6 & 0x3e000U |
                                                    (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                               (ushort)((uint)fVar3 >> 8) & 0xf800;
                        }
                        puVar8 = puVar8 + 1;
                        fVar3 = (float)((int)fVar3 + (int)local_dc[6]);
                        fVar12 = (float)((int)fVar12 + (int)local_dc[5]);
                        fVar19 = (float)((int)fVar19 + (int)local_dc[2]);
                        fVar17 = (float)((int)fVar17 + (int)local_dc[3]);
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                    break;
                  case 8:
                    local_128 = iVar5 - iVar6;
                    iVar5 = local_e4 + iVar6 * 2;
                    puVar8 = (ushort *)(param_1 + iVar6 * 2);
                    local_148 = (ushort *)local_110[3];
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_128 = -local_128;
                        fVar3 = local_110[6];
                        fVar17 = local_110[5];
                        puVar13 = puVar8 + -1;
                        fVar12 = local_110[2];
                        do {
                          fVar3 = (float)((int)fVar3 - (int)local_dc[6]);
                          fVar17 = (float)((int)fVar17 - (int)local_dc[5]);
                          fVar12 = (float)((int)fVar12 - (int)local_dc[2]);
                          local_148 = (ushort *)((int)local_148 - (int)local_dc[3]);
                          *(short *)((iVar5 - (int)puVar8) + 2 + (int)(puVar13 + -1)) =
                               (short)((uint)local_148 >> 0x10);
                          *puVar13 = (ushort)((uint)((int)((int)fVar12 >> 6 & 0x3e000U |
                                                          (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                     (ushort)((uint)fVar3 >> 8) & 0xf800;
                          local_128 = local_128 + -1;
                          puVar13 = puVar13 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      fVar3 = local_110[6];
                      fVar17 = local_110[5];
                      fVar12 = local_110[2];
                      puVar13 = puVar8;
                      do {
                        *(short *)((int)puVar13 + (iVar5 - (int)puVar8)) =
                             (short)((uint)local_148 >> 0x10);
                        *puVar13 = (ushort)((uint)((int)((int)fVar12 >> 6 & 0x3e000U |
                                                        (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                   (ushort)((uint)fVar3 >> 8) & 0xf800;
                        fVar3 = (float)((int)fVar3 + (int)local_dc[6]);
                        fVar17 = (float)((int)fVar17 + (int)local_dc[5]);
                        fVar12 = (float)((int)fVar12 + (int)local_dc[2]);
                        local_148 = (ushort *)((int)local_148 + (int)local_dc[3]);
                        local_128 = local_128 - 1;
                        puVar13 = puVar13 + 1;
                      } while (local_128 != 0);
                    }
                    break;
                  case 0x10:
                    iVar7 = (int)local_134 >> 0x10;
                    iVar6 = local_e4 + iVar7 * 2;
                    local_128 = iVar5 - iVar7;
                    puVar8 = (ushort *)((int)local_130 + iVar7 * 2);
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        iVar6 = iVar6 - (int)puVar8;
                        local_128 = -local_128;
                        fVar3 = local_110[6];
                        fVar17 = local_110[3];
                        fVar12 = local_110[5];
                        fVar19 = local_110[2];
                        do {
                          puVar8 = puVar8 + -1;
                          fVar3 = (float)((int)fVar3 - (int)local_dc[6]);
                          fVar12 = (float)((int)fVar12 - (int)local_dc[5]);
                          fVar19 = (float)((int)fVar19 - (int)local_dc[2]);
                          fVar17 = (float)((int)fVar17 - (int)local_dc[3]);
                          if (((int)fVar17 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)(iVar6 + (int)puVar8)) {
                            *puVar8 = (ushort)((uint)((int)((int)fVar19 >> 6 & 0x3e000U |
                                                           (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                                      (ushort)((uint)fVar3 >> 8) & 0xf800;
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      iVar6 = iVar6 - (int)puVar8;
                      fVar3 = local_110[6];
                      fVar17 = local_110[3];
                      fVar12 = local_110[5];
                      fVar19 = local_110[2];
                      do {
                        if (((int)fVar17 >> 0x10 & 0xffffU) <=
                            (uint)*(ushort *)((int)puVar8 + iVar6)) {
                          *puVar8 = (ushort)((uint)((int)((int)fVar19 >> 6 & 0x3e000U |
                                                         (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                                    (ushort)((uint)fVar3 >> 8) & 0xf800;
                        }
                        puVar8 = puVar8 + 1;
                        fVar3 = (float)((int)fVar3 + (int)local_dc[6]);
                        fVar12 = (float)((int)fVar12 + (int)local_dc[5]);
                        fVar19 = (float)((int)fVar19 + (int)local_dc[2]);
                        fVar17 = (float)((int)fVar17 + (int)local_dc[3]);
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                    break;
                  case 0x18:
                    local_128 = iVar5 - iVar6;
                    puVar8 = (ushort *)(param_1 + iVar6 * 2);
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        iVar5 = -local_128;
                        fVar3 = local_110[6];
                        fVar17 = local_110[5];
                        fVar12 = local_110[2];
                        do {
                          puVar8 = puVar8 + -1;
                          fVar3 = (float)((int)fVar3 - (int)local_dc[6]);
                          fVar12 = (float)((int)fVar12 - (int)local_dc[2]);
                          fVar17 = (float)((int)fVar17 - (int)local_dc[5]);
                          *puVar8 = (ushort)((uint)((int)((int)fVar12 >> 6 & 0x3e000U |
                                                         (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                    (ushort)((uint)fVar3 >> 8) & 0xf800;
                          iVar5 = iVar5 + -1;
                        } while (iVar5 != 0);
                      }
                    }
                    else {
                      fVar3 = local_110[6];
                      fVar17 = local_110[5];
                      fVar12 = local_110[2];
                      if (0 < (int)local_128) {
                        do {
                          *puVar8 = (ushort)((uint)((int)((int)fVar12 >> 6 & 0x3e000U |
                                                         (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                    (ushort)((uint)fVar3 >> 8) & 0xf800;
                          local_128 = local_128 - 1;
                          fVar3 = (float)((int)fVar3 + (int)local_dc[6]);
                          fVar17 = (float)((int)fVar17 + (int)local_dc[5]);
                          puVar8 = puVar8 + 1;
                          fVar12 = (float)((int)fVar12 + (int)local_dc[2]);
                        } while (local_128 != 0);
                      }
                    }
                  }
                }
                else if (local_64 == 0) {
                  if (local_98 == 0x18) {
                    local_128 = iVar5 - iVar6;
                    local_11c = (short *)(param_1 + iVar6 * 2);
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_128 = -local_128;
                        do {
                          local_11c = local_11c + -1;
                          fVar3 = (float)((int)fVar3 - (int)local_dc[1]);
                          local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                          sVar2 = *(short *)(param_3 +
                                            ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                  (uint)fVar3 & 0xff0000) >> 8) * 2);
                          if (((param_9 & 4) == 0) || (sVar2 != 0)) {
                            *local_11c = sVar2;
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      do {
                        sVar2 = *(short *)(param_3 +
                                          ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                (uint)fVar3 & 0xff0000) >> 8) * 2);
                        if (((param_9 & 4) == 0) || (sVar2 != 0)) {
                          *local_11c = sVar2;
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                        fVar3 = (float)((int)fVar3 + (int)local_dc[1]);
                        local_11c = local_11c + 1;
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                  else {
                    local_138 = local_110[3];
                    local_b0 = local_dc[1];
                    local_128 = iVar5 - iVar6;
                    puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                    param_1 = param_1 + iVar6 * 2;
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_b4 = param_1 - (int)puVar8;
                        local_128 = -local_128;
                        do {
                          puVar8 = puVar8 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                          fVar3 = (float)((int)fVar3 - (int)local_dc[1]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 - (int)local_dc[3]);
                          }
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)) &&
                             ((sVar2 = *(short *)(param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar3 & 0xff0000) >> 8) * 2),
                              (param_9 & 4) == 0 || (sVar2 != 0)))) {
                            if ((uVar9 & 2) == 0) {
                              *puVar8 = (ushort)((uint)local_138 >> 0x10);
                            }
                            *(short *)(local_b4 + (int)puVar8) = sVar2;
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      local_b4 = param_1 - (int)puVar8;
                      do {
                        if ((((uVar9 & 1) != 0) ||
                            (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)) &&
                           ((sVar2 = *(short *)(param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)fVar3 & 0xff0000) >> 8) * 2),
                            (param_9 & 4) == 0 || (sVar2 != 0)))) {
                          if ((uVar9 & 2) == 0) {
                            *puVar8 = (ushort)((uint)local_138 >> 0x10);
                          }
                          *(short *)(local_b4 + (int)puVar8) = sVar2;
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                        fVar3 = (float)((int)fVar3 + (int)local_dc[1]);
                        if ((uVar9 & 3) != 3) {
                          local_138 = (float)((int)local_138 + (int)local_dc[3]);
                        }
                        puVar8 = puVar8 + 1;
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                }
                else {
                  iVar7 = (int)local_110[6] >> 0x13;
                  iVar15 = (int)local_110[5] >> 0x13;
                  iVar10 = (int)local_110[2] >> 0x13;
                  if (local_98 == 0) {
                    if ((param_9 & 0x102) == 0x102) {
                      local_a4 = (float)(param_9 & 4);
                      local_140 = (ushort *)local_110[1];
                      local_148 = (ushort *)local_110[0];
                      local_144 = (ushort *)local_110[3];
                      puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                      local_128 = iVar5 - iVar6;
                      param_1 = param_1 + iVar6 * 2;
                      if ((int)local_128 < 0) {
                        if (0x7fffffff < local_128) {
                          local_b4 = param_1 - (int)puVar8;
                          local_128 = -local_128;
                          do {
                            puVar8 = puVar8 + -1;
                            local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                            local_140 = (ushort *)((int)local_140 - (int)local_dc[1]);
                            local_144 = (ushort *)((int)local_144 - (int)local_dc[3]);
                            if (((int)local_144 >> 0x10 & 0xffffU) <= (uint)*puVar8) {
                              uVar1 = *(ushort *)
                                       (param_3 +
                                       ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                             (uint)local_140 & 0xff0000) >> 8) * 2);
                              uVar16 = (uint)uVar1;
                              if ((local_a4 == 0.0) || (uVar16 != 0)) {
                                local_11c._0_2_ = (ushort)((uint)local_144 >> 0x10);
                                *puVar8 = (ushort)local_11c;
                                *(short *)(local_b4 + (int)puVar8) =
                                     (short)(((uVar16 & 0x7e0) * iVar15 & 0xfc00 |
                                              (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                             (uVar1 & 0xf800) * iVar7 & 0x1f0000) >> 5);
                              }
                            }
                            local_128 = local_128 + -1;
                          } while (local_128 != 0);
                        }
                      }
                      else if (0 < (int)local_128) {
                        local_b4 = param_1 - (int)puVar8;
                        do {
                          if (((int)local_144 >> 0x10 & 0xffffU) <= (uint)*puVar8) {
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                           (uint)local_140 & 0xff0000) >> 8) * 2);
                            uVar16 = (uint)uVar1;
                            if ((local_a4 == 0.0) || (uVar16 != 0)) {
                              local_11c._0_2_ = (ushort)((uint)local_144 >> 0x10);
                              *puVar8 = (ushort)local_11c;
                              *(short *)(local_b4 + (int)puVar8) =
                                   (short)(((uVar16 & 0x7e0) * iVar15 & 0xfc00 |
                                            (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                           (uVar1 & 0xf800) * iVar7 & 0x1f0000) >> 5);
                            }
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                          local_140 = (ushort *)((int)local_140 + (int)local_dc[1]);
                          puVar8 = puVar8 + 1;
                          local_144 = (ushort *)((int)local_144 + (int)local_dc[3]);
                          local_128 = local_128 - 1;
                        } while (local_128 != 0);
                      }
                    }
                    else {
                      local_a4 = (float)(param_9 & 4);
                      local_140 = (ushort *)local_110[3];
                      local_b0 = local_dc[1];
                      local_e8 = local_dc[3];
                      local_128 = iVar5 - iVar6;
                      puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                      param_1 = param_1 + iVar6 * 2;
                      if ((int)local_128 < 0) {
                        if (0x7fffffff < local_128) {
                          param_1 = param_1 - (int)puVar8;
                          local_128 = -local_128;
                          fVar17 = local_110[2];
                          do {
                            puVar8 = puVar8 + -1;
                            local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                            fVar3 = (float)((int)fVar3 - (int)local_dc[1]);
                            local_140 = (ushort *)((int)local_140 - (int)local_dc[3]);
                            fVar17 = (float)((int)fVar17 - (int)local_dc[2]);
                            if ((((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar8) &&
                               ((uVar16 = (uint)*(ushort *)
                                                 (param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar3 & 0xff0000) >> 8) * 2),
                                local_a4 == 0.0 || (uVar16 != 0)))) {
                              *puVar8 = (ushort)((uint)local_140 >> 0x10);
                              uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                       ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                              *(short *)(param_1 + (int)puVar8) =
                                   (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_128 = local_128 + -1;
                          } while (local_128 != 0);
                        }
                      }
                      else if (0 < (int)local_128) {
                        param_1 = param_1 - (int)puVar8;
                        fVar17 = local_110[2];
                        do {
                          if ((((int)local_140 >> 0x10 & 0xffffU) <= (uint)*puVar8) &&
                             ((uVar16 = (uint)*(ushort *)
                                               (param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)fVar3 & 0xff0000) >> 8) * 2),
                              local_a4 == 0.0 || (uVar16 != 0)))) {
                            *puVar8 = (ushort)((uint)local_140 >> 0x10);
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                     ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                            *(short *)((int)puVar8 + param_1) =
                                 (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                          fVar17 = (float)((int)fVar17 + (int)local_dc[2]);
                          fVar3 = (float)((int)fVar3 + (int)local_dc[1]);
                          local_140 = (ushort *)((int)local_140 + (int)local_dc[3]);
                          puVar8 = puVar8 + 1;
                          local_128 = local_128 - 1;
                        } while (local_128 != 0);
                      }
                    }
                  }
                  else if ((param_9 & 0x102) == 0x102) {
                    local_a4 = (float)(param_9 & 4);
                    local_140 = (ushort *)local_110[1];
                    local_138 = local_110[3];
                    local_148 = (ushort *)local_110[0];
                    puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                    local_128 = iVar5 - iVar6;
                    param_1 = param_1 + iVar6 * 2;
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_b4 = uVar9 & 1;
                        param_1 = param_1 - (int)puVar8;
                        local_128 = -local_128;
                        do {
                          puVar8 = puVar8 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                          local_140 = (ushort *)((int)local_140 - (int)local_dc[1]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 - (int)local_dc[3]);
                          }
                          if ((local_b4 != 0) ||
                             (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)) {
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                           (uint)local_140 & 0xff0000) >> 8) * 2);
                            uVar16 = (uint)uVar1;
                            if ((local_a4 == 0.0) || (uVar16 != 0)) {
                              if ((uVar9 & 2) == 0) {
                                *puVar8 = (ushort)((uint)local_138 >> 0x10);
                              }
                              *(short *)(param_1 + (int)puVar8) =
                                   (short)(((uVar16 & 0x7e0) * iVar15 & 0xfc00 |
                                            (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                           (uVar1 & 0xf800) * iVar7 & 0x1f0000) >> 5);
                            }
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      local_b4 = uVar9 & 1;
                      param_1 = param_1 - (int)puVar8;
                      do {
                        if ((local_b4 != 0) || (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)
                           ) {
                          uVar1 = *(ushort *)
                                   (param_3 +
                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                         (uint)local_140 & 0xff0000) >> 8) * 2);
                          uVar16 = (uint)uVar1;
                          if ((local_a4 == 0.0) || (uVar16 != 0)) {
                            if ((uVar9 & 2) == 0) {
                              *puVar8 = (ushort)((uint)local_138 >> 0x10);
                            }
                            *(short *)(param_1 + (int)puVar8) =
                                 (short)(((uVar16 & 0x7e0) * iVar15 & 0xfc00 |
                                          (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                         (uVar1 & 0xf800) * iVar7 & 0x1f0000) >> 5);
                          }
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                        local_140 = (ushort *)((int)local_140 + (int)local_dc[1]);
                        if ((uVar9 & 3) != 3) {
                          local_138 = (float)((int)local_138 + (int)local_dc[3]);
                        }
                        puVar8 = puVar8 + 1;
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                  else {
                    local_e8 = local_dc[3];
                    local_138 = local_110[3];
                    local_b0 = local_dc[1];
                    local_128 = iVar5 - iVar6;
                    puVar8 = (ushort *)(local_e4 + iVar6 * 2);
                    param_1 = param_1 + iVar6 * 2;
                    local_a4 = fVar3;
                    if ((int)local_128 < 0) {
                      if (0x7fffffff < local_128) {
                        local_b4 = param_1 - (int)puVar8;
                        local_128 = -local_128;
                        fVar17 = local_110[2];
                        do {
                          puVar8 = puVar8 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_dc[0]);
                          fVar3 = (float)((int)fVar3 - (int)local_dc[1]);
                          fVar17 = (float)((int)fVar17 - (int)local_dc[2]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 - (int)local_dc[3]);
                          }
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)) &&
                             ((uVar16 = (uint)*(ushort *)
                                               (param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)fVar3 & 0xff0000) >> 8) * 2),
                              (param_9 & 4) == 0 || (uVar16 != 0)))) {
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                     ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                            if ((uVar9 & 2) == 0) {
                              *puVar8 = (ushort)((uint)local_138 >> 0x10);
                            }
                            *(short *)(local_b4 + (int)puVar8) =
                                 (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          }
                          local_128 = local_128 + -1;
                        } while (local_128 != 0);
                      }
                    }
                    else if (0 < (int)local_128) {
                      local_b4 = param_1 - (int)puVar8;
                      fVar17 = local_110[2];
                      do {
                        if ((((uVar9 & 1) != 0) ||
                            (((int)local_138 >> 0x10 & 0xffffU) <= (uint)*puVar8)) &&
                           ((uVar16 = (uint)*(ushort *)
                                             (param_3 +
                                             ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                   (uint)fVar3 & 0xff0000) >> 8) * 2),
                            (param_9 & 4) == 0 || (uVar16 != 0)))) {
                          uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                   ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                          if ((uVar9 & 2) == 0) {
                            *puVar8 = (ushort)((uint)local_138 >> 0x10);
                          }
                          *(short *)(local_b4 + (int)puVar8) =
                               (short)((uVar16 >> 0x10 | uVar16) >> 5);
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_dc[0]);
                        fVar3 = (float)((int)fVar3 + (int)local_dc[1]);
                        fVar17 = (float)((int)fVar17 + (int)local_dc[2]);
                        if ((uVar9 & 3) != 3) {
                          local_138 = (float)((int)local_138 + (int)local_dc[3]);
                        }
                        puVar8 = puVar8 + 1;
                        local_128 = local_128 - 1;
                      } while (local_128 != 0);
                    }
                  }
                }
                uVar11 = (int)local_134 + local_68;
                local_f0 = local_f0 + local_120;
                iVar5 = 0;
                do {
                  if ((local_90 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
                    local_88[iVar5] = afStack_60[iVar5] + local_88[iVar5];
                  }
                  iVar5 = iVar5 + 1;
                } while (iVar5 < 8);
                param_1 = (int)local_130 + param_4 * 2;
                if (local_94 != 0) {
                  local_e4 = local_e4 + param_5 * 2;
                }
                local_e0 = local_e0 + 1;
                local_134 = (float)uVar11;
                local_130 = (float)param_1;
              } while (local_e0 < local_ec);
            }
            local_13c = local_13c + 1;
          } while ((int)local_13c < 2);
          return;
        }
      }
    }
  }
  else {
    if (uVar18 != 0) {
      local_88[0] = param_6[6] * _DAT_0056e4c4;
      local_110[0] = param_7[6] * _DAT_0056e4c4;
      local_dc[0] = param_8[6] * _DAT_0056e4c4;
      local_88[1] = param_6[7] * _DAT_0056e4c4;
      local_110[1] = param_7[7] * _DAT_0056e4c4;
      local_dc[1] = param_8[7] * _DAT_0056e4c4;
    }
    if ((uVar16 & 0x60) != 0) {
      local_88[6] = (float)((uint)param_6[4] & 0xff0000) * _DAT_0056e4d4;
      local_110[6] = (float)((uint)param_7[4] & 0xff0000) * _DAT_0056e4d4;
      local_dc[6] = (float)((uint)param_8[4] & 0xff0000) * _DAT_0056e4d4;
      local_88[5] = (float)((uint)param_6[4] & 0xff00) * _DAT_0056e118;
      uStack_a8 = 0;
      local_110[5] = (float)((uint)param_7[4] & 0xff00) * _DAT_0056e118;
      local_ac = (uint)param_8[4] & 0xff00;
      local_dc[5] = (float)local_ac * _DAT_0056e118;
    }
    if ((uVar16 & 4) != 0) {
      local_88[2] = (float)((uint)param_6[4] & 0xff);
      uStack_a8 = 0;
      local_110[2] = (float)((uint)param_7[4] & 0xff);
      local_ac = (uint)param_8[4] & 0xff;
      local_dc[2] = (float)local_ac;
    }
    if ((uVar11 & 0x10) != 0 || uVar14 != 0) {
      local_88[4] = _DAT_0056e0c4 - (float)((uint)param_6[4] >> 0x18);
      uStack_a8 = 0;
      local_110[4] = _DAT_0056e0c4 - (float)((uint)param_7[4] >> 0x18);
      local_ac = (uint)param_8[4] >> 0x18;
      local_dc[4] = _DAT_0056e0c4 - (float)local_ac;
    }
    if (local_94 != 0) {
      local_88[3] = param_6[2] * _DAT_0056e1cc;
      local_110[3] = param_7[2] * _DAT_0056e1cc;
      local_dc[3] = param_8[2] * _DAT_0056e1cc;
    }
    if (param_6[1] != param_8[1]) {
      fVar3 = (param_7[1] - param_6[1]) / (param_8[1] - param_6[1]);
      fVar17 = (*param_8 - *param_6) * fVar3 + *param_6;
      if (fVar17 != *param_7) {
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_60[iVar5] = (local_dc[iVar5] - local_88[iVar5]) * fVar3 + local_88[iVar5];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        fVar3 = *param_7;
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_40[iVar5] =
                 (local_110[iVar5] - afStack_60[iVar5]) * (_DAT_0056e008 / (fVar3 - fVar17));
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        fVar3 = param_8[1];
        fVar17 = param_6[1];
        local_9c = *param_6;
        local_a0 = *param_7;
        if (param_7[1] != param_6[1]) {
          local_144 = (ushort *)((*param_7 - *param_6) / (param_7[1] - param_6[1]));
        }
        if (param_8[1] != param_7[1]) {
          local_130 = (*param_8 - *param_7) / (param_8[1] - param_7[1]);
        }
        iVar5 = 0;
        do {
          if ((uVar16 & 1 << ((byte)iVar5 & 0x1f)) != 0) {
            afStack_60[iVar5] =
                 (local_dc[iVar5] - local_88[iVar5]) * (_DAT_0056e008 / (fVar3 - fVar17));
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        iVar5 = __ftol();
        local_11c = (short *)__ftol();
        local_8c = __ftol();
        if (local_8c != iVar5) {
          iVar6 = 0;
          fVar3 = (float)iVar5 - (param_6[1] - _DAT_0056e158);
          do {
            if ((uVar16 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
              local_88[iVar6] = fVar3 * afStack_60[iVar6] + local_88[iVar6];
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < 8);
          local_ec = param_2;
          local_9c = fVar3 * (float)local_144 + local_9c + _DAT_0056e4d0;
          local_a0 = ((float)(int)local_11c - (param_7[1] - _DAT_0056e158)) * local_130 + local_a0 +
                     _DAT_0056e4d0;
          uVar11 = __ftol();
          local_e4 = uVar11;
          local_ac = __ftol();
          local_a4 = (float)__ftol();
          local_68 = __ftol();
          iVar6 = 0;
          do {
            if ((uVar16 & 1 << ((byte)iVar6 & 0x1f)) != 0) {
              fVar3 = (float)__ftol();
              local_dc[iVar6] = fVar3;
              fVar3 = (float)__ftol();
              local_110[iVar6] = fVar3;
              uVar4 = __ftol();
              auStack_20[iVar6] = uVar4;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < 8);
          if (local_94 != 0) {
            local_ec = param_2 + iVar5 * param_5 * 2;
          }
          local_128 = 0;
          fVar3 = local_dc[0];
          fVar17 = local_dc[1];
          local_f0 = param_1 + iVar5 * param_4 * 2;
          local_b4 = iVar5;
          do {
            if (local_128 == 0) {
              local_e0 = __ftol();
              iVar5 = local_f0;
              local_138 = local_dc[3];
            }
            else {
              local_e0 = __ftol();
              local_11c = (short *)local_8c;
              iVar5 = local_f0;
              local_138 = local_dc[3];
              local_a4 = (float)local_68;
            }
            for (; local_f0 = iVar5, local_dc[3] = local_138, (int)local_b4 < (int)local_11c;
                local_b4 = local_b4 + 1) {
              uStack_b8 = 0;
              local_148 = (ushort *)0x0;
              local_bc = ((uVar11 & 0xffff0000) - uVar11) + 0xffff;
              do {
                if ((local_90 & 1 << ((byte)local_148 & 0x1f)) != 0) {
                  fVar3 = (float)__ftol();
                  local_dc[(int)local_148] = fVar3;
                  local_138 = local_dc[3];
                  fVar3 = local_dc[0];
                  fVar17 = local_dc[1];
                }
                local_148 = (ushort *)((int)local_148 + 1);
              } while ((int)local_148 < 8);
              iVar6 = local_e0 >> 0x10;
              if (param_3 == 0) {
                if (local_98 < 0x19) {
                  iVar5 = (int)local_e4 >> 0x10;
                  switch(local_98) {
                  case 0:
                    if ((param_9 & 0x80) == 0) {
                      local_138 = local_dc[4];
                      local_144 = (ushort *)local_dc[3];
                      local_134 = local_dc[2];
                      local_13c = iVar6 - iVar5;
                      iVar6 = local_ec + iVar5 * 2;
                      puVar8 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          local_13c = -local_13c;
                          fVar3 = local_dc[6];
                          fVar17 = local_dc[5];
                          do {
                            puVar8 = puVar8 + -1;
                            fVar17 = (float)((int)fVar17 - (int)local_110[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[6]);
                            local_134 = (float)((int)local_134 - (int)local_110[2]);
                            local_144 = (ushort *)((int)local_144 - (int)local_110[3]);
                            local_138 = (float)((int)local_138 - (int)local_110[4]);
                            if (((int)local_144 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar6 + (int)puVar8)) {
                              uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                       ((int)local_138 >> 0x13) & 0xfc1f03e0;
                              *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_144 >> 0x10);
                              *puVar8 = ((ushort)((uint)((int)((int)local_134 >> 6 & 0x3e000U |
                                                              (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                        (ushort)((uint)fVar3 >> 8) & 0xf800) +
                                        (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)puVar8;
                        fVar3 = local_dc[6];
                        fVar17 = local_dc[5];
                        fVar12 = local_dc[3];
                        do {
                          if (((int)fVar12 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)puVar8 + iVar6)) {
                            uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                     ((int)local_138 >> 0x13) & 0xfc1f03e0;
                            *(short *)((int)puVar8 + iVar6) = (short)((uint)fVar12 >> 0x10);
                            *puVar8 = ((ushort)((uint)((int)((int)local_134 >> 6 & 0x3e000U |
                                                            (uint)fVar17 & 0xfc0000) >> 5) >> 8) |
                                      (ushort)((uint)fVar3 >> 8) & 0xf800) +
                                      (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          }
                          fVar17 = (float)((int)fVar17 + (int)local_110[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[6]);
                          local_134 = (float)((int)local_134 + (int)local_110[2]);
                          puVar8 = puVar8 + 1;
                          fVar12 = (float)((int)fVar12 + (int)local_110[3]);
                          local_138 = (float)((int)local_138 + (int)local_110[4]);
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                    else {
                      local_134 = local_dc[2];
                      local_138 = local_dc[5];
                      local_13c = iVar6 - iVar5;
                      iVar6 = local_ec + iVar5 * 2;
                      local_144 = (ushort *)local_dc[3];
                      puVar8 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          local_13c = -local_13c;
                          fVar3 = local_dc[6];
                          fVar17 = local_dc[3];
                          do {
                            puVar8 = puVar8 + -1;
                            local_138 = (float)((int)local_138 - (int)local_110[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[6]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[3]);
                            local_134 = (float)((int)local_134 - (int)local_110[2]);
                            if (((int)fVar17 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar6 + (int)puVar8)) {
                              uVar11 = (int)((int)((int)local_134 >> 6 & 0x3e000U |
                                                  (uint)local_138 & 0xfc0000) >> 5 |
                                            (uint)fVar3 & 0xf80000) >> 8;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *(short *)(iVar6 + (int)puVar8) = (short)((uint)fVar17 >> 0x10);
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)puVar8;
                        fVar3 = local_dc[6];
                        do {
                          if (((int)local_144 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)puVar8 + iVar6)) {
                            uVar11 = (int)((int)((int)local_134 >> 6 & 0x3e000U |
                                                (uint)local_138 & 0xfc0000) >> 5 |
                                          (uint)fVar3 & 0xf80000) >> 8;
                            uVar16 = *puVar8 + uVar11;
                            uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *(short *)((int)puVar8 + iVar6) = (short)((uint)local_144 >> 0x10);
                            *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          }
                          fVar3 = (float)((int)fVar3 + (int)local_110[6]);
                          local_138 = (float)((int)local_138 + (int)local_110[5]);
                          local_144 = (ushort *)((int)local_144 + (int)local_110[3]);
                          local_134 = (float)((int)local_134 + (int)local_110[2]);
                          puVar8 = puVar8 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                    break;
                  case 8:
                    if ((param_9 & 0x80) == 0) {
                      local_138 = local_dc[4];
                      local_134 = local_dc[3];
                      local_13c = iVar6 - iVar5;
                      iVar6 = local_ec + iVar5 * 2;
                      puVar8 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          local_13c = -local_13c;
                          fVar3 = local_dc[2];
                          puVar13 = puVar8 + -1;
                          fVar17 = local_dc[6];
                          fVar12 = local_dc[5];
                          do {
                            fVar17 = (float)((int)fVar17 - (int)local_110[6]);
                            fVar12 = (float)((int)fVar12 - (int)local_110[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                            local_134 = (float)((int)local_134 - (int)local_110[3]);
                            local_138 = (float)((int)local_138 - (int)local_110[4]);
                            uVar16 = ((*puVar13 & 0x7e0) << 0x10 | *puVar13 & 0x7e0f81f) *
                                     ((int)local_138 >> 0x13) & 0xfc1f03e0;
                            *(short *)((iVar6 - (int)puVar8) + 2 + (int)(puVar13 + -1)) =
                                 (short)((uint)local_134 >> 0x10);
                            *puVar13 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                             (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                                       (ushort)((uint)fVar17 >> 8) & 0xf800) +
                                       (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            local_13c = local_13c + -1;
                            puVar13 = puVar13 + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        fVar3 = local_dc[2];
                        puVar13 = puVar8;
                        fVar17 = local_dc[6];
                        fVar12 = local_dc[5];
                        do {
                          uVar16 = ((*puVar13 & 0x7e0) << 0x10 | *puVar13 & 0x7e0f81f) *
                                   ((int)local_138 >> 0x13) & 0xfc1f03e0;
                          *(short *)((iVar6 - (int)puVar8) + -2 + (int)(puVar13 + 1)) =
                               (short)((uint)local_134 >> 0x10);
                          *puVar13 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                           (uint)fVar12 & 0xfc0000) >> 5) >> 8) |
                                     (ushort)((uint)fVar17 >> 8) & 0xf800) +
                                     (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          fVar17 = (float)((int)fVar17 + (int)local_110[6]);
                          fVar12 = (float)((int)fVar12 + (int)local_110[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                          local_134 = (float)((int)local_134 + (int)local_110[3]);
                          local_138 = (float)((int)local_138 + (int)local_110[4]);
                          local_13c = local_13c - 1;
                          puVar13 = puVar13 + 1;
                        } while (local_13c != 0);
                      }
                    }
                    else {
                      local_134 = local_dc[3];
                      local_13c = iVar6 - iVar5;
                      iVar6 = local_ec + iVar5 * 2;
                      local_140 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)local_140;
                          local_13c = -local_13c;
                          fVar3 = local_dc[5];
                          fVar17 = local_dc[2];
                          fVar12 = local_dc[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar17 = (float)((int)fVar17 - (int)local_110[2]);
                            local_134 = (float)((int)local_134 - (int)local_110[3]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[5]);
                            fVar12 = (float)((int)fVar12 - (int)local_110[6]);
                            uVar11 = (int)((int)((int)fVar17 >> 6 & 0x3e000U |
                                                (uint)fVar3 & 0xfc0000) >> 5 |
                                          (uint)fVar12 & 0xf80000) >> 8;
                            uVar16 = *local_140 + uVar11;
                            uVar11 = (uVar16 ^ *local_140 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *(short *)(iVar6 + (int)local_140) = (short)((uint)local_134 >> 0x10);
                            *local_140 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)local_140;
                        fVar3 = local_dc[5];
                        fVar17 = local_dc[2];
                        fVar12 = local_dc[6];
                        do {
                          uVar11 = (int)((int)((int)fVar17 >> 6 & 0x3e000U | (uint)fVar3 & 0xfc0000)
                                         >> 5 | (uint)fVar12 & 0xf80000) >> 8;
                          uVar16 = *local_140 + uVar11;
                          uVar11 = (uVar16 ^ *local_140 ^ uVar11) & 0x10820;
                          sVar2 = (short)uVar11;
                          *(short *)((int)local_140 + iVar6) = (short)((uint)local_134 >> 0x10);
                          *local_140 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          fVar12 = (float)((int)fVar12 + (int)local_110[6]);
                          fVar17 = (float)((int)fVar17 + (int)local_110[2]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[5]);
                          local_134 = (float)((int)local_134 + (int)local_110[3]);
                          local_140 = local_140 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                    break;
                  case 0x10:
                    if ((param_9 & 0x80) == 0) {
                      local_134 = local_dc[3];
                      iVar7 = local_ec + iVar5 * 2;
                      local_13c = iVar6 - iVar5;
                      local_148 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar7 = iVar7 - (int)local_148;
                          local_13c = -local_13c;
                          fVar3 = local_dc[2];
                          fVar17 = local_dc[4];
                          fVar12 = local_dc[6];
                          fVar19 = local_dc[5];
                          do {
                            local_148 = local_148 + -1;
                            fVar12 = (float)((int)fVar12 - (int)local_110[6]);
                            fVar19 = (float)((int)fVar19 - (int)local_110[5]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                            local_134 = (float)((int)local_134 - (int)local_110[3]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[4]);
                            if (((int)local_134 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar7 + (int)local_148)) {
                              uVar16 = ((*local_148 & 0x7e0) << 0x10 | *local_148 & 0x7e0f81f) *
                                       ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                              *local_148 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                                 (uint)fVar19 & 0xfc0000) >> 5) >> 8
                                                    ) | (ushort)((uint)fVar12 >> 8) & 0xf800) +
                                           (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar7 = iVar7 - (int)local_148;
                        fVar3 = local_dc[2];
                        fVar17 = local_dc[4];
                        fVar12 = local_dc[6];
                        fVar19 = local_dc[5];
                        do {
                          if (((int)local_134 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)local_148 + iVar7)) {
                            uVar16 = ((*local_148 & 0x7e0) << 0x10 | *local_148 & 0x7e0f81f) *
                                     ((int)fVar17 >> 0x13) & 0xfc1f03e0;
                            *local_148 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                               (uint)fVar19 & 0xfc0000) >> 5) >> 8)
                                         | (ushort)((uint)fVar12 >> 8) & 0xf800) +
                                         (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          }
                          fVar12 = (float)((int)fVar12 + (int)local_110[6]);
                          fVar19 = (float)((int)fVar19 + (int)local_110[5]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                          local_134 = (float)((int)local_134 + (int)local_110[3]);
                          fVar17 = (float)((int)fVar17 + (int)local_110[4]);
                          local_148 = local_148 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                    else {
                      local_134 = local_dc[3];
                      local_13c = iVar6 - iVar5;
                      iVar6 = local_ec + iVar5 * 2;
                      local_148 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)local_148;
                          local_13c = -local_13c;
                          fVar3 = local_dc[3];
                          fVar17 = local_dc[5];
                          fVar12 = local_dc[2];
                          fVar19 = local_dc[6];
                          do {
                            local_148 = local_148 + -1;
                            fVar19 = (float)((int)fVar19 - (int)local_110[6]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[5]);
                            fVar12 = (float)((int)fVar12 - (int)local_110[2]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[3]);
                            if (((int)fVar3 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)(iVar6 + (int)local_148)) {
                              uVar11 = (int)((int)((int)fVar12 >> 6 & 0x3e000U |
                                                  (uint)fVar17 & 0xfc0000) >> 5 |
                                            (uint)fVar19 & 0xf80000) >> 8;
                              uVar16 = *local_148 + uVar11;
                              uVar11 = (uVar16 ^ *local_148 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *local_148 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)local_148;
                        fVar3 = local_dc[5];
                        fVar17 = local_dc[2];
                        fVar12 = local_dc[6];
                        do {
                          if (((int)local_134 >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)((int)local_148 + iVar6)) {
                            uVar11 = (int)((int)((int)fVar17 >> 6 & 0x3e000U |
                                                (uint)fVar3 & 0xfc0000) >> 5 |
                                          (uint)fVar12 & 0xf80000) >> 8;
                            uVar16 = *local_148 + uVar11;
                            uVar11 = (uVar16 ^ *local_148 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *local_148 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          }
                          fVar12 = (float)((int)fVar12 + (int)local_110[6]);
                          fVar17 = (float)((int)fVar17 + (int)local_110[2]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[5]);
                          local_134 = (float)((int)local_134 + (int)local_110[3]);
                          local_148 = local_148 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                    break;
                  case 0x18:
                    if ((param_9 & 0x80) == 0) {
                      local_13c = iVar6 - iVar5;
                      local_140 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          local_13c = -local_13c;
                          fVar3 = local_dc[2];
                          fVar17 = local_dc[5];
                          fVar12 = local_dc[4];
                          fVar19 = local_dc[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar19 = (float)((int)fVar19 - (int)local_110[6]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                            fVar12 = (float)((int)fVar12 - (int)local_110[4]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[5]);
                            uVar16 = ((*local_140 & 0x7e0) << 0x10 | *local_140 & 0x7e0f81f) *
                                     ((int)fVar12 >> 0x13) & 0xfc1f03e0;
                            *local_140 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                               (uint)fVar17 & 0xfc0000) >> 5) >> 8)
                                         | (ushort)((uint)fVar19 >> 8) & 0xf800) +
                                         (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else {
                        fVar3 = local_dc[2];
                        fVar17 = local_dc[5];
                        fVar12 = local_dc[4];
                        fVar19 = local_dc[6];
                        if (0 < (int)local_13c) {
                          do {
                            uVar16 = ((*local_140 & 0x7e0) << 0x10 | *local_140 & 0x7e0f81f) *
                                     ((int)fVar12 >> 0x13) & 0xfc1f03e0;
                            *local_140 = ((ushort)((uint)((int)((int)fVar3 >> 6 & 0x3e000U |
                                                               (uint)fVar17 & 0xfc0000) >> 5) >> 8)
                                         | (ushort)((uint)fVar19 >> 8) & 0xf800) +
                                         (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            local_140 = local_140 + 1;
                            local_13c = local_13c - 1;
                            fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[5]);
                            fVar12 = (float)((int)fVar12 + (int)local_110[4]);
                            fVar19 = (float)((int)fVar19 + (int)local_110[6]);
                          } while (local_13c != 0);
                        }
                      }
                    }
                    else {
                      local_13c = iVar6 - iVar5;
                      local_140 = (ushort *)(local_f0 + iVar5 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          local_13c = -local_13c;
                          fVar3 = local_dc[5];
                          fVar17 = local_dc[2];
                          fVar12 = local_dc[6];
                          do {
                            local_140 = local_140 + -1;
                            fVar17 = (float)((int)fVar17 - (int)local_110[2]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[5]);
                            fVar12 = (float)((int)fVar12 - (int)local_110[6]);
                            uVar11 = (int)((int)((int)fVar17 >> 6 & 0x3e000U |
                                                (uint)fVar3 & 0xfc0000) >> 5 |
                                          (uint)fVar12 & 0xf80000) >> 8;
                            uVar16 = *local_140 + uVar11;
                            uVar11 = (uVar16 ^ *local_140 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *local_140 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else {
                        fVar3 = local_dc[5];
                        fVar17 = local_dc[2];
                        fVar12 = local_dc[6];
                        if (0 < (int)local_13c) {
                          do {
                            uVar11 = (int)((int)((int)fVar17 >> 6 & 0x3e000U |
                                                (uint)fVar3 & 0xfc0000) >> 5 |
                                          (uint)fVar12 & 0xf80000) >> 8;
                            uVar16 = *local_140 + uVar11;
                            uVar11 = (uVar16 ^ *local_140 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *local_140 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            local_140 = local_140 + 1;
                            local_13c = local_13c - 1;
                            fVar3 = (float)((int)fVar3 + (int)local_110[5]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[2]);
                            fVar12 = (float)((int)fVar12 + (int)local_110[6]);
                          } while (local_13c != 0);
                        }
                      }
                    }
                  }
                }
              }
              else {
                iVar7 = (int)uVar11 >> 0x10;
                local_148 = (ushort *)fVar3;
                local_144 = (ushort *)fVar17;
                if (local_64 == 0) {
                  local_dc[2] = 2.3418052e-38;
                  local_110[2] = 0.0;
                  if ((param_9 & 0x80) == 0) {
                    if ((param_9 & 0x200) == 0) {
                      local_b0 = local_110[3];
                      local_12c = iVar6 - iVar7;
                      iVar6 = local_ec + iVar7 * 2;
                      puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                      if ((int)local_12c < 0) {
                        if (0x7fffffff < local_12c) {
                          iVar6 = iVar6 - (int)puVar8;
                          local_12c = -local_12c;
                          fVar3 = local_dc[4];
                          do {
                            puVar8 = puVar8 + -1;
                            local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                            local_144 = (ushort *)((int)local_144 - (int)local_110[1]);
                            if ((uVar9 & 3) != 3) {
                              local_138 = (float)((int)local_138 - (int)local_110[3]);
                            }
                            fVar3 = (float)((int)fVar3 - (int)local_110[4]);
                            if ((((uVar9 & 1) != 0) ||
                                (((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                               ((uVar16 = (uint)*(ushort *)
                                                 (param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)local_144 & 0xff0000) >> 8) * 2),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) * 0x1f &
                                       0xfc1f03e0;
                              uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                       ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                              if ((uVar9 & 2) == 0) {
                                *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                              }
                              *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                        (short)((uVar11 >> 0x10 | uVar11) >> 5);
                            }
                            local_12c = local_12c + -1;
                          } while (local_12c != 0);
                        }
                      }
                      else if (0 < (int)local_12c) {
                        iVar6 = iVar6 - (int)puVar8;
                        fVar3 = local_dc[4];
                        do {
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)((int)puVar8 + iVar6))) &&
                             ((uVar16 = (uint)*(ushort *)
                                               (param_3 +
                                               ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                     (uint)local_144 & 0xff0000) >> 8) * 2),
                              (param_9 & 4) == 0 || (uVar16 != 0)))) {
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) * 0x1f &
                                     0xfc1f03e0;
                            uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                     ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                            if ((uVar9 & 2) == 0) {
                              *(short *)((int)puVar8 + iVar6) = (short)((uint)local_138 >> 0x10);
                            }
                            *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                      (short)((uVar11 >> 0x10 | uVar11) >> 5);
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                          local_144 = (ushort *)((int)local_144 + (int)local_110[1]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 + (int)local_110[3]);
                          }
                          fVar3 = (float)((int)fVar3 + (int)local_110[4]);
                          puVar8 = puVar8 + 1;
                          local_12c = local_12c - 1;
                        } while (local_12c != 0);
                      }
                    }
                    else {
                      local_144 = (ushort *)local_dc[4];
                      local_138 = local_dc[3];
                      local_e8 = local_110[4];
                      local_b0 = local_110[1];
                      iVar5 = local_ec + iVar7 * 2;
                      local_12c = iVar6 - iVar7;
                      puVar8 = (ushort *)(local_f0 + iVar7 * 2);
                      if ((int)local_12c < 0) {
                        if (0x7fffffff < local_12c) {
                          iVar5 = iVar5 - (int)puVar8;
                          local_12c = -local_12c;
                          do {
                            puVar8 = puVar8 + -1;
                            fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                            local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                            if ((uVar9 & 3) != 3) {
                              local_138 = (float)((int)local_138 - (int)local_110[3]);
                            }
                            local_144 = (ushort *)((int)local_144 - (int)local_110[4]);
                            if ((((uVar9 & 1) != 0) ||
                                (((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar5 + (int)puVar8))) &&
                               ((uVar16 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar17 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar11 = (uVar16 & 0x7e0f81f) * 0x1f & 0xfc1f03e0;
                              uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                       (((uVar16 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0xfc1f03e0;
                              if ((uVar9 & 2) == 0) {
                                *(short *)(iVar5 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                              }
                              *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                        (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_12c = local_12c + -1;
                          } while (local_12c != 0);
                        }
                      }
                      else if (0 < (int)local_12c) {
                        iVar5 = iVar5 - (int)puVar8;
                        do {
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar5 + (int)puVar8))) &&
                             ((uVar16 = *(uint *)(param_3 +
                                                 ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar17 & 0xff0000) >> 8) * 4),
                              (param_9 & 4) == 0 || (uVar16 != 0)))) {
                            uVar11 = (uVar16 & 0x7e0f81f) * 0x1f & 0xfc1f03e0;
                            uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                     (((uVar16 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^ 0x1f000000)
                                     >> 0x18) & 0xfc1f03e0;
                            if ((uVar9 & 2) == 0) {
                              *(short *)(iVar5 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                            }
                            *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                      (short)((uVar16 >> 0x10 | uVar16) >> 5);
                          }
                          local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                          fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 + (int)local_110[3]);
                          }
                          local_144 = (ushort *)((int)local_144 + (int)local_110[4]);
                          puVar8 = puVar8 + 1;
                          local_12c = local_12c - 1;
                        } while (local_12c != 0);
                      }
                    }
                  }
                  else {
                    local_b0 = local_110[1];
                    local_12c = iVar6 - iVar7;
                    iVar6 = local_ec + iVar7 * 2;
                    puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                    if ((int)local_12c < 0) {
                      if (0x7fffffff < local_12c) {
                        iVar6 = iVar6 - (int)puVar8;
                        local_12c = -local_12c;
                        do {
                          puVar8 = puVar8 + -1;
                          local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                          fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 - (int)local_110[3]);
                          }
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                             (uVar16 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar17 & 0xff0000) >> 8) * 2), uVar16 != 0
                             )) {
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) * 0x1f &
                                     0xfc1f03e0;
                            uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                            uVar16 = *puVar8 + uVar11;
                            uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            if ((uVar9 & 2) == 0) {
                              *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                            }
                            *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          }
                          local_12c = local_12c + -1;
                        } while (local_12c != 0);
                      }
                    }
                    else if (0 < (int)local_12c) {
                      iVar6 = iVar6 - (int)puVar8;
                      do {
                        if ((((uVar9 & 1) != 0) ||
                            (((int)local_138 >> 0x10 & 0xffffU) <=
                             (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                           (uVar16 = (uint)*(ushort *)
                                            (param_3 +
                                            ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                  (uint)fVar17 & 0xff0000) >> 8) * 2), uVar16 != 0))
                        {
                          uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) * 0x1f &
                                   0xfc1f03e0;
                          uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                          uVar16 = *puVar8 + uVar11;
                          uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                          sVar2 = (short)uVar11;
                          if ((uVar9 & 2) == 0) {
                            *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                          }
                          *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                        }
                        local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                        fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                        if ((uVar9 & 3) != 3) {
                          local_138 = (float)((int)local_138 + (int)local_110[3]);
                        }
                        puVar8 = puVar8 + 1;
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
                        local_134 = local_dc[4];
                        local_130 = local_dc[2];
                        local_e8 = local_110[1];
                        local_13c = iVar6 - iVar7;
                        iVar6 = local_ec + iVar7 * 2;
                        puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                        if ((int)local_13c < 0) {
                          if (0x7fffffff < local_13c) {
                            iVar6 = iVar6 - (int)puVar8;
                            local_13c = -local_13c;
                            do {
                              puVar8 = puVar8 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                              local_130 = (float)((int)local_130 - (int)local_110[2]);
                              local_138 = (float)((int)local_138 - (int)local_110[3]);
                              local_134 = (float)((int)local_134 - (int)local_110[4]);
                              if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                 ((uVar16 = (uint)*(ushort *)
                                                   (param_3 +
                                                   ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar17 & 0xff0000) >> 8) * 2),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar1 = *puVar8;
                                uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                         ((int)local_130 >> 0x13) & 0xfc1f03e0;
                                *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                                uVar11 = ((uVar1 & 0x7e0) << 0x10 | uVar1 & 0x7e0f81f) *
                                         ((int)local_134 >> 0x13) & 0xfc1f03e0;
                                *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                          (short)((uVar11 >> 0x10 | uVar11) >> 5);
                              }
                              local_13c = local_13c + -1;
                            } while (local_13c != 0);
                          }
                        }
                        else if (0 < (int)local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          do {
                            if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)puVar8 + iVar6)) &&
                               ((uVar16 = (uint)*(ushort *)
                                                 (param_3 +
                                                 ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                       (uint)fVar17 & 0xff0000) >> 8) * 2),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar1 = *puVar8;
                              uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                       ((int)local_130 >> 0x13) & 0xfc1f03e0;
                              *(short *)((int)puVar8 + iVar6) = (short)((uint)local_138 >> 0x10);
                              uVar11 = ((uVar1 & 0x7e0) << 0x10 | uVar1 & 0x7e0f81f) *
                                       ((int)local_134 >> 0x13) & 0xfc1f03e0;
                              *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                        (short)((uVar11 >> 0x10 | uVar11) >> 5);
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                            local_130 = (float)((int)local_130 + (int)local_110[2]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                            puVar8 = puVar8 + 1;
                            local_138 = (float)((int)local_138 + (int)local_110[3]);
                            local_134 = (float)((int)local_134 + (int)local_110[4]);
                            local_13c = local_13c - 1;
                          } while (local_13c != 0);
                        }
                      }
                      else {
                        local_144 = (ushort *)local_dc[4];
                        local_e8 = local_110[3];
                        local_130 = local_dc[2];
                        local_13c = iVar6 - iVar7;
                        iVar6 = local_ec + iVar7 * 2;
                        puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                        if ((int)local_13c < 0) {
                          if (0x7fffffff < local_13c) {
                            iVar6 = iVar6 - (int)puVar8;
                            local_13c = -local_13c;
                            do {
                              puVar8 = puVar8 + -1;
                              local_134 = (float)((int)local_134 - (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                              local_130 = (float)((int)local_130 - (int)local_110[2]);
                              local_138 = (float)((int)local_138 - (int)local_110[3]);
                              local_144 = (ushort *)((int)local_144 - (int)local_110[4]);
                              if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                 ((uVar16 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar11 = ((int)local_130 >> 0x13) * (uVar16 & 0x7e0f81f) &
                                         0xfc1f03e0;
                                uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                         (((uVar16 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0xfc1f03e0;
                                *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                                *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                          (short)((uVar16 >> 0x10 | uVar16) >> 5);
                              }
                              local_13c = local_13c + -1;
                            } while (local_13c != 0);
                          }
                        }
                        else if (0 < (int)local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          do {
                            if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)puVar8 + iVar6)) &&
                               ((uVar16 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar17 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar11 = ((int)local_130 >> 0x13) * (uVar16 & 0x7e0f81f) & 0xfc1f03e0;
                              uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                       (((uVar16 >> 0x1b) * ((uint)local_144 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0xfc1f03e0;
                              *(short *)((int)puVar8 + iVar6) = (short)((uint)local_138 >> 0x10);
                              *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                        (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_134 = (float)((int)local_134 + (int)local_110[0]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                            local_130 = (float)((int)local_130 + (int)local_110[2]);
                            local_138 = (float)((int)local_138 + (int)local_110[3]);
                            local_144 = (ushort *)((int)local_144 + (int)local_110[4]);
                            puVar8 = puVar8 + 1;
                            local_13c = local_13c - 1;
                          } while (local_13c != 0);
                        }
                      }
                    }
                    else {
                      local_13c = iVar6 - iVar7;
                      iVar6 = local_ec + iVar7 * 2;
                      puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                      local_130 = local_138;
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          local_13c = -local_13c;
                          fVar3 = local_dc[2];
                          local_144 = (ushort *)fVar17;
                          do {
                            puVar8 = puVar8 + -1;
                            local_134 = (float)((int)local_134 - (int)local_110[0]);
                            local_144 = (ushort *)((int)local_144 - (int)local_110[1]);
                            local_130 = (float)((int)local_130 - (int)local_110[3]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                            if ((((int)local_130 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                               (uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                               (uint)local_144 & 0xff0000) >> 8) * 2), uVar1 != 0))
                            {
                              uVar16 = ((uint)(uVar1 & 0x7e0) << 0x10 | uVar1 & 0x7e0f81f) *
                                       ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                              uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_130 >> 0x10);
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)puVar8;
                        fVar3 = local_dc[2];
                        local_144 = (ushort *)fVar17;
                        do {
                          if ((((int)local_130 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                             (uVar16 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_134 >> 0x10 & 0xff) << 8 |
                                                    (uint)local_144 & 0xff0000) >> 8) * 2),
                             uVar16 != 0)) {
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                     ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                            uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                            uVar16 = *puVar8 + uVar11;
                            uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_130 >> 0x10);
                            *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          }
                          local_134 = (float)((int)local_134 + (int)local_110[0]);
                          local_144 = (ushort *)((int)local_144 + (int)local_110[1]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                          local_130 = (float)((int)local_130 + (int)local_110[3]);
                          puVar8 = puVar8 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                  }
                  else {
                    iVar15 = (int)local_dc[6] >> 0x13;
                    iVar20 = (int)local_dc[5] >> 0x13;
                    iVar10 = (int)local_dc[2] >> 0x13;
                    if (local_98 == 0x10) {
                      local_148 = (ushort *)local_138;
                      if ((param_9 & 0x80) == 0) {
                        if ((param_9 & 0x200) == 0) {
                          if ((param_9 & 0x40) == 0) {
                            local_e8 = local_110[1];
                            local_13c = iVar6 - iVar7;
                            iVar6 = local_ec + iVar7 * 2;
                            puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                            if ((int)local_13c < 0) {
                              if (0x7fffffff < local_13c) {
                                iVar6 = iVar6 - (int)puVar8;
                                local_13c = -local_13c;
                                fVar3 = local_dc[2];
                                fVar12 = local_dc[4];
                                do {
                                  puVar8 = puVar8 + -1;
                                  local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                                  fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                                  fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                                  local_148 = (ushort *)((int)local_148 - (int)local_110[3]);
                                  fVar12 = (float)((int)fVar12 - (int)local_110[4]);
                                  if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                       (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                     ((uVar16 = (uint)*(ushort *)
                                                       (param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar17 & 0xff0000) >> 8) * 2),
                                      (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                    uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                             ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                                    uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                             ((int)fVar12 >> 0x13) & 0xfc1f03e0;
                                    *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                              (short)((uVar11 >> 0x10 | uVar11) >> 5);
                                  }
                                  local_13c = local_13c + -1;
                                } while (local_13c != 0);
                              }
                            }
                            else if (0 < (int)local_13c) {
                              iVar6 = iVar6 - (int)puVar8;
                              fVar3 = local_dc[2];
                              fVar12 = local_dc[4];
                              do {
                                if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                   ((uVar16 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                  uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                           ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                                  uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                           ((int)fVar12 >> 0x13) & 0xfc1f03e0;
                                  *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                            (short)((uVar11 >> 0x10 | uVar11) >> 5);
                                }
                                local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                                fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                                fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                                fVar12 = (float)((int)fVar12 + (int)local_110[4]);
                                local_148 = (ushort *)((int)local_148 + (int)local_110[3]);
                                puVar8 = puVar8 + 1;
                                local_13c = local_13c - 1;
                              } while (local_13c != 0);
                            }
                          }
                          else {
                            local_e8 = local_110[1];
                            local_13c = iVar6 - iVar7;
                            iVar6 = local_ec + iVar7 * 2;
                            puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                            if ((int)local_13c < 0) {
                              if (0x7fffffff < local_13c) {
                                iVar6 = iVar6 - (int)puVar8;
                                local_13c = -local_13c;
                                fVar3 = local_dc[2];
                                do {
                                  puVar8 = puVar8 + -1;
                                  local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                                  fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                                  fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                                  local_138 = (float)((int)local_138 - (int)local_110[3]);
                                  if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                       (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                     ((uVar16 = (uint)*(ushort *)
                                                       (param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar17 & 0xff0000) >> 8) * 2),
                                      (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                    uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                             ((int)fVar3 >> 0x13) & 0x7c0f01e0;
                                    *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                              (*puVar8 >> 1 & 0x7bef);
                                  }
                                  local_13c = local_13c + -1;
                                } while (local_13c != 0);
                              }
                            }
                            else if (0 < (int)local_13c) {
                              iVar6 = iVar6 - (int)puVar8;
                              fVar3 = local_dc[2];
                              do {
                                if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)((int)puVar8 + iVar6)) &&
                                   ((uVar16 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                  uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                           ((int)fVar3 >> 0x13) & 0x7c0f01e0;
                                  *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                            (*puVar8 >> 1 & 0x7bef);
                                }
                                local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                                fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                                local_138 = (float)((int)local_138 + (int)local_110[3]);
                                fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                                puVar8 = puVar8 + 1;
                                local_13c = local_13c - 1;
                              } while (local_13c != 0);
                            }
                          }
                        }
                        else {
                          local_134 = local_dc[4];
                          local_130 = local_dc[2];
                          local_e8 = local_110[0];
                          local_13c = iVar6 - iVar7;
                          iVar6 = local_ec + iVar7 * 2;
                          puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                          if ((int)local_13c < 0) {
                            if (0x7fffffff < local_13c) {
                              iVar6 = iVar6 - (int)puVar8;
                              local_13c = -local_13c;
                              do {
                                puVar8 = puVar8 + -1;
                                local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                                fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                                local_130 = (float)((int)local_130 - (int)local_110[2]);
                                local_138 = (float)((int)local_138 - (int)local_110[3]);
                                local_134 = (float)((int)local_134 - (int)local_110[4]);
                                if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                   ((uVar16 = *(uint *)(param_3 +
                                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8
                                                             | (uint)fVar17 & 0xff0000) >> 8) * 4),
                                    (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                  uVar11 = ((int)local_130 >> 0x13) * (uVar16 & 0x7e0f81f) &
                                           0xfc1f03e0;
                                  uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                           (((uVar16 >> 0x1b) * ((uint)local_134 ^ 0xffffff) ^
                                            0x1f000000) >> 0x18) & 0xfc1f03e0;
                                  *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                            (short)((uVar16 >> 0x10 | uVar16) >> 5);
                                }
                                local_13c = local_13c + -1;
                              } while (local_13c != 0);
                            }
                          }
                          else if (0 < (int)local_13c) {
                            iVar6 = iVar6 - (int)puVar8;
                            do {
                              if ((((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)((int)puVar8 + iVar6)) &&
                                 ((uVar16 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar11 = ((int)local_130 >> 0x13) * (uVar16 & 0x7e0f81f) &
                                         0xfc1f03e0;
                                uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                         (((uVar16 >> 0x1b) * ((uint)local_134 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0xfc1f03e0;
                                *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                          (short)((uVar16 >> 0x10 | uVar16) >> 5);
                              }
                              local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                              local_130 = (float)((int)local_130 + (int)local_110[2]);
                              local_138 = (float)((int)local_138 + (int)local_110[3]);
                              local_134 = (float)((int)local_134 + (int)local_110[4]);
                              puVar8 = puVar8 + 1;
                              local_13c = local_13c - 1;
                            } while (local_13c != 0);
                          }
                        }
                      }
                      else if ((param_9 & 0x102) == 0x102) {
                        local_e8 = local_110[1];
                        local_13c = iVar6 - iVar7;
                        iVar6 = local_ec + iVar7 * 2;
                        local_148 = (ushort *)(iVar5 + iVar7 * 2);
                        local_134 = local_138;
                        local_130 = fVar17;
                        if ((int)local_13c < 0) {
                          if (0x7fffffff < local_13c) {
                            iVar6 = iVar6 - (int)local_148;
                            local_13c = -local_13c;
                            do {
                              local_148 = local_148 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                              local_130 = (float)((int)local_130 - (int)local_110[1]);
                              local_134 = (float)((int)local_134 - (int)local_110[3]);
                              if (((int)local_134 >> 0x10 & 0xffffU) <=
                                  (uint)*(ushort *)(iVar6 + (int)local_148)) {
                                uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                               (uint)local_130 & 0xff0000) >> 8) * 2);
                                uVar16 = (uint)uVar1;
                                if (uVar16 != 0) {
                                  uVar11 = ((uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                            (uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                           (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5;
                                  uVar16 = *local_148 + uVar11;
                                  uVar11 = (uVar16 ^ *local_148 ^ uVar11) & 0x10820;
                                  sVar2 = (short)uVar11;
                                  *local_148 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                                }
                              }
                              local_13c = local_13c + -1;
                            } while (local_13c != 0);
                          }
                        }
                        else if (0 < (int)local_13c) {
                          iVar6 = iVar6 - (int)local_148;
                          do {
                            if (((int)local_134 >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)((int)local_148 + iVar6)) {
                              uVar1 = *(ushort *)
                                       (param_3 +
                                       ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                             (uint)local_130 & 0xff0000) >> 8) * 2);
                              uVar16 = (uint)uVar1;
                              if (uVar16 != 0) {
                                uVar11 = ((uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                          (uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                         (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5;
                                uVar16 = *local_148 + uVar11;
                                uVar11 = (uVar16 ^ *local_148 ^ uVar11) & 0x10820;
                                sVar2 = (short)uVar11;
                                *local_148 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                              }
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                            local_130 = (float)((int)local_130 + (int)local_110[1]);
                            local_134 = (float)((int)local_134 + (int)local_110[3]);
                            local_148 = local_148 + 1;
                            local_13c = local_13c - 1;
                          } while (local_13c != 0);
                        }
                      }
                      else {
                        local_e8 = local_110[1];
                        local_13c = iVar6 - iVar7;
                        iVar6 = local_ec + iVar7 * 2;
                        puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                        if ((int)local_13c < 0) {
                          if (0x7fffffff < local_13c) {
                            iVar6 = iVar6 - (int)puVar8;
                            local_13c = -local_13c;
                            fVar3 = local_dc[2];
                            do {
                              puVar8 = puVar8 + -1;
                              local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                              local_148 = (ushort *)((int)local_148 - (int)local_110[3]);
                              fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                              if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                                 (uVar16 = (uint)*(ushort *)
                                                  (param_3 +
                                                  ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                        (uint)fVar17 & 0xff0000) >> 8) * 2),
                                 uVar16 != 0)) {
                                uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                         ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                                uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                                uVar16 = *puVar8 + uVar11;
                                uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                                sVar2 = (short)uVar11;
                                *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                              }
                              local_13c = local_13c + -1;
                            } while (local_13c != 0);
                          }
                        }
                        else if (0 < (int)local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          fVar3 = local_dc[2];
                          do {
                            if ((((int)local_148 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar6 + (int)puVar8)) &&
                               (uVar16 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar17 & 0xff0000) >> 8) * 2),
                               uVar16 != 0)) {
                              uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                       ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                              uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                            fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                            local_148 = (ushort *)((int)local_148 + (int)local_110[3]);
                            puVar8 = puVar8 + 1;
                            local_13c = local_13c - 1;
                          } while (local_13c != 0);
                        }
                      }
                    }
                    else if ((param_9 & 0x19a) == 0x19a) {
                      local_e8 = local_110[1];
                      local_13c = iVar6 - iVar7;
                      puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          local_13c = -local_13c;
                          do {
                            puVar8 = puVar8 + -1;
                            local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                           (uint)fVar17 & 0xff0000) >> 8) * 2);
                            uVar16 = (uint)uVar1;
                            if (uVar16 != 0) {
                              uVar11 = ((uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                        (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                       (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else {
                        local_148 = (ushort *)fVar17;
                        if (0 < (int)local_13c) {
                          do {
                            uVar1 = *(ushort *)
                                     (param_3 +
                                     ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                           (uint)local_148 & 0xff0000) >> 8) * 2);
                            uVar16 = (uint)uVar1;
                            if (uVar16 != 0) {
                              uVar11 = ((uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                        (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                       (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            puVar8 = puVar8 + 1;
                            local_13c = local_13c - 1;
                            local_148 = (ushort *)((int)local_148 + (int)local_110[1]);
                            local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                          } while (local_13c != 0);
                        }
                      }
                    }
                    else if ((param_9 & 0x80) == 0) {
                      if ((param_9 & 0x200) == 0) {
                        if ((param_9 & 0x102) == 0x102) {
                          local_b0 = local_110[1];
                          iVar5 = local_ec + iVar7 * 2;
                          local_138 = local_dc[3];
                          puVar8 = (ushort *)(local_f0 + iVar7 * 2);
                          local_120 = iVar6 - iVar7;
                          if ((int)local_120 < 0) {
                            if (0x7fffffff < local_120) {
                              iVar5 = iVar5 - (int)puVar8;
                              local_120 = -local_120;
                              local_144 = (ushort *)fVar17;
                              do {
                                puVar8 = puVar8 + -1;
                                local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                                local_144 = (ushort *)((int)local_144 - (int)local_110[1]);
                                if ((uVar9 & 3) != 3) {
                                  local_138 = (float)((int)local_138 - (int)local_110[3]);
                                }
                                if (((uVar9 & 1) != 0) ||
                                   (((int)local_138 >> 0x10 & 0xffffU) <=
                                    (uint)*(ushort *)(iVar5 + (int)puVar8))) {
                                  uVar1 = *(ushort *)
                                           (param_3 +
                                           ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                 (uint)local_144 & 0xff0000) >> 8) * 2);
                                  uVar16 = (uint)uVar1;
                                  if (((param_9 & 4) == 0) || (uVar16 != 0)) {
                                    uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                             ((int)local_dc[4] >> 0x13) & 0xfc1f03e0;
                                    if ((uVar9 & 2) == 0) {
                                      *(short *)(iVar5 + (int)puVar8) =
                                           (short)((uint)local_138 >> 0x10);
                                    }
                                    *puVar8 = (short)(((uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                                       (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                                      (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5) +
                                              (short)((uVar11 >> 0x10 | uVar11) >> 5);
                                  }
                                }
                                local_120 = local_120 + -1;
                              } while (local_120 != 0);
                            }
                          }
                          else if (0 < (int)local_120) {
                            iVar5 = iVar5 - (int)puVar8;
                            local_144 = (ushort *)fVar17;
                            do {
                              if (((uVar9 & 1) != 0) ||
                                 (((int)local_138 >> 0x10 & 0xffffU) <=
                                  (uint)*(ushort *)((int)puVar8 + iVar5))) {
                                uVar1 = *(ushort *)
                                         (param_3 +
                                         ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                               (uint)local_144 & 0xff0000) >> 8) * 2);
                                uVar16 = (uint)uVar1;
                                if (((param_9 & 4) == 0) || (uVar16 != 0)) {
                                  uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                           ((int)local_dc[4] >> 0x13) & 0xfc1f03e0;
                                  if ((uVar9 & 2) == 0) {
                                    *(short *)((int)puVar8 + iVar5) =
                                         (short)((uint)local_138 >> 0x10);
                                  }
                                  *puVar8 = (short)(((uVar16 & 0x7e0) * iVar20 & 0xfc00 |
                                                     (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                                    (uVar1 & 0xf800) * iVar15 & 0x1f0000) >> 5) +
                                            (short)((uVar11 >> 0x10 | uVar11) >> 5);
                                }
                              }
                              local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                              local_144 = (ushort *)((int)local_144 + (int)local_110[1]);
                              if ((uVar9 & 3) != 3) {
                                local_138 = (float)((int)local_138 + (int)local_110[3]);
                              }
                              puVar8 = puVar8 + 1;
                              local_120 = local_120 - 1;
                            } while (local_120 != 0);
                          }
                        }
                        else {
                          local_130 = local_dc[4];
                          local_e8 = local_110[3];
                          local_144 = (ushort *)local_dc[2];
                          local_b0 = local_110[1];
                          local_12c = iVar6 - iVar7;
                          iVar6 = local_ec + iVar7 * 2;
                          puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                          if ((int)local_12c < 0) {
                            if (0x7fffffff < local_12c) {
                              iVar6 = iVar6 - (int)puVar8;
                              local_12c = -local_12c;
                              do {
                                puVar8 = puVar8 + -1;
                                local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                                fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                                local_144 = (ushort *)((int)local_144 - (int)local_110[2]);
                                if ((uVar9 & 3) != 3) {
                                  local_138 = (float)((int)local_138 - (int)local_110[3]);
                                }
                                local_130 = (float)((int)local_130 - (int)local_110[4]);
                                if ((((uVar9 & 1) != 0) ||
                                    (((int)local_138 >> 0x10 & 0xffffU) <=
                                     (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                                   ((uVar16 = (uint)*(ushort *)
                                                     (param_3 +
                                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 2),
                                    (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                  uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                           ((int)local_144 >> 0x13) & 0xfc1f03e0;
                                  uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                           ((int)local_130 >> 0x13) & 0xfc1f03e0;
                                  if ((uVar9 & 2) == 0) {
                                    *(short *)(iVar6 + (int)puVar8) =
                                         (short)((uint)local_138 >> 0x10);
                                  }
                                  *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                            (short)((uVar11 >> 0x10 | uVar11) >> 5);
                                }
                                local_12c = local_12c + -1;
                              } while (local_12c != 0);
                            }
                          }
                          else if (0 < (int)local_12c) {
                            iVar6 = iVar6 - (int)puVar8;
                            do {
                              if ((((uVar9 & 1) != 0) ||
                                  (((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                                 ((uVar16 = (uint)*(ushort *)
                                                   (param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar17 & 0xff0000) >> 8) * 2),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                         ((int)local_144 >> 0x13) & 0xfc1f03e0;
                                uVar11 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                         ((int)local_130 >> 0x13) & 0xfc1f03e0;
                                if ((uVar9 & 2) == 0) {
                                  *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10)
                                  ;
                                }
                                *puVar8 = (short)((uVar16 >> 0x10 | uVar16) >> 5) +
                                          (short)((uVar11 >> 0x10 | uVar11) >> 5);
                              }
                              local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                              local_144 = (ushort *)((int)local_144 + (int)local_110[2]);
                              if ((uVar9 & 3) != 3) {
                                local_138 = (float)((int)local_138 + (int)local_110[3]);
                              }
                              local_130 = (float)((int)local_130 + (int)local_110[4]);
                              puVar8 = puVar8 + 1;
                              local_12c = local_12c - 1;
                            } while (local_12c != 0);
                          }
                        }
                      }
                      else if ((param_9 & 0x100) == 0) {
                        local_130 = local_dc[4];
                        local_e8 = local_110[3];
                        local_138 = local_dc[3];
                        local_144 = (ushort *)local_dc[2];
                        local_b0 = local_110[1];
                        iVar5 = local_ec + iVar7 * 2;
                        local_12c = iVar6 - iVar7;
                        puVar8 = (ushort *)(local_f0 + iVar7 * 2);
                        if ((int)local_12c < 0) {
                          if (0x7fffffff < local_12c) {
                            iVar5 = iVar5 - (int)puVar8;
                            local_12c = -local_12c;
                            do {
                              puVar8 = puVar8 + -1;
                              local_148 = (ushort *)((int)local_148 - (int)local_110[0]);
                              fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                              local_144 = (ushort *)((int)local_144 - (int)local_110[2]);
                              if ((uVar9 & 3) != 3) {
                                local_138 = (float)((int)local_138 - (int)local_110[3]);
                              }
                              local_130 = (float)((int)local_130 - (int)local_110[4]);
                              if ((((uVar9 & 1) != 0) ||
                                  (((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar5 + (int)puVar8))) &&
                                 ((uVar16 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                           (uint)fVar17 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar11 = ((int)local_144 >> 0x13) * (uVar16 & 0x7e0f81f) &
                                         0xfc1f03e0;
                                uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                         (((uVar16 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0xfc1f03e0;
                                if ((uVar9 & 2) == 0) {
                                  *(short *)(iVar5 + (int)puVar8) = (short)((uint)local_138 >> 0x10)
                                  ;
                                }
                                *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                          (short)((uVar16 >> 0x10 | uVar16) >> 5);
                              }
                              local_12c = local_12c + -1;
                            } while (local_12c != 0);
                          }
                        }
                        else if (0 < (int)local_12c) {
                          iVar5 = iVar5 - (int)puVar8;
                          do {
                            if ((((uVar9 & 1) != 0) ||
                                (((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar5 + (int)puVar8))) &&
                               ((uVar16 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_148 >> 0x10 & 0xff) << 8 |
                                                         (uint)fVar17 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar11 = ((int)local_144 >> 0x13) * (uVar16 & 0x7e0f81f) & 0xfc1f03e0;
                              uVar16 = ((*puVar8 & 0x7e0) << 0x10 | *puVar8 & 0x7e0f81f) *
                                       (((uVar16 >> 0x1b) * ((uint)local_130 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0xfc1f03e0;
                              if ((uVar9 & 2) == 0) {
                                *(short *)(iVar5 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                              }
                              *puVar8 = (short)((uVar11 >> 0x10 | uVar11) >> 5) +
                                        (short)((uVar16 >> 0x10 | uVar16) >> 5);
                            }
                            local_148 = (ushort *)((int)local_148 + (int)local_110[0]);
                            fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                            local_144 = (ushort *)((int)local_144 + (int)local_110[2]);
                            if ((uVar9 & 3) != 3) {
                              local_138 = (float)((int)local_138 + (int)local_110[3]);
                            }
                            local_130 = (float)((int)local_130 + (int)local_110[4]);
                            puVar8 = puVar8 + 1;
                            local_12c = local_12c - 1;
                          } while (local_12c != 0);
                        }
                      }
                      else {
                        local_148 = (ushort *)local_dc[4];
                        local_b0 = local_110[3];
                        local_138 = local_dc[3];
                        local_e8 = local_110[1];
                        iVar5 = local_ec + iVar7 * 2;
                        local_13c = iVar6 - iVar7;
                        local_144 = (ushort *)(local_f0 + iVar7 * 2);
                        local_134 = fVar17;
                        local_130 = fVar3;
                        if ((int)local_13c < 0) {
                          if (0x7fffffff < local_13c) {
                            iVar5 = iVar5 - (int)local_144;
                            local_13c = -local_13c;
                            do {
                              local_144 = local_144 + -1;
                              local_130 = (float)((int)local_130 - (int)local_110[0]);
                              local_134 = (float)((int)local_134 - (int)local_110[1]);
                              if ((uVar9 & 3) != 3) {
                                local_138 = (float)((int)local_138 - (int)local_110[3]);
                              }
                              local_148 = (ushort *)((int)local_148 - (int)local_110[4]);
                              if ((((uVar9 & 1) != 0) ||
                                  (((int)local_138 >> 0x10 & 0xffffU) <=
                                   (uint)*(ushort *)(iVar5 + (int)local_144))) &&
                                 ((uVar16 = *(uint *)(param_3 +
                                                     ((int)(((uint)local_130 >> 0x10 & 0xff) << 8 |
                                                           (uint)local_134 & 0xff0000) >> 8) * 4),
                                  (param_9 & 4) == 0 || (uVar16 != 0)))) {
                                uVar11 = ((*local_144 & 0x7e0) << 0x10 | *local_144 & 0x7e0f81f) *
                                         (((uVar16 >> 0x1b) * ((uint)local_148 ^ 0xffffff) ^
                                          0x1f000000) >> 0x18) & 0xfc1f03e0;
                                if ((uVar9 & 2) == 0) {
                                  *(short *)(iVar5 + (int)local_144) =
                                       (short)((uint)local_138 >> 0x10);
                                }
                                *local_144 = (short)(((uVar16 & 0x7e00000) * iVar20 >> 0x10 & 0xfc00
                                                      | (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                                     (uVar16 & 0xf800) * iVar15 & 0x1f0000) >> 5) +
                                             (short)((uVar11 >> 0x10 | uVar11) >> 5);
                              }
                              local_13c = local_13c + -1;
                            } while (local_13c != 0);
                          }
                        }
                        else if (0 < (int)local_13c) {
                          iVar5 = iVar5 - (int)local_144;
                          do {
                            if ((((uVar9 & 1) != 0) ||
                                (((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)((int)local_144 + iVar5))) &&
                               ((uVar16 = *(uint *)(param_3 +
                                                   ((int)(((uint)local_130 >> 0x10 & 0xff) << 8 |
                                                         (uint)local_134 & 0xff0000) >> 8) * 4),
                                (param_9 & 4) == 0 || (uVar16 != 0)))) {
                              uVar11 = ((*local_144 & 0x7e0) << 0x10 | *local_144 & 0x7e0f81f) *
                                       (((uVar16 >> 0x1b) * ((uint)local_148 ^ 0xffffff) ^
                                        0x1f000000) >> 0x18) & 0xfc1f03e0;
                              if ((uVar9 & 2) == 0) {
                                *(short *)((int)local_144 + iVar5) =
                                     (short)((uint)local_138 >> 0x10);
                              }
                              *local_144 = (short)(((uVar16 & 0x7e00000) * iVar20 >> 0x10 & 0xfc00 |
                                                    (uVar16 & 0x1f) * iVar10 & 0x3e0 |
                                                   (uVar16 & 0xf800) * iVar15 & 0x1f0000) >> 5) +
                                           (short)((uVar11 >> 0x10 | uVar11) >> 5);
                            }
                            local_130 = (float)((int)local_130 + (int)local_110[0]);
                            local_134 = (float)((int)local_134 + (int)local_110[1]);
                            if ((uVar9 & 3) != 3) {
                              local_138 = (float)((int)local_138 + (int)local_110[3]);
                            }
                            local_148 = (ushort *)((int)local_148 + (int)local_110[4]);
                            local_144 = local_144 + 1;
                            local_13c = local_13c - 1;
                          } while (local_13c != 0);
                        }
                      }
                    }
                    else {
                      local_e8 = local_110[1];
                      local_13c = iVar6 - iVar7;
                      iVar6 = local_ec + iVar7 * 2;
                      puVar8 = (ushort *)(iVar5 + iVar7 * 2);
                      if ((int)local_13c < 0) {
                        if (0x7fffffff < local_13c) {
                          iVar6 = iVar6 - (int)puVar8;
                          local_13c = -local_13c;
                          fVar3 = local_dc[2];
                          do {
                            puVar8 = puVar8 + -1;
                            local_144 = (ushort *)((int)local_144 - (int)local_110[0]);
                            fVar17 = (float)((int)fVar17 - (int)local_110[1]);
                            fVar3 = (float)((int)fVar3 - (int)local_110[2]);
                            if ((uVar9 & 3) != 3) {
                              local_138 = (float)((int)local_138 - (int)local_110[3]);
                            }
                            if ((((uVar9 & 1) != 0) ||
                                (((int)local_138 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                               (uVar16 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar17 & 0xff0000) >> 8) * 2),
                               uVar16 != 0)) {
                              uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                       ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                              uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                              uVar16 = *puVar8 + uVar11;
                              uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                              sVar2 = (short)uVar11;
                              if ((uVar9 & 2) == 0) {
                                *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                              }
                              *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                            }
                            local_13c = local_13c + -1;
                          } while (local_13c != 0);
                        }
                      }
                      else if (0 < (int)local_13c) {
                        iVar6 = iVar6 - (int)puVar8;
                        fVar3 = local_dc[2];
                        do {
                          if ((((uVar9 & 1) != 0) ||
                              (((int)local_138 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar6 + (int)puVar8))) &&
                             (uVar16 = (uint)*(ushort *)
                                              (param_3 +
                                              ((int)(((uint)local_144 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar17 & 0xff0000) >> 8) * 2), uVar16 != 0
                             )) {
                            uVar16 = ((uVar16 & 0x7e0) << 0x10 | uVar16 & 0x7e0f81f) *
                                     ((int)fVar3 >> 0x13) & 0xfc1f03e0;
                            uVar11 = (uVar16 >> 0x10 | uVar16) >> 5;
                            uVar16 = *puVar8 + uVar11;
                            uVar11 = (uVar16 ^ *puVar8 ^ uVar11) & 0x10820;
                            sVar2 = (short)uVar11;
                            if ((uVar9 & 2) == 0) {
                              *(short *)(iVar6 + (int)puVar8) = (short)((uint)local_138 >> 0x10);
                            }
                            *puVar8 = sVar2 - (short)(uVar11 >> 5) | (short)uVar16 - sVar2;
                          }
                          local_144 = (ushort *)((int)local_144 + (int)local_110[0]);
                          fVar17 = (float)((int)fVar17 + (int)local_110[1]);
                          fVar3 = (float)((int)fVar3 + (int)local_110[2]);
                          if ((uVar9 & 3) != 3) {
                            local_138 = (float)((int)local_138 + (int)local_110[3]);
                          }
                          puVar8 = puVar8 + 1;
                          local_13c = local_13c - 1;
                        } while (local_13c != 0);
                      }
                    }
                  }
                }
              }
              local_e0 = local_e0 + (int)local_a4;
              uVar11 = local_e4 + local_ac;
              iVar5 = 0;
              do {
                if ((1 << ((byte)iVar5 & 0x1f) & local_90) != 0) {
                  local_88[iVar5] = afStack_60[iVar5] + local_88[iVar5];
                }
                iVar5 = iVar5 + 1;
              } while (iVar5 < 8);
              if (local_94 != 0) {
                local_ec = local_ec + param_5 * 2;
              }
              fVar3 = local_dc[0];
              fVar17 = local_dc[1];
              iVar5 = local_f0 + param_4 * 2;
              local_e4 = uVar11;
              local_138 = local_dc[3];
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

