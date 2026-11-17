/* sub_41BEE0 @ 0041bee0   77 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall sub_41BEE0(float *param_1)

{
  float fVar1;
  
  *param_1 = param_1[4];
  param_1[1] = param_1[5];
  param_1[2] = param_1[6];
  param_1[3] = param_1[7];
  if (DAT_006d7c61 == '\0') {
    fVar1 = *param_1 * _DAT_0056e138 + param_1[2] * _DAT_0056e130 + param_1[1] * _DAT_0056e134;
    param_1[2] = fVar1;
    param_1[1] = fVar1;
    *param_1 = fVar1;
  }
  return;
}

