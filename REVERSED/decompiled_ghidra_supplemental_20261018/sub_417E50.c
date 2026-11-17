/* Selected Ghidra export at 00417e50. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DWORD sub_417E50(void)

{
  char cVar1;
  DWORD DVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if ((((DAT_00583420 != DAT_005839f8) || (DAT_00583424 != DAT_005839fc)) ||
      (DAT_00583428 != DAT_00583a00)) || (DVar2 = DAT_0058342c, DAT_0058342c != DAT_00583a04)) {
    sub_546170(0,0xffffff81,8);
    sub_408300();
    sub_40FE10();
    cVar1 = sub_40FD80();
    if (cVar1 != '\0') {
      sub_410430();
      sub_424590();
      sub_438180();
      cVar1 = sub_4071D0();
      if (cVar1 != '\0') {
        sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
        sub_437D00();
        sub_439600();
        sub_435CE0();
        sub_4170A0(DAT_00583b70);
        DAT_00583b70 = &DAT_00571e30;
        _DAT_005839d0 = timeGetTime();
        _DAT_00571e3c = 2;
        return _DAT_005839d0;
      }
    }
    puVar4 = &DAT_00583420;
    puVar5 = &DAT_00583958;
    for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    cVar1 = sub_40FE30();
    if (cVar1 != '\0') {
      sub_410430();
      sub_424590();
      sub_438180();
      cVar1 = sub_4071D0();
      if (cVar1 != '\0') {
        sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
        sub_437D00();
        sub_439600();
        DVar2 = sub_435CE0();
        puVar4 = &DAT_00583958;
        puVar5 = &DAT_00583420;
        for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        return DVar2;
      }
    }
    sub_41DF60();
    DVar2 = 0;
  }
  return DVar2;
}

