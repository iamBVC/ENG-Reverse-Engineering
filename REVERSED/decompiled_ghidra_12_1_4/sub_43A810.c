/* sub_43A810 @ 0043a810   976 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_43A810(int param_1,int param_2,int param_3,float *param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  int local_8;
  int local_4;
  
  local_8 = 0;
  if (param_5._0_1_ == '\0') {
    switch(param_1) {
    case 0:
      fVar9 = (float10)_DAT_0056e418;
      fVar10 = -(float10)_DAT_00583398;
      break;
    case 1:
      fVar9 = (float10)_DAT_0056e008;
      fVar10 = (float10)_DAT_0058339c;
      break;
    case 2:
      fVar9 = (float10)_DAT_0056e008;
      fVar10 = (float10)_DAT_005833a4;
      break;
    case 3:
      fVar9 = (float10)_DAT_0056e418;
      fVar10 = -(float10)_DAT_005833a0;
      break;
    default:
      goto switchD_0043a832_default;
    }
  }
  else {
    switch(param_1) {
    case 0:
    case 3:
      fVar9 = (float10)_DAT_0056e418;
      fVar10 = (float10)_DAT_0056e00c;
      break;
    case 1:
      fVar9 = (float10)_DAT_0056e008;
      fVar10 = (float10)DAT_00583390;
      break;
    case 2:
      fVar9 = (float10)_DAT_0056e008;
      fVar10 = (float10)DAT_00583394;
      break;
    default:
switchD_0043a832_default:
      fVar9 = (float10)param_5;
      fVar10 = (float10)param_5;
    }
  }
  param_1 = param_1 / 2;
  pfVar7 = (float *)(param_3 * 0x20 + -0x20 + param_2);
  fVar11 = fVar9 * (float10)pfVar7[param_1] - fVar10;
  if (param_3 == 0) {
    return 0;
  }
  pfVar3 = (float *)(param_2 + param_1 * 4);
  pfVar6 = (float *)(param_2 + 8);
  local_4 = param_3;
  do {
    param_5 = (float)fVar11;
    fVar11 = fVar9 * (float10)*pfVar3 - fVar10;
    if ((float10)_DAT_0056e00c < fVar11) {
      if (param_5 < _DAT_0056e00c) {
        fVar9 = (float10)param_5 / ((float10)param_5 - fVar11);
        *param_4 = (float)(((float10)pfVar6[-2] - (float10)*pfVar7) * fVar9 + (float10)*pfVar7);
        param_4[1] = (float)(((float10)pfVar6[-1] - (float10)pfVar7[1]) * fVar9 + (float10)pfVar7[1]
                            );
        param_4[2] = (float)(((float10)*pfVar6 - (float10)pfVar7[2]) * fVar9 + (float10)pfVar7[2]);
        param_4[6] = (float)(((float10)pfVar6[4] - (float10)pfVar7[6]) * fVar9 + (float10)pfVar7[6])
        ;
        param_4[7] = (float)(((float10)pfVar6[5] - (float10)pfVar7[7]) * fVar9 + (float10)pfVar7[7])
        ;
        param_4[3] = (float)(((float10)pfVar6[1] - (float10)pfVar7[3]) * fVar9 + (float10)pfVar7[3])
        ;
        fVar9 = fVar10;
        iVar4 = __ftol();
        fVar1 = pfVar6[2];
        fVar2 = pfVar7[4];
        param_4[4] = (float)(((((uint)fVar1 >> 8 & 0xff) - ((uint)fVar2 >> 8 & 0xff)) * iVar4 >> 8)
                             + ((uint)fVar2 & 0xffffff00) & 0xff00 |
                             (((uint)fVar1 >> 0x10 & 0xff) - ((uint)fVar2 >> 0x10 & 0xff)) * iVar4 +
                             ((uint)fVar2 & 0xffff0000) & 0xff0000 |
                             (((uint)fVar1 >> 0x18) - ((uint)fVar2 >> 0x18)) * iVar4 * 0x100 +
                             ((uint)fVar2 & 0xff000000) & 0xff000000 |
                            ((((uint)fVar1 & 0xff) - ((uint)fVar2 & 0xff)) * iVar4 >> 0x10) +
                            (int)fVar2 & 0xff);
        param_4[param_1] = (float)(extraout_ST1_00 * fVar9);
        fVar11 = extraout_ST0_00;
        fVar10 = extraout_ST1_00;
        goto LAB_0043ab92;
      }
    }
    else {
      if (_DAT_0056e00c < param_5) {
        pfVar5 = param_4;
        if (fVar11 < (float10)_DAT_0056e00c) {
          fVar9 = fVar11 / (fVar11 - (float10)param_5);
          *param_4 = (float)(((float10)*pfVar7 - (float10)pfVar6[-2]) * fVar9 + (float10)pfVar6[-2])
          ;
          param_4[1] = (float)(((float10)pfVar7[1] - (float10)pfVar6[-1]) * fVar9 +
                              (float10)pfVar6[-1]);
          param_4[2] = (float)(((float10)pfVar7[2] - (float10)*pfVar6) * fVar9 + (float10)*pfVar6);
          param_4[6] = (float)(((float10)pfVar7[6] - (float10)pfVar6[4]) * fVar9 +
                              (float10)pfVar6[4]);
          param_4[7] = (float)(((float10)pfVar7[7] - (float10)pfVar6[5]) * fVar9 +
                              (float10)pfVar6[5]);
          fVar9 = fVar10;
          iVar4 = __ftol();
          fVar10 = fVar11;
          fVar1 = pfVar6[2];
          fVar2 = pfVar7[4];
          pfVar5 = param_4 + 8;
          param_4[4] = (float)(((((uint)fVar2 >> 8 & 0xff) - ((uint)fVar1 >> 8 & 0xff)) * iVar4 >> 8
                               ) + ((uint)fVar1 & 0xffffff00) & 0xff00 |
                               (((uint)fVar2 >> 0x10 & 0xff) - ((uint)fVar1 >> 0x10 & 0xff)) * iVar4
                               + ((uint)fVar1 & 0xffff0000) & 0xff0000 |
                               ((((uint)fVar2 & 0xff) - ((uint)fVar1 & 0xff)) * iVar4 >> 0x10) +
                               (int)fVar1 & 0xff |
                              (((uint)fVar2 >> 0x18) - ((uint)fVar1 >> 0x18)) * iVar4 * 0x100 +
                              ((uint)fVar1 & 0xff000000) & 0xff000000);
          param_4[3] = (float)(((float10)pfVar7[3] - (float10)pfVar6[1]) * extraout_ST0 +
                              (float10)pfVar6[1]);
          param_4[param_1] = (float)(fVar10 * fVar9);
          local_8 = local_8 + 1;
          fVar11 = extraout_ST1;
        }
        pfVar7 = pfVar6 + -2;
        pfVar8 = pfVar5;
        for (iVar4 = 8; param_4 = pfVar5, iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar8 = *pfVar7;
          pfVar7 = pfVar7 + 1;
          pfVar8 = pfVar8 + 1;
        }
      }
      else {
        pfVar7 = pfVar6 + -2;
        pfVar5 = param_4;
        for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar5 = *pfVar7;
          pfVar7 = pfVar7 + 1;
          pfVar5 = pfVar5 + 1;
        }
      }
LAB_0043ab92:
      param_4 = param_4 + 8;
      local_8 = local_8 + 1;
    }
    pfVar7 = pfVar6 + -2;
    pfVar3 = pfVar3 + 8;
    pfVar6 = pfVar6 + 8;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return local_8;
    }
  } while( true );
}

