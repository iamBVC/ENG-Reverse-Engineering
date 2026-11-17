/* sub_2110DD25 @ 2110dd25   155 bytes */

void __cdecl sub_2110DD25(undefined4 param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  DAT_21115610 = (int *)sub_2110F827();
  DAT_21115618 = DAT_21115610[1] + -1;
  iVar1 = *DAT_21115610;
  sub_2110F7B0(param_2 + (iVar1 == 0x2d),param_3,(int)DAT_21115610);
  DAT_2111561c = DAT_21115618 < DAT_21115610[1] + -1;
  DAT_21115618 = DAT_21115610[1] + -1;
  if ((DAT_21115618 < -4) || ((int)param_3 <= DAT_21115618)) {
    sub_2110DDC0(param_1,param_2,param_3,param_4);
  }
  else {
    pcVar2 = param_2 + (iVar1 == 0x2d);
    if ((bool)DAT_2111561c) {
      do {
        pcVar3 = pcVar2;
        pcVar2 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
      pcVar3[-1] = '\0';
    }
    sub_2110DDE7(param_1,param_2,param_3);
  }
  return;
}

