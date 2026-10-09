/* sub_41E820 @ 0041e820   66 bytes */

void sub_41E820(float param_1,float *param_2)

{
  int iVar1;
  float *pfVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar3 = (float10)fcos((float10)param_1);
  pfVar2 = param_2;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = 0.0;
    pfVar2 = pfVar2 + 1;
  }
  param_2[5] = 1.0;
  param_2[0xf] = 1.0;
  fVar4 = (float10)fsin((float10)param_1);
  *param_2 = (float)fVar3;
  param_2[10] = (float)fVar3;
  param_2[8] = -(float)fVar4;
  param_2[2] = (float)fVar4;
  return;
}

