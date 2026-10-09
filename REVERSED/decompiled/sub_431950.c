/* sub_431950 @ 00431950   2159 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_431950(void)

{
  float *pfVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  code *pcVar11;
  undefined *puVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined *puVar15;
  undefined4 *puVar16;
  int local_39c;
  int local_394;
  uint local_390;
  float local_380 [32];
  undefined4 local_300 [192];
  
  local_394 = 0;
  do {
    iVar4 = local_394 * 0x42c;
    if ((&DAT_005fd594)[local_394 * 0x10b] != 0) {
      DAT_005ff07c = &DAT_005fd180 + iVar4;
      DAT_005ff078 = &DAT_005fd270 + iVar4;
      DAT_005ff0b0 = (&DAT_005fd590)[local_394 * 0x10b];
      DAT_005ff0ac = &DAT_005fd540 + iVar4;
      iVar4 = 0x14 - DAT_005ff0b0;
      local_390 = 0;
      if (iVar4 < 0x14) {
        iVar13 = iVar4 * 0x24;
        local_39c = iVar4 * 0xc;
        iVar4 = iVar4 * 4;
        do {
          uVar5 = *(uint *)(DAT_005ff0ac + iVar4);
          if ((uint)(DAT_005724d4 * 0x280000) < (uVar5 & 0xff0000)) {
            uVar5 = uVar5 + DAT_005724d4 * -0x280000;
          }
          else {
            uVar5 = uVar5 & 0xffff;
          }
          *(uint *)(DAT_005ff0ac + iVar4) = uVar5;
          uVar5 = *(uint *)(DAT_005ff0ac + iVar4);
          if ((uint)(DAT_005724d4 * 0x2800) < (uVar5 & 0xff00)) {
            uVar5 = uVar5 + DAT_005724d4 * -0x2800;
          }
          else {
            uVar5 = uVar5 & 0xff00ff;
          }
          *(uint *)(DAT_005ff0ac + iVar4) = uVar5;
          uVar5 = *(uint *)(DAT_005ff0ac + iVar4);
          if ((uint)(DAT_005724d4 * 0x28) < (uVar5 & 0xff)) {
            uVar5 = uVar5 + DAT_005724d4 * -0x28;
          }
          else {
            uVar5 = uVar5 & 0xffff00;
          }
          *(uint *)(DAT_005ff0ac + iVar4) = uVar5;
          pfVar7 = (float *)(DAT_005ff078 + iVar13);
          pfVar1 = (float *)(DAT_005ff07c + local_39c);
          *pfVar7 = _DAT_0057db30 * pfVar1[1] +
                    _DAT_0057db20 * *(float *)(DAT_005ff07c + local_39c) +
                    _DAT_0057db40 * *(float *)(DAT_005ff07c + local_39c + 8) + _DAT_0057db50;
          pfVar7[1] = _DAT_0057db34 * pfVar1[1] +
                      _DAT_0057db24 * *pfVar1 + _DAT_0057db44 * pfVar1[2] + _DAT_0057db54;
          pfVar7[2] = _DAT_0057db38 * pfVar1[1] +
                      _DAT_0057db28 * *pfVar1 + _DAT_0057db48 * pfVar1[2] + _DAT_0057db58;
          pfVar7[3] = _DAT_0057db3c * pfVar1[1] +
                      _DAT_0057db2c * *pfVar1 + _DAT_0057db4c * pfVar1[2] + _DAT_0057db5c;
          puVar12 = DAT_005ff078 + iVar13;
          uVar6 = sub_401080(puVar12);
          *(undefined4 *)(puVar12 + 0x20) = uVar6;
          iVar4 = iVar4 + 4;
          local_39c = local_39c + 0xc;
          iVar10 = iVar13 + 0x20;
          iVar13 = iVar13 + 0x24;
          local_390 = local_390 | *(uint *)(DAT_005ff078 + iVar10);
        } while (iVar4 < 0x50);
      }
      local_39c = 0x16 - DAT_005ff0b0;
      if (local_39c < 0x12) {
        uVar5 = 0;
        pfVar7 = local_380 + 1;
        puVar12 = DAT_005ff0ac;
        puVar15 = DAT_005ff078;
LAB_00431b96:
        do {
          iVar4 = local_39c + ((int)uVar5 >> 1 & 1U ^ uVar5);
          pfVar7[-1] = *(float *)(puVar15 + iVar4 * 0x24);
          *pfVar7 = *(float *)(puVar15 + iVar4 * 0x24 + 4);
          pfVar7[1] = *(float *)(puVar15 + iVar4 * 0x24 + 8);
          pfVar7[2] = *(float *)(puVar15 + iVar4 * 0x24 + 0xc);
          pfVar7[3] = (float)(*(uint *)(puVar12 + iVar4 * 4) | 0xff000000);
          pfVar7[4] = 0.0;
          uVar5 = uVar5 + 1;
          pfVar7 = pfVar7 + 8;
        } while ((int)uVar5 < 4);
        pfVar7 = local_380 + 3;
        iVar4 = 4;
        fVar2 = _DAT_0056e00c;
        do {
          if (fVar2 < *pfVar7) {
            fVar2 = *pfVar7;
          }
          pfVar7 = pfVar7 + 8;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        iVar4 = sub_439F20(local_300,local_380,4,local_390);
        puVar8 = (undefined4 *)sub_41ED90(iVar4 << 5);
        if (puVar8 == (undefined4 *)0x0) goto LAB_0043218e;
        if (0 < iVar4) {
          puVar9 = puVar8;
          iVar13 = iVar4;
          do {
            iVar13 = iVar13 + -1;
            puVar14 = (undefined4 *)(((int)local_300 - (int)puVar8) + (int)puVar9);
            puVar16 = puVar9;
            for (iVar10 = 8; iVar10 != 0; iVar10 = iVar10 + -1) {
              *puVar16 = *puVar14;
              puVar14 = puVar14 + 1;
              puVar16 = puVar16 + 1;
            }
            puVar9 = puVar9 + 8;
          } while (iVar13 != 0);
        }
        uVar3 = DAT_0057407c;
        iVar10 = DAT_00574078;
        iVar13 = DAT_00573ed4;
        uVar5 = DAT_00573ed0;
        if ((DAT_005833e4._1_1_ != '\0') && ((DAT_00573ed0 != 0 || (DAT_00573d36 != '\0')))) {
          iVar10 = __ftol();
          if (iVar10 < 0) {
            iVar10 = 0;
          }
          else if (0x7ff < iVar10) {
            iVar10 = 0x7ff;
          }
          if ((0 < iVar4) && (puVar9 = (undefined4 *)sub_41ED90(0x20), puVar9 != (undefined4 *)0x0))
          {
            uVar6 = (&DAT_005f6ef8)[iVar10];
            puVar9[1] = puVar8;
            *puVar9 = uVar6;
            puVar9[3] = 0;
            puVar9[2] = iVar4;
            puVar9[4] = 0;
            puVar9[5] = 0;
            puVar9[6] = 0;
            puVar9[7] = (iVar13 * 4 | uVar5) << 0xc | 0x43;
            (&DAT_005f6ef8)[iVar10] = puVar9;
          }
          goto LAB_0043218e;
        }
        if (iVar4 < 1) goto LAB_0043218e;
        if (DAT_005833e1 != '\0') {
          pcVar11 = sub_4C6CD0;
          if (DAT_00583380 == '\0') {
            pcVar11 = sub_442BD0;
          }
          (*pcVar11)(DAT_0058331c,DAT_005832f0,0,DAT_00583308 >> 1,DAT_00583374,puVar8,iVar4,1,0,
                     (DAT_00574078 * 4 | DAT_0057407c) << 5 | 0x211);
          goto LAB_0043218e;
        }
        if (DAT_006d7c58 != 1) {
          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
          DAT_006d7c58 = 1;
        }
        if (DAT_006d7c34 != (DAT_005833f2 != '\0') + 1) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,(DAT_005833f2 != '\0') + '\x01');
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
        if ((bool)DAT_006d7c39 != (DAT_005833e4._2_1_ == '\0')) {
          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,DAT_005833e4._2_1_ == '\0');
          DAT_006d7c39 = DAT_005833e4._2_1_ == '\0';
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
        switch(iVar10) {
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
          iVar13 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
          if (DAT_006d7c40 != iVar13) {
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar13);
            DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
          }
          iVar13 = 6;
          if (DAT_006d7c44 == 6) break;
          goto LAB_004320e4;
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
          goto joined_r0x004320e2;
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
joined_r0x004320e2:
          iVar13 = 2;
          if (DAT_006d7c44 != 2) {
LAB_004320e4:
            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,iVar13);
            DAT_006d7c44 = iVar13;
          }
        }
        switch(uVar3) {
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
        (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,puVar8,iVar4,0x1c);
LAB_0043218e:
        local_39c = local_39c + 2;
        if (local_39c < 0x12) {
          uVar5 = 0;
          pfVar7 = local_380 + 1;
          puVar12 = DAT_005ff0ac;
          puVar15 = DAT_005ff078;
          goto LAB_00431b96;
        }
      }
    }
    local_394 = local_394 + 1;
    if (3 < local_394) {
      return;
    }
  } while( true );
}

