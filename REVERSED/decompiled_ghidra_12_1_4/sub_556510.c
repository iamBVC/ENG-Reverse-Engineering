/* sub_556510 @ 00556510   8815 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_556510(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  float *pfVar1;
  ushort *puVar2;
  ushort uVar3;
  int iVar4;
  bool bVar5;
  ushort uVar6;
  char cVar7;
  byte bVar8;
  float *pfVar9;
  float fVar10;
  float *pfVar11;
  undefined4 *puVar12;
  code *pcVar13;
  int iVar14;
  uint uVar15;
  undefined4 uVar16;
  uint uVar17;
  uint uVar18;
  float *pfVar19;
  int iVar20;
  undefined4 *puVar21;
  bool bVar22;
  bool bVar23;
  char local_60;
  byte local_5f;
  char local_5d;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  uint local_4c;
  int local_48;
  int local_44;
  ushort *local_40;
  uint local_3c;
  float local_38;
  int local_34;
  byte local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  undefined4 *local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  uint local_4;
  
  local_5f = 0;
  sub_41E730(param_2,param_3,&DAT_006d7b68);
  _DAT_006d7be8 =
       _DAT_0057db50 * _DAT_006d7b74 +
       _DAT_0057db30 * _DAT_006d7b6c + _DAT_0057db40 * _DAT_006d7b70 + _DAT_0057db20 * _DAT_006d7b68
  ;
  _DAT_006d7bec =
       _DAT_0057db54 * _DAT_006d7b74 +
       _DAT_0057db24 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db34 + _DAT_006d7b70 * _DAT_0057db44
  ;
  _DAT_006d7bf0 =
       _DAT_0057db58 * _DAT_006d7b74 +
       _DAT_0057db28 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db38 + _DAT_006d7b70 * _DAT_0057db48
  ;
  _DAT_006d7bf4 =
       _DAT_0057db5c * _DAT_006d7b74 +
       _DAT_0057db2c * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db3c + _DAT_006d7b70 * _DAT_0057db4c
  ;
  _DAT_006d7bf8 =
       _DAT_006d7b84 * _DAT_0057db50 +
       _DAT_0057db20 * _DAT_006d7b78 + _DAT_0057db30 * _DAT_006d7b7c + _DAT_0057db40 * _DAT_006d7b80
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
       _DAT_006d7b94 * _DAT_0057db50 +
       _DAT_0057db20 * _DAT_006d7b88 + _DAT_0057db30 * _DAT_006d7b8c + _DAT_0057db40 * _DAT_006d7b90
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
       _DAT_006d7ba4 * _DAT_0057db50 +
       _DAT_0057db20 * DAT_006d7b98 + _DAT_0057db30 * DAT_006d7b9c + _DAT_0057db40 * DAT_006d7ba0;
  _DAT_006d7c1c =
       DAT_006d7b98 * _DAT_0057db24 +
       DAT_006d7b9c * _DAT_0057db34 + DAT_006d7ba0 * _DAT_0057db44 + _DAT_006d7ba4 * _DAT_0057db54;
  _DAT_006d7c20 =
       DAT_006d7b98 * _DAT_0057db28 +
       DAT_006d7b9c * _DAT_0057db38 + DAT_006d7ba0 * _DAT_0057db48 + _DAT_006d7ba4 * _DAT_0057db58;
  _DAT_006d7c24 =
       DAT_006d7b98 * _DAT_0057db2c +
       DAT_006d7b9c * _DAT_0057db3c + DAT_006d7ba0 * _DAT_0057db4c + _DAT_006d7ba4 * _DAT_0057db5c;
  cVar7 = sub_402840(param_1,&DAT_006d7be8,&local_8);
  if (cVar7 == '\0') {
    return 1;
  }
  bVar22 = local_8 == 0;
  bVar23 = false;
  sub_41E7B0(param_2,param_3,&DAT_006d8418);
  iVar14 = 0;
  local_54 = 0;
  _DAT_006d84a0 =
       _DAT_006d8428 * _DAT_006d8404 + _DAT_006d8438 * _DAT_006d8408 + _DAT_006d8418 * _DAT_006d8400
       + _DAT_006d8448;
  _DAT_006d84a4 =
       _DAT_006d842c * _DAT_006d8404 + _DAT_006d843c * _DAT_006d8408 + _DAT_006d8400 * _DAT_006d841c
       + _DAT_006d844c;
  _DAT_006d84a8 =
       _DAT_006d8430 * _DAT_006d8404 + _DAT_006d8440 * _DAT_006d8408 + _DAT_006d8400 * _DAT_006d8420
       + _DAT_006d8450;
  if (bVar22) {
    iVar20 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      pfVar19 = (float *)&DAT_0058b0fc;
      do {
        iVar4 = *(int *)(param_1 + 0x70);
        pfVar9 = (float *)(iVar4 + 8 + iVar14);
        pfVar1 = (float *)(iVar4 + iVar14);
        pfVar11 = (float *)(iVar4 + iVar14);
        iVar20 = iVar20 + 1;
        iVar14 = iVar14 + 0x18;
        pfVar19[-3] = _DAT_006d7bf8 * pfVar11[1] + _DAT_006d7be8 * *pfVar1 + _DAT_006d7c08 * *pfVar9
                      + _DAT_006d7c18;
        pfVar19[-2] = _DAT_006d7bfc * pfVar11[1] +
                      _DAT_006d7bec * *pfVar11 + _DAT_006d7c0c * pfVar11[2] + _DAT_006d7c1c;
        pfVar19[-1] = _DAT_006d7c00 * pfVar11[1] +
                      _DAT_006d7bf0 * *pfVar11 + _DAT_006d7c10 * pfVar11[2] + _DAT_006d7c20;
        *pfVar19 = _DAT_006d7c04 * pfVar11[1] +
                   _DAT_006d7bf4 * *pfVar11 + _DAT_006d7c14 * pfVar11[2] + _DAT_006d7c24;
        fVar10 = _DAT_0056e008 / *pfVar19;
        pfVar19[1] = (pfVar19[-3] * fVar10 + (float)_DAT_0056e038) * _DAT_00583388;
        pfVar19[2] = ((float)_DAT_0056e038 - pfVar19[-2] * fVar10) * _DAT_0058338c;
        pfVar19[3] = ((float)_DAT_0056e038 - pfVar19[-1] * fVar10) * (float)_DAT_0056e030;
        pfVar19[4] = fVar10;
        pfVar19 = pfVar19 + 9;
      } while (iVar20 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  else {
    local_34 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      iVar14 = 0;
      pfVar19 = (float *)&DAT_0058b0fc;
      do {
        iVar20 = *(int *)(param_1 + 0x70);
        pfVar9 = (float *)(iVar14 + iVar20);
        pfVar1 = pfVar19 + -3;
        *pfVar1 = _DAT_006d7c08 * pfVar9[2] +
                  _DAT_006d7be8 * *(float *)(iVar14 + iVar20) +
                  _DAT_006d7bf8 * *(float *)(iVar14 + 4 + iVar20) + _DAT_006d7c18;
        pfVar19[-2] = _DAT_006d7c0c * pfVar9[2] +
                      _DAT_006d7bec * *pfVar9 + _DAT_006d7bfc * pfVar9[1] + _DAT_006d7c1c;
        pfVar19[-1] = _DAT_006d7c10 * pfVar9[2] +
                      _DAT_006d7bf0 * *pfVar9 + _DAT_006d7c00 * pfVar9[1] + _DAT_006d7c20;
        *pfVar19 = _DAT_006d7c14 * pfVar9[2] + _DAT_006d7bf4 * *pfVar9 + _DAT_006d7c04 * pfVar9[1] +
                   _DAT_006d7c24;
        fVar10 = (float)sub_401080(pfVar1);
        pfVar19[5] = fVar10;
        if (fVar10 == 0.0) {
          fVar10 = _DAT_0056e008 / *pfVar19;
          pfVar19[1] = (*pfVar1 * fVar10 + (float)_DAT_0056e038) * _DAT_00583388;
          pfVar19[2] = ((float)_DAT_0056e038 - pfVar19[-2] * fVar10) * _DAT_0058338c;
          pfVar19[3] = ((float)_DAT_0056e038 - pfVar19[-1] * fVar10) * (float)_DAT_0056e030;
          pfVar19[4] = fVar10;
        }
        local_34 = local_34 + 1;
        iVar14 = iVar14 + 0x18;
        pfVar19 = pfVar19 + 9;
      } while (local_34 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  local_34 = 0;
  if (*(short *)(param_1 + 0x6e) == 0) {
    return 1;
  }
  do {
    puVar2 = (ushort *)(*(int *)(param_1 + 0x74) + local_34 * 0x1c);
    if (((*puVar2 & 8) != 0) ||
       ((local_5f != 0 && ((byte)local_40[1] != *(byte *)(*(int *)(puVar2 + 4) + 2))))) {
      if (local_54 != 0) {
        uVar6 = *local_40;
        uVar17 = local_28 & 0xff;
        uVar18 = _DAT_006d7c60 & 0xff;
        if (0 < local_54) {
          if (DAT_005833e1 == '\0') {
            if (local_5c == 0) {
              if (DAT_006d7c58 != 1) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                DAT_006d7c58 = 1;
              }
            }
            else {
              if ((local_58 != 0) && (*(int *)(local_5c + 0x14) != local_58)) {
                (**(code **)(**(int **)(local_5c + 0xc) + 0x7c))
                          (*(int **)(local_5c + 0xc),*(undefined4 *)(local_58 + 0x10));
                *(int *)(local_5c + 0x14) = local_58;
              }
              if (DAT_006d7c54 != *(int *)(local_5c + 0x10)) {
                (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_5c + 0x10));
                DAT_006d7c54 = *(int *)(local_5c + 0x10);
              }
              if ((uVar18 == 0) || (iVar14 = 4, DAT_005833f0 == '\0')) {
                iVar14 = 2;
              }
              if (DAT_006d7c58 != iVar14) {
                if ((uVar18 == 0) || (uVar16 = 4, DAT_005833f0 == '\0')) {
                  uVar16 = 2;
                }
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar16);
                if ((uVar18 == 0) || (DAT_005833f0 == '\0')) {
                  DAT_006d7c58 = 2;
                }
                else {
                  DAT_006d7c58 = 4;
                }
              }
            }
            if ((local_30 != 0) || (iVar14 = 2, DAT_005833f2 == '\0')) {
              iVar14 = 1;
            }
            if (DAT_006d7c34 != iVar14) {
              if ((local_30 != 0) || (uVar16 = 2, DAT_005833f2 == '\0')) {
                uVar16 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,uVar16);
              if ((local_30 != 0) || (DAT_006d7c34 = 2, DAT_005833f2 == '\0')) {
                DAT_006d7c34 = 1;
              }
            }
            if ((_DAT_006d7c38 & 0xff) != uVar17) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar17);
              _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_28);
            }
            if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
              cVar7 = '\0';
            }
            else {
              cVar7 = '\x01';
            }
            if (DAT_006d7c4e != cVar7) {
              if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
                uVar16 = 0;
              }
              else {
                uVar16 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar16);
              if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                 (DAT_006d7c4e = '\x01', (local_50 & 2) != 0)) {
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
            if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
              uVar17 = 0;
            }
            else {
              uVar17 = 1;
            }
            if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar17) {
              if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                uVar16 = 0;
              }
              else {
                uVar16 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar16);
              if ((uVar6 & 2) != 0) {
                _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                if (DAT_006d7c70 != '\0') goto LAB_00557015;
              }
              _DAT_006d7c38 = (uint3)_DAT_006d7c38;
            }
LAB_00557015:
            if (DAT_006d7c50 != 0) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
              DAT_006d7c50 = 0;
            }
            switch(local_3c) {
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
              iVar14 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              if (DAT_006d7c40 != iVar14) {
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar14);
                DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              }
              iVar14 = 6;
              if (DAT_006d7c44 != 6) {
LAB_00557250:
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,iVar14);
                DAT_006d7c44 = iVar14;
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
              iVar14 = 2;
              if (DAT_006d7c44 != 2) goto LAB_00557250;
            }
            switch(local_50) {
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
            (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_54,0x1c);
          }
          else {
            if (local_5c == 0) {
              uVar16 = 0;
            }
            else {
              uVar16 = *(undefined4 *)(local_5c + 0x1c);
            }
            pcVar13 = sub_4C6CD0;
            if (DAT_00583380 == '\0') {
              pcVar13 = sub_442BD0;
            }
            (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar16,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8
                       ,local_54,0,local_58,
                       (local_3c * 4 | local_50) << 5 | (-(uint)(uVar17 != 0) & 0xfffffe00) + 0x200
                       | (uint)(uVar18 != 0) | -(uint)(local_30 != 0) & 2 |
                       -(uint)((uVar6 & 2) != 0) & 4);
          }
        }
        local_54 = 0;
      }
      local_40 = *(ushort **)(puVar2 + 4);
      uVar6 = *local_40;
      uVar17 = uVar6 >> 0xc & 7;
      if ((uVar6 & 1) == 0) {
        local_14 = *(uint *)(&DAT_00574280 + uVar17 * 4);
        local_28 = (uint)(DAT_006d7c61 == '\0');
        if ((byte)local_40[1] == 0xff) {
          local_5c = 0;
        }
        else {
          local_5c = (char)(byte)local_40[1] * 0x20 + DAT_0058114c;
        }
        if (*(byte *)((int)local_40 + 3) == 0xff) {
          local_58 = 0;
        }
        else {
          local_58 = DAT_00581144 + (char)*(byte *)((int)local_40 + 3) * 0x1c;
        }
        iVar14 = uVar17 + (uVar6 >> 8 & 7) * 5;
        local_50 = (&DAT_00573efc)[iVar14 * 3];
        local_3c = (&DAT_00573ef8)[iVar14 * 3];
        local_10 = (&DAT_005740a4)[iVar14 * 3];
        local_c = (&DAT_005740a0)[iVar14 * 3];
        local_5d = *(char *)((int)&DAT_00573f00 + iVar14 * 0xc + 1);
        local_60 = *(char *)(&DAT_00573f00 + iVar14 * 3);
      }
      else {
        local_18 = (uint)(byte)local_40[2];
        local_28 = 0;
        local_24 = (uint)(byte)local_40[4];
        local_2c = (uint)(byte)local_40[6];
        local_14 = (uint)(byte)local_40[8];
        local_5c = 0;
        local_58 = 0;
        local_3c = (&DAT_00573eb8)[uVar17 * 3];
        local_50 = (&DAT_00573ebc)[uVar17 * 3];
        local_c = (&DAT_00574060)[uVar17 * 3];
        local_10 = (&DAT_00574064)[uVar17 * 3];
        local_60 = *(char *)(&DAT_00573ec0 + uVar17 * 3);
        local_5d = *(char *)((int)&DAT_00573ec0 + uVar17 * 0xc + 1);
      }
      local_30 = DAT_006d7c60 == '\0';
      local_5f = (byte)uVar6 >> 5 & 1;
    }
    if (((bVar22) ||
        (((&DAT_0058b110)[(uint)puVar2[1] * 9] &
         (&DAT_0058b110)[(uint)puVar2[3] * 9] & (&DAT_0058b110)[(uint)puVar2[2] * 9]) == 0)) &&
       ((_DAT_0056e00c <=
         (_DAT_006d84a0 * *(float *)(puVar2 + 6) +
         _DAT_006d84a4 * *(float *)(puVar2 + 8) + _DAT_006d84a8 * *(float *)(puVar2 + 10)) -
         *(float *)(puVar2 + 0xc) || ((*puVar2 & 0x400) != 0)))) {
      if (!bVar22) {
        local_20 = (&DAT_0058b110)[(uint)puVar2[3] * 9] | (&DAT_0058b110)[(uint)puVar2[2] * 9] |
                   (&DAT_0058b110)[(uint)puVar2[1] * 9];
        bVar23 = local_20 != 0;
      }
      local_38 = (float)(&DAT_0058b0fc)[(uint)puVar2[1] * 9];
      if (local_38 < (float)(&DAT_0058b0fc)[(uint)puVar2[2] * 9]) {
        local_38 = (float)(&DAT_0058b0fc)[(uint)puVar2[2] * 9];
      }
      if (local_38 < (float)(&DAT_0058b0fc)[(uint)puVar2[3] * 9]) {
        local_38 = (float)(&DAT_0058b0fc)[(uint)puVar2[3] * 9];
      }
      if ((local_38 <= _DAT_0057f8f8) || (DAT_006d7c6a == '\0')) {
        bVar5 = false;
      }
      else {
        bVar5 = true;
      }
      if (DAT_005833e4._1_1_ == '\0') {
LAB_005575d5:
        local_48 = -1;
      }
      else if (((*puVar2 & 2) == 0) || ((DAT_005f6ee8 & 1) == 0)) {
        if ((local_3c == 0) && (((*local_40 & 2) == 0 || (DAT_00573d36 == '\0')))) {
          if ((!bVar5) || ((DAT_005f6ee8 & 2) == 0)) goto LAB_005575d5;
          local_48 = 2;
          iVar14 = __ftol();
          if (iVar14 < 0) {
LAB_005576a2:
            local_44 = 0x7ff;
          }
          else if (iVar14 < 0x800) {
            local_44 = 0x7ff - iVar14;
          }
          else {
            local_44 = 0;
          }
        }
        else {
          if (((*puVar2 & 1) == 0) || ((DAT_005f6ee8 & 1) == 0)) {
            local_48 = 0;
          }
          else {
            local_48 = 1;
          }
          local_44 = __ftol();
          if (local_44 < 0) {
            local_44 = 0;
          }
          else if (0x7ff < local_44) goto LAB_005576a2;
        }
      }
      else {
        local_44 = 0;
        local_48 = 1;
      }
      local_38 = 4.2039e-45;
      if (bVar23) {
        iVar14 = 0;
        for (uVar17 = local_20; uVar17 != 0; uVar17 = (int)uVar17 >> 1) {
          if ((uVar17 & 1) != 0) {
            iVar14 = iVar14 + 1;
          }
        }
        local_38 = (float)(iVar14 * 3 + 3);
      }
      if (local_48 == -1) {
        puVar12 = (undefined4 *)(&DAT_005d15f8 + local_54 * 0x20);
      }
      else {
        puVar12 = (undefined4 *)sub_41ED90((int)local_38 << 5);
        if (puVar12 == (undefined4 *)0x0) goto LAB_005580d4;
      }
      if (bVar23) {
        iVar14 = ((int)local_38 + local_54) * 0x20;
        uVar17 = (uint)puVar2[1];
        uVar18 = (uint)puVar2[3];
        uVar15 = (uint)puVar2[2];
        *(undefined4 *)(&DAT_005d15f8 + iVar14) = (&DAT_0058b0f0)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d15fc + iVar14) = (&DAT_0058b0f4)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d1600 + iVar14) = (&DAT_0058b0f8)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d1604 + iVar14) = (&DAT_0058b0fc)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d1618 + iVar14) = (&DAT_0058b0f0)[uVar15 * 9];
        *(undefined4 *)(&DAT_005d161c + iVar14) = (&DAT_0058b0f4)[uVar15 * 9];
        *(undefined4 *)(&DAT_005d1620 + iVar14) = (&DAT_0058b0f8)[uVar15 * 9];
        *(undefined4 *)(&DAT_005d1624 + iVar14) = (&DAT_0058b0fc)[uVar15 * 9];
        *(undefined4 *)(&DAT_005d1638 + iVar14) = (&DAT_0058b0f0)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d163c + iVar14) = (&DAT_0058b0f4)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d1640 + iVar14) = (&DAT_0058b0f8)[uVar18 * 9];
        uVar16 = (&DAT_0058b0fc)[uVar18 * 9];
        puVar21 = (undefined4 *)(&DAT_005d15f8 + iVar14);
        local_1c = puVar12;
      }
      else {
        uVar17 = (uint)puVar2[1];
        uVar18 = (uint)puVar2[3];
        uVar15 = (uint)puVar2[2];
        *puVar12 = (&DAT_0058b100)[uVar17 * 9];
        puVar12[1] = (&DAT_0058b104)[uVar17 * 9];
        puVar12[2] = (&DAT_0058b108)[uVar17 * 9];
        puVar12[3] = (&DAT_0058b10c)[uVar17 * 9];
        puVar12[8] = (&DAT_0058b100)[uVar15 * 9];
        puVar12[9] = (&DAT_0058b104)[uVar15 * 9];
        puVar12[10] = (&DAT_0058b108)[uVar15 * 9];
        puVar12[0xb] = (&DAT_0058b10c)[uVar15 * 9];
        puVar12[0x10] = (&DAT_0058b100)[uVar18 * 9];
        puVar12[0x11] = (&DAT_0058b104)[uVar18 * 9];
        puVar12[0x12] = (&DAT_0058b108)[uVar18 * 9];
        uVar16 = (&DAT_0058b10c)[uVar18 * 9];
        puVar21 = puVar12;
      }
      puVar21[0x13] = uVar16;
      if ((*local_40 & 1) == 0) {
        if (((*puVar2 & 0x4000) == 0) && (DAT_006d7c60 != '\0')) {
          uVar6 = puVar2[3];
          uVar3 = puVar2[2];
          puVar21[4] = *(undefined4 *)(param_4 + (uint)puVar2[1] * 4);
          puVar21[5] = 0;
          puVar21[0xc] = *(undefined4 *)(param_4 + (uint)uVar3 * 4);
          puVar21[0xd] = 0;
          puVar21[0x14] = *(undefined4 *)(param_4 + (uint)uVar6 * 4);
        }
        else {
          puVar21[4] = 0xffffff;
          puVar21[5] = 0;
          puVar21[0xc] = 0xffffff;
          puVar21[0xd] = 0;
          puVar21[0x14] = 0xffffff;
        }
        puVar21[0x15] = 0;
        uVar6 = *puVar2;
        bVar8 = (byte)uVar6;
        if ((uVar6 & 0x800) == 0) {
          iVar14 = *(int *)(puVar2 + 4);
          bVar8 = bVar8 >> 5 & 1;
          if (bVar8 == 0) {
            uVar16 = *(undefined4 *)(iVar14 + 8);
          }
          else {
            uVar16 = *(undefined4 *)(iVar14 + 4);
          }
          puVar21[6] = uVar16;
          puVar21[7] = *(undefined4 *)(iVar14 + 0x10);
          if (bVar8 == 0) {
            uVar16 = *(undefined4 *)(iVar14 + 4);
          }
          else {
            uVar16 = *(undefined4 *)(iVar14 + 8);
          }
          puVar21[0xe] = uVar16;
          puVar21[0xf] = *(undefined4 *)(iVar14 + 0x10);
          if (bVar8 == 0) goto LAB_00557a7e;
LAB_00557b14:
          uVar16 = *(undefined4 *)(iVar14 + 4);
LAB_00557a81:
          puVar21[0x16] = uVar16;
          uVar16 = *(undefined4 *)(iVar14 + 0xc);
        }
        else {
          if ((uVar6 & 0x10) == 0) {
            iVar14 = *(int *)(puVar2 + 4);
            bVar8 = bVar8 >> 5 & 1;
            if (bVar8 == 0) {
              uVar16 = *(undefined4 *)(iVar14 + 8);
            }
            else {
              uVar16 = *(undefined4 *)(iVar14 + 4);
            }
            puVar21[6] = uVar16;
            puVar21[7] = *(undefined4 *)(iVar14 + 0x10);
            if (bVar8 == 0) {
              uVar16 = *(undefined4 *)(iVar14 + 4);
            }
            else {
              uVar16 = *(undefined4 *)(iVar14 + 8);
            }
            puVar21[0xe] = uVar16;
            puVar21[0xf] = *(undefined4 *)(iVar14 + 0x10);
            if (bVar8 == 0) goto LAB_00557b14;
LAB_00557a7e:
            uVar16 = *(undefined4 *)(iVar14 + 8);
            goto LAB_00557a81;
          }
          iVar14 = *(int *)(puVar2 + 4);
          bVar8 = bVar8 >> 5 & 1;
          if (bVar8 == 0) {
            uVar16 = *(undefined4 *)(iVar14 + 4);
          }
          else {
            uVar16 = *(undefined4 *)(iVar14 + 8);
          }
          puVar21[6] = uVar16;
          puVar21[7] = *(undefined4 *)(iVar14 + 0xc);
          if (bVar8 == 0) {
            uVar16 = *(undefined4 *)(iVar14 + 8);
          }
          else {
            uVar16 = *(undefined4 *)(iVar14 + 4);
          }
          puVar21[0xe] = uVar16;
          puVar21[0xf] = *(undefined4 *)(iVar14 + 0xc);
          if (bVar8 == 0) {
            puVar21[0x16] = *(undefined4 *)(iVar14 + 8);
            uVar16 = *(undefined4 *)(iVar14 + 0x10);
          }
          else {
            puVar21[0x16] = *(undefined4 *)(iVar14 + 4);
            uVar16 = *(undefined4 *)(iVar14 + 0x10);
          }
        }
        puVar21[0x17] = uVar16;
      }
      else if (((*puVar2 & 0x4000) == 0) && (DAT_006d7c60 != '\0')) {
        uVar6 = puVar2[3];
        uVar17 = *(uint *)(param_4 + (uint)puVar2[1] * 4);
        uVar3 = puVar2[2];
        uVar18 = uVar17 >> 8;
        puVar21[5] = 0;
        puVar21[4] = (uint)CONCAT11((char)((uVar18 & 0xff) * local_24 >> 8),
                                    (char)((uVar17 & 0xff) * local_2c >> 8)) |
                     (uVar18 & 0xff00) * local_18 & 0xff0000;
        uVar17 = *(uint *)(param_4 + (uint)uVar3 * 4);
        puVar21[0xd] = 0;
        uVar18 = uVar17 >> 8;
        puVar21[0xc] = (uint)CONCAT11((char)((uVar18 & 0xff) * local_24 >> 8),
                                      (char)((uVar17 & 0xff) * local_2c >> 8)) |
                       (uVar18 & 0xff00) * local_18 & 0xff0000;
        uVar17 = *(uint *)(param_4 + (uint)uVar6 * 4);
        puVar21[0x15] = 0;
        uVar18 = uVar17 >> 8;
        puVar21[0x14] =
             (uint)CONCAT11((char)((uVar18 & 0xff) * local_24 >> 8),
                            (char)((uVar17 & 0xff) * local_2c >> 8)) |
             (uVar18 & 0xff00) * local_18 & 0xff0000;
      }
      else {
        uVar17 = (local_18 << 8 | local_24) << 8 | local_2c;
        puVar21[4] = uVar17;
        puVar21[5] = 0;
        puVar21[0xc] = uVar17;
        puVar21[0xd] = 0;
        puVar21[0x14] = uVar17;
        puVar21[0x15] = 0;
      }
      if ((bVar5) && (DAT_006d7c6b != '\0')) {
        local_4 = (uint)puVar2[3];
        iVar14 = __ftol();
        uVar17 = (uint)puVar21[4] >> 8;
        puVar21[4] = (puVar21[4] & 0xff) * iVar14 >> 8 & 0xff |
                     (uVar17 & 0xff00) * iVar14 & 0xff0000 | (uVar17 & 0xff) * iVar14 & 0xff00;
        iVar14 = __ftol();
        uVar17 = (uint)puVar21[0xc] >> 8;
        puVar21[0xc] = (puVar21[0xc] & 0xff) * iVar14 >> 8 & 0xff |
                       (uVar17 & 0xff00) * iVar14 & 0xff0000 | (uVar17 & 0xff) * iVar14 & 0xff00;
        iVar14 = __ftol();
        uVar17 = (uint)puVar21[0x14] >> 8;
        puVar21[0x14] =
             (puVar21[0x14] & 0xff) * iVar14 >> 8 & 0xff | (uVar17 & 0xff00) * iVar14 & 0xff0000 |
             (uVar17 & 0xff) * iVar14 & 0xff00;
      }
      if (local_60 == '\0') {
        *(undefined1 *)((int)puVar21 + 0x13) = 0xff;
        *(undefined1 *)((int)puVar21 + 0x33) = 0xff;
        *(undefined1 *)((int)puVar21 + 0x53) = 0xff;
      }
      else {
        *(undefined1 *)((int)puVar21 + 0x13) = (undefined1)local_14;
        *(undefined1 *)((int)puVar21 + 0x33) = (undefined1)local_14;
        *(undefined1 *)((int)puVar21 + 0x53) = (undefined1)local_14;
      }
      if ((bVar5) && (DAT_006d7c6c != '\0')) {
        iVar14 = __ftol();
        *(char *)((int)puVar21 + 0x13) = (char)(iVar14 * (uint)*(byte *)((int)puVar21 + 0x13) >> 8);
        iVar14 = __ftol();
        *(char *)((int)puVar21 + 0x33) = (char)(iVar14 * (uint)*(byte *)((int)puVar21 + 0x33) >> 8);
        iVar14 = __ftol();
        *(char *)((int)puVar21 + 0x53) = (char)(iVar14 * (uint)*(byte *)((int)puVar21 + 0x53) >> 8);
      }
      if ((DAT_006d7c6f != '\0') && ((local_60 != '\0' || ((bVar5 && (DAT_006d7c6c != '\0')))))) {
        uVar17 = puVar21[4];
        uVar15 = (uint)*(byte *)((int)puVar21 + 0x13);
        uVar18 = puVar21[0xc];
        puVar21[4] = (uVar17 & 0xff) * uVar15 >> 8 | (uVar17 >> 8 & 0xff00) * uVar15 & 0xff0000 |
                     (uVar17 >> 8 & 0xff) * uVar15 & 0xff00 | uVar17 & 0xff000000;
        uVar15 = (uint)*(byte *)((int)puVar21 + 0x33);
        uVar17 = puVar21[0x14];
        puVar21[0xc] = (uVar18 & 0xff) * uVar15 >> 8 | (uVar18 >> 8 & 0xff00) * uVar15 & 0xff0000 |
                       (uVar18 >> 8 & 0xff) * uVar15 & 0xff00 | uVar18 & 0xff000000;
        uVar18 = (uint)*(byte *)((int)puVar21 + 0x53);
        puVar21[0x14] =
             (uVar17 & 0xff) * uVar18 >> 8 | (uVar17 >> 8 & 0xff00) * uVar18 & 0xff0000 |
             (uVar17 >> 8 & 0xff) * uVar18 & 0xff00 | uVar17 & 0xff000000;
      }
      if (bVar23) {
        if (bVar5) {
          local_38 = (float)sub_43A610(local_1c,puVar21,3,local_20);
        }
        else {
          local_38 = (float)sub_439F20(local_1c,puVar21,3,local_20);
        }
        puVar21 = local_1c;
        if (local_38 == 0.0) goto LAB_005580d4;
      }
      if (local_48 == -1) {
        local_30 = local_30 & !bVar5;
        local_54 = local_54 + (int)local_38;
      }
      else {
        if ((bVar5) && (DAT_006d7c6c != '\0')) {
          param_3 = local_10;
        }
        else {
          param_3 = local_50;
        }
        if ((bVar5) && (DAT_006d7c6c != '\0')) {
          local_4c = local_c;
        }
        else {
          local_4c = local_3c;
        }
        if ((local_30 == 0) || (bVar5)) {
          bVar8 = 0;
        }
        else {
          bVar8 = 1;
        }
        uVar17 = _DAT_006d7c60 & 0xff;
        uVar6 = *local_40;
        if ((0 < (int)local_38) &&
           (puVar12 = (undefined4 *)sub_41ED90(0x20), puVar12 != (undefined4 *)0x0)) {
          iVar14 = local_48 * 0x800 + local_44;
          *puVar12 = (&DAT_005f6ef8)[iVar14];
          puVar12[2] = local_38;
          puVar12[1] = puVar21;
          puVar12[3] = 0;
          puVar12[4] = 0;
          puVar12[5] = local_5c;
          puVar12[6] = local_58;
          puVar12[7] = (param_3 << 2 | local_4c) << 0xc | -(uint)bVar8 & 8 |
                       -(uint)(uVar17 != 0) & 2 | -(uint)((uVar6 & 2) != 0) & 0x10 |
                       -(uint)(local_5d != '\0') & 0x40 | -(uint)((char)local_28 != '\0') & 4;
          (&DAT_005f6ef8)[iVar14] = puVar12;
        }
      }
    }
LAB_005580d4:
    local_34 = local_34 + 1;
  } while (local_34 < (int)(uint)*(ushort *)(param_1 + 0x6e));
  if (local_54 == 0) {
    return 1;
  }
  uVar18 = local_28 & 0xff;
  uVar6 = *local_40;
  uVar17 = _DAT_006d7c60 & 0xff;
  if (local_54 < 1) {
    return 1;
  }
  if (DAT_005833e1 != '\0') {
    if (local_5c == 0) {
      uVar16 = 0;
    }
    else {
      uVar16 = *(undefined4 *)(local_5c + 0x1c);
    }
    pcVar13 = sub_4C6CD0;
    if (DAT_00583380 == '\0') {
      pcVar13 = sub_442BD0;
    }
    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar16,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8,
               local_54,0,local_58,
               (local_3c * 4 | local_50) << 5 | (-(uint)(uVar18 != 0) & 0xfffffe00) + 0x200 |
               (uint)(uVar17 != 0) | -(uint)(local_30 != 0) & 2 | -(uint)((uVar6 & 2) != 0) & 4);
    return 1;
  }
  if (local_5c == 0) {
    if (DAT_006d7c58 != 1) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
  }
  else {
    if ((local_58 != 0) && (*(int *)(local_5c + 0x14) != local_58)) {
      (**(code **)(**(int **)(local_5c + 0xc) + 0x7c))
                (*(int **)(local_5c + 0xc),*(undefined4 *)(local_58 + 0x10));
      *(int *)(local_5c + 0x14) = local_58;
    }
    if (DAT_006d7c54 != *(int *)(local_5c + 0x10)) {
      (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_5c + 0x10));
      DAT_006d7c54 = *(int *)(local_5c + 0x10);
    }
    if ((uVar17 == 0) || (iVar14 = 4, DAT_005833f0 == '\0')) {
      iVar14 = 2;
    }
    if (DAT_006d7c58 != iVar14) {
      if ((uVar17 == 0) || (uVar16 = 4, DAT_005833f0 == '\0')) {
        uVar16 = 2;
      }
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar16);
      if ((uVar17 == 0) || (DAT_005833f0 == '\0')) {
        DAT_006d7c58 = 2;
      }
      else {
        DAT_006d7c58 = 4;
      }
    }
  }
  if ((local_30 != 0) || (iVar14 = 2, DAT_005833f2 == '\0')) {
    iVar14 = 1;
  }
  if (DAT_006d7c34 != iVar14) {
    if ((local_30 != 0) || (uVar16 = 2, DAT_005833f2 == '\0')) {
      uVar16 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,uVar16);
    if ((local_30 != 0) || (DAT_006d7c34 = 2, DAT_005833f2 == '\0')) {
      DAT_006d7c34 = 1;
    }
  }
  if ((_DAT_006d7c38 & 0xff) != uVar18) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar18);
    _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_28);
  }
  if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
    cVar7 = '\0';
  }
  else {
    cVar7 = '\x01';
  }
  if (DAT_006d7c4e != cVar7) {
    if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
      uVar16 = 0;
    }
    else {
      uVar16 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar16);
    if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
       (DAT_006d7c4e = '\x01', (local_50 & 2) != 0)) {
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
  if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
    uVar17 = 0;
  }
  else {
    uVar17 = 1;
  }
  if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar17) {
    if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
      uVar16 = 0;
    }
    else {
      uVar16 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar16);
    if ((uVar6 & 2) != 0) {
      _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
      if (DAT_006d7c70 != '\0') goto LAB_00558486;
    }
    _DAT_006d7c38 = (uint3)_DAT_006d7c38;
  }
LAB_00558486:
  if (DAT_006d7c50 != 0) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
    DAT_006d7c50 = 0;
  }
  switch(local_3c) {
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
    iVar14 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
    if (DAT_006d7c40 != iVar14) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar14);
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
  switch(local_50) {
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
  (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_54,0x1c);
  return 1;
}

