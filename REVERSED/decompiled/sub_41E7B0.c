/* sub_41E7B0 @ 0041e7b0   110 bytes */

void sub_41E7B0(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar3 = (float10)fcos((float10)*param_2);
  fVar4 = (float10)fsin((float10)*param_2);
  param_3[1] = 0.0;
  param_3[3] = 0.0;
  param_3[4] = 0.0;
  param_3[6] = 0.0;
  param_3[7] = 0.0;
  param_3[9] = 0.0;
  param_3[0xb] = 0.0;
  param_3[5] = 1.0;
  *param_3 = (float)fVar3;
  param_3[2] = (float)-fVar4;
  param_3[8] = (float)fVar4;
  param_3[10] = (float)fVar3;
  param_3[0xc] = (float)-(fVar3 * (float10)*param_1 + fVar4 * (float10)param_1[2]);
  param_3[0xd] = -param_1[1];
  fVar1 = *param_1;
  fVar2 = param_1[2];
  param_3[0xf] = 1.0;
  param_3[0xe] = (float)(fVar4 * (float10)fVar1 - fVar3 * (float10)fVar2);
  return;
}

