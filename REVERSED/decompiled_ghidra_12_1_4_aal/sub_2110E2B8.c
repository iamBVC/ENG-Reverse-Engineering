/* sub_2110E2B8 @ 2110e2b8   153 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_2110E2B8(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  int local_c;
  int local_8;
  
  if (DAT_21115b4c == 0) {
    sub_21110138();
  }
  GetModuleFileNameA((HMODULE)0x0,&DAT_2111566c,0x104);
  _DAT_21115658 = &DAT_2111566c;
  pbVar2 = &DAT_2111566c;
  if (*DAT_21115b58 != 0) {
    pbVar2 = DAT_21115b58;
  }
  sub_2110E351(pbVar2,(undefined4 *)0x0,(byte *)0x0,&local_8,&local_c);
  puVar1 = _malloc(local_c + local_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    __amsg_exit(8);
  }
  sub_2110E351(pbVar2,puVar1,(byte *)(puVar1 + local_8),&local_8,&local_c);
  _DAT_21115640 = puVar1;
  _DAT_2111563c = local_8 + -1;
  return;
}

