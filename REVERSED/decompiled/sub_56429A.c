/* sub_56429A @ 0056429a   222 bytes */

undefined1 * sub_56429A(undefined8 *param_1,undefined1 *param_2,size_t param_3)

{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  
  piVar1 = DAT_006da3bc;
  if (DAT_006da3c0 == '\0') {
    piVar1 = (int *)sub_569AF7(*param_1);
    sub_569A80(param_2 + (*piVar1 == 0x2d),piVar1[1] + param_3,piVar1);
  }
  else if (DAT_006da3c4 == param_3) {
    iVar2 = (*DAT_006da3bc == 0x2d) + DAT_006da3c4;
    param_2[iVar2] = 0x30;
    (param_2 + iVar2)[1] = 0;
  }
  puVar3 = param_2;
  if (*piVar1 == 0x2d) {
    *param_2 = 0x2d;
    puVar3 = param_2 + 1;
  }
  if (piVar1[1] < 1) {
    sub_5644AE(puVar3,1);
    *puVar3 = 0x30;
    puVar3 = puVar3 + 1;
  }
  else {
    puVar3 = puVar3 + piVar1[1];
  }
  if (0 < (int)param_3) {
    sub_5644AE(puVar3,1);
    *puVar3 = DAT_0057ca14;
    iVar2 = piVar1[1];
    if (iVar2 < 0) {
      if ((DAT_006da3c0 != '\0') || (-iVar2 <= (int)param_3)) {
        param_3 = -iVar2;
      }
      sub_5644AE(puVar3 + 1,param_3);
      _memset(puVar3 + 1,0x30,param_3);
    }
  }
  return param_2;
}

