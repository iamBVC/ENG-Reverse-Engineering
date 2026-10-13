/* sub_42C8C0 @ 0042c8c0   20359 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_42C8C0(void)

{
  /* Original ESP-relative slots share storage; clipper inputs and four 32-byte
   * vertices must remain contiguous, including overlapping byte fields. */
  union { uint alignment; byte bytes[0x180]; } sprite_stack;
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





























































































  
  (*(uint *)(sprite_stack.bytes + 0x8c)) = 0xffffffff;
  sub_431950();
  if (DAT_006d9be4 != 0) {
    (*DAT_005ff038)();
  }
  (*(float *)(sprite_stack.bytes + 0xf8)) = (float)DAT_00583374 * _DAT_0056e430;
  (*(float *)(sprite_stack.bytes + 0xfc)) = (float)DAT_00583378 * _DAT_0056e42c;
  uVar8 = 0xffffffff;
  puVar10 = DAT_006d9bdc;
  do {
    if (puVar10 == (undefined4 *)0x0) {
      return;
    }
    (*(char *)(sprite_stack.bytes + 0x16)) = 0;
    uVar1 = *(ushort *)(puVar10 + 0xd);
    (*(float *)(sprite_stack.bytes + 0x1c)) = (float)(uint)uVar1;
    uVar22 = (uint)(*(float *)(sprite_stack.bytes + 0x1c)) & 3;
    (*(undefined4 * *)(sprite_stack.bytes + 0x90)) = puVar10;
    if ((uVar1 & 4) == 0) {
      if ((uVar1 & 0x800) == 0) {
        (*(char *)(sprite_stack.bytes + 0x16)) = uVar22 == 3;
        if ((bool)(*(char *)(sprite_stack.bytes + 0x16))) {
          uVar22 = 1;
        }
        uVar17 = (uint)*(ushort *)(puVar10 + 0x10);
        if ((uVar8 != uVar17) && (uVar8 = uVar17, (*(uint *)(sprite_stack.bytes + 0x8c)) = uVar17, uVar17 < 0x30)) {
          uVar8 = *(uint *)(&DAT_005fd0c0 + uVar17 * 4);
          (*(uint *)(sprite_stack.bytes + 0x8c)) = uVar8;
        }
        if ((uVar1 & 8) != 0) {
          uVar8 = uVar8 + 1 + ((int)puVar10[0x11] >> 5);
          (*(uint *)(sprite_stack.bytes + 0x8c)) = uVar8;
        }
        (*(ushort * *)(sprite_stack.bytes + 0x4c)) = (ushort *)(DAT_00581154 + uVar8 * 0x14);
        uVar2 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
        if ((uVar2 & 1) == 0) {
          (*(int *)(sprite_stack.bytes + 0x34)) = (char)(byte)(*(ushort * *)(sprite_stack.bytes + 0x4c))[1] * 0x20 + DAT_0058114c;
        }
        else {
          (*(int *)(sprite_stack.bytes + 0x34)) = 0;
        }
        uVar8 = uVar2 >> 0xc & 7;
        (*(float *)(sprite_stack.bytes + 0x4)) = (float)puVar10[0xf];
        uVar17 = uVar2 >> 8 & 7;
        if ((int)(*(float *)(sprite_stack.bytes + 0x4)) < 0) {
          if ((uVar1 & 0x80) == 0) {
            iVar23 = 0x20 - *(short *)((int)puVar10 + 0x32);
          }
          else {
            iVar23 = (int)*(short *)((int)puVar10 + 0x32);
          }
          (*(float *)(sprite_stack.bytes + 0x4)) = (float)-(iVar23 * (int)(*(float *)(sprite_stack.bytes + 0x4)));
        }
        G_WR3((*(uint *)(sprite_stack.bytes + 0x38)), 1, (undefined3)((*(uint *)(sprite_stack.bytes + 0x38)) >> 8));
        G_WR3((*(uint *)(sprite_stack.bytes + 0x30)), 1, (undefined3)((*(uint *)(sprite_stack.bytes + 0x30)) >> 8));
        G_WR3((*(uint *)(sprite_stack.bytes + 0x2c)), 1, (undefined3)((*(uint *)(sprite_stack.bytes + 0x2c)) >> 8));
        if ((uVar1 & 0x10) == 0) {
          (*(uint *)(sprite_stack.bytes + 0x38)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x38)), 1),0x80);
          (*(uint *)(sprite_stack.bytes + 0x30)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x30)), 1),0x80);
          (*(uint *)(sprite_stack.bytes + 0x2c)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x2c)), 1),0x80);
        }
        else {
          uVar19 = puVar10[0xe];
          (*(uint *)(sprite_stack.bytes + 0x38)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x38)), 1),(char)uVar19);
          (*(uint *)(sprite_stack.bytes + 0x30)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x30)), 1),(char)((uint)uVar19 >> 8));
          (*(uint *)(sprite_stack.bytes + 0x2c)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x2c)), 1),(char)((uint)uVar19 >> 0x10));
        }
        (**(code **)(&DAT_00570358 + uVar8 * 4))
                  (&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)),&(*(char *)(sprite_stack.bytes + 0x17)),uVar8);
        if ((*(*(ushort * *)(sprite_stack.bytes + 0x4c)) & 1) == 0) {
          iVar23 = uVar8 + uVar17 * 4;
          if ((*(char *)(sprite_stack.bytes + 0x17)) == -1) {
            iVar23 = uVar17 + iVar23;
            (*(uint *)(sprite_stack.bytes + 0x18)) = (&DAT_00573ef8)[iVar23 * 3];
            (*(uint *)(sprite_stack.bytes + 0xc)) = (&DAT_00573efc)[iVar23 * 3];
          }
          else {
            iVar23 = uVar17 + iVar23;
            (*(uint *)(sprite_stack.bytes + 0x18)) = (&DAT_005740a0)[iVar23 * 3];
            (*(uint *)(sprite_stack.bytes + 0xc)) = (&DAT_005740a4)[iVar23 * 3];
          }
        }
        else {
          (*(uint *)(sprite_stack.bytes + 0x38)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x38)), 1),
                                (char)((uint)(byte)(*(ushort * *)(sprite_stack.bytes + 0x4c))[2] * ((*(uint *)(sprite_stack.bytes + 0x38)) & 0xff) >> 8));
          (*(uint *)(sprite_stack.bytes + 0x30)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x30)), 1),
                                (char)((uint)(byte)(*(ushort * *)(sprite_stack.bytes + 0x4c))[4] * ((*(uint *)(sprite_stack.bytes + 0x30)) & 0xff) >> 8));
          (*(uint *)(sprite_stack.bytes + 0x2c)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x2c)), 1),
                                (char)((uint)(byte)(*(ushort * *)(sprite_stack.bytes + 0x4c))[6] * ((*(uint *)(sprite_stack.bytes + 0x2c)) & 0xff) >> 8));
          if ((*(char *)(sprite_stack.bytes + 0x17)) == -1) {
            (*(uint *)(sprite_stack.bytes + 0x18)) = (&DAT_00573eb8)[uVar8 * 3];
            (*(uint *)(sprite_stack.bytes + 0xc)) = (&DAT_00573ebc)[uVar8 * 3];
          }
          else {
            (*(uint *)(sprite_stack.bytes + 0x18)) = (&DAT_00574060)[uVar8 * 3];
            (*(uint *)(sprite_stack.bytes + 0xc)) = (&DAT_00574064)[uVar8 * 3];
          }
        }
        (*(char *)(sprite_stack.bytes + 0xb)) = sub_40C510(&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)));
        if (((char)(*(uint *)(sprite_stack.bytes + 0x38)) == (char)(*(uint *)(sprite_stack.bytes + 0x30))) && ((char)(*(uint *)(sprite_stack.bytes + 0x30)) == (char)(*(uint *)(sprite_stack.bytes + 0x2c)))) {
          (*(uint *)(sprite_stack.bytes + 0x40)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x40)), 1),1);
          if ((char)(*(uint *)(sprite_stack.bytes + 0x38)) != -1) goto LAB_0042ecfe;
          cVar20 = '\0';
        }
        else {
          (*(uint *)(sprite_stack.bytes + 0x40)) = (uint)G_RD3((*(uint *)(sprite_stack.bytes + 0x40)), 1) << 8;
LAB_0042ecfe: ;
          cVar20 = '\x01';
        }
        fVar12 = (float)(((uint)CONCAT11((*(char *)(sprite_stack.bytes + 0x17)),(char)(*(uint *)(sprite_stack.bytes + 0x38))) << 8 | (*(uint *)(sprite_stack.bytes + 0x30)) & 0xff) << 8
                        | (*(uint *)(sprite_stack.bytes + 0x2c)) & 0xff);
        (*(uint *)(sprite_stack.bytes + 0xa0)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0xa0)), 1),cVar20);
        (*(float *)(sprite_stack.bytes + 0x3c)) = fVar12;
        if (uVar22 == 1) {
          if (((uint)(*(float *)(sprite_stack.bytes + 0x1c)) & 0x2000) != 0) {
            fVar12 = (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (float)_DAT_0056e020;
            (*(float *)(sprite_stack.bytes + 0x4)) = (float)((*(byte *)((int)puVar10 + 0x32) & 7) << 9);
            sub_41ECE0((float)(int)puVar10[2] * (float)_DAT_0056e020,
                       (float)(int)puVar10[3] * (float)_DAT_0056e020,
                       -((float)(int)puVar10[4] * (float)_DAT_0056e020),
                       (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (float)_DAT_0056e018,fVar12,fVar12,fVar12,
                       &DAT_006d7b68);
            (*(float *)(sprite_stack.bytes + 0x94)) = DAT_006d7b98;
            (*(float *)(sprite_stack.bytes + 0x9c)) = DAT_006d7ba0;
            (*(float *)(sprite_stack.bytes + 0x98)) = DAT_006d7b9c;
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
          (*(float *)(sprite_stack.bytes + 0x74)) = _DAT_0057dc28 * fVar3 + _DAT_0057dc38 * fVar4 + _DAT_0057dc48 * fVar5 +
                       _DAT_0057dc58;
          (*(float *)(sprite_stack.bytes + 0x78)) = _DAT_0057dc2c * fVar3 + _DAT_0057dc3c * fVar4 + _DAT_0057dc4c * fVar5 +
                       _DAT_0057dc5c;
          (*(float *)(sprite_stack.bytes + 0x7c)) = _DAT_0057dc30 * fVar3 + _DAT_0057dc40 * fVar4 + _DAT_0057dc50 * fVar5 +
                       _DAT_0057dc60;
          uVar8 = sub_401000(&(*(float *)(sprite_stack.bytes + 0x74)));
          puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
          if ((uVar8 & 0x30) == 0) {
            (*(float *)(sprite_stack.bytes + 0x28)) = _DAT_0056e008 / (*(float *)(sprite_stack.bytes + 0x7c));
            fVar3 = ((*(float *)(sprite_stack.bytes + 0x28)) * (*(float *)(sprite_stack.bytes + 0x74)) + _DAT_0056e008) * _DAT_00583388;
            (*(float *)(sprite_stack.bytes + 0x5c)) = (_DAT_0056e008 - (*(float *)(sprite_stack.bytes + 0x28)) * (*(float *)(sprite_stack.bytes + 0x78))) * _DAT_0058338c;
            (*(float *)(sprite_stack.bytes + 0x60)) = ((*(float *)(sprite_stack.bytes + 0x7c)) - _DAT_0057d70c) * _DAT_0057d7fc * _DAT_0057f914 * (*(float *)(sprite_stack.bytes + 0x28));
            fVar4 = (float)(int)(*(float *)(sprite_stack.bytes + 0x4));
            (*(float *)(sprite_stack.bytes + 0x4)) = (float)DAT_00583374;
            (*(float *)(sprite_stack.bytes + 0x20)) = (*(float *)(sprite_stack.bytes + 0x4)) * fVar4 * (float)_DAT_0056e020 * (*(float *)(sprite_stack.bytes + 0x28));
            (*(float *)(sprite_stack.bytes + 0x10)) = (float)DAT_00583378;
            (*(float *)(sprite_stack.bytes + 0x1c)) = (*(float *)(sprite_stack.bytes + 0x10)) * fVar4 * (float)_DAT_0056e020 * (*(float *)(sprite_stack.bytes + 0x28));
            (*(float *)(sprite_stack.bytes + 0x3c)) = fVar3 - (*(float *)(sprite_stack.bytes + 0x20));
            (*(float *)(sprite_stack.bytes + 0x20)) = (*(float *)(sprite_stack.bytes + 0x20)) + fVar3;
            (*(float *)(sprite_stack.bytes + 0x44)) = (*(float *)(sprite_stack.bytes + 0x5c)) - (*(float *)(sprite_stack.bytes + 0x1c));
            (*(float *)(sprite_stack.bytes + 0x48)) = (*(float *)(sprite_stack.bytes + 0x1c)) + (*(float *)(sprite_stack.bytes + 0x5c));
            puVar24 = puVar10;
            if (_DAT_0056e00c < (*(float *)(sprite_stack.bytes + 0x48))) {
              if ((((*(float *)(sprite_stack.bytes + 0x3c)) < (*(float *)(sprite_stack.bytes + 0x4))) && (_DAT_0056e00c < (*(float *)(sprite_stack.bytes + 0x20)))) &&
                 ((*(float *)(sprite_stack.bytes + 0x44)) < (*(float *)(sprite_stack.bytes + 0x10)))) {
                (*(float *)(sprite_stack.bytes + 0x68)) = *(float *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 4);
                (*(float *)(sprite_stack.bytes + 0x70)) = *(float *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 2);
                (*(float *)(sprite_stack.bytes + 0x64)) = *(float *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 8);
                (*(float *)(sprite_stack.bytes + 0x6c)) = *(float *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 6);
                if ((*(float *)(sprite_stack.bytes + 0x3c)) < _DAT_0056e00c) {
                  fVar4 = -(*(float *)(sprite_stack.bytes + 0x3c));
                  fVar3 = (*(float *)(sprite_stack.bytes + 0x20)) - (*(float *)(sprite_stack.bytes + 0x3c));
                  (*(float *)(sprite_stack.bytes + 0x3c)) = 0.0;
                  (*(float *)(sprite_stack.bytes + 0x70)) = (fVar4 * ((*(float *)(sprite_stack.bytes + 0x68)) - (*(float *)(sprite_stack.bytes + 0x70)))) / fVar3 + (*(float *)(sprite_stack.bytes + 0x70));
                }
                if ((*(float *)(sprite_stack.bytes + 0x4)) < (*(float *)(sprite_stack.bytes + 0x20))) {
                  (*(float *)(sprite_stack.bytes + 0x68)) = (((*(float *)(sprite_stack.bytes + 0x4)) - (*(float *)(sprite_stack.bytes + 0x20))) * ((*(float *)(sprite_stack.bytes + 0x68)) - (*(float *)(sprite_stack.bytes + 0x70)))) /
                               ((*(float *)(sprite_stack.bytes + 0x20)) - (*(float *)(sprite_stack.bytes + 0x3c))) + (*(float *)(sprite_stack.bytes + 0x68));
                  (*(float *)(sprite_stack.bytes + 0x20)) = (*(float *)(sprite_stack.bytes + 0x4));
                }
                if ((*(float *)(sprite_stack.bytes + 0x44)) < _DAT_0056e00c) {
                  fVar4 = -(*(float *)(sprite_stack.bytes + 0x44));
                  fVar3 = (*(float *)(sprite_stack.bytes + 0x48)) - (*(float *)(sprite_stack.bytes + 0x44));
                  (*(float *)(sprite_stack.bytes + 0x44)) = 0.0;
                  (*(float *)(sprite_stack.bytes + 0x6c)) = (fVar4 * ((*(float *)(sprite_stack.bytes + 0x64)) - (*(float *)(sprite_stack.bytes + 0x6c)))) / fVar3 + (*(float *)(sprite_stack.bytes + 0x6c));
                }
                if ((*(float *)(sprite_stack.bytes + 0x10)) < (*(float *)(sprite_stack.bytes + 0x48))) {
                  (*(float *)(sprite_stack.bytes + 0x64)) = (((*(float *)(sprite_stack.bytes + 0x10)) - (*(float *)(sprite_stack.bytes + 0x48))) *
                               ((*(float *)(sprite_stack.bytes + 0x64)) - (*(float *)(sprite_stack.bytes + 0x6c)))) / ((*(float *)(sprite_stack.bytes + 0x48)) - (*(float *)(sprite_stack.bytes + 0x44))) +
                               (*(float *)(sprite_stack.bytes + 0x64));
                  (*(float * *)(sprite_stack.bytes + 0x48)) = (*(float * *)(sprite_stack.bytes + 0x10));
                }
                if (((puVar10[7] & 0x4000) == 0) || ((DAT_006da330 & 0x800) == 0)) {
                  bVar6 = false;
                }
                else {
                  bVar6 = true;
                }
                if ((G_BYTE(DAT_005833e4, 1) == '\0') ||
                   (((*(uint *)(sprite_stack.bytes + 0x18)) == 0 && (((*(*(ushort * *)(sprite_stack.bytes + 0x4c)) & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                  iVar23 = -1;
LAB_0042f0eb: ;
                  (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)&DAT_005ff250;
                }
                else {
                  if ((bVar6) && ((DAT_005f6ee8 & 1) != 0)) {
                    iVar23 = 1;
                  }
                  else {
                    iVar23 = 0;
                  }
                  (*(int *)(sprite_stack.bytes + 0x24)) = __ftol();
                  if ((*(int *)(sprite_stack.bytes + 0x24)) < 0) {
                    (*(int *)(sprite_stack.bytes + 0x24)) = 0;
                  }
                  else if (0x7ff < (*(int *)(sprite_stack.bytes + 0x24))) {
                    (*(int *)(sprite_stack.bytes + 0x24)) = 0x7ff;
                  }
                  if (iVar23 == -1) goto LAB_0042f0eb;
                  (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)sub_41ED90(0x80);
                  puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                  if ((*(float * *)(sprite_stack.bytes + 0x10)) == (float *)0x0) goto LAB_0043182b;
                }
                iVar16 = (*(int *)(sprite_stack.bytes + 0x34));
                pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10));
                uVar19 = 0;
                (*(float * *)(sprite_stack.bytes + 0x10))[0x18] = (*(float *)(sprite_stack.bytes + 0x3c));
                *(*(float * *)(sprite_stack.bytes + 0x10)) = (*(float *)(sprite_stack.bytes + 0x3c));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x10] = (*(float *)(sprite_stack.bytes + 0x20));
                (*(float * *)(sprite_stack.bytes + 0x10))[8] = (*(float *)(sprite_stack.bytes + 0x20));
                (*(float * *)(sprite_stack.bytes + 0x10))[9] = (*(float *)(sprite_stack.bytes + 0x44));
                (*(float * *)(sprite_stack.bytes + 0x10))[1] = (*(float *)(sprite_stack.bytes + 0x44));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x19] = (*(float *)(sprite_stack.bytes + 0x48));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x11] = (*(float *)(sprite_stack.bytes + 0x48));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1a] = (*(float *)(sprite_stack.bytes + 0x60));
                (*(float * *)(sprite_stack.bytes + 0x10))[10] = (*(float *)(sprite_stack.bytes + 0x60));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x12] = (*(float *)(sprite_stack.bytes + 0x60));
                (*(float * *)(sprite_stack.bytes + 0x10))[2] = (*(float *)(sprite_stack.bytes + 0x60));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1b] = (*(float *)(sprite_stack.bytes + 0x28));
                (*(float * *)(sprite_stack.bytes + 0x10))[0xb] = (*(float *)(sprite_stack.bytes + 0x28));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x13] = (*(float *)(sprite_stack.bytes + 0x28));
                (*(float * *)(sprite_stack.bytes + 0x10))[3] = (*(float *)(sprite_stack.bytes + 0x28));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1e] = (*(float *)(sprite_stack.bytes + 0x70));
                (*(float * *)(sprite_stack.bytes + 0x10))[6] = (*(float *)(sprite_stack.bytes + 0x70));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x16] = (*(float *)(sprite_stack.bytes + 0x68));
                (*(float * *)(sprite_stack.bytes + 0x10))[0xe] = (*(float *)(sprite_stack.bytes + 0x68));
                (*(float * *)(sprite_stack.bytes + 0x10))[0xf] = (*(float *)(sprite_stack.bytes + 0x6c));
                (*(float * *)(sprite_stack.bytes + 0x10))[7] = (*(float *)(sprite_stack.bytes + 0x6c));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1c] = fVar12;
                (*(float * *)(sprite_stack.bytes + 0x10))[0x14] = fVar12;
                (*(float * *)(sprite_stack.bytes + 0x10))[0xc] = fVar12;
                (*(float * *)(sprite_stack.bytes + 0x10))[4] = fVar12;
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1d] = 0.0;
                (*(float * *)(sprite_stack.bytes + 0x10))[0x15] = 0.0;
                (*(float * *)(sprite_stack.bytes + 0x10))[0xd] = 0.0;
                (*(float * *)(sprite_stack.bytes + 0x10))[5] = 0.0;
                (*(float * *)(sprite_stack.bytes + 0x10))[0x1f] = (*(float *)(sprite_stack.bytes + 0x64));
                (*(float * *)(sprite_stack.bytes + 0x10))[0x17] = (*(float *)(sprite_stack.bytes + 0x64));
                if (iVar23 == -1) {
                  uVar8 = (*(uint *)(sprite_stack.bytes + 0x40)) & 0xff;
                  uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                  fVar12 = (float)((*(uint *)(sprite_stack.bytes + 0xa0)) & 0xff);
                  uVar21 = (undefined1)(*(uint *)(sprite_stack.bytes + 0x40));
                  (*(float *)(sprite_stack.bytes + 0x4)) = fVar12;
                  if (DAT_005833e1 == '\0') {
                    if ((*(int *)(sprite_stack.bytes + 0x34)) == 0) {
                      if (DAT_006d7c58 != 1) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                        DAT_006d7c58 = 1;
                      }
                    }
                    else {
                      if (DAT_006d7c54 != *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10)) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x98))
                                  (DAT_00582cd4,0,*(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10));
                        DAT_006d7c54 = *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10);
                      }
                      if ((fVar12 == 0.0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                        iVar23 = 2;
                      }
                      if (DAT_006d7c58 != iVar23) {
                        if ((fVar12 == 0.0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                          uVar19 = 2;
                        }
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                        if ((fVar12 == 0.0) || (DAT_005833f0 == '\0')) {
                          DAT_006d7c58 = 2;
                        }
                        else {
                          DAT_006d7c58 = 4;
                        }
                      }
                    }
                    if (DAT_006d7c34 != 1) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                      DAT_006d7c34 = 1;
                    }
                    if ((_DAT_006d7c38 & 0xff) != uVar8) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                    }
                    if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                      cVar20 = '\0';
                    }
                    else {
                      cVar20 = '\x01';
                    }
                    if (DAT_006d7c4e != cVar20) {
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0))
                      {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                         (DAT_006d7c4e = '\x01', ((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                        DAT_006d7c4e = '\0';
                      }
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
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
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                      if ((uVar1 & 2) != 0) {
                        _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                        if (DAT_006d7c70 != '\0') goto LAB_0042f5cd;
                      }
                      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                    }
LAB_0042f5cd: ;
                    if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
                      DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
                    }
                    switch((*(uint *)(sprite_stack.bytes + 0x18))) {
                    case 0:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\0') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                          DAT_006d7c4c = '\0';
                        }
                      }
                      else if (DAT_006d7c4d != '\0') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                        DAT_006d7c4d = '\0';
                      }
                      break;
                    case 1:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar23) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
                        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      }
                      if (DAT_006d7c44 != 6) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                        DAT_006d7c44 = 6;
                      }
                      break;
                    case 2:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                        DAT_006d7c40 = 2;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                      break;
                    case 3:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 5) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                        DAT_006d7c40 = 5;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                    }
                    switch((*(uint *)(sprite_stack.bytes + 0xc))) {
                    case 0:
                    case 2:
                      if (DAT_006d7c5c != 2) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                        DAT_006d7c5c = 2;
                      }
                      break;
                    case 1:
                      if (DAT_006d7c5c != 3) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                        DAT_006d7c5c = 3;
                      }
                      break;
                    case 3:
                      if (DAT_006d7c5c != 4) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                        DAT_006d7c5c = 4;
                      }
                    }
                    if (G_BYTE(DAT_005833e4, 3) == '\0') {
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
                    (**(groove_com6 **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
                    iVar16 = (*(int *)(sprite_stack.bytes + 0x34));
                  }
                  else {
                    iVar23 = ((*(uint *)(sprite_stack.bytes + 0x18)) << 2 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
                    if ((*(int *)(sprite_stack.bytes + 0x34)) != 0) {
                      uVar19 = *(undefined4 *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x1c);
                    }
                    pcVar13 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar13 = sub_442BD0;
                    }
                    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                               (*(float * *)(sprite_stack.bytes + 0x10)),4,1,0,
                               CONCAT31((uint3)((uint)iVar23 >> 8) |
                                        (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                        (byte)iVar23 | fVar12 != 0.0 | -((uVar1 & 2) != 0) & 4U) | 2
                              );
                  }
                  puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                  if ((*(char *)(sprite_stack.bytes + 0xb)) != '\0') {
                    (*(float *)(sprite_stack.bytes + 0x1c)) = (float)((*(uint *)(sprite_stack.bytes + 0x18)) | 2);
                    uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                    if (DAT_005833e1 == '\0') {
                      if (iVar16 == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)(iVar16 + 0x10)) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)(iVar16 + 0x10));
                          DAT_006d7c54 = *(int *)(iVar16 + 0x10);
                        }
                        if (((*(float *)(sprite_stack.bytes + 0x4)) == 0.0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                          iVar23 = 2;
                        }
                        if (DAT_006d7c58 != iVar23) {
                          if (((*(float *)(sprite_stack.bytes + 0x4)) == 0.0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                            uVar19 = 2;
                          }
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                          if (((*(float *)(sprite_stack.bytes + 0x4)) == 0.0) || (DAT_005833f0 == '\0')) {
                            DAT_006d7c58 = 2;
                          }
                          else {
                            DAT_006d7c58 = 4;
                          }
                        }
                      }
                      if (DAT_006d7c34 != 1) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                        DAT_006d7c34 = 1;
                      }
                      if ((_DAT_006d7c38 & 0xff) != uVar8) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                      }
                      uVar8 = (*(uint *)(sprite_stack.bytes + 0xc));
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0))
                      {
                        cVar20 = '\0';
                      }
                      else {
                        cVar20 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar20) {
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uVar8 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
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
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                        if ((uVar1 & 2) != 0) {
                          _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                          if (DAT_006d7c70 != '\0') goto LAB_0042fc02;
                        }
                        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                      }
