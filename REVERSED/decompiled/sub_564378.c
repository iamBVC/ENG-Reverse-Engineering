/* sub_564378 @ 00564378   155 bytes */

void sub_564378(undefined8 *param_1,int param_2,int param_3,undefined4 param_4)

{
  char *pcVar1;
  char *pcVar2;
  
  DAT_006da3bc = (int *)sub_569AF7(*param_1);
  DAT_006da3c4 = DAT_006da3bc[1] + -1;
  pcVar1 = (char *)((uint)(*DAT_006da3bc == 0x2d) + param_2);
  sub_569A80(pcVar1,param_3,DAT_006da3bc);
  DAT_006da3c8 = DAT_006da3c4 < DAT_006da3bc[1] + -1;
  DAT_006da3c4 = DAT_006da3bc[1] + -1;
  if ((DAT_006da3c4 < -4) || (param_3 <= DAT_006da3c4)) {
    sub_564413(param_1,param_2,param_3,param_4);
  }
  else {
    if ((bool)DAT_006da3c8) {
      do {
        pcVar2 = pcVar1;
        pcVar1 = pcVar2 + 1;
      } while (*pcVar2 != '\0');
      pcVar2[-1] = '\0';
    }
    sub_56443A(param_1,param_2,param_3);
  }
  return;
}

