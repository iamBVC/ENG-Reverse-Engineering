/* sub_568E66 @ 00568e66   153 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_568E66(void)

{
  void *pvVar1;
  char *pcVar2;
  int local_c;
  int local_8;
  
  if (DAT_006db928 == 0) {
    sub_56C06A();
  }
  GetModuleFileNameA((HMODULE)0x0,&DAT_006da438,0x104);
  _DAT_006da39c = &DAT_006da438;
  pcVar2 = &DAT_006da438;
  if (*DAT_006db920 != '\0') {
    pcVar2 = DAT_006db920;
  }
  sub_568EFF(pcVar2,0,0,&local_8,&local_c);
  pvVar1 = _malloc(local_c + local_8 * 4);
  if (pvVar1 == (void *)0x0) {
    __amsg_exit(8);
  }
  sub_568EFF(pcVar2,pvVar1,(void *)((int)pvVar1 + local_8 * 4),&local_8,&local_c);
  _DAT_006da384 = pvVar1;
  _DAT_006da380 = local_8 + -1;
  return;
}

