/* Selected Ghidra export at 00418be0. */

undefined4 sub_418BE0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = &DAT_005847c8;
  puVar3 = &DAT_00584758;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  sub_418AA0();
  sub_419A60(0);
  return 0;
}

