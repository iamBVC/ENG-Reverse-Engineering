/* Selected Ghidra export at 00418050. */

undefined4 sub_418050(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar3 = &DAT_00583420;
  puVar4 = &DAT_00583958;
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  sub_408300();
  sub_40FE10();
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
      sub_435CE0();
      DAT_00583914 = 4;
      puVar3 = &DAT_005839f8;
      puVar4 = &DAT_00583420;
      for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      sub_417750();
      DAT_00583b70 = sub_4170C0();
      return 0;
    }
  }
  sub_41DF60();
  return 0;
}

