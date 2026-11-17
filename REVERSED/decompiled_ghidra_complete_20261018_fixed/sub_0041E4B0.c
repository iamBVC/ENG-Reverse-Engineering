/* sub_41E4B0 @ 0041e4b0   352 bytes */

void sub_41E4B0(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
               float *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  
  fVar6 = (float10)fcos(-(float10)param_4);
  param_7[3] = 0.0;
  param_7[7] = 0.0;
  fVar1 = (float)fVar6;
  fVar6 = (float10)fsin(-(float10)param_4);
  fVar7 = (float10)fcos(-(float10)param_5);
  fVar2 = (float)fVar7;
  fVar7 = (float10)fsin(-(float10)param_5);
  fVar8 = (float10)fcos(-(float10)param_6);
  fVar3 = (float)fVar8;
  fVar8 = (float10)fsin(-(float10)param_6);
  fVar9 = (float10)(float)(fVar8 * fVar7) * fVar6 + (float10)(fVar3 * fVar2);
  *param_7 = (float)fVar9;
  fVar4 = (float)fVar8 * fVar2;
  fVar10 = -(float10)fVar4 + (float10)(float)((float10)fVar3 * fVar7) * fVar6;
  param_7[1] = (float)fVar10;
  param_7[2] = (float)(fVar7 * (float10)fVar1);
  fVar5 = (float)fVar8 * fVar1;
  param_7[4] = fVar5;
  param_7[5] = fVar3 * fVar1;
  param_7[6] = (float)-fVar6;
  fVar11 = -(float10)(float)((float10)fVar3 * fVar7) + (float10)fVar4 * fVar6;
  param_7[8] = (float)fVar11;
  fVar8 = fVar6 * (float10)(fVar3 * fVar2) + (float10)(float)(fVar8 * fVar7);
  param_7[9] = (float)fVar8;
  param_7[0xb] = 0.0;
  param_7[0xf] = 1.0;
  param_7[10] = fVar2 * fVar1;
  param_7[0xc] = -((float)fVar9 * param_1 + fVar5 * param_2 + (float)fVar11 * param_3);
  param_7[0xd] = (float)-((float10)(float)fVar10 * (float10)param_1 +
                         (float10)(fVar3 * fVar1) * (float10)param_2 + fVar8 * (float10)param_3);
  param_7[0xe] = -((float)(fVar7 * (float10)fVar1) * param_1 +
                  (float)-fVar6 * param_2 + fVar2 * fVar1 * param_3);
  return;
}

