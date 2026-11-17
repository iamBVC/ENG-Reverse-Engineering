/* sub_401210 @ 00401210   510 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float sub_401210(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,float param_6,
                float param_7,float *param_8)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float *pfVar10;
  
  pfVar10 = (float *)(param_2 + (int)param_6 * 0xc);
  fVar3 = *pfVar10;
  fVar4 = pfVar10[1];
  fVar5 = pfVar10[2];
  fVar6 = *(float *)(param_2 + (int)param_7 * 0xc) - fVar3;
  iVar1 = param_2 + (int)param_7 * 0xc;
  fVar7 = *(float *)(iVar1 + 4) - fVar4;
  fVar8 = *(float *)(iVar1 + 8) - fVar5;
  fVar9 = param_6;
  switch(param_1) {
  case 0:
    fVar9 = -((fVar5 + fVar3) / (fVar8 + fVar6));
    break;
  case 1:
    fVar9 = (fVar3 - fVar5) / (fVar8 - fVar6);
    break;
  case 2:
    fVar9 = -((fVar4 + fVar5) / (fVar8 + fVar7));
    break;
  case 3:
    fVar9 = (fVar4 - fVar5) / (fVar8 - fVar7);
    break;
  case 4:
    fVar9 = (_DAT_0057d70c - fVar5) / fVar8;
    break;
  case 5:
    fVar9 = (_DAT_0057d7fc - fVar5) / fVar8;
  }
  if (fVar9 != _DAT_0056e00c) {
    if (fVar9 != _DAT_0056e008) {
      fVar3 = pfVar10[1];
      fVar4 = pfVar10[2];
      pfVar2 = (float *)(param_2 + (int)*param_8 * 0xc);
      *pfVar2 = fVar6 * fVar9 + *pfVar10;
      pfVar2[1] = fVar7 * fVar9 + fVar3;
      pfVar2[2] = fVar8 * fVar9 + fVar4;
      iVar1 = (int)param_7 * 0x10 + param_3;
      pfVar10 = (float *)((int)param_6 * 0x10 + param_3);
      *(float *)(param_3 + (int)*param_8 * 0x10) =
           (*(float *)((int)param_7 * 0x10 + param_3) - *pfVar10) * fVar9 + *pfVar10;
      *(float *)(param_3 + 4 + (int)*param_8 * 0x10) =
           (*(float *)(iVar1 + 4) - pfVar10[1]) * fVar9 + pfVar10[1];
      *(float *)(param_3 + 8 + (int)*param_8 * 0x10) =
           (*(float *)(iVar1 + 8) - pfVar10[2]) * fVar9 + pfVar10[2];
      *(float *)((int)*param_8 * 0x10 + 0xc + param_3) =
           (*(float *)(iVar1 + 0xc) - pfVar10[3]) * fVar9 + pfVar10[3];
      *(float *)(param_4 + (int)*param_8 * 4) =
           (*(float *)(param_4 + (int)param_7 * 4) - *(float *)(param_4 + (int)param_6 * 4)) * fVar9
           + *(float *)(param_4 + (int)param_6 * 4);
      *(float *)(param_5 + (int)*param_8 * 4) =
           (*(float *)(param_5 + (int)param_7 * 4) - *(float *)(param_5 + (int)param_6 * 4)) * fVar9
           + *(float *)(param_5 + (int)param_6 * 4);
      fVar3 = *param_8;
      *param_8 = (float)((int)fVar3 + 1);
      return fVar3;
    }
    return param_7;
  }
  return param_6;
}

