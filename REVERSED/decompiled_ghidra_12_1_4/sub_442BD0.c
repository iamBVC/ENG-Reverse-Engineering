/* sub_442BD0 @ 00442bd0   12166 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_442BD0(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6,
               int param_7,int param_8,undefined4 param_9,uint param_10)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  float fVar6;
  int iVar7;
  undefined4 uVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  float fVar14;
  int iVar15;
  float *pfVar16;
  uint uVar17;
  float fVar18;
  int iVar19;
  float fVar20;
  float *local_1dc;
  float *local_1d8;
  uint local_1d4;
  float local_1d0;
  uint local_1cc;
  float local_1c8;
  int local_1c4;
  ushort *local_1c0;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  ushort *local_1ac;
  int local_1a8;
  uint local_1a4;
  uint local_1a0;
  int local_198;
  uint local_194;
  int local_190;
  int local_184;
  float local_168 [8];
  ushort *local_148;
  undefined4 uStack_144;
  uint local_140;
  undefined4 uStack_13c;
  uint local_138;
  undefined4 uStack_134;
  uint local_130;
  undefined4 uStack_12c;
  uint local_128;
  undefined4 uStack_124;
  uint local_120;
  undefined4 uStack_11c;
  uint local_118;
  undefined4 uStack_114;
  uint local_110;
  undefined4 uStack_10c;
  int local_108 [8];
  float local_e8 [8];
  float local_c8 [8];
  float local_a8 [8];
  float afStack_88 [8];
  float afStack_68 [8];
  uint local_48;
  undefined4 uStack_44;
  float afStack_40 [8];
  undefined4 auStack_20 [8];
  
  iVar13 = 0;
  uVar17 = param_10 >> 1 & 0x180 | (param_10 & 0x40) << 3 | param_10 & 0x3f;
  if ((param_3 == 0) || (param_8 != 0)) {
    sub_445BF0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,0);
    return;
  }
  DAT_0057d850 = param_1;
  DAT_0057d864 = param_4 * 2;
  _DAT_0057d8a8 = param_2;
  DAT_0057d8bc = param_5 * 2;
  DAT_0057d8d4 = param_3;
  if (0x211 < uVar17) {
    switch(uVar17) {
    case 0x213:
    case 0x231:
    case 0x233:
      goto switchD_00444790_caseD_213;
    default:
switchD_00442c7b_caseD_2:
      if (param_7 < 1) {
        return;
      }
      param_6 = param_6 + 0x11;
      iVar15 = param_7;
      do {
        if (iVar15 < 3) {
          return;
        }
        if (param_6[-8] <= param_6[-0x10]) {
          if (param_6[-8] <= *param_6) {
            pfVar9 = param_6 + -9;
            if (param_6[-0x10] <= *param_6) {
              pfVar11 = param_6 + -0x11;
              goto LAB_00445aa6;
            }
            pfVar11 = param_6 + -1;
            pfVar12 = param_6 + -0x11;
          }
          else {
            pfVar9 = param_6 + -1;
            pfVar11 = param_6 + -9;
            pfVar12 = param_6 + -0x11;
          }
        }
        else if (*param_6 <= param_6[-8]) {
          if (*param_6 <= param_6[-0x10]) {
            pfVar9 = param_6 + -1;
            pfVar11 = param_6 + -0x11;
            pfVar12 = param_6 + -9;
          }
          else {
            pfVar9 = param_6 + -0x11;
            pfVar11 = param_6 + -1;
            pfVar12 = param_6 + -9;
          }
        }
        else {
          pfVar9 = param_6 + -0x11;
          pfVar11 = param_6 + -9;
LAB_00445aa6:
          pfVar12 = param_6 + -1;
        }
        sub_43CD60(param_1,param_2,param_3,param_4,param_5,pfVar9,pfVar11,pfVar12,uVar17);
        iVar13 = iVar13 + 3;
        iVar15 = iVar15 + -3;
        param_6 = param_6 + 0x18;
        if (param_7 <= iVar13) {
          return;
        }
      } while( true );
    case 0x215:
    case 0x217:
    case 0x235:
    case 0x237:
      local_184 = 0;
      if (param_7 < 1) {
        return;
      }
      local_1c0 = (ushort *)param_7;
      pfVar9 = param_6 + 0x11;
      do {
        if ((int)local_1c0 < 3) {
          return;
        }
        pfVar11 = param_6;
        if (pfVar9[-8] <= param_6[1]) {
          pfVar12 = param_6;
          if (pfVar9[-8] <= *pfVar9) {
            pfVar16 = pfVar9 + -9;
            if (param_6[1] <= *pfVar9) goto LAB_00445170;
            pfVar11 = pfVar9 + -1;
          }
          else {
            pfVar16 = pfVar9 + -1;
            pfVar11 = pfVar9 + -9;
          }
        }
        else {
          pfVar16 = param_6;
          if (*pfVar9 <= pfVar9[-8]) {
            if (*pfVar9 <= param_6[1]) {
              pfVar16 = pfVar9 + -1;
              pfVar12 = pfVar9 + -9;
            }
            else {
              pfVar12 = pfVar9 + -9;
              pfVar11 = pfVar9 + -1;
            }
          }
          else {
            pfVar11 = pfVar9 + -9;
LAB_00445170:
            pfVar12 = pfVar9 + -1;
          }
        }
        uStack_13c = 0;
        local_140 = (uint)pfVar16[4] & 0xff;
        uStack_11c = 0;
        local_168[0] = pfVar16[6] * _DAT_0056e4c4;
        local_a8[0] = pfVar11[6] * _DAT_0056e4c4;
        local_120 = (uint)pfVar11[4] & 0xff;
        local_130 = (uint)pfVar12[4] & 0xff;
        local_e8[0] = pfVar12[6] * _DAT_0056e4c4;
        iVar13 = 0;
        uStack_12c = 0;
        uStack_134 = 0;
        local_138 = (uint)pfVar16[4] >> 0x18;
        local_168[1] = pfVar16[7] * _DAT_0056e4c4;
        uStack_124 = 0;
        local_128 = (uint)pfVar11[4] >> 0x18;
        uStack_114 = 0;
        local_a8[1] = pfVar11[7] * _DAT_0056e4c4;
        local_118 = (uint)pfVar12[4] >> 0x18;
        local_e8[1] = pfVar12[7] * _DAT_0056e4c4;
        local_168[2] = (float)local_140;
        local_a8[2] = (float)local_120;
        local_e8[2] = (float)local_130;
        local_168[4] = _DAT_0056e0c4 - (float)local_138;
        local_a8[4] = _DAT_0056e0c4 - (float)local_128;
        local_e8[4] = _DAT_0056e0c4 - (float)local_118;
        local_168[3] = pfVar16[2] * _DAT_0056e1cc;
        local_a8[3] = pfVar11[2] * _DAT_0056e1cc;
        local_e8[3] = pfVar12[2] * _DAT_0056e1cc;
        if (pfVar16[1] != pfVar12[1]) {
          fVar6 = pfVar12[1];
          fVar14 = pfVar16[1];
          fVar20 = (pfVar11[1] - pfVar16[1]) / (fVar6 - fVar14);
          fVar18 = (*pfVar12 - *pfVar16) * fVar20 + *pfVar16;
          if (fVar18 != *pfVar11) {
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_40[iVar13] =
                     (local_e8[iVar13] - local_168[iVar13]) * fVar20 + local_168[iVar13];
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            fVar20 = *pfVar11;
            iVar13 = 0;
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_68[iVar13] =
                     (local_a8[iVar13] - afStack_40[iVar13]) * (_DAT_0056e008 / (fVar20 - fVar18));
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            iVar13 = 0;
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_88[iVar13] =
                     (local_e8[iVar13] - local_168[iVar13]) * (_DAT_0056e008 / (fVar6 - fVar14));
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            iVar13 = __ftol();
            local_1bc = __ftol();
            iVar15 = __ftol();
            if (iVar15 != iVar13) {
              fVar6 = pfVar16[1];
              iVar10 = 0;
              do {
                if ((1 << ((byte)iVar10 & 0x1f) & 0x1fU) != 0) {
                  local_168[iVar10] =
                       ((float)iVar13 - (fVar6 - _DAT_0056e158)) * afStack_88[iVar10] +
                       local_168[iVar10];
                }
                iVar10 = iVar10 + 1;
              } while (iVar10 < 8);
              local_1cc = __ftol();
              iVar10 = __ftol();
              local_1d4 = __ftol();
              iVar19 = __ftol();
              iVar7 = 0;
              do {
                if ((1 << ((byte)iVar7 & 0x1f) & 0x1fU) != 0) {
                  fVar6 = (float)__ftol();
                  local_c8[iVar7] = fVar6;
                  iVar2 = __ftol();
                  local_108[iVar7] = iVar2;
                  uVar8 = __ftol();
                  auStack_20[iVar7] = uVar8;
                }
                iVar7 = iVar7 + 1;
              } while (iVar7 < 8);
              local_1a8 = param_1 + iVar13 * param_4 * 2;
              local_194 = 0;
              local_1a4 = param_2 + iVar13 * param_5 * 2;
              do {
                if (local_194 == 0) {
                  local_1b8 = __ftol();
                }
                else {
                  local_1b8 = __ftol();
                  local_1d4 = iVar19;
                  local_1bc = iVar15;
                }
                if (iVar13 < local_1bc) {
                  local_190 = local_1bc - iVar13;
                  iVar13 = iVar13 + local_190;
                  do {
                    local_110 = ((local_1cc & 0xffff0000) - local_1cc) + 0xffff;
                    iVar7 = 0;
                    uStack_10c = 0;
                    do {
                      if ((1 << ((byte)iVar7 & 0x1f) & 0x1fU) != 0) {
                        fVar6 = (float)__ftol();
                        local_c8[iVar7] = fVar6;
                      }
                      iVar7 = iVar7 + 1;
                    } while (iVar7 < 8);
                    iVar2 = (int)local_1cc >> 0x10;
                    iVar7 = local_1a4 + iVar2 * 2;
                    local_1c8 = local_c8[0];
                    local_148 = (ushort *)(local_1a8 + iVar2 * 2);
                    local_1a0 = (local_1b8 >> 0x10) - iVar2;
                    local_1d0 = local_c8[3];
                    local_1dc = (float *)local_c8[1];
                    if ((int)local_1a0 < 0) {
                      if (0x7fffffff < local_1a0) {
                        local_1a0 = -local_1a0;
                        fVar6 = local_c8[3];
                        fVar14 = local_c8[4];
                        fVar20 = local_c8[1];
                        fVar18 = local_c8[2];
                        puVar4 = local_148;
                        do {
                          puVar4 = puVar4 + -1;
                          local_1c8 = (float)((int)local_1c8 - local_108[0]);
                          fVar20 = (float)((int)fVar20 - local_108[1]);
                          fVar18 = (float)((int)fVar18 - local_108[2]);
                          fVar6 = (float)((int)fVar6 - local_108[3]);
                          fVar14 = (float)((int)fVar14 - local_108[4]);
                          if ((((int)fVar6 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)((iVar7 - (int)local_148) + (int)puVar4)) &&
                             (uVar17 = *(uint *)(param_3 +
                                                ((int)(((uint)local_1c8 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar20 & 0xff0000) >> 8) * 4),
                             uVar17 != 0)) {
                            uVar5 = ((int)fVar18 >> 0x13) * (uVar17 & 0x3e07c1f) & 0x7c0f83e0;
                            uVar17 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                     (((uVar17 >> 0x1b) * ((uint)fVar14 ^ 0xffffff) ^ 0x1f000000) >>
                                     0x18) & 0x7c0f83e0;
                            *puVar4 = ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5)) +
                                      ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5));
                          }
                          local_1a0 = local_1a0 + -1;
                        } while (local_1a0 != 0);
                      }
                    }
                    else if (0 < (int)local_1a0) {
                      fVar6 = local_c8[4];
                      puVar4 = local_148;
                      fVar14 = local_c8[2];
                      do {
                        if ((((int)local_1d0 >> 0x10 & 0xffffU) <=
                             (uint)*(ushort *)((iVar7 - (int)local_148) + (int)puVar4)) &&
                           (uVar17 = *(uint *)(param_3 +
                                              ((int)(((uint)local_1c8 >> 0x10 & 0xff) << 8 |
                                                    (uint)local_1dc & 0xff0000) >> 8) * 4),
                           uVar17 != 0)) {
                          uVar5 = ((int)fVar14 >> 0x13) * (uVar17 & 0x3e07c1f) & 0x7c0f83e0;
                          uVar17 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                   (((uVar17 >> 0x1b) * ((uint)fVar6 ^ 0xffffff) ^ 0x1f000000) >>
                                   0x18) & 0x7c0f83e0;
                          *puVar4 = ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5)) +
                                    ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5));
                        }
                        local_1c8 = (float)((int)local_1c8 + local_108[0]);
                        fVar14 = (float)((int)fVar14 + local_108[2]);
                        local_1dc = (float *)((int)local_1dc + local_108[1]);
                        local_1d0 = (float)((int)local_1d0 + local_108[3]);
                        fVar6 = (float)((int)fVar6 + local_108[4]);
                        puVar4 = puVar4 + 1;
                        local_1a0 = local_1a0 - 1;
                      } while (local_1a0 != 0);
                    }
                    local_1cc = local_1cc + iVar10;
                    local_1b8 = local_1b8 + local_1d4;
                    iVar7 = 0;
                    do {
                      if ((1 << ((byte)iVar7 & 0x1f) & 0x1fU) != 0) {
                        local_168[iVar7] = afStack_88[iVar7] + local_168[iVar7];
                      }
                      iVar7 = iVar7 + 1;
                    } while (iVar7 < 8);
                    local_1a8 = local_1a8 + param_4 * 2;
                    local_1a4 = local_1a4 + param_5 * 2;
                    local_190 = local_190 + -1;
                  } while (local_190 != 0);
                }
                local_194 = local_194 + 1;
              } while ((int)local_194 < 2);
            }
          }
        }
        local_184 = local_184 + 1;
        pfVar9 = pfVar9 + 8;
        local_1c0 = (ushort *)((int)local_1c0 + -1);
        if (param_7 <= local_184) {
          return;
        }
      } while( true );
    }
  }
  if (uVar17 == 0x211) {
switchD_00444790_caseD_213:
    local_184 = 0;
    if (0 < param_7) {
      local_1bc = param_7;
      pfVar9 = param_6 + 0x11;
      while (2 < local_1bc) {
        pfVar11 = param_6;
        if (pfVar9[-8] <= param_6[1]) {
          pfVar12 = param_6;
          if (pfVar9[-8] <= *pfVar9) {
            pfVar16 = pfVar9 + -9;
            if (param_6[1] <= *pfVar9) goto LAB_00444840;
            pfVar11 = pfVar9 + -1;
          }
          else {
            pfVar16 = pfVar9 + -1;
            pfVar11 = pfVar9 + -9;
          }
        }
        else {
          pfVar16 = param_6;
          if (*pfVar9 <= pfVar9[-8]) {
            if (*pfVar9 <= param_6[1]) {
              pfVar16 = pfVar9 + -1;
              pfVar12 = pfVar9 + -9;
            }
            else {
              pfVar12 = pfVar9 + -9;
              pfVar11 = pfVar9 + -1;
            }
          }
          else {
            pfVar11 = pfVar9 + -9;
LAB_00444840:
            pfVar12 = pfVar9 + -1;
          }
        }
        uStack_13c = 0;
        uStack_11c = 0;
        local_140 = (uint)pfVar16[4] & 0xff;
        local_168[0] = pfVar16[6] * _DAT_0056e4c4;
        local_120 = (uint)pfVar11[4] & 0xff;
        local_a8[0] = pfVar11[6] * _DAT_0056e4c4;
        local_130 = (uint)pfVar12[4] & 0xff;
        local_e8[0] = pfVar12[6] * _DAT_0056e4c4;
        uStack_12c = 0;
        uStack_134 = 0;
        local_138 = (uint)pfVar16[4] >> 0x18;
        local_168[1] = pfVar16[7] * _DAT_0056e4c4;
        local_128 = (uint)pfVar11[4] >> 0x18;
        uStack_124 = 0;
        local_118 = (uint)pfVar12[4] >> 0x18;
        local_a8[1] = pfVar11[7] * _DAT_0056e4c4;
        uStack_114 = 0;
        local_e8[1] = pfVar12[7] * _DAT_0056e4c4;
        local_168[2] = (float)local_140;
        local_a8[2] = (float)local_120;
        local_e8[2] = (float)local_130;
        local_168[4] = _DAT_0056e0c4 - (float)local_138;
        local_a8[4] = _DAT_0056e0c4 - (float)local_128;
        local_e8[4] = _DAT_0056e0c4 - (float)local_118;
        local_168[3] = pfVar16[2] * _DAT_0056e1cc;
        local_a8[3] = pfVar11[2] * _DAT_0056e1cc;
        local_e8[3] = pfVar12[2] * _DAT_0056e1cc;
        if (pfVar16[1] != pfVar12[1]) {
          fVar6 = pfVar12[1];
          fVar14 = pfVar16[1];
          fVar20 = (pfVar11[1] - pfVar16[1]) / (fVar6 - fVar14);
          fVar18 = (*pfVar12 - *pfVar16) * fVar20 + *pfVar16;
          if (fVar18 != *pfVar11) {
            iVar13 = 0;
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_40[iVar13] =
                     (local_e8[iVar13] - local_168[iVar13]) * fVar20 + local_168[iVar13];
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            fVar20 = *pfVar11;
            iVar13 = 0;
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_68[iVar13] =
                     (local_a8[iVar13] - afStack_40[iVar13]) * (_DAT_0056e008 / (fVar20 - fVar18));
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            iVar13 = 0;
            do {
              if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                afStack_88[iVar13] =
                     (local_e8[iVar13] - local_168[iVar13]) * (_DAT_0056e008 / (fVar6 - fVar14));
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 < 8);
            iVar13 = __ftol();
            uVar17 = __ftol();
            iVar15 = __ftol();
            if (iVar15 != iVar13) {
              fVar6 = pfVar16[1];
              iVar10 = 0;
              do {
                if ((1 << ((byte)iVar10 & 0x1f) & 0x1fU) != 0) {
                  local_168[iVar10] =
                       ((float)iVar13 - (fVar6 - _DAT_0056e158)) * afStack_88[iVar10] +
                       local_168[iVar10];
                }
                iVar10 = iVar10 + 1;
              } while (iVar10 < 8);
              uVar5 = __ftol();
              iVar10 = __ftol();
              local_1ac = (ushort *)__ftol();
              local_148 = (ushort *)__ftol();
              iVar19 = 0;
              do {
                if ((1 << ((byte)iVar19 & 0x1f) & 0x1fU) != 0) {
                  fVar6 = (float)__ftol();
                  local_c8[iVar19] = fVar6;
                  iVar7 = __ftol();
                  local_108[iVar19] = iVar7;
                  uVar8 = __ftol();
                  auStack_20[iVar19] = uVar8;
                }
                iVar19 = iVar19 + 1;
              } while (iVar19 < 8);
              local_1c4 = param_1 + iVar13 * param_4 * 2;
              local_1b8 = 0;
              local_1a4 = param_2 + iVar13 * param_5 * 2;
              local_1cc = uVar17;
              local_194 = uVar5;
              do {
                if (local_1b8 == 0) {
                  local_1d0 = (float)__ftol();
                }
                else {
                  local_1d0 = (float)__ftol();
                  local_1ac = local_148;
                  uVar17 = iVar15;
                  local_1cc = iVar15;
                }
                if (iVar13 < (int)uVar17) {
                  local_1c0 = (ushort *)(uVar17 - iVar13);
                  iVar13 = iVar13 + (int)local_1c0;
                  do {
                    local_110 = ((uVar5 & 0xffff0000) - uVar5) + 0xffff;
                    iVar19 = 0;
                    uStack_10c = 0;
                    do {
                      if ((1 << ((byte)iVar19 & 0x1f) & 0x1fU) != 0) {
                        fVar6 = (float)__ftol();
                        local_c8[iVar19] = fVar6;
                      }
                      iVar19 = iVar19 + 1;
                    } while (iVar19 < 8);
                    local_1dc = (float *)local_c8[3];
                    local_1c8 = local_c8[0];
                    iVar7 = (int)uVar5 >> 0x10;
                    local_1d4 = ((int)local_1d0 >> 0x10) - iVar7;
                    iVar19 = local_1a4 + iVar7 * 2;
                    local_1d8 = (float *)(local_1c4 + iVar7 * 2);
                    if ((int)local_1d4 < 0) {
                      if (0x7fffffff < local_1d4) {
                        iVar19 = iVar19 - (int)local_1d8;
                        local_1d4 = -local_1d4;
                        fVar6 = local_c8[2];
                        fVar14 = local_c8[4];
                        fVar20 = local_c8[1];
                        do {
                          local_1d8 = (float *)((int)local_1d8 + -2);
                          local_1c8 = (float)((int)local_1c8 - local_108[0]);
                          fVar6 = (float)((int)fVar6 - local_108[2]);
                          fVar20 = (float)((int)fVar20 - local_108[1]);
                          local_1dc = (float *)((int)local_1dc - local_108[3]);
                          fVar14 = (float)((int)fVar14 - local_108[4]);
                          if (((int)local_1dc >> 0x10 & 0xffffU) <=
                              (uint)*(ushort *)(iVar19 + (int)local_1d8)) {
                            uVar17 = *(uint *)(param_3 +
                                              ((int)(((uint)local_1c8 >> 0x10 & 0xff) << 8 |
                                                    (uint)fVar20 & 0xff0000) >> 8) * 4);
                            uVar5 = ((int)fVar6 >> 0x13) * (uVar17 & 0x3e07c1f) & 0x7c0f83e0;
                            uVar17 = ((*(ushort *)local_1d8 & 0x3e0) << 0x10 |
                                     *(ushort *)local_1d8 & 0x3e07c1f) *
                                     (((uVar17 >> 0x1b) * ((uint)fVar14 ^ 0xffffff) ^ 0x1f000000) >>
                                     0x18) & 0x7c0f83e0;
                            *(ushort *)local_1d8 =
                                 ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5)) +
                                 ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5));
                          }
                          local_1d4 = local_1d4 + -1;
                        } while (local_1d4 != 0);
                      }
                    }
                    else if (0 < (int)local_1d4) {
                      iVar19 = iVar19 - (int)local_1d8;
                      fVar6 = local_c8[2];
                      fVar14 = local_c8[4];
                      fVar20 = local_c8[1];
                      do {
                        if (((int)local_1dc >> 0x10 & 0xffffU) <=
                            (uint)*(ushort *)((int)local_1d8 + iVar19)) {
                          uVar17 = *(uint *)(param_3 +
                                            ((int)(((uint)local_1c8 >> 0x10 & 0xff) << 8 |
                                                  (uint)fVar20 & 0xff0000) >> 8) * 4);
                          uVar5 = ((int)fVar6 >> 0x13) * (uVar17 & 0x3e07c1f) & 0x7c0f83e0;
                          uVar17 = ((*(ushort *)local_1d8 & 0x3e0) << 0x10 |
                                   *(ushort *)local_1d8 & 0x3e07c1f) *
                                   (((uVar17 >> 0x1b) * ((uint)fVar14 ^ 0xffffff) ^ 0x1f000000) >>
                                   0x18) & 0x7c0f83e0;
                          *(ushort *)local_1d8 =
                               ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5)) +
                               ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5));
                        }
                        local_1c8 = (float)((int)local_1c8 + local_108[0]);
                        fVar20 = (float)((int)fVar20 + local_108[1]);
                        fVar6 = (float)((int)fVar6 + local_108[2]);
                        fVar14 = (float)((int)fVar14 + local_108[4]);
                        local_1dc = (float *)((int)local_1dc + local_108[3]);
                        local_1d8 = (float *)((int)local_1d8 + 2);
                        local_1d4 = local_1d4 - 1;
                      } while (local_1d4 != 0);
                    }
                    uVar5 = local_194 + iVar10;
                    local_1d0 = (float)((int)local_1d0 + (int)local_1ac);
                    iVar19 = 0;
                    do {
                      if ((1 << ((byte)iVar19 & 0x1f) & 0x1fU) != 0) {
                        local_168[iVar19] = afStack_88[iVar19] + local_168[iVar19];
                      }
                      iVar19 = iVar19 + 1;
                    } while (iVar19 < 8);
                    local_1c4 = local_1c4 + param_4 * 2;
                    local_1a4 = local_1a4 + param_5 * 2;
                    local_1c0 = (ushort *)((int)local_1c0 + -1);
                    uVar17 = local_1cc;
                    local_194 = uVar5;
                  } while (local_1c0 != (ushort *)0x0);
                }
                local_1b8 = local_1b8 + 1;
              } while (local_1b8 < 2);
            }
          }
        }
        local_184 = local_184 + 1;
        pfVar9 = pfVar9 + 8;
        local_1bc = local_1bc + -1;
        if (param_7 <= local_184) {
          return;
        }
      }
    }
  }
  else {
    switch(uVar17) {
    case 1:
      iVar13 = 0;
      if (0 < param_7) {
        param_6 = param_6 + 9;
        iVar15 = param_7;
        while (2 < iVar15) {
          param_6[-9] = param_6[-9] + _DAT_0056e158;
          param_6[-8] = param_6[-8] + _DAT_0056e158;
          param_6[-7] = param_6[-7] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[-6] = param_6[-3] * _DAT_0056e4c4;
          param_6[-4] = (float)((uint)param_6[-5] & 0xff);
          param_6[-5] = param_6[-2] * _DAT_0056e4c4;
          param_6[-1] = param_6[-1] + _DAT_0056e158;
          *param_6 = *param_6 + _DAT_0056e158;
          param_6[1] = param_6[1] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[2] = param_6[5] * _DAT_0056e4c4;
          param_6[4] = (float)((uint)param_6[3] & 0xff);
          param_6[3] = param_6[6] * _DAT_0056e4c4;
          param_6[7] = param_6[7] + _DAT_0056e158;
          param_6[8] = param_6[8] + _DAT_0056e158;
          param_6[9] = param_6[9] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[10] = param_6[0xd] * _DAT_0056e4c4;
          param_6[0xc] = (float)((uint)param_6[0xb] & 0xff);
          param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
          sub_55B874(param_6 + -0xe,param_6 + -6,param_6 + 2);
          iVar13 = iVar13 + 3;
          iVar15 = iVar15 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
      break;
    default:
      goto switchD_00442c7b_caseD_2;
    case 5:
      iVar13 = 0;
      if (0 < param_7) {
        param_6 = param_6 + 9;
        iVar15 = param_7;
        while (2 < iVar15) {
          param_6[-9] = param_6[-9] + _DAT_0056e158;
          param_6[-8] = param_6[-8] + _DAT_0056e158;
          param_6[-7] = param_6[-7] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[-6] = param_6[-3] * _DAT_0056e4c4;
          param_6[-4] = (float)((uint)param_6[-5] & 0xff);
          param_6[-5] = param_6[-2] * _DAT_0056e4c4;
          param_6[-1] = param_6[-1] + _DAT_0056e158;
          *param_6 = *param_6 + _DAT_0056e158;
          param_6[1] = param_6[1] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[2] = param_6[5] * _DAT_0056e4c4;
          param_6[4] = (float)((uint)param_6[3] & 0xff);
          param_6[3] = param_6[6] * _DAT_0056e4c4;
          param_6[7] = param_6[7] + _DAT_0056e158;
          param_6[8] = param_6[8] + _DAT_0056e158;
          param_6[9] = param_6[9] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[10] = param_6[0xd] * _DAT_0056e4c4;
          param_6[0xc] = (float)((uint)param_6[0xb] & 0xff);
          param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
          sub_55C13E(param_6 + -0xe,param_6 + -6,param_6 + 2);
          iVar13 = iVar13 + 3;
          iVar15 = iVar15 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
      break;
    case 0x18:
    case 0x1a:
      iVar13 = 0;
      if (0 < param_7) {
        param_6 = param_6 + 9;
        iVar15 = param_7;
        while (2 < iVar15) {
          param_6[-9] = param_6[-9] + _DAT_0056e158;
          param_6[-8] = param_6[-8] + _DAT_0056e158;
          param_6[-6] = param_6[-3] * _DAT_0056e4c4;
          param_6[-5] = param_6[-2] * _DAT_0056e4c4;
          param_6[-1] = param_6[-1] + _DAT_0056e158;
          *param_6 = *param_6 + _DAT_0056e158;
          param_6[2] = param_6[5] * _DAT_0056e4c4;
          param_6[3] = param_6[6] * _DAT_0056e4c4;
          param_6[7] = param_6[7] + _DAT_0056e158;
          param_6[8] = param_6[8] + _DAT_0056e158;
          param_6[10] = param_6[0xd] * _DAT_0056e4c4;
          param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
          sub_560EA0(param_6 + -0xe,param_6 + -6,param_6 + 2);
          iVar13 = iVar13 + 3;
          iVar15 = iVar15 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
      break;
    case 0x21:
      if (0 < param_7) {
        param_6 = param_6 + 9;
        iVar15 = param_7;
        while (2 < iVar15) {
          uStack_144 = 0;
          param_6[-9] = param_6[-9] + _DAT_0056e158;
          param_6[-8] = param_6[-8] + _DAT_0056e158;
          param_6[-7] = param_6[-7] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[-6] = param_6[-3] * _DAT_0056e4c4;
          param_6[-4] = (float)((uint)param_6[-5] & 0xff);
          param_6[-3] = _DAT_0056e0c4 - (float)((uint)param_6[-5] >> 0x18);
          param_6[-5] = param_6[-2] * _DAT_0056e4c4;
          param_6[-1] = param_6[-1] + _DAT_0056e158;
          *param_6 = *param_6 + _DAT_0056e158;
          param_6[1] = param_6[1] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[2] = param_6[5] * _DAT_0056e4c4;
          param_6[4] = (float)((uint)param_6[3] & 0xff);
          local_148 = (ushort *)((uint)param_6[3] >> 0x18);
          param_6[5] = _DAT_0056e0c4 - (float)local_148;
          param_6[3] = param_6[6] * _DAT_0056e4c4;
          param_6[7] = param_6[7] + _DAT_0056e158;
          param_6[8] = param_6[8] + _DAT_0056e158;
          param_6[9] = param_6[9] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[10] = param_6[0xd] * _DAT_0056e4c4;
          param_6[0xc] = (float)((uint)param_6[0xb] & 0xff);
          param_6[0xd] = _DAT_0056e0c4 - (float)((uint)param_6[0xb] >> 0x18);
          param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
          sub_55F55C(param_6 + -0xe,param_6 + -6,param_6 + 2);
          iVar13 = iVar13 + 3;
          iVar15 = iVar15 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
      break;
    case 0x25:
      if (0 < param_7) {
        param_6 = param_6 + 9;
        iVar15 = param_7;
        while (2 < iVar15) {
          uStack_144 = 0;
          param_6[-9] = param_6[-9] + _DAT_0056e158;
          param_6[-8] = param_6[-8] + _DAT_0056e158;
          param_6[-7] = param_6[-7] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[-6] = param_6[-3] * _DAT_0056e4c4;
          param_6[-4] = (float)((uint)param_6[-5] & 0xff);
          param_6[-3] = _DAT_0056e0c4 - (float)((uint)param_6[-5] >> 0x18);
          param_6[-5] = param_6[-2] * _DAT_0056e4c4;
          param_6[-1] = param_6[-1] + _DAT_0056e158;
          *param_6 = *param_6 + _DAT_0056e158;
          param_6[1] = param_6[1] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[2] = param_6[5] * _DAT_0056e4c4;
          param_6[4] = (float)((uint)param_6[3] & 0xff);
          local_148 = (ushort *)((uint)param_6[3] >> 0x18);
          param_6[5] = _DAT_0056e0c4 - (float)local_148;
          param_6[3] = param_6[6] * _DAT_0056e4c4;
          param_6[7] = param_6[7] + _DAT_0056e158;
          param_6[8] = param_6[8] + _DAT_0056e158;
          param_6[9] = param_6[9] * _DAT_0056e1cc - _DAT_0056e4d8;
          param_6[10] = param_6[0xd] * _DAT_0056e4c4;
          param_6[0xc] = (float)((uint)param_6[0xb] & 0xff);
          param_6[0xd] = _DAT_0056e0c4 - (float)((uint)param_6[0xb] >> 0x18);
          param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
          sub_5601F2(param_6 + -0xe,param_6 + -6,param_6 + 2);
          iVar13 = iVar13 + 3;
          iVar15 = iVar15 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
      break;
    case 0x31:
      local_184 = 0;
      if (0 < param_7) {
        local_1c4 = param_7;
        param_6 = param_6 + 9;
        while (2 < local_1c4) {
          if (*param_6 <= param_6[-8]) {
            if (*param_6 <= param_6[8]) {
              pfVar9 = param_6 + -1;
              if (param_6[-8] <= param_6[8]) {
                local_1d8 = param_6 + -9;
                goto LAB_004434a0;
              }
              local_1d8 = param_6 + 7;
              local_1dc = param_6 + -9;
            }
            else {
              local_1d8 = param_6 + -1;
              pfVar9 = param_6 + 7;
              local_1dc = param_6 + -9;
            }
          }
          else if (param_6[8] <= *param_6) {
            if (param_6[8] <= param_6[-8]) {
              local_1d8 = param_6 + -9;
              pfVar9 = param_6 + 7;
              local_1dc = param_6 + -1;
            }
            else {
              local_1d8 = param_6 + 7;
              pfVar9 = param_6 + -9;
              local_1dc = param_6 + -1;
            }
          }
          else {
            pfVar9 = param_6 + -9;
            local_1d8 = param_6 + -1;
LAB_004434a0:
            local_1dc = param_6 + 7;
          }
          fVar6 = local_1d8[4];
          fVar14 = pfVar9[4];
          if ((((((uint)fVar6 ^ (uint)fVar14) & 0xff000000) == 0) &&
              ((((uint)local_1dc[4] ^ (uint)fVar14) & 0xff000000) == 0)) &&
             (((uint)fVar14 & 0xff000000) == 0x80000000)) {
            param_6[-9] = param_6[-9] + _DAT_0056e158;
            param_6[-8] = param_6[-8] + _DAT_0056e158;
            param_6[-7] = param_6[-7] * _DAT_0056e1cc - _DAT_0056e4d8;
            param_6[-6] = param_6[-3] * _DAT_0056e4c4;
            uStack_44 = 0;
            param_6[-4] = (float)((uint)param_6[-5] & 0xff);
            param_6[-5] = param_6[-2] * _DAT_0056e4c4;
            param_6[-1] = param_6[-1] + _DAT_0056e158;
            *param_6 = *param_6 + _DAT_0056e158;
            param_6[1] = param_6[1] * _DAT_0056e1cc - _DAT_0056e4d8;
            param_6[2] = param_6[5] * _DAT_0056e4c4;
            param_6[4] = (float)((uint)param_6[3] & 0xff);
            param_6[3] = param_6[6] * _DAT_0056e4c4;
            param_6[7] = param_6[7] + _DAT_0056e158;
            param_6[8] = param_6[8] + _DAT_0056e158;
            param_6[9] = param_6[9] * _DAT_0056e1cc - _DAT_0056e4d8;
            param_6[10] = param_6[0xd] * _DAT_0056e4c4;
            local_48 = (uint)param_6[0xb] & 0xff;
            param_6[0xc] = (float)local_48;
            param_6[0xb] = param_6[0xe] * _DAT_0056e4c4;
            sub_55D316(param_6 + -0xe,param_6 + -6,param_6 + 2);
          }
          else {
            local_110 = (uint)fVar14 & 0xff;
            local_168[0] = pfVar9[6] * _DAT_0056e4c4;
            local_118 = (uint)fVar6 & 0xff;
            local_a8[0] = local_1d8[6] * _DAT_0056e4c4;
            local_138 = (uint)fVar14 >> 0x18;
            local_c8[0] = local_1dc[6] * _DAT_0056e4c4;
            local_130 = (uint)fVar6 >> 0x18;
            local_168[1] = pfVar9[7] * _DAT_0056e4c4;
            uStack_10c = 0;
            uStack_114 = 0;
            local_a8[1] = local_1d8[7] * _DAT_0056e4c4;
            local_128 = (uint)local_1dc[4] & 0xff;
            local_c8[1] = local_1dc[7] * _DAT_0056e4c4;
            uStack_124 = 0;
            uStack_134 = 0;
            uStack_12c = 0;
            uStack_11c = 0;
            local_168[2] = (float)local_110;
            local_120 = (uint)local_1dc[4] >> 0x18;
            local_a8[2] = (float)local_118;
            local_c8[2] = (float)local_128;
            local_168[4] = _DAT_0056e0c4 - (float)local_138;
            local_a8[4] = _DAT_0056e0c4 - (float)local_130;
            local_c8[4] = _DAT_0056e0c4 - (float)local_120;
            local_168[3] = pfVar9[2] * _DAT_0056e1cc;
            local_a8[3] = local_1d8[2] * _DAT_0056e1cc;
            local_c8[3] = local_1dc[2] * _DAT_0056e1cc;
            if (pfVar9[1] != local_1dc[1]) {
              fVar6 = local_1dc[1];
              fVar14 = pfVar9[1];
              fVar20 = (local_1d8[1] - pfVar9[1]) / (fVar6 - fVar14);
              fVar18 = (*local_1dc - *pfVar9) * fVar20 + *pfVar9;
              if (fVar18 != *local_1d8) {
                iVar13 = 0;
                do {
                  if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                    afStack_40[iVar13] =
                         (local_c8[iVar13] - local_168[iVar13]) * fVar20 + local_168[iVar13];
                  }
                  iVar13 = iVar13 + 1;
                } while (iVar13 < 8);
                fVar20 = *local_1d8;
                iVar13 = 0;
                do {
                  if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                    afStack_68[iVar13] =
                         (local_a8[iVar13] - afStack_40[iVar13]) *
                         (_DAT_0056e008 / (fVar20 - fVar18));
                  }
                  iVar13 = iVar13 + 1;
                } while (iVar13 < 8);
                iVar13 = 0;
                do {
                  if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                    afStack_88[iVar13] =
                         (local_c8[iVar13] - local_168[iVar13]) * (_DAT_0056e008 / (fVar6 - fVar14))
                    ;
                  }
                  iVar13 = iVar13 + 1;
                } while (iVar13 < 8);
                iVar15 = __ftol();
                iVar13 = __ftol();
                iVar10 = __ftol();
                if (iVar10 != iVar15) {
                  fVar6 = pfVar9[1];
                  iVar19 = 0;
                  do {
                    if ((1 << ((byte)iVar19 & 0x1f) & 0x1fU) != 0) {
                      local_168[iVar19] =
                           ((float)iVar15 - (fVar6 - _DAT_0056e158)) * afStack_88[iVar19] +
                           local_168[iVar19];
                    }
                    iVar19 = iVar19 + 1;
                  } while (iVar19 < 8);
                  local_1d0 = (float)__ftol();
                  local_148 = (ushort *)__ftol();
                  local_1bc = __ftol();
                  iVar19 = __ftol();
                  iVar7 = 0;
                  do {
                    if ((1 << ((byte)iVar7 & 0x1f) & 0x1fU) != 0) {
                      fVar6 = (float)__ftol();
                      local_e8[iVar7] = fVar6;
                      iVar2 = __ftol();
                      local_108[iVar7] = iVar2;
                      uVar8 = __ftol();
                      auStack_20[iVar7] = uVar8;
                    }
                    iVar7 = iVar7 + 1;
                  } while (iVar7 < 8);
                  local_1cc = param_1 + iVar15 * param_4 * 2;
                  local_1b0 = param_2 + iVar15 * param_5 * 2;
                  local_1ac = (ushort *)0x0;
                  local_198 = iVar13;
                  do {
                    if (local_1ac == (ushort *)0x0) {
                      local_1c8 = (float)__ftol();
                    }
                    else {
                      local_1c8 = (float)__ftol();
                      iVar13 = iVar10;
                      local_1bc = iVar19;
                      local_198 = iVar10;
                    }
                    if (iVar15 < iVar13) {
                      local_190 = iVar13 - iVar15;
                      iVar15 = iVar15 + local_190;
                      do {
                        local_140 = (((uint)local_1d0 & 0xffff0000) - (int)local_1d0) + 0xffff;
                        iVar13 = 0;
                        uStack_13c = 0;
                        do {
                          if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                            fVar6 = (float)__ftol();
                            local_e8[iVar13] = fVar6;
                          }
                          iVar13 = iVar13 + 1;
                        } while (iVar13 < 8);
                        local_1dc = (float *)local_e8[3];
                        local_1d8 = (float *)local_e8[0];
                        iVar7 = (int)local_1d0 >> 0x10;
                        local_1c0 = (ushort *)(((int)local_1c8 >> 0x10) - iVar7);
                        iVar13 = local_1b0 + iVar7 * 2;
                        puVar4 = (ushort *)(local_1cc + iVar7 * 2);
                        if ((int)local_1c0 < 0) {
                          if (0x7fffffff < local_1c0) {
                            iVar13 = iVar13 - (int)puVar4;
                            local_1c0 = (ushort *)-(int)local_1c0;
                            fVar6 = local_e8[3];
                            fVar14 = local_e8[2];
                            fVar20 = local_e8[4];
                            fVar18 = local_e8[1];
                            do {
                              puVar4 = puVar4 + -1;
                              local_1d8 = (float *)((int)local_1d8 - local_108[0]);
                              fVar18 = (float)((int)fVar18 - local_108[1]);
                              fVar14 = (float)((int)fVar14 - local_108[2]);
                              fVar6 = (float)((int)fVar6 - local_108[3]);
                              fVar20 = (float)((int)fVar20 - local_108[4]);
                              if (((int)fVar6 >> 0x10 & 0xffffU) <=
                                  (uint)*(ushort *)(iVar13 + (int)puVar4)) {
                                uVar17 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_1d8 >> 0x10 & 0xff) << 8 |
                                                      (uint)fVar18 & 0xff0000) >> 8) * 2);
                                uVar17 = ((uVar17 & 0x3e0) << 0x10 | uVar17 & 0x3e07c1f) *
                                         ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                                uVar5 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                        ((int)fVar20 >> 0x13) & 0x7c0f83e0;
                                *puVar4 = ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5)) +
                                          ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5));
                              }
                              local_1c0 = (ushort *)((int)local_1c0 + -1);
                            } while (local_1c0 != (ushort *)0x0);
                          }
                        }
                        else if (0 < (int)local_1c0) {
                          iVar13 = iVar13 - (int)puVar4;
                          fVar6 = local_e8[2];
                          fVar14 = local_e8[4];
                          fVar20 = local_e8[1];
                          do {
                            if (((int)local_1dc >> 0x10 & 0xffffU) <=
                                (uint)*(ushort *)((int)puVar4 + iVar13)) {
                              uVar1 = *(ushort *)
                                       (param_3 +
                                       ((int)(((uint)local_1d8 >> 0x10 & 0xff) << 8 |
                                             (uint)fVar20 & 0xff0000) >> 8) * 2);
                              uVar17 = ((uVar1 & 0x3e0) << 0x10 | uVar1 & 0x3e07c1f) *
                                       ((int)fVar6 >> 0x13) & 0x7c0f83e0;
                              uVar5 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                      ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                              *puVar4 = ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5)) +
                                        ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5));
                            }
                            local_1d8 = (float *)((int)local_1d8 + local_108[0]);
                            fVar20 = (float)((int)fVar20 + local_108[1]);
                            fVar6 = (float)((int)fVar6 + local_108[2]);
                            local_1dc = (float *)((int)local_1dc + local_108[3]);
                            fVar14 = (float)((int)fVar14 + local_108[4]);
                            puVar4 = puVar4 + 1;
                            local_1c0 = (ushort *)((int)local_1c0 - 1);
                          } while (local_1c0 != (ushort *)0x0);
                        }
                        local_1d0 = (float)((int)local_1d0 + (int)local_148);
                        local_1c8 = (float)((int)local_1c8 + local_1bc);
                        iVar13 = 0;
                        do {
                          if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                            local_168[iVar13] = afStack_88[iVar13] + local_168[iVar13];
                          }
                          iVar13 = iVar13 + 1;
                        } while (iVar13 < 8);
                        local_1cc = local_1cc + param_4 * 2;
                        local_1b0 = local_1b0 + param_5 * 2;
                        local_190 = local_190 + -1;
                        iVar13 = local_198;
                      } while (local_190 != 0);
                    }
                    local_1ac = (ushort *)((int)local_1ac + 1);
                  } while ((int)local_1ac < 2);
                }
              }
            }
          }
          local_184 = local_184 + 3;
          local_1c4 = local_1c4 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= local_184) {
            return;
          }
        }
      }
      break;
    case 0x35:
      local_184 = 0;
      if (0 < param_7) {
        local_1b4 = param_7;
        param_6 = param_6 + 0x11;
        while (2 < local_1b4) {
          if (param_6[-8] <= param_6[-0x10]) {
            if (param_6[-8] <= *param_6) {
              pfVar9 = param_6 + -9;
              if (param_6[-0x10] <= *param_6) {
                pfVar11 = param_6 + -0x11;
                goto LAB_00443f15;
              }
              pfVar11 = param_6 + -1;
              pfVar12 = param_6 + -0x11;
            }
            else {
              pfVar9 = param_6 + -1;
              pfVar11 = param_6 + -9;
              pfVar12 = param_6 + -0x11;
            }
          }
          else if (*param_6 <= param_6[-8]) {
            if (*param_6 <= param_6[-0x10]) {
              pfVar9 = param_6 + -1;
              pfVar11 = param_6 + -0x11;
              pfVar12 = param_6 + -9;
            }
            else {
              pfVar9 = param_6 + -0x11;
              pfVar11 = param_6 + -1;
              pfVar12 = param_6 + -9;
            }
          }
          else {
            pfVar9 = param_6 + -0x11;
            pfVar11 = param_6 + -9;
LAB_00443f15:
            pfVar12 = param_6 + -1;
          }
          uStack_13c = 0;
          local_140 = (uint)pfVar9[4] & 0xff;
          uStack_11c = 0;
          local_168[0] = pfVar9[6] * _DAT_0056e4c4;
          local_a8[0] = pfVar11[6] * _DAT_0056e4c4;
          local_120 = (uint)pfVar11[4] & 0xff;
          local_130 = (uint)pfVar12[4] & 0xff;
          local_e8[0] = pfVar12[6] * _DAT_0056e4c4;
          iVar13 = 0;
          uStack_12c = 0;
          uStack_134 = 0;
          local_138 = (uint)pfVar9[4] >> 0x18;
          local_168[1] = pfVar9[7] * _DAT_0056e4c4;
          uStack_124 = 0;
          local_128 = (uint)pfVar11[4] >> 0x18;
          uStack_114 = 0;
          local_a8[1] = pfVar11[7] * _DAT_0056e4c4;
          local_118 = (uint)pfVar12[4] >> 0x18;
          local_e8[1] = pfVar12[7] * _DAT_0056e4c4;
          local_168[2] = (float)local_140;
          local_a8[2] = (float)local_120;
          local_e8[2] = (float)local_130;
          local_168[4] = _DAT_0056e0c4 - (float)local_138;
          local_a8[4] = _DAT_0056e0c4 - (float)local_128;
          local_e8[4] = _DAT_0056e0c4 - (float)local_118;
          local_168[3] = pfVar9[2] * _DAT_0056e1cc;
          local_a8[3] = pfVar11[2] * _DAT_0056e1cc;
          local_e8[3] = pfVar12[2] * _DAT_0056e1cc;
          if (pfVar9[1] != pfVar12[1]) {
            fVar6 = pfVar12[1];
            fVar14 = pfVar9[1];
            fVar20 = (pfVar11[1] - pfVar9[1]) / (fVar6 - fVar14);
            fVar18 = (*pfVar12 - *pfVar9) * fVar20 + *pfVar9;
            if (fVar18 != *pfVar11) {
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                  afStack_40[iVar13] =
                       (local_e8[iVar13] - local_168[iVar13]) * fVar20 + local_168[iVar13];
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              fVar20 = *pfVar11;
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                  afStack_68[iVar13] =
                       (local_a8[iVar13] - afStack_40[iVar13]) * (_DAT_0056e008 / (fVar20 - fVar18))
                  ;
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                  afStack_88[iVar13] =
                       (local_e8[iVar13] - local_168[iVar13]) * (_DAT_0056e008 / (fVar6 - fVar14));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              puVar3 = (ushort *)__ftol();
              puVar4 = (ushort *)__ftol();
              local_148 = (ushort *)__ftol();
              if (local_148 != puVar3) {
                fVar6 = pfVar9[1];
                iVar13 = 0;
                do {
                  if ((1 << ((byte)iVar13 & 0x1f) & 0x1fU) != 0) {
                    local_168[iVar13] =
                         ((float)(int)puVar3 - (fVar6 - _DAT_0056e158)) * afStack_88[iVar13] +
                         local_168[iVar13];
                  }
                  iVar13 = iVar13 + 1;
                } while (iVar13 < 8);
                local_1a4 = __ftol();
                iVar13 = __ftol();
                local_1ac = (ushort *)__ftol();
                iVar15 = __ftol();
                iVar10 = 0;
                do {
                  if ((1 << ((byte)iVar10 & 0x1f) & 0x1fU) != 0) {
                    fVar6 = (float)__ftol();
                    local_c8[iVar10] = fVar6;
                    iVar19 = __ftol();
                    local_108[iVar10] = iVar19;
                    uVar8 = __ftol();
                    auStack_20[iVar10] = uVar8;
                  }
                  iVar10 = iVar10 + 1;
                } while (iVar10 < 8);
                local_1b8 = param_1 + (int)puVar3 * param_4 * 2;
                local_1cc = param_2 + (int)puVar3 * param_5 * 2;
                local_1bc = 0;
                local_1c0 = puVar4;
                do {
                  if (local_1bc == 0) {
                    local_1d0 = (float)__ftol();
                  }
                  else {
                    local_1d0 = (float)__ftol();
                    local_1c0 = local_148;
                    puVar4 = local_148;
                    local_1ac = (ushort *)iVar15;
                  }
                  if ((int)puVar3 < (int)puVar4) {
                    local_194 = (int)puVar4 - (int)puVar3;
                    puVar3 = (ushort *)((int)puVar3 + local_194);
                    do {
                      local_110 = ((local_1a4 & 0xffff0000) - local_1a4) + 0xffff;
                      iVar10 = 0;
                      uStack_10c = 0;
                      do {
                        if ((1 << ((byte)iVar10 & 0x1f) & 0x1fU) != 0) {
                          fVar6 = (float)__ftol();
                          local_c8[iVar10] = fVar6;
                        }
                        iVar10 = iVar10 + 1;
                      } while (iVar10 < 8);
                      local_1d8 = (float *)local_c8[0];
                      local_1dc = (float *)local_c8[1];
                      iVar19 = (int)local_1a4 >> 0x10;
                      local_1d4 = ((int)local_1d0 >> 0x10) - iVar19;
                      iVar10 = local_1cc + iVar19 * 2;
                      puVar4 = (ushort *)(local_1b8 + iVar19 * 2);
                      if ((int)local_1d4 < 0) {
                        if (0x7fffffff < local_1d4) {
                          iVar10 = iVar10 - (int)puVar4;
                          local_1d4 = -local_1d4;
                          fVar6 = local_c8[4];
                          fVar14 = local_c8[3];
                          fVar20 = local_c8[2];
                          do {
                            puVar4 = puVar4 + -1;
                            local_1d8 = (float *)((int)local_1d8 - local_108[0]);
                            local_1dc = (float *)((int)local_1dc - local_108[1]);
                            fVar20 = (float)((int)fVar20 - local_108[2]);
                            fVar14 = (float)((int)fVar14 - local_108[3]);
                            fVar6 = (float)((int)fVar6 - local_108[4]);
                            if ((((int)fVar14 >> 0x10 & 0xffffU) <=
                                 (uint)*(ushort *)(iVar10 + (int)puVar4)) &&
                               (uVar17 = (uint)*(ushort *)
                                                (param_3 +
                                                ((int)(((uint)local_1d8 >> 0x10 & 0xff) << 8 |
                                                      (uint)local_1dc & 0xff0000) >> 8) * 2),
                               uVar17 != 0)) {
                              uVar17 = ((uVar17 & 0x3e0) << 0x10 | uVar17 & 0x3e07c1f) *
                                       ((int)fVar20 >> 0x13) & 0x7c0f83e0;
                              uVar5 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                      ((int)fVar6 >> 0x13) & 0x7c0f83e0;
                              *puVar4 = ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5)) +
                                        ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5));
                            }
                            local_1d4 = local_1d4 + -1;
                          } while (local_1d4 != 0);
                        }
                      }
                      else if (0 < (int)local_1d4) {
                        iVar10 = iVar10 - (int)puVar4;
                        fVar6 = local_c8[4];
                        fVar14 = local_c8[3];
                        fVar20 = local_c8[2];
                        do {
                          if ((((int)fVar14 >> 0x10 & 0xffffU) <=
                               (uint)*(ushort *)(iVar10 + (int)puVar4)) &&
                             (uVar1 = *(ushort *)
                                       (param_3 +
                                       ((int)(((uint)local_1d8 >> 0x10 & 0xff) << 8 |
                                             (uint)local_1dc & 0xff0000) >> 8) * 2), uVar1 != 0)) {
                            uVar17 = ((uint)(uVar1 & 0x3e0) << 0x10 | uVar1 & 0x3e07c1f) *
                                     ((int)fVar20 >> 0x13) & 0x7c0f83e0;
                            uVar5 = ((*puVar4 & 0x3e0) << 0x10 | *puVar4 & 0x3e07c1f) *
                                    ((int)fVar6 >> 0x13) & 0x7c0f83e0;
                            *puVar4 = ((ushort)(uVar5 >> 0x15) | (ushort)(uVar5 >> 5)) +
                                      ((ushort)(uVar17 >> 0x15) | (ushort)(uVar17 >> 5));
                          }
                          local_1d8 = (float *)((int)local_1d8 + local_108[0]);
                          fVar20 = (float)((int)fVar20 + local_108[2]);
                          local_1dc = (float *)((int)local_1dc + local_108[1]);
                          fVar14 = (float)((int)fVar14 + local_108[3]);
                          fVar6 = (float)((int)fVar6 + local_108[4]);
                          puVar4 = puVar4 + 1;
                          local_1d4 = local_1d4 - 1;
                        } while (local_1d4 != 0);
                      }
                      local_1a4 = local_1a4 + iVar13;
                      local_1d0 = (float)((int)local_1d0 + (int)local_1ac);
                      iVar10 = 0;
                      do {
                        if ((1 << ((byte)iVar10 & 0x1f) & 0x1fU) != 0) {
                          local_168[iVar10] = afStack_88[iVar10] + local_168[iVar10];
                        }
                        iVar10 = iVar10 + 1;
                      } while (iVar10 < 8);
                      local_1b8 = local_1b8 + param_4 * 2;
                      local_1cc = local_1cc + param_5 * 2;
                      local_194 = local_194 + -1;
                      puVar4 = local_1c0;
                    } while (local_194 != 0);
                  }
                  local_1bc = local_1bc + 1;
                } while (local_1bc < 2);
              }
            }
          }
          local_184 = local_184 + 3;
          local_1b4 = local_1b4 + -3;
          param_6 = param_6 + 0x18;
          if (param_7 <= local_184) {
            return;
          }
        }
      }
    }
  }
  return;
}

