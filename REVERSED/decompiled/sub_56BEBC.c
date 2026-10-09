/* sub_56BEBC @ 0056bebc   41 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_56BEBC(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_006da6c0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_006da5ac = 0;
  _DAT_006da5bc = 0;
  DAT_006da7c4 = 0;
  DAT_006da5b0 = 0;
  DAT_006da5b4 = 0;
  DAT_006da5b8 = 0;
  return;
}