LAB_0042fc02: ;
                      if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))
                                  (DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
                        DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
                      }
                      switch((int)(*(float *)(sprite_stack.bytes + 0x1c))) {
                      case 0:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\0') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                            DAT_006d7c4c = '\0';
                          }
                        }
                        else if (DAT_006d7c4d != '\0') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                          DAT_006d7c4d = '\0';
                        }
                        break;
                      case 1:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar23) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
                          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        }
                        if (DAT_006d7c44 != 6) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                          DAT_006d7c44 = 6;
                        }
                        break;
                      case 2:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                          DAT_006d7c40 = 2;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                        break;
                      case 3:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 5) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                          DAT_006d7c40 = 5;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                      }
                      switch((*(uint *)(sprite_stack.bytes + 0xc))) {
                      case 0:
                      case 2:
                        if (DAT_006d7c5c != 2) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                          DAT_006d7c5c = 2;
                        }
                        break;
                      case 1:
                        if (DAT_006d7c5c != 3) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                          DAT_006d7c5c = 3;
                        }
                        break;
                      case 3:
                        if (DAT_006d7c5c != 4) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                          DAT_006d7c5c = 4;
                        }
                      }
                      if (G_BYTE(DAT_005833e4, 3) == '\0') {
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
                      (**(groove_com6 **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
                      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                    }
                    else {
                      iVar23 = ((int)(*(float *)(sprite_stack.bytes + 0x1c)) << 2 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
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
                                          (byte)iVar23 | (*(float *)(sprite_stack.bytes + 0x4)) != 0.0 |
                                          -((uVar1 & 2) != 0) & 4U) | 2);
                      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                    }
                  }
                }
                else {
                  if ((*(char *)(sprite_stack.bytes + 0xb)) != '\0') {
                    uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                    puVar10 = (undefined4 *)sub_41ED90(0x20);
                    if (puVar10 != (undefined4 *)0x0) {
                      iVar16 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
                      *puVar10 = (&DAT_005f6ef8)[iVar16];
                      puVar10[1] = (*(float * *)(sprite_stack.bytes + 0x10));
                      puVar10[3] = 0;
                      puVar10[4] = 0;
                      puVar10[6] = 0;
                      puVar10[5] = (*(int *)(sprite_stack.bytes + 0x34));
                      puVar10[2] = 4;
                      puVar10[7] = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc |
                                   -(uint)((uVar1 & 2) != 0) & 0x10 | -(uint)(cVar20 != '\0') & 2 |
                                   -(uint)((char)(*(uint *)(sprite_stack.bytes + 0x40)) != '\0') & 4 | 0x20c9;
                      (&DAT_005f6ef8)[iVar16] = puVar10;
                      pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10));
                    }
                  }
                  uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                  puVar10 = (undefined4 *)sub_41ED90(0x20);
                  puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                  if (puVar10 != (undefined4 *)0x0) {
                    iVar23 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
                    *puVar10 = (&DAT_005f6ef8)[iVar23];
                    puVar10[3] = 0;
                    puVar10[4] = 0;
                    puVar10[6] = 0;
                    puVar10[5] = (*(int *)(sprite_stack.bytes + 0x34));
                    puVar10[1] = pfVar9;
                    puVar10[2] = 4;
                    uVar8 = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc | -(uint)((uVar1 & 2) != 0) & 0x10
                            | -(uint)(cVar20 != '\0') & 2;
                    goto LAB_0042f2bc;
                  }
                }
              }
            }
            else if (((uVar8 & 8) != 0) && ((*(char *)(sprite_stack.bytes + 0x16)) == '\0')) {
              *(undefined2 *)((int)puVar10 + 0x32) = 0;
            }
          }
        }
        else {
          fVar12 = (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (float)_DAT_0056e020;
          (*(float *)(sprite_stack.bytes + 0x4)) = (float)(*(ushort *)(puVar10 + 0xc) + 0xc00);
          sub_41EC70((float)(int)puVar10[2] * (float)_DAT_0056e020,
                     (float)(int)puVar10[3] * (float)_DAT_0056e020,
                     -((float)(int)puVar10[4] * (float)_DAT_0056e020),
                     (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (float)_DAT_0056e018,fVar12,fVar12,fVar12,
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
LAB_004302db: ;
            _DAT_005ff158 = (_DAT_006d7c18 - _DAT_006d7be8) + _DAT_006d7bf8;
            DAT_005ff15c = (_DAT_006d7c1c - _DAT_006d7bec) + _DAT_006d7bfc;
            DAT_005ff160 = (_DAT_006d7c20 - _DAT_006d7bf0) + _DAT_006d7c00;
            DAT_005ff164 = _DAT_006d7c18 + _DAT_006d7bf8 + _DAT_006d7be8;
            DAT_005ff168 = _DAT_006d7c1c + _DAT_006d7bfc + _DAT_006d7bec;
            DAT_005ff16c = _DAT_006d7c20 + _DAT_006d7c00 + _DAT_006d7bf0;
            _DAT_005ff170 = (_DAT_006d7c18 - _DAT_006d7bf8) + _DAT_006d7be8;
            _DAT_005ff174 = _DAT_006d7bec + (_DAT_006d7c1c - _DAT_006d7bfc);
            (*(float *)(sprite_stack.bytes + 0x1c)) = _DAT_006d7c20 - _DAT_006d7c00;
            _DAT_005ff178 = _DAT_006d7bf0 + (*(float *)(sprite_stack.bytes + 0x1c));
            _DAT_005ff17c = (_DAT_006d7c18 - _DAT_006d7bf8) - _DAT_006d7be8;
            _DAT_005ff180 = (_DAT_006d7c1c - _DAT_006d7bfc) - _DAT_006d7bec;
          }
          else {
            _DAT_005ff158 = (_DAT_006d7c08 - _DAT_006d7be8) + _DAT_006d7c18;
            DAT_005ff15c = (_DAT_006d7c0c - _DAT_006d7bec) + _DAT_006d7c1c;
            DAT_005ff160 = (_DAT_006d7c10 - _DAT_006d7bf0) + _DAT_006d7c20;
            DAT_005ff164 = _DAT_006d7c08 + _DAT_006d7c18 + _DAT_006d7be8;
            DAT_005ff168 = _DAT_006d7c0c + _DAT_006d7c1c + _DAT_006d7bec;
            DAT_005ff16c = _DAT_006d7c10 + _DAT_006d7c20 + _DAT_006d7bf0;
            _DAT_005ff170 = (_DAT_006d7c18 - _DAT_006d7c08) + _DAT_006d7be8;
            _DAT_005ff174 = _DAT_006d7bec + (_DAT_006d7c1c - _DAT_006d7c0c);
            (*(float *)(sprite_stack.bytes + 0x1c)) = _DAT_006d7c20 - _DAT_006d7c10;
            _DAT_005ff178 = _DAT_006d7bf0 + (*(float *)(sprite_stack.bytes + 0x1c));
            _DAT_005ff17c = (_DAT_006d7c18 - _DAT_006d7c08) - _DAT_006d7be8;
            _DAT_005ff180 = (_DAT_006d7c1c - _DAT_006d7c0c) - _DAT_006d7bec;
          }
          _DAT_006d7c24 = 0x3f800000;
          _DAT_006d7c14 = 0;
          _DAT_006d7c04 = 0;
          _DAT_006d7bf4 = 0;
          _DAT_005ff184 = (*(float *)(sprite_stack.bytes + 0x1c)) - _DAT_006d7bf0;
          iVar23 = 0;
          DAT_005ff104 = *(undefined4 *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 2);
          _DAT_005ff108 = *(undefined4 *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 4);
          DAT_005ff0b4 = *(undefined4 *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 6);
          _DAT_005ff0bc = *(undefined4 *)((*(ushort * *)(sprite_stack.bytes + 0x4c)) + 8);
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
          (*(float *)(sprite_stack.bytes + 0x4)) = 0.0;
          (*(float *)(sprite_stack.bytes + 0x54)) = 0.0;
          do {
            uVar8 = sub_401000(pfVar9 + -2);
            (*(float *)(sprite_stack.bytes + 0x54)) = (*(float *)(sprite_stack.bytes + 0x54)) + *pfVar9;
            pfVar9 = pfVar9 + 3;
            fVar12 = (float)((uint)(*(float *)(sprite_stack.bytes + 0x4)) | ~uVar8 << 0x10 | uVar8);
            (*(float *)(sprite_stack.bytes + 0x4)) = fVar12;
          } while ((int)pfVar9 < 0x5ff190);
          (*(float *)(sprite_stack.bytes + 0x54)) = (*(float *)(sprite_stack.bytes + 0x54)) * _DAT_0056e164;
          if ((((uint)fVar12 & 8) != 0) && ((*(char *)(sprite_stack.bytes + 0x16)) == '\0')) {
            *(undefined2 *)((int)puVar10 + 0x32) = 0;
          }
          puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
          if (((uint)fVar12 & 0xffff0000) == 0xffff0000) {
            (*(float *)(sprite_stack.bytes + 0x4)) = (float)((uint)fVar12 & 0xffff);
            (*(int *)(sprite_stack.bytes + 0x50)) = 4;
            if (((*(float *)(sprite_stack.bytes + 0x4)) == 0.0) ||
               (cVar7 = sub_4015F0(&_DAT_005ff158,&DAT_005ff4d0,&DAT_005ff104,&DAT_005ff0b4,
                                   &(*(int *)(sprite_stack.bytes + 0x50)),&DAT_005ff080,&(*(float *)(sprite_stack.bytes + 0x4))), puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90)),
               fVar12 = (*(float *)(sprite_stack.bytes + 0x4)), cVar7 != '\0')) {
              (*(float *)(sprite_stack.bytes + 0x4)) = fVar12;
              if ((G_BYTE(DAT_005833e4, 1) == '\0') ||
                 (((*(uint *)(sprite_stack.bytes + 0x18)) == 0 && (((*(*(ushort * *)(sprite_stack.bytes + 0x4c)) & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                iVar23 = -1;
                (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)&DAT_005ff250;
              }
              else {
                iVar23 = 0;
                (*(int *)(sprite_stack.bytes + 0x24)) = __ftol();
                if ((*(int *)(sprite_stack.bytes + 0x24)) < 0) {
                  (*(int *)(sprite_stack.bytes + 0x24)) = 0;
                }
                else if (0x7ff < (*(int *)(sprite_stack.bytes + 0x24))) {
                  (*(int *)(sprite_stack.bytes + 0x24)) = 0x7ff;
                }
                (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)sub_41ED90((int)DAT_005ff0a8 << 5);
                puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                if ((*(float * *)(sprite_stack.bytes + 0x10)) == (float *)0x0) goto LAB_0043182b;
              }
              iVar16 = 0;
              if (0 < (int)DAT_005ff0a8) {
                piVar11 = &DAT_005ff080;
                pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10)) + 2;
                do {
                  iVar18 = *piVar11;
                  piVar11 = piVar11 + 1;
                  iVar16 = iVar16 + 1;
                  fVar12 = _DAT_0056e008 / (&DAT_005ff160)[iVar18 * 3];
                  pfVar9[-2] = (fVar12 * (&_DAT_005ff158)[iVar18 * 3] + _DAT_0056e008) *
                               _DAT_00583388;
                  pfVar9[-1] = (_DAT_0056e008 - fVar12 * (&DAT_005ff15c)[iVar18 * 3]) *
                               _DAT_0058338c;
                  *pfVar9 = ((&DAT_005ff160)[iVar18 * 3] - _DAT_0057d70c) * _DAT_0057d7fc *
                            _DAT_0057f914 * fVar12;
                  pfVar9[1] = fVar12;
                  pfVar9[2] = (*(float *)(sprite_stack.bytes + 0x3c));
                  pfVar9[3] = 0.0;
                  pfVar9[4] = (float)(&DAT_005ff104)[iVar18];
                  pfVar9[5] = (float)(&DAT_005ff0b4)[iVar18];
                  pfVar9 = pfVar9 + 8;
                } while (iVar16 < (int)DAT_005ff0a8);
              }
              if (iVar23 == -1) {
                uVar8 = (*(uint *)(sprite_stack.bytes + 0x40)) & 0xff;
                uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                uVar22 = (*(uint *)(sprite_stack.bytes + 0xa0)) & 0xff;
                (*(float *)(sprite_stack.bytes + 0x4)) = DAT_005ff0a8;
                uVar21 = (undefined1)(*(uint *)(sprite_stack.bytes + 0x40));
                if (0 < (int)DAT_005ff0a8) {
                  if (DAT_005833e1 == '\0') {
                    if ((*(int *)(sprite_stack.bytes + 0x34)) == 0) {
                      if (DAT_006d7c58 != 1) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                        DAT_006d7c58 = 1;
                      }
                    }
                    else {
                      if (DAT_006d7c54 != *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10)) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x98))
                                  (DAT_00582cd4,0,*(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10));
                        DAT_006d7c54 = *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10);
                      }
                      if ((uVar22 == 0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                        iVar23 = 2;
                      }
                      if (DAT_006d7c58 != iVar23) {
                        if ((uVar22 == 0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                          uVar19 = 2;
                        }
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                        if ((uVar22 == 0) || (DAT_005833f0 == '\0')) {
                          DAT_006d7c58 = 2;
                        }
                        else {
                          DAT_006d7c58 = 4;
                        }
                      }
                    }
                    if (DAT_006d7c34 != 1) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                      DAT_006d7c34 = 1;
                    }
                    if ((_DAT_006d7c38 & 0xff) != uVar8) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                    }
                    if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                      cVar20 = '\0';
                    }
                    else {
                      cVar20 = '\x01';
                    }
                    if (DAT_006d7c4e != cVar20) {
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0))
                      {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = 1;
                      }
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                         (DAT_006d7c4e = '\x01', ((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                        DAT_006d7c4e = '\0';
                      }
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
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
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                      if ((uVar1 & 2) != 0) {
                        _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                        if (DAT_006d7c70 != '\0') goto LAB_00430e7e;
                      }
                      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                    }
LAB_00430e7e: ;
                    if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
                      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))
                                (DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
                      DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
                    }
                    switch((*(uint *)(sprite_stack.bytes + 0x18))) {
                    case 0:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\0') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                          DAT_006d7c4c = '\0';
                        }
                      }
                      else if (DAT_006d7c4d != '\0') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                        DAT_006d7c4d = '\0';
                      }
                      break;
                    case 1:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar23) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
                        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      }
                      if (DAT_006d7c44 != 6) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                        DAT_006d7c44 = 6;
                      }
                      break;
                    case 2:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                        DAT_006d7c40 = 2;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                      break;
                    case 3:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 5) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                        DAT_006d7c40 = 5;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                    }
                    switch((*(uint *)(sprite_stack.bytes + 0xc))) {
                    case 0:
                    case 2:
                      if (DAT_006d7c5c != 2) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                        DAT_006d7c5c = 2;
                      }
                      break;
                    case 1:
                      if (DAT_006d7c5c != 3) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                        DAT_006d7c5c = 3;
                      }
                      break;
                    case 3:
                      if (DAT_006d7c5c != 4) {
                        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                        DAT_006d7c5c = 4;
                      }
                    }
                    if ((G_BYTE(DAT_005833e4, 3) == '\0') && (0 < (int)(*(float *)(sprite_stack.bytes + 0x4)))) {
                      pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10)) + 2;
                      fVar12 = (*(float *)(sprite_stack.bytes + 0x4));
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
                    (**(groove_com6 **)(*DAT_00582cd4 + 0x70))
                              (DAT_00582cd4,6,0x1c4,(*(float * *)(sprite_stack.bytes + 0x10)),(*(float *)(sprite_stack.bytes + 0x4)),0x1c);
                  }
                  else {
                    iVar23 = ((*(uint *)(sprite_stack.bytes + 0x18)) << 2 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
                    if ((*(int *)(sprite_stack.bytes + 0x34)) == 0) {
                      uVar19 = 0;
                    }
                    else {
                      uVar19 = *(undefined4 *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x1c);
                    }
                    pcVar13 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar13 = sub_442BD0;
                    }
                    (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                               (*(float * *)(sprite_stack.bytes + 0x10)),DAT_005ff0a8,1,0,
                               CONCAT31((uint3)((uint)iVar23 >> 8) |
                                        (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                        (byte)iVar23 | uVar22 != 0 | -((uVar1 & 2) != 0) & 4U) | 2);
                  }
                }
                puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                if ((*(char *)(sprite_stack.bytes + 0xb)) != '\0') {
                  uVar17 = (*(uint *)(sprite_stack.bytes + 0x18)) | 2;
                  uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                  (*(float *)(sprite_stack.bytes + 0x4)) = DAT_005ff0a8;
                  if (0 < (int)DAT_005ff0a8) {
                    if (DAT_005833e1 == '\0') {
                      if ((*(int *)(sprite_stack.bytes + 0x34)) == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10)) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10));
                          DAT_006d7c54 = *(int *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x10);
                        }
                        if ((uVar22 == 0) || (iVar23 = 4, DAT_005833f0 == '\0')) {
                          iVar23 = 2;
                        }
                        if (DAT_006d7c58 != iVar23) {
                          if ((uVar22 == 0) || (uVar19 = 4, DAT_005833f0 == '\0')) {
                            uVar19 = 2;
                          }
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar19);
                          if ((uVar22 == 0) || (DAT_005833f0 == '\0')) {
                            DAT_006d7c58 = 2;
                          }
                          else {
                            DAT_006d7c58 = 4;
                          }
                        }
                      }
                      if (DAT_006d7c34 != 1) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                        DAT_006d7c34 = 1;
                      }
                      if ((_DAT_006d7c38 & 0xff) != uVar8) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
                        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
                      }
                      uVar8 = (*(uint *)(sprite_stack.bytes + 0xc));
                      if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) || (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0))
                      {
                        cVar20 = '\0';
                      }
                      else {
                        cVar20 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar20) {
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (((*(uint *)(sprite_stack.bytes + 0xc)) & 2) != 0)) {
                          uVar19 = 0;
                        }
                        else {
                          uVar19 = 1;
                        }
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar19);
                        if ((((uVar1 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uVar8 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
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
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar19);
                        if ((uVar1 & 2) != 0) {
                          _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                          if (DAT_006d7c70 != '\0') goto LAB_004314d7;
                        }
                        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
                      }
LAB_004314d7: ;
                      if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
                        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))
                                  (DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
                        DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
                      }
                      switch(uVar17) {
                      case 0:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\0') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                            DAT_006d7c4c = '\0';
                          }
                        }
                        else if (DAT_006d7c4d != '\0') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                          DAT_006d7c4d = '\0';
                        }
                        break;
                      case 1:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar23) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
                          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        }
                        if (DAT_006d7c44 != 6) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                          DAT_006d7c44 = 6;
                        }
                        break;
                      case 2:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                          DAT_006d7c40 = 2;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                        break;
                      case 3:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 5) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                          DAT_006d7c40 = 5;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                      }
                      switch((*(uint *)(sprite_stack.bytes + 0xc))) {
                      case 0:
                      case 2:
                        if (DAT_006d7c5c != 2) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                          DAT_006d7c5c = 2;
                        }
                        break;
                      case 1:
                        if (DAT_006d7c5c != 3) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                          DAT_006d7c5c = 3;
                        }
                        break;
                      case 3:
                        if (DAT_006d7c5c != 4) {
                          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                          DAT_006d7c5c = 4;
                        }
                      }
                      if ((G_BYTE(DAT_005833e4, 3) == '\0') && (0 < (int)(*(float *)(sprite_stack.bytes + 0x4)))) {
                        pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10)) + 2;
                        fVar12 = (*(float *)(sprite_stack.bytes + 0x4));
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
                      (**(groove_com6 **)(*DAT_00582cd4 + 0x70))
                                (DAT_00582cd4,6,0x1c4,(*(float * *)(sprite_stack.bytes + 0x10)),(*(float *)(sprite_stack.bytes + 0x4)),0x1c);
                      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                    }
                    else {
                      iVar23 = (uVar17 * 4 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
                      if ((*(int *)(sprite_stack.bytes + 0x34)) == 0) {
                        uVar19 = 0;
                      }
                      else {
                        uVar19 = *(undefined4 *)((*(int *)(sprite_stack.bytes + 0x34)) + 0x1c);
                      }
                      pcVar13 = sub_4C6CD0;
                      if (DAT_00583380 == '\0') {
                        pcVar13 = sub_442BD0;
                      }
                      (*pcVar13)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,
                                 (*(float * *)(sprite_stack.bytes + 0x10)),DAT_005ff0a8,1,0,
                                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),
                                          (byte)iVar23 | uVar22 != 0 | -((uVar1 & 2) != 0) & 4U) | 2
                                );
                      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                    }
                  }
                }
              }
              else {
                if ((*(char *)(sprite_stack.bytes + 0xb)) != '\0') {
                  (*(float *)(sprite_stack.bytes + 0x4)) = DAT_005ff0a8;
                  uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                  if ((0 < (int)DAT_005ff0a8) &&
                     (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
                    iVar16 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
                    *puVar10 = (&DAT_005f6ef8)[iVar16];
                    puVar10[1] = (*(float * *)(sprite_stack.bytes + 0x10));
                    puVar10[2] = (*(float *)(sprite_stack.bytes + 0x4));
                    puVar10[3] = 0;
                    puVar10[4] = 0;
                    puVar10[6] = 0;
                    puVar10[5] = (*(int *)(sprite_stack.bytes + 0x34));
                    puVar10[7] = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc | -(uint)(cVar20 != '\0') & 2
                                 | -(uint)((uVar1 & 2) != 0) & 0x10 |
                                 -(uint)((char)(*(uint *)(sprite_stack.bytes + 0x40)) != '\0') & 4 | 0x20c9;
                    (&DAT_005f6ef8)[iVar16] = puVar10;
                  }
                }
                fVar12 = DAT_005ff0a8;
                uVar1 = *(*(ushort * *)(sprite_stack.bytes + 0x4c));
                puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
                if ((0 < (int)DAT_005ff0a8) &&
                   (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90)),
                   puVar10 != (undefined4 *)0x0)) {
                  iVar23 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
                  *puVar10 = (&DAT_005f6ef8)[iVar23];
                  puVar10[1] = (*(float * *)(sprite_stack.bytes + 0x10));
                  puVar10[3] = 0;
                  puVar10[4] = 0;
                  puVar10[6] = 0;
                  puVar10[5] = (*(int *)(sprite_stack.bytes + 0x34));
                  puVar10[2] = fVar12;
                  uVar8 = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc | -(uint)(cVar20 != '\0') & 2 |
                          -(uint)((uVar1 & 2) != 0) & 0x10;
LAB_0042f2bc: ;
                  puVar10[7] = CONCAT31((int3)(uVar8 >> 8),
                                        (byte)uVar8 | -((char)(*(uint *)(sprite_stack.bytes + 0x40)) != '\0') & 4U) | 0xc9;
                  (&DAT_005f6ef8)[iVar23] = puVar10;
                  puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
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
      (*(float *)(sprite_stack.bytes + 0xa4)) = _DAT_0057db20 * fVar12 + _DAT_0057db30 * fVar3 + _DAT_0057db40 * fVar4 +
                  _DAT_0057db50;
      (*(float *)(sprite_stack.bytes + 0xa8)) = _DAT_0057db24 * fVar12 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar4 +
                  _DAT_0057db54;
      (*(float *)(sprite_stack.bytes + 0xac)) = _DAT_0057db28 * fVar12 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar4 +
                  _DAT_0057db58;
      (*(float *)(sprite_stack.bytes + 0xb0)) = _DAT_0057db2c * fVar12 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar4 +
                  _DAT_0057db5c;
      (*(uint *)(sprite_stack.bytes + 0xc4)) = sub_401080(&(*(float *)(sprite_stack.bytes + 0xa4)));
      if (((*(uint *)(sprite_stack.bytes + 0xc4)) != 0) && (puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90)), ((*(uint *)(sprite_stack.bytes + 0xc4)) & 0x30) != 0)) goto LAB_0043182b;
      if ((uVar1 & 0x4000) == 0) {
        fVar12 = (float)(puVar10[2] + puVar10[6] * 2) * (float)_DAT_0056e020;
        (*(float *)(sprite_stack.bytes + 0x4)) = (float)(puVar10[4] + puVar10[8] * 2);
        fVar3 = (float)(puVar10[3] + puVar10[7] * 2) * (float)_DAT_0056e020;
      }
      else {
        (*(float *)(sprite_stack.bytes + 0x4)) = (float)(puVar10[8] + puVar10[4]);
        fVar12 = (float)(int)(puVar10[6] + puVar10[2]) * (float)_DAT_0056e020;
        fVar3 = (float)(int)(puVar10[7] + puVar10[3]) * (float)_DAT_0056e020;
      }
      fVar4 = -((float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (float)_DAT_0056e020);
      (*(float *)(sprite_stack.bytes + 0xc8)) = _DAT_0057db20 * fVar12 + _DAT_0057db30 * fVar3 + _DAT_0057db40 * fVar4 +
                  _DAT_0057db50;
      (*(float *)(sprite_stack.bytes + 0xcc)) = _DAT_0057db24 * fVar12 + _DAT_0057db34 * fVar3 + _DAT_0057db44 * fVar4 +
                  _DAT_0057db54;
      (*(float *)(sprite_stack.bytes + 0xd0)) = _DAT_0057db28 * fVar12 + _DAT_0057db38 * fVar3 + _DAT_0057db48 * fVar4 +
                  _DAT_0057db58;
      (*(float *)(sprite_stack.bytes + 0xd4)) = _DAT_0057db2c * fVar12 + _DAT_0057db3c * fVar3 + _DAT_0057db4c * fVar4 +
                  _DAT_0057db5c;
      (*(uint *)(sprite_stack.bytes + 0xe8)) = sub_401080(&(*(float *)(sprite_stack.bytes + 0xc8)));
      if (((*(uint *)(sprite_stack.bytes + 0xe8)) != 0) && (puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90)), ((*(uint *)(sprite_stack.bytes + 0xe8)) & 0x30) != 0)) goto LAB_0043182b;
      (*(float *)(sprite_stack.bytes + 0xc0)) = _DAT_0056e008 / (*(float *)(sprite_stack.bytes + 0xb0));
      (*(float *)(sprite_stack.bytes + 0xb4)) = ((*(float *)(sprite_stack.bytes + 0xa4)) * (*(float *)(sprite_stack.bytes + 0xc0)) + (float)_DAT_0056e038) * _DAT_00583388;
      (*(float *)(sprite_stack.bytes + 0xb8)) = ((float)_DAT_0056e038 - (*(float *)(sprite_stack.bytes + 0xa8)) * (*(float *)(sprite_stack.bytes + 0xc0))) * _DAT_0058338c;
      (*(float *)(sprite_stack.bytes + 0xbc)) = ((float)_DAT_0056e038 - (*(float *)(sprite_stack.bytes + 0xac)) * (*(float *)(sprite_stack.bytes + 0xc0))) * (float)_DAT_0056e030;
      (*(float *)(sprite_stack.bytes + 0xe4)) = _DAT_0056e008 / (*(float *)(sprite_stack.bytes + 0xd4));
      (*(float *)(sprite_stack.bytes + 0xd8)) = ((*(float *)(sprite_stack.bytes + 0xc8)) * (*(float *)(sprite_stack.bytes + 0xe4)) + (float)_DAT_0056e038) * _DAT_00583388;
      (*(float *)(sprite_stack.bytes + 0xdc)) = ((float)_DAT_0056e038 - (*(float *)(sprite_stack.bytes + 0xcc)) * (*(float *)(sprite_stack.bytes + 0xe4))) * _DAT_0058338c;
      (*(float *)(sprite_stack.bytes + 0xe0)) = ((float)_DAT_0056e038 - (*(float *)(sprite_stack.bytes + 0xd0)) * (*(float *)(sprite_stack.bytes + 0xe4))) * (float)_DAT_0056e030;
      (*(float *)(sprite_stack.bytes + 0x54)) = ((*(float *)(sprite_stack.bytes + 0xd4)) + (*(float *)(sprite_stack.bytes + 0xb0))) * _DAT_0056e158;
      (*(float *)(sprite_stack.bytes + 0xec)) = (*(float *)(sprite_stack.bytes + 0xdc)) - (*(float *)(sprite_stack.bytes + 0xb8));
      (*(float *)(sprite_stack.bytes + 0xf0)) = (*(float *)(sprite_stack.bytes + 0xb4)) - (*(float *)(sprite_stack.bytes + 0xd8));
      (*(float *)(sprite_stack.bytes + 0x4)) = SQRT((*(float *)(sprite_stack.bytes + 0xec)) * (*(float *)(sprite_stack.bytes + 0xec)) + (*(float *)(sprite_stack.bytes + 0xf0)) * (*(float *)(sprite_stack.bytes + 0xf0)));
      (*(float *)(sprite_stack.bytes + 0xec)) = (*(float *)(sprite_stack.bytes + 0xec)) / (*(float *)(sprite_stack.bytes + 0x4));
      (*(float *)(sprite_stack.bytes + 0xf0)) = (*(float *)(sprite_stack.bytes + 0xf0)) / (*(float *)(sprite_stack.bytes + 0x4));
      (*(float *)(sprite_stack.bytes + 0x88)) = _DAT_0056e00c / (*(float *)(sprite_stack.bytes + 0x4));
      (*(float *)(sprite_stack.bytes + 0x80)) = (float)DAT_00583374 * _DAT_0056e1dc * (*(float *)(sprite_stack.bytes + 0xec)) * _DAT_0056e158;
      uVar19 = puVar10[0xe];
      (*(uint *)(sprite_stack.bytes + 0x38)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x38)), 1),(char)uVar19);
      (*(uint *)(sprite_stack.bytes + 0x2c)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x2c)), 1),(char)((uint)uVar19 >> 0x10));
      (*(uint *)(sprite_stack.bytes + 0x30)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x30)), 1),(char)((uint)uVar19 >> 8));
      (*(float *)(sprite_stack.bytes + 0x84)) = (float)DAT_00583378 * _DAT_0056e1d8 * (*(float *)(sprite_stack.bytes + 0xf0)) * _DAT_0056e158;
      (*(float *)(sprite_stack.bytes + 0xf4)) = (*(float *)(sprite_stack.bytes + 0x88));
      (*(code *)PTR_sub_408390_00570360)(&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)),&(*(char *)(sprite_stack.bytes + 0x17)),2);
      (*(uint *)(sprite_stack.bytes + 0x18)) = DAT_00573ed0;
      (*(uint *)(sprite_stack.bytes + 0xc)) = DAT_00573ed4;
      (*(char *)(sprite_stack.bytes + 0xb)) = sub_40C510(&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)));
      if (((char)(*(uint *)(sprite_stack.bytes + 0x38)) == (char)(*(uint *)(sprite_stack.bytes + 0x30))) && ((char)(*(uint *)(sprite_stack.bytes + 0x30)) == (char)(*(uint *)(sprite_stack.bytes + 0x2c)))) {
        cVar20 = '\x01';
      }
      else {
        cVar20 = '\0';
      }
      ((float *)(sprite_stack.bytes + 0x100))[0] = (*(float *)(sprite_stack.bytes + 0xb4)) - (*(float *)(sprite_stack.bytes + 0x80));
      ((float *)(sprite_stack.bytes + 0x100))[2] = (*(float *)(sprite_stack.bytes + 0xbc));
      (*(float *)(sprite_stack.bytes + 0x128)) = (*(float *)(sprite_stack.bytes + 0xbc));
      ((float *)(sprite_stack.bytes + 0x100))[3] = (*(float *)(sprite_stack.bytes + 0xc0));
      ((float *)(sprite_stack.bytes + 0x100))[1] = (*(float *)(sprite_stack.bytes + 0xb8)) - (*(float *)(sprite_stack.bytes + 0x84));
      (*(float *)(sprite_stack.bytes + 0x148)) = (*(float *)(sprite_stack.bytes + 0xe0));
      (*(float *)(sprite_stack.bytes + 0x168)) = (*(float *)(sprite_stack.bytes + 0xe0));
      (*(float *)(sprite_stack.bytes + 0x12c)) = (*(float *)(sprite_stack.bytes + 0xc0));
      (*(float *)(sprite_stack.bytes + 0x14c)) = (*(float *)(sprite_stack.bytes + 0xe4));
      (*(float *)(sprite_stack.bytes + 0x120)) = (*(float *)(sprite_stack.bytes + 0xb4)) + (*(float *)(sprite_stack.bytes + 0x80));
      (*(float *)(sprite_stack.bytes + 0x16c)) = (*(float *)(sprite_stack.bytes + 0xe4));
      (*(float *)(sprite_stack.bytes + 0x124)) = (*(float *)(sprite_stack.bytes + 0x84)) + (*(float *)(sprite_stack.bytes + 0xb8));
      (*(float *)(sprite_stack.bytes + 0x140)) = (*(float *)(sprite_stack.bytes + 0xd8)) + (*(float *)(sprite_stack.bytes + 0x80));
      (*(uint *)(sprite_stack.bytes + 0x110)) = (*(uint *)(sprite_stack.bytes + 0x2c)) & 0xff |
                  ((uint)CONCAT11((*(char *)(sprite_stack.bytes + 0x17)),(char)(*(uint *)(sprite_stack.bytes + 0x38))) << 8 | (*(uint *)(sprite_stack.bytes + 0x30)) & 0xff) << 8;
      (*(float *)(sprite_stack.bytes + 0x144)) = (*(float *)(sprite_stack.bytes + 0x84)) + (*(float *)(sprite_stack.bytes + 0xdc));
      (*(uint *)(sprite_stack.bytes + 0x40)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x40)), 1),cVar20);
      (*(undefined4 *)(sprite_stack.bytes + 0x174)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x154)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x134)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x114)) = 0;
      (*(float *)(sprite_stack.bytes + 0x160)) = (*(float *)(sprite_stack.bytes + 0xd8)) - (*(float *)(sprite_stack.bytes + 0x80));
      (*(undefined4 *)(sprite_stack.bytes + 0x178)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x158)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x138)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x118)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x17c)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x15c)) = 0;
      (*(float *)(sprite_stack.bytes + 0x164)) = (*(float *)(sprite_stack.bytes + 0xdc)) - (*(float *)(sprite_stack.bytes + 0x84));
      (*(undefined4 *)(sprite_stack.bytes + 0x13c)) = 0;
      (*(undefined4 *)(sprite_stack.bytes + 0x11c)) = 0;
      uVar8 = (uint)(((float *)(sprite_stack.bytes + 0x100))[0] < _DAT_0056e00c);
      if (DAT_00583390 <= ((float *)(sprite_stack.bytes + 0x100))[0]) {
        uVar8 = uVar8 | 2;
      }
      if (((float *)(sprite_stack.bytes + 0x100))[1] < _DAT_0056e00c) {
        uVar8 = uVar8 | 8;
      }
      if (DAT_00583394 <= ((float *)(sprite_stack.bytes + 0x100))[1]) {
        uVar8 = uVar8 | 4;
      }
      uVar22 = (uint)((*(float *)(sprite_stack.bytes + 0x120)) < _DAT_0056e00c);
      if (DAT_00583390 <= (*(float *)(sprite_stack.bytes + 0x120))) {
        uVar22 = uVar22 | 2;
      }
      if ((*(float *)(sprite_stack.bytes + 0x124)) < _DAT_0056e00c) {
        uVar22 = uVar22 | 8;
      }
      if (DAT_00583394 <= (*(float *)(sprite_stack.bytes + 0x124))) {
        uVar22 = uVar22 | 4;
      }
      uVar17 = (uint)((*(float *)(sprite_stack.bytes + 0x140)) < _DAT_0056e00c);
      if (DAT_00583390 <= (*(float *)(sprite_stack.bytes + 0x140))) {
        uVar17 = uVar17 | 2;
      }
      if ((*(float *)(sprite_stack.bytes + 0x144)) < _DAT_0056e00c) {
        uVar17 = uVar17 | 8;
      }
      if (DAT_00583394 <= (*(float *)(sprite_stack.bytes + 0x144))) {
        uVar17 = uVar17 | 4;
      }
      uVar14 = (uint)((*(float *)(sprite_stack.bytes + 0x160)) < _DAT_0056e00c);
      if (DAT_00583390 <= (*(float *)(sprite_stack.bytes + 0x160))) {
        uVar14 = uVar14 | 2;
      }
      if ((*(float *)(sprite_stack.bytes + 0x164)) < _DAT_0056e00c) {
        uVar14 = uVar14 | 8;
      }
      if (DAT_00583394 <= (*(float *)(sprite_stack.bytes + 0x164))) {
        uVar14 = uVar14 | 4;
      }
      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
      (*(uint *)(sprite_stack.bytes + 0x130)) = (*(uint *)(sprite_stack.bytes + 0x110));
      (*(uint *)(sprite_stack.bytes + 0x150)) = (*(uint *)(sprite_stack.bytes + 0x110));
      (*(uint *)(sprite_stack.bytes + 0x170)) = (*(uint *)(sprite_stack.bytes + 0x110));
      if (((~uVar14 | ~uVar17 | ~uVar22 | ~uVar8) & 0xffff) != 0xffff) goto LAB_0043182b;
      if (G_BYTE(DAT_005833e4, 1) == '\0') {
        iVar23 = -1;
      }
      else if ((*(uint *)(sprite_stack.bytes + 0x18)) == 0) {
        iVar23 = -1;
      }
      else {
        iVar23 = 0;
        (*(int *)(sprite_stack.bytes + 0x24)) = __ftol();
        if ((*(int *)(sprite_stack.bytes + 0x24)) < 0) {
          (*(int *)(sprite_stack.bytes + 0x24)) = 0;
        }
        else if (0x7ff < (*(int *)(sprite_stack.bytes + 0x24))) {
          (*(int *)(sprite_stack.bytes + 0x24)) = 0x7ff;
        }
      }
      uVar8 = uVar14 | uVar17 | uVar22 | uVar8;
      (*(char *)(sprite_stack.bytes + 0x16)) = uVar8 != 0;
      if ((bool)(*(char *)(sprite_stack.bytes + 0x16))) {
        iVar16 = 0;
        for (uVar22 = uVar8; uVar22 != 0; uVar22 = (int)uVar22 >> 1) {
          if ((uVar22 & 1) != 0) {
            iVar16 = iVar16 + 1;
          }
        }
        (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)sub_41ED90((iVar16 * 3 + 3) * 0x40);
        if ((*(float * *)(sprite_stack.bytes + 0x10)) == (float *)0x0) {
          return;
        }
        iVar16 = sub_43AC00((*(float * *)(sprite_stack.bytes + 0x10)),((float *)(sprite_stack.bytes + 0x100)),4,uVar8);
      }
      else {
        (*(float * *)(sprite_stack.bytes + 0x10)) = (float *)sub_41ED90(0x80);
        puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
        if ((*(float * *)(sprite_stack.bytes + 0x10)) == (float *)0x0) goto LAB_0043182b;
        iVar16 = 4;
        pfVar9 = ((float *)(sprite_stack.bytes + 0x100));
        pfVar15 = (*(float * *)(sprite_stack.bytes + 0x10));
        for (iVar18 = 0x20; iVar18 != 0; iVar18 = iVar18 + -1) {
          *pfVar15 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar15 = pfVar15 + 1;
        }
      }
      uVar22 = (*(uint *)(sprite_stack.bytes + 0x18));
      uVar8 = (*(uint *)(sprite_stack.bytes + 0xc));
      (*(int *)(sprite_stack.bytes + 0x50)) = iVar16;
      if (iVar23 != -1) {
        if ((((*(char *)(sprite_stack.bytes + 0xb)) != '\0') && (0 < iVar16)) &&
           (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
          iVar18 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
          *puVar10 = (&DAT_005f6ef8)[iVar18];
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[5] = 0;
          puVar10[6] = 0;
          puVar10[1] = (*(float * *)(sprite_stack.bytes + 0x10));
          puVar10[2] = iVar16;
          puVar10[7] = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc | (uint)((*(char *)(sprite_stack.bytes + 0x16)) == '\0') |
                       -(uint)(cVar20 != '\0') & 4 | 0x20c8;
          (&DAT_005f6ef8)[iVar18] = puVar10;
        }
        iVar16 = (*(int *)(sprite_stack.bytes + 0x50));
        puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
        if ((0 < (*(int *)(sprite_stack.bytes + 0x50))) &&
           (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90)),
           puVar10 != (undefined4 *)0x0)) {
          iVar23 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
          *puVar10 = (&DAT_005f6ef8)[iVar23];
          puVar10[1] = (*(float * *)(sprite_stack.bytes + 0x10));
          puVar10[2] = iVar16;
          puVar10[3] = 0;
          puVar10[4] = 0;
          puVar10[5] = 0;
          puVar10[6] = 0;
          puVar10[7] = CONCAT31((int3)((((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc) >> 8),
                                (*(char *)(sprite_stack.bytes + 0x16)) == '\0' | -(cVar20 != '\0') & 4U) | 200;
          (&DAT_005f6ef8)[iVar23] = puVar10;
        }
        goto LAB_0043182b;
      }
      uVar17 = (*(uint *)(sprite_stack.bytes + 0x40)) & 0xff;
      (*(float *)(sprite_stack.bytes + 0x4)) = (float)(uint)((*(char *)(sprite_stack.bytes + 0x16)) == '\0');
      uVar21 = (undefined1)(*(uint *)(sprite_stack.bytes + 0x40));
      if (iVar16 < 1) goto LAB_0042e5fa;
      (*(float *)(sprite_stack.bytes + 0x1c)) = (float)iVar16;
      if (DAT_005833e1 != '\0') {
        pcVar13 = sub_4C6CD0;
        if (DAT_00583380 == '\0') {
          pcVar13 = sub_442BD0;
        }
        (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,(*(float * *)(sprite_stack.bytes + 0x10)),iVar16,
                   (*(float *)(sprite_stack.bytes + 0x4)),0,
                   ((*(uint *)(sprite_stack.bytes + 0x18)) * 4 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5 | (-(uint)(uVar17 != 0) & 0xfffffe00) + 0x200
                   | 2);
        goto LAB_0042e5fa;
      }
      if (DAT_006d7c58 != 1) {
        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
        DAT_006d7c58 = 1;
      }
      if (DAT_006d7c34 != 1) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
        DAT_006d7c34 = 1;
      }
      if ((_DAT_006d7c38 & 0xff) != uVar17) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar17);
        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
      }
      if (DAT_006d7c4e != '\0') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
        DAT_006d7c4e = '\0';
      }
      if (DAT_006d7c30 != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
        DAT_006d7c30 = '\x01';
      }
      if (DAT_006d7c39 != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
      }
      if (DAT_006d7c48 != 4) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
        DAT_006d7c48 = 4;
      }
      if (DAT_006d7c3a != '\0') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
      }
      if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
        DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
      }
      uVar22 = (*(uint *)(sprite_stack.bytes + 0x18));
      switch((*(uint *)(sprite_stack.bytes + 0x18))) {
      case 0:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\0') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
            DAT_006d7c4c = '\0';
          }
        }
        else if (DAT_006d7c4d != '\0') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
          DAT_006d7c4d = '\0';
        }
        break;
      case 1:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        if (DAT_006d7c40 != iVar23) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        }
        if (DAT_006d7c44 != 6) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
          DAT_006d7c44 = 6;
        }
        break;
      case 2:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        if (DAT_006d7c40 != 2) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
          DAT_006d7c40 = 2;
        }
        goto joined_r0x0042e4fd;
      case 3:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        if (DAT_006d7c40 != 5) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
          DAT_006d7c40 = 5;
        }
