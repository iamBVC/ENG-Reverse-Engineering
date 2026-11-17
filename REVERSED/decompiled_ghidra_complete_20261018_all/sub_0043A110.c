/* sub_43A110 @ 0043a110   1273 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_43A110(int param_1,int param_2,int param_3,float *param_4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  float *pfVar6;
  float *pfVar7;
  uint *puVar8;
  float *pfVar9;
  uint uVar10;
  float *pfVar11;
  float10 fVar12;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST1;
  int local_10;
  int local_4;
  
  local_10 = 0;
  iVar2 = (-(uint)((~(byte)param_1 & 1) != 0) & 0xfffffffe) + 1;
  param_1 = param_1 / 2;
  pfVar9 = (float *)(param_3 * 0x20 + -0x20 + param_2);
  if (param_3 == 0) {
    return 0;
  }
  pfVar1 = (float *)(param_2 + param_1 * 4);
  puVar8 = (uint *)(param_2 + 0x10);
  local_4 = param_3;
  pfVar7 = param_4;
  param_4 = (float *)((float)iVar2 * pfVar9[param_1] - pfVar9[3]);
  do {
    fVar12 = (float10)iVar2 * (float10)*pfVar1 - (float10)(float)puVar8[-1];
    if ((float10)_DAT_0056e00c < fVar12) {
      if ((float)param_4 < _DAT_0056e00c) {
        fVar12 = (float10)(float)param_4 / ((float10)(float)param_4 - fVar12);
        *pfVar7 = (float)(((float10)(float)puVar8[-4] - (float10)*pfVar9) * fVar12 +
                         (float10)*pfVar9);
        pfVar7[1] = (float)(((float10)(float)puVar8[-3] - (float10)pfVar9[1]) * fVar12 +
                           (float10)pfVar9[1]);
        pfVar7[2] = (float)(((float10)(float)puVar8[-2] - (float10)pfVar9[2]) * fVar12 +
                           (float10)pfVar9[2]);
        pfVar7[6] = (float)(((float10)(float)puVar8[2] - (float10)pfVar9[6]) * fVar12 +
                           (float10)pfVar9[6]);
        pfVar7[7] = (float)(((float10)(float)puVar8[3] - (float10)pfVar9[7]) * fVar12 +
                           (float10)pfVar9[7]);
        pfVar7[3] = (float)(((float10)(float)puVar8[-1] - (float10)pfVar9[3]) * fVar12 +
                           (float10)pfVar9[3]);
        iVar3 = __ftol();
        if (DAT_006d7c6c == '\0') {
          if (DAT_006d7c6b == '\0') {
            uVar10 = *puVar8;
            fVar5 = pfVar9[4];
            uVar4 = (((uVar10 >> 8 & 0xff) - ((uint)fVar5 >> 8 & 0xff)) * iVar3 >> 8) +
                    ((uint)fVar5 & 0xffffff00) & 0xff00 |
                    ((uVar10 >> 0x10 & 0xff) - ((uint)fVar5 >> 0x10 & 0xff)) * iVar3 +
                    ((uint)fVar5 & 0xffff0000) & 0xff0000 |
                    (((uVar10 & 0xff) - ((uint)fVar5 & 0xff)) * iVar3 >> 0x10) + (int)fVar5 & 0xff;
            uVar10 = ((uVar10 >> 0x18) - ((uint)fVar5 >> 0x18)) * iVar3 * 0x100 +
                     ((uint)fVar5 & 0xff000000) & 0xff000000;
            goto LAB_0043a5b0;
          }
          fVar5 = (float)(((*puVar8 >> 0x18) - ((uint)pfVar9[4] >> 0x18)) * iVar3 * 0x100 +
                          ((uint)pfVar9[4] & 0xff000000) & 0xff000000);
LAB_0043a5b2:
          pfVar7[4] = fVar5;
        }
        else {
          if (DAT_006d7c6f == '\0') {
            uVar10 = *puVar8;
            fVar5 = pfVar9[4];
            uVar4 = (((uVar10 >> 8 & 0xff) - ((uint)fVar5 >> 8 & 0xff)) * iVar3 >> 8) +
                    ((uint)fVar5 & 0xffffff00) & 0xff00 |
                    ((uVar10 >> 0x10 & 0xff) - ((uint)fVar5 >> 0x10 & 0xff)) * iVar3 +
                    ((uint)fVar5 & 0xffff0000) & 0xff0000;
            uVar10 = (((uVar10 & 0xff) - ((uint)fVar5 & 0xff)) * iVar3 >> 0x10) + (int)fVar5 & 0xff;
LAB_0043a5b0:
            fVar5 = (float)(uVar4 | uVar10);
            goto LAB_0043a5b2;
          }
          pfVar7[4] = 0.0;
        }
        pfVar7[param_1] = (float)iVar2 * pfVar7[3];
        fVar12 = extraout_ST0_00;
        goto LAB_0043a5c3;
      }
    }
    else {
      if (_DAT_0056e00c < (float)param_4) {
        pfVar6 = pfVar7;
        if (fVar12 < (float10)_DAT_0056e00c) {
          fVar12 = fVar12 / (fVar12 - (float10)(float)param_4);
          *pfVar7 = (float)(((float10)*pfVar9 - (float10)(float)puVar8[-4]) * fVar12 +
                           (float10)(float)puVar8[-4]);
          pfVar7[1] = (float)(((float10)pfVar9[1] - (float10)(float)puVar8[-3]) * fVar12 +
                             (float10)(float)puVar8[-3]);
          pfVar7[2] = (float)(((float10)pfVar9[2] - (float10)(float)puVar8[-2]) * fVar12 +
                             (float10)(float)puVar8[-2]);
          pfVar7[6] = (float)(((float10)pfVar9[6] - (float10)(float)puVar8[2]) * fVar12 +
                             (float10)(float)puVar8[2]);
          pfVar7[7] = (float)(((float10)pfVar9[7] - (float10)(float)puVar8[3]) * fVar12 +
                             (float10)(float)puVar8[3]);
          iVar3 = __ftol();
          if (DAT_006d7c6c == '\0') {
            if (DAT_006d7c6b == '\0') {
              uVar10 = *puVar8;
              fVar5 = pfVar9[4];
              uVar4 = ((((uint)fVar5 >> 8 & 0xff) - (uVar10 >> 8 & 0xff)) * iVar3 >> 8) +
                      (uVar10 & 0xffffff00) & 0xff00 |
                      (((uint)fVar5 >> 0x10 & 0xff) - (uVar10 >> 0x10 & 0xff)) * iVar3 +
                      (uVar10 & 0xffff0000) & 0xff0000 |
                      ((((uint)fVar5 & 0xff) - (uVar10 & 0xff)) * iVar3 >> 0x10) + uVar10 & 0xff;
              uVar10 = (((uint)fVar5 >> 0x18) - (uVar10 >> 0x18)) * iVar3 * 0x100 +
                       (uVar10 & 0xff000000) & 0xff000000;
              goto LAB_0043a3a2;
            }
            fVar5 = (float)((((uint)pfVar9[4] >> 0x18) - (*puVar8 >> 0x18)) * iVar3 * 0x100 +
                            (*puVar8 & 0xff000000) & 0xff000000);
LAB_0043a3a4:
            pfVar7[4] = fVar5;
          }
          else {
            if (DAT_006d7c6f == '\0') {
              uVar10 = *puVar8;
              fVar5 = pfVar9[4];
              uVar4 = ((((uint)fVar5 >> 8 & 0xff) - (uVar10 >> 8 & 0xff)) * iVar3 >> 8) +
                      (uVar10 & 0xffffff00) & 0xff00 |
                      (((uint)fVar5 >> 0x10 & 0xff) - (uVar10 >> 0x10 & 0xff)) * iVar3 +
                      (uVar10 & 0xffff0000) & 0xff0000;
              uVar10 = ((((uint)fVar5 & 0xff) - (uVar10 & 0xff)) * iVar3 >> 0x10) + uVar10 & 0xff;
LAB_0043a3a2:
              fVar5 = (float)(uVar4 | uVar10);
              goto LAB_0043a3a4;
            }
            pfVar7[4] = 0.0;
          }
          pfVar6 = pfVar7 + 8;
          fVar12 = ((float10)pfVar9[3] - (float10)(float)puVar8[-1]) * extraout_ST0 +
                   (float10)(float)puVar8[-1];
          pfVar7[3] = (float)fVar12;
          pfVar7[param_1] = (float)(fVar12 * (float10)iVar2);
          local_10 = local_10 + 1;
          fVar12 = extraout_ST1;
        }
        pfVar9 = (float *)(puVar8 + -4);
        pfVar11 = pfVar6;
        for (iVar3 = 8; pfVar7 = pfVar6, iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar11 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar11 = pfVar11 + 1;
        }
      }
      else {
        pfVar9 = (float *)(puVar8 + -4);
        pfVar6 = pfVar7;
        for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar6 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar6 = pfVar6 + 1;
        }
      }
LAB_0043a5c3:
      pfVar7 = pfVar7 + 8;
      local_10 = local_10 + 1;
    }
    param_4 = (float *)(float)fVar12;
    pfVar9 = (float *)(puVar8 + -4);
    pfVar1 = pfVar1 + 8;
    puVar8 = puVar8 + 8;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return local_10;
    }
  } while( true );
}

