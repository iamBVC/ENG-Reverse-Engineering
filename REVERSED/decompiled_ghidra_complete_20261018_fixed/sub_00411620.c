/* sub_411620 @ 00411620   135 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_411620(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = DAT_00583424;
  _DAT_00583400 = *(undefined4 *)(DAT_00583420 + 0x14);
  _DAT_00583404 = *(undefined4 *)(DAT_00583420 + 0x18);
  puVar3 = (undefined4 *)(DAT_00583424 + 0x10);
  puVar4 = (undefined4 *)&DAT_005833e0;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar3 = (undefined4 *)(DAT_0058342c + 0x5c);
  puVar4 = &DAT_005833c0;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar3 = (undefined4 *)(iVar1 + 0x58);
  puVar4 = &DAT_00583490;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar3 = (undefined4 *)(iVar1 + 0x78);
  puVar4 = &DAT_005834b0;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar3 = (undefined4 *)(iVar1 + 0x98);
  puVar4 = &DAT_00583470;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar3 = (undefined4 *)(iVar1 + 0xb8);
  puVar4 = &DAT_00583450;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return;
}

