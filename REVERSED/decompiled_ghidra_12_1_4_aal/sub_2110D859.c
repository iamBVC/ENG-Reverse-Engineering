/* entry @ 2110d859   157 bytes */

int entry(HMODULE param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = param_2;
  iVar2 = DAT_211155fc;
  if (param_2 != 0) {
    if ((param_2 != 1) && (param_2 != 2)) goto LAB_2110d8a1;
    if ((DAT_21115b5c != (code *)0x0) &&
       (iVar2 = (*DAT_21115b5c)(param_1,param_2,param_3), iVar2 == 0)) {
      return 0;
    }
    iVar2 = sub_2110D7A1(param_1,param_2);
  }
  if (iVar2 == 0) {
    return 0;
  }
LAB_2110d8a1:
  iVar2 = sub_21101090(param_1,param_2);
  if (param_2 == 1) {
    if (iVar2 != 0) {
      return iVar2;
    }
    sub_2110D7A1(param_1,0);
  }
  if ((param_2 != 0) && (param_2 != 3)) {
    return iVar2;
  }
  iVar3 = sub_2110D7A1(param_1,param_2);
  param_2 = iVar2;
  if (iVar3 == 0) {
    param_2 = 0;
  }
  if (param_2 != 0) {
    if (DAT_21115b5c != (code *)0x0) {
      iVar2 = (*DAT_21115b5c)(param_1,iVar1,param_3);
      return iVar2;
    }
    return param_2;
  }
  return 0;
}

