/* sub_4191C0 @ 004191c0   183 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4191C0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  
  bVar4 = *(int *)(DAT_00582260 + 0x70) != 0;
  if (bVar4) {
    DAT_00583c08 = DAT_00583c08 & 0xffffffef;
  }
  else {
    DAT_00583c08 = DAT_00583c08 | 0x10;
  }
  _DAT_00583bfc = (uint)bVar4;
  if (DAT_00584640 == 0) {
    _DAT_00583c28 = (&PTR_s_Uscita_0057bc84)[DAT_00584f04];
    _DAT_00571dac = 2;
  }
  else {
    _DAT_00583c28 = (&PTR_s_Continua_0057bb90)[DAT_00584f04];
    _DAT_00571dac = 6;
  }
  puVar2 = &DAT_00583420;
  puVar3 = &DAT_005839f8;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  if (DAT_00583b78 == 0) {
    DAT_00583b70 = &DAT_00571da0;
    DAT_00583910 = 0;
  }
  DAT_00583a68 = 0xffffffff;
  DAT_00583a6c = 0;
  DAT_00583b78 = 0;
  return;
}

