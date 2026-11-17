/* sub_41F630 @ 0041f630   173 bytes */

void sub_41F630(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char local_80 [128];
  
  pcVar2 = local_80;
  local_80[0] = *param_1;
  if (*param_1 != '\0') {
    do {
      cVar1 = pcVar2[(int)(param_1 + (1 - (int)local_80))];
      pcVar2 = pcVar2 + 1;
      *pcVar2 = cVar1;
    } while (cVar1 != '\0');
  }
  iVar4 = 0;
  pcVar2 = s_132INTRO_00572640;
  do {
    iVar3 = sub_41F600(local_80,pcVar2);
    if (iVar3 == 0) {
      iVar3 = 0;
      goto LAB_0041f68a;
    }
    pcVar2 = pcVar2 + 0x12;
    iVar4 = iVar4 + 1;
  } while ((int)pcVar2 < 0x572664);
  goto LAB_0041f6bd;
  while (iVar3 = iVar3 + 1, iVar3 < 8) {
LAB_0041f68a:
    cVar1 = s_131INTRO_00572649[iVar4 * 0x12 + iVar3];
    local_80[iVar3] = cVar1;
    if (cVar1 == '\0') break;
  }
  builtin_strncpy(local_80 + iVar3,".DAT",5);
  local_80[iVar3 + 5] = '\0';
LAB_0041f6bd:
  DAT_005865e4 = 0;
  sub_41F590(local_80);
  return;
}

