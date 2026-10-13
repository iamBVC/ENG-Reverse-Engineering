/* Selected Ghidra export at 00418020. */

undefined4 sub_418020(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = &DAT_00583420;
  puVar3 = &DAT_005839f8;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  sub_410330();
  DAT_00583b70 = sub_4170C0();
  return 0;
}

