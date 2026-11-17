/* sub_5686EC @ 005686ec   101 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall sub_5686EC(undefined4 param_1,double param_2)

{
  uint uVar1;
  float10 fVar2;
  undefined4 uVar3;
  
  uVar1 = sub_56BB21(param_2,param_1,param_1);
  if ((uVar1 & 0x90) == 0) {
    fVar2 = (float10)__frnd(param_2);
    if ((double)fVar2 == param_2) {
      param_2 = param_2 / _DAT_0056e3d8;
      fVar2 = (float10)__frnd();
      if (fVar2 == (float10)param_2) {
        uVar3 = 2;
      }
      else {
        uVar3 = 1;
      }
      return uVar3;
    }
  }
  return 0;
}

