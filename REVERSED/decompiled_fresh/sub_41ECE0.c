/* sub_41ECE0 @ 0041ece0   108 bytes */

void sub_41ECE0(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float *param_8)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_4);
  param_8[2] = 0.0;
  param_8[3] = 0.0;
  param_8[6] = 0.0;
  param_8[7] = 0.0;
  param_8[8] = 0.0;
  param_8[9] = 0.0;
  param_8[0xb] = 0.0;
  param_8[10] = param_7;
  param_8[0xc] = param_1;
  param_8[0xd] = param_2;
  param_8[0xe] = param_3;
  param_8[0xf] = 1.0;
  fVar2 = (float10)fsin((float10)param_4);
  *param_8 = (float)(fVar1 * (float10)param_5);
  param_8[1] = (float)-(fVar2 * (float10)param_5);
  param_8[4] = (float)(fVar2 * (float10)param_6);
  param_8[5] = (float)(fVar1 * (float10)param_6);
  return;
}

