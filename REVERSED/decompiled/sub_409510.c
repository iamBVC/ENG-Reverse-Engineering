/* sub_409510 @ 00409510   292 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_409510(float *param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = _DAT_0056e008;
  if (param_4 == _DAT_0056e00c) {
    *param_1 = 0.5;
    *param_2 = 0.5;
    *param_3 = 0.5;
    return;
  }
  fVar1 = (param_4 + _DAT_0056e008) / (param_4 + param_4);
  fVar2 = fVar1 * *param_1;
  *param_1 = fVar2;
  if (fVar3 < fVar2) {
    if (_DAT_0056e154 < fVar2) {
      fVar1 = (_DAT_0056e154 / fVar2) * fVar1;
    }
    *param_1 = 1.0;
  }
  fVar2 = _DAT_0056e008;
  fVar3 = fVar1 * *param_2;
  *param_2 = fVar3;
  if (fVar2 < fVar3) {
    if (_DAT_0056e154 < fVar3) {
      fVar3 = _DAT_0056e154 / fVar3;
      *param_1 = fVar3 * *param_1;
      fVar1 = fVar3 * fVar1;
    }
    *param_2 = 1.0;
  }
  fVar3 = _DAT_0056e008;
  fVar1 = fVar1 * *param_3;
  *param_3 = fVar1;
  if (fVar3 < fVar1) {
    if (_DAT_0056e154 < fVar1) {
      fVar1 = _DAT_0056e154 / fVar1;
      *param_1 = fVar1 * *param_1;
      *param_2 = fVar1 * *param_2;
    }
    *param_3 = 1.0;
  }
  return;
}

