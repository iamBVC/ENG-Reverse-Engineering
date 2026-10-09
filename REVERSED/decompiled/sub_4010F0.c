/* sub_4010F0 @ 004010f0   250 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_4010F0(undefined4 param_1,float *param_2)

{
  float fVar1;
  
  switch(param_1) {
  case 0:
    fVar1 = *param_2;
    goto LAB_00401177;
  case 1:
    if (*param_2 < param_2[2]) {
      return 1;
    }
    if (param_2[2] < *param_2) {
      return 0xffffffff;
    }
    break;
  case 2:
    fVar1 = param_2[1];
LAB_00401177:
    if (-fVar1 < param_2[2]) {
      return 1;
    }
    if (param_2[2] < -fVar1) {
      return 0xffffffff;
    }
    break;
  case 3:
    if (param_2[1] < param_2[2]) {
      return 1;
    }
    if (param_2[2] < param_2[1]) {
      return 0xffffffff;
    }
    break;
  case 4:
    if (_DAT_0057d70c < param_2[2]) {
      return 1;
    }
    if (param_2[2] < _DAT_0057d70c) {
      return 0xffffffff;
    }
    break;
  case 5:
    if (param_2[2] < _DAT_0057d7fc) {
      return 1;
    }
    if (_DAT_0057d7fc < param_2[2]) {
      return 0xffffffff;
    }
  }
  return 0;
}

