/* sub_439BC0 @ 00439bc0   860 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_439BC0(int param_1,int param_2,int param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float10 fVar11;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST1;
  int local_10;
  int local_4;
  
  local_10 = 0;
  iVar4 = (-(uint)((~(byte)param_1 & 1) != 0) & 0xfffffffe) + 1;
  param_1 = param_1 / 2;
  pfVar9 = (float *)(param_3 * 0x20 + -0x20 + param_2);
  if (param_3 == 0) {
    return 0;
  }
  pfVar3 = (float *)(param_2 + param_1 * 4);
  pfVar8 = (float *)(param_2 + 8);
  local_4 = param_3;
  pfVar7 = param_4;
  param_4 = (float *)((float)iVar4 * pfVar9[param_1] - pfVar9[3]);
  do {
    fVar11 = (float10)iVar4 * (float10)*pfVar3 - (float10)pfVar8[1];
    if ((float10)_DAT_0056e00c < fVar11) {
      if ((float)param_4 < _DAT_0056e00c) {
        fVar11 = (float10)(float)param_4 / ((float10)(float)param_4 - fVar11);
        *pfVar7 = (float)(((float10)pfVar8[-2] - (float10)*pfVar9) * fVar11 + (float10)*pfVar9);
        pfVar7[1] = (float)(((float10)pfVar8[-1] - (float10)pfVar9[1]) * fVar11 + (float10)pfVar9[1]
                           );
        pfVar7[2] = (float)(((float10)*pfVar8 - (float10)pfVar9[2]) * fVar11 + (float10)pfVar9[2]);
        pfVar7[6] = (float)(((float10)pfVar8[4] - (float10)pfVar9[6]) * fVar11 + (float10)pfVar9[6])
        ;
        pfVar7[7] = (float)(((float10)pfVar8[5] - (float10)pfVar9[7]) * fVar11 + (float10)pfVar9[7])
        ;
        pfVar7[3] = (float)(((float10)pfVar8[1] - (float10)pfVar9[3]) * fVar11 + (float10)pfVar9[3])
        ;
        iVar5 = __ftol();
        fVar1 = pfVar8[2];
        fVar2 = pfVar9[4];
        pfVar7[4] = (float)(((((uint)fVar1 >> 8 & 0xff) - ((uint)fVar2 >> 8 & 0xff)) * iVar5 >> 8) +
                            ((uint)fVar2 & 0xffffff00) & 0xff00 |
                            (((uint)fVar1 >> 0x10 & 0xff) - ((uint)fVar2 >> 0x10 & 0xff)) * iVar5 +
                            ((uint)fVar2 & 0xffff0000) & 0xff0000 |
                            (((uint)fVar1 >> 0x18) - ((uint)fVar2 >> 0x18)) * iVar5 * 0x100 +
                            ((uint)fVar2 & 0xff000000) & 0xff000000 |
                           ((((uint)fVar1 & 0xff) - ((uint)fVar2 & 0xff)) * iVar5 >> 0x10) +
                           (int)fVar2 & 0xff);
        pfVar7[param_1] = (float)iVar4 * pfVar7[3];
        fVar11 = extraout_ST0_00;
        goto LAB_00439ed6;
      }
    }
    else {
      if (_DAT_0056e00c < (float)param_4) {
        pfVar6 = pfVar7;
        if (fVar11 < (float10)_DAT_0056e00c) {
          fVar11 = fVar11 / (fVar11 - (float10)(float)param_4);
          *pfVar7 = (float)(((float10)*pfVar9 - (float10)pfVar8[-2]) * fVar11 + (float10)pfVar8[-2])
          ;
          pfVar7[1] = (float)(((float10)pfVar9[1] - (float10)pfVar8[-1]) * fVar11 +
                             (float10)pfVar8[-1]);
          pfVar7[2] = (float)(((float10)pfVar9[2] - (float10)*pfVar8) * fVar11 + (float10)*pfVar8);
          pfVar7[6] = (float)(((float10)pfVar9[6] - (float10)pfVar8[4]) * fVar11 +
                             (float10)pfVar8[4]);
          pfVar7[7] = (float)(((float10)pfVar9[7] - (float10)pfVar8[5]) * fVar11 +
                             (float10)pfVar8[5]);
          iVar5 = __ftol();
          fVar1 = pfVar8[2];
          fVar2 = pfVar9[4];
          pfVar6 = pfVar7 + 8;
          pfVar7[4] = (float)(((((uint)fVar2 >> 8 & 0xff) - ((uint)fVar1 >> 8 & 0xff)) * iVar5 >> 8)
                              + ((uint)fVar1 & 0xffffff00) & 0xff00 |
                              (((uint)fVar2 >> 0x10 & 0xff) - ((uint)fVar1 >> 0x10 & 0xff)) * iVar5
                              + ((uint)fVar1 & 0xffff0000) & 0xff0000 |
                              ((((uint)fVar2 & 0xff) - ((uint)fVar1 & 0xff)) * iVar5 >> 0x10) +
                              (int)fVar1 & 0xff |
                             (((uint)fVar2 >> 0x18) - ((uint)fVar1 >> 0x18)) * iVar5 * 0x100 +
                             ((uint)fVar1 & 0xff000000) & 0xff000000);
          fVar11 = ((float10)pfVar9[3] - (float10)pfVar8[1]) * extraout_ST0 + (float10)pfVar8[1];
          pfVar7[3] = (float)fVar11;
          pfVar7[param_1] = (float)(fVar11 * (float10)iVar4);
          local_10 = local_10 + 1;
          fVar11 = extraout_ST1;
        }
        pfVar9 = pfVar8 + -2;
        pfVar10 = pfVar6;
        for (iVar5 = 8; pfVar7 = pfVar6, iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar10 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar10 = pfVar10 + 1;
        }
      }
      else {
        pfVar9 = pfVar8 + -2;
        pfVar6 = pfVar7;
        for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar6 = *pfVar9;
          pfVar9 = pfVar9 + 1;
          pfVar6 = pfVar6 + 1;
        }
      }
LAB_00439ed6:
      pfVar7 = pfVar7 + 8;
      local_10 = local_10 + 1;
    }
    param_4 = (float *)(float)fVar11;
    pfVar9 = pfVar8 + -2;
    pfVar3 = pfVar3 + 8;
    pfVar8 = pfVar8 + 8;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return local_10;
    }
  } while( true );
}

