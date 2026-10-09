/* sub_412E50 @ 00412e50   181 bytes */

int sub_412E50(uint param_1,uint param_2,uint param_3,uint param_4,int param_5,int param_6,
              int param_7,int param_8)

{
  int iVar1;
  int iVar2;
  
  for (; (0 < param_5 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      param_5 = param_5 + -1;
    }
  }
  for (; (0 < param_6 && (param_2 != 0)); param_2 = param_2 >> 1) {
    if ((param_2 & 1) != 0) {
      param_6 = param_6 + -1;
    }
  }
  for (; (0 < param_7 && (param_3 != 0)); param_3 = param_3 >> 1) {
    if ((param_3 & 1) != 0) {
      param_7 = param_7 + -1;
    }
  }
  for (; (0 < param_8 && (param_4 != 0)); param_4 = param_4 >> 1) {
    if ((param_4 & 1) != 0) {
      param_8 = param_8 + -1;
    }
  }
  iVar2 = param_5;
  if (param_5 <= param_6) {
    iVar2 = param_6;
  }
  iVar1 = param_7;
  if ((param_7 < iVar2) && (iVar1 = param_6, param_6 < param_5)) {
    iVar1 = param_5;
  }
  if (param_8 < iVar1) {
    iVar2 = param_5;
    if (param_5 <= param_6) {
      iVar2 = param_6;
    }
    param_8 = param_7;
    if (param_7 < iVar2) {
      if (param_6 < param_5) {
        return param_5;
      }
      return param_6;
    }
  }
  return param_8;
}

