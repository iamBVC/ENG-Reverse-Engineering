/* sub_41E610 @ 0041e610   112 bytes */

void sub_41E610(float param_1,float param_2,undefined4 param_3,undefined4 param_4,float param_5,
               float param_6,undefined4 *param_7)

{
  *param_7 = param_3;
  param_7[8] = -param_1;
  param_7[9] = -param_2;
  param_7[1] = 0;
  param_7[2] = 0;
  param_7[3] = 0;
  param_7[4] = 0;
  param_7[5] = param_4;
  param_7[6] = 0;
  param_7[7] = 0;
  param_7[0xb] = 0x3f800000;
  param_7[0xc] = 0;
  param_7[0xd] = 0;
  param_7[0xf] = 0;
  param_7[10] = -((param_5 + param_6) / (param_6 - param_5));
  param_7[0xe] = (param_5 * param_6 + param_5 * param_6) / (param_6 - param_5);
  return;
}

