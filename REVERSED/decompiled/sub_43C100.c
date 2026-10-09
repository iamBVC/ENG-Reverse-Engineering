/* sub_43C100 @ 0043c100   174 bytes */

void sub_43C100(int param_1,short *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int local_4;
  
  local_4 = 0;
  if (0 < param_2[7]) {
    do {
      iVar4 = (int)param_2[6];
      iVar6 = 0;
      if (0 < iVar4) {
        do {
          iVar3 = ((int)*param_2 + iVar6 + (param_2[1] + local_4) * (int)*(short *)(param_1 + 0xc))
                  * 3;
          pcVar5 = (char *)(*(int *)(param_2 + 0x10a) + (iVar4 * local_4 + iVar6) * 3);
          cVar1 = pcVar5[1];
          cVar2 = pcVar5[2];
          if (((*pcVar5 != '\0') || (cVar1 != -1)) || (cVar2 != -1)) {
            *(char *)(iVar3 + *(int *)(param_1 + 0x214)) = *pcVar5;
            *(char *)(iVar3 + 1 + *(int *)(param_1 + 0x214)) = cVar1;
            *(char *)(iVar3 + 2 + *(int *)(param_1 + 0x214)) = cVar2;
          }
          iVar4 = (int)param_2[6];
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
      }
      local_4 = local_4 + 1;
    } while (local_4 < param_2[7]);
  }
  return;
}

