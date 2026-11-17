/* sub_41FB30 @ 0041fb30   11212 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sub_41FB30(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          float param_6,char param_7,char param_8,int param_9,int param_10,uint param_11,
          uint param_12,char param_13,byte *param_14)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  byte bVar6;
  bool bVar7;
  ushort uVar8;
  char cVar9;
  byte bVar10;
  undefined1 uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  float fVar15;
  float *pfVar16;
  undefined4 *puVar17;
  int iVar18;
  float *pfVar19;
  code *pcVar20;
  int iVar21;
  uint uVar22;
  undefined4 uVar23;
  int iVar24;
  uint *puVar25;
  undefined4 *puVar26;
  undefined4 *puVar27;
  float *pfVar28;
  bool bVar29;
  uint local_13c;
  int local_134;
  float local_130;
  char local_129;
  int local_128;
  byte local_122;
  char local_121;
  int local_120;
  int local_11c;
  int local_114;
  uint local_110;
  uint local_10c;
  uint local_108;
  int local_104;
  byte local_100;
  ushort *local_fc;
  uint local_f8;
  uint local_f4;
  uint local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  uint local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  undefined4 *local_b8;
  float local_b4;
  float local_b0;
  uint local_a8;
  float local_a4;
  float local_a0;
  float local_98 [4];
  float local_88;
  float local_84;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40 [4];
  undefined4 local_3c [15];
  
  local_122 = 0;
  sub_41E990(param_2,param_3,param_4,param_5,&DAT_006d7b68);
  _DAT_006d7be8 =
       _DAT_0057db40 * _DAT_006d7b70 +
       _DAT_0057db50 * _DAT_006d7b74 + _DAT_0057db20 * _DAT_006d7b68 + _DAT_0057db30 * _DAT_006d7b6c
  ;
  _DAT_006d7bec =
       _DAT_0057db34 * _DAT_006d7b6c +
       _DAT_0057db44 * _DAT_006d7b70 + _DAT_0057db54 * _DAT_006d7b74 + _DAT_0057db24 * _DAT_006d7b68
  ;
  _DAT_006d7bf0 =
       _DAT_0057db38 * _DAT_006d7b6c +
       _DAT_0057db48 * _DAT_006d7b70 + _DAT_0057db58 * _DAT_006d7b74 + _DAT_0057db28 * _DAT_006d7b68
  ;
  _DAT_006d7bf4 =
       _DAT_0057db2c * _DAT_006d7b68 +
       _DAT_0057db3c * _DAT_006d7b6c + _DAT_0057db4c * _DAT_006d7b70 + _DAT_0057db5c * _DAT_006d7b74
  ;
  _DAT_006d7bf8 =
       _DAT_006d7b78 * _DAT_0057db20 +
       _DAT_006d7b7c * _DAT_0057db30 + _DAT_006d7b80 * _DAT_0057db40 + _DAT_006d7b84 * _DAT_0057db50
  ;
  _DAT_006d7bfc =
       _DAT_006d7b78 * _DAT_0057db24 +
       _DAT_006d7b7c * _DAT_0057db34 + _DAT_006d7b80 * _DAT_0057db44 + _DAT_006d7b84 * _DAT_0057db54
  ;
  _DAT_006d7c00 =
       _DAT_006d7b78 * _DAT_0057db28 +
       _DAT_006d7b7c * _DAT_0057db38 + _DAT_006d7b80 * _DAT_0057db48 + _DAT_006d7b84 * _DAT_0057db58
  ;
  _DAT_006d7c04 =
       _DAT_006d7b78 * _DAT_0057db2c +
       _DAT_006d7b7c * _DAT_0057db3c + _DAT_006d7b80 * _DAT_0057db4c + _DAT_006d7b84 * _DAT_0057db5c
  ;
  _DAT_006d7c08 =
       _DAT_006d7b88 * _DAT_0057db20 +
       _DAT_006d7b8c * _DAT_0057db30 + _DAT_006d7b90 * _DAT_0057db40 + _DAT_006d7b94 * _DAT_0057db50
  ;
  _DAT_006d7c0c =
       _DAT_006d7b88 * _DAT_0057db24 +
       _DAT_006d7b8c * _DAT_0057db34 + _DAT_006d7b90 * _DAT_0057db44 + _DAT_006d7b94 * _DAT_0057db54
  ;
  _DAT_006d7c10 =
       _DAT_006d7b88 * _DAT_0057db28 +
       _DAT_006d7b8c * _DAT_0057db38 + _DAT_006d7b90 * _DAT_0057db48 + _DAT_006d7b94 * _DAT_0057db58
  ;
  _DAT_006d7c14 =
       _DAT_006d7b88 * _DAT_0057db2c +
       _DAT_006d7b8c * _DAT_0057db3c + _DAT_006d7b90 * _DAT_0057db4c + _DAT_006d7b94 * _DAT_0057db5c
  ;
  _DAT_006d7c18 =
       DAT_006d7b98 * _DAT_0057db20 +
       DAT_006d7b9c * _DAT_0057db30 + DAT_006d7ba0 * _DAT_0057db40 + _DAT_006d7ba4 * _DAT_0057db50;
  _DAT_006d7c1c =
       DAT_006d7b98 * _DAT_0057db24 +
       DAT_006d7b9c * _DAT_0057db34 + DAT_006d7ba0 * _DAT_0057db44 + _DAT_006d7ba4 * _DAT_0057db54;
  _DAT_006d7c20 =
       DAT_006d7b98 * _DAT_0057db28 +
       DAT_006d7b9c * _DAT_0057db38 + DAT_006d7ba0 * _DAT_0057db48 + _DAT_006d7ba4 * _DAT_0057db58;
  _DAT_006d7c24 =
       DAT_006d7b98 * _DAT_0057db2c +
       DAT_006d7b9c * _DAT_0057db3c + DAT_006d7ba0 * _DAT_0057db4c + _DAT_006d7ba4 * _DAT_0057db5c;
  cVar9 = sub_402840(param_1,&DAT_006d7be8,local_40);
  if ((cVar9 == '\0') && (param_13 != '\0')) {
    if (DAT_00584eb4 != 4) {
      return 1;
    }
    if (DAT_00584eb8 != 1) {
      return 1;
    }
    if (DAT_00584ebc != 1) {
      return 1;
    }
    if (DAT_00584ec0 != 1) {
      return 1;
    }
  }
  sub_41EA70(param_2,param_3,param_4,param_5,&DAT_006d8418);
  _DAT_006d84a0 =
       _DAT_006d8418 * _DAT_006d8400 + _DAT_006d8428 * _DAT_006d8404 + _DAT_006d8438 * _DAT_006d8408
       + _DAT_006d8448;
  _DAT_006d84a4 =
       _DAT_006d841c * _DAT_006d8400 + _DAT_006d842c * _DAT_006d8404 + _DAT_006d843c * _DAT_006d8408
       + _DAT_006d844c;
  _DAT_006d84a8 =
       _DAT_006d8420 * _DAT_006d8400 + _DAT_006d8430 * _DAT_006d8404 + _DAT_006d8440 * _DAT_006d8408
       + _DAT_006d8450;
  sub_41E960(*param_2,param_2[1],param_2[2],&DAT_006d8458);
  if (DAT_006d7c60 != '\0') {
    if (DAT_005865cc == 1) {
      if (DAT_00581160[8] != 0.0) {
        sub_41C000(DAT_00581160[8],&DAT_006d8418,&DAT_006d8458);
      }
      sub_41BDB0(param_2 + 3,local_3c,6);
      local_d8 = *DAT_00581160;
      local_d4 = DAT_00581160[1];
      local_d0 = DAT_00581160[2];
      local_cc = DAT_00581160[3];
    }
    else {
      if (DAT_0058115c[8] != 0.0) {
        sub_41C000(DAT_0058115c[8],&DAT_006d8418,&DAT_006d8458);
      }
      sub_41BDB0(param_2 + 3,local_3c,6);
      local_d8 = *DAT_0058115c;
      local_d4 = DAT_0058115c[1];
      local_d0 = DAT_0058115c[2];
      local_cc = DAT_0058115c[3];
    }
    if ((param_14 != (byte *)0x0) && (param_14[3] != 0)) {
      local_d8 = (float)*param_14 * _DAT_0056e0c8;
      local_d4 = (float)param_14[1] * _DAT_0056e0c8;
      local_d0 = (float)param_14[2] * _DAT_0056e0c8;
    }
  }
  iVar21 = 0;
  local_11c = 0;
  if ((param_8 == '\0') || (param_9 == 0)) {
    puVar26 = *(undefined4 **)(param_1 + 0x70);
  }
  else {
    iVar24 = 0;
    local_134 = 0;
    if (*(short *)(param_1 + 0x84) != 0) {
      do {
        iVar24 = iVar24 + 1;
        puVar26 = (undefined4 *)(iVar21 + *(int *)(param_1 + 0x70));
        puVar17 = (undefined4 *)((int)&DAT_005b53f8 + iVar21);
        for (iVar18 = 6; iVar18 != 0; iVar18 = iVar18 + -1) {
          *puVar17 = *puVar26;
          puVar26 = puVar26 + 1;
          puVar17 = puVar17 + 1;
        }
        iVar21 = iVar21 + 0x18;
        local_134 = iVar24;
      } while (iVar24 < (int)(uint)*(ushort *)(param_1 + 0x84));
    }
    local_110 = 0;
    if (*(short *)(param_1 + 0x86) != 0) {
      iVar21 = 0;
      pfVar16 = (float *)(param_9 + 0x10);
      do {
        if ((param_10 < 0) || ((local_110 != param_11 && (local_110 != param_12)))) {
          iVar24 = 0;
          if (*(short *)(*(int *)(param_1 + 0x88) + iVar21) != 0) {
            iVar18 = local_134 * 0x18;
            do {
              iVar3 = *(int *)(param_1 + 0x70);
              pfVar19 = (float *)(iVar18 + iVar3);
              iVar24 = iVar24 + 1;
              *(float *)((int)&DAT_005b53f8 + iVar18) =
                   *pfVar19 * pfVar16[-4] +
                   pfVar16[4] * *(float *)(iVar18 + 8 + iVar3) +
                   *pfVar16 * *(float *)(iVar18 + 4 + iVar3) + pfVar16[8];
              *(float *)((int)&DAT_005b53fc + iVar18) =
                   pfVar16[5] * pfVar19[2] + pfVar16[-3] * *pfVar19 + pfVar16[1] * pfVar19[1] +
                   pfVar16[9];
              *(float *)((int)&DAT_005b5400 + iVar18) =
                   pfVar16[6] * pfVar19[2] + pfVar16[-2] * *pfVar19 + pfVar16[2] * pfVar19[1] +
                   pfVar16[10];
              iVar3 = *(int *)(param_1 + 0x70);
              pfVar19 = (float *)(iVar18 + 0xc + iVar3);
              *(float *)(iVar18 + 0x5b5404) =
                   pfVar16[4] * pfVar19[2] +
                   *pfVar16 * *(float *)(iVar18 + 0x10 + iVar3) +
                   pfVar16[-4] * *(float *)(iVar18 + 0xc + iVar3);
              *(float *)(iVar18 + 0x5b5408) =
                   pfVar16[-3] * *pfVar19 + pfVar16[5] * pfVar19[2] + pfVar16[1] * pfVar19[1];
              *(float *)(iVar18 + 0x5b540c) =
                   pfVar19[2] * pfVar16[6] + pfVar16[2] * pfVar19[1] + pfVar16[-2] * *pfVar19;
              local_134 = local_134 + 1;
              iVar18 = iVar18 + 0x18;
            } while (iVar24 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x88) + iVar21));
          }
        }
        else {
          pfVar19 = pfVar16 + -4;
          pfVar28 = local_98;
          for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
            *pfVar28 = *pfVar19;
            pfVar19 = pfVar19 + 1;
            pfVar28 = pfVar28 + 1;
          }
          local_78 = local_78 * *(float *)(&DAT_00572ac0 + param_10 * 4);
          local_74 = local_74 * *(float *)(&DAT_00572ac0 + param_10 * 4);
          local_70 = local_70 * *(float *)(&DAT_00572ac0 + param_10 * 4);
          iVar24 = 0;
          if (*(short *)(*(int *)(param_1 + 0x88) + iVar21) != 0) {
            iVar18 = local_134 * 0x18;
            do {
              iVar3 = *(int *)(param_1 + 0x70);
              pfVar19 = (float *)(iVar18 + iVar3);
              iVar24 = iVar24 + 1;
              *(float *)((int)&DAT_005b53f8 + iVar18) =
                   local_88 * pfVar19[1] +
                   local_78 * *(float *)(iVar18 + 8 + iVar3) +
                   local_98[0] * *(float *)(iVar18 + iVar3) + local_68;
              *(float *)((int)&DAT_005b53fc + iVar18) =
                   local_74 * pfVar19[2] + local_84 * pfVar19[1] + local_98[1] * *pfVar19 + local_64
              ;
              *(float *)((int)&DAT_005b5400 + iVar18) =
                   local_70 * pfVar19[2] + local_80 * pfVar19[1] + local_98[2] * *pfVar19 + local_60
              ;
              iVar3 = *(int *)(param_1 + 0x70);
              pfVar19 = (float *)(iVar18 + 0xc + iVar3);
              *(float *)(iVar18 + 0x5b5404) =
                   local_78 * pfVar19[2] +
                   local_98[0] * *(float *)(iVar18 + 0xc + iVar3) +
                   local_88 * *(float *)(iVar18 + 0x10 + iVar3);
              *(float *)(iVar18 + 0x5b5408) =
                   local_84 * pfVar19[1] + local_98[1] * *pfVar19 + local_74 * pfVar19[2];
              *(float *)(iVar18 + 0x5b540c) =
                   local_80 * pfVar19[1] + local_98[2] * *pfVar19 + local_70 * pfVar19[2];
              local_134 = local_134 + 1;
              iVar18 = iVar18 + 0x18;
            } while (iVar24 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x88) + iVar21));
          }
        }
        local_110 = local_110 + 1;
        pfVar16 = pfVar16 + 0x10;
        iVar21 = iVar21 + 2;
      } while ((int)local_110 < (int)(uint)*(ushort *)(param_1 + 0x86));
    }
    puVar26 = &DAT_005b53f8;
  }
  if ((param_7 == '\0') && (DAT_006d7c60 != '\0')) {
    local_134 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      puVar25 = &DAT_005865f0;
      pfVar19 = (float *)&DAT_0058b0fc;
      pfVar16 = (float *)(puVar26 + 1);
      do {
        local_e8 = local_d8;
        local_e4 = local_d4;
        local_e0 = local_d0;
        puVar17 = local_3c;
        if (&stack0x00000000 != (undefined1 *)0x3c) {
          do {
            sub_41BA10(*puVar17,pfVar16 + -1,&local_e8);
            puVar17 = (undefined4 *)puVar17[1];
          } while (puVar17 != (undefined4 *)0x0);
        }
        uVar12 = __ftol();
        uVar13 = __ftol();
        uVar14 = __ftol();
        fVar15 = _DAT_006d7c08;
        *puVar25 = ((uVar12 | 0xffffff00) << 8 | uVar13) << 8 | uVar14;
        pfVar28 = pfVar19 + -3;
        *pfVar28 = _DAT_006d7be8 * pfVar16[-1] + _DAT_006d7bf8 * *pfVar16 + fVar15 * pfVar16[1] +
                   _DAT_006d7c18;
        pfVar19[-2] = _DAT_006d7bec * pfVar16[-1] +
                      _DAT_006d7bfc * *pfVar16 + _DAT_006d7c0c * pfVar16[1] + _DAT_006d7c1c;
        pfVar19[-1] = _DAT_006d7c00 * *pfVar16 +
                      _DAT_006d7bf0 * pfVar16[-1] + _DAT_006d7c10 * pfVar16[1] + _DAT_006d7c20;
        *pfVar19 = _DAT_006d7c04 * *pfVar16 +
                   _DAT_006d7bf4 * pfVar16[-1] + _DAT_006d7c14 * pfVar16[1] + _DAT_006d7c24;
        fVar15 = (float)sub_401080(pfVar28);
        pfVar19[5] = fVar15;
        if (fVar15 == 0.0) {
          fVar15 = _DAT_0056e008 / *pfVar19;
          pfVar19[1] = (*pfVar28 * fVar15 + (float)_DAT_0056e038) * _DAT_00583388;
          pfVar19[2] = ((float)_DAT_0056e038 - pfVar19[-2] * fVar15) * _DAT_0058338c;
          pfVar19[3] = ((float)_DAT_0056e038 - pfVar19[-1] * fVar15) * (float)_DAT_0056e030;
          pfVar19[4] = fVar15;
        }
        local_134 = local_134 + 1;
        puVar25 = puVar25 + 1;
        pfVar16 = pfVar16 + 6;
        pfVar19 = pfVar19 + 9;
      } while (local_134 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  else {
    local_134 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      pfVar19 = (float *)&DAT_0058b0fc;
      pfVar16 = (float *)(puVar26 + 1);
      do {
        pfVar28 = pfVar19 + -3;
        *pfVar28 = _DAT_006d7be8 * pfVar16[-1] +
                   _DAT_006d7bf8 * *pfVar16 + _DAT_006d7c08 * pfVar16[1] + _DAT_006d7c18;
        pfVar19[-2] = _DAT_006d7bec * pfVar16[-1] +
                      _DAT_006d7bfc * *pfVar16 + _DAT_006d7c0c * pfVar16[1] + _DAT_006d7c1c;
        pfVar19[-1] = _DAT_006d7c00 * *pfVar16 +
                      _DAT_006d7bf0 * pfVar16[-1] + _DAT_006d7c10 * pfVar16[1] + _DAT_006d7c20;
        *pfVar19 = _DAT_006d7c04 * *pfVar16 +
                   _DAT_006d7bf4 * pfVar16[-1] + _DAT_006d7c14 * pfVar16[1] + _DAT_006d7c24;
        fVar15 = (float)sub_401080(pfVar28);
        pfVar19[5] = fVar15;
        if (fVar15 == 0.0) {
          fVar15 = _DAT_0056e008 / *pfVar19;
          pfVar19[1] = (*pfVar28 * fVar15 + (float)_DAT_0056e038) * _DAT_00583388;
          pfVar19[2] = ((float)_DAT_0056e038 - pfVar19[-2] * fVar15) * _DAT_0058338c;
          pfVar19[3] = ((float)_DAT_0056e038 - pfVar19[-1] * fVar15) * (float)_DAT_0056e030;
          pfVar19[4] = fVar15;
        }
        local_134 = local_134 + 1;
        pfVar16 = pfVar16 + 6;
        pfVar19 = pfVar19 + 9;
      } while (local_134 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  local_134 = 0;
  if (*(short *)(param_1 + 0x6e) == 0) {
    return 1;
  }
  do {
    puVar1 = (ushort *)(*(int *)(param_1 + 0x74) + local_134 * 0x1c);
    if (((*(byte *)(*(int *)(param_1 + 0x74) + local_134 * 0x1c) & 8) != 0) ||
       ((local_122 != 0 && ((byte)local_fc[1] != *(byte *)(*(int *)(puVar1 + 4) + 2))))) {
      if (local_11c != 0) {
        uVar8 = *local_fc;
        uVar12 = local_110 & 0xff;
        uVar13 = _DAT_006d7c60 & 0xff;
        if (0 < local_11c) {
          if (DAT_005833e1 == '\0') {
            if (local_128 == 0) {
              if (DAT_006d7c58 != 1) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                DAT_006d7c58 = 1;
              }
            }
            else {
              if ((local_120 != 0) && (*(int *)(local_128 + 0x14) != local_120)) {
                (**(code **)(**(int **)(local_128 + 0xc) + 0x7c))
                          (*(int **)(local_128 + 0xc),*(undefined4 *)(local_120 + 0x10));
                *(int *)(local_128 + 0x14) = local_120;
              }
              if (DAT_006d7c54 != *(int *)(local_128 + 0x10)) {
                (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_128 + 0x10));
                DAT_006d7c54 = *(int *)(local_128 + 0x10);
              }
              if ((uVar13 == 0) || (iVar21 = 4, DAT_005833f0 == '\0')) {
                iVar21 = 2;
              }
              if (DAT_006d7c58 != iVar21) {
                if ((uVar13 == 0) || (uVar23 = 4, DAT_005833f0 == '\0')) {
                  uVar23 = 2;
                }
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar23);
                if ((uVar13 == 0) || (DAT_005833f0 == '\0')) {
                  DAT_006d7c58 = 2;
                }
                else {
                  DAT_006d7c58 = 4;
                }
              }
            }
            if ((local_100 != 0) || (iVar21 = 2, DAT_005833f2 == '\0')) {
              iVar21 = 1;
            }
            if (DAT_006d7c34 != iVar21) {
              if ((local_100 != 0) || (uVar23 = 2, DAT_005833f2 == '\0')) {
                uVar23 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,uVar23);
              if ((local_100 != 0) || (DAT_006d7c34 = 2, DAT_005833f2 == '\0')) {
                DAT_006d7c34 = 1;
              }
            }
            if ((_DAT_006d7c38 & 0xff) != uVar12) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar12);
              _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_110);
            }
            if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_10c & 2) != 0)) {
              cVar9 = '\0';
            }
            else {
              cVar9 = '\x01';
            }
            if (DAT_006d7c4e != cVar9) {
              if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_10c & 2) != 0)) {
                uVar23 = 0;
              }
              else {
                uVar23 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar23);
              if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                 (DAT_006d7c4e = '\x01', (local_10c & 2) != 0)) {
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
            if (((uVar8 & 2) == 0) || (DAT_006d7c70 == '\0')) {
              uVar12 = 0;
            }
            else {
              uVar12 = 1;
            }
            if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar12) {
              if (((uVar8 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                uVar23 = 0;
              }
              else {
                uVar23 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar23);
              if ((uVar8 & 2) != 0) {
                _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                if (DAT_006d7c70 != '\0') goto LAB_00420c36;
              }
              _DAT_006d7c38 = (uint3)_DAT_006d7c38;
            }
LAB_00420c36:
            if (DAT_006d7c50 != 0) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
              DAT_006d7c50 = 0;
            }
            switch(local_108) {
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
              iVar21 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              if (DAT_006d7c40 != iVar21) {
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar21);
                DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              }
              iVar21 = 6;
              if (DAT_006d7c44 != 6) {
LAB_00420e71:
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,iVar21);
                DAT_006d7c44 = iVar21;
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
              iVar21 = 2;
              if (DAT_006d7c44 != 2) goto LAB_00420e71;
            }
            switch(local_10c) {
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
            (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_11c,0x1c);
          }
          else {
            if (local_128 == 0) {
              uVar23 = 0;
            }
            else {
              uVar23 = *(undefined4 *)(local_128 + 0x1c);
            }
            pcVar20 = sub_4C6CD0;
            if (DAT_00583380 == '\0') {
              pcVar20 = sub_442BD0;
            }
            (*pcVar20)(DAT_0058331c,DAT_005832f0,uVar23,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8
                       ,local_11c,0,local_120,
                       (local_108 << 2 | local_10c) << 5 |
                       (-(uint)(uVar12 != 0) & 0xfffffe00) + 0x200 | (uint)(uVar13 != 0) |
                       -(uint)(local_100 != 0) & 2 | -(uint)((uVar8 & 2) != 0) & 4);
          }
        }
        local_11c = 0;
      }
      local_fc = *(ushort **)(puVar1 + 4);
      uVar8 = *local_fc;
      uVar12 = uVar8 >> 0xc & 7;
      if ((uVar8 & 1) == 0) {
        local_c8 = *(uint *)(&DAT_00574280 + uVar12 * 4);
        local_110 = (uint)(DAT_006d7c61 == '\0');
        if ((byte)local_fc[1] == 0xff) {
          local_128 = 0;
        }
        else {
          local_128 = (char)(byte)local_fc[1] * 0x20 + DAT_0058114c;
        }
        if (*(byte *)((int)local_fc + 3) == 0xff) {
          local_120 = 0;
        }
        else {
          local_120 = DAT_00581144 + (char)*(byte *)((int)local_fc + 3) * 0x1c;
        }
        iVar21 = uVar12 + (uVar8 >> 8 & 7) * 5;
        local_108 = (&DAT_00573ef8)[iVar21 * 3];
        local_10c = (&DAT_00573efc)[iVar21 * 3];
        local_c4 = (&DAT_005740a0)[iVar21 * 3];
        local_bc = (&DAT_005740a4)[iVar21 * 3];
        local_129 = *(char *)(&DAT_00573f00 + iVar21 * 3);
        local_121 = *(char *)((int)&DAT_00573f00 + iVar21 * 0xc + 1);
      }
      else {
        local_c0 = (uint)(byte)local_fc[2];
        local_110 = 0;
        local_f4 = (uint)(byte)local_fc[4];
        local_ec = (uint)(byte)local_fc[6];
        local_c8 = (uint)(byte)local_fc[8];
        local_128 = 0;
        local_120 = 0;
        local_108 = (&DAT_00573eb8)[uVar12 * 3];
        local_10c = (&DAT_00573ebc)[uVar12 * 3];
        local_c4 = (&DAT_00574060)[uVar12 * 3];
        local_bc = (&DAT_00574064)[uVar12 * 3];
        local_129 = *(char *)(&DAT_00573ec0 + uVar12 * 3);
        local_121 = *(char *)((int)&DAT_00573ec0 + uVar12 * 0xc + 1);
      }
      local_100 = DAT_006d7c60 == '\0';
      local_122 = (byte)uVar8 >> 5 & 1;
    }
    uVar14 = (uint)puVar1[2];
    uVar12 = (uint)puVar1[1];
    uVar13 = (uint)puVar1[3];
    if (((&DAT_0058b110)[uVar13 * 9] & (&DAT_0058b110)[uVar12 * 9] & (&DAT_0058b110)[uVar14 * 9]) ==
        0) {
      if (param_8 != '\0') {
        pfVar16 = (float *)(puVar26 + uVar12 * 6);
        local_a4 = (float)puVar26[uVar14 * 6] - *pfVar16;
        local_a0 = (float)puVar26[uVar14 * 6 + 1] - pfVar16[1];
        local_b4 = local_a0 * ((float)puVar26[uVar13 * 6 + 2] - pfVar16[2]) -
                   ((float)puVar26[uVar14 * 6 + 2] - pfVar16[2]) *
                   ((float)puVar26[uVar13 * 6 + 1] - pfVar16[1]);
        local_b0 = ((float)puVar26[uVar14 * 6 + 2] - pfVar16[2]) *
                   ((float)puVar26[uVar13 * 6] - *pfVar16) -
                   ((float)puVar26[uVar13 * 6 + 2] - pfVar16[2]) * local_a4;
        fVar15 = ((float)puVar26[uVar13 * 6 + 1] - pfVar16[1]) * local_a4 -
                 local_a0 * ((float)puVar26[uVar13 * 6] - *pfVar16);
        fVar5 = SQRT(local_b0 * local_b0 + fVar15 * fVar15 + local_b4 * local_b4);
        pfVar16 = (float *)sub_41E790(local_b4 / fVar5,local_b0 / fVar5,fVar15 / fVar5);
        *(float *)(puVar1 + 6) = *pfVar16;
        *(float *)(puVar1 + 8) = pfVar16[1];
        uVar12 = (uint)puVar1[1];
        *(float *)(puVar1 + 10) = pfVar16[2];
        *(float *)(puVar1 + 0xc) =
             (float)puVar26[uVar12 * 6] * *(float *)(puVar1 + 6) +
             (float)puVar26[uVar12 * 6 + 1] * *(float *)(puVar1 + 8) +
             (float)puVar26[uVar12 * 6 + 2] * *(float *)(puVar1 + 10);
      }
      if ((_DAT_0056e00c <=
           (_DAT_006d84a0 * *(float *)(puVar1 + 6) +
           _DAT_006d84a4 * *(float *)(puVar1 + 8) + _DAT_006d84a8 * *(float *)(puVar1 + 10)) -
           *(float *)(puVar1 + 0xc)) || ((*puVar1 & 0x400) != 0)) {
        local_130 = (float)(&DAT_0058b0fc)[uVar12 * 9];
        uVar12 = (&DAT_0058b110)[uVar12 * 9] | (&DAT_0058b110)[(uint)puVar1[2] * 9] |
                 (&DAT_0058b110)[(uint)puVar1[3] * 9];
        bVar29 = uVar12 != 0;
        if (local_130 < (float)(&DAT_0058b0fc)[(uint)puVar1[2] * 9]) {
          local_130 = (float)(&DAT_0058b0fc)[(uint)puVar1[2] * 9];
        }
        if (local_130 < (float)(&DAT_0058b0fc)[(uint)puVar1[3] * 9]) {
          local_130 = (float)(&DAT_0058b0fc)[(uint)puVar1[3] * 9];
        }
        if ((local_130 <= _DAT_0057f8f8) || (DAT_006d7c6a == '\0')) {
          bVar7 = false;
        }
        else {
          bVar7 = true;
        }
        bVar4 = param_6 < _DAT_0056e008;
        uVar13 = local_108;
        if (bVar4) {
          uVar13 = local_c4;
        }
        if (DAT_005833e4._1_1_ == '\0') {
LAB_0042131d:
          iVar21 = -1;
          local_114 = -1;
        }
        else if ((uVar13 == 0) && (((*local_fc & 2) == 0 || (DAT_00573d36 == '\0')))) {
          if ((!bVar7) || ((DAT_005f6ee8 & 2) == 0)) goto LAB_0042131d;
          iVar21 = 2;
          local_114 = 2;
          iVar24 = __ftol();
          if (iVar24 < 0) {
LAB_004213bc:
            local_104 = 0x7ff;
          }
          else if (iVar24 < 0x800) {
            local_104 = 0x7ff - iVar24;
          }
          else {
            local_104 = 0;
          }
        }
        else {
          iVar21 = 0;
          local_114 = 0;
          local_104 = __ftol();
          if (local_104 < 0) {
            local_104 = 0;
          }
          else if (0x7ff < local_104) goto LAB_004213bc;
        }
        local_130 = 4.2039e-45;
        if (bVar29) {
          iVar24 = 0;
          for (uVar13 = uVar12; uVar13 != 0; uVar13 = (int)uVar13 >> 1) {
            if ((uVar13 & 1) != 0) {
              iVar24 = iVar24 + 1;
            }
          }
          local_130 = (float)(iVar24 * 3 + 3);
        }
        if (iVar21 == -1) {
          puVar17 = (undefined4 *)(&DAT_005d15f8 + local_11c * 0x20);
        }
        else {
          puVar17 = (undefined4 *)sub_41ED90((int)local_130 << 5);
          if (puVar17 == (undefined4 *)0x0) goto LAB_00422048;
        }
        puVar27 = puVar17;
        if (bVar29) {
          puVar27 = (undefined4 *)(&DAT_005d15f8 + ((int)local_130 + local_11c) * 0x20);
          local_b8 = puVar17;
        }
        if ((param_7 != '\0') && (DAT_006d7c60 != '\0')) {
          puVar17 = local_3c;
          uVar13 = (uint)puVar1[1];
          local_58 = puVar26[uVar13 * 6];
          local_54 = puVar26[uVar13 * 6 + 1];
          local_50 = puVar26[uVar13 * 6 + 2];
          local_4c = *(undefined4 *)(puVar1 + 6);
          local_48 = *(undefined4 *)(puVar1 + 8);
          local_44 = *(undefined4 *)(puVar1 + 10);
          local_e8 = local_d8;
          local_e4 = local_d4;
          local_e0 = local_d0;
          if (&stack0x00000000 != (undefined1 *)0x3c) {
            do {
              sub_41BA10(*puVar17,&local_58,&local_e8);
              puVar17 = (undefined4 *)puVar17[1];
            } while (puVar17 != (undefined4 *)0x0);
          }
          uVar13 = __ftol();
          uVar14 = __ftol();
          local_a8 = __ftol();
          local_a8 = ((uVar13 | 0xffffff00) << 8 | uVar14) << 8 | local_a8;
        }
        if (bVar29) {
          uVar13 = (uint)puVar1[1];
          uVar14 = (uint)puVar1[3];
          uVar22 = (uint)puVar1[2];
          *puVar27 = (&DAT_0058b0f0)[uVar13 * 9];
          puVar27[1] = (&DAT_0058b0f4)[uVar13 * 9];
          puVar27[2] = (&DAT_0058b0f8)[uVar13 * 9];
          puVar27[3] = (&DAT_0058b0fc)[uVar13 * 9];
          puVar27[8] = (&DAT_0058b0f0)[uVar22 * 9];
          puVar27[9] = (&DAT_0058b0f4)[uVar22 * 9];
          puVar27[10] = (&DAT_0058b0f8)[uVar22 * 9];
          puVar27[0xb] = (&DAT_0058b0fc)[uVar22 * 9];
          puVar27[0x10] = (&DAT_0058b0f0)[uVar14 * 9];
          puVar27[0x11] = (&DAT_0058b0f4)[uVar14 * 9];
          puVar27[0x12] = (&DAT_0058b0f8)[uVar14 * 9];
          uVar23 = (&DAT_0058b0fc)[uVar14 * 9];
        }
        else {
          uVar13 = (uint)puVar1[1];
          uVar14 = (uint)puVar1[3];
          uVar22 = (uint)puVar1[2];
          *puVar27 = (&DAT_0058b100)[uVar13 * 9];
          puVar27[1] = (&DAT_0058b104)[uVar13 * 9];
          puVar27[2] = (&DAT_0058b108)[uVar13 * 9];
          puVar27[3] = (&DAT_0058b10c)[uVar13 * 9];
          puVar27[8] = (&DAT_0058b100)[uVar22 * 9];
          puVar27[9] = (&DAT_0058b104)[uVar22 * 9];
          puVar27[10] = (&DAT_0058b108)[uVar22 * 9];
          puVar27[0xb] = (&DAT_0058b10c)[uVar22 * 9];
          puVar27[0x10] = (&DAT_0058b100)[uVar14 * 9];
          puVar27[0x11] = (&DAT_0058b104)[uVar14 * 9];
          puVar27[0x12] = (&DAT_0058b108)[uVar14 * 9];
          uVar23 = (&DAT_0058b10c)[uVar14 * 9];
        }
        puVar27[0x13] = uVar23;
        if ((**(byte **)(puVar1 + 4) & 1) == 0) {
          if (((*puVar1 & 0x4000) == 0) && (DAT_006d7c60 != '\0')) {
            if (param_7 != '\0') {
              puVar27[4] = local_a8;
              puVar27[5] = 0;
              puVar27[0xc] = local_a8;
              puVar27[0xd] = 0;
              puVar27[0x14] = local_a8;
              goto LAB_004218dd;
            }
            uVar8 = puVar1[3];
            uVar2 = puVar1[2];
            puVar27[4] = (&DAT_005865f0)[puVar1[1]];
            puVar27[5] = 0;
            puVar27[0xc] = (&DAT_005865f0)[uVar2];
            puVar27[0xd] = 0;
            uVar23 = (&DAT_005865f0)[uVar8];
            puVar27[0x15] = 0;
            puVar27[0x14] = uVar23;
          }
          else {
            puVar27[4] = 0xffffff;
            puVar27[5] = 0;
            puVar27[0xc] = 0xffffff;
            puVar27[0xd] = 0;
            puVar27[0x14] = 0xffffff;
LAB_004218dd:
            puVar27[0x15] = 0;
          }
          uVar8 = *puVar1;
          bVar10 = (byte)uVar8;
          if ((uVar8 & 0x800) == 0) {
            iVar21 = *(int *)(puVar1 + 4);
            bVar10 = bVar10 >> 5 & 1;
            if (bVar10 == 0) {
              uVar23 = *(undefined4 *)(iVar21 + 8);
            }
            else {
              uVar23 = *(undefined4 *)(iVar21 + 4);
            }
            puVar27[6] = uVar23;
            puVar27[7] = *(undefined4 *)(iVar21 + 0x10);
            if (bVar10 == 0) {
              uVar23 = *(undefined4 *)(iVar21 + 4);
            }
            else {
              uVar23 = *(undefined4 *)(iVar21 + 8);
            }
            puVar27[0xe] = uVar23;
            puVar27[0xf] = *(undefined4 *)(iVar21 + 0x10);
            if (bVar10 == 0) goto LAB_00421972;
LAB_00421a08:
            uVar23 = *(undefined4 *)(iVar21 + 4);
LAB_00421975:
            puVar27[0x16] = uVar23;
            uVar23 = *(undefined4 *)(iVar21 + 0xc);
          }
          else {
            if ((uVar8 & 0x10) == 0) {
              iVar21 = *(int *)(puVar1 + 4);
              bVar10 = bVar10 >> 5 & 1;
              if (bVar10 == 0) {
                uVar23 = *(undefined4 *)(iVar21 + 8);
              }
              else {
                uVar23 = *(undefined4 *)(iVar21 + 4);
              }
              puVar27[6] = uVar23;
              puVar27[7] = *(undefined4 *)(iVar21 + 0x10);
              if (bVar10 == 0) {
                uVar23 = *(undefined4 *)(iVar21 + 4);
              }
              else {
                uVar23 = *(undefined4 *)(iVar21 + 8);
              }
              puVar27[0xe] = uVar23;
              puVar27[0xf] = *(undefined4 *)(iVar21 + 0x10);
              if (bVar10 == 0) goto LAB_00421a08;
LAB_00421972:
              uVar23 = *(undefined4 *)(iVar21 + 8);
              goto LAB_00421975;
            }
            iVar21 = *(int *)(puVar1 + 4);
            bVar10 = bVar10 >> 5 & 1;
            if (bVar10 == 0) {
              uVar23 = *(undefined4 *)(iVar21 + 4);
            }
            else {
              uVar23 = *(undefined4 *)(iVar21 + 8);
            }
            puVar27[6] = uVar23;
            puVar27[7] = *(undefined4 *)(iVar21 + 0xc);
            if (bVar10 == 0) {
              uVar23 = *(undefined4 *)(iVar21 + 8);
            }
            else {
              uVar23 = *(undefined4 *)(iVar21 + 4);
            }
            puVar27[0xe] = uVar23;
            puVar27[0xf] = *(undefined4 *)(iVar21 + 0xc);
            if (bVar10 == 0) {
              puVar27[0x16] = *(undefined4 *)(iVar21 + 8);
              uVar23 = *(undefined4 *)(iVar21 + 0x10);
            }
            else {
              puVar27[0x16] = *(undefined4 *)(iVar21 + 4);
              uVar23 = *(undefined4 *)(iVar21 + 0x10);
            }
          }
          puVar27[0x17] = uVar23;
        }
        else if (((*puVar1 & 0x4000) == 0) && (DAT_006d7c60 != '\0')) {
          if (param_7 == '\0') {
            uVar8 = puVar1[2];
            uVar2 = puVar1[3];
            uVar13 = (&DAT_005865f0)[puVar1[1]];
            puVar27[5] = 0;
            uVar14 = uVar13 >> 8;
            puVar27[4] = (uint)CONCAT11((char)((uVar14 & 0xff) * local_f4 >> 8),
                                        (char)((uVar13 & 0xff) * local_ec >> 8)) |
                         (uVar14 & 0xff00) * local_c0 & 0xff0000;
            uVar13 = (&DAT_005865f0)[uVar8];
            puVar27[0xd] = 0;
            uVar14 = uVar13 >> 8;
            puVar27[0xc] = (uint)CONCAT11((char)((uVar14 & 0xff) * local_f4 >> 8),
                                          (char)((uVar13 & 0xff) * local_ec >> 8)) |
                           (uVar14 & 0xff00) * local_c0 & 0xff0000;
            uVar13 = (&DAT_005865f0)[uVar2];
            uVar14 = uVar13 >> 8;
            puVar27[0x15] = 0;
            puVar27[0x14] =
                 (uint)CONCAT11((char)((uVar14 & 0xff) * local_f4 >> 8),
                                (char)((uVar13 & 0xff) * local_ec >> 8)) |
                 (uVar14 & 0xff00) * local_c0 & 0xff0000;
          }
          else {
            uVar13 = (uint)CONCAT11((char)((local_a8 >> 8 & 0xff) * local_f4 >> 8),
                                    (char)((local_a8 & 0xff) * local_ec >> 8)) |
                     (local_a8 >> 8 & 0xff00) * local_c0 & 0xff0000;
            puVar27[4] = uVar13;
            puVar27[5] = 0;
            puVar27[0xc] = uVar13;
            puVar27[0xd] = 0;
            puVar27[0x14] = uVar13;
            puVar27[0x15] = 0;
          }
        }
        else {
          uVar13 = (local_c0 << 8 | local_f4) << 8 | local_ec;
          puVar27[4] = uVar13;
          puVar27[5] = 0;
          puVar27[0xc] = uVar13;
          puVar27[0xd] = 0;
          puVar27[0x14] = uVar13;
          puVar27[0x15] = 0;
        }
        if ((bVar7) && (DAT_006d7c6b != '\0')) {
          iVar21 = __ftol();
          uVar13 = (uint)puVar27[4] >> 8;
          puVar27[4] = (puVar27[4] & 0xff) * iVar21 >> 8 & 0xff |
                       (uVar13 & 0xff00) * iVar21 & 0xff0000 | (uVar13 & 0xff) * iVar21 & 0xff00;
          iVar21 = __ftol();
          uVar13 = (uint)puVar27[0xc] >> 8;
          puVar27[0xc] = (puVar27[0xc] & 0xff) * iVar21 >> 8 & 0xff |
                         (uVar13 & 0xff00) * iVar21 & 0xff0000 | (uVar13 & 0xff) * iVar21 & 0xff00;
          iVar21 = __ftol();
          uVar13 = (uint)puVar27[0x14] >> 8;
          puVar27[0x14] =
               (puVar27[0x14] & 0xff) * iVar21 >> 8 & 0xff | (uVar13 & 0xff00) * iVar21 & 0xff0000 |
               (uVar13 & 0xff) * iVar21 & 0xff00;
        }
        if (local_129 == '\0') {
          if (bVar4) {
            uVar11 = __ftol();
            *(undefined1 *)((int)puVar27 + 0x13) = uVar11;
            *(undefined1 *)((int)puVar27 + 0x33) = uVar11;
            *(undefined1 *)((int)puVar27 + 0x53) = uVar11;
          }
          else {
            *(undefined1 *)((int)puVar27 + 0x13) = 0xff;
            *(undefined1 *)((int)puVar27 + 0x33) = 0xff;
            *(undefined1 *)((int)puVar27 + 0x53) = 0xff;
          }
        }
        else if (bVar4) {
          uVar11 = __ftol();
          *(undefined1 *)((int)puVar27 + 0x13) = uVar11;
          *(undefined1 *)((int)puVar27 + 0x33) = uVar11;
          *(undefined1 *)((int)puVar27 + 0x53) = uVar11;
        }
        else {
          *(undefined1 *)((int)puVar27 + 0x13) = (undefined1)local_c8;
          *(undefined1 *)((int)puVar27 + 0x33) = (undefined1)local_c8;
          *(undefined1 *)((int)puVar27 + 0x53) = (undefined1)local_c8;
        }
        if ((bVar7) && (DAT_006d7c6c != '\0')) {
          iVar21 = __ftol();
          *(char *)((int)puVar27 + 0x13) =
               (char)(iVar21 * (uint)*(byte *)((int)puVar27 + 0x13) >> 8);
          iVar21 = __ftol();
          *(char *)((int)puVar27 + 0x33) =
               (char)(iVar21 * (uint)*(byte *)((int)puVar27 + 0x33) >> 8);
          iVar21 = __ftol();
          *(char *)((int)puVar27 + 0x53) =
               (char)(iVar21 * (uint)*(byte *)((int)puVar27 + 0x53) >> 8);
        }
        puVar17 = local_b8;
        if ((DAT_006d7c6f != '\0') &&
           (((bVar4 || (local_129 != '\0')) || ((bVar7 && (DAT_006d7c6c != '\0')))))) {
          uVar13 = puVar27[4];
          uVar22 = (uint)*(byte *)((int)puVar27 + 0x13);
          uVar14 = puVar27[0xc];
          puVar27[4] = (uVar13 & 0xff) * uVar22 >> 8 | (uVar13 >> 8 & 0xff00) * uVar22 & 0xff0000 |
                       (uVar13 >> 8 & 0xff) * uVar22 & 0xff00 | uVar13 & 0xff000000;
          uVar22 = (uint)*(byte *)((int)puVar27 + 0x33);
          uVar13 = puVar27[0x14];
          puVar27[0xc] = (uVar14 & 0xff) * uVar22 >> 8 | (uVar14 >> 8 & 0xff00) * uVar22 & 0xff0000
                         | (uVar14 >> 8 & 0xff) * uVar22 & 0xff00 | uVar14 & 0xff000000;
          uVar14 = (uint)*(byte *)((int)puVar27 + 0x53);
          puVar27[0x14] =
               (uVar13 & 0xff) * uVar14 >> 8 | (uVar13 >> 8 & 0xff00) * uVar14 & 0xff0000 |
               (uVar13 >> 8 & 0xff) * uVar14 & 0xff00 | uVar13 & 0xff000000;
        }
        if (bVar29) {
          if (bVar7) {
            local_130 = (float)sub_43A610(local_b8,puVar27,3,uVar12);
          }
          else {
            local_130 = (float)sub_439F20(local_b8,puVar27,3,uVar12);
          }
          puVar27 = puVar17;
          if (local_130 == 0.0) goto LAB_00422048;
        }
        if (local_114 == -1) {
          local_100 = local_100 & !bVar7;
          local_11c = local_11c + (int)local_130;
        }
        else {
          if ((bVar4) || ((bVar7 && (DAT_006d7c6c != '\0')))) {
            local_f8 = local_bc;
            if (!bVar4) goto LAB_00421f19;
LAB_00421f31:
            local_13c = local_c4;
            if (!bVar4) goto LAB_00421f40;
LAB_00421f50:
            bVar10 = 1;
          }
          else {
            local_f8 = local_10c;
LAB_00421f19:
            if ((bVar7) && (DAT_006d7c6c != '\0')) goto LAB_00421f31;
            local_13c = local_108;
LAB_00421f40:
            bVar10 = 0;
            if (local_121 != '\0') goto LAB_00421f50;
          }
          if ((local_100 == 0) || (bVar7)) {
            bVar6 = 0;
          }
          else {
            bVar6 = 1;
          }
          uVar12 = _DAT_006d7c60 & 0xff;
          uVar8 = *local_fc;
          if ((0 < (int)local_130) &&
             (puVar17 = (undefined4 *)sub_41ED90(0x20), puVar17 != (undefined4 *)0x0)) {
            iVar21 = local_114 * 0x800 + local_104;
            *puVar17 = (&DAT_005f6ef8)[iVar21];
            puVar17[2] = local_130;
            puVar17[1] = puVar27;
            puVar17[3] = 0;
            puVar17[4] = 0;
            puVar17[5] = local_128;
            puVar17[6] = local_120;
            puVar17[7] = (local_f8 * 4 | local_13c) << 0xc | -(uint)(uVar12 != 0) & 2 |
                         -(uint)((uVar8 & 2) != 0) & 0x10 | -(uint)bVar6 & 8 | -(uint)bVar10 & 0x40
                         | -(uint)((char)local_110 != '\0') & 4;
            (&DAT_005f6ef8)[iVar21] = puVar17;
          }
        }
      }
    }
LAB_00422048:
    local_134 = local_134 + 1;
  } while (local_134 < (int)(uint)*(ushort *)(param_1 + 0x6e));
  if (local_11c == 0) {
    return 1;
  }
  uVar13 = local_110 & 0xff;
  uVar8 = *local_fc;
  uVar12 = _DAT_006d7c60 & 0xff;
  if (local_11c < 1) {
    return 1;
  }
  if (DAT_005833e1 != '\0') {
    if (local_128 == 0) {
      uVar23 = 0;
    }
    else {
      uVar23 = *(undefined4 *)(local_128 + 0x1c);
    }
    pcVar20 = sub_4C6CD0;
    if (DAT_00583380 == '\0') {
      pcVar20 = sub_442BD0;
    }
    (*pcVar20)(DAT_0058331c,DAT_005832f0,uVar23,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8,
               local_11c,0,local_120,
               (local_108 * 4 | local_10c) << 5 | (-(uint)(uVar13 != 0) & 0xfffffe00) + 0x200 |
               (uint)(uVar12 != 0) | -(uint)(local_100 != 0) & 2 | -(uint)((uVar8 & 2) != 0) & 4);
    return 1;
  }
  if (local_128 == 0) {
    if (DAT_006d7c58 != 1) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
  }
  else {
    if ((local_120 != 0) && (*(int *)(local_128 + 0x14) != local_120)) {
      (**(code **)(**(int **)(local_128 + 0xc) + 0x7c))
                (*(int **)(local_128 + 0xc),*(undefined4 *)(local_120 + 0x10));
      *(int *)(local_128 + 0x14) = local_120;
    }
    if (DAT_006d7c54 != *(int *)(local_128 + 0x10)) {
      (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_128 + 0x10));
      DAT_006d7c54 = *(int *)(local_128 + 0x10);
    }
    if ((uVar12 == 0) || (iVar21 = 4, DAT_005833f0 == '\0')) {
      iVar21 = 2;
    }
    if (DAT_006d7c58 != iVar21) {
      if ((uVar12 == 0) || (uVar23 = 4, DAT_005833f0 == '\0')) {
        uVar23 = 2;
      }
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar23);
      if ((uVar12 == 0) || (DAT_005833f0 == '\0')) {
        DAT_006d7c58 = 2;
      }
      else {
        DAT_006d7c58 = 4;
      }
    }
  }
  if ((local_100 != 0) || (iVar21 = 2, DAT_005833f2 == '\0')) {
    iVar21 = 1;
  }
  if (DAT_006d7c34 != iVar21) {
    if ((local_100 != 0) || (uVar23 = 2, DAT_005833f2 == '\0')) {
      uVar23 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,uVar23);
    if ((local_100 != 0) || (DAT_006d7c34 = 2, DAT_005833f2 == '\0')) {
      DAT_006d7c34 = 1;
    }
  }
  if ((_DAT_006d7c38 & 0xff) != uVar13) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar13);
    _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_110);
  }
  if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_10c & 2) != 0)) {
    cVar9 = '\0';
  }
  else {
    cVar9 = '\x01';
  }
  if (DAT_006d7c4e != cVar9) {
    if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_10c & 2) != 0)) {
      uVar23 = 0;
    }
    else {
      uVar23 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar23);
    if ((((uVar8 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
       (DAT_006d7c4e = '\x01', (local_10c & 2) != 0)) {
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
  if (((uVar8 & 2) == 0) || (DAT_006d7c70 == '\0')) {
    uVar12 = 0;
  }
  else {
    uVar12 = 1;
  }
  if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar12) {
    if (((uVar8 & 2) == 0) || (DAT_006d7c70 == '\0')) {
      uVar23 = 0;
    }
    else {
      uVar23 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar23);
    if ((uVar8 & 2) != 0) {
      _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
      if (DAT_006d7c70 != '\0') goto LAB_00422400;
    }
    _DAT_006d7c38 = (uint3)_DAT_006d7c38;
  }
LAB_00422400:
  if (DAT_006d7c50 != 0) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
    DAT_006d7c50 = 0;
  }
  switch(local_108) {
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
    iVar21 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
    if (DAT_006d7c40 != iVar21) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar21);
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
  switch(local_10c) {
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
  (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_11c,0x1c);
  return 1;
}

