/* sub_2110DC47 @ 2110dc47   222 bytes */

char * __cdecl sub_2110DC47(undefined4 param_1,char *param_2,size_t param_3)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  
  piVar1 = DAT_21115610;
  if (DAT_21115614 == '\0') {
    piVar1 = (int *)sub_2110F827();
    sub_2110F7B0(param_2 + (*piVar1 == 0x2d),piVar1[1] + param_3,(int)piVar1);
  }
  else if (DAT_21115618 == param_3) {
    iVar2 = (*DAT_21115610 == 0x2d) + DAT_21115618;
    param_2[iVar2] = '0';
    (param_2 + iVar2)[1] = '\0';
  }
  pcVar3 = param_2;
  if (*piVar1 == 0x2d) {
    *param_2 = '-';
    pcVar3 = param_2 + 1;
  }
  if (piVar1[1] < 1) {
    sub_2110DE5B(pcVar3,1);
    *pcVar3 = '0';
    pcVar3 = pcVar3 + 1;
  }
  else {
    pcVar3 = pcVar3 + piVar1[1];
  }
  if (0 < (int)param_3) {
    sub_2110DE5B(pcVar3,1);
    *pcVar3 = DAT_21114ed0;
    iVar2 = piVar1[1];
    if (iVar2 < 0) {
      if ((DAT_21115614 != '\0') || (-iVar2 <= (int)param_3)) {
        param_3 = -iVar2;
      }
      sub_2110DE5B(pcVar3 + 1,param_3);
      _memset(pcVar3 + 1,0x30,param_3);
    }
  }
  return param_2;
}

