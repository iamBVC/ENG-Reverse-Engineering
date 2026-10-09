/* sub_414780 @ 00414780   2092 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_414780(void)

{
  short sVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  float *pfVar9;
  short *psVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  uint uVar14;
  undefined4 *puVar15;
  int local_530;
  int local_528;
  int local_524;
  float local_50c;
  float local_508;
  float local_504 [7];
  float local_4e8;
  undefined4 local_4dc [4];
  float local_4cc;
  float local_4c8;
  float local_4ac;
  float local_4a8;
  short local_48a [8];
  short local_47a [189];
  undefined4 local_300 [192];
  
  if (((((DAT_00583734 != 0) || (DAT_00583738 != 0)) || (DAT_00583740 != 0)) ||
      ((DAT_00583744 != 0 || (DAT_005ff058 != '\0')))) && (DAT_006d7c71 != '\0')) {
    if (DAT_005ff058 != '\0') {
      DAT_005ff058 = '\0';
      if (DAT_005833f7 == '\0') {
        if (DAT_005833f3 == '\0') {
          DAT_005ff058 = 0;
          return;
        }
        sub_40C340(&DAT_005ff05c,0x5ff05d,0x5ff05e,0x5ff05f);
        uVar14 = 1;
        local_524 = 1;
      }
      else {
        uVar14 = 2;
        local_524 = 0;
      }
      puVar6 = (undefined4 *)sub_41ED90(0x80);
      if (puVar6 == (undefined4 *)0x0) {
        return;
      }
      puVar6[0x1c] = DAT_005ff05c;
      puVar6[0x14] = DAT_005ff05c;
      puVar6[0xc] = DAT_005ff05c;
      puVar6[4] = DAT_005ff05c;
      puVar6[0x1d] = 0;
      puVar6[0x15] = 0;
      puVar6[0xd] = 0;
      puVar6[5] = 0;
      puVar6[0x1a] = 0;
      puVar6[0x12] = 0;
      puVar6[10] = 0;
      puVar6[2] = 0;
      puVar6[0x1b] = 0x3f800000;
      puVar6[0x13] = 0x3f800000;
      puVar6[0xb] = 0x3f800000;
      puVar6[3] = 0x3f800000;
      puVar6[0x18] = 0;
      *puVar6 = 0;
      fVar2 = (float)DAT_00583374;
      puVar6[9] = 0;
      puVar6[1] = 0;
      puVar6[0x10] = fVar2;
      puVar6[8] = fVar2;
      fVar2 = (float)DAT_00583378;
      puVar6[0x19] = fVar2;
      puVar6[0x11] = fVar2;
      puVar7 = (undefined4 *)sub_41ED90(0x20);
      if (puVar7 != (undefined4 *)0x0) {
        *puVar7 = DAT_005f6ef8;
        puVar7[1] = puVar6;
        puVar7[2] = 4;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        puVar7[7] = (local_524 * 4 | uVar14) << 0xc | 0x6d;
        DAT_005f6ef8 = puVar7;
      }
    }
    if (DAT_00583744 != 0) {
      puVar6 = (undefined4 *)sub_41ED90(0x80);
      if (puVar6 == (undefined4 *)0x0) {
        return;
      }
      puVar6[0x1d] = 0;
      puVar6[0x1c] = 0xff000000;
      puVar6[0x14] = 0xff000000;
      puVar6[0xc] = 0xff000000;
      puVar6[4] = 0xff000000;
      puVar6[0x15] = 0;
      puVar6[0xd] = 0;
      puVar6[5] = 0;
      puVar6[0x1a] = 0;
      puVar6[0x12] = 0;
      puVar6[10] = 0;
      puVar6[2] = 0;
      puVar6[0x1b] = 0x3f800000;
      puVar6[0x13] = 0x3f800000;
      puVar6[0xb] = 0x3f800000;
      puVar6[3] = 0x3f800000;
      puVar6[0x18] = 0;
      *puVar6 = 0;
      fVar2 = (float)DAT_00583374;
      puVar6[9] = 0;
      puVar6[1] = 0;
      puVar6[0x10] = fVar2;
      puVar6[8] = fVar2;
      fVar2 = (float)DAT_00583378;
      puVar6[0x19] = fVar2;
      puVar6[0x11] = fVar2;
      puVar7 = (undefined4 *)sub_41ED90(0x20);
      if (puVar7 != (undefined4 *)0x0) {
        puVar7[1] = puVar6;
        *puVar7 = DAT_005f6ef8;
        puVar7[2] = 4;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        puVar7[7] = 0x6d;
        DAT_005f6ef8 = puVar7;
      }
    }
    if (DAT_00583734 != 0) {
      puVar6 = (undefined4 *)sub_41ED90(0x80);
      if (puVar6 == (undefined4 *)0x0) {
        return;
      }
      puVar6[0x1c] = DAT_0058373c;
      puVar6[0x14] = DAT_0058373c;
      puVar6[0xc] = DAT_0058373c;
      puVar6[4] = DAT_0058373c;
      puVar6[0x1d] = 0;
      puVar6[0x15] = 0;
      puVar6[0xd] = 0;
      puVar6[5] = 0;
      puVar6[0x1a] = 0;
      puVar6[0x12] = 0;
      puVar6[10] = 0;
      puVar6[2] = 0;
      puVar6[0x1b] = 0x3f800000;
      puVar6[0x13] = 0x3f800000;
      puVar6[0xb] = 0x3f800000;
      puVar6[3] = 0x3f800000;
      puVar6[0x18] = 0;
      *puVar6 = 0;
      fVar2 = (float)DAT_00583374;
      puVar6[9] = 0;
      puVar6[1] = 0;
      puVar6[0x10] = fVar2;
      puVar6[8] = fVar2;
      fVar2 = (float)DAT_00583378;
      puVar6[0x19] = fVar2;
      puVar6[0x11] = fVar2;
      puVar7 = (undefined4 *)sub_41ED90(0x20);
      if (puVar7 != (undefined4 *)0x0) {
        puVar7[1] = puVar6;
        *puVar7 = DAT_005f6ef8;
        puVar7[2] = 4;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        puVar7[7] = 0x506d;
        DAT_005f6ef8 = puVar7;
      }
    }
    if (DAT_00583740 != 0) {
      uVar14 = ((DAT_00583724 & 0xff | DAT_00583728 << 8) << 8 | DAT_0058371c & 0xff) << 8 |
               DAT_00583720 & 0xff;
      if (DAT_006d7c6f != '\0') {
        uVar8 = DAT_00583724 * ((int)uVar14 >> 0x18) >> 8 & 0xff;
        uVar14 = ((((int)uVar14 >> 0x18) << 8 | uVar8) << 8 | uVar8) << 8 | uVar8;
      }
      puVar6 = (undefined4 *)sub_41ED90(0x80);
      if (puVar6 == (undefined4 *)0x0) {
        return;
      }
      puVar6[0x1c] = uVar14;
      puVar6[0x14] = uVar14;
      puVar6[0xc] = uVar14;
      puVar6[4] = uVar14;
      puVar6[0x1d] = 0;
      puVar6[0x15] = 0;
      puVar6[0xd] = 0;
      puVar6[5] = 0;
      puVar6[0x1a] = 0;
      puVar6[0x12] = 0;
      puVar6[10] = 0;
      puVar6[2] = 0;
      puVar6[0x1b] = 0x3f800000;
      puVar6[0x13] = 0x3f800000;
      puVar6[0xb] = 0x3f800000;
      puVar6[3] = 0x3f800000;
      puVar6[0x18] = 0;
      *puVar6 = 0;
      fVar2 = (float)DAT_00583374;
      puVar6[9] = 0;
      puVar6[1] = 0;
      puVar6[0x10] = fVar2;
      puVar6[8] = fVar2;
      fVar2 = (float)DAT_00583378;
      puVar6[0x19] = fVar2;
      puVar6[0x11] = fVar2;
      puVar7 = (undefined4 *)sub_41ED90(0x20);
      if (puVar7 != (undefined4 *)0x0) {
        puVar7[1] = puVar6;
        *puVar7 = DAT_005f6ef8;
        puVar7[2] = 4;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        puVar7[7] = 0x506d;
        DAT_005f6ef8 = puVar7;
      }
    }
    if (DAT_00583738 != 0) {
      uVar14 = 0;
      psVar10 = local_48a;
      do {
        iVar11 = (&DAT_00574318)[uVar14 & 0xfff];
        sVar1 = (short)((0x100 - DAT_0058370c) * iVar11 >> 0xd);
        psVar10[-1] = (sVar1 >> 1) + 0x100 + sVar1;
        iVar12 = (&DAT_00574318)[uVar14 + 0x400 & 0xfff];
        *psVar10 = (short)((0x100 - DAT_0058370c) * iVar12 >> 0xd) + 0x78;
        sVar1 = (short)((iVar11 << 9) >> 0xd);
        psVar10[1] = (sVar1 >> 1) + 0x100 + sVar1;
        psVar10[2] = (short)((iVar12 << 9) >> 0xd) + 0x78;
        if (DAT_0058370c < 0xc0) {
          sVar1 = (short)((0xc0 - DAT_0058370c) * iVar11 >> 0xd);
          psVar10[3] = (sVar1 >> 1) + 0x100 + sVar1;
          psVar10[4] = (short)((0xc0 - DAT_0058370c) * iVar12 >> 0xd) + 0x78;
        }
        else {
          psVar10[3] = 0x100;
          psVar10[4] = 0x78;
        }
        uVar14 = uVar14 + 0x80;
        psVar10 = psVar10 + 6;
      } while ((int)uVar14 < 0x1080);
      pfVar9 = local_504 + 1;
      iVar11 = 4;
      do {
        pfVar9[-1] = 0.0;
        *pfVar9 = 1.0;
        pfVar9[1] = -1.7014118e+38;
        pfVar9[2] = 0.0;
        pfVar9 = pfVar9 + 8;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      psVar10 = local_47a;
      local_528 = 0x20;
      do {
        fVar2 = (float)(int)psVar10[-9] * _DAT_0056e118 - _DAT_0056e008;
        fVar3 = _DAT_0056e008 - (float)(int)psVar10[-8] * _DAT_0056e1f4;
        fVar4 = (float)(int)psVar10[-3] * _DAT_0056e118 - _DAT_0056e008;
        fVar5 = _DAT_0056e008 - (float)(int)psVar10[-2] * _DAT_0056e1f4;
        local_4cc = (float)(int)psVar10[-1] * _DAT_0056e118 - _DAT_0056e008;
        puVar6 = local_4dc;
        local_4c8 = _DAT_0056e008 - (float)(int)*psVar10 * _DAT_0056e1f4;
        iVar11 = 2;
        local_4ac = (float)(int)psVar10[-7] * _DAT_0056e118 - _DAT_0056e008;
        local_4a8 = _DAT_0056e008 - (float)(int)psVar10[-6] * _DAT_0056e1f4;
        do {
          *puVar6 = 0xff000000;
          puVar6 = puVar6 + 8;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        local_50c = fVar2;
        local_508 = fVar3;
        local_504[6] = fVar4;
        local_4e8 = fVar5;
        iVar11 = sub_439F20(local_300,&local_50c,4,0xf);
        puVar6 = (undefined4 *)sub_41ED90(iVar11 << 5);
        if (iVar11 != 0) {
          puVar7 = puVar6;
          local_530 = iVar11;
          do {
            puVar13 = (undefined4 *)(((int)local_300 - (int)puVar6) + (int)puVar7);
            puVar15 = puVar7;
            for (iVar12 = 8; iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar15 = *puVar13;
              puVar13 = puVar13 + 1;
              puVar15 = puVar15 + 1;
            }
            local_530 = local_530 + -1;
            puVar7 = puVar7 + 8;
          } while (local_530 != 0);
          if ((0 < iVar11) && (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)
             ) {
            *puVar7 = DAT_005f6ef8;
            puVar7[1] = puVar6;
            puVar7[2] = iVar11;
            puVar7[3] = 0;
            puVar7[4] = 0;
            puVar7[5] = 0;
            puVar7[6] = 0;
            puVar7[7] = 0x506d;
            DAT_005f6ef8 = puVar7;
          }
        }
        local_504[6] = (float)(int)psVar10[-5] * _DAT_0056e118 - _DAT_0056e008;
        puVar6 = local_4dc;
        local_4e8 = _DAT_0056e008 - (float)(int)psVar10[-4] * _DAT_0056e1f4;
        iVar11 = 2;
        local_4cc = (float)(int)psVar10[1] * _DAT_0056e118 - _DAT_0056e008;
        local_4c8 = _DAT_0056e008 - (float)(int)psVar10[2] * _DAT_0056e1f4;
        local_4ac = fVar4;
        local_4a8 = fVar5;
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 8;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        local_50c = fVar2;
        local_508 = fVar3;
        iVar11 = sub_439F20(local_300,&local_50c,4,0xf);
        puVar6 = (undefined4 *)sub_41ED90(iVar11 << 5);
        if (iVar11 != 0) {
          puVar7 = puVar6;
          local_530 = iVar11;
          do {
            puVar13 = (undefined4 *)((int)puVar7 + ((int)local_300 - (int)puVar6));
            puVar15 = puVar7;
            for (iVar12 = 8; iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar15 = *puVar13;
              puVar13 = puVar13 + 1;
              puVar15 = puVar15 + 1;
            }
            local_530 = local_530 + -1;
            puVar7 = puVar7 + 8;
          } while (local_530 != 0);
          if ((0 < iVar11) && (puVar7 = (undefined4 *)sub_41ED90(0x20), puVar7 != (undefined4 *)0x0)
             ) {
            *puVar7 = DAT_005f6ef8;
            puVar7[1] = puVar6;
            puVar7[2] = iVar11;
            puVar7[3] = 0;
            puVar7[4] = 0;
            puVar7[5] = 0;
            puVar7[6] = 0;
            puVar7[7] = 0x5063;
            DAT_005f6ef8 = puVar7;
          }
        }
        psVar10 = psVar10 + 6;
        local_528 = local_528 + -1;
      } while (local_528 != 0);
    }
  }
  return;
}

