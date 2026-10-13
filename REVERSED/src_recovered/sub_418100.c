/* Selected Ghidra export at 00418100. */

undefined4 sub_418100(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  sub_4170A0(DAT_00583b70);
  puVar2 = &DAT_005839f8;
  puVar3 = &DAT_00583420;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_00583b70 = &DAT_00571dd0;
  DAT_00583914 = 4;
  sub_417750();
  return 0;
}

