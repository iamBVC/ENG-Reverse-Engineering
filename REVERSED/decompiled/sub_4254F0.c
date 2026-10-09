/* sub_4254F0 @ 004254f0   17 bytes */

void sub_4254F0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005f6ef8;
  for (iVar1 = 0x1800; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

