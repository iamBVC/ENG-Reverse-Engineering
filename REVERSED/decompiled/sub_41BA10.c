/* sub_41BA10 @ 0041ba10   370 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41BA10(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if (param_1 != (float *)0x0) {
    if (param_1[0x1a] == 1.4013e-45) {
      fVar1 = param_1[0x11] * param_2[3] + param_2[4] * param_1[0x12] + param_2[5] * param_1[0x13];
      if (_DAT_0056e00c <= fVar1) {
        *param_3 = fVar1 * *param_1 + *param_3;
        param_3[1] = fVar1 * param_1[1] + param_3[1];
        param_3[2] = fVar1 * param_1[2] + param_3[2];
        return;
      }
    }
    else if (param_1[0x1a] == 2.8026e-45) {
      fVar1 = param_1[0xe] - *param_2;
      fVar3 = param_1[0xf] - param_2[1];
      fVar4 = param_1[0x10] - param_2[2];
      fVar2 = fVar1 * fVar1 + fVar3 * fVar3 + fVar4 * fVar4;
      if ((fVar2 <= param_1[0x14]) &&
         (fVar1 = fVar1 * param_2[3] + fVar3 * param_2[4] + fVar4 * param_2[5],
         _DAT_0056e00c <= fVar1)) {
        fVar4 = (float)(0x5f3759df - ((int)fVar2 >> 1));
        fVar4 = (_DAT_0056e184 - fVar4 * fVar4 * fVar2 * _DAT_0056e158) * fVar4;
        fVar4 = (_DAT_0056e184 - fVar4 * fVar4 * fVar2 * _DAT_0056e158) * fVar4;
        if (param_1[0x15] < fVar2) {
          fVar4 = (fVar4 * param_1[0x16] - _DAT_0056e008) * param_1[0x18];
        }
        if (param_1[0x19] == 1.4013e-45) {
          if (DAT_005865d4 == 1) {
            fVar4 = fVar4 * _DAT_0056e184;
          }
          else if (DAT_005865d4 == 3) {
            fVar4 = fVar4 * _DAT_0056e158;
          }
        }
        fVar4 = fVar4 * fVar1;
        *param_3 = fVar4 * *param_1 + *param_3;
        param_3[1] = fVar4 * param_1[1] + param_3[1];
        param_3[2] = fVar4 * param_1[2] + param_3[2];
        return;
      }
    }
  }
  return;
}

