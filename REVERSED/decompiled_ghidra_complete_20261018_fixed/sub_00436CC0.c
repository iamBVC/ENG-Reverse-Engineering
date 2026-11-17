/* sub_436CC0 @ 00436cc0   113 bytes */

void sub_436CC0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  DAT_006d76c8 = param_1;
  iVar1 = 0;
  piVar2 = &DAT_0061fb34;
  do {
    piVar3 = piVar2 + 1;
    *piVar2 = iVar1 * iVar1;
    iVar1 = iVar1 + 1;
    piVar2 = piVar3;
  } while ((int)piVar3 < 0x61ff34);
  puVar4 = &DAT_006b4544;
  for (iVar1 = 0x8c61; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_006913c0;
  for (iVar1 = 0x8c61; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_0066e23c;
  for (iVar1 = 0x8c61; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_0064b0b8;
  for (iVar1 = 0x8c61; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_00627f34;
  for (iVar1 = 0x8c61; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_0061ff34;
  for (iVar1 = 0x2000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  return;
}

