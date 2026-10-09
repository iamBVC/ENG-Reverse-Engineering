/* sub_41E870 @ 0041e870   228 bytes */

void sub_41E870(float param_1,float param_2,float param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  
  fVar4 = (float10)fcos((float10)param_1);
  param_4[3] = 0.0;
  param_4[7] = 0.0;
  param_4[0xb] = 0.0;
  param_4[0xc] = 0.0;
  param_4[0xd] = 0.0;
  param_4[0xe] = 0.0;
  param_4[0xf] = 1.0;
  fVar5 = (float10)fsin((float10)param_1);
  fVar6 = (float10)fcos((float10)param_2);
  fVar1 = (float)fVar6;
  fVar6 = (float10)fsin((float10)param_2);
  fVar7 = (float10)fcos((float10)param_3);
  fVar2 = (float)fVar7;
  fVar7 = (float10)fsin((float10)param_3);
  *param_4 = (float)((float10)(float)(fVar7 * fVar6) * fVar5 + (float10)(fVar2 * fVar1));
  fVar3 = (float)fVar7 * fVar1;
  param_4[1] = (float)(-(float10)fVar3 + (float10)(float)((float10)fVar2 * fVar6) * fVar5);
  param_4[2] = (float)(fVar6 * fVar4);
  param_4[4] = (float)((float10)(float)fVar7 * fVar4);
  param_4[5] = (float)((float10)fVar2 * fVar4);
  param_4[6] = (float)-fVar5;
  param_4[8] = (float)(-(float10)(float)((float10)fVar2 * fVar6) + (float10)fVar3 * fVar5);
  param_4[9] = (float)((float10)(fVar2 * fVar1) * fVar5 + (float10)(float)(fVar7 * fVar6));
  param_4[10] = (float)((float10)fVar1 * fVar4);
  return;
}

