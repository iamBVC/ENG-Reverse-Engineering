/* sub_555140 @ 00555140   4418 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_555140(void)

{
  float *pfVar1;
  ushort *puVar2;
  ushort uVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  float *pfVar10;
  uint uVar11;
  float fVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int iVar15;
  int iVar16;
  code *pcVar17;
  int iVar18;
  uint uVar19;
  float *pfVar20;
  undefined4 *puVar21;
  undefined4 uVar22;
  float *pfVar23;
  undefined4 *puVar24;
  int iVar25;
  int local_4c0;
  uint local_4bc;
  int local_4a8;
  float local_4a0;
  float local_49c;
  undefined4 local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined4 local_48c;
  undefined4 local_488;
  undefined4 local_484;
  undefined4 local_480;
  undefined4 local_47c;
  undefined4 local_478;
  float local_470;
  float local_468;
  float local_464;
  float local_460;
  float local_45c;
  float local_458;
  float local_450;
  float local_44c;
  float local_448;
  float local_440;
  float local_43c;
  float local_438;
  float local_430;
  float local_42c;
  float local_428;
  float local_410 [14];
  undefined4 local_3d8;
  undefined4 local_3d4;
  undefined4 local_3b8;
  undefined4 local_3b4;
  undefined4 local_398;
  undefined4 local_394;
  float local_388 [34];
  undefined4 local_300 [192];
  
  iVar16 = DAT_006d9e28;
  iVar7 = DAT_006d9e38;
  if (DAT_006d9e28 != 0) {
    for (; iVar7 != 0; iVar7 = *(int *)(iVar7 + 4)) {
      local_4a0 = 0.0;
      local_49c = -1.0;
      local_498 = 0xbf800000;
      local_494 = 0;
      local_490 = 0x3f800000;
      local_48c = 0x3f800000;
      local_488 = 0;
      local_484 = 0x3f800000;
      local_480 = 0x3f800000;
      local_47c = 0;
      local_478 = 0xbf800000;
      if (((((*(uint *)(iVar7 + 0xe8) & 0x1000020) != 0x20) ||
           ((*(uint *)(iVar7 + 0xec) & 0x40000) == 0)) || (*(uint *)(iVar7 + 300) < 0x80)) ||
         ((piVar4 = *(int **)(iVar7 + 0xc0), piVar4 == (int *)0x0 || ((short)piVar4[1] == -1))))
      goto LAB_00556264;
      iVar9 = *(int *)(iVar7 + 0x30) - *(int *)(iVar16 + 0x30);
      iVar18 = *(int *)(iVar7 + 0x38) - *(int *)(iVar16 + 0x38);
      iVar15 = *(int *)(iVar7 + 0x34) - *(int *)(iVar16 + 0x34);
      if ((((0x4000 < iVar9) || ((iVar9 < -0x4000 || (0x4000 < iVar15)))) || (iVar15 < -0x4000)) ||
         ((0x4000 < iVar18 || (iVar18 < -0x4000)))) goto LAB_00556264;
      if ((*(ushort *)((int)piVar4 + 6) & 2) == 0) {
        if ((*(ushort *)((int)piVar4 + 6) & 1) == 0) goto LAB_00556264;
        uVar11 = (uint)(short)piVar4[3];
      }
      else {
        uVar11 = (uint)*(ushort *)(piVar4 + 2);
      }
      iVar9 = *(int *)(uVar11 * 0x20 + 4 + *(int *)(DAT_00584648 + 0x3c));
      if (iVar9 == -1) goto LAB_00556264;
      local_4a8 = *(int *)(iVar7 + 0x14c);
      if (local_4a8 == -0x1000) {
        local_4a8 = DAT_00586424;
      }
      iVar15 = *piVar4;
      local_4bc = (*(uint *)(iVar7 + 300) & 0xffffff) >> 4;
      if (*(int *)(iVar16 + 0x34) < iVar15) goto LAB_00556264;
      if (*(int *)(iVar7 + 0x98) < iVar15) {
        iVar15 = *(int *)(iVar7 + 0x98);
      }
      iVar16 = *(int *)(iVar7 + 0x34) - iVar15;
      local_470 = (float)*(int *)(iVar7 + 0x24) * (float)_DAT_0056e058;
      local_468 = (float)*(int *)(iVar7 + 0x30) * (float)_DAT_0056e020;
      local_464 = (float)(iVar15 + 0x10) * (float)_DAT_0056e020;
      local_460 = -((float)*(int *)(iVar7 + 0x38) * (float)_DAT_0056e020);
      if (0 < iVar16) {
        iVar16 = 0x2000 - iVar16 >> 1;
        if (iVar16 < 1) {
          iVar16 = 1;
        }
        local_4bc = (int)(iVar16 * local_4bc) >> 0xc;
      }
      fVar12 = (float)(int)local_4bc * (float)_DAT_0056e020;
      sub_41EC70(local_468,local_464,local_460,local_470,fVar12,fVar12,fVar12,&DAT_006d7b68);
      _DAT_006d7be8 =
           _DAT_0057db20 * _DAT_006d7b68 +
           _DAT_0057db30 * _DAT_006d7b6c +
           _DAT_0057db40 * _DAT_006d7b70 + _DAT_0057db50 * _DAT_006d7b74;
      _DAT_006d7bec =
           _DAT_0057db34 * _DAT_006d7b6c +
           _DAT_0057db44 * _DAT_006d7b70 +
           _DAT_0057db54 * _DAT_006d7b74 + _DAT_0057db24 * _DAT_006d7b68;
      _DAT_006d7bf0 =
           _DAT_0057db38 * _DAT_006d7b6c +
           _DAT_0057db48 * _DAT_006d7b70 +
           _DAT_0057db58 * _DAT_006d7b74 + _DAT_0057db28 * _DAT_006d7b68;
      _DAT_006d7bf4 =
           _DAT_0057db3c * _DAT_006d7b6c +
           _DAT_0057db4c * _DAT_006d7b70 +
           _DAT_0057db5c * _DAT_006d7b74 + _DAT_0057db2c * _DAT_006d7b68;
      _DAT_006d7bf8 =
           _DAT_006d7b7c * _DAT_0057db30 +
           _DAT_006d7b80 * _DAT_0057db40 +
           _DAT_006d7b84 * _DAT_0057db50 + _DAT_006d7b78 * _DAT_0057db20;
      _DAT_006d7bfc =
           _DAT_006d7b78 * _DAT_0057db24 +
           _DAT_006d7b7c * _DAT_0057db34 +
           _DAT_006d7b80 * _DAT_0057db44 + _DAT_006d7b84 * _DAT_0057db54;
      _DAT_006d7c00 =
           _DAT_006d7b78 * _DAT_0057db28 +
           _DAT_006d7b7c * _DAT_0057db38 +
           _DAT_006d7b80 * _DAT_0057db48 + _DAT_006d7b84 * _DAT_0057db58;
      _DAT_006d7c04 =
           _DAT_006d7b78 * _DAT_0057db2c +
           _DAT_006d7b7c * _DAT_0057db3c +
           _DAT_006d7b80 * _DAT_0057db4c + _DAT_006d7b84 * _DAT_0057db5c;
      _DAT_006d7c08 =
           _DAT_006d7b8c * _DAT_0057db30 +
           _DAT_006d7b90 * _DAT_0057db40 +
           _DAT_006d7b94 * _DAT_0057db50 + _DAT_006d7b88 * _DAT_0057db20;
      _DAT_006d7c0c =
           _DAT_006d7b88 * _DAT_0057db24 +
           _DAT_006d7b8c * _DAT_0057db34 +
           _DAT_006d7b90 * _DAT_0057db44 + _DAT_006d7b94 * _DAT_0057db54;
      _DAT_006d7c10 =
           _DAT_006d7b88 * _DAT_0057db28 +
           _DAT_006d7b8c * _DAT_0057db38 +
           _DAT_006d7b90 * _DAT_0057db48 + _DAT_006d7b94 * _DAT_0057db58;
      _DAT_006d7c14 =
           _DAT_006d7b88 * _DAT_0057db2c +
           _DAT_006d7b8c * _DAT_0057db3c +
           _DAT_006d7b90 * _DAT_0057db4c + _DAT_006d7b94 * _DAT_0057db5c;
      _DAT_006d7c18 =
           DAT_006d7b9c * _DAT_0057db30 +
           DAT_006d7ba0 * _DAT_0057db40 +
           _DAT_006d7ba4 * _DAT_0057db50 + DAT_006d7b98 * _DAT_0057db20;
      _DAT_006d7c1c =
           DAT_006d7b98 * _DAT_0057db24 +
           DAT_006d7b9c * _DAT_0057db34 +
           DAT_006d7ba0 * _DAT_0057db44 + _DAT_006d7ba4 * _DAT_0057db54;
      _DAT_006d7c20 =
           DAT_006d7b98 * _DAT_0057db28 +
           DAT_006d7b9c * _DAT_0057db38 +
           DAT_006d7ba0 * _DAT_0057db48 + _DAT_006d7ba4 * _DAT_0057db58;
      _DAT_006d7c24 =
           DAT_006d7b98 * _DAT_0057db2c +
           DAT_006d7b9c * _DAT_0057db3c +
           DAT_006d7ba0 * _DAT_0057db4c + _DAT_006d7ba4 * _DAT_0057db5c;
      fVar12 = (float)iVar9;
      sub_41E820(((fVar12 + fVar12) * (float)_DAT_0056e020 -
                 ((float)*(int *)(iVar7 + 0x24) + (float)*(int *)(iVar7 + 0x24)) *
                 (float)_DAT_0056e588) * (float)_DAT_0056e578,&local_450);
      iVar16 = *(int *)(iVar7 + 0xc0);
      if ((*(byte *)(iVar16 + 6) & 2) == 0) {
        uVar3 = *(ushort *)(iVar16 + 0xe);
        iVar16 = *(int *)(DAT_005846ec + 0x80 +
                         *(int *)(*(int *)(DAT_00584648 + 0x4c) + *(short *)(iVar16 + 0xc) * 4) *
                         0x84);
      }
      else {
        uVar3 = *(ushort *)(iVar16 + 10);
        iVar16 = *(int *)(*(int *)(DAT_006d9dc0 + 0x10 + (uint)*(ushort *)(iVar16 + 8) * 0x154) +
                         0x80);
      }
      iVar16 = iVar16 + (uint)uVar3 * 0x20;
      iVar9 = 4;
      fVar12 = (float)((int)*(char *)(iVar16 + 2) << 5) * _DAT_0056e28c;
      fVar6 = (float)((int)*(char *)(iVar16 + 3) << 5) * _DAT_0056e28c;
      fVar5 = (float)((int)*(char *)(iVar16 + 4) << 5) * _DAT_0056e580;
      local_45c = local_450 * fVar12 + local_440 * fVar6 + local_430 * fVar5;
      local_458 = local_44c * fVar12 + local_43c * fVar6 + local_42c * fVar5;
      fVar5 = local_428 * fVar5;
      fVar6 = local_438 * fVar6;
      fVar12 = local_448 * fVar12;
      pfVar10 = &local_4a0;
      do {
        iVar9 = iVar9 + -1;
        *pfVar10 = *pfVar10 -
                   (local_45c * pfVar10[-1] + (fVar12 + fVar6 + fVar5) * pfVar10[1]) / local_458;
        pfVar10 = pfVar10 + 3;
      } while (iVar9 != 0);
      iVar16 = 4;
      fVar12 = SQRT(local_4a0 * local_4a0 + local_49c * local_49c + 1.0);
      pfVar10 = &local_4a0;
      do {
        iVar16 = iVar16 + -1;
        pfVar10[-1] = (pfVar10[-1] * _DAT_0056e184) / fVar12;
        *pfVar10 = (*pfVar10 * _DAT_0056e184) / fVar12;
        pfVar10[1] = (pfVar10[1] * _DAT_0056e184) / fVar12;
        pfVar10 = pfVar10 + 3;
      } while (iVar16 != 0);
      if (DAT_006d7c69 == '\0') {
        uVar11 = *(int *)(iVar7 + 0x10c) << 7;
      }
      else {
        uVar11 = *(int *)(iVar7 + 0x10c) * 0xff;
      }
      local_4bc = 0;
      pfVar20 = local_410 + 1;
      pfVar10 = &local_4a0;
      pfVar23 = local_388;
      local_4c0 = 4;
      puVar2 = (ushort *)(DAT_00581154 + (uint)*(ushort *)(iVar7 + 0x128) * 0x14);
      do {
        pfVar1 = pfVar23 + -2;
        *pfVar1 = _DAT_006d7bf8 * *pfVar10 +
                  _DAT_006d7c08 * pfVar10[1] + _DAT_006d7be8 * pfVar10[-1] + _DAT_006d7c18;
        pfVar23[-1] = _DAT_006d7bec * pfVar10[-1] +
                      _DAT_006d7bfc * *pfVar10 + _DAT_006d7c0c * pfVar10[1] + _DAT_006d7c1c;
        *pfVar23 = _DAT_006d7bf0 * pfVar10[-1] +
                   _DAT_006d7c00 * *pfVar10 + _DAT_006d7c10 * pfVar10[1] + _DAT_006d7c20;
        pfVar23[1] = _DAT_006d7bf4 * pfVar10[-1] +
                     _DAT_006d7c04 * *pfVar10 + _DAT_006d7c14 * pfVar10[1] + _DAT_006d7c24;
        fVar12 = (float)sub_401080(pfVar1);
        pfVar23[6] = fVar12;
        fVar12 = pfVar23[-1];
        fVar5 = *pfVar23;
        pfVar20[-1] = *pfVar1;
        fVar6 = pfVar23[1];
        *pfVar20 = fVar12;
        pfVar20[1] = fVar5;
        fVar12 = pfVar23[6];
        pfVar20[2] = fVar6;
        pfVar20[3] = (float)((uVar11 >> 0xc) << 0x18 | 0xffffff);
        pfVar20[4] = 0.0;
        local_4bc = local_4bc | (uint)fVar12;
        pfVar10 = pfVar10 + 3;
        pfVar20 = pfVar20 + 8;
        pfVar23 = pfVar23 + 9;
        local_4c0 = local_4c0 + -1;
      } while (local_4c0 != 0);
      local_410[6] = (float)*(undefined4 *)(puVar2 + 2);
      local_410[7] = (float)*(undefined4 *)(puVar2 + 6);
      local_3d8 = *(undefined4 *)(puVar2 + 4);
      local_3d4 = *(undefined4 *)(puVar2 + 6);
      local_3b8 = *(undefined4 *)(puVar2 + 4);
      local_3b4 = *(undefined4 *)(puVar2 + 8);
      local_398 = *(undefined4 *)(puVar2 + 2);
      local_394 = *(undefined4 *)(puVar2 + 8);
      pfVar10 = local_410 + 3;
      iVar16 = 4;
      fVar12 = _DAT_0056e00c;
      do {
        if (fVar12 < *pfVar10) {
          fVar12 = *pfVar10;
        }
        pfVar10 = pfVar10 + 8;
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
      iVar9 = sub_439F20(local_300,local_410,4,local_4bc);
      puVar13 = (undefined4 *)sub_41ED90(iVar9 << 5);
      iVar16 = DAT_006d9e28;
      if (puVar13 == (undefined4 *)0x0) goto LAB_00556264;
      if (0 < iVar9) {
        puVar14 = puVar13;
        iVar16 = iVar9;
        do {
          iVar16 = iVar16 + -1;
          puVar21 = (undefined4 *)(((int)local_300 - (int)puVar13) + (int)puVar14);
          puVar24 = puVar14;
          for (iVar18 = 8; iVar18 != 0; iVar18 = iVar18 + -1) {
            *puVar24 = *puVar21;
            puVar21 = puVar21 + 1;
            puVar24 = puVar24 + 1;
          }
          puVar14 = puVar14 + 8;
        } while (iVar16 != 0);
      }
      uVar11 = *puVar2 >> 8 & 7;
      iVar16 = ((*puVar2 & 0x7000) >> 0xc) + uVar11 * 4;
      if (*(uint *)(iVar7 + 0x10c) < 0x1000) {
        iVar16 = uVar11 + iVar16;
        uVar11 = (&DAT_005740a0)[iVar16 * 3];
        uVar19 = (&DAT_005740a4)[iVar16 * 3];
      }
      else {
        iVar16 = uVar11 + iVar16;
        uVar11 = (&DAT_00573ef8)[iVar16 * 3];
        uVar19 = (&DAT_00573efc)[iVar16 * 3];
      }
      if ((DAT_005833e4._1_1_ != '\0') && ((uVar11 != 0 || (DAT_00573d36 != '\0')))) {
        if ((iVar15 < local_4a8) && ((DAT_005f6ee8 & 1) != 0)) {
          iVar15 = 1;
        }
        else {
          iVar15 = 0;
        }
        iVar18 = __ftol();
        if (iVar18 < 0) {
          iVar18 = 0;
        }
        else if (0x7ff < iVar18) {
          iVar18 = 0x7ff;
        }
        if (iVar15 != -1) {
          if ((char)puVar2[1] == -1) {
            iVar25 = 0;
          }
          else {
            iVar25 = (char)puVar2[1] * 0x20 + DAT_0058114c;
          }
          iVar16 = DAT_006d9e28;
          if ((0 < iVar9) &&
             (puVar14 = (undefined4 *)sub_41ED90(0x20), iVar16 = DAT_006d9e28,
             puVar14 != (undefined4 *)0x0)) {
            iVar18 = iVar15 * 0x800 + iVar18;
            *puVar14 = (&DAT_005f6ef8)[iVar18];
            puVar14[1] = puVar13;
            puVar14[2] = iVar9;
            puVar14[3] = 0;
            puVar14[4] = 0;
            puVar14[5] = iVar25;
            puVar14[6] = 0;
            puVar14[7] = (uVar19 << 2 | uVar11) << 0xc | 0xdf;
            (&DAT_005f6ef8)[iVar18] = puVar14;
            iVar16 = DAT_006d9e28;
          }
          goto LAB_00556264;
        }
      }
      if ((char)puVar2[1] == -1) {
        iVar15 = 0;
      }
      else {
        iVar15 = (char)puVar2[1] * 0x20 + DAT_0058114c;
      }
      iVar16 = DAT_006d9e28;
      if (iVar9 < 1) goto LAB_00556264;
      if (DAT_005833e1 != '\0') {
        if (iVar15 == 0) {
          uVar22 = 0;
        }
        else {
          uVar22 = *(undefined4 *)(iVar15 + 0x1c);
        }
        pcVar17 = sub_4C6CD0;
        if (DAT_00583380 == '\0') {
          pcVar17 = sub_442BD0;
        }
        (*pcVar17)(DAT_0058331c,DAT_005832f0,uVar22,DAT_00583308 >> 1,DAT_00583374,puVar13,iVar9,1,0
                   ,(uVar11 * 4 | uVar19) << 5 | 7);
        iVar16 = DAT_006d9e28;
        goto LAB_00556264;
      }
      if (iVar15 == 0) {
        if (DAT_006d7c58 != 1) {
          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
          DAT_006d7c58 = 1;
        }
      }
      else {
        if (DAT_006d7c54 != *(int *)(iVar15 + 0x10)) {
          (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(iVar15 + 0x10));
          DAT_006d7c54 = *(int *)(iVar15 + 0x10);
        }
        if (DAT_006d7c58 != (-(uint)(DAT_005833f0 != '\0') & 2) + 2) {
          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,(-(DAT_005833f0 != '\0') & 2U) + 2);
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
      if (DAT_006d7c38 != '\x01') {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,1);
        DAT_006d7c38 = '\x01';
      }
      if ((DAT_006d7c6e == '\0') || ((uVar19 & 2) != 0)) {
        cVar8 = '\0';
      }
      else {
        cVar8 = '\x01';
      }
      if (DAT_006d7c4e != cVar8) {
        if ((DAT_006d7c6e == '\0') || ((uVar19 & 2) != 0)) {
          uVar22 = 0;
        }
        else {
          uVar22 = 1;
        }
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar22);
        if ((DAT_006d7c6e == '\0') || (DAT_006d7c4e = '\x01', (uVar19 & 2) != 0)) {
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
      if ((bool)DAT_006d7c3a != (DAT_006d7c70 != '\0')) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,DAT_006d7c70 != '\0');
        DAT_006d7c3a = DAT_006d7c70 != '\0';
      }
      if (DAT_006d7c50 != (-(uint)(DAT_005833e4._3_1_ != '\0') & 0x10)) {
        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,-(DAT_005833e4._3_1_ != '\0') & 0x10);
        DAT_006d7c50 = -(uint)(DAT_005833e4._3_1_ != '\0') & 0x10;
      }
      switch(uVar11) {
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
        iVar16 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
        if (DAT_006d7c40 != iVar16) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar16);
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
        goto joined_r0x00556172;
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
joined_r0x00556172:
        if (DAT_006d7c44 != 2) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
          DAT_006d7c44 = 2;
        }
      }
      switch(uVar19) {
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
      if ((DAT_005833e4._3_1_ == '\0') && (0 < iVar9)) {
        pfVar10 = (float *)(puVar13 + 2);
        iVar16 = iVar9;
        do {
          fVar12 = _DAT_0056e00c;
          if (_DAT_0056e28c < *pfVar10) {
            fVar12 = *pfVar10 - _DAT_0056e28c;
          }
          *pfVar10 = fVar12;
          pfVar10 = pfVar10 + 8;
          iVar16 = iVar16 + -1;
        } while (iVar16 != 0);
      }
      (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,puVar13,iVar9,0x1c);
      iVar16 = DAT_006d9e28;
LAB_00556264:
    }
  }
  return;
}

