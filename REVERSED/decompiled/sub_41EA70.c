/* sub_41EA70 @ 0041ea70   401 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41EA70(float *param_1,float param_2,float param_3,float param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  
  fVar4 = (float10)fcos((float10)*param_1);
  fVar5 = (float10)fsin((float10)*param_1);
  fVar6 = (float10)fcos((float10)param_1[1]);
  fVar1 = (float)fVar6;
  fVar6 = (float10)fsin((float10)param_1[1]);
  fVar7 = (float10)fcos((float10)param_1[2]);
  fVar2 = (float)fVar7;
  fVar7 = (float10)fsin((float10)param_1[2]);
  param_5[3] = 0.0;
  param_5[7] = 0.0;
  fVar3 = (float)fVar7;
  param_2 = _DAT_0056e008 / param_2;
  param_3 = _DAT_0056e008 / param_3;
  param_4 = _DAT_0056e008 / param_4;
  fVar7 = ((float10)(fVar2 * fVar1) - (float10)fVar3 * fVar6 * fVar5) * (float10)param_2;
  *param_5 = (float)fVar7;
  fVar8 = ((float10)(float)((float10)fVar2 * fVar6) * fVar5 + (float10)(fVar3 * fVar1)) *
          (float10)param_3;
  param_5[1] = (float)fVar8;
  fVar9 = -(fVar6 * (float10)param_4 * fVar4);
  param_5[2] = (float)fVar9;
  fVar10 = -((float10)param_2 * (float10)fVar3 * fVar4);
  param_5[4] = (float)fVar10;
  fVar11 = (float10)param_3 * (float10)fVar2 * fVar4;
  param_5[5] = (float)fVar11;
  param_5[6] = (float)((float10)param_4 * fVar5);
  fVar12 = ((float10)(fVar3 * fVar1) * fVar5 + (float10)(float)((float10)fVar2 * fVar6)) *
           (float10)param_2;
  param_5[8] = (float)fVar12;
  param_5[0xb] = 0.0;
  fVar6 = ((float10)(float)((float10)fVar3 * fVar6) - fVar5 * (float10)(fVar2 * fVar1)) *
          (float10)param_3;
  param_5[9] = (float)fVar6;
  fVar4 = (float10)param_4 * (float10)fVar1 * fVar4;
  param_5[10] = (float)fVar4;
  param_5[0xc] = -((float)fVar12 * param_1[5] +
                  (float)fVar7 * param_1[3] + (float)fVar10 * param_1[4]);
  param_5[0xd] = -((float)fVar6 * param_1[5] +
                  (float)fVar8 * param_1[3] + (float)fVar11 * param_1[4]);
  fVar1 = param_1[4];
  fVar2 = param_1[3];
  fVar3 = param_1[5];
  param_5[0xf] = 1.0;
  param_5[0xe] = (float)-(fVar4 * (float10)fVar3 +
                         (float10)(float)fVar9 * (float10)fVar2 +
                         (float10)(float)((float10)param_4 * fVar5) * (float10)fVar1);
  return;
}

