/* sub_2110FF8A @ 2110ff8a   41 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_2110FF8A(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_21115920;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_211157f0 = 0;
  _DAT_2111580c = 0;
  DAT_21115a24 = 0;
  DAT_21115800 = 0;
  DAT_21115804 = 0;
  DAT_21115808 = 0;
  return;
}

