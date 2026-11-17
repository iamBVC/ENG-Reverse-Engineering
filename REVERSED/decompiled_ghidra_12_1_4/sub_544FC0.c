/* sub_544FC0 @ 00544fc0   112 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 sub_544FC0(float param_1,float param_2,float param_3)

{
  float10 fVar1;
  
  if (param_3 <= param_1 + _DAT_0056e4fc) {
    return (float10)_DAT_0056e4f8;
  }
  if (param_3 < param_2 - _DAT_0056e4fc) {
    fVar1 = (float10)param_2;
    if ((float10)param_3 != (float10)_DAT_0056e470) {
      fVar1 = (float10)param_3;
    }
    fVar1 = (float10)log2(((float10)param_2 + (float10)param_1) / fVar1);
    return (float10)0.3010299956639812 * fVar1 * (float10)_DAT_0056e4f0;
  }
  return (float10)_DAT_0056e00c;
}

