/* sub_568DAD @ 00568dad   185 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_568DAD(void)

{
  char cVar1;
  size_t sVar2;
  undefined4 *puVar3;
  void *pvVar4;
  int iVar5;
  char *pcVar6;
  
  if (DAT_006db928 == 0) {
    sub_56C06A();
  }
  iVar5 = 0;
  for (pcVar6 = DAT_006da3b0; *pcVar6 != '\0'; pcVar6 = pcVar6 + sVar2 + 1) {
    if (*pcVar6 != '=') {
      iVar5 = iVar5 + 1;
    }
    sVar2 = _strlen(pcVar6);
  }
  puVar3 = _malloc(iVar5 * 4 + 4);
  _DAT_006da38c = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    __amsg_exit(9);
  }
  cVar1 = *DAT_006da3b0;
  pcVar6 = DAT_006da3b0;
  while (cVar1 != '\0') {
    sVar2 = _strlen(pcVar6);
    if (*pcVar6 != '=') {
      pvVar4 = _malloc(sVar2 + 1);
      *puVar3 = pvVar4;
      if (pvVar4 == (void *)0x0) {
        __amsg_exit(9);
      }
      sub_569990(*puVar3,pcVar6);
      puVar3 = puVar3 + 1;
    }
    pcVar6 = pcVar6 + sVar2 + 1;
    cVar1 = *pcVar6;
  }
  sub_5628BC(DAT_006da3b0);
  DAT_006da3b0 = (char *)0x0;
  *puVar3 = 0;
  _DAT_006db924 = 1;
  return;
}

