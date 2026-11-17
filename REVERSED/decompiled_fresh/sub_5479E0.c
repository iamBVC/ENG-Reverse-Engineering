/* sub_5479E0 @ 005479e0   62 bytes */

undefined4 sub_5479E0(short *param_1,short param_2)

{
  short sVar1;
  short sVar2;
  
  sVar1 = *param_1;
  if (sVar1 == param_2) {
    return 0;
  }
  if (sVar1 < param_2) {
    sVar2 = param_2 + -0x200;
    if ((short)(param_2 + -0x200) < sVar1) {
      *param_1 = sVar1;
      return 1;
    }
  }
  else {
    sVar2 = param_2 + 0x200;
    if (sVar1 < (short)(param_2 + 0x200)) {
      sVar2 = sVar1;
    }
  }
  *param_1 = sVar2;
  return 1;
}

