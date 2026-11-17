/* sub_445BF0 @ 00445bf0   7026 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_445BF0(int param_1,int param_2,int param_3,int param_4,int param_5,float *param_6,
               int param_7,int param_8,undefined4 param_9,uint param_10)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  ushort *puVar7;
  float *pfVar8;
  uint uVar9;
  float *pfVar10;
  uint uVar11;
  float *pfVar12;
  int iVar13;
  float fVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  float fVar18;
  int iVar19;
  int iVar20;
  float fVar21;
  uint local_1d8;
  uint local_1d4;
  int local_1d0;
  int local_1cc;
  uint local_1c8;
  int local_1c4;
  uint local_1c0;
  int local_1bc;
  uint local_1b8;
  int local_1b4;
  int local_1b0;
  int local_1a8;
  int local_1a4;
  int local_19c;
  int local_198;
  int local_194;
  int local_190;
  ushort local_18c;
  ushort uStack_18a;
  float afStack_180 [8];
  uint local_160;
  undefined4 uStack_15c;
  uint local_158;
  undefined4 uStack_154;
  uint local_150;
  undefined4 uStack_14c;
  uint local_148;
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
  uint local_108;
  undefined4 uStack_104;
  int aiStack_100 [8];
  float afStack_e0 [3];
  int local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float afStack_c0 [8];
  float afStack_a0 [8];
  float afStack_80 [8];
  float afStack_60 [8];
  float afStack_40 [8];
  undefined4 auStack_20 [8];
  
  uVar15 = param_10 >> 1;
  uVar9 = (param_10 & 0x40) << 3;
  uVar11 = param_10 & 0x3f;
  iVar13 = 0;
  uVar16 = uVar15 & 0x180 | uVar9 | uVar11;
  if (param_3 != 0) {
    sub_447770(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,0,0)
    ;
    return;
  }
  if (param_8 == 0) {
    if ((uVar15 & 0x80 | uVar9 | uVar11) == 1) {
      local_190 = 0;
      if (0 < param_7) {
        local_1c4 = param_7;
        param_6 = param_6 + 0x11;
        do {
          if (local_1c4 < 3) {
            return;
          }
          if (param_6[-8] <= param_6[-0x10]) {
            if (param_6[-8] <= *param_6) {
              pfVar8 = param_6 + -9;
              if (param_6[-0x10] <= *param_6) {
                pfVar10 = param_6 + -0x11;
                goto LAB_00446fcc;
              }
              pfVar10 = param_6 + -1;
              pfVar12 = param_6 + -0x11;
            }
            else {
              pfVar8 = param_6 + -1;
              pfVar10 = param_6 + -9;
              pfVar12 = param_6 + -0x11;
            }
          }
          else if (*param_6 <= param_6[-8]) {
            if (*param_6 <= param_6[-0x10]) {
              pfVar8 = param_6 + -1;
              pfVar10 = param_6 + -0x11;
              pfVar12 = param_6 + -9;
            }
            else {
              pfVar8 = param_6 + -0x11;
              pfVar10 = param_6 + -1;
              pfVar12 = param_6 + -9;
            }
          }
          else {
            pfVar8 = param_6 + -0x11;
            pfVar10 = param_6 + -9;
LAB_00446fcc:
            pfVar12 = param_6 + -1;
          }
          fVar4 = pfVar8[4];
          uStack_154 = 0;
          local_158 = (uint)fVar4 & 0xff0000;
          uStack_124 = 0;
          fVar14 = pfVar10[4];
          fVar18 = pfVar12[4];
          local_128 = (uint)fVar14 & 0xff0000;
          uStack_15c = 0;
          local_160 = (uint)fVar18 & 0xff0000;
          uStack_134 = 0;
          afStack_180[6] = (float)local_158 * _DAT_0056e4d4;
          local_138 = (uint)fVar4 & 0xff00;
          uStack_144 = 0;
          local_148 = (uint)fVar14 & 0xff00;
          local_120 = (uint)fVar4 & 0xff;
          local_130 = (uint)fVar18 & 0xff00;
          afStack_a0[6] = (float)local_128 * _DAT_0056e4d4;
          iVar13 = 0;
          uStack_12c = 0;
          uStack_11c = 0;
          local_140 = (uint)fVar14 & 0xff;
          uStack_13c = 0;
          local_118 = (uint)fVar18 & 0xff;
          uStack_114 = 0;
          afStack_c0[6] = (float)local_160 * _DAT_0056e4d4;
          afStack_180[5] = (float)local_138 * _DAT_0056e118;
          afStack_a0[5] = (float)local_148 * _DAT_0056e118;
          afStack_c0[5] = (float)local_130 * _DAT_0056e118;
          afStack_180[2] = (float)local_120;
          afStack_a0[2] = (float)local_140;
          afStack_c0[2] = (float)local_118;
          afStack_180[3] = pfVar8[2] * _DAT_0056e1cc;
          afStack_a0[3] = pfVar10[2] * _DAT_0056e1cc;
          afStack_c0[3] = pfVar12[2] * _DAT_0056e1cc;
          if (pfVar8[1] != pfVar12[1]) {
            fVar4 = pfVar12[1];
            fVar14 = pfVar8[1];
            fVar18 = (pfVar10[1] - pfVar8[1]) / (fVar4 - fVar14);
            fVar21 = (*pfVar12 - *pfVar8) * fVar18 + *pfVar8;
            if (fVar21 != *pfVar10) {
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x6cU) != 0) {
                  afStack_40[iVar13] =
                       (afStack_c0[iVar13] - afStack_180[iVar13]) * fVar18 + afStack_180[iVar13];
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              fVar18 = *pfVar10;
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x6cU) != 0) {
                  afStack_60[iVar13] =
                       (afStack_a0[iVar13] - afStack_40[iVar13]) *
                       (_DAT_0056e008 / (fVar18 - fVar21));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x6cU) != 0) {
                  afStack_80[iVar13] =
                       (afStack_c0[iVar13] - afStack_180[iVar13]) *
                       (_DAT_0056e008 / (fVar4 - fVar14));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              uVar9 = __ftol();
              local_1b0 = __ftol();
              iVar13 = __ftol();
              if (iVar13 != uVar9) {
                fVar4 = pfVar8[1];
                iVar17 = 0;
                do {
                  if ((1 << ((byte)iVar17 & 0x1f) & 0x6cU) != 0) {
                    afStack_180[iVar17] =
                         ((float)(int)uVar9 - (fVar4 - _DAT_0056e158)) * afStack_80[iVar17] +
                         afStack_180[iVar17];
                  }
                  iVar17 = iVar17 + 1;
                } while (iVar17 < 8);
                uVar11 = __ftol();
                local_108 = __ftol();
                local_19c = __ftol();
                iVar17 = __ftol();
                iVar2 = 0;
                do {
                  if ((1 << ((byte)iVar2 & 0x1f) & 0x6cU) != 0) {
                    fVar4 = (float)__ftol();
                    afStack_e0[iVar2] = fVar4;
                    iVar19 = __ftol();
                    aiStack_100[iVar2] = iVar19;
                    uVar6 = __ftol();
                    auStack_20[iVar2] = uVar6;
                  }
                  iVar2 = iVar2 + 1;
                } while (iVar2 < 8);
                local_1a8 = param_1 + uVar9 * param_4 * 2;
                local_1c0 = param_2 + uVar9 * param_5 * 2;
                local_1a4 = 0;
                local_1d4 = uVar11;
                do {
                  if (local_1a4 == 0) {
                    local_1d0 = __ftol();
                  }
                  else {
                    local_1d0 = __ftol();
                    local_1b0 = iVar13;
                    local_19c = iVar17;
                  }
                  if ((int)uVar9 < local_1b0) {
                    local_198 = local_1b0 - uVar9;
                    local_110 = uVar9 + local_198;
                    do {
                      local_150 = ((uVar11 & 0xffff0000) - uVar11) + 0xffff;
                      iVar2 = 0;
                      uStack_14c = 0;
                      do {
                        if ((1 << ((byte)iVar2 & 0x1f) & 0x6cU) != 0) {
                          fVar4 = (float)__ftol();
                          afStack_e0[iVar2] = fVar4;
                        }
                        iVar2 = iVar2 + 1;
                      } while (iVar2 < 8);
                      iVar2 = (int)local_1d4 >> 0x10;
                      puVar7 = (ushort *)(local_1c0 + iVar2 * 2);
                      local_1d8 = (local_1d0 >> 0x10) - iVar2;
                      iVar2 = local_1a8 + iVar2 * 2;
                      if ((int)local_1d8 < 0) {
                        if (0x7fffffff < local_1d8) {
                          iVar2 = iVar2 - (int)puVar7;
                          local_1d8 = -local_1d8;
                          fVar4 = local_c8;
                          iVar19 = local_d4;
                          fVar14 = local_cc;
                          fVar18 = afStack_e0[2];
                          do {
                            puVar7 = puVar7 + -1;
                            fVar14 = (float)((int)fVar14 - aiStack_100[5]);
                            iVar19 = iVar19 - aiStack_100[3];
                            fVar4 = (float)((int)fVar4 - aiStack_100[6]);
                            fVar18 = (float)((int)fVar18 - aiStack_100[2]);
                            uStack_18a = (ushort)((uint)iVar19 >> 0x10);
                            if ((iVar19 >> 0x10 & 0xffffU) <= (uint)*puVar7) {
                              *puVar7 = uStack_18a;
                              *(ushort *)(iVar2 + (int)puVar7) =
                                   (ushort)((int)fVar14 >> 0xe) & 0x3e0 |
                                   (ushort)((int)fVar18 >> 0x13) & 0x1f |
                                   (ushort)((int)fVar4 >> 9) & 0x7c00;
                            }
                            local_1d8 = local_1d8 + -1;
                          } while (local_1d8 != 0);
                        }
                      }
                      else if (0 < (int)local_1d8) {
                        iVar2 = iVar2 - (int)puVar7;
                        fVar4 = local_c8;
                        iVar19 = local_d4;
                        fVar14 = local_cc;
                        fVar18 = afStack_e0[2];
                        do {
                          local_18c = (ushort)((uint)iVar19 >> 0x10);
                          if ((iVar19 >> 0x10 & 0xffffU) <= (uint)*puVar7) {
                            *puVar7 = local_18c;
                            *(ushort *)((int)puVar7 + iVar2) =
                                 (ushort)((int)fVar14 >> 0xe) & 0x3e0 |
                                 (ushort)((int)fVar18 >> 0x13) & 0x1f |
                                 (ushort)((int)fVar4 >> 9) & 0x7c00;
                          }
                          fVar14 = (float)((int)fVar14 + aiStack_100[5]);
                          fVar4 = (float)((int)fVar4 + aiStack_100[6]);
                          iVar19 = iVar19 + aiStack_100[3];
                          fVar18 = (float)((int)fVar18 + aiStack_100[2]);
                          puVar7 = puVar7 + 1;
                          local_1d8 = local_1d8 - 1;
                        } while (local_1d8 != 0);
                      }
                      uVar11 = local_1d4 + local_108;
                      local_1d0 = local_1d0 + local_19c;
                      iVar2 = 0;
                      do {
                        if ((1 << ((byte)iVar2 & 0x1f) & 0x6cU) != 0) {
                          afStack_180[iVar2] = afStack_80[iVar2] + afStack_180[iVar2];
                        }
                        iVar2 = iVar2 + 1;
                      } while (iVar2 < 8);
                      local_1a8 = local_1a8 + param_4 * 2;
                      local_1c0 = local_1c0 + param_5 * 2;
                      local_198 = local_198 + -1;
                      uVar9 = local_110;
                      local_1d4 = uVar11;
                    } while (local_198 != 0);
                  }
                  local_1a4 = local_1a4 + 1;
                } while (local_1a4 < 2);
              }
            }
          }
          local_190 = local_190 + 3;
          local_1c4 = local_1c4 + -3;
          param_6 = param_6 + 0x18;
        } while (local_190 < param_7);
      }
    }
    else if (0 < param_7) {
      param_6 = param_6 + 0x11;
      iVar17 = param_7;
      while (2 < iVar17) {
        if (param_6[-8] <= param_6[-0x10]) {
          if (param_6[-8] <= *param_6) {
            pfVar8 = param_6 + -9;
            if (param_6[-0x10] <= *param_6) {
              pfVar10 = param_6 + -0x11;
              goto LAB_00446ed0;
            }
            pfVar10 = param_6 + -1;
            pfVar12 = param_6 + -0x11;
          }
          else {
            pfVar8 = param_6 + -1;
            pfVar10 = param_6 + -9;
            pfVar12 = param_6 + -0x11;
          }
        }
        else if (*param_6 <= param_6[-8]) {
          if (*param_6 <= param_6[-0x10]) {
            pfVar8 = param_6 + -1;
            pfVar10 = param_6 + -0x11;
            pfVar12 = param_6 + -9;
          }
          else {
            pfVar8 = param_6 + -0x11;
            pfVar10 = param_6 + -1;
            pfVar12 = param_6 + -9;
          }
        }
        else {
          pfVar8 = param_6 + -0x11;
          pfVar10 = param_6 + -9;
LAB_00446ed0:
          pfVar12 = param_6 + -1;
        }
        sub_43CD60(param_1,param_2,0,param_4,param_5,pfVar8,pfVar10,pfVar12,uVar16);
        iVar13 = iVar13 + 3;
        iVar17 = iVar17 + -3;
        param_6 = param_6 + 0x18;
        if (param_7 <= iVar13) {
          return;
        }
      }
    }
  }
  else {
    uVar11 = uVar15 & 0x80 | uVar9 | uVar11;
    if (uVar11 == 0x3a) {
      local_190 = 0;
      if (0 < param_7) {
        local_1b4 = param_7;
        pfVar8 = param_6 + 0x11;
        while (2 < local_1b4) {
          pfVar10 = param_6;
          if (pfVar8[-8] <= param_6[1]) {
            pfVar12 = param_6;
            if (pfVar8[-8] <= *pfVar8) {
              pfVar1 = pfVar8 + -9;
              if (param_6[1] <= *pfVar8) goto LAB_00446687;
              pfVar10 = pfVar8 + -1;
            }
            else {
              pfVar1 = pfVar8 + -1;
              pfVar10 = pfVar8 + -9;
            }
          }
          else {
            pfVar1 = param_6;
            if (*pfVar8 <= pfVar8[-8]) {
              if (*pfVar8 <= param_6[1]) {
                pfVar1 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
              else {
                pfVar10 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
            }
            else {
              pfVar10 = pfVar8 + -9;
LAB_00446687:
              pfVar12 = pfVar8 + -1;
            }
          }
          fVar4 = pfVar1[4];
          uStack_154 = 0;
          local_158 = (uint)fVar4 & 0xff0000;
          uStack_124 = 0;
          fVar14 = pfVar10[4];
          fVar18 = pfVar12[4];
          local_128 = (uint)fVar14 & 0xff0000;
          uStack_15c = 0;
          local_160 = (uint)fVar18 & 0xff0000;
          uStack_134 = 0;
          afStack_180[6] = (float)local_158 * _DAT_0056e4d4;
          local_138 = (uint)fVar4 & 0xff00;
          uStack_144 = 0;
          local_148 = (uint)fVar14 & 0xff00;
          uStack_12c = 0;
          local_130 = (uint)fVar18 & 0xff00;
          uStack_11c = 0;
          afStack_a0[6] = (float)local_128 * _DAT_0056e4d4;
          local_120 = (uint)fVar4 & 0xff;
          uStack_13c = 0;
          local_140 = (uint)fVar14 & 0xff;
          afStack_c0[6] = (float)local_160 * _DAT_0056e4d4;
          local_118 = (uint)fVar18 & 0xff;
          iVar13 = 0;
          uStack_114 = 0;
          uStack_14c = 0;
          local_150 = (uint)fVar4 >> 0x18;
          uStack_10c = 0;
          afStack_180[5] = (float)local_138 * _DAT_0056e118;
          local_110 = (uint)fVar14 >> 0x18;
          uStack_104 = 0;
          local_108 = (uint)fVar18 >> 0x18;
          afStack_a0[5] = (float)local_148 * _DAT_0056e118;
          afStack_c0[5] = (float)local_130 * _DAT_0056e118;
          afStack_180[2] = (float)local_120;
          afStack_a0[2] = (float)local_140;
          afStack_c0[2] = (float)local_118;
          afStack_180[4] = _DAT_0056e0c4 - (float)local_150;
          afStack_a0[4] = _DAT_0056e0c4 - (float)local_110;
          afStack_c0[4] = _DAT_0056e0c4 - (float)local_108;
          if (pfVar1[1] != pfVar12[1]) {
            fVar4 = pfVar12[1];
            fVar14 = pfVar1[1];
            fVar18 = (pfVar10[1] - pfVar1[1]) / (fVar4 - fVar14);
            fVar21 = (*pfVar12 - *pfVar1) * fVar18 + *pfVar1;
            if (fVar21 != *pfVar10) {
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_40[iVar13] =
                       (afStack_c0[iVar13] - afStack_180[iVar13]) * fVar18 + afStack_180[iVar13];
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              fVar18 = *pfVar10;
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_60[iVar13] =
                       (afStack_a0[iVar13] - afStack_40[iVar13]) *
                       (_DAT_0056e008 / (fVar18 - fVar21));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_80[iVar13] =
                       (afStack_c0[iVar13] - afStack_180[iVar13]) *
                       (_DAT_0056e008 / (fVar4 - fVar14));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar13 = __ftol();
              uVar9 = __ftol();
              iVar17 = __ftol();
              if (iVar17 != iVar13) {
                fVar4 = pfVar1[1];
                iVar2 = 0;
                do {
                  if ((1 << ((byte)iVar2 & 0x1f) & 0x74U) != 0) {
                    afStack_180[iVar2] =
                         ((float)iVar13 - (fVar4 - _DAT_0056e158)) * afStack_80[iVar2] +
                         afStack_180[iVar2];
                  }
                  iVar2 = iVar2 + 1;
                } while (iVar2 < 8);
                iVar2 = __ftol();
                iVar19 = __ftol();
                local_1c4 = __ftol();
                iVar3 = __ftol();
                iVar20 = 0;
                do {
                  if ((1 << ((byte)iVar20 & 0x1f) & 0x74U) != 0) {
                    fVar4 = (float)__ftol();
                    afStack_e0[iVar20] = fVar4;
                    iVar5 = __ftol();
                    aiStack_100[iVar20] = iVar5;
                    uVar6 = __ftol();
                    auStack_20[iVar20] = uVar6;
                  }
                  iVar20 = iVar20 + 1;
                } while (iVar20 < 8);
                local_1bc = param_1 + iVar13 * param_4 * 2;
                local_1c8 = 0;
                local_1d4 = uVar9;
                local_198 = iVar2;
                do {
                  if (local_1c8 == 0) {
                    local_1cc = __ftol();
                  }
                  else {
                    local_1cc = __ftol();
                    uVar9 = iVar17;
                    local_1d4 = iVar17;
                    local_1c4 = iVar3;
                  }
                  if (iVar13 < (int)uVar9) {
                    local_1c0 = uVar9 - iVar13;
                    iVar13 = iVar13 + local_1c0;
                    do {
                      iVar20 = 0;
                      do {
                        if ((1 << ((byte)iVar20 & 0x1f) & 0x74U) != 0) {
                          fVar4 = (float)__ftol();
                          afStack_e0[iVar20] = fVar4;
                        }
                        iVar20 = iVar20 + 1;
                      } while (iVar20 < 8);
                      local_1b8 = (local_1cc >> 0x10) - (iVar2 >> 0x10);
                      puVar7 = (ushort *)(local_1bc + (iVar2 >> 0x10) * 2);
                      if ((int)local_1b8 < 0) {
                        if (0x7fffffff < local_1b8) {
                          local_1b8 = -local_1b8;
                          fVar4 = local_c8;
                          fVar14 = local_d0;
                          fVar18 = local_cc;
                          fVar21 = afStack_e0[2];
                          do {
                            puVar7 = puVar7 + -1;
                            fVar18 = (float)((int)fVar18 - aiStack_100[5]);
                            fVar14 = (float)((int)fVar14 - aiStack_100[4]);
                            fVar4 = (float)((int)fVar4 - aiStack_100[6]);
                            fVar21 = (float)((int)fVar21 - aiStack_100[2]);
                            uVar9 = ((*puVar7 & 0x3e0) << 0x10 | *puVar7 & 0x3e07c1f) *
                                    ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                            *puVar7 = ((ushort)((int)fVar18 >> 0xe) & 0x3e0 |
                                       (ushort)((int)fVar21 >> 0x13) & 0x1f |
                                      (ushort)((int)fVar4 >> 9) & 0x7c00) +
                                      ((ushort)(uVar9 >> 0x15) | (ushort)(uVar9 >> 5));
                            local_1b8 = local_1b8 + -1;
                          } while (local_1b8 != 0);
                        }
                      }
                      else {
                        fVar4 = local_c8;
                        fVar14 = local_d0;
                        fVar18 = local_cc;
                        fVar21 = afStack_e0[2];
                        if (0 < (int)local_1b8) {
                          do {
                            uVar9 = ((*puVar7 & 0x3e0) << 0x10 | *puVar7 & 0x3e07c1f) *
                                    ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                            *puVar7 = ((ushort)((int)fVar18 >> 0xe) & 0x3e0 |
                                       (ushort)((int)fVar21 >> 0x13) & 0x1f |
                                      (ushort)((int)fVar4 >> 9) & 0x7c00) +
                                      ((ushort)(uVar9 >> 0x15) | (ushort)(uVar9 >> 5));
                            puVar7 = puVar7 + 1;
                            local_1b8 = local_1b8 - 1;
                            fVar4 = (float)((int)fVar4 + aiStack_100[6]);
                            fVar14 = (float)((int)fVar14 + aiStack_100[4]);
                            fVar18 = (float)((int)fVar18 + aiStack_100[5]);
                            fVar21 = (float)((int)fVar21 + aiStack_100[2]);
                          } while (local_1b8 != 0);
                        }
                      }
                      iVar2 = local_198 + iVar19;
                      local_1cc = local_1cc + local_1c4;
                      iVar20 = 0;
                      do {
                        if ((1 << ((byte)iVar20 & 0x1f) & 0x74U) != 0) {
                          afStack_180[iVar20] = afStack_80[iVar20] + afStack_180[iVar20];
                        }
                        iVar20 = iVar20 + 1;
                      } while (iVar20 < 8);
                      local_1bc = local_1bc + param_4 * 2;
                      local_1c0 = local_1c0 + -1;
                      uVar9 = local_1d4;
                      local_198 = iVar2;
                    } while (local_1c0 != 0);
                  }
                  local_1c8 = local_1c8 + 1;
                } while ((int)local_1c8 < 2);
              }
            }
          }
          local_190 = local_190 + 1;
          pfVar8 = pfVar8 + 8;
          local_1b4 = local_1b4 + -1;
          if (param_7 <= local_190) {
            return;
          }
        }
      }
    }
    else if (uVar11 == 0x3b) {
      local_190 = 0;
      if (0 < param_7) {
        local_1bc = param_7;
        pfVar8 = param_6 + 0x11;
        while (2 < local_1bc) {
          pfVar10 = param_6;
          if (pfVar8[-8] <= param_6[1]) {
            pfVar12 = param_6;
            if (pfVar8[-8] <= *pfVar8) {
              pfVar1 = pfVar8 + -9;
              if (param_6[1] <= *pfVar8) goto LAB_00445e37;
              pfVar10 = pfVar8 + -1;
            }
            else {
              pfVar1 = pfVar8 + -1;
              pfVar10 = pfVar8 + -9;
            }
          }
          else {
            pfVar1 = param_6;
            if (*pfVar8 <= pfVar8[-8]) {
              if (*pfVar8 <= param_6[1]) {
                pfVar1 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
              else {
                pfVar10 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
            }
            else {
              pfVar10 = pfVar8 + -9;
LAB_00445e37:
              pfVar12 = pfVar8 + -1;
            }
          }
          fVar4 = pfVar1[4];
          uStack_10c = 0;
          local_110 = (uint)fVar4 & 0xff0000;
          uStack_104 = 0;
          fVar14 = pfVar10[4];
          fVar18 = pfVar12[4];
          local_108 = (uint)fVar14 & 0xff0000;
          uStack_14c = 0;
          afStack_180[6] = (float)local_110 * _DAT_0056e4d4;
          local_150 = (uint)fVar4 & 0xff00;
          uStack_114 = 0;
          local_118 = (uint)fVar14 & 0xff00;
          uStack_13c = 0;
          local_140 = (uint)fVar18 & 0xff00;
          uStack_11c = 0;
          afStack_a0[6] = (float)local_108 * _DAT_0056e4d4;
          local_120 = (uint)fVar4 & 0xff;
          uStack_12c = 0;
          local_130 = (uint)fVar14 & 0xff;
          local_c8 = (float)((uint)fVar18 & 0xff0000) * _DAT_0056e4d4;
          local_148 = (uint)fVar18 & 0xff;
          iVar13 = 0;
          uStack_144 = 0;
          uStack_134 = 0;
          local_138 = (uint)fVar4 >> 0x18;
          uStack_15c = 0;
          afStack_180[5] = (float)local_150 * _DAT_0056e118;
          local_160 = (uint)fVar14 >> 0x18;
          uStack_124 = 0;
          local_128 = (uint)fVar18 >> 0x18;
          afStack_a0[5] = (float)local_118 * _DAT_0056e118;
          local_cc = (float)local_140 * _DAT_0056e118;
          afStack_180[2] = (float)local_120;
          afStack_a0[2] = (float)local_130;
          afStack_e0[2] = (float)local_148;
          afStack_180[4] = _DAT_0056e0c4 - (float)local_138;
          afStack_a0[4] = _DAT_0056e0c4 - (float)local_160;
          local_d0 = _DAT_0056e0c4 - (float)local_128;
          if (pfVar1[1] != pfVar12[1]) {
            fVar4 = pfVar12[1];
            fVar14 = pfVar1[1];
            fVar18 = (pfVar10[1] - pfVar1[1]) / (fVar4 - fVar14);
            fVar21 = (*pfVar12 - *pfVar1) * fVar18 + *pfVar1;
            if (fVar21 != *pfVar10) {
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_40[iVar13] =
                       (afStack_e0[iVar13] - afStack_180[iVar13]) * fVar18 + afStack_180[iVar13];
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              fVar18 = *pfVar10;
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_60[iVar13] =
                       (afStack_a0[iVar13] - afStack_40[iVar13]) *
                       (_DAT_0056e008 / (fVar18 - fVar21));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar13 = 0;
              do {
                if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                  afStack_80[iVar13] =
                       (afStack_e0[iVar13] - afStack_180[iVar13]) *
                       (_DAT_0056e008 / (fVar4 - fVar14));
                }
                iVar13 = iVar13 + 1;
              } while (iVar13 < 8);
              iVar17 = __ftol();
              iVar13 = __ftol();
              iVar2 = __ftol();
              if (iVar2 != iVar17) {
                fVar4 = pfVar1[1];
                iVar19 = 0;
                do {
                  if ((1 << ((byte)iVar19 & 0x1f) & 0x74U) != 0) {
                    afStack_180[iVar19] =
                         ((float)iVar17 - (fVar4 - _DAT_0056e158)) * afStack_80[iVar19] +
                         afStack_180[iVar19];
                  }
                  iVar19 = iVar19 + 1;
                } while (iVar19 < 8);
                uVar9 = __ftol();
                iVar19 = __ftol();
                local_1d0 = __ftol();
                iVar3 = __ftol();
                iVar20 = 0;
                do {
                  if ((1 << ((byte)iVar20 & 0x1f) & 0x74U) != 0) {
                    fVar4 = (float)__ftol();
                    afStack_c0[iVar20] = fVar4;
                    iVar5 = __ftol();
                    aiStack_100[iVar20] = iVar5;
                    uVar6 = __ftol();
                    auStack_20[iVar20] = uVar6;
                  }
                  iVar20 = iVar20 + 1;
                } while (iVar20 < 8);
                local_1d4 = param_1 + iVar17 * param_4 * 2;
                local_1b8 = 0;
                local_1c8 = uVar9;
                local_194 = iVar13;
                do {
                  if (local_1b8 == 0) {
                    local_1cc = __ftol();
                  }
                  else {
                    local_1cc = __ftol();
                    iVar13 = iVar2;
                    local_1d0 = iVar3;
                    local_194 = iVar2;
                  }
                  if (iVar17 < iVar13) {
                    local_19c = iVar13 - iVar17;
                    iVar17 = iVar17 + local_19c;
                    do {
                      local_158 = ((uVar9 & 0xffff0000) - uVar9) + 0xffff;
                      iVar13 = 0;
                      uStack_154 = 0;
                      do {
                        if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                          fVar4 = (float)__ftol();
                          afStack_c0[iVar13] = fVar4;
                        }
                        iVar13 = iVar13 + 1;
                      } while (iVar13 < 8);
                      local_1c0 = (local_1cc >> 0x10) - ((int)uVar9 >> 0x10);
                      puVar7 = (ushort *)(local_1d4 + ((int)uVar9 >> 0x10) * 2);
                      if ((int)local_1c0 < 0) {
                        if (0x7fffffff < local_1c0) {
                          local_1c0 = -local_1c0;
                          fVar4 = afStack_c0[6];
                          fVar14 = afStack_c0[4];
                          fVar18 = afStack_c0[5];
                          fVar21 = afStack_c0[2];
                          do {
                            puVar7 = puVar7 + -1;
                            fVar18 = (float)((int)fVar18 - aiStack_100[5]);
                            fVar14 = (float)((int)fVar14 - aiStack_100[4]);
                            fVar4 = (float)((int)fVar4 - aiStack_100[6]);
                            fVar21 = (float)((int)fVar21 - aiStack_100[2]);
                            uVar9 = ((*puVar7 & 0x3e0) << 0x10 | *puVar7 & 0x3e07c1f) *
                                    ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                            *puVar7 = ((ushort)((int)fVar18 >> 0xe) & 0x3e0 |
                                       (ushort)((int)fVar21 >> 0x13) & 0x1f |
                                      (ushort)((int)fVar4 >> 9) & 0x7c00) +
                                      ((ushort)(uVar9 >> 0x15) | (ushort)(uVar9 >> 5));
                            local_1c0 = local_1c0 + -1;
                          } while (local_1c0 != 0);
                        }
                      }
                      else {
                        fVar4 = afStack_c0[6];
                        fVar14 = afStack_c0[4];
                        fVar18 = afStack_c0[5];
                        fVar21 = afStack_c0[2];
                        if (0 < (int)local_1c0) {
                          do {
                            uVar9 = ((*puVar7 & 0x3e0) << 0x10 | *puVar7 & 0x3e07c1f) *
                                    ((int)fVar14 >> 0x13) & 0x7c0f83e0;
                            *puVar7 = ((ushort)((int)fVar18 >> 0xe) & 0x3e0 |
                                       (ushort)((int)fVar21 >> 0x13) & 0x1f |
                                      (ushort)((int)fVar4 >> 9) & 0x7c00) +
                                      ((ushort)(uVar9 >> 0x15) | (ushort)(uVar9 >> 5));
                            puVar7 = puVar7 + 1;
                            local_1c0 = local_1c0 - 1;
                            fVar4 = (float)((int)fVar4 + aiStack_100[6]);
                            fVar14 = (float)((int)fVar14 + aiStack_100[4]);
                            fVar18 = (float)((int)fVar18 + aiStack_100[5]);
                            fVar21 = (float)((int)fVar21 + aiStack_100[2]);
                          } while (local_1c0 != 0);
                        }
                      }
                      uVar9 = local_1c8 + iVar19;
                      local_1cc = local_1cc + local_1d0;
                      iVar13 = 0;
                      do {
                        if ((1 << ((byte)iVar13 & 0x1f) & 0x74U) != 0) {
                          afStack_180[iVar13] = afStack_80[iVar13] + afStack_180[iVar13];
                        }
                        iVar13 = iVar13 + 1;
                      } while (iVar13 < 8);
                      local_1d4 = local_1d4 + param_4 * 2;
                      local_19c = local_19c + -1;
                      iVar13 = local_194;
                      local_1c8 = uVar9;
                    } while (local_19c != 0);
                  }
                  local_1b8 = local_1b8 + 1;
                } while ((int)local_1b8 < 2);
              }
            }
          }
          local_190 = local_190 + 1;
          pfVar8 = pfVar8 + 8;
          local_1bc = local_1bc + -1;
          if (param_7 <= local_190) {
            return;
          }
        }
      }
    }
    else {
      iVar13 = 0;
      if (0 < param_7) {
        pfVar8 = param_6 + 0x11;
        iVar17 = param_7;
        while (2 < iVar17) {
          pfVar10 = param_6;
          if (pfVar8[-8] <= param_6[1]) {
            pfVar12 = param_6;
            if (pfVar8[-8] <= *pfVar8) {
              pfVar1 = pfVar8 + -9;
              if (param_6[1] <= *pfVar8) goto LAB_00445d39;
              pfVar10 = pfVar8 + -1;
            }
            else {
              pfVar1 = pfVar8 + -1;
              pfVar10 = pfVar8 + -9;
            }
          }
          else {
            pfVar1 = param_6;
            if (*pfVar8 <= pfVar8[-8]) {
              if (*pfVar8 <= param_6[1]) {
                pfVar1 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
              else {
                pfVar10 = pfVar8 + -1;
                pfVar12 = pfVar8 + -9;
              }
            }
            else {
              pfVar10 = pfVar8 + -9;
LAB_00445d39:
              pfVar12 = pfVar8 + -1;
            }
          }
          sub_43CD60(param_1,param_2,0,param_4,param_5,pfVar1,pfVar10,pfVar12,uVar16);
          iVar13 = iVar13 + 1;
          pfVar8 = pfVar8 + 8;
          iVar17 = iVar17 + -1;
          if (param_7 <= iVar13) {
            return;
          }
        }
      }
    }
  }
  return;
}

