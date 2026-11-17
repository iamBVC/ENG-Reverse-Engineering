/* Selected Ghidra export at 004321e0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4321E0(void)

{
  int iVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  char cVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  float *pfVar9;
  byte bVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  code *pcVar14;
  float fVar15;
  uint uVar16;
  int iVar17;
  int *piVar18;
  uint uVar19;
  float *pfVar20;
  undefined4 uVar21;
  uint uVar22;
  bool bVar23;
  byte bStack_132;
  char cStack_131;
  float *pfStack_130;
  float fStack_12c;
  byte bStack_126;
  undefined1 uStack_125;
  int iStack_124;
  int *piStack_120;
  float fStack_11c;
  uint uStack_118;
  uint uStack_114;
  float fStack_110;
  uint uStack_10c;
  undefined1 uStack_105;
  uint uStack_104;
  ushort *puStack_100;
  uint uStack_fc;
  int iStack_f8;
  uint uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  uint uStack_e4;
  uint uStack_e0;
  uint uStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  uint uStack_b8;
  uint uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  uint uStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float afStack_80 [4];
  uint uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  uint uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  uint uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  uint uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  piStack_120 = DAT_006d94b8;
  uStack_104 = DAT_00573ed0;
  puStack_100 = (ushort *)(DAT_00581154 + (DAT_006d9be8 * 5 + 10) * 4);
  iStack_f8 = (char)(byte)puStack_100[1] * 0x20 + DAT_0058114c;
  uStack_f4 = DAT_00573ed4;
  uStack_b4 = 0;
  iVar6 = ((*puStack_100 & 0x7000) >> 0xc) + (*puStack_100 >> 8 & 7) * 5;
  uStack_fc = (&DAT_00573ef8)[iVar6 * 3];
  uStack_118 = (&DAT_00573efc)[iVar6 * 3];
  if (DAT_006da320 != 0) {
    do {
      piVar8 = piStack_120;
      if ((char)piStack_120[4] == '\0') goto LAB_00434a1c;
      if (*(short *)((int)piStack_120 + 0x12) < 0) {
        fVar15 = (float)*piStack_120 * (float)_DAT_0056e020;
        fVar3 = (float)piStack_120[1] * (float)_DAT_0056e020;
        fVar2 = -((float)piStack_120[2] * (float)_DAT_0056e020);
        fStack_d8 = _DAT_0057db20 * fVar15 + _DAT_0057db40 * fVar2 + _DAT_0057db30 * fVar3 +
                    _DAT_0057db50;
        fStack_d4 = _DAT_0057db24 * fVar15 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar2 +
                    _DAT_0057db54;
        fStack_d0 = _DAT_0057db28 * fVar15 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar2 +
                    _DAT_0057db58;
        fStack_cc = _DAT_0057db2c * fVar15 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar2 +
                    _DAT_0057db5c;
        uStack_b8 = sub_401080(&fStack_d8);
        piVar18 = piVar8;
        if (uStack_b8 == 0) {
LAB_00432386:
          fVar15 = (float)((int)(short)piVar18[5] + *piVar18) * (float)_DAT_0056e020;
          if (*(short *)((int)piVar18 + 0x12) < -0x30) {
            iVar6 = -0x30;
          }
          else {
            iVar6 = (int)*(short *)((int)piVar18 + 0x12);
          }
          fStack_12c = (float)((int)*(short *)((int)piVar18 + 0x16) + piVar18[2]);
          fVar3 = (float)(piVar18[1] + iVar6 * 8) * (float)_DAT_0056e020;
          fVar2 = -((float)(int)fStack_12c * (float)_DAT_0056e020);
          fStack_b0 = _DAT_0057db20 * fVar15 + _DAT_0057db40 * fVar2 + _DAT_0057db30 * fVar3 +
                      _DAT_0057db50;
          fStack_ac = _DAT_0057db24 * fVar15 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar2 +
                      _DAT_0057db54;
          fStack_a8 = _DAT_0057db28 * fVar15 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar2 +
                      _DAT_0057db58;
          fStack_a4 = _DAT_0057db2c * fVar15 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar2 +
                      _DAT_0057db5c;
          uStack_90 = sub_401080(&fStack_b0);
          piVar8 = piVar18;
          if (uStack_90 == 0) {
LAB_004324bf:
            if ((((fStack_d4 < -fStack_cc) ||
                 ((fStack_d8 < fStack_cc * _DAT_0056e440 && (fStack_b0 < fStack_cc * _DAT_0056e440))
                 )) || ((fStack_cc * _DAT_0056e154 < fStack_d8 &&
                        (fStack_cc * _DAT_0056e154 < fStack_b0)))) ||
               (-(int)*(short *)((int)piVar8 + 0x12) < 7)) goto LAB_00434a18;
            fStack_bc = _DAT_0056e008 / fStack_cc;
            fStack_c8 = (fStack_d8 * fStack_bc + (float)_DAT_0056e038) * _DAT_00583388;
            fStack_c4 = ((float)_DAT_0056e038 - fStack_d4 * fStack_bc) * _DAT_0058338c;
            fStack_c0 = ((float)_DAT_0056e038 - fStack_d0 * fStack_bc) * (float)_DAT_0056e030;
            fStack_94 = _DAT_0056e008 / fStack_a4;
            fStack_a0 = (fStack_b0 * fStack_94 + (float)_DAT_0056e038) * _DAT_00583388;
            fStack_9c = ((float)_DAT_0056e038 - fStack_ac * fStack_94) * _DAT_0058338c;
            fStack_98 = ((float)_DAT_0056e038 - fStack_a8 * fStack_94) * (float)_DAT_0056e030;
            fStack_11c = (fStack_a4 + fStack_cc) * _DAT_0056e158;
            fStack_8c = fStack_9c - fStack_c4;
            fStack_88 = fStack_c8 - fStack_a0;
            pfStack_130 = (float *)SQRT(fStack_8c * fStack_8c + fStack_88 * fStack_88);
            fStack_8c = fStack_8c / (float)pfStack_130;
            fStack_88 = fStack_88 / (float)pfStack_130;
            fStack_e8 = _DAT_0056e00c / (float)pfStack_130;
            fStack_f0 = (float)DAT_00583374 * _DAT_0056e1dc * fStack_8c * _DAT_0056e158;
            fStack_ec = (float)DAT_00583378 * _DAT_0056e1d8 * fStack_88 * _DAT_0056e158;
            fStack_84 = fStack_e8;
            iVar6 = __ftol();
            bVar10 = (byte)(0xff - iVar6);
            uStack_10c = CONCAT31(uStack_10c._1_3_,bVar10);
            bStack_132 = (byte)(0xff - iVar6 >> 2);
            uStack_114 = CONCAT31(uStack_114._1_3_,bStack_132);
            bStack_126 = bStack_132 >> 1;
            uStack_e4 = CONCAT31(uStack_e4._1_3_,bVar10 >> 1);
            uStack_dc = CONCAT31(uStack_dc._1_3_,bStack_132 >> 1);
            (*(code *)PTR_sub_408390_00570360)(&bStack_126,&uStack_dc,&uStack_e4,&uStack_105,2);
            (*(code *)PTR_sub_408390_00570360)(&bStack_132,&uStack_114,&uStack_10c,&uStack_125,2);
            cVar5 = sub_40C510(&bStack_132,&uStack_114,&uStack_10c);
            if (cVar5 == '\0') {
              cVar5 = sub_40C510(&bStack_126,&uStack_dc,&uStack_e4);
              cStack_131 = '\0';
              if (cVar5 != '\0') goto LAB_00432779;
            }
            else {
LAB_00432779:
              cStack_131 = '\x01';
            }
            uVar19 = uStack_104;
            afStack_80[0] = fStack_c8 - fStack_f0;
            afStack_80[2] = fStack_c0;
            afStack_80[3] = fStack_bc;
            afStack_80[1] = fStack_c4 - fStack_ec;
            fStack_54 = fStack_bc;
            fStack_58 = fStack_c0;
            fStack_18 = fStack_98;
            fStack_60 = fStack_c8 + fStack_f0;
            fStack_38 = fStack_98;
            fStack_34 = fStack_94;
            fStack_5c = fStack_ec + fStack_c4;
            fStack_14 = fStack_94;
            fStack_40 = fStack_a0 + fStack_f0;
            uStack_70 = ((uint)CONCAT11(uStack_105,bStack_126) << 8 | uStack_dc & 0xff) << 8 |
                        uStack_e4 & 0xff;
            fStack_3c = fStack_ec + fStack_9c;
            fStack_20 = fStack_a0 - fStack_f0;
            uStack_c = 0;
            fStack_1c = fStack_9c - fStack_ec;
            uStack_30 = ((uint)CONCAT11(uStack_125,bStack_132) << 8 | uStack_114 & 0xff) << 8 |
                        uStack_10c & 0xff;
            uStack_2c = 0;
            uStack_4c = 0;
            uStack_6c = 0;
            uStack_8 = 0;
            uStack_28 = 0;
            uStack_48 = 0;
            uStack_68 = 0;
            uStack_4 = 0;
            uStack_24 = 0;
            uStack_44 = 0;
            uStack_64 = 0;
            uVar16 = (uint)(afStack_80[0] < _DAT_0056e00c);
            if (DAT_00583390 <= afStack_80[0]) {
              uVar16 = uVar16 | 2;
            }
            if (afStack_80[1] < _DAT_0056e00c) {
              uVar16 = uVar16 | 8;
            }
            if (DAT_00583394 <= afStack_80[1]) {
              uVar16 = uVar16 | 4;
            }
            uVar22 = (uint)(fStack_60 < _DAT_0056e00c);
            if (DAT_00583390 <= fStack_60) {
              uVar22 = uVar22 | 2;
            }
            if (fStack_5c < _DAT_0056e00c) {
              uVar22 = uVar22 | 8;
            }
            if (DAT_00583394 <= fStack_5c) {
              uVar22 = uVar22 | 4;
            }
            uVar13 = (uint)(fStack_40 < _DAT_0056e00c);
            if (DAT_00583390 <= fStack_40) {
              uVar13 = uVar13 | 2;
            }
            if (fStack_3c < _DAT_0056e00c) {
              uVar13 = uVar13 | 8;
            }
            if (DAT_00583394 <= fStack_3c) {
              uVar13 = uVar13 | 4;
            }
            uVar11 = (uint)(fStack_20 < _DAT_0056e00c);
            if (DAT_00583390 <= fStack_20) {
              uVar11 = uVar11 | 2;
            }
            if (fStack_1c < _DAT_0056e00c) {
              uVar11 = uVar11 | 8;
            }
            if (DAT_00583394 <= fStack_1c) {
              uVar11 = uVar11 | 4;
            }
            uStack_50 = uStack_70;
            uStack_10 = uStack_30;
            if (((~uVar11 | ~uVar13 | ~uVar22 | ~uVar16) & 0xffff) == 0xffff) {
              if (DAT_005833e4._1_1_ == '\0') {
                iVar6 = -1;
              }
              else {
                iVar6 = 0;
                if (uStack_104 == 0) {
                  iVar6 = -1;
                }
                else {
                  iStack_124 = __ftol();
                  if (iStack_124 < 0) {
                    iStack_124 = 0;
                  }
                  else if (0x7ff < iStack_124) {
                    iStack_124 = 0x7ff;
                  }
                }
              }
              uVar16 = uVar11 | uVar13 | uVar22 | uVar16;
              bVar23 = uVar16 == 0;
              if (bVar23) {
                pfStack_130 = (float *)sub_41ED90(0x80);
                if (pfStack_130 == (float *)0x0) goto LAB_00434a1c;
                pfVar20 = afStack_80;
                pfVar9 = pfStack_130;
                for (iVar12 = 0x20; iVar12 != 0; iVar12 = iVar12 + -1) {
                  *pfVar9 = *pfVar20;
                  pfVar20 = pfVar20 + 1;
                  pfVar9 = pfVar9 + 1;
                }
                fStack_110 = 5.60519e-45;
                uVar19 = uStack_104;
              }
              else {
                iVar12 = 0;
                for (uVar22 = uVar16; uVar22 != 0; uVar22 = (int)uVar22 >> 1) {
                  if ((uVar22 & 1) != 0) {
                    iVar12 = iVar12 + 1;
                  }
                }
                pfStack_130 = (float *)sub_41ED90((iVar12 * 3 + 3) * 0x40);
                if (pfStack_130 == (float *)0x0) {
                  return;
                }
                fStack_110 = (float)sub_43AC00(pfStack_130,afStack_80,4,uVar16);
              }
              fVar15 = fStack_110;
              if (iVar6 == -1) {
                uVar16 = (uint)bVar23;
                fStack_12c = fStack_110;
                uStack_e0 = uVar16;
                if (0 < (int)fStack_110) {
                  if (DAT_005833e1 == '\0') {
                    if (DAT_006d7c58 != 1) {
                      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                      DAT_006d7c58 = 1;
                    }
                    if (DAT_006d7c34 != (DAT_005833f2 != '\0') + 1) {
                      (**(code **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,9,(DAT_005833f2 != '\0') + '\x01');
                      DAT_006d7c34 = (DAT_005833f2 != '\0') + 1;
                    }
                    if (DAT_006d7c38 != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,0);
                      DAT_006d7c38 = '\0';
                    }
                    if (DAT_006d7c4e != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
                      DAT_006d7c4e = '\0';
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      DAT_006d7c39 = '\x01';
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                      DAT_006d7c48 = 4;
                    }
                    if (DAT_006d7c3a != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
                      DAT_006d7c3a = '\0';
                    }
                    if (DAT_006d7c50 != 0) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
                      DAT_006d7c50 = 0;
                    }
                    switch(uVar19) {
                    case 0:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                          DAT_006d7c4c = '\0';
                        }
                      }
                      else if (DAT_006d7c4d != '\0') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                        DAT_006d7c4d = '\0';
                      }
                      break;
                    case 1:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      iVar6 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar6) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar6);
                        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      }
                      if (DAT_006d7c44 != 6) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                        DAT_006d7c44 = 6;
                      }
                      break;
                    case 2:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                        DAT_006d7c40 = 2;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                      break;
                    case 3:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 5) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                        DAT_006d7c40 = 5;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                    }
                    switch(uStack_f4) {
                    case 0:
                    case 2:
                      if (DAT_006d7c5c != 2) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                        DAT_006d7c5c = 2;
                      }
                      break;
                    case 1:
                      if (DAT_006d7c5c != 3) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                        DAT_006d7c5c = 3;
                      }
                      break;
                    case 3:
                      if (DAT_006d7c5c != 4) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                        DAT_006d7c5c = 4;
                      }
                    }
                    (**(code **)(*DAT_00582cd4 + 0x70))
                              (DAT_00582cd4,(-(uVar16 != 0) & 2U) + 4,0x1c4,pfStack_130,fStack_12c,
                               0x1c);
                  }
                  else {
                    pcVar14 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar14 = sub_442BD0;
                    }
                    (*pcVar14)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,
                               pfStack_130,fStack_110,uVar16,0,((uVar19 | 4) << 2 | uStack_f4) << 5)
                    ;
                  }
                }
                if ((cStack_131 != '\0') &&
                   (uVar19 = uStack_104 | 2, fStack_12c = fStack_110, 0 < (int)fStack_110)) {
                  if (DAT_005833e1 == '\0') {
                    if (DAT_006d7c58 != 1) {
                      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                      DAT_006d7c58 = 1;
                    }
                    if (DAT_006d7c34 != (DAT_005833f2 != '\0') + 1) {
                      (**(code **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,9,(DAT_005833f2 != '\0') + '\x01');
                      DAT_006d7c34 = (DAT_005833f2 != '\0') + 1;
                    }
                    if (DAT_006d7c38 != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,0);
                      DAT_006d7c38 = '\0';
                    }
                    if (DAT_006d7c4e != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
                      DAT_006d7c4e = '\0';
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      DAT_006d7c39 = '\x01';
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                      DAT_006d7c48 = 4;
                    }
                    if (DAT_006d7c3a != '\0') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
                      DAT_006d7c3a = '\0';
                    }
                    if (DAT_006d7c50 != 0) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
                      DAT_006d7c50 = 0;
                    }
                    switch(uVar19) {
                    case 0:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                          DAT_006d7c4c = '\0';
                        }
                      }
                      else if (DAT_006d7c4d != '\0') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                        DAT_006d7c4d = '\0';
                      }
                      break;
                    case 1:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      iVar6 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar6) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar6);
                        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      }
                      if (DAT_006d7c44 != 6) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                        DAT_006d7c44 = 6;
                      }
                      break;
                    case 2:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                        DAT_006d7c40 = 2;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                      break;
                    case 3:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 5) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                        DAT_006d7c40 = 5;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                    }
                    switch(uStack_f4) {
                    case 0:
                    case 2:
                      if (DAT_006d7c5c != 2) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                        DAT_006d7c5c = 2;
                      }
                      break;
                    case 1:
                      if (DAT_006d7c5c != 3) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                        DAT_006d7c5c = 3;
                      }
                      break;
                    case 3:
                      if (DAT_006d7c5c != 4) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                        DAT_006d7c5c = 4;
                      }
                    }
                    (**(code **)(*DAT_00582cd4 + 0x70))
                              (DAT_00582cd4,(-(uStack_e0 != 0) & 2U) + 4,0x1c4,pfStack_130,
                               fStack_12c,0x1c);
                  }
                  else {
                    pcVar14 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar14 = sub_442BD0;
                    }
                    (*pcVar14)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,
                               pfStack_130,fStack_110,uVar16,0,
                               ((uStack_104 | 6) << 2 | uStack_f4) << 5);
                  }
                }
              }
              else {
                if (((cStack_131 != '\0') && (0 < (int)fStack_110)) &&
                   (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)) {
                  iVar12 = iVar6 * 0x800 + iStack_124;
                  *puVar7 = (&DAT_005f6ef8)[iVar12];
                  puVar7[3] = 0;
                  puVar7[4] = 0;
                  puVar7[5] = 0;
                  puVar7[6] = 0;
                  puVar7[1] = pfStack_130;
                  puVar7[2] = fVar15;
                  puVar7[7] = (uStack_f4 * 4 | uStack_104) << 0xc | (uint)bVar23 | 0x2040;
                  (&DAT_005f6ef8)[iVar12] = puVar7;
                }
                fVar15 = fStack_110;
                if ((0 < (int)fStack_110) &&
                   (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)) {
                  iVar6 = iVar6 * 0x800 + iStack_124;
                  *puVar7 = (&DAT_005f6ef8)[iVar6];
                  puVar7[1] = pfStack_130;
                  puVar7[2] = fVar15;
                  puVar7[3] = 0;
                  puVar7[4] = 0;
                  puVar7[5] = 0;
                  puVar7[6] = 0;
                  puVar7[7] = (uStack_f4 * 4 | uStack_104) << 0xc | (uint)bVar23 | 0x40;
                  (&DAT_005f6ef8)[iVar6] = puVar7;
                }
              }
            }
          }
          else if ((uStack_90 & 0x10) == 0) {
            piVar8 = piStack_120;
            if ((uStack_90 & 0x20) == 0) goto LAB_004324bf;
            *(undefined1 *)(piStack_120 + 4) = 0;
          }
        }
        else if ((uStack_b8 & 0x10) == 0) {
          piVar18 = piStack_120;
          if ((uStack_b8 & 0x20) == 0) goto LAB_00432386;
          *(undefined1 *)(piVar8 + 4) = 0;
        }
      }
      else {
        sub_41EC10((float)*piStack_120 * (float)_DAT_0056e020,
                   (float)piStack_120[1] * (float)_DAT_0056e020,
                   -((float)piStack_120[2] * (float)_DAT_0056e020),0x3c800000,0x3c800000,0x3c800000,
                   &DAT_006d7b68);
        _DAT_006d7bf4 = 0;
        _DAT_006d7be8 =
             _DAT_0057dc38 * _DAT_006d7b6c +
             _DAT_0057dc28 * _DAT_006d7b68 + _DAT_0057dc48 * _DAT_006d7b70;
        _DAT_006d7bec =
             _DAT_0057dc3c * _DAT_006d7b6c +
             _DAT_0057dc2c * _DAT_006d7b68 + _DAT_0057dc4c * _DAT_006d7b70;
        _DAT_006d7bf0 =
             _DAT_0057dc40 * _DAT_006d7b6c +
             _DAT_0057dc30 * _DAT_006d7b68 + _DAT_0057dc50 * _DAT_006d7b70;
        _DAT_006d7bf8 =
             _DAT_006d7b7c * _DAT_0057dc38 +
             _DAT_006d7b78 * _DAT_0057dc28 + _DAT_006d7b80 * _DAT_0057dc48;
        _DAT_006d7bfc =
             _DAT_006d7b78 * _DAT_0057dc2c +
             _DAT_006d7b7c * _DAT_0057dc3c + _DAT_006d7b80 * _DAT_0057dc4c;
        _DAT_006d7c04 = 0;
        _DAT_006d7c14 = 0;
        _DAT_006d7c00 =
             _DAT_006d7b78 * _DAT_0057dc30 +
             _DAT_006d7b7c * _DAT_0057dc40 + _DAT_006d7b80 * _DAT_0057dc50;
        _DAT_006d7c08 =
             _DAT_006d7b8c * _DAT_0057dc38 +
             _DAT_006d7b88 * _DAT_0057dc28 + _DAT_006d7b90 * _DAT_0057dc48;
        _DAT_006d7c0c =
             _DAT_006d7b88 * _DAT_0057dc2c +
             _DAT_006d7b8c * _DAT_0057dc3c + _DAT_006d7b90 * _DAT_0057dc4c;
        _DAT_006d7c10 =
             _DAT_006d7b88 * _DAT_0057dc30 +
             _DAT_006d7b8c * _DAT_0057dc40 + _DAT_006d7b90 * _DAT_0057dc50;
        _DAT_006d7c18 =
             DAT_006d7b9c * _DAT_0057dc38 +
             DAT_006d7b98 * _DAT_0057dc28 + DAT_006d7ba0 * _DAT_0057dc48 + _DAT_0057dc58;
        _DAT_006d7c1c =
             DAT_006d7b98 * _DAT_0057dc2c +
             DAT_006d7b9c * _DAT_0057dc3c + DAT_006d7ba0 * _DAT_0057dc4c + _DAT_0057dc5c;
        _DAT_006d7c24 = 0x3f800000;
        _DAT_006d7c20 =
             DAT_006d7b98 * _DAT_0057dc30 +
             DAT_006d7b9c * _DAT_0057dc40 + DAT_006d7ba0 * _DAT_0057dc50 + _DAT_0057dc60;
        if ((((_DAT_0056e418 <= _DAT_006d7c1c) && (_DAT_0056e438 <= _DAT_006d7c18)) &&
            (_DAT_006d7c18 <= _DAT_0056e434)) && (7 < *(short *)((int)piVar8 + 0x12))) {
          iVar6 = 0;
          DAT_005ff158 = (_DAT_006d7c08 - _DAT_006d7be8) + _DAT_006d7c18;
          DAT_005ff15c = (_DAT_006d7c0c - _DAT_006d7bec) + _DAT_006d7c1c;
          DAT_005ff160 = (_DAT_006d7c20 - _DAT_006d7bf0) + _DAT_006d7c10;
          DAT_005ff164 = _DAT_006d7c08 + _DAT_006d7be8 + _DAT_006d7c18;
          DAT_005ff168 = _DAT_006d7c0c + _DAT_006d7bec + _DAT_006d7c1c;
          DAT_005ff16c = _DAT_006d7c20 + _DAT_006d7c10 + _DAT_006d7bf0;
          _DAT_005ff170 = (_DAT_006d7be8 - _DAT_006d7c08) + _DAT_006d7c18;
          _DAT_005ff174 = (_DAT_006d7bec - _DAT_006d7c0c) + _DAT_006d7c1c;
          _DAT_005ff178 = (_DAT_006d7c20 - _DAT_006d7c10) + _DAT_006d7bf0;
          _DAT_005ff17c = (_DAT_006d7c18 - _DAT_006d7c08) - _DAT_006d7be8;
          _DAT_005ff180 = (_DAT_006d7c1c - _DAT_006d7c0c) - _DAT_006d7bec;
          _DAT_005ff184 = (_DAT_006d7c20 - _DAT_006d7c10) - _DAT_006d7bf0;
          DAT_005ff104 = *(undefined4 *)(puStack_100 + 2);
          _DAT_005ff108 = *(undefined4 *)(puStack_100 + 4);
          DAT_005ff0b4 = *(undefined4 *)(puStack_100 + 6);
          _DAT_005ff0bc = *(undefined4 *)(puStack_100 + 8);
          DAT_005ff0a8 = 5.60519e-45;
          piVar8 = &DAT_005ff080;
          _DAT_005ff0b8 = DAT_005ff0b4;
          _DAT_005ff0c0 = _DAT_005ff0bc;
          _DAT_005ff10c = _DAT_005ff108;
          _DAT_005ff110 = DAT_005ff104;
          do {
            *piVar8 = iVar6;
            piVar8 = piVar8 + 1;
            iVar6 = iVar6 + 1;
          } while ((int)piVar8 < 0x5ff090);
          uVar19 = 0;
          pfVar20 = &DAT_005ff160;
          fStack_11c = 0.0;
          do {
            uVar16 = sub_401000(pfVar20 + -2);
            fStack_11c = fStack_11c + *pfVar20;
            pfVar20 = pfVar20 + 3;
            uVar19 = uVar19 | ~uVar16 << 0x10 | uVar16;
          } while ((int)pfVar20 < 0x5ff190);
          fStack_11c = fStack_11c * _DAT_0056e164;
          if ((uVar19 & 0x20) == 0) {
            if ((uVar19 & 0xffff0000) == 0xffff0000) {
              fStack_110 = 5.60519e-45;
              iVar6 = __ftol();
              uStack_10c = CONCAT31(uStack_10c._1_3_,(char)(0xff - iVar6));
              bStack_132 = (byte)(0xff - iVar6 >> 2);
              uStack_114 = CONCAT31(uStack_114._1_3_,bStack_132);
              (*(code *)PTR_sub_408390_00570360)(&bStack_132,&uStack_114,&uStack_10c,&uStack_125,2);
              cStack_131 = sub_40C510(&bStack_132,&uStack_114,&uStack_10c);
              fStack_12c = (float)(((uint)CONCAT11(uStack_125,bStack_132) << 8 | uStack_114 & 0xff)
                                   << 8 | uStack_10c & 0xff);
              if (((uVar19 & 0xffff) == 0) ||
                 (uStack_e0 = uVar19 & 0xffff,
                 cVar5 = sub_4015F0(&DAT_005ff158,&DAT_005ff4d0,&DAT_005ff104,&DAT_005ff0b4,
                                    &fStack_110,&DAT_005ff080,&uStack_e0), cVar5 != '\0')) {
                if ((DAT_005833e4._1_1_ == '\0') ||
                   ((iVar6 = 0, uStack_fc == 0 &&
                    (((*puStack_100 & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                  pfStack_130 = (float *)&DAT_005ff250;
                  iVar6 = -1;
                }
                else {
                  iStack_124 = __ftol();
                  if (iStack_124 < 0) {
                    iStack_124 = 0;
                  }
                  else if (0x7ff < iStack_124) {
                    iStack_124 = 0x7ff;
                  }
                  pfStack_130 = (float *)sub_41ED90((int)DAT_005ff0a8 << 5);
                  if (pfStack_130 == (float *)0x0) goto LAB_00434a1c;
                }
                iVar12 = iStack_f8;
                uVar19 = uStack_fc;
                pfVar20 = pfStack_130;
                iVar17 = 0;
                if (0 < (int)DAT_005ff0a8) {
                  piVar8 = &DAT_005ff080;
                  pfVar9 = pfStack_130 + 2;
                  do {
                    iVar1 = *piVar8;
                    piVar8 = piVar8 + 1;
                    iVar17 = iVar17 + 1;
                    fVar15 = _DAT_0056e008 / (&DAT_005ff160)[iVar1 * 3];
                    pfVar9[-2] = (fVar15 * (&DAT_005ff158)[iVar1 * 3] + _DAT_0056e008) *
                                 _DAT_00583388;
                    pfVar9[-1] = (_DAT_0056e008 - fVar15 * (&DAT_005ff15c)[iVar1 * 3]) *
                                 _DAT_0058338c;
                    *pfVar9 = ((&DAT_005ff160)[iVar1 * 3] - _DAT_0057d70c) * _DAT_0057d7fc *
                              _DAT_0057f914 * fVar15;
                    pfVar9[1] = fVar15;
                    pfVar9[2] = fStack_12c;
                    pfVar9[3] = 0.0;
                    pfVar9[4] = (float)(&DAT_005ff104)[iVar1];
                    pfVar9[5] = (float)(&DAT_005ff0b4)[iVar1];
                    pfVar9 = pfVar9 + 8;
                  } while (iVar17 < (int)DAT_005ff0a8);
                }
                fVar15 = DAT_005ff0a8;
                if (iVar6 == -1) {
                  fStack_12c = DAT_005ff0a8;
                  uVar4 = *puStack_100;
                  if (0 < (int)DAT_005ff0a8) {
                    if (DAT_005833e1 == '\0') {
                      if (iStack_f8 == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)(iStack_f8 + 0x10)) {
                          (**(code **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)(iStack_f8 + 0x10));
                          DAT_006d7c54 = *(int *)(iVar12 + 0x10);
                        }
                        if (DAT_006d7c58 != (-(uint)(DAT_005833f0 != '\0') & 2) + 2) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))
                                    (DAT_00582cd4,0,1,(-(DAT_005833f0 != '\0') & 2U) + 2);
                          if (DAT_005833f0 == '\0') {
                            DAT_006d7c58 = 2;
                          }
                          else {
                            DAT_006d7c58 = 4;
                          }
                        }
                      }
                      if (DAT_006d7c34 != 1) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                        DAT_006d7c34 = 1;
                      }
                      if (DAT_006d7c38 != '\0') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,0);
                        DAT_006d7c38 = '\0';
                      }
                      uVar16 = uStack_118;
                      if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_118 & 2) != 0))
                      {
                        cVar5 = '\0';
                      }
                      else {
                        cVar5 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar5) {
                        if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           ((uStack_118 & 2) != 0)) {
                          uVar21 = 0;
                        }
                        else {
                          uVar21 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar21);
                        if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uVar16 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        DAT_006d7c39 = '\x01';
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                        DAT_006d7c48 = 4;
                      }
                      if (((uVar4 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        cVar5 = '\0';
                      }
                      else {
                        cVar5 = '\x01';
                      }
                      if (DAT_006d7c3a != cVar5) {
                        if (((uVar4 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                          uVar21 = 0;
                        }
                        else {
                          uVar21 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar21);
                        if (((uVar4 & 2) == 0) || (DAT_006d7c3a = '\x01', DAT_006d7c70 == '\0')) {
                          DAT_006d7c3a = '\0';
                        }
                      }
                      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x58))
                                  (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                      }
                      uVar19 = uStack_fc;
                      switch(uStack_fc) {
                      case 0:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\0') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                            DAT_006d7c4c = '\0';
                          }
                        }
                        else if (DAT_006d7c4d != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                          DAT_006d7c4d = '\0';
                        }
                        break;
                      case 1:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        iVar6 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar6) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar6);
                          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        }
                        if (DAT_006d7c44 != 6) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                          DAT_006d7c44 = 6;
                        }
                        break;
                      case 2:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                          DAT_006d7c40 = 2;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                        break;
                      case 3:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 5) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                          DAT_006d7c40 = 5;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                      }
                      switch(uVar16) {
                      case 0:
                      case 2:
                        if (DAT_006d7c5c != 2) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                          DAT_006d7c5c = 2;
                        }
                        break;
                      case 1:
                        if (DAT_006d7c5c != 3) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                          DAT_006d7c5c = 3;
                        }
                        break;
                      case 3:
                        if (DAT_006d7c5c != 4) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                          DAT_006d7c5c = 4;
                        }
                      }
                      pfVar20 = pfStack_130;
                      if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_12c)) {
                        pfVar9 = pfStack_130 + 2;
                        fVar15 = fStack_12c;
                        do {
                          fVar2 = _DAT_0056e00c;
                          if (_DAT_0056e28c < *pfVar9) {
                            fVar2 = *pfVar9 - _DAT_0056e28c;
                          }
                          *pfVar9 = fVar2;
                          pfVar9 = pfVar9 + 8;
                          fVar15 = (float)((int)fVar15 + -1);
                        } while (fVar15 != 0.0);
                      }
                      (**(code **)(*DAT_00582cd4 + 0x70))
                                (DAT_00582cd4,6,0x1c4,pfStack_130,fStack_12c,0x1c);
                      iVar12 = iStack_f8;
                    }
                    else {
                      if (iStack_f8 == 0) {
                        uVar21 = 0;
                      }
                      else {
                        uVar21 = *(undefined4 *)(iStack_f8 + 0x1c);
                      }
                      pcVar14 = sub_4C6CD0;
                      if (DAT_00583380 == '\0') {
                        pcVar14 = sub_442BD0;
                      }
                      (*pcVar14)(DAT_0058331c,DAT_005832f0,uVar21,DAT_00583308 >> 1,DAT_00583374,
                                 pfStack_130,DAT_005ff0a8,1,0,
                                 (uStack_fc * 4 | uStack_118) << 5 | -(uint)((uVar4 & 2) != 0) & 4 |
                                 0x203);
                    }
                  }
                  if (cStack_131 != '\0') {
                    uVar4 = *puStack_100;
                    fStack_12c = DAT_005ff0a8;
                    if (0 < (int)DAT_005ff0a8) {
                      if (DAT_005833e1 == '\0') {
                        if (iVar12 == 0) {
                          if (DAT_006d7c58 != 1) {
                            (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                            DAT_006d7c58 = 1;
                          }
                        }
                        else {
                          if (DAT_006d7c54 != *(int *)(iVar12 + 0x10)) {
                            (**(code **)(*DAT_00582cd4 + 0x98))
                                      (DAT_00582cd4,0,*(int *)(iVar12 + 0x10));
                            DAT_006d7c54 = *(int *)(iVar12 + 0x10);
                          }
                          if (DAT_006d7c58 != (-(uint)(DAT_005833f0 != '\0') & 2) + 2) {
                            (**(code **)(*DAT_00582cd4 + 0xa0))
                                      (DAT_00582cd4,0,1,(-(DAT_005833f0 != '\0') & 2U) + 2);
                            if (DAT_005833f0 == '\0') {
                              DAT_006d7c58 = 2;
                            }
                            else {
                              DAT_006d7c58 = 4;
                            }
                          }
                        }
                        if (DAT_006d7c34 != 1) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                          DAT_006d7c34 = 1;
                        }
                        if (DAT_006d7c38 != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,0);
                          DAT_006d7c38 = '\0';
                        }
                        uVar16 = uStack_118;
                        if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           ((uStack_118 & 2) != 0)) {
                          cVar5 = '\0';
                        }
                        else {
                          cVar5 = '\x01';
                        }
                        if (DAT_006d7c4e != cVar5) {
                          if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                             ((uStack_118 & 2) != 0)) {
                            uVar21 = 0;
                          }
                          else {
                            uVar21 = 1;
                          }
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar21);
                          if ((((uVar4 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                             (DAT_006d7c4e = '\x01', (uVar16 & 2) != 0)) {
                            DAT_006d7c4e = '\0';
                          }
                        }
                        if (DAT_006d7c30 != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                          DAT_006d7c30 = '\x01';
                        }
                        if (DAT_006d7c39 != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                          DAT_006d7c39 = '\x01';
                        }
                        if (DAT_006d7c48 != 4) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                          DAT_006d7c48 = 4;
                        }
                        if (((uVar4 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                          cVar5 = '\0';
                        }
                        else {
                          cVar5 = '\x01';
                        }
                        if (DAT_006d7c3a != cVar5) {
                          if (((uVar4 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                            uVar21 = 0;
                          }
                          else {
                            uVar21 = 1;
                          }
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar21);
                          if (((uVar4 & 2) == 0) || (DAT_006d7c3a = '\x01', DAT_006d7c70 == '\0')) {
                            DAT_006d7c3a = '\0';
                          }
                        }
                        if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                          (**(code **)(*DAT_00582cd4 + 0x58))
                                    (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                          DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                        }
                        iVar6 = 3;
                        switch(uVar19 | 2) {
                        case 0:
                          if (DAT_005833fa == '\0') {
                            if (DAT_006d7c4c != '\0') {
                              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                              DAT_006d7c4c = '\0';
                            }
                          }
                          else if (DAT_006d7c4d != '\0') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                            DAT_006d7c4d = '\0';
                          }
                          break;
                        case 1:
                          if (DAT_005833fa == '\0') {
                            if (DAT_006d7c4c != '\x01') {
                              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                              DAT_006d7c4c = '\x01';
                            }
                          }
                          else if (DAT_006d7c4d != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                            DAT_006d7c4d = '\x01';
                          }
                          iVar12 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                          if (DAT_006d7c40 != iVar12) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar12);
                            DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                          }
                          if (DAT_006d7c44 != 6) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                            DAT_006d7c44 = 6;
                          }
                          break;
                        case 2:
                          if (DAT_005833fa == '\0') {
                            if (DAT_006d7c4c != '\x01') {
                              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                              DAT_006d7c4c = '\x01';
                            }
                          }
                          else if (DAT_006d7c4d != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                            DAT_006d7c4d = '\x01';
                          }
                          if (DAT_006d7c40 != 2) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                            DAT_006d7c40 = 2;
                          }
                          if (DAT_006d7c44 != 2) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                            DAT_006d7c44 = 2;
                          }
                          break;
                        case 3:
                          if (DAT_005833fa == '\0') {
                            if (DAT_006d7c4c != '\x01') {
                              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                              DAT_006d7c4c = '\x01';
                            }
                          }
                          else if (DAT_006d7c4d != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                            DAT_006d7c4d = '\x01';
                          }
                          if (DAT_006d7c40 != 5) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                            DAT_006d7c40 = 5;
                          }
                          if (DAT_006d7c44 != 2) {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                            DAT_006d7c44 = 2;
                          }
                        }
                        switch(uVar16) {
                        case 0:
                        case 2:
                          if (DAT_006d7c5c != 2) {
                            (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                            DAT_006d7c5c = 2;
                          }
                          break;
                        case 1:
                          if (DAT_006d7c5c != 3) {
                            uVar21 = 3;
                            iVar12 = *DAT_00582cd4;
LAB_004349b4:
                            (**(code **)(iVar12 + 0xa0))(DAT_00582cd4,0,4,uVar21);
                            DAT_006d7c5c = iVar6;
                          }
                          break;
                        case 3:
                          iVar6 = 4;
                          if (DAT_006d7c5c != 4) {
                            uVar21 = 4;
                            iVar12 = *DAT_00582cd4;
                            goto LAB_004349b4;
                          }
                        }
                        if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_12c)) {
                          pfVar9 = pfVar20 + 2;
                          fVar15 = fStack_12c;
                          do {
                            fVar2 = _DAT_0056e00c;
                            if (_DAT_0056e28c < *pfVar9) {
                              fVar2 = *pfVar9 - _DAT_0056e28c;
                            }
                            *pfVar9 = fVar2;
                            pfVar9 = pfVar9 + 8;
                            fVar15 = (float)((int)fVar15 + -1);
                          } while (fVar15 != 0.0);
                        }
                        (**(code **)(*DAT_00582cd4 + 0x70))
                                  (DAT_00582cd4,6,0x1c4,pfVar20,fStack_12c,0x1c);
                      }
                      else {
                        if (iVar12 == 0) {
                          uVar21 = 0;
                        }
                        else {
                          uVar21 = *(undefined4 *)(iVar12 + 0x1c);
                        }
                        pcVar14 = sub_4C6CD0;
                        if (DAT_00583380 == '\0') {
                          pcVar14 = sub_442BD0;
                        }
                        (*pcVar14)(DAT_0058331c,DAT_005832f0,uVar21,DAT_00583308 >> 1,DAT_00583374,
                                   pfVar20,DAT_005ff0a8,1,0,
                                   ((uVar19 | 2) * 4 | uStack_118) << 5 |
                                   -(uint)((uVar4 & 2) != 0) & 4 | 0x203);
                      }
                    }
                  }
                }
                else {
                  if (((cStack_131 != '\0') && (uVar4 = *puStack_100, 0 < (int)DAT_005ff0a8)) &&
                     (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)) {
                    iVar12 = iVar6 * 0x800 + iStack_124;
                    *puVar7 = (&DAT_005f6ef8)[iVar12];
                    puVar7[1] = pfStack_130;
                    puVar7[2] = fVar15;
                    puVar7[5] = iStack_f8;
                    puVar7[3] = 0;
                    puVar7[4] = 0;
                    puVar7[6] = 0;
                    puVar7[7] = (uStack_118 << 2 | uStack_fc) << 0xc |
                                -(uint)((uVar4 & 2) != 0) & 0x10 | 0x20cb;
                    (&DAT_005f6ef8)[iVar12] = puVar7;
                  }
                  fVar15 = DAT_005ff0a8;
                  uVar4 = *puStack_100;
                  if ((0 < (int)DAT_005ff0a8) &&
                     (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)) {
                    iVar6 = iVar6 * 0x800 + iStack_124;
                    *puVar7 = (&DAT_005f6ef8)[iVar6];
                    puVar7[1] = pfStack_130;
                    puVar7[5] = iStack_f8;
                    puVar7[3] = 0;
                    puVar7[4] = 0;
                    puVar7[6] = 0;
                    puVar7[2] = fVar15;
                    puVar7[7] = CONCAT31((int3)(((uStack_118 << 2 | uStack_fc) << 0xc) >> 8),
                                         -((uVar4 & 2) != 0)) & 0xffffff10 | 0xcb;
                    (&DAT_005f6ef8)[iVar6] = puVar7;
                  }
                }
              }
            }
          }
          else {
            *(undefined1 *)(piStack_120 + 4) = 0;
          }
          goto LAB_00434a1c;
        }
LAB_00434a18:
        *(undefined1 *)(piVar8 + 4) = 0;
      }
LAB_00434a1c:
      uStack_b4 = uStack_b4 + 1;
      piStack_120 = piStack_120 + 8;
    } while (uStack_b4 < DAT_006da320);
  }
  return;
}

