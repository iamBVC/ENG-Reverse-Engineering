/* sub_43AD50 @ 0043ad50   51 bytes */

void sub_43AD50(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar2 = &DAT_006d8750;
  do {
    puVar3 = puVar2 + 0x25;
    puVar4 = puVar2 + 4;
    for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    *puVar2 = 0;
    puVar2[2] = 0;
    puVar2 = puVar3;
  } while ((int)puVar3 < 0x6d91b8);
  DAT_006d8748 = 0;
  return;
}

