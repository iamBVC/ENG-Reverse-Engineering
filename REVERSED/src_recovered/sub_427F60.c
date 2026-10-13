/* Selected Ghidra export at 00427f60. */

void sub_427F60(void)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005fd180;
  iVar2 = 4;
  do {
    sub_402810(puVar1,0xc,0x14,&LAB_00427fa0);
    sub_402810(puVar1 + 0xf0,0x24,0x14,&LAB_00427fa0);
    puVar1 = puVar1 + 0x42c;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