joined_r0x0042e4fd:
        if (DAT_006d7c44 != 2) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
          DAT_006d7c44 = 2;
        }
      }
      uVar8 = (*(uint *)(sprite_stack.bytes + 0xc));
      iVar23 = 3;
      switch((*(uint *)(sprite_stack.bytes + 0xc))) {
      case 0:
      case 2:
        if (DAT_006d7c5c != 2) {
          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
          DAT_006d7c5c = 2;
        }
        break;
      case 1:
        if (DAT_006d7c5c != 3) {
          uVar19 = 3;
          iVar16 = *DAT_00582cd4;
LAB_0042e575: ;
          (**(groove_com4 **)(iVar16 + 0xa0))(DAT_00582cd4,0,4,uVar19);
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
      if ((G_BYTE(DAT_005833e4, 3) == '\0') && (0 < (int)(*(float *)(sprite_stack.bytes + 0x1c)))) {
        pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10)) + 2;
        fVar12 = (*(float *)(sprite_stack.bytes + 0x1c));
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
      (**(groove_com6 **)(*DAT_00582cd4 + 0x70))
                (DAT_00582cd4,(-((*(float *)(sprite_stack.bytes + 0x4)) != 0.0) & 2U) + 4,0x1c4,(*(float * *)(sprite_stack.bytes + 0x10)),(*(float *)(sprite_stack.bytes + 0x1c)),0x1c);
LAB_0042e5fa: ;
      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
      if (((*(char *)(sprite_stack.bytes + 0xb)) != '\0') && (0 < (*(int *)(sprite_stack.bytes + 0x50)))) {
        (*(float *)(sprite_stack.bytes + 0x1c)) = (float)(*(int *)(sprite_stack.bytes + 0x50));
        if (DAT_005833e1 == '\0') {
          if (DAT_006d7c58 != 1) {
            (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
            DAT_006d7c58 = 1;
          }
          if (DAT_006d7c34 != 1) {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
            DAT_006d7c34 = 1;
          }
          if ((_DAT_006d7c38 & 0xff) != uVar17) {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar17);
            _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
          }
          if (DAT_006d7c4e != '\0') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
            DAT_006d7c4e = '\0';
          }
          if (DAT_006d7c30 != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
            DAT_006d7c30 = '\x01';
          }
          if (DAT_006d7c39 != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
            _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
          }
          if (DAT_006d7c48 != 4) {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
            DAT_006d7c48 = 4;
          }
          if (DAT_006d7c3a != '\0') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
            _DAT_006d7c38 = (uint3)_DAT_006d7c38;
          }
          if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))
                      (DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
            DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
          }
          switch(uVar22 | 2) {
          case 0:
            if (DAT_005833fa == '\0') {
              if (DAT_006d7c4c != '\0') {
                (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                DAT_006d7c4c = '\0';
              }
            }
            else if (DAT_006d7c4d != '\0') {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
              DAT_006d7c4d = '\0';
            }
            break;
          case 1:
            if (DAT_005833fa == '\0') {
              if (DAT_006d7c4c != '\x01') {
                (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                DAT_006d7c4c = '\x01';
              }
            }
            else if (DAT_006d7c4d != '\x01') {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
              DAT_006d7c4d = '\x01';
            }
            iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
            if (DAT_006d7c40 != iVar23) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
              DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
            }
            if (DAT_006d7c44 != 6) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
              DAT_006d7c44 = 6;
            }
            break;
          case 2:
            if (DAT_005833fa == '\0') {
              if (DAT_006d7c4c != '\x01') {
                (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                DAT_006d7c4c = '\x01';
              }
            }
            else if (DAT_006d7c4d != '\x01') {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
              DAT_006d7c4d = '\x01';
            }
            if (DAT_006d7c40 != 2) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
              DAT_006d7c40 = 2;
            }
            if (DAT_006d7c44 != 2) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
              DAT_006d7c44 = 2;
            }
            break;
          case 3:
            if (DAT_005833fa == '\0') {
              if (DAT_006d7c4c != '\x01') {
                (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                DAT_006d7c4c = '\x01';
              }
            }
            else if (DAT_006d7c4d != '\x01') {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
              DAT_006d7c4d = '\x01';
            }
            if (DAT_006d7c40 != 5) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
              DAT_006d7c40 = 5;
            }
            if (DAT_006d7c44 != 2) {
              (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
              DAT_006d7c44 = 2;
            }
          }
          switch((*(uint *)(sprite_stack.bytes + 0xc))) {
          case 0:
          case 2:
            if (DAT_006d7c5c != 2) {
              (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
              DAT_006d7c5c = 2;
            }
            break;
          case 1:
            if (DAT_006d7c5c != 3) {
              (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
              DAT_006d7c5c = 3;
            }
            break;
          case 3:
            if (DAT_006d7c5c != 4) {
              (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
              DAT_006d7c5c = 4;
            }
          }
          if ((G_BYTE(DAT_005833e4, 3) == '\0') && (0 < (int)(*(float *)(sprite_stack.bytes + 0x1c)))) {
            pfVar9 = (*(float * *)(sprite_stack.bytes + 0x10)) + 2;
            fVar12 = (*(float *)(sprite_stack.bytes + 0x1c));
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
          (**(groove_com6 **)(*DAT_00582cd4 + 0x70))
                    (DAT_00582cd4,(-((*(float *)(sprite_stack.bytes + 0x4)) != 0.0) & 2U) + 4,0x1c4,(*(float * *)(sprite_stack.bytes + 0x10)),(*(float *)(sprite_stack.bytes + 0x1c)),0x1c)
          ;
          puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
        }
        else {
          pcVar13 = sub_4C6CD0;
          if (DAT_00583380 == '\0') {
            pcVar13 = sub_442BD0;
          }
          (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,(*(float * *)(sprite_stack.bytes + 0x10)),
                     (*(int *)(sprite_stack.bytes + 0x50)),(*(float *)(sprite_stack.bytes + 0x4)),0,
                     ((uVar22 | 2) * 4 | uVar8) << 5 | (-(uint)(uVar17 != 0) & 0xfffffe00) + 0x200 |
                     2);
          puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
        }
      }
      goto LAB_0043182b;
    }
    fVar12 = (float)(int)puVar10[2] * (float)_DAT_0056e020;
    fVar3 = (float)(int)puVar10[3] * (float)_DAT_0056e020;
    fVar4 = -((float)(int)puVar10[4] * (float)_DAT_0056e020);
    (*(float *)(sprite_stack.bytes + 0x74)) = _DAT_0057dc28 * fVar12 + _DAT_0057dc38 * fVar3 + _DAT_0057dc48 * fVar4 +
                 _DAT_0057dc58;
    (*(float *)(sprite_stack.bytes + 0x78)) = _DAT_0057dc2c * fVar12 + _DAT_0057dc3c * fVar3 + _DAT_0057dc4c * fVar4 +
                 _DAT_0057dc5c;
    (*(float *)(sprite_stack.bytes + 0x7c)) = _DAT_0057dc30 * fVar12 + _DAT_0057dc40 * fVar3 + _DAT_0057dc50 * fVar4 +
                 _DAT_0057dc60;
    uVar8 = sub_401000(&(*(float *)(sprite_stack.bytes + 0x74)));
    puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
    if ((uVar8 & 0x30) != 0) goto LAB_0043182b;
    (*(float *)(sprite_stack.bytes + 0x28)) = _DAT_0056e008 / (*(float *)(sprite_stack.bytes + 0x7c));
    (*(float *)(sprite_stack.bytes + 0x4)) = (float)((int)puVar10[0xf] >> 0xc);
    (*(float *)(sprite_stack.bytes + 0x58)) = ((*(float *)(sprite_stack.bytes + 0x28)) * (*(float *)(sprite_stack.bytes + 0x74)) + _DAT_0056e008) * _DAT_00583388;
    (*(float *)(sprite_stack.bytes + 0x5c)) = (_DAT_0056e008 - (*(float *)(sprite_stack.bytes + 0x28)) * (*(float *)(sprite_stack.bytes + 0x78))) * _DAT_0058338c;
    (*(float *)(sprite_stack.bytes + 0x60)) = ((*(float *)(sprite_stack.bytes + 0x7c)) - _DAT_0057d70c) * _DAT_0057d7fc * _DAT_0057f914 * (*(float *)(sprite_stack.bytes + 0x28));
    fVar12 = (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (*(float *)(sprite_stack.bytes + 0xf8));
    (*(float *)(sprite_stack.bytes + 0x1c)) = (float)(int)(*(float *)(sprite_stack.bytes + 0x4)) * (*(float *)(sprite_stack.bytes + 0xfc));
    (*(float *)(sprite_stack.bytes + 0x3c)) = _DAT_0056e00c;
    if (fVar12 < (*(float *)(sprite_stack.bytes + 0x58))) {
      (*(float *)(sprite_stack.bytes + 0x3c)) = (*(float *)(sprite_stack.bytes + 0x58)) - fVar12;
    }
    fVar3 = (float)DAT_00583374;
    (*(float *)(sprite_stack.bytes + 0x20)) = fVar3;
    if ((*(float *)(sprite_stack.bytes + 0x58)) < fVar3 - fVar12) {
      (*(float *)(sprite_stack.bytes + 0x20)) = fVar12 + (*(float *)(sprite_stack.bytes + 0x58));
    }
    if ((*(float *)(sprite_stack.bytes + 0x1c)) < (*(float *)(sprite_stack.bytes + 0x5c))) {
      (*(float *)(sprite_stack.bytes + 0x44)) = (*(float *)(sprite_stack.bytes + 0x5c)) - (*(float *)(sprite_stack.bytes + 0x1c));
    }
    else {
      (*(float *)(sprite_stack.bytes + 0x44)) = 0.0;
    }
    (*(float *)(sprite_stack.bytes + 0x10)) = (float)DAT_00583378;
    (*(float *)(sprite_stack.bytes + 0x48)) = (*(float *)(sprite_stack.bytes + 0x10));
    if ((*(float *)(sprite_stack.bytes + 0x5c)) < (float)(*(float *)(sprite_stack.bytes + 0x10)) - (*(float *)(sprite_stack.bytes + 0x1c))) {
      (*(float *)(sprite_stack.bytes + 0x48)) = ((*(float *)(sprite_stack.bytes + 0x1c)) + (*(float *)(sprite_stack.bytes + 0x5c)));
    }
    if ((((fVar3 <= (*(float *)(sprite_stack.bytes + 0x3c))) || ((*(float *)(sprite_stack.bytes + 0x20)) <= _DAT_0056e00c)) ||
        ((float)(*(float *)(sprite_stack.bytes + 0x10)) <= (*(float *)(sprite_stack.bytes + 0x44)))) || ((float)(*(float *)(sprite_stack.bytes + 0x48)) <= _DAT_0056e00c))
    goto LAB_0043182b;
    uVar19 = puVar10[0xe];
    (*(uint *)(sprite_stack.bytes + 0x38)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x38)), 1),(char)uVar19);
    (*(uint *)(sprite_stack.bytes + 0x30)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x30)), 1),(char)((uint)uVar19 >> 8));
    (*(uint *)(sprite_stack.bytes + 0x2c)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x2c)), 1),(char)((uint)uVar19 >> 0x10));
    if ((uVar1 & 8) == 0) {
      (*(uint *)(sprite_stack.bytes + 0x18)) = 0;
      (*(uint *)(sprite_stack.bytes + 0xc)) = 0;
    }
    else {
      (*(code *)PTR_sub_408390_00570360)(&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)),&(*(char *)(sprite_stack.bytes + 0x17)),2);
      (*(uint *)(sprite_stack.bytes + 0x18)) = DAT_00573ed0;
      (*(uint *)(sprite_stack.bytes + 0xc)) = DAT_00573ed4;
    }
    uVar8 = (*(uint *)(sprite_stack.bytes + 0x18));
    (*(char *)(sprite_stack.bytes + 0xb)) = sub_40C510(&(*(uint *)(sprite_stack.bytes + 0x38)),&(*(uint *)(sprite_stack.bytes + 0x30)),&(*(uint *)(sprite_stack.bytes + 0x2c)));
    if (((char)(*(uint *)(sprite_stack.bytes + 0x38)) == (char)(*(uint *)(sprite_stack.bytes + 0x30))) && ((char)(*(uint *)(sprite_stack.bytes + 0x30)) == (char)(*(uint *)(sprite_stack.bytes + 0x2c)))) {
      cVar20 = '\x01';
    }
    else {
      cVar20 = '\0';
    }
    fVar12 = (float)(((uint)CONCAT11((*(char *)(sprite_stack.bytes + 0x17)),(char)(*(uint *)(sprite_stack.bytes + 0x38))) << 8 | (*(uint *)(sprite_stack.bytes + 0x30)) & 0xff) << 8 |
                    (*(uint *)(sprite_stack.bytes + 0x2c)) & 0xff);
    (*(uint *)(sprite_stack.bytes + 0x40)) = CONCAT31(G_RD3((*(uint *)(sprite_stack.bytes + 0x40)), 1),cVar20);
    if ((G_BYTE(DAT_005833e4, 1) == '\0') || (uVar8 == 0)) {
      iVar23 = -1;
      pfVar9 = (float *)&DAT_005ff250;
    }
    else {
      iVar23 = 0;
      (*(int *)(sprite_stack.bytes + 0x24)) = __ftol();
      if ((*(int *)(sprite_stack.bytes + 0x24)) < 0) {
        (*(int *)(sprite_stack.bytes + 0x24)) = 0;
      }
      else if (0x7ff < (*(int *)(sprite_stack.bytes + 0x24))) {
        (*(int *)(sprite_stack.bytes + 0x24)) = 0x7ff;
      }
      pfVar9 = (float *)sub_41ED90(0x80);
      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
      if (pfVar9 == (float *)0x0) goto LAB_0043182b;
    }
    pfVar9[0x18] = (*(float *)(sprite_stack.bytes + 0x3c));
    *pfVar9 = (*(float *)(sprite_stack.bytes + 0x3c));
    pfVar9[0x10] = (*(float *)(sprite_stack.bytes + 0x20));
    pfVar9[8] = (*(float *)(sprite_stack.bytes + 0x20));
    pfVar9[1] = (*(float *)(sprite_stack.bytes + 0x44));
    pfVar9[9] = (*(float *)(sprite_stack.bytes + 0x44));
    pfVar9[0x19] = (float)(*(float *)(sprite_stack.bytes + 0x48));
    pfVar9[0x11] = (float)(*(float *)(sprite_stack.bytes + 0x48));
    pfVar9[0x12] = (*(float *)(sprite_stack.bytes + 0x60));
    pfVar9[0x1a] = (*(float *)(sprite_stack.bytes + 0x60));
    pfVar9[2] = (*(float *)(sprite_stack.bytes + 0x60));
    pfVar9[10] = (*(float *)(sprite_stack.bytes + 0x60));
    pfVar9[0xb] = (*(float *)(sprite_stack.bytes + 0x28));
    pfVar9[0x1b] = (*(float *)(sprite_stack.bytes + 0x28));
    pfVar9[0x13] = (*(float *)(sprite_stack.bytes + 0x28));
    pfVar9[3] = (*(float *)(sprite_stack.bytes + 0x28));
    ((uint *)pfVar9)[0x1c] = (uint)fVar12;
    ((uint *)pfVar9)[0x14] = (uint)fVar12;
    ((uint *)pfVar9)[0xc] = (uint)fVar12;
    ((uint *)pfVar9)[4] = (uint)fVar12;
    pfVar9[0x1d] = 0.0;
    pfVar9[0x15] = 0.0;
    pfVar9[0xd] = 0.0;
    pfVar9[5] = 0.0;
    if (iVar23 != -1) {
      if (((*(char *)(sprite_stack.bytes + 0xb)) != '\0') &&
         (puVar10 = (undefined4 *)sub_41ED90(0x20), puVar10 != (undefined4 *)0x0)) {
        iVar16 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
        *puVar10 = (&DAT_005f6ef8)[iVar16];
        puVar10[1] = pfVar9;
        puVar10[3] = 0;
        puVar10[4] = 0;
        puVar10[5] = 0;
        puVar10[6] = 0;
        puVar10[2] = 4;
        puVar10[7] = ((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc | -(uint)(cVar20 != '\0') & 4 | 0x20c9;
        (&DAT_005f6ef8)[iVar16] = puVar10;
      }
      puVar10 = (undefined4 *)sub_41ED90(0x20);
      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
      if (puVar10 != (undefined4 *)0x0) {
        iVar23 = iVar23 * 0x800 + (*(int *)(sprite_stack.bytes + 0x24));
        *puVar10 = (&DAT_005f6ef8)[iVar23];
        puVar10[1] = pfVar9;
        puVar10[3] = 0;
        puVar10[4] = 0;
        puVar10[5] = 0;
        puVar10[6] = 0;
        puVar10[2] = 4;
        puVar10[7] = CONCAT31((int3)((((*(uint *)(sprite_stack.bytes + 0xc)) * 4 | (*(uint *)(sprite_stack.bytes + 0x18))) << 0xc) >> 8),-(cVar20 != '\0'))
                     & 0xffffff04 | 0xc9;
        (&DAT_005f6ef8)[iVar23] = puVar10;
      }
      goto LAB_0043182b;
    }
    uVar8 = (*(uint *)(sprite_stack.bytes + 0x40)) & 0xff;
    uVar21 = (undefined1)(*(uint *)(sprite_stack.bytes + 0x40));
    if (DAT_005833e1 == '\0') {
      if (DAT_006d7c58 != 1) {
        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
        DAT_006d7c58 = 1;
      }
      if (DAT_006d7c34 != 1) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
        DAT_006d7c34 = 1;
      }
      if ((_DAT_006d7c38 & 0xff) != uVar8) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
        _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
      }
      if (DAT_006d7c4e != '\0') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
        DAT_006d7c4e = '\0';
      }
      if (DAT_006d7c30 != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
        DAT_006d7c30 = '\x01';
      }
      if (DAT_006d7c39 != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
        _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
      }
      if (DAT_006d7c48 != 4) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
        DAT_006d7c48 = 4;
      }
      if (DAT_006d7c3a != '\0') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
        _DAT_006d7c38 = (uint3)_DAT_006d7c38;
      }
      if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
        DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
      }
      switch((*(uint *)(sprite_stack.bytes + 0x18))) {
      case 0:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\0') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
            DAT_006d7c4c = '\0';
          }
        }
        else if (DAT_006d7c4d != '\0') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
          DAT_006d7c4d = '\0';
        }
        break;
      case 1:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        if (DAT_006d7c40 != iVar23) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        }
        if (DAT_006d7c44 != 6) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
          DAT_006d7c44 = 6;
        }
        break;
      case 2:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        if (DAT_006d7c40 != 2) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
          DAT_006d7c40 = 2;
        }
        if (DAT_006d7c44 != 2) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
          DAT_006d7c44 = 2;
        }
        break;
      case 3:
        if (DAT_005833fa == '\0') {
          if (DAT_006d7c4c != '\x01') {
            (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
            DAT_006d7c4c = '\x01';
          }
        }
        else if (DAT_006d7c4d != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
          DAT_006d7c4d = '\x01';
        }
        if (DAT_006d7c40 != 5) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
          DAT_006d7c40 = 5;
        }
        if (DAT_006d7c44 != 2) {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
          DAT_006d7c44 = 2;
        }
      }
      iVar23 = 3;
      switch((*(uint *)(sprite_stack.bytes + 0xc))) {
      case 0:
      case 2:
        if (DAT_006d7c5c != 2) {
          (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
          DAT_006d7c5c = 2;
        }
        break;
      case 1:
        if (DAT_006d7c5c != 3) {
          uVar19 = 3;
          iVar16 = *DAT_00582cd4;
LAB_0042d25c: ;
          (**(groove_com4 **)(iVar16 + 0xa0))(DAT_00582cd4,0,4,uVar19);
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
      if (G_BYTE(DAT_005833e4, 3) == '\0') {
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
      (**(groove_com6 **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
    }
    else {
      iVar23 = ((*(uint *)(sprite_stack.bytes + 0x18)) * 4 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
      pcVar13 = sub_4C6CD0;
      if (DAT_00583380 == '\0') {
        pcVar13 = sub_442BD0;
      }
      (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfVar9,4,1,0,
                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),(char)iVar23) | 2
                );
    }
    puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
    if ((*(char *)(sprite_stack.bytes + 0xb)) == '\0') goto LAB_0043182b;
    uVar22 = (*(uint *)(sprite_stack.bytes + 0x18)) | 2;
    if (DAT_005833e1 != '\0') {
      iVar23 = (uVar22 * 4 | (*(uint *)(sprite_stack.bytes + 0xc))) << 5;
      pcVar13 = sub_4C6CD0;
      if (DAT_00583380 == '\0') {
        pcVar13 = sub_442BD0;
      }
      (*pcVar13)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,pfVar9,4,1,0,
                 CONCAT31((uint3)((uint)iVar23 >> 8) |
                          (uint3)((-(uint)(uVar8 != 0) & 0xfffffe00) + 0x200 >> 8),(char)iVar23) | 2
                );
      puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
      goto LAB_0043182b;
    }
    if (DAT_006d7c58 != 1) {
      (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
    if (DAT_006d7c34 != 1) {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
      DAT_006d7c34 = 1;
    }
    if ((_DAT_006d7c38 & 0xff) != uVar8) {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar8);
      _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,uVar21);
    }
    if (DAT_006d7c4e != '\0') {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
      DAT_006d7c4e = '\0';
    }
    if (DAT_006d7c30 != '\x01') {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
      DAT_006d7c30 = '\x01';
    }
    if (DAT_006d7c39 != '\x01') {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
      _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
    }
    if (DAT_006d7c48 != 4) {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
      DAT_006d7c48 = 4;
    }
    if (DAT_006d7c3a != '\0') {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
      _DAT_006d7c38 = (uint3)_DAT_006d7c38;
    }
    if (DAT_006d7c50 != (-(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10)) {
      (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10);
      DAT_006d7c50 = -(uint)(G_BYTE(DAT_005833e4, 3) != '\0') & 0x10;
    }
    switch(uVar22) {
    case 0:
      if (DAT_005833fa == '\0') {
        if (DAT_006d7c4c != '\0') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
          DAT_006d7c4c = '\0';
        }
      }
      else if (DAT_006d7c4d != '\0') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
        DAT_006d7c4d = '\0';
      }
      break;
    case 1:
      if (DAT_005833fa == '\0') {
        if (DAT_006d7c4c != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
          DAT_006d7c4c = '\x01';
        }
      }
      else if (DAT_006d7c4d != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
        DAT_006d7c4d = '\x01';
      }
      iVar23 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
      if (DAT_006d7c40 != iVar23) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar23);
        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
      }
      if (DAT_006d7c44 != 6) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
        DAT_006d7c44 = 6;
      }
      break;
    case 2:
      if (DAT_005833fa == '\0') {
        if (DAT_006d7c4c != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
          DAT_006d7c4c = '\x01';
        }
      }
      else if (DAT_006d7c4d != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
        DAT_006d7c4d = '\x01';
      }
      if (DAT_006d7c40 != 2) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
        DAT_006d7c40 = 2;
      }
      goto joined_r0x0042d682;
    case 3:
      if (DAT_005833fa == '\0') {
        if (DAT_006d7c4c != '\x01') {
          (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
          DAT_006d7c4c = '\x01';
        }
      }
      else if (DAT_006d7c4d != '\x01') {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
        DAT_006d7c4d = '\x01';
      }
      if (DAT_006d7c40 != 5) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
        DAT_006d7c40 = 5;
      }
joined_r0x0042d682:
      if (DAT_006d7c44 != 2) {
        (**(groove_com3 **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
        DAT_006d7c44 = 2;
      }
    }
    switch((*(uint *)(sprite_stack.bytes + 0xc))) {
    case 0:
    case 2:
      if (DAT_006d7c5c != 2) {
        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
        DAT_006d7c5c = 2;
      }
      break;
    case 1:
      if (DAT_006d7c5c != 3) {
        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
        DAT_006d7c5c = 3;
      }
      break;
    case 3:
      if (DAT_006d7c5c != 4) {
        (**(groove_com4 **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
        DAT_006d7c5c = 4;
      }
    }
    if (G_BYTE(DAT_005833e4, 3) == '\0') {
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
    (**(groove_com6 **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar9,4,0x1c);
    puVar24 = (*(undefined4 * *)(sprite_stack.bytes + 0x90));
LAB_0043182b: ;
    puVar10 = (undefined4 *)*puVar24;
    uVar8 = (*(uint *)(sprite_stack.bytes + 0x8c));
  } while( true );
}
