/* sub_567693 @ 00567693   423 bytes */

void sub_567693(int *param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
               char param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_18 = local_18 & 0xffffff00;
  local_14 = *(int *)(param_2 + 8);
  if ((local_14 < -1) || (*(int *)(param_5 + 4) <= local_14)) {
    sub_567EA2();
  }
  piVar3 = DAT_006da420;
  if (*param_1 == -0x1f928c9d) {
    if (((param_1[4] == 3) && (param_1[5] == 0x19930520)) && (param_1[7] == 0)) {
      if (DAT_006da420 == (int *)0x0) {
        return;
      }
      param_3 = DAT_006da424;
      local_18 = CONCAT31(local_18._1_3_,1);
      iVar2 = sub_56AB08(DAT_006da420,1);
      if (iVar2 == 0) {
        sub_567EA2();
      }
      param_1 = piVar3;
      if (*piVar3 != -0x1f928c9d) goto LAB_0056780f;
      if (((piVar3[4] == 3) && (piVar3[5] == 0x19930520)) && (piVar3[7] == 0)) {
        sub_567EA2();
      }
    }
    iVar2 = local_14;
    if (((*param_1 == -0x1f928c9d) && (param_1[4] == 3)) && (param_1[5] == 0x19930520)) {
      piVar3 = (int *)sub_563181(param_5,param_7,local_14,&local_8,&local_1c);
      do {
        if (local_1c <= local_8) {
          if (param_6 == '\0') {
            return;
          }
          sub_567D68(param_1,1);
          return;
        }
        if ((*piVar3 <= iVar2) && (iVar2 <= piVar3[1])) {
          iVar1 = piVar3[4];
          for (local_10 = piVar3[3]; iVar2 = local_14, 0 < local_10; local_10 = local_10 + -1) {
            piVar4 = *(int **)(param_1[7] + 0xc);
            for (local_c = *piVar4; 0 < local_c; local_c = local_c + -1) {
              piVar4 = piVar4 + 1;
              iVar2 = sub_5678E2(iVar1,*piVar4,param_1[7]);
              if (iVar2 != 0) {
                sub_5679F3(param_1,param_2,param_3,param_4,param_5,iVar1,*piVar4,piVar3,param_7,
                           param_8,local_18);
                iVar2 = local_14;
                goto LAB_005677ef;
              }
            }
            iVar1 = iVar1 + 0x10;
          }
        }
LAB_005677ef:
        local_8 = local_8 + 1;
        piVar3 = piVar3 + 5;
      } while( true );
    }
  }
LAB_0056780f:
  if (param_6 == '\0') {
    sub_56783A(param_1,param_2,param_3,param_4,param_5,local_14,param_7,param_8);
    return;
  }
  sub_567E4C();
  return;
}

