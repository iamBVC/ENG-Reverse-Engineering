/* sub_42C8C0 @ 0042c8c0   20359 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_42C8C0(void)

{
  ushort uVar1;
  ushort uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  char cVar7;
  uint uVar8;
  float *pfVar9;
  undefined4 *puVar10;
  int *piVar11;
  float fVar12;
  code *pcVar13;
  uint uVar14;
  float *pfVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  undefined4 uVar19;
  char cVar20;
  undefined1 uVar21;
  uint uVar22;
  int iVar23;
  undefined4 *puVar24;
  float fStack_17c;
  char cStack_175;
  uint uStack_174;
  float *pfStack_170;
  char cStack_16a;
  char cStack_169;
  uint uStack_168;
  float fStack_164;
  float fStack_160;
  int iStack_15c;
  float fStack_158;
  uint uStack_154;
  uint uStack_150;
  int iStack_14c;
  uint uStack_148;
  float fStack_144;
  uint uStack_140;
  float fStack_13c;
  float *pfStack_138;
  ushort *puStack_134;
  int iStack_130;
  float fStack_12c;
  float fStack_128;
  float fStack_124;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  uint local_f4;
  undefined4 *local_f0;
  float fStack_ec;
  float fStack_e8;
  float fStack_e4;
  uint uStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  uint uStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  uint uStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float local_88;
  float local_84;
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
  
  local_f4 = 0xffffffff;
  sub_431950();
  if (DAT_006d9be4 != 0) {
    (*DAT_005ff038)();
  }
  local_88 = (float)DAT_00583374 * _DAT_0056e430;
  local_84 = (float)DAT_00583378 * _DAT_0056e42c;
  uVar8 = 0xffffffff;
  puVar10 = DAT_006d9bdc;
  do {
    if (puVar10 == (undefined4 *)0x0) {
      return;
    }
    cStack_16a = 0;
    uVar1 = *(ushort *)(puVar10 + 0xd);
    fStack_164 = (float)(uint)uVar1;
    uVar22 = (uint)fStack_164 & 3;
    local_f0 = puVar10;
    if ((uVar1 & 4) == 0) {
      if ((uVar1 & 0x800) == 0) {
        cStack_16a = uVar22 == 3;
        if ((bool)cStack_16a) {
          uVar22 = 1;
        }
        uVar17 = (uint)*(ushort *)(puVar10 + 0x10);
        if ((uVar8 != uVar17) && (uVar8 = uVar17, local_f4 = uVar17, uVar17 < 0x30)) {
          uVar8 = *(uint *)(&DAT_005fd0c0 + uVar17 * 4);
          local_f4 = uVar8;
        }
        if ((uVar1 & 8) != 0) {
          uVar8 = uVar8 + 1 + ((int)puVar10[0x11] >> 5);
          local_f4 = uVar8;
        }
        puStack_134 = (ushort *)(DAT_00581154 + uVar8 * 0x14);
        uVar2 = *puStack_134;
        if ((uVar2 & 1) == 0) {
          iStack_14c = (char)(byte)puStack_134[1] * 0x20 + DAT_0058114c;
        }
        else {
          iStack_14c = 0;
        }
        uVar8 = uVar2 >> 0xc & 7;
        fStack_17c = (float)puVar10[0xf];
        uVar17 = uVar2 >> 8 & 7;
        if ((int)fStack_17c < 0) {
          if ((uVar1 & 0x80) == 0) {
            iVar23 = 0x20 - *(short *)((int)puVar10 + 0x32);
          }
          else {
            iVar23 = (int)*(short *)((int)puVar10 + 0x32);
          }
          fStack_17c = (float)-(iVar23 * (int)fStack_17c);
        }
        uStack_148._1_3_ = (undefined3)(uStack_148 >> 8);
        uStack_150._1_3_ = (undefined3)(uStack_150 >> 8);
        uStack_154._1_3_ = (undefined3)(uStack_154 >> 8);
        if ((uVar1 & 0x10) == 0) {
          uStack_148 = CONCAT31(uStack_148._1_3_,0x80);
          uStack_150 = CONCAT31(uStack_150._1_3_,0x80);
          uStack_154 = CONCAT31(uStack_154._1_3_,0x80);
        }
        else {
          uVar19 = puVar10[0xe];
          uStack_148 = CONCAT31(uStack_148._1_3_,(char)uVar19);
          uStack_150 = CONCAT31(uStack_150._1_3_,(char)((uint)uVar19 >> 8));
          uStack_154 = CONCAT31(uStack_154._1_3_,(char)((uint)uVar19 >> 0x10));
        }
        (**(code **)(&DAT_00570358 + uVar8 * 4))
                  (&uStack_148,&uStack_150,&uStack_154,&cStack_169,uVar8);
        if ((*puStack_134 & 1) == 0) {
          iVar23 = uVar8 + uVar17 * 4;
          if (cStack_169 == -1) {
            iVar23 = uVar17 + iVar23;
            uStack_168 = (&DAT_00573ef8)[iVar23 * 3];
            uStack_174 = (&DAT_00573efc)[iVar23 * 3];
          }
          else {
            iVar23 = uVar17 + iVar23;
            uStack_168 = (&DAT_005740a0)[iVar23 * 3];
            uStack_174 = (&DAT_005740a4)[iVar23 * 3];
          }
        }
        else {
          uStack_148 = CONCAT31(uStack_148._1_3_,
                                (char)((uint)(byte)puStack_134[2] * (uStack_148 & 0xff) >> 8));
          uStack_150 = CONCAT31(uStack_150._1_3_,
                                (char)((uint)(byte)puStack_134[4] * (uStack_150 & 0xff) >> 8));
          uStack_154 = CONCAT31(uStack_154._1_3_,
                                (char)((uint)(byte)puStack_134[6] * (uStack_154 & 0xff) >> 8));
          if (cStack_169 == -1) {
            uStack_168 = (&DAT_00573eb8)[uVar8 * 3];
            uStack_174 = (&DAT_00573ebc)[uVar8 * 3];
          }
          else {
            uStack_168 = (&DAT_00574060)[uVar8 * 3];
            uStack_174 = (&DAT_00574064)[uVar8 * 3];
          }
        }
        cStack_175 = sub_40C510(&uStack_148,&uStack_150,&uStack_154);
        if (((char)uStack_148 == (char)uStack_150) && ((char)uStack_150 == (char)uStack_154)) {
          uStack_140 = CONCAT31(uStack_140._1_3_,1);
          if ((char)uStack_148 != -1) goto LAB_0042ecfe;
          cVar20 = '\0';
        }
        else {
          uStack_140 = (uint)uStack_140._1_3_ << 8;
LAB_0042ecfe:
          cVar20 = '\x01';
        }
        fVar12 = (float)(((uint)CONCAT11(cStack_169,(char)uStack_148) << 8 | uStack_150 & 0xff) << 8
                        | uStack_154 & 0xff);
        uStack_e0 = CONCAT31(uStack_e0._1_3_,cVar20);
        fStack_144 = fVar12;
        if (uVar22 == 1) {
          if (((uint)fStack_164 & 0x2000) != 0) {
            fVar12 = (float)(int)fStack_17c * (float)_DAT_0056e020;
            fStack_17c = (float)((*(byte *)((int)puVar10 + 0x32) & 7) << 9);
            sub_41ECE0((float)(int)puVar10[2] * (float)_DAT_0056e020,
                       (float)(int)puVar10[3] * (float)_DAT_0056e020,
                       -((float)(int)puVar10[4] * (float)_DAT_0056e020),
                       (float)(int)fStack_17c * (float)_DAT_0056e018,fVar12,fVar12,fVar12,
                       &DAT_006d7b68);
            fStack_ec = DAT_006d7b98;
            fStack_e4 = DAT_006d7ba0;
            fStack_e8 = DAT_006d7b9c;
            fVar12 = DAT_006d7b9c * _DAT_0057dbf8 +
                     DAT_006d7ba0 * _DAT_0057dc08 + DAT_006d7b98 * _DAT_0057dbe8 + _DAT_0057dc18;
            fVar3 = DAT_006d7b98 * _DAT_0057dbec +
                    DAT_006d7b9c * _DAT_0057dbfc + DAT_006d7ba0 * _DAT_0057dc0c + _DAT_0057dc1c;
            DAT_006d7ba0 = DAT_006d7b98 * _DAT_0057dbf0 +
                           DAT_006d7b9c * _DAT_0057dc00 + DAT_006d7ba0 * _DAT_0057dc10 +
                           _DAT_0057dc20;
            _DAT_006d7be8 =
                 _DAT_0057dbb0 * _DAT_006d7b6c +
                 _DAT_0057dbc0 * _DAT_006d7b70 + _DAT_0057dba0 * _DAT_006d7b68;
            _DAT_006d7bec =
                 _DAT_0057dbb4 * _DAT_006d7b6c +
                 _DAT_0057dbc4 * _DAT_006d7b70 + _DAT_006d7b68 * _DAT_0057dba4;
            _DAT_006d7bf0 =
                 _DAT_0057dbb8 * _DAT_006d7b6c +
                 _DAT_0057dbc8 * _DAT_006d7b70 + _DAT_006d7b68 * _DAT_0057dba8;
            _DAT_006d7bf8 =
                 _DAT_006d7b7c * _DAT_0057dbb0 +
                 _DAT_006d7b80 * _DAT_0057dbc0 + _DAT_0057dba0 * _DAT_006d7b78;
            _DAT_006d7bfc =
                 _DAT_006d7b78 * _DAT_0057dba4 +
                 _DAT_006d7b7c * _DAT_0057dbb4 + _DAT_006d7b80 * _DAT_0057dbc4;
            _DAT_006d7c00 =
                 _DAT_006d7b78 * _DAT_0057dba8 +
                 _DAT_006d7b7c * _DAT_0057dbb8 + _DAT_006d7b80 * _DAT_0057dbc8;
            _DAT_006d7c08 =
                 _DAT_006d7b8c * _DAT_0057dbb0 +
                 _DAT_006d7b90 * _DAT_0057dbc0 + _DAT_0057dba0 * _DAT_006d7b88;
            _DAT_006d7c0c =
                 _DAT_006d7b88 * _DAT_0057dba4 +
                 _DAT_006d7b8c * _DAT_0057dbb4 + _DAT_006d7b90 * _DAT_0057dbc4;
            _DAT_006d7c10 =
                 _DAT_006d7b88 * _DAT_0057dba8 +
                 _DAT_006d7b8c * _DAT_0057dbb8 + _DAT_006d7b90 * _DAT_0057dbc8;
            _DAT_006d7c18 =
                 _DAT_0057dbb0 * fVar3 + _DAT_0057dbc0 * DAT_006d7ba0 + _DAT_0057dba0 * fVar12 +
                 _DAT_0057dbd0;
            _DAT_006d7c1c =
                 _DAT_0057dbb4 * fVar3 + _DAT_0057dbc4 * DAT_006d7ba0 + _DAT_0057dba4 * fVar12 +
                 _DAT_0057dbd4;
            _DAT_006d7c20 =
                 _DAT_0057dbb8 * fVar3 + _DAT_0057dbc8 * DAT_006d7ba0 + _DAT_0057dba8 * fVar12 +
                 _DAT_0057dbd8;
            DAT_006d7b98 = fVar12;
            DAT_006d7b9c = fVar3;
            goto LAB_004302db;
          }
          fVar3 = (float)(int)puVar10[2] * (float)_DAT_0056e020;
          fVar4 = (float)(int)puVar10[3] * (float)_DAT_0056e020;
          fVar5 = -((float)(int)puVar10[4] * (float)_DAT_0056e020);
          fStack_10c = _DAT_0057dc28 * fVar3 + _DAT_0057dc38 * fVar4 + _DAT_0057dc48 * fVar5 +
                       _DAT_0057dc58;
          fStack_108 = _DAT_0057dc2c * fVar3 + _DAT_0057dc3c * fVar4 + _DAT_0057dc4c * fVar5 +
                       _DAT_0057dc5c;
          fStack_104 = _DAT_0057dc30 * fVar3 + _DAT_0057dc40 * fVar4 + _DAT_0057dc50 * fVar5 +
                       _DAT_0057dc60;
          uVar8 = sub_401000(&fStack_10c);
          puVar24 = local_f0;
          if ((uVar8 & 0x30) == 0) {
            fStack_158 = _DAT_0056e008 / fStack_104;
            fVar3 = (fStack_158 * fStack_10c + _DAT_0056e008) * _DAT_00583388;
            fStack_124 = (_DAT_0056e008 - fStack_158 * fStack_108) * _DAT_0058338c;
            fStack_120 = (fStack_104 - _DAT_0057d70c) * _DAT_0057d7fc * _DAT_0057f914 * fStack_158;
            fVar4 = (float)(int)fStack_17c;
            fStack_17c = (float)DAT_00583374;
            fStack_160 = fStack_17c * fVar4 * (float)_DAT_0056e020 * fStack_158;
            pfStack_170 = (float *)(float)DAT_00583378;
            fStack_164 = (float)pfStack_170 * fVar4 * (float)_DAT_0056e020 * fStack_158;
            fStack_144 = fVar3 - fStack_160;
            fStack_160 = fStack_160 + fVar3;
            fStack_13c = fStack_124 - fStack_164;
            pfStack_138 = (float *)(fStack_164 + fStack_124);
            puVar24 = puVar10;
            if (_DAT_0056e00c < (float)pfStack_138) {
              if (((fStack_144 < fStack_17c) && (_DAT_0056e00c < fStack_160)) &&
                 (fStack_13c < (float)pfStack_170)) {
                fStack_118 = *(float *)(puStack_134 + 4);
                fStack_110 = *(float *)(puStack_134 + 2);
                fStack_11c = *(float *)(puStack_134 + 8);
                fStack_114 = *(float *)(puStack_134 + 6);
                if (fStack_144 < _DAT_0056e00c) {
                  fVar4 = -fStack_144;
                  fVar3 = fStack_160 - fStack_144;
                  fStack_144 = 0.0;
                  fStack_110 = (fVar4 * (fStack_118 - fStack_110)) / fVar3 + fStack_110;
                }
                if (fStack_17c < fStack_160) {
                  fStack_118 = ((fStack_17c - fStack_160) * (fStack_118 - fStack_110)) /
                               (fStack_160 - fStack_144) + fStack_118;
                  fStack_160 = fStack_17c;
                }
                if (fStack_13c < _DAT_0056e00c) {
                  fVar4 = -fStack_13c;
                  fVar3 = (float)pfStack_138 - fStack_13c;
                  fStack_13c = 0.0;
                  fStack_114 = (fVar4 * (fStack_11c - fStack_114)) / fVar3 + fStack_114;
                }
                if ((float)pfStack_170 < (float)pfStack_138) {
                  fStack_11c = (((float)pfStack_170 - (float)pfStack_138) *
                               (fStack_11c - fStack_114)) / ((float)pfStack_138 - fStack_13c) +
                               fStack_11c;
                  pfStack_138 = pfStack_170;
                }
                if (((puVar10[7] & 0x4000) == 0) || ((DAT_006da330 & 0x800) == 0)) {
                  bVar6 = false;
                }
                else {
                  bVar6 = true;
                }
                if ((DAT_005833e4._1_1_ == '\0') ||
                   ((uStack_168 == 0 && (((*puStack_134 & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                  iVar23 = -1;
LAB_0042f0eb:
                  pfStack_170 = (float *)&DAT_005ff250;
                }
                else {
                  if ((bVar6) && ((DAT_005f6ee8 & 1) != 0)) {
                    iVar23 = 1;
                  }
                  else {
                    iVar23 = 0;
                  }
                  iStack_15c = __ftol();
                  if (iStack_15c < 0) {
                    iStack_15c = 0;
                  }
                  else if (0x7ff < iStack_15c) {
                    iStack_15c = 0x7ff;
                  }
                  if (iVar23 == -1) goto LAB_0042f0eb;
                  pfStack_170 = (float *)sub_41ED90(0x80);
                  puVar24 = local_f0;
                  if (pfStack_170 == (float *)0x0) goto LAB_0043182b;
                }
                iVar16 = iStack_14c;
                pfVar9 = pfStack_170;
                uVar19 = 0;
                pfStack_170[0x18] = fStack_144;
                *pfStack_170 = fStack_144;
                pfStack_170[0x10] = fStack_160;
                pfStack_170[8] = fStack_160;
                pfStack_170[9] = fStack_13c;
                pfStack_170[1] = fStack_13c;
                pfStack_170[0x19] = (float)pfStack_138;
                pfStack_170[0x11] = (float)pfStack_138;
                pfStack_170[0x1a] = fStack_120;
                pfStack_170[10] = fStack_120;
                pfStack_170[0x12] = fStack_120;
                pfStack_170[2] = fStack_120;
                pfStack_170[0x1b] = fStack_158;
                pfStack_170[0xb] = fStack_158;
                pfStack_170[0x13] = fStack_158;
                pfStack_170[3] = fStack_158;
                pfStack_170[0x1e] = fStack_110;
                pfStack_170[6] = fStack_110;
                pfStack_170[0x16] = fStack_118;
                pfStack_170[0xe] = fStack_118;
                pfStack_170[0xf] = fStack_114;
                pfStack_170[7] = fStack_114;
                pfStack_170[0x1c] = fVar12;
                pfStack_170[0x14] = fVar12;
                pfStack_170[0xc] = fVar12;
                pfStack_170[4] = fVar12;
                pfStack_170[0x1d] = 0.0;
                pfStack_170[0x15] = 0.0;
                pfStack_170[0xd] = 0.0;
                pfStack_170[5] = 0.0;
                pfStack_170[0x1f] = fStack_11c;
                pfStack_170[0x17] = fStack_11c;
                if (iVar23 == -1) {
                  uVar8 = uStack_140 & 0xff;
                  uVar1 = *puStack_134;
                  fVar12 = (float)(uStack_e0 & 0xff);
                  uVar21 = (undefined1)uStack_140;
                  fStack_17c = fVar12;
                  if (DAT_005833e1 == '\0') {
                    if (iStack_14c == 0) {
                      if (DAT_006d7c58 != 1) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                        DAT_006d7c58 = 1;
                      }
                    }
                    else {
                      if (DAT_006d7c54 != *(int *)(iStack_14c + 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x98))
                                  (DAT_00582cd4,0,*(int *)(iStack_14c + 0x10));
                        DAT_006d7c54 = *(int *)(iStack_14c + 0x10);
                      }
                      if ((fVar12 == 0.0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                        iVar23 = 2;
                      }
                      if (DAT_006d7c58 != iVar23) {
                        if ((fVar12 == 0.0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                          uVar19 = 2;
                        }
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                        if ((fVar12 == 0.0) || (DAT_005833f0 == '\0')) {
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
                    if ((_DAT_006d7c38 & 0xff) != uVar8) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                    }
                    if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0)) {
                      cVar20 = '\0';
                    }
                    else {
                      cVar20 = '\x01';
                    }
                    if (DAT_006d7c4e != cVar20) {
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0))
                      {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                         (DAT_006d7c4e = '\x01', (uStack_174 & 2) != 0)) {
                        DAT_006d7c4e = '\0';
                      }
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                      DAT_006d7c48 = 4;
                    }
                    if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                      uVar22 = 0;
                    }
                    else {
                      uVar22 = 1;
                    }
                    if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar22) {
                      if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                      if ((uVar1 & 2) != 0) {
                        _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                        if (DAT_006d7c70 != '\0') goto LAB_0042f5cd;
                      }
                      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                    }
LAB_0042f5cd:
                    if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                      (**(code **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                      DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                    }
                    switch(uStack_168) {
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
                      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar23) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
                    switch(uStack_174) {
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
                    if (DAT_005833e4._3_1_ == '\0') {
                      pfVar15 = pfVar9 + 2;
                      iVar23 = 4;
                      do {
                        fVar12 = _DAT_0056e00c;
                        if (_DAT_0056e28c < *pfVar15) {
                          fVar12 = *pfVar15 - _DAT_0056e28c;
                        }
                        *pfVar15 = fVar12;
                        pfVar15 = pfVar15 + 8;
                        iVar23 = iVar23 + -1;
                      } while (iVar23 != 0);
                    }
                    (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
                    iVar16 = iStack_14c;
                  }
                  else {
                    iVar23 = (uStack_168 << 2 | uStack_174) << 5;
                    if (iStack_14c != 0) {
                      uVar19 = *(undefined4 *)(iStack_14c + 0x1c);
                    }
                    pcVar13 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar13 = sub_442BD0;
                    }
                    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                               pfStack_170,4,1,0,
                               CONCAT31((uint3)((uint)iVar23 >> 8) |
                                        (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                        (byte)iVar23 | fVar12 != 0.0 | -((uVar1 & 2) != 0) & 4U) | 2
                              );
                  }
                  puVar24 = local_f0;
                  if (cStack_175 != '\0') {
                    fStack_164 = (float)(uStack_168 | 2);
                    uVar1 = *puStack_134;
                    if (DAT_005833e1 == '\0') {
                      if (iVar16 == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)(iVar16 + 0x10)) {
                          (**(code **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)(iVar16 + 0x10));
                          DAT_006d7c54 = *(int *)(iVar16 + 0x10);
                        }
                        if ((fStack_17c == 0.0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                          iVar23 = 2;
                        }
                        if (DAT_006d7c58 != iVar23) {
                          if ((fStack_17c == 0.0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                            uVar19 = 2;
                          }
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                          if ((fStack_17c == 0.0) || (DAT_005833f0 == '\0')) {
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
                      if ((_DAT_006d7c38 & 0xff) != uVar8) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                      }
                      uVar8 = uStack_174;
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0))
                      {
                        cVar20 = '\0';
                      }
                      else {
                        cVar20 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar20) {
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           ((uStack_174 & 2) != 0)) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uVar8 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                        DAT_006d7c48 = 4;
                      }
                      if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        uVar8 = 0;
                      }
                      else {
                        uVar8 = 1;
                      }
                      if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar8) {
                        if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                        if ((uVar1 & 2) != 0) {
                          _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                          if (DAT_006d7c70 != '\0') goto LAB_0042fc02;
                        }
                        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                      }
LAB_0042fc02:
                      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x58))
                                  (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                      }
                      switch(fStack_164) {
                      case 0.0:
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
                      case 1.4013e-45:
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
                        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar23) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
                          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        }
                        if (DAT_006d7c44 != 6) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                          DAT_006d7c44 = 6;
                        }
                        break;
                      case 2.8026e-45:
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
                      case 4.2039e-45:
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
                      switch(uStack_174) {
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
                      if (DAT_005833e4._3_1_ == '\0') {
                        pfVar15 = pfVar9 + 2;
                        iVar23 = 4;
                        do {
                          fVar12 = _DAT_0056e00c;
                          if (_DAT_0056e28c < *pfVar15) {
                            fVar12 = *pfVar15 - _DAT_0056e28c;
                          }
                          *pfVar15 = fVar12;
                          pfVar15 = pfVar15 + 8;
                          iVar23 = iVar23 + -1;
                        } while (iVar23 != 0);
                      }
                      (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
                      puVar24 = local_f0;
                    }
                    else {
                      iVar23 = ((int)fStack_164 << 2 | uStack_174) << 5;
                      if (iVar16 == 0) {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = *(undefined4 *)(iVar16 + 0x1c);
                      }
                      pcVar13 = sub_4C6CD0;
                      if (DAT_00583380 == '\0') {
                        pcVar13 = sub_442BD0;
                      }
                      (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                                 pfVar9,4,1,0,
                                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                          (byte)iVar23 | fStack_17c != 0.0 |
                                          -((uVar1 & 2) != 0) & 4U) | 2);
                      puVar24 = local_f0;
                    }
                  }
                }
                else {
                  if (cStack_175 != '\0') {
                    uVar1 = *puStack_134;
                    puVar10 = (undefined4 *)sub_41ED90(0x20);
                    if (puVar10 != (undefined4 *)0x0) {
                      iVar16 = iVar23 * 0x800 + iStack_15c;
                      *puVar10 = (&DAT_005f6ef8)[iVar16];
                      puVar10[1] = pfStack_170;
                      puVar10[3] = 0;
                      puVar10[4] = 0;
                      puVar10[6] = 0;
                      puVar10[5] = iStack_14c;
                      puVar10[2] = 4;
                      puVar10[7] = (uStack_174 * 4 | uStack_168) << 0xc |
                                   -(uint)((uVar1 & 2) != 0) & 0x10 | -(uint)(cVar20 != '\0') & 2 |
                                   -(uint)((char)uStack_140 != '\0') & 4 | 0x20c9;
                      (&DAT_005f6ef8)[iVar16] = puVar10;
                      pfVar9 = pfStack_170;
                    }
                  }
                  uVar1 = *puStack_134;
                  puVar10 = (undefined4 *)sub_41ED90(0x20);
                  puVar24 = local_f0;
                  if (puVar10 != (undefined4 *)0x0) {
                    iVar23 = iVar23 * 0x800 + iStack_15c;
                    *puVar10 = (&DAT_005f6ef8)[iVar23];
                    puVar10[3] = 0;
                    puVar10[4] = 0;
                    puVar10[6] = 0;
                    puVar10[5] = iStack_14c;
                    puVar10[1] = pfVar9;
                    puVar10[2] = 4;
                    uVar8 = (uStack_174 * 4 | uStack_168) << 0xc | -(uint)((uVar1 & 2) != 0) & 0x10
                            | -(uint)(cVar20 != '\0') & 2;
                    goto LAB_0042f2bc;
                  }
                }
              }
            }
            else if (((uVar8 & 8) != 0) && (cStack_16a == '\0')) {
              *(undefined2 *)((int)puVar10 + 0x32) = 0;
            }
          }
        }
        else {
          fVar12 = (float)(int)fStack_17c * (float)_DAT_0056e020;
          fStack_17c = (float)(*(ushort *)(puVar10 + 0xc) + 0xc00);
          sub_41EC70((float)(int)puVar10[2] * (float)_DAT_0056e020,
                     (float)(int)puVar10[3] * (float)_DAT_0056e020,
                     -((float)(int)puVar10[4] * (float)_DAT_0056e020),
                     (float)(int)fStack_17c * (float)_DAT_0056e018,fVar12,fVar12,fVar12,
                     &DAT_006d7b68);
          _DAT_006d7be8 =
               _DAT_006d7b6c * _DAT_0057dc38 +
               _DAT_006d7b70 * _DAT_0057dc48 + _DAT_006d7b68 * _DAT_0057dc28;
          _DAT_006d7bec =
               _DAT_006d7b6c * _DAT_0057dc3c +
               _DAT_006d7b70 * _DAT_0057dc4c + _DAT_006d7b68 * _DAT_0057dc2c;
          _DAT_006d7bf0 =
               _DAT_006d7b6c * _DAT_0057dc40 +
               _DAT_006d7b70 * _DAT_0057dc50 + _DAT_006d7b68 * _DAT_0057dc30;
          _DAT_006d7bf8 =
               _DAT_006d7b78 * _DAT_0057dc28 +
               _DAT_006d7b7c * _DAT_0057dc38 + _DAT_006d7b80 * _DAT_0057dc48;
          _DAT_006d7bfc =
               _DAT_006d7b78 * _DAT_0057dc2c +
               _DAT_006d7b7c * _DAT_0057dc3c + _DAT_006d7b80 * _DAT_0057dc4c;
          _DAT_006d7c00 =
               _DAT_006d7b78 * _DAT_0057dc30 +
               _DAT_006d7b7c * _DAT_0057dc40 + _DAT_006d7b80 * _DAT_0057dc50;
          _DAT_006d7c08 =
               _DAT_006d7b88 * _DAT_0057dc28 +
               _DAT_006d7b8c * _DAT_0057dc38 + _DAT_006d7b90 * _DAT_0057dc48;
          _DAT_006d7c0c =
               _DAT_006d7b88 * _DAT_0057dc2c +
               _DAT_006d7b8c * _DAT_0057dc3c + _DAT_006d7b90 * _DAT_0057dc4c;
          _DAT_006d7c10 =
               _DAT_006d7b88 * _DAT_0057dc30 +
               _DAT_006d7b8c * _DAT_0057dc40 + _DAT_006d7b90 * _DAT_0057dc50;
          _DAT_006d7c18 =
               DAT_006d7b98 * _DAT_0057dc28 +
               DAT_006d7b9c * _DAT_0057dc38 + DAT_006d7ba0 * _DAT_0057dc48 + _DAT_0057dc58;
          _DAT_006d7c1c =
               DAT_006d7b98 * _DAT_0057dc2c +
               DAT_006d7b9c * _DAT_0057dc3c + DAT_006d7ba0 * _DAT_0057dc4c + _DAT_0057dc5c;
          _DAT_006d7c20 =
               DAT_006d7b98 * _DAT_0057dc30 +
               DAT_006d7b9c * _DAT_0057dc40 + DAT_006d7ba0 * _DAT_0057dc50 + _DAT_0057dc60;
          if (uVar22 == 2) {
LAB_004302db:
            DAT_005ff158 = (_DAT_006d7c18 - _DAT_006d7be8) + _DAT_006d7bf8;
            DAT_005ff15c = (_DAT_006d7c1c - _DAT_006d7bec) + _DAT_006d7bfc;
            DAT_005ff160 = (_DAT_006d7c20 - _DAT_006d7bf0) + _DAT_006d7c00;
            DAT_005ff164 = _DAT_006d7c18 + _DAT_006d7bf8 + _DAT_006d7be8;
            DAT_005ff168 = _DAT_006d7c1c + _DAT_006d7bfc + _DAT_006d7bec;
            DAT_005ff16c = _DAT_006d7c20 + _DAT_006d7c00 + _DAT_006d7bf0;
            _DAT_005ff170 = (_DAT_006d7c18 - _DAT_006d7bf8) + _DAT_006d7be8;
            _DAT_005ff174 = _DAT_006d7bec + (_DAT_006d7c1c - _DAT_006d7bfc);
            fStack_164 = _DAT_006d7c20 - _DAT_006d7c00;
            _DAT_005ff178 = _DAT_006d7bf0 + fStack_164;
            _DAT_005ff17c = (_DAT_006d7c18 - _DAT_006d7bf8) - _DAT_006d7be8;
            _DAT_005ff180 = (_DAT_006d7c1c - _DAT_006d7bfc) - _DAT_006d7bec;
          }
          else {
            DAT_005ff158 = (_DAT_006d7c08 - _DAT_006d7be8) + _DAT_006d7c18;
            DAT_005ff15c = (_DAT_006d7c0c - _DAT_006d7bec) + _DAT_006d7c1c;
            DAT_005ff160 = (_DAT_006d7c10 - _DAT_006d7bf0) + _DAT_006d7c20;
            DAT_005ff164 = _DAT_006d7c08 + _DAT_006d7c18 + _DAT_006d7be8;
            DAT_005ff168 = _DAT_006d7c0c + _DAT_006d7c1c + _DAT_006d7bec;
            DAT_005ff16c = _DAT_006d7c10 + _DAT_006d7c20 + _DAT_006d7bf0;
            _DAT_005ff170 = (_DAT_006d7c18 - _DAT_006d7c08) + _DAT_006d7be8;
            _DAT_005ff174 = _DAT_006d7bec + (_DAT_006d7c1c - _DAT_006d7c0c);
            fStack_164 = _DAT_006d7c20 - _DAT_006d7c10;
            _DAT_005ff178 = _DAT_006d7bf0 + fStack_164;
            _DAT_005ff17c = (_DAT_006d7c18 - _DAT_006d7c08) - _DAT_006d7be8;
            _DAT_005ff180 = (_DAT_006d7c1c - _DAT_006d7c0c) - _DAT_006d7bec;
          }
          _DAT_006d7c24 = 0x3f800000;
          _DAT_006d7c14 = 0;
          _DAT_006d7c04 = 0;
          _DAT_006d7bf4 = 0;
          _DAT_005ff184 = fStack_164 - _DAT_006d7bf0;
          iVar23 = 0;
          DAT_005ff104 = *(undefined4 *)(puStack_134 + 2);
          _DAT_005ff108 = *(undefined4 *)(puStack_134 + 4);
          DAT_005ff0b4 = *(undefined4 *)(puStack_134 + 6);
          _DAT_005ff0bc = *(undefined4 *)(puStack_134 + 8);
          DAT_005ff0a8 = 5.60519e-45;
          piVar11 = &DAT_005ff080;
          _DAT_005ff0b8 = DAT_005ff0b4;
          _DAT_005ff0c0 = _DAT_005ff0bc;
          _DAT_005ff10c = _DAT_005ff108;
          _DAT_005ff110 = DAT_005ff104;
          do {
            *piVar11 = iVar23;
            piVar11 = piVar11 + 1;
            iVar23 = iVar23 + 1;
          } while ((int)piVar11 < 0x5ff090);
          pfVar9 = &DAT_005ff160;
          fStack_17c = 0.0;
          fStack_12c = 0.0;
          do {
            uVar8 = sub_401000(pfVar9 + -2);
            fStack_12c = fStack_12c + *pfVar9;
            pfVar9 = pfVar9 + 3;
            fVar12 = (float)((uint)fStack_17c | ~uVar8 << 0x10 | uVar8);
            fStack_17c = fVar12;
          } while ((int)pfVar9 < 0x5ff190);
          fStack_12c = fStack_12c * _DAT_0056e164;
          if ((((uint)fVar12 & 8) != 0) && (cStack_16a == '\0')) {
            *(undefined2 *)((int)puVar10 + 0x32) = 0;
          }
          puVar24 = local_f0;
          if (((uint)fVar12 & 0xffff0000) == 0xffff0000) {
            fStack_17c = (float)((uint)fVar12 & 0xffff);
            iStack_130 = 4;
            if ((fStack_17c == 0.0) ||
               (cVar7 = sub_4015F0(&DAT_005ff158,&DAT_005ff4d0,&DAT_005ff104,&DAT_005ff0b4,
                                   &iStack_130,&DAT_005ff080,&fStack_17c), puVar24 = local_f0,
               fVar12 = fStack_17c, cVar7 != '\0')) {
              fStack_17c = fVar12;
              if ((DAT_005833e4._1_1_ == '\0') ||
                 ((uStack_168 == 0 && (((*puStack_134 & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                iVar23 = -1;
                pfStack_170 = (float *)&DAT_005ff250;
              }
              else {
                iVar23 = 0;
                iStack_15c = __ftol();
                if (iStack_15c < 0) {
                  iStack_15c = 0;
                }
                else if (0x7ff < iStack_15c) {
                  iStack_15c = 0x7ff;
                }
                pfStack_170 = (float *)sub_41ED90((int)DAT_005ff0a8 << 5);
                puVar24 = local_f0;
                if (pfStack_170 == (float *)0x0) goto LAB_0043182b;
              }
              iVar16 = 0;
              if (0 < (int)DAT_005ff0a8) {
                piVar11 = &DAT_005ff080;
                pfVar9 = pfStack_170 + 2;
                do {
                  iVar18 = *piVar11;
                  piVar11 = piVar11 + 1;
                  iVar16 = iVar16 + 1;
                  fVar12 = _DAT_0056e008 / (&DAT_005ff160)[iVar18 * 3];
                  pfVar9[-2] = (fVar12 * (&DAT_005ff158)[iVar18 * 3] + _DAT_0056e008) *
                               _DAT_00583388;
                  pfVar9[-1] = (_DAT_0056e008 - fVar12 * (&DAT_005ff15c)[iVar18 * 3]) *
                               _DAT_0058338c;
                  *pfVar9 = ((&DAT_005ff160)[iVar18 * 3] - _DAT_0057d70c) * _DAT_0057d7fc *
                            _DAT_0057f914 * fVar12;
                  pfVar9[1] = fVar12;
                  pfVar9[2] = fStack_144;
                  pfVar9[3] = 0.0;
                  pfVar9[4] = (float)(&DAT_005ff104)[iVar18];
                  pfVar9[5] = (float)(&DAT_005ff0b4)[iVar18];
                  pfVar9 = pfVar9 + 8;
                } while (iVar16 < (int)DAT_005ff0a8);
              }
              if (iVar23 == -1) {
                uVar8 = uStack_140 & 0xff;
                uVar1 = *puStack_134;
                uVar22 = uStack_e0 & 0xff;
                fStack_17c = DAT_005ff0a8;
                uVar21 = (undefined1)uStack_140;
                if (0 < (int)DAT_005ff0a8) {
                  if (DAT_005833e1 == '\0') {
                    if (iStack_14c == 0) {
                      if (DAT_006d7c58 != 1) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                        DAT_006d7c58 = 1;
                      }
                    }
                    else {
                      if (DAT_006d7c54 != *(int *)(iStack_14c + 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x98))
                                  (DAT_00582cd4,0,*(int *)(iStack_14c + 0x10));
                        DAT_006d7c54 = *(int *)(iStack_14c + 0x10);
                      }
                      if ((uVar22 == 0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                        iVar23 = 2;
                      }
                      if (DAT_006d7c58 != iVar23) {
                        if ((uVar22 == 0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                          uVar19 = 2;
                        }
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                        if ((uVar22 == 0) || (DAT_005833f0 == '\0')) {
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
                    if ((_DAT_006d7c38 & 0xff) != uVar8) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                    }
                    if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0)) {
                      cVar20 = '\0';
                    }
                    else {
                      cVar20 = '\x01';
                    }
                    if (DAT_006d7c4e != cVar20) {
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0))
                      {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                         (DAT_006d7c4e = '\x01', (uStack_174 & 2) != 0)) {
                        DAT_006d7c4e = '\0';
                      }
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                      DAT_006d7c48 = 4;
                    }
                    if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                      uVar17 = 0;
                    }
                    else {
                      uVar17 = 1;
                    }
                    if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar17) {
                      if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                      if ((uVar1 & 2) != 0) {
                        _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                        if (DAT_006d7c70 != '\0') goto LAB_00430e7e;
                      }
                      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                    }
LAB_00430e7e:
                    if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                      (**(code **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                      DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                    }
                    switch(uStack_168) {
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
                      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar23) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
                    switch(uStack_174) {
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
                    if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_17c)) {
                      pfVar9 = pfStack_170 + 2;
                      fVar12 = fStack_17c;
                      do {
                        fVar3 = _DAT_0056e00c;
                        if (_DAT_0056e28c < *pfVar9) {
                          fVar3 = *pfVar9 - _DAT_0056e28c;
                        }
                        *pfVar9 = fVar3;
                        pfVar9 = pfVar9 + 8;
                        fVar12 = (float)((int)fVar12 + -1);
                      } while (fVar12 != 0.0);
                    }
                    (**(code **)(*DAT_00582cd4 + 0x70))
                              (DAT_00582cd4,6,0x1c4,pfStack_170,fStack_17c,0x1c);
                  }
                  else {
                    iVar23 = (uStack_168 << 2 | uStack_174) << 5;
                    if (iStack_14c == 0) {
                      uVar19 = 0;
                    }
                    else {
                      uVar19 = *(undefined4 *)(iStack_14c + 0x1c);
                    }
                    pcVar13 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar13 = sub_442BD0;
                    }
                    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                               pfStack_170,DAT_005ff0a8,1,0,
                               CONCAT31((uint3)((uint)iVar23 >> 8) |
                                        (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                        (byte)iVar23 | uVar22 != 0 | -((uVar1 & 2) != 0) & 4U) | 2);
                  }
                }
                puVar24 = local_f0;
                if (cStack_175 != '\0') {
                  uVar17 = uStack_168 | 2;
                  uVar1 = *puStack_134;
                  fStack_17c = DAT_005ff0a8;
                  if (0 < (int)DAT_005ff0a8) {
                    if (DAT_005833e1 == '\0') {
                      if (iStack_14c == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)(iStack_14c + 0x10)) {
                          (**(code **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)(iStack_14c + 0x10));
                          DAT_006d7c54 = *(int *)(iStack_14c + 0x10);
                        }
                        if ((uVar22 == 0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                          iVar23 = 2;
                        }
                        if (DAT_006d7c58 != iVar23) {
                          if ((uVar22 == 0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                            uVar19 = 2;
                          }
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                          if ((uVar22 == 0) || (DAT_005833f0 == '\0')) {
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
                      if ((_DAT_006d7c38 & 0xff) != uVar8) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                      }
                      uVar8 = uStack_174;
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_174 & 2) != 0))
                      {
                        cVar20 = '\0';
                      }
                      else {
                        cVar20 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar20) {
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           ((uStack_174 & 2) != 0)) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uVar8 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                        DAT_006d7c48 = 4;
                      }
                      if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        uVar8 = 0;
                      }
                      else {
                        uVar8 = 1;
                      }
                      if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar8) {
                        if (((uVar1 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                        if ((uVar1 & 2) != 0) {
                          _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                          if (DAT_006d7c70 != '\0') goto LAB_004314d7;
                        }
                        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                      }
LAB_004314d7:
                      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x58))
                                  (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
                        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
                      }
                      switch(uVar17) {
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
                        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar23) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
                      switch(uStack_174) {
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
                      if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_17c)) {
                        pfVar9 = pfStack_170 + 2;
                        fVar12 = fStack_17c;
                        do {
                          fVar3 = _DAT_0056e00c;
                          if (_DAT_0056e28c < *pfVar9) {
                            fVar3 = *pfVar9 - _DAT_0056e28c;
                          }
                          *pfVar9 = fVar3;
                          pfVar9 = pfVar9 + 8;
                          fVar12 = (float)((int)fVar12 + -1);
                        } while (fVar12 != 0.0);
                      }
                      (**(code **)(*DAT_00582cd4 + 0x70))
                                (DAT_00582cd4,6,0x1c4,pfStack_170,fStack_17c,0x1c);
                      puVar24 = local_f0;
                    }
                    else {
                      iVar23 = (uVar17 * 4 | uStack_174) << 5;
                      if (iStack_14c == 0) {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = *(undefined4 *)(iStack_14c + 0x1c);
                      }
                      pcVar13 = sub_4C6CD0;
                      if (DAT_00583380 == '\0') {
                        pcVar13 = sub_442BD0;
                      }
                      (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                                 pfStack_170,DAT_005ff0a8,1,0,
                                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                          (byte)iVar23 | uVar22 != 0 | -((uVar1 & 2) != 0) & 4U) | 2
                                );
                      puVar24 = local_f0;
                    }
                  }
                }
              }
              else {
                if (cStack_175 != '\0') {
                  fStack_17c = DAT_005ff0a8;
                  uVar1 = *puStack_134;
                  if ((0 < (int)DAT_005ff0a8) &&
                     (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
                    iVar16 = iVar23 * 0x800 + iStack_15c;
                    *puVar10 = (&DAT_005f6ef8)[iVar16];
                    puVar10[1] = pfStack_170;
                    puVar10[2] = fStack_17c;
                    puVar10[3] = 0;
                    puVar10[4] = 0;
                    puVar10[6] = 0;
                    puVar10[5] = iStack_14c;
                    puVar10[7] = (uStack_174 * 4 | uStack_168) << 0xc | -(uint)(cVar20 != '\0') & 2
                                 | -(uint)((uVar1 & 2) != 0) & 0x10 |
                                 -(uint)((char)uStack_140 != '\0') & 4 | 0x20c9;
                    (&DAT_005f6ef8)[iVar16] = puVar10;
                  }
                }
                fVar12 = DAT_005ff0a8;
                uVar1 = *puStack_134;
                puVar24 = local_f0;
                if ((0 < (int)DAT_005ff0a8) &&
                   (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar24 = local_f0,
                   puVar10 != (undefined4 *)0x0)) {
                  iVar23 = iVar23 * 0x800 + iStack_15c;
                  *puVar10 = (&DAT_005f6ef8)[iVar23];
                  puVar10[1] = pfStack_170;
                  puVar10[3] = 0;
                  puVar10[4] = 0;
                  puVar10[6] = 0;
                  puVar10[5] = iStack_14c;
                  puVar10[2] = fVar12;
                  uVar8 = (uStack_174 * 4 | uStack_168) << 0xc | -(uint)(cVar20 != '\0') & 2 |
                          -(uint)((uVar1 & 2) != 0) & 0x10;
LAB_0042f2bc:
                  puVar10[7] = CONCAT31((int3)(uVar8 >> 8),
                                        (byte)uVar8 | -((char)uStack_140 != '\0') & 4U) | 0xc9;
                  (&DAT_005f6ef8)[iVar23] = puVar10;
                  puVar24 = local_f0;
                }
              }
            }
          }
        }
        goto LAB_0043182b;
      }
      fVar12 = (float)(int)puVar10[2] * (float)_DAT_0056e020;
      fVar3 = (float)(int)puVar10[3] * (float)_DAT_0056e020;
      fVar4 = -((float)(int)puVar10[4] * (float)_DAT_0056e020);
      fStack_dc = _DAT_0057db20 * fVar12 + _DAT_0057db30 * fVar3 + _DAT_0057db40 * fVar4 +
                  _DAT_0057db50;
      fStack_d8 = _DAT_0057db24 * fVar12 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar4 +
                  _DAT_0057db54;
      fStack_d4 = _DAT_0057db28 * fVar12 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar4 +
                  _DAT_0057db58;
      fStack_d0 = _DAT_0057db2c * fVar12 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar4 +
                  _DAT_0057db5c;
      uStack_bc = sub_401080(&fStack_dc);
      if ((uStack_bc != 0) && (puVar24 = local_f0, (uStack_bc & 0x30) != 0)) goto LAB_0043182b;
      if ((uVar1 & 0x4000) == 0) {
        fVar12 = (float)(puVar10[2] + puVar10[6] * 2) * (float)_DAT_0056e020;
        fStack_17c = (float)(puVar10[4] + puVar10[8] * 2);
        fVar3 = (float)(puVar10[3] + puVar10[7] * 2) * (float)_DAT_0056e020;
      }
      else {
        fStack_17c = (float)(puVar10[8] + puVar10[4]);
        fVar12 = (float)(int)(puVar10[6] + puVar10[2]) * (float)_DAT_0056e020;
        fVar3 = (float)(int)(puVar10[7] + puVar10[3]) * (float)_DAT_0056e020;
      }
      fVar4 = -((float)(int)fStack_17c * (float)_DAT_0056e020);
      fStack_b8 = _DAT_0057db20 * fVar12 + _DAT_0057db30 * fVar3 + _DAT_0057db40 * fVar4 +
                  _DAT_0057db50;
      fStack_b4 = _DAT_0057db24 * fVar12 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar4 +
                  _DAT_0057db54;
      fStack_b0 = _DAT_0057db28 * fVar12 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar4 +
                  _DAT_0057db58;
      fStack_ac = _DAT_0057db2c * fVar12 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar4 +
                  _DAT_0057db5c;
      uStack_98 = sub_401080(&fStack_b8);
      if ((uStack_98 != 0) && (puVar24 = local_f0, (uStack_98 & 0x30) != 0)) goto LAB_0043182b;
      fStack_c0 = _DAT_0056e008 / fStack_d0;
      fStack_cc = (fStack_dc * fStack_c0 + (float)_DAT_0056e038) * _DAT_00583388;
      fStack_c8 = ((float)_DAT_0056e038 - fStack_d8 * fStack_c0) * _DAT_0058338c;
      fStack_c4 = ((float)_DAT_0056e038 - fStack_d4 * fStack_c0) * (float)_DAT_0056e030;
      fStack_9c = _DAT_0056e008 / fStack_ac;
      fStack_a8 = (fStack_b8 * fStack_9c + (float)_DAT_0056e038) * _DAT_00583388;
      fStack_a4 = ((float)_DAT_0056e038 - fStack_b4 * fStack_9c) * _DAT_0058338c;
      fStack_a0 = ((float)_DAT_0056e038 - fStack_b0 * fStack_9c) * (float)_DAT_0056e030;
      fStack_12c = (fStack_ac + fStack_d0) * _DAT_0056e158;
      fStack_94 = fStack_a4 - fStack_c8;
      fStack_90 = fStack_cc - fStack_a8;
      fStack_17c = SQRT(fStack_94 * fStack_94 + fStack_90 * fStack_90);
      fStack_94 = fStack_94 / fStack_17c;
      fStack_90 = fStack_90 / fStack_17c;
      fStack_f8 = _DAT_0056e00c / fStack_17c;
      fStack_100 = (float)DAT_00583374 * _DAT_0056e1dc * fStack_94 * _DAT_0056e158;
      uVar19 = puVar10[0xe];
      uStack_148 = CONCAT31(uStack_148._1_3_,(char)uVar19);
      uStack_154 = CONCAT31(uStack_154._1_3_,(char)((uint)uVar19 >> 0x10));
      uStack_150 = CONCAT31(uStack_150._1_3_,(char)((uint)uVar19 >> 8));
      fStack_fc = (float)DAT_00583378 * _DAT_0056e1d8 * fStack_90 * _DAT_0056e158;
      fStack_8c = fStack_f8;
      (*(code *)PTR_sub_408390_00570360)(&uStack_148,&uStack_150,&uStack_154,&cStack_169,2);
      uStack_168 = DAT_00573ed0;
      uStack_174 = DAT_00573ed4;
      cStack_175 = sub_40C510(&uStack_148,&uStack_150,&uStack_154);
      if (((char)uStack_148 == (char)uStack_150) && ((char)uStack_150 == (char)uStack_154)) {
        cVar20 = '\x01';
      }
      else {
        cVar20 = '\0';
      }
      afStack_80[0] = fStack_cc - fStack_100;
      afStack_80[2] = fStack_c4;
      fStack_58 = fStack_c4;
      afStack_80[3] = fStack_c0;
      afStack_80[1] = fStack_c8 - fStack_fc;
      fStack_38 = fStack_a0;
      fStack_18 = fStack_a0;
      fStack_54 = fStack_c0;
      fStack_34 = fStack_9c;
      fStack_60 = fStack_cc + fStack_100;
      fStack_14 = fStack_9c;
      fStack_5c = fStack_fc + fStack_c8;
      fStack_40 = fStack_a8 + fStack_100;
      uStack_70 = uStack_154 & 0xff |
                  ((uint)CONCAT11(cStack_169,(char)uStack_148) << 8 | uStack_150 & 0xff) << 8;
      fStack_3c = fStack_fc + fStack_a4;
      uStack_140 = CONCAT31(uStack_140._1_3_,cVar20);
      uStack_c = 0;
      uStack_2c = 0;
      uStack_4c = 0;
      uStack_6c = 0;
      fStack_20 = fStack_a8 - fStack_100;
      uStack_8 = 0;
      uStack_28 = 0;
      uStack_48 = 0;
      uStack_68 = 0;
      uStack_4 = 0;
      uStack_24 = 0;
      fStack_1c = fStack_a4 - fStack_fc;
      uStack_44 = 0;
      uStack_64 = 0;
      uVar8 = (uint)(afStack_80[0] < _DAT_0056e00c);
      if (DAT_00583390 <= afStack_80[0]) {
        uVar8 = uVar8 | 2;
      }
      if (afStack_80[1] < _DAT_0056e00c) {
        uVar8 = uVar8 | 8;
      }
      if (DAT_00583394 <= afStack_80[1]) {
        uVar8 = uVar8 | 4;
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
      uVar17 = (uint)(fStack_40 < _DAT_0056e00c);
      if (DAT_00583390 <= fStack_40) {
        uVar17 = uVar17 | 2;
      }
      if (fStack_3c < _DAT_0056e00c) {
        uVar17 = uVar17 | 8;
      }
      if (DAT_00583394 <= fStack_3c) {
        uVar17 = uVar17 | 4;
      }
      uVar14 = (uint)(fStack_20 < _DAT_0056e00c);
      if (DAT_00583390 <= fStack_20) {
        uVar14 = uVar14 | 2;
      }
      if (fStack_1c < _DAT_0056e00c) {
        uVar14 = uVar14 | 8;
      }
      if (DAT_00583394 <= fStack_1c) {
        uVar14 = uVar14 | 4;
      }
      puVar24 = local_f0;
      uStack_50 = uStack_70;
      uStack_30 = uStack_70;
      uStack_10 = uStack_70;
      if (((~uVar14 | ~uVar17 | ~uVar22 | ~uVar8) & 0xffff) != 0xffff) goto LAB_0043182b;
      if (DAT_005833e4._1_1_ == '\0') {
        iVar23 = -1;
      }
      else if (uStack_168 == 0) {
        iVar23 = -1;
      }
      else {
        iVar23 = 0;
        iStack_15c = __ftol();
        if (iStack_15c < 0) {
          iStack_15c = 0;
        }
        else if (0x7ff < iStack_15c) {
          iStack_15c = 0x7ff;
        }
      }
      uVar8 = uVar14 | uVar17 | uVar22 | uVar8;
      cStack_16a = uVar8 != 0;
      if ((bool)cStack_16a) {
        iVar16 = 0;
        for (uVar22 = uVar8; uVar22 != 0; uVar22 = (int)uVar22 >> 1) {
          if ((uVar22 & 1) != 0) {
            iVar16 = iVar16 + 1;
          }
        }
        pfStack_170 = (float *)sub_41ED90((iVar16 * 3 + 3) * 0x40);
        if (pfStack_170 == (float *)0x0) {
          return;
        }
        iVar16 = sub_43AC00(pfStack_170,afStack_80,4,uVar8);
      }
      else {
        pfStack_170 = (float *)sub_41ED90(0x80);
        puVar24 = local_f0;
        if (pfStack_170 == (float *)0x0) goto LAB_0043182b;
        iVar16 = 4;
        pfVar9 = afStack_80;
        pfVar15 = pfStack_170;
        for (iVar18 = 0x20; iVar18 != 0; iVar18 = iVar18 + -1) {
          *pfVar15 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar15 = pfVar15 + 1;
        }
      }
      uVar22 = uStack_168;
      uVar8 = uStack_174;
      iStack_130 = iVar16;
      if (iVar23 != -1) {
        if (((cStack_175 != '\0') && (0 < iVar16)) &&
           (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
          iVar18 = iVar23 * 0x800 + iStack_15c;
          *puVar10 = (&DAT_005f6ef8)[iVar18];
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[5] = 0;
          puVar10[6] = 0;
          puVar10[1] = pfStack_170;
          puVar10[2] = iVar16;
          puVar10[7] = (uStack_174 * 4 | uStack_168) << 0xc | (uint)(cStack_16a == '\0') |
                       -(uint)(cVar20 != '\0') & 4 | 0x20c8;
          (&DAT_005f6ef8)[iVar18] = puVar10;
        }
        iVar16 = iStack_130;
        puVar24 = local_f0;
        if ((0 < iStack_130) &&
           (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar24 = local_f0,
           puVar10 != (undefined4 *)0x0)) {
          iVar23 = iVar23 * 0x800 + iStack_15c;
          *puVar10 = (&DAT_005f6ef8)[iVar23];
          puVar10[1] = pfStack_170;
          puVar10[2] = iVar16;
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[5] = 0;
          puVar10[6] = 0;
          puVar10[7] = CONCAT31((int3)(((uStack_174 * 4 | uStack_168) << 0xc) >> 8),
                                cStack_16a == '\0' | -(cVar20 != '\0') & 4U) | 200;
          (&DAT_005f6ef8)[iVar23] = puVar10;
        }
        goto LAB_0043182b;
      }
      uVar17 = uStack_140 & 0xff;
      fStack_17c = (float)(uint)(cStack_16a == '\0');
      uVar21 = (undefined1)uStack_140;
      if (iVar16 < 1) goto LAB_0042e5fa;
      fStack_164 = (float)iVar16;
      if (DAT_005833e1 != '\0') {
        pcVar13 = sub_4C6CD0;
        if (DAT_00583380 == '\0') {
          pcVar13 = sub_442BD0;
        }
        (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfStack_170,iVar16,
                   fStack_17c,0,
                   (uStack_168 * 4 | uStack_174) << 5 | (-(uint)(uVar17 != 0) & 0xfffffe00) + 0x200
                   | 2);
        goto LAB_0042e5fa;
      }
      if (DAT_006d7c58 != 1) {
        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
        DAT_006d7c58 = 1;
      }
      if (DAT_006d7c34 != 1) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
        DAT_006d7c34 = 1;
      }
      if ((_DAT_006d7c38 & 0xff) != uVar17) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar17);
        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
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
        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
      }
      if (DAT_006d7c48 != 4) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
        DAT_006d7c48 = 4;
      }
      if (DAT_006d7c3a != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
      }
      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
      }
      uVar22 = uStack_168;
      switch(uStack_168) {
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
        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        if (DAT_006d7c40 != iVar23) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
        goto joined_r0x0042e4fd;
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
joined_r0x0042e4fd:
        if (DAT_006d7c44 != 2) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
          DAT_006d7c44 = 2;
        }
      }
      uVar8 = uStack_174;
      iVar23 = 3;
      switch(uStack_174) {
      case 0:
      case 2:
        if (DAT_006d7c5c != 2) {
          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
          DAT_006d7c5c = 2;
        }
        break;
      case 1:
        if (DAT_006d7c5c != 3) {
          uVar19 = 3;
          iVar16 = *DAT_00582cd4;
LAB_0042e575:
          (**(code **)(iVar16 + 0xa0))(DAT_00582cd4,0,4,uVar19);
          DAT_006d7c5c = iVar23;
        }
        break;
      case 3:
        iVar23 = 4;
        if (DAT_006d7c5c != 4) {
          uVar19 = 4;
          iVar16 = *DAT_00582cd4;
          goto LAB_0042e575;
        }
      }
      if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_164)) {
        pfVar9 = pfStack_170 + 2;
        fVar12 = fStack_164;
        do {
          fVar3 = _DAT_0056e00c;
          if (_DAT_0056e28c < *pfVar9) {
            fVar3 = *pfVar9 - _DAT_0056e28c;
          }
          *pfVar9 = fVar3;
          pfVar9 = pfVar9 + 8;
          fVar12 = (float)((int)fVar12 + -1);
        } while (fVar12 != 0.0);
      }
      (**(code **)(*DAT_00582cd4 + 0x70))
                (DAT_00582cd4,(-(fStack_17c != 0.0) & 2U) + 4,0x1c4,pfStack_170,fStack_164,0x1c);
LAB_0042e5fa:
      puVar24 = local_f0;
      if ((cStack_175 != '\0') && (0 < iStack_130)) {
        fStack_164 = (float)iStack_130;
        if (DAT_005833e1 == '\0') {
          if (DAT_006d7c58 != 1) {
            (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
            DAT_006d7c58 = 1;
          }
          if (DAT_006d7c34 != 1) {
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
            DAT_006d7c34 = 1;
          }
          if ((_DAT_006d7c38 & 0xff) != uVar17) {
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar17);
            _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
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
            _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
          }
          if (DAT_006d7c48 != 4) {
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
            DAT_006d7c48 = 4;
          }
          if (DAT_006d7c3a != '\0') {
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
            _DAT_006d7c38 = (uint3)_DAT_006d7c38;
          }
          if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
            (**(code **)(*DAT_00582cd4 + 0x58))
                      (DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
            DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
          }
          switch(uVar22 | 2) {
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
            iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
            if (DAT_006d7c40 != iVar23) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
          switch(uStack_174) {
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
          if ((DAT_005833e4._3_1_ == '\0') && (0 < (int)fStack_164)) {
            pfVar9 = pfStack_170 + 2;
            fVar12 = fStack_164;
            do {
              fVar3 = _DAT_0056e00c;
              if (_DAT_0056e28c < *pfVar9) {
                fVar3 = *pfVar9 - _DAT_0056e28c;
              }
              *pfVar9 = fVar3;
              pfVar9 = pfVar9 + 8;
              fVar12 = (float)((int)fVar12 + -1);
            } while (fVar12 != 0.0);
          }
          (**(code **)(*DAT_00582cd4 + 0x70))
                    (DAT_00582cd4,(-(fStack_17c != 0.0) & 2U) + 4,0x1c4,pfStack_170,fStack_164,0x1c)
          ;
          puVar24 = local_f0;
        }
        else {
          pcVar13 = sub_4C6CD0;
          if (DAT_00583380 == '\0') {
            pcVar13 = sub_442BD0;
          }
          (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfStack_170,
                     iStack_130,fStack_17c,0,
                     ((uVar22 | 2) * 4 | uVar8) << 5 | (-(uint)(uVar17 != 0) & 0xfffffe00) + 0x200 |
                     2);
          puVar24 = local_f0;
        }
      }
      goto LAB_0043182b;
    }
    fVar12 = (float)(int)puVar10[2] * (float)_DAT_0056e020;
    fVar3 = (float)(int)puVar10[3] * (float)_DAT_0056e020;
    fVar4 = -((float)(int)puVar10[4] * (float)_DAT_0056e020);
    fStack_10c = _DAT_0057dc28 * fVar12 + _DAT_0057dc38 * fVar3 + _DAT_0057dc48 * fVar4 +
                 _DAT_0057dc58;
    fStack_108 = _DAT_0057dc2c * fVar12 + _DAT_0057dc3c * fVar3 + _DAT_0057dc4c * fVar4 +
                 _DAT_0057dc5c;
    fStack_104 = _DAT_0057dc30 * fVar12 + _DAT_0057dc40 * fVar3 + _DAT_0057dc50 * fVar4 +
                 _DAT_0057dc60;
    uVar8 = sub_401000(&fStack_10c);
    puVar24 = local_f0;
    if ((uVar8 & 0x30) != 0) goto LAB_0043182b;
    fStack_158 = _DAT_0056e008 / fStack_104;
    fStack_17c = (float)((int)puVar10[0xf] >> 0xc);
    fStack_128 = (fStack_158 * fStack_10c + _DAT_0056e008) * _DAT_00583388;
    fStack_124 = (_DAT_0056e008 - fStack_158 * fStack_108) * _DAT_0058338c;
    fStack_120 = (fStack_104 - _DAT_0057d70c) * _DAT_0057d7fc * _DAT_0057f914 * fStack_158;
    fVar12 = (float)(int)fStack_17c * local_88;
    fStack_164 = (float)(int)fStack_17c * local_84;
    fStack_144 = _DAT_0056e00c;
    if (fVar12 < fStack_128) {
      fStack_144 = fStack_128 - fVar12;
    }
    fVar3 = (float)DAT_00583374;
    fStack_160 = fVar3;
    if (fStack_128 < fVar3 - fVar12) {
      fStack_160 = fVar12 + fStack_128;
    }
    if (fStack_164 < fStack_124) {
      fStack_13c = fStack_124 - fStack_164;
    }
    else {
      fStack_13c = 0.0;
    }
    pfStack_170 = (float *)(float)DAT_00583378;
    pfStack_138 = pfStack_170;
    if (fStack_124 < (float)pfStack_170 - fStack_164) {
      pfStack_138 = (float *)(fStack_164 + fStack_124);
    }
    if ((((fVar3 <= fStack_144) || (fStack_160 <= _DAT_0056e00c)) ||
        ((float)pfStack_170 <= fStack_13c)) || ((float)pfStack_138 <= _DAT_0056e00c))
    goto LAB_0043182b;
    uVar19 = puVar10[0xe];
    uStack_148 = CONCAT31(uStack_148._1_3_,(char)uVar19);
    uStack_150 = CONCAT31(uStack_150._1_3_,(char)((uint)uVar19 >> 8));
    uStack_154 = CONCAT31(uStack_154._1_3_,(char)((uint)uVar19 >> 0x10));
    if ((uVar1 & 8) == 0) {
      uStack_168 = 0;
      uStack_174 = 0;
    }
    else {
      (*(code *)PTR_sub_408390_00570360)(&uStack_148,&uStack_150,&uStack_154,&cStack_169,2);
      uStack_168 = DAT_00573ed0;
      uStack_174 = DAT_00573ed4;
    }
    uVar8 = uStack_168;
    cStack_175 = sub_40C510(&uStack_148,&uStack_150,&uStack_154);
    if (((char)uStack_148 == (char)uStack_150) && ((char)uStack_150 == (char)uStack_154)) {
      cVar20 = '\x01';
    }
    else {
      cVar20 = '\0';
    }
    fVar12 = (float)(((uint)CONCAT11(cStack_169,(char)uStack_148) << 8 | uStack_150 & 0xff) << 8 |
                    uStack_154 & 0xff);
    uStack_140 = CONCAT31(uStack_140._1_3_,cVar20);
    if ((DAT_005833e4._1_1_ == '\0') || (uVar8 == 0)) {
      iVar23 = -1;
      pfVar9 = (float *)&DAT_005ff250;
    }
    else {
      iVar23 = 0;
      iStack_15c = __ftol();
      if (iStack_15c < 0) {
        iStack_15c = 0;
      }
      else if (0x7ff < iStack_15c) {
        iStack_15c = 0x7ff;
      }
      pfVar9 = (float *)sub_41ED90(0x80);
      puVar24 = local_f0;
      if (pfVar9 == (float *)0x0) goto LAB_0043182b;
    }
    pfVar9[0x18] = fStack_144;
    *pfVar9 = fStack_144;
    pfVar9[0x10] = fStack_160;
    pfVar9[8] = fStack_160;
    pfVar9[1] = fStack_13c;
    pfVar9[9] = fStack_13c;
    pfVar9[0x19] = (float)pfStack_138;
    pfVar9[0x11] = (float)pfStack_138;
    pfVar9[0x12] = fStack_120;
    pfVar9[0x1a] = fStack_120;
    pfVar9[2] = fStack_120;
    pfVar9[10] = fStack_120;
    pfVar9[0xb] = fStack_158;
    pfVar9[0x1b] = fStack_158;
    pfVar9[0x13] = fStack_158;
    pfVar9[3] = fStack_158;
    pfVar9[0x1c] = fVar12;
    pfVar9[0x14] = fVar12;
    pfVar9[0xc] = fVar12;
    pfVar9[4] = fVar12;
    pfVar9[0x1d] = 0.0;
    pfVar9[0x15] = 0.0;
    pfVar9[0xd] = 0.0;
    pfVar9[5] = 0.0;
    if (iVar23 != -1) {
      if ((cStack_175 != '\0') &&
         (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
        iVar16 = iVar23 * 0x800 + iStack_15c;
        *puVar10 = (&DAT_005f6ef8)[iVar16];
        puVar10[1] = pfVar9;
        puVar10[3] = 0;
        puVar10[4] = 0;
        puVar10[5] = 0;
        puVar10[6] = 0;
        puVar10[2] = 4;
        puVar10[7] = (uStack_174 * 4 | uStack_168) << 0xc | -(uint)(cVar20 != '\0') & 4 | 0x20c9;
        (&DAT_005f6ef8)[iVar16] = puVar10;
      }
      puVar10 = (undefined4 *)sub_41ED90(0x20);
      puVar24 = local_f0;
      if (puVar10 != (undefined4 *)0x0) {
        iVar23 = iVar23 * 0x800 + iStack_15c;
        *puVar10 = (&DAT_005f6ef8)[iVar23];
        puVar10[1] = pfVar9;
        puVar10[3] = 0;
        puVar10[4] = 0;
        puVar10[5] = 0;
        puVar10[6] = 0;
        puVar10[2] = 4;
        puVar10[7] = CONCAT31((int3)(((uStack_174 * 4 | uStack_168) << 0xc) >> 8),-(cVar20 != '\0'))
                     & 0xffffff04 | 0xc9;
        (&DAT_005f6ef8)[iVar23] = puVar10;
      }
      goto LAB_0043182b;
    }
    uVar8 = uStack_140 & 0xff;
    uVar21 = (undefined1)uStack_140;
    if (DAT_005833e1 == '\0') {
      if (DAT_006d7c58 != 1) {
        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
        DAT_006d7c58 = 1;
      }
      if (DAT_006d7c34 != 1) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
        DAT_006d7c34 = 1;
      }
      if ((_DAT_006d7c38 & 0xff) != uVar8) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
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
        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
      }
      if (DAT_006d7c48 != 4) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
        DAT_006d7c48 = 4;
      }
      if (DAT_006d7c3a != '\0') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
      }
      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
      }
      switch(uStack_168) {
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
        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        if (DAT_006d7c40 != iVar23) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
      iVar23 = 3;
      switch(uStack_174) {
      case 0:
      case 2:
        if (DAT_006d7c5c != 2) {
          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
          DAT_006d7c5c = 2;
        }
        break;
      case 1:
        if (DAT_006d7c5c != 3) {
          uVar19 = 3;
          iVar16 = *DAT_00582cd4;
LAB_0042d25c:
          (**(code **)(iVar16 + 0xa0))(DAT_00582cd4,0,4,uVar19);
          DAT_006d7c5c = iVar23;
        }
        break;
      case 3:
        iVar23 = 4;
        if (DAT_006d7c5c != 4) {
          uVar19 = 4;
          iVar16 = *DAT_00582cd4;
          goto LAB_0042d25c;
        }
      }
      if (DAT_005833e4._3_1_ == '\0') {
        pfVar15 = pfVar9 + 2;
        iVar23 = 4;
        do {
          fVar12 = _DAT_0056e00c;
          if (_DAT_0056e28c < *pfVar15) {
            fVar12 = *pfVar15 - _DAT_0056e28c;
          }
          *pfVar15 = fVar12;
          pfVar15 = pfVar15 + 8;
          iVar23 = iVar23 + -1;
        } while (iVar23 != 0);
      }
      (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
    }
    else {
      iVar23 = (uStack_168 * 4 | uStack_174) << 5;
      pcVar13 = sub_4C6CD0;
      if (DAT_00583380 == '\0') {
        pcVar13 = sub_442BD0;
      }
      (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfVar9,4,1,0,
                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),(char)iVar23) | 2
                );
    }
    puVar24 = local_f0;
    if (cStack_175 == '\0') goto LAB_0043182b;
    uVar22 = uStack_168 | 2;
    if (DAT_005833e1 != '\0') {
      iVar23 = (uVar22 * 4 | uStack_174) << 5;
      pcVar13 = sub_4C6CD0;
      if (DAT_00583380 == '\0') {
        pcVar13 = sub_442BD0;
      }
      (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfVar9,4,1,0,
                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),(char)iVar23) | 2
                );
      puVar24 = local_f0;
      goto LAB_0043182b;
    }
    if (DAT_006d7c58 != 1) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
    if (DAT_006d7c34 != 1) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
      DAT_006d7c34 = 1;
    }
    if ((_DAT_006d7c38 & 0xff) != uVar8) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
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
      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
    }
    if (DAT_006d7c48 != 4) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
      DAT_006d7c48 = 4;
    }
    if (DAT_006d7c3a != '\0') {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
    }
    if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
      DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
    }
    switch(uVar22) {
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
      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
      if (DAT_006d7c40 != iVar23) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
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
      goto joined_r0x0042d682;
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
joined_r0x0042d682:
      if (DAT_006d7c44 != 2) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
        DAT_006d7c44 = 2;
      }
    }
    switch(uStack_174) {
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
    if (DAT_005833e4._3_1_ == '\0') {
      pfVar15 = pfVar9 + 2;
      iVar23 = 4;
      do {
        fVar12 = _DAT_0056e00c;
        if (_DAT_0056e28c < *pfVar15) {
          fVar12 = *pfVar15 - _DAT_0056e28c;
        }
        *pfVar15 = fVar12;
        pfVar15 = pfVar15 + 8;
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
    }
    (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
    puVar24 = local_f0;
LAB_0043182b:
    puVar10 = (undefined4 *)*puVar24;
    uVar8 = local_f4;
  } while( true );
}

