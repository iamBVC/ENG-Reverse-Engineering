/* sub_439F20 @ 00439f20   472 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_439F20(int param_1,float *param_2,int param_3,uint param_4)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  
  if ((DAT_006d7c72 & 1) == 0) {
    DAT_006d7c72 = DAT_006d7c72 | 1;
    sub_5626AD(&DAT_0043a100);
  }
  iVar5 = 0;
  iVar4 = 0;
  pfVar2 = (float *)&DAT_006d84b0;
  do {
    if (param_4 == 0) {
      fVar1 = _DAT_0056e008 / param_2[3];
      iVar5 = param_3 + -2;
      *param_2 = (_DAT_005833b8 * *param_2 * fVar1 + _DAT_005833b0) - (float)_DAT_0056e4a0;
      param_2[1] = (_DAT_005833bc * param_2[1] * fVar1 + _DAT_005833b4) - (float)_DAT_0056e4a0;
      param_2[2] = ((float)_DAT_0056e038 - param_2[2] * fVar1) * (float)_DAT_0056e030;
      param_2[3] = fVar1;
      fVar1 = _DAT_0056e008 / param_2[0xb];
      param_2[8] = (_DAT_005833b8 * param_2[8] * fVar1 + _DAT_005833b0) - (float)_DAT_0056e4a0;
      param_2[9] = (_DAT_005833bc * param_2[9] * fVar1 + _DAT_005833b4) - (float)_DAT_0056e4a0;
      param_2[10] = ((float)_DAT_0056e038 - param_2[10] * fVar1) * (float)_DAT_0056e030;
      param_2[0xb] = fVar1;
      if (0 < iVar5) {
        pfVar2 = param_2 + 0x12;
        pfVar3 = (float *)(param_1 + 0x40);
        param_3 = iVar5;
        do {
          fVar1 = _DAT_0056e008 / pfVar2[1];
          pfVar7 = pfVar2 + -2;
          *pfVar7 = (_DAT_005833b8 * *pfVar7 * fVar1 + _DAT_005833b0) - (float)_DAT_0056e4a0;
          pfVar2[-1] = (_DAT_005833bc * pfVar2[-1] * fVar1 + _DAT_005833b4) - (float)_DAT_0056e4a0;
          *pfVar2 = ((float)_DAT_0056e038 - *pfVar2 * fVar1) * (float)_DAT_0056e030;
          pfVar2[1] = fVar1;
          pfVar6 = param_2;
          pfVar8 = pfVar3 + -0x10;
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pfVar8 = *pfVar6;
            pfVar6 = pfVar6 + 1;
            pfVar8 = pfVar8 + 1;
          }
          pfVar6 = pfVar2 + -10;
          pfVar2 = pfVar2 + 8;
          pfVar8 = pfVar3 + -8;
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pfVar8 = *pfVar6;
            pfVar6 = pfVar6 + 1;
            pfVar8 = pfVar8 + 1;
          }
          pfVar6 = pfVar3;
          for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pfVar6 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pfVar6 = pfVar6 + 1;
          }
          param_3 = param_3 + -1;
          pfVar3 = pfVar3 + 0x18;
        } while (param_3 != 0);
      }
      return iVar5 * 3;
    }
    pfVar3 = pfVar2;
    if ((param_4 & 1) != 0) {
      param_3 = sub_439BC0(iVar4,param_2,param_3,pfVar2);
      if (param_3 < 3) {
        return 0;
      }
      iVar5 = 1 - iVar5;
      pfVar3 = (float *)(&DAT_006d84b0 + iVar5 * 0x50);
      param_2 = pfVar2;
    }
    iVar4 = iVar4 + 1;
    param_4 = (int)param_4 >> 1;
    pfVar2 = pfVar3;
  } while( true );
}

