/* sub_41E990 @ 0041e990   219 bytes */

void sub_41E990(float *param_1,float param_2,float param_3,float param_4,float *param_5)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar2 = (float10)fcos((float10)*param_1);
  fVar3 = (float10)fsin((float10)*param_1);
  fVar4 = (float10)fcos((float10)param_1[1]);
  fVar1 = (float)fVar4;
  fVar4 = (float10)fsin((float10)param_1[1]);
  fVar5 = (float10)fcos((float10)param_1[2]);
  fVar6 = (float10)fsin((float10)param_1[2]);
  param_5[3] = 0.0;
  param_5[7] = 0.0;
  param_5[0xb] = 0.0;
  *param_5 = (float)(((float10)(float)(fVar5 * (float10)fVar1) - fVar6 * fVar4 * fVar3) *
                    (float10)param_2);
  param_5[1] = (float)-(fVar6 * fVar2 * (float10)param_2);
  param_5[2] = (float)((fVar6 * (float10)fVar1 * fVar3 + fVar5 * fVar4) * (float10)param_2);
  param_5[4] = (float)((fVar5 * fVar4 * fVar3 + fVar6 * (float10)fVar1) * (float10)param_3);
  param_5[5] = (float)(fVar5 * fVar2 * (float10)param_3);
  param_5[6] = (float)(((float10)(float)(fVar6 * fVar4) -
                       (float10)(float)(fVar5 * (float10)fVar1) * fVar3) * (float10)param_3);
  param_5[8] = (float)-(fVar4 * fVar2 * (float10)param_4);
  param_5[9] = (float)(fVar3 * (float10)param_4);
  param_5[10] = (float)((float10)fVar1 * fVar2 * (float10)param_4);
  param_5[0xc] = param_1[3];
  param_5[0xd] = param_1[4];
  param_5[0xe] = param_1[5];
  param_5[0xf] = 1.0;
  return;
}

