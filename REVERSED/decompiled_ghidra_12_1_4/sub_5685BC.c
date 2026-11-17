/* sub_5685BC @ 005685bc   304 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_5685BC(int param_1,int param_2,double param_3,double *param_4)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  dVar1 = (double)CONCAT44(param_2,param_1);
  if ((double)CONCAT44(param_2,param_1) < _DAT_0056e470) {
    dVar1 = -dVar1;
  }
  dVar2 = _DAT_0057d190;
  if (param_3._4_4_ == 0x7ff00000) {
    if (param_3._0_4_ != 0) {
LAB_00568647:
      if (param_2 == 0x7ff00000) {
        if (param_1 != 0) {
          return 0;
        }
        if (_DAT_0056e470 < param_3) goto LAB_005686e2;
        if (param_3 < _DAT_0056e470) goto LAB_00568679;
      }
      else {
        if (param_2 != -0x100000) {
          return 0;
        }
        if (param_1 != 0) {
          return 0;
        }
        iVar3 = sub_5686EC(param_3);
        if (_DAT_0056e470 < param_3) {
          dVar2 = _DAT_0057d190;
          if (iVar3 == 1) {
            dVar2 = -_DAT_0057d190;
          }
          goto LAB_005686e2;
        }
        if (param_3 < _DAT_0056e470) {
          dVar2 = _DAT_0057d1b0;
          if (iVar3 != 1) {
            dVar2 = 0.0;
          }
          goto LAB_005686e2;
        }
      }
      dVar2 = 1.0;
      goto LAB_005686e2;
    }
    if (_DAT_0056e038 < dVar1) goto LAB_005686e2;
    if (_DAT_0056e038 <= dVar1) {
LAB_0056860c:
      *param_4 = _DAT_0057d198;
      return 1;
    }
  }
  else {
    if ((param_3._4_4_ != -0x100000) || (param_3._0_4_ != 0)) goto LAB_00568647;
    if (dVar1 <= _DAT_0056e038) {
      if (_DAT_0056e038 <= dVar1) goto LAB_0056860c;
      goto LAB_005686e2;
    }
  }
LAB_00568679:
  dVar2 = 0.0;
LAB_005686e2:
  *param_4 = dVar2;
  return 0;
}

