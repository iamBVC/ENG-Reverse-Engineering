/* sub_422740 @ 00422740   7599 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_422740(int param_1,int param_2,uint param_3,uint param_4,undefined4 param_5)

{
  float *pfVar1;
  ushort *puVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  ushort uVar6;
  char cVar7;
  byte bVar8;
  float *pfVar9;
  float fVar10;
  undefined4 *puVar11;
  uint uVar12;
  code *pcVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  undefined4 uVar17;
  uint uVar18;
  int iVar19;
  float *pfVar20;
  undefined4 *puVar21;
  bool bVar22;
  bool bVar23;
  byte local_55;
  int local_54;
  uint local_50;
  int local_4c;
  int local_48;
  uint local_44;
  int local_40;
  ushort *local_3c;
  int local_38;
  uint local_34;
  int local_30;
  uint local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  undefined4 *local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_c = _DAT_0057dc08 * *(float *)(param_2 + 0x14) +
            _DAT_0057dbe8 * *(float *)(param_2 + 0xc) + _DAT_0057dbf8 * *(float *)(param_2 + 0x10) +
            _DAT_0057dc18;
  iVar19 = 0;
  local_55 = 0;
  local_8 = _DAT_0057dbec * *(float *)(param_2 + 0xc) +
            _DAT_0057dc0c * *(float *)(param_2 + 0x14) + _DAT_0057dbfc * *(float *)(param_2 + 0x10)
            + _DAT_0057dc1c;
  local_4 = _DAT_0057dbf0 * *(float *)(param_2 + 0xc) +
            _DAT_0057dc10 * *(float *)(param_2 + 0x14) + _DAT_0057dc00 * *(float *)(param_2 + 0x10)
            + _DAT_0057dc20;
  sub_41ECE0(local_c,local_8,local_4,*(undefined4 *)(param_2 + 8),param_3,param_4,param_5,
             &DAT_006d7b68);
  _DAT_006d7be8 =
       _DAT_0057db60 * _DAT_006d7b68 +
       _DAT_0057db90 * _DAT_006d7b74 + _DAT_0057db70 * _DAT_006d7b6c + _DAT_0057db80 * _DAT_006d7b70
  ;
  _DAT_006d7bec =
       _DAT_0057db94 * _DAT_006d7b74 +
       _DAT_0057db64 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db74 + _DAT_006d7b70 * _DAT_0057db84
  ;
  _DAT_006d7bf0 =
       _DAT_0057db98 * _DAT_006d7b74 +
       _DAT_0057db68 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db78 + _DAT_006d7b70 * _DAT_0057db88
  ;
  _DAT_006d7bf4 =
       _DAT_0057db9c * _DAT_006d7b74 +
       _DAT_0057db6c * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db7c + _DAT_006d7b70 * _DAT_0057db8c
  ;
  _DAT_006d7bf8 =
       _DAT_006d7b84 * _DAT_0057db90 +
       _DAT_006d7b78 * _DAT_0057db60 + _DAT_0057db70 * _DAT_006d7b7c + _DAT_0057db80 * _DAT_006d7b80
  ;
  _DAT_006d7bfc =
       _DAT_006d7b78 * _DAT_0057db64 +
       _DAT_006d7b7c * _DAT_0057db74 + _DAT_006d7b80 * _DAT_0057db84 + _DAT_006d7b84 * _DAT_0057db94
  ;
  _DAT_006d7c00 =
       _DAT_006d7b78 * _DAT_0057db68 +
       _DAT_006d7b7c * _DAT_0057db78 + _DAT_006d7b80 * _DAT_0057db88 + _DAT_006d7b84 * _DAT_0057db98
  ;
  _DAT_006d7c04 =
       _DAT_006d7b78 * _DAT_0057db6c +
       _DAT_006d7b7c * _DAT_0057db7c + _DAT_006d7b80 * _DAT_0057db8c + _DAT_006d7b84 * _DAT_0057db9c
  ;
  _DAT_006d7c08 =
       _DAT_006d7b94 * _DAT_0057db90 +
       _DAT_006d7b88 * _DAT_0057db60 + _DAT_0057db70 * _DAT_006d7b8c + _DAT_0057db80 * _DAT_006d7b90
  ;
  _DAT_006d7c0c =
       _DAT_006d7b88 * _DAT_0057db64 +
       _DAT_006d7b8c * _DAT_0057db74 + _DAT_006d7b90 * _DAT_0057db84 + _DAT_006d7b94 * _DAT_0057db94
  ;
  _DAT_006d7c10 =
       _DAT_006d7b88 * _DAT_0057db68 +
       _DAT_006d7b8c * _DAT_0057db78 + _DAT_006d7b90 * _DAT_0057db88 + _DAT_006d7b94 * _DAT_0057db98
  ;
  _DAT_006d7c14 =
       _DAT_006d7b88 * _DAT_0057db6c +
       _DAT_006d7b8c * _DAT_0057db7c + _DAT_006d7b90 * _DAT_0057db8c + _DAT_006d7b94 * _DAT_0057db9c
  ;
  _DAT_006d7c18 =
       _DAT_006d7ba4 * _DAT_0057db90 +
       DAT_006d7b98 * _DAT_0057db60 + _DAT_0057db70 * DAT_006d7b9c + _DAT_0057db80 * DAT_006d7ba0;
  _DAT_006d7c1c =
       DAT_006d7b98 * _DAT_0057db64 +
       DAT_006d7b9c * _DAT_0057db74 + DAT_006d7ba0 * _DAT_0057db84 + _DAT_006d7ba4 * _DAT_0057db94;
  _DAT_006d7c20 =
       DAT_006d7b98 * _DAT_0057db68 +
       DAT_006d7b9c * _DAT_0057db78 + DAT_006d7ba0 * _DAT_0057db88 + _DAT_006d7ba4 * _DAT_0057db98;
  _DAT_006d7c24 =
       DAT_006d7b98 * _DAT_0057db6c +
       DAT_006d7b9c * _DAT_0057db7c + DAT_006d7ba0 * _DAT_0057db8c + _DAT_006d7ba4 * _DAT_0057db9c;
  cVar7 = sub_402840(param_1,&DAT_006d7be8,&local_20);
  if (cVar7 == '\0') {
    return 1;
  }
  bVar22 = local_20 != 0;
  bVar23 = false;
  _DAT_006d7be8 =
       _DAT_0057db60 * _DAT_006d7b68 +
       _DAT_0057db90 * _DAT_006d7b74 + _DAT_0057db70 * _DAT_006d7b6c + _DAT_0057db80 * _DAT_006d7b70
  ;
  _DAT_006d7bec =
       _DAT_0057db94 * _DAT_006d7b74 +
       _DAT_0057db64 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db74 + _DAT_006d7b70 * _DAT_0057db84
  ;
  _DAT_006d7bf0 =
       _DAT_0057db98 * _DAT_006d7b74 +
       _DAT_0057db68 * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db78 + _DAT_006d7b70 * _DAT_0057db88
  ;
  _DAT_006d7bf4 =
       _DAT_0057db9c * _DAT_006d7b74 +
       _DAT_0057db6c * _DAT_006d7b68 + _DAT_006d7b6c * _DAT_0057db7c + _DAT_006d7b70 * _DAT_0057db8c
  ;
  _DAT_006d7bf8 =
       _DAT_006d7b84 * _DAT_0057db90 +
       _DAT_006d7b78 * _DAT_0057db60 + _DAT_0057db70 * _DAT_006d7b7c + _DAT_0057db80 * _DAT_006d7b80
  ;
  _DAT_006d7bfc =
       _DAT_006d7b78 * _DAT_0057db64 +
       _DAT_006d7b7c * _DAT_0057db74 + _DAT_006d7b80 * _DAT_0057db84 + _DAT_006d7b84 * _DAT_0057db94
  ;
  _DAT_006d7c00 =
       _DAT_006d7b78 * _DAT_0057db68 +
       _DAT_006d7b7c * _DAT_0057db78 + _DAT_006d7b80 * _DAT_0057db88 + _DAT_006d7b84 * _DAT_0057db98
  ;
  _DAT_006d7c04 =
       _DAT_006d7b78 * _DAT_0057db6c +
       _DAT_006d7b7c * _DAT_0057db7c + _DAT_006d7b80 * _DAT_0057db8c + _DAT_006d7b84 * _DAT_0057db9c
  ;
  _DAT_006d7c08 =
       _DAT_006d7b94 * _DAT_0057db90 +
       _DAT_006d7b88 * _DAT_0057db60 + _DAT_0057db70 * _DAT_006d7b8c + _DAT_0057db80 * _DAT_006d7b90
  ;
  _DAT_006d7c0c =
       _DAT_006d7b88 * _DAT_0057db64 +
       _DAT_006d7b8c * _DAT_0057db74 + _DAT_006d7b90 * _DAT_0057db84 + _DAT_006d7b94 * _DAT_0057db94
  ;
  _DAT_006d7c10 =
       _DAT_006d7b88 * _DAT_0057db68 +
       _DAT_006d7b8c * _DAT_0057db78 + _DAT_006d7b90 * _DAT_0057db88 + _DAT_006d7b94 * _DAT_0057db98
  ;
  _DAT_006d7c14 =
       _DAT_006d7b88 * _DAT_0057db6c +
       _DAT_006d7b8c * _DAT_0057db7c + _DAT_006d7b90 * _DAT_0057db8c + _DAT_006d7b94 * _DAT_0057db9c
  ;
  _DAT_006d7c18 =
       _DAT_006d7ba4 * _DAT_0057db90 +
       DAT_006d7b98 * _DAT_0057db60 + _DAT_0057db70 * DAT_006d7b9c + _DAT_0057db80 * DAT_006d7ba0;
  _DAT_006d7c1c =
       DAT_006d7b98 * _DAT_0057db64 +
       DAT_006d7b9c * _DAT_0057db74 + DAT_006d7ba0 * _DAT_0057db84 + _DAT_006d7ba4 * _DAT_0057db94;
  local_4c = 0;
  _DAT_006d7c20 =
       DAT_006d7b98 * _DAT_0057db68 +
       DAT_006d7b9c * _DAT_0057db78 + DAT_006d7ba0 * _DAT_0057db88 + _DAT_006d7ba4 * _DAT_0057db98;
  _DAT_006d7c24 =
       DAT_006d7b98 * _DAT_0057db6c +
       DAT_006d7b9c * _DAT_0057db7c + DAT_006d7ba0 * _DAT_0057db8c + _DAT_006d7ba4 * _DAT_0057db9c;
  if (bVar22) {
    local_40 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      pfVar20 = (float *)&DAT_0058b0fc;
      do {
        iVar14 = *(int *)(param_1 + 0x70);
        pfVar1 = pfVar20 + -3;
        pfVar9 = (float *)(iVar14 + iVar19);
        *pfVar1 = _DAT_006d7c08 * pfVar9[2] +
                  _DAT_006d7bf8 * *(float *)(iVar14 + 4 + iVar19) +
                  _DAT_006d7be8 * *(float *)(iVar14 + iVar19) + _DAT_006d7c18;
        pfVar20[-2] = _DAT_006d7c0c * pfVar9[2] +
                      _DAT_006d7bec * *pfVar9 + _DAT_006d7bfc * pfVar9[1] + _DAT_006d7c1c;
        pfVar20[-1] = _DAT_006d7c10 * pfVar9[2] +
                      _DAT_006d7bf0 * *pfVar9 + _DAT_006d7c00 * pfVar9[1] + _DAT_006d7c20;
        *pfVar20 = _DAT_006d7c14 * pfVar9[2] + _DAT_006d7bf4 * *pfVar9 + _DAT_006d7c04 * pfVar9[1] +
                   _DAT_006d7c24;
        fVar10 = (float)sub_401080(pfVar1);
        pfVar20[5] = fVar10;
        if (fVar10 == 0.0) {
          fVar10 = _DAT_0056e008 / *pfVar20;
          pfVar20[1] = (*pfVar1 * fVar10 + (float)_DAT_0056e038) * _DAT_00583388;
          pfVar20[2] = ((float)_DAT_0056e038 - pfVar20[-2] * fVar10) * _DAT_0058338c;
          pfVar20[3] = ((float)_DAT_0056e038 - pfVar20[-1] * fVar10) * (float)_DAT_0056e030;
          pfVar20[4] = fVar10;
        }
        local_40 = local_40 + 1;
        iVar19 = iVar19 + 0x18;
        pfVar20 = pfVar20 + 9;
      } while (local_40 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  else {
    iVar19 = 0;
    if (*(short *)(param_1 + 0x6c) != 0) {
      iVar14 = 0;
      pfVar20 = (float *)&DAT_0058b0fc;
      do {
        iVar5 = *(int *)(param_1 + 0x70);
        iVar3 = iVar14 + 8;
        pfVar1 = (float *)(iVar14 + iVar5);
        pfVar9 = (float *)(iVar14 + iVar5);
        iVar19 = iVar19 + 1;
        iVar14 = iVar14 + 0x18;
        pfVar20[-3] = _DAT_006d7bf8 * pfVar9[1] +
                      _DAT_006d7be8 * *pfVar1 + _DAT_006d7c08 * *(float *)(iVar3 + iVar5) +
                      _DAT_006d7c18;
        pfVar20[-2] = _DAT_006d7bec * *pfVar9 +
                      _DAT_006d7bfc * pfVar9[1] + _DAT_006d7c0c * pfVar9[2] + _DAT_006d7c1c;
        pfVar20[-1] = _DAT_006d7bf0 * *pfVar9 +
                      _DAT_006d7c00 * pfVar9[1] + _DAT_006d7c10 * pfVar9[2] + _DAT_006d7c20;
        *pfVar20 = _DAT_006d7bf4 * *pfVar9 + _DAT_006d7c04 * pfVar9[1] + _DAT_006d7c14 * pfVar9[2] +
                   _DAT_006d7c24;
        fVar10 = _DAT_0056e008 / *pfVar20;
        pfVar20[1] = (pfVar20[-3] * fVar10 + (float)_DAT_0056e038) * _DAT_00583388;
        pfVar20[2] = ((float)_DAT_0056e038 - pfVar20[-2] * fVar10) * _DAT_0058338c;
        pfVar20[3] = ((float)_DAT_0056e038 - pfVar20[-1] * fVar10) * (float)_DAT_0056e030;
        pfVar20[4] = fVar10;
        pfVar20 = pfVar20 + 9;
      } while (iVar19 < (int)(uint)*(ushort *)(param_1 + 0x6c));
    }
  }
  local_40 = 0;
  if (*(short *)(param_1 + 0x6e) == 0) {
    return 1;
  }
  do {
    puVar2 = (ushort *)(*(int *)(param_1 + 0x74) + local_40 * 0x1c);
    if (((*puVar2 & 8) != 0) ||
       ((local_55 != 0 && ((byte)local_3c[1] != *(byte *)(*(int *)(puVar2 + 4) + 2))))) {
      uVar17 = 0;
      if (local_4c != 0) {
        uVar18 = local_34 & 0xff;
        uVar6 = *local_3c;
        if (0 < local_4c) {
          if (DAT_005833e1 == '\0') {
            if (local_54 == 0) {
              if (DAT_006d7c58 != 1) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                DAT_006d7c58 = 1;
              }
            }
            else {
              if ((local_48 != 0) && (*(int *)(local_54 + 0x14) != local_48)) {
                (**(code **)(**(int **)(local_54 + 0xc) + 0x7c))
                          (*(int **)(local_54 + 0xc),*(undefined4 *)(local_48 + 0x10));
                *(int *)(local_54 + 0x14) = local_48;
              }
              if (DAT_006d7c54 != *(int *)(local_54 + 0x10)) {
                (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_54 + 0x10));
                DAT_006d7c54 = *(int *)(local_54 + 0x10);
              }
              if (DAT_006d7c58 != 2) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,2);
                DAT_006d7c58 = 2;
              }
            }
            if (DAT_006d7c34 != 1) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
              DAT_006d7c34 = 1;
            }
            if ((_DAT_006d7c38 & 0xff) != uVar18) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar18);
              _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_34);
            }
            if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
              cVar7 = '\0';
            }
            else {
              cVar7 = '\x01';
            }
            if (DAT_006d7c4e != cVar7) {
              if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
                uVar17 = 0;
              }
              else {
                uVar17 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar17);
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
              uVar18 = 0;
            }
            else {
              uVar18 = 1;
            }
            if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar18) {
              if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                uVar17 = 0;
              }
              else {
                uVar17 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar17);
              if ((uVar6 & 2) != 0) {
                _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                if (DAT_006d7c70 != '\0') goto LAB_00423523;
              }
              _DAT_006d7c38 = (uint3)_DAT_006d7c38;
            }
LAB_00423523:
            if (DAT_006d7c50 != 0) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
              DAT_006d7c50 = 0;
            }
            switch(local_44) {
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
              iVar19 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              if (DAT_006d7c40 != iVar19) {
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar19);
                DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              }
              iVar19 = 6;
              if (DAT_006d7c44 != 6) {
LAB_00423758:
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,iVar19);
                DAT_006d7c44 = iVar19;
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
              iVar19 = 2;
              if (DAT_006d7c44 != 2) goto LAB_00423758;
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
            (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_4c,0x1c);
          }
          else {
            iVar19 = (local_44 * 4 | local_50) << 5;
            if (local_54 != 0) {
              uVar17 = *(undefined4 *)(local_54 + 0x1c);
            }
            pcVar13 = sub_4C6CD0;
            if (DAT_00583380 == '\0') {
              pcVar13 = sub_442BD0;
            }
            (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar17,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8
                       ,local_4c,0,local_48,
                       CONCAT31((uint3)((uint)iVar19 >> 8) |
                                (uint3)((-(uint)(uVar18 != 0) & 0xfffffe00) + 0x200 >> 8),
                                (byte)iVar19 | -((uVar6 & 2) != 0) & 4U) | 2);
          }
        }
        local_4c = 0;
      }
      local_3c = *(ushort **)(puVar2 + 4);
      uVar6 = *local_3c;
      uVar18 = uVar6 >> 0xc & 7;
      if ((uVar6 & 1) == 0) {
        local_28 = *(uint *)(&DAT_00574280 + uVar18 * 4);
        local_34 = 1;
        if ((byte)local_3c[1] == 0xff) {
          local_54 = 0;
        }
        else {
          local_54 = (char)(byte)local_3c[1] * 0x20 + DAT_0058114c;
        }
        if (*(byte *)((int)local_3c + 3) == 0xff) {
          local_48 = 0;
        }
        else {
          local_48 = DAT_00581144 + (char)*(byte *)((int)local_3c + 3) * 0x1c;
        }
        iVar19 = uVar18 + (uVar6 >> 8 & 7) * 5;
        local_44 = (&DAT_00573ef8)[iVar19 * 3];
        local_50 = (&DAT_00573efc)[iVar19 * 3];
        bVar8 = *(byte *)(&DAT_00573f00 + iVar19 * 3);
        bVar4 = *(byte *)((int)&DAT_00573f00 + iVar19 * 0xc + 1);
      }
      else {
        local_1c = (uint)(byte)local_3c[2];
        local_54 = 0;
        local_18 = (uint)(byte)local_3c[4];
        local_48 = 0;
        local_14 = (uint)(byte)local_3c[6];
        local_34 = 0;
        local_28 = (uint)(byte)local_3c[8];
        local_44 = (&DAT_00573eb8)[uVar18 * 3];
        local_50 = (&DAT_00573ebc)[uVar18 * 3];
        bVar8 = *(byte *)(&DAT_00573ec0 + uVar18 * 3);
        bVar4 = *(byte *)((int)&DAT_00573ec0 + uVar18 * 0xc + 1);
      }
      param_4 = (uint)bVar8;
      param_3 = (uint)bVar4;
      local_55 = (byte)uVar6 >> 5 & 1;
    }
    if (bVar22) {
      if (((&DAT_0058b110)[(uint)puVar2[3] * 9] &
          (&DAT_0058b110)[(uint)puVar2[1] * 9] & (&DAT_0058b110)[(uint)puVar2[2] * 9]) == 0) {
        local_24 = (&DAT_0058b110)[(uint)puVar2[1] * 9] | (&DAT_0058b110)[(uint)puVar2[2] * 9] |
                   (&DAT_0058b110)[(uint)puVar2[3] * 9];
        bVar23 = local_24 != 0;
        goto LAB_0042398d;
      }
    }
    else {
LAB_0042398d:
      if (DAT_005833e4._1_1_ == '\0') {
        iVar19 = -1;
      }
      else {
        iVar19 = 0;
        if ((local_44 == 0) && (((*local_3c & 2) == 0 || (DAT_00573d36 == '\0')))) {
          iVar19 = -1;
        }
        else {
          local_30 = __ftol();
          if (local_30 < 0) {
            local_30 = 0;
          }
          else if (0x7ff < local_30) {
            local_30 = 0x7ff;
          }
        }
      }
      local_38 = 3;
      if (bVar22) {
        iVar14 = 0;
        for (uVar18 = local_24; uVar18 != 0; uVar18 = (int)uVar18 >> 1) {
          if ((uVar18 & 1) != 0) {
            iVar14 = iVar14 + 1;
          }
        }
        local_38 = iVar14 * 3 + 3;
      }
      if (iVar19 == -1) {
        puVar11 = (undefined4 *)(&DAT_005d15f8 + local_4c * 0x20);
      }
      else {
        puVar11 = (undefined4 *)sub_41ED90(local_38 << 5);
        if (puVar11 == (undefined4 *)0x0) goto LAB_00423efb;
      }
      puVar21 = puVar11;
      if (bVar22) {
        puVar21 = (undefined4 *)(&DAT_005d15f8 + (local_4c + local_38) * 0x20);
        local_10 = puVar11;
      }
      puVar11 = local_10;
      if (bVar23) {
        uVar18 = (uint)puVar2[1];
        uVar15 = (uint)puVar2[3];
        uVar12 = (uint)puVar2[2];
        *puVar21 = (&DAT_0058b0f0)[uVar18 * 9];
        puVar21[1] = (&DAT_0058b0f4)[uVar18 * 9];
        puVar21[2] = (&DAT_0058b0f8)[uVar18 * 9];
        puVar21[3] = (&DAT_0058b0fc)[uVar18 * 9];
        puVar21[8] = (&DAT_0058b0f0)[uVar12 * 9];
        puVar21[9] = (&DAT_0058b0f4)[uVar12 * 9];
        puVar21[10] = (&DAT_0058b0f8)[uVar12 * 9];
        puVar21[0xb] = (&DAT_0058b0fc)[uVar12 * 9];
        puVar21[0x10] = (&DAT_0058b0f0)[uVar15 * 9];
        puVar21[0x11] = (&DAT_0058b0f4)[uVar15 * 9];
        puVar21[0x12] = (&DAT_0058b0f8)[uVar15 * 9];
        uVar17 = (&DAT_0058b0fc)[uVar15 * 9];
      }
      else {
        uVar18 = (uint)puVar2[1];
        uVar15 = (uint)puVar2[3];
        uVar12 = (uint)puVar2[2];
        *puVar21 = (&DAT_0058b100)[uVar18 * 9];
        puVar21[1] = (&DAT_0058b104)[uVar18 * 9];
        puVar21[2] = (&DAT_0058b108)[uVar18 * 9];
        puVar21[3] = (&DAT_0058b10c)[uVar18 * 9];
        puVar21[8] = (&DAT_0058b100)[uVar12 * 9];
        puVar21[9] = (&DAT_0058b104)[uVar12 * 9];
        puVar21[10] = (&DAT_0058b108)[uVar12 * 9];
        puVar21[0xb] = (&DAT_0058b10c)[uVar12 * 9];
        puVar21[0x10] = (&DAT_0058b100)[uVar15 * 9];
        puVar21[0x11] = (&DAT_0058b104)[uVar15 * 9];
        puVar21[0x12] = (&DAT_0058b108)[uVar15 * 9];
        uVar17 = (&DAT_0058b10c)[uVar15 * 9];
      }
      puVar21[0x13] = uVar17;
      if ((**(byte **)(puVar2 + 4) & 1) == 0) {
        puVar21[4] = 0xffffff;
        puVar21[5] = 0;
        puVar21[0xc] = 0xffffff;
        puVar21[0xd] = 0;
        puVar21[0x14] = 0xffffff;
        puVar21[0x15] = 0;
        uVar6 = *puVar2;
        bVar8 = (byte)uVar6;
        if ((uVar6 & 0x800) == 0) {
          iVar14 = *(int *)(puVar2 + 4);
          bVar8 = bVar8 >> 5 & 1;
          if (bVar8 == 0) {
            uVar17 = *(undefined4 *)(iVar14 + 8);
          }
          else {
            uVar17 = *(undefined4 *)(iVar14 + 4);
          }
          puVar21[6] = uVar17;
          puVar21[7] = *(undefined4 *)(iVar14 + 0x10);
          if (bVar8 == 0) {
            uVar17 = *(undefined4 *)(iVar14 + 4);
          }
          else {
            uVar17 = *(undefined4 *)(iVar14 + 8);
          }
          puVar21[0xe] = uVar17;
          puVar21[0xf] = *(undefined4 *)(iVar14 + 0x10);
          if (bVar8 == 0) goto LAB_00423ccc;
LAB_00423d23:
          uVar17 = *(undefined4 *)(iVar14 + 4);
LAB_00423ccf:
          puVar21[0x16] = uVar17;
          uVar17 = *(undefined4 *)(iVar14 + 0xc);
        }
        else {
          if ((uVar6 & 0x10) == 0) {
            iVar14 = *(int *)(puVar2 + 4);
            bVar8 = bVar8 >> 5 & 1;
            if (bVar8 == 0) {
              uVar17 = *(undefined4 *)(iVar14 + 8);
            }
            else {
              uVar17 = *(undefined4 *)(iVar14 + 4);
            }
            puVar21[6] = uVar17;
            puVar21[7] = *(undefined4 *)(iVar14 + 0x10);
            if (bVar8 == 0) {
              uVar17 = *(undefined4 *)(iVar14 + 4);
            }
            else {
              uVar17 = *(undefined4 *)(iVar14 + 8);
            }
            puVar21[0xe] = uVar17;
            puVar21[0xf] = *(undefined4 *)(iVar14 + 0x10);
            if (bVar8 == 0) goto LAB_00423d23;
LAB_00423ccc:
            uVar17 = *(undefined4 *)(iVar14 + 8);
            goto LAB_00423ccf;
          }
          iVar14 = *(int *)(puVar2 + 4);
          bVar8 = bVar8 >> 5 & 1;
          if (bVar8 == 0) {
            uVar17 = *(undefined4 *)(iVar14 + 4);
          }
          else {
            uVar17 = *(undefined4 *)(iVar14 + 8);
          }
          puVar21[6] = uVar17;
          puVar21[7] = *(undefined4 *)(iVar14 + 0xc);
          if (bVar8 == 0) {
            uVar17 = *(undefined4 *)(iVar14 + 8);
          }
          else {
            uVar17 = *(undefined4 *)(iVar14 + 4);
          }
          puVar21[0xe] = uVar17;
          puVar21[0xf] = *(undefined4 *)(iVar14 + 0xc);
          if (bVar8 == 0) {
            puVar21[0x16] = *(undefined4 *)(iVar14 + 8);
            uVar17 = *(undefined4 *)(iVar14 + 0x10);
          }
          else {
            puVar21[0x16] = *(undefined4 *)(iVar14 + 4);
            uVar17 = *(undefined4 *)(iVar14 + 0x10);
          }
        }
        puVar21[0x17] = uVar17;
      }
      else {
        uVar18 = (local_1c << 8 | local_18) << 8 | local_14;
        puVar21[4] = uVar18;
        puVar21[5] = 0;
        puVar21[0xc] = uVar18;
        puVar21[0xd] = 0;
        puVar21[0x14] = uVar18;
        puVar21[0x15] = 0;
      }
      if ((char)param_4 == '\0') {
        *(undefined1 *)((int)puVar21 + 0x13) = 0xff;
        *(undefined1 *)((int)puVar21 + 0x33) = 0xff;
        *(undefined1 *)((int)puVar21 + 0x53) = 0xff;
      }
      else {
        *(undefined1 *)((int)puVar21 + 0x13) = (undefined1)local_28;
        *(undefined1 *)((int)puVar21 + 0x33) = (undefined1)local_28;
        *(undefined1 *)((int)puVar21 + 0x53) = (undefined1)local_28;
      }
      if ((DAT_006d7c6f != '\0') && ((char)param_4 != '\0')) {
        uVar18 = puVar21[4];
        uVar16 = (uint)*(byte *)((int)puVar21 + 0x13);
        uVar12 = (uint)*(byte *)((int)puVar21 + 0x33);
        uVar15 = puVar21[0xc];
        puVar21[4] = (uVar18 & 0xff) * uVar16 >> 8 | (uVar18 >> 8 & 0xff00) * uVar16 & 0xff0000 |
                     (uVar18 >> 8 & 0xff) * uVar16 & 0xff00 | uVar18 & 0xff000000;
        uVar18 = puVar21[0x14];
        puVar21[0xc] = (uVar15 & 0xff) * uVar12 >> 8 | (uVar15 >> 8 & 0xff00) * uVar12 & 0xff0000 |
                       (uVar15 >> 8 & 0xff) * uVar12 & 0xff00 | uVar15 & 0xff000000;
        uVar15 = (uint)*(byte *)((int)puVar21 + 0x53);
        puVar21[0x14] =
             (uVar18 & 0xff) * uVar15 >> 8 | (uVar18 >> 8 & 0xff00) * uVar15 & 0xff0000 |
             (uVar18 >> 8 & 0xff) * uVar15 & 0xff00 | uVar18 & 0xff000000;
      }
      if ((!bVar23) ||
         (local_38 = sub_439F20(local_10,puVar21,3,local_24), puVar21 = puVar11, local_38 != 0)) {
        if (iVar19 == -1) {
          local_4c = local_4c + local_38;
        }
        else {
          uVar6 = *local_3c;
          if ((0 < local_38) &&
             (puVar11 = (undefined4 *)sub_41ED90(0x20), puVar11 != (undefined4 *)0x0)) {
            iVar19 = iVar19 * 0x800 + local_30;
            *puVar11 = (&DAT_005f6ef8)[iVar19];
            puVar11[3] = 0;
            puVar11[4] = 0;
            puVar11[2] = local_38;
            puVar11[5] = local_54;
            puVar11[6] = local_48;
            puVar11[1] = puVar21;
            puVar11[7] = (local_50 << 2 | local_44) << 0xc | -(uint)((uVar6 & 2) != 0) & 0x10 |
                         -(uint)((char)param_3 != '\0') & 0x40 | -(uint)((char)local_34 != '\0') & 4
                         | 8;
            (&DAT_005f6ef8)[iVar19] = puVar11;
          }
        }
      }
    }
LAB_00423efb:
    local_40 = local_40 + 1;
  } while (local_40 < (int)(uint)*(ushort *)(param_1 + 0x6e));
  if (local_4c == 0) {
    return 1;
  }
  uVar18 = local_34 & 0xff;
  uVar6 = *local_3c;
  if (local_4c < 1) {
    return 1;
  }
  if (DAT_005833e1 != '\0') {
    iVar19 = (local_44 << 2 | local_50) << 5;
    if (local_54 == 0) {
      uVar17 = 0;
    }
    else {
      uVar17 = *(undefined4 *)(local_54 + 0x1c);
    }
    pcVar13 = sub_4C6CD0;
    if (DAT_00583380 == '\0') {
      pcVar13 = sub_442BD0;
    }
    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar17,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8,
               local_4c,0,local_48,
               CONCAT31((uint3)((uint)iVar19 >> 8) |
                        (uint3)((-(uint)(uVar18 != 0) & 0xfffffe00) + 0x200 >> 8),
                        (byte)iVar19 | -((uVar6 & 2) != 0) & 4U) | 2);
    return 1;
  }
  if (local_54 == 0) {
    if (DAT_006d7c58 != 1) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
  }
  else {
    if ((local_48 != 0) && (*(int *)(local_54 + 0x14) != local_48)) {
      (**(code **)(**(int **)(local_54 + 0xc) + 0x7c))
                (*(int **)(local_54 + 0xc),*(undefined4 *)(local_48 + 0x10));
      *(int *)(local_54 + 0x14) = local_48;
    }
    if (DAT_006d7c54 != *(int *)(local_54 + 0x10)) {
      (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_54 + 0x10));
      DAT_006d7c54 = *(int *)(local_54 + 0x10);
    }
    if (DAT_006d7c58 != 2) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,2);
      DAT_006d7c58 = 2;
    }
  }
  if (DAT_006d7c34 != 1) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
    DAT_006d7c34 = 1;
  }
  if ((_DAT_006d7c38 & 0xff) != uVar18) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar18);
    _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)local_34);
  }
  if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
    cVar7 = '\0';
  }
  else {
    cVar7 = '\x01';
  }
  if (DAT_006d7c4e != cVar7) {
    if ((((uVar6 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((local_50 & 2) != 0)) {
      uVar17 = 0;
    }
    else {
      uVar17 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar17);
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
    uVar18 = 0;
  }
  else {
    uVar18 = 1;
  }
  if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar18) {
    if (((uVar6 & 2) == 0) || (DAT_006d7c70 == '\0')) {
      uVar17 = 0;
    }
    else {
      uVar17 = 1;
    }
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar17);
    if ((uVar6 & 2) != 0) {
      _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
      if (DAT_006d7c70 != '\0') goto LAB_004241f6;
    }
    _DAT_006d7c38 = (uint3)_DAT_006d7c38;
  }
LAB_004241f6:
  if (DAT_006d7c50 != 0) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
    DAT_006d7c50 = 0;
  }
  switch(local_44) {
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
    iVar19 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
    if (DAT_006d7c40 != iVar19) {
      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar19);
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
  (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,local_4c,0x1c);
  return 1;
}

