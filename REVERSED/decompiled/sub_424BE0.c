/* sub_424BE0 @ 00424be0   2276 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_424BE0(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  code *pcVar10;
  undefined4 uVar11;
  int iVar12;
  float *pfVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  undefined4 uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  int local_18;
  int local_14;
  
  local_14 = 2;
  do {
    local_18 = 0x7ff;
    do {
      iVar7 = local_18 + local_14 * 0x800;
      for (puVar1 = (undefined4 *)(&DAT_005f6ef8)[iVar7]; puVar1 != (undefined4 *)0x0;
          puVar1 = (undefined4 *)*puVar1) {
        uVar8 = puVar1[7];
        uVar14 = (int)uVar8 >> 0xe;
        uVar15 = (int)uVar8 >> 0xc & 3;
        uVar16 = uVar8 & 0x80;
        uVar17 = uVar8 & 0x10;
        uVar21 = uVar8 & 0x40;
        uVar18 = uVar8 & 2;
        uVar23 = uVar8 & 0x20;
        iVar9 = puVar1[6];
        iVar12 = puVar1[5];
        uVar19 = puVar1[4];
        iVar2 = puVar1[3];
        iVar3 = puVar1[2];
        iVar4 = puVar1[1];
        uVar20 = uVar8 & 4;
        uVar22 = uVar8 & 8;
        uVar8 = uVar8 & 1;
        if (0 < iVar3) {
          if (DAT_005833e1 == '\0') {
            if (iVar12 == 0) {
              if (DAT_006d7c58 != 1) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                DAT_006d7c58 = 1;
              }
            }
            else {
              if ((iVar9 != 0) && (*(int *)(iVar12 + 0x14) != iVar9)) {
                (**(code **)(**(int **)(iVar12 + 0xc) + 0x7c))
                          (*(int **)(iVar12 + 0xc),*(undefined4 *)(iVar9 + 0x10));
                *(int *)(iVar12 + 0x14) = iVar9;
              }
              if (DAT_006d7c54 != *(int *)(iVar12 + 0x10)) {
                (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(iVar12 + 0x10));
                DAT_006d7c54 = *(int *)(iVar12 + 0x10);
              }
              if ((uVar18 == 0) || (iVar9 = 4, DAT_005833f0 == '\0')) {
                iVar9 = 2;
              }
              if (DAT_006d7c58 != iVar9) {
                if ((uVar18 == 0) || (uVar11 = 4, DAT_005833f0 == '\0')) {
                  uVar11 = 2;
                }
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,uVar11);
                if ((uVar18 == 0) || (DAT_005833f0 == '\0')) {
                  DAT_006d7c58 = 2;
                }
                else {
                  DAT_006d7c58 = 4;
                }
              }
            }
            if ((uVar22 != 0) || (iVar9 = 2, DAT_005833f2 == '\0')) {
              iVar9 = 1;
            }
            if (DAT_006d7c34 != iVar9) {
              if ((uVar22 != 0) || (uVar11 = 2, DAT_005833f2 == '\0')) {
                uVar11 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,uVar11);
              if ((uVar22 != 0) || (DAT_006d7c34 = 2, DAT_005833f2 == '\0')) {
                DAT_006d7c34 = 1;
              }
            }
            if ((_DAT_006d7c38 & 0xff) != uVar20) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar20);
              _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)uVar20);
            }
            if (((uVar17 == 0) || (DAT_006d7c6e == '\0')) || ((uVar14 & 2) != 0)) {
              cVar6 = '\0';
            }
            else {
              cVar6 = '\x01';
            }
            if (DAT_006d7c4e != cVar6) {
              if (((uVar17 == 0) || (DAT_006d7c6e == '\0')) || ((uVar14 & 2) != 0)) {
                uVar11 = 0;
              }
              else {
                uVar11 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar11);
              if (((uVar17 == 0) || (DAT_006d7c6e == '\0')) ||
                 (DAT_006d7c4e = '\x01', (uVar14 & 2) != 0)) {
                DAT_006d7c4e = '\0';
              }
            }
            if (((uVar23 == 0) || (uVar21 == 0)) || (DAT_005833e4._2_1_ == '\0')) {
              uVar18 = 1;
            }
            else {
              uVar18 = 0;
            }
            if ((_DAT_006d7c30 & 0xff) != uVar18) {
              if (((uVar23 == 0) || (uVar21 == 0)) || (DAT_005833e4._2_1_ == '\0')) {
                uVar11 = 1;
              }
              else {
                uVar11 = 0;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,uVar11);
              if (((uVar23 == 0) || (uVar21 == 0)) ||
                 (_DAT_006d7c30 = _DAT_006d7c30 & 0xffffff00, DAT_005833e4._2_1_ == '\0')) {
                _DAT_006d7c30 = CONCAT31(DAT_006d7c30_1,1);
              }
            }
            if ((uVar21 == 0) || (DAT_005833e4._2_1_ == '\0')) {
              uVar18 = 1;
            }
            else {
              uVar18 = 0;
            }
            if ((_DAT_006d7c38 >> 8 & 0xff) != uVar18) {
              if ((uVar21 == 0) || (DAT_005833e4._2_1_ == '\0')) {
                uVar11 = 1;
              }
              else {
                uVar11 = 0;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,uVar11);
              if (uVar21 != 0) {
                _DAT_006d7c38 = (ushort)DAT_006d7c38;
                if (DAT_005833e4._2_1_ != '\0') goto LAB_0042502f;
              }
              _DAT_006d7c38 = CONCAT11(1,DAT_006d7c38);
            }
LAB_0042502f:
            iVar9 = (-(uint)(uVar23 != 0) & 4) + 4;
            if (DAT_006d7c48 != iVar9) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,iVar9);
              DAT_006d7c48 = iVar9;
            }
            if ((uVar17 == 0) || (DAT_006d7c70 == '\0')) {
              uVar18 = 0;
            }
            else {
              uVar18 = 1;
            }
            if ((_DAT_006d7c38 >> 0x10 & 0xff) != uVar18) {
              if ((uVar17 == 0) || (DAT_006d7c70 == '\0')) {
                uVar11 = 0;
              }
              else {
                uVar11 = 1;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar11);
              if (uVar17 != 0) {
                _DAT_006d7c38 = CONCAT12(1,_DAT_006d7c38);
                if (DAT_006d7c70 != '\0') goto LAB_004250bb;
              }
              _DAT_006d7c38 = (uint3)_DAT_006d7c38;
            }
LAB_004250bb:
            if ((DAT_005833e4._3_1_ == '\0') || (uVar16 == 0)) {
              iVar9 = 0;
            }
            else {
              iVar9 = 0x10;
            }
            if (DAT_006d7c50 != iVar9) {
              if ((DAT_005833e4._3_1_ == '\0') || (uVar16 == 0)) {
                uVar11 = 0;
              }
              else {
                uVar11 = 0x10;
              }
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,uVar11);
              if ((DAT_005833e4._3_1_ == '\0') || (DAT_006d7c50 = 0x10, uVar16 == 0)) {
                DAT_006d7c50 = 0;
              }
            }
            switch(uVar15) {
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
              iVar9 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
              if (DAT_006d7c40 != iVar9) {
                (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar9);
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
            iVar9 = 3;
            switch(uVar14 & 3) {
            case 0:
            case 2:
              if (DAT_006d7c5c != 2) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                DAT_006d7c5c = 2;
              }
              break;
            case 1:
              if (DAT_006d7c5c != 3) {
                uVar11 = 3;
                iVar12 = *DAT_00582cd4;
LAB_004253c5:
                (**(code **)(iVar12 + 0xa0))(DAT_00582cd4,0,4,uVar11);
                DAT_006d7c5c = iVar9;
              }
              break;
            case 3:
              iVar9 = 4;
              if (DAT_006d7c5c != 4) {
                uVar11 = 4;
                iVar12 = *DAT_00582cd4;
                goto LAB_004253c5;
              }
            }
            if (((uVar16 != 0) && (DAT_005833e4._3_1_ == '\0')) && (0 < iVar3)) {
              pfVar13 = (float *)(iVar4 + 8);
              iVar9 = iVar3;
              do {
                fVar5 = _DAT_0056e00c;
                if (_DAT_0056e28c < *pfVar13) {
                  fVar5 = *pfVar13 - _DAT_0056e28c;
                }
                *pfVar13 = fVar5;
                pfVar13 = pfVar13 + 8;
                iVar9 = iVar9 + -1;
              } while (iVar9 != 0);
            }
            if (iVar2 == 0) {
              (**(code **)(*DAT_00582cd4 + 0x70))
                        (DAT_00582cd4,(-(uVar8 != 0) & 2U) + 4,0x1c4,iVar4,iVar3,0x1c);
            }
            else {
              (**(code **)(*DAT_00582cd4 + 0x74))
                        (DAT_00582cd4,(-(uVar8 != 0) & 2U) + 4,0x1c4,iVar4,iVar3,iVar2,uVar19);
            }
          }
          else {
            if (iVar12 == 0) {
              uVar19 = 0;
            }
            else {
              uVar19 = *(undefined4 *)(iVar12 + 0x1c);
            }
            pcVar10 = sub_4C6CD0;
            if (DAT_00583380 == '\0') {
              pcVar10 = sub_442BD0;
            }
            (*pcVar10)(DAT_0058331c,DAT_005832f0,uVar19,DAT_00583308 >> 1,DAT_00583374,iVar4,iVar3,
                       uVar8,iVar9,
                       (uVar15 * 4 | uVar14 & 3) << 5 | (-(uint)(uVar20 != 0) & 0xfffffe00) + 0x200
                       | (uint)(uVar18 != 0) | -(uint)(uVar22 != 0) & 2 | -(uint)(uVar17 != 0) & 4 |
                       -(uint)(uVar23 != 0) & 8 | -(uint)(uVar21 != 0) & 0x10);
          }
        }
      }
      (&DAT_005f6ef8)[iVar7] = 0;
      local_18 = local_18 + -1;
    } while (-1 < local_18);
    local_14 = local_14 + -1;
    if (local_14 < 0) {
      return;
    }
  } while( true );
}

