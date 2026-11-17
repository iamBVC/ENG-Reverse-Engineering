/* sub_56783A @ 0056783a   168 bytes */

void sub_56783A(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint local_c;
  uint local_8;
  
  if ((DAT_006da428 != 0) &&
     (iVar1 = sub_563058(param_1,param_2,param_3,param_4,param_5,param_7,param_8), iVar1 != 0)) {
    return;
  }
  piVar2 = (int *)sub_563181(param_5,param_7,param_6,&local_8,&local_c);
  for (; local_8 < local_c; local_8 = local_8 + 1) {
    if ((*piVar2 <= param_6) && (param_6 <= piVar2[1])) {
      iVar3 = piVar2[3] * 0x10 + piVar2[4];
      iVar1 = *(int *)(iVar3 + -0xc);
      if ((iVar1 == 0) || (*(char *)(iVar1 + 8) == '\0')) {
        sub_5679F3(param_1,param_2,param_3,param_4,param_5,iVar3 + -0x10,0,piVar2,param_7,param_8,1)
        ;
      }
    }
    piVar2 = piVar2 + 5;
  }
  return;
}

