/* sub_40E6F0 @ 0040e6f0   252 bytes */

undefined1 sub_40E6F0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  puVar6 = &DAT_00582a70;
  for (iVar3 = 0x38; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  DAT_00582a70 = param_1;
  iVar3 = DirectInputCreateA(param_2,0x700,&DAT_00582a74,0);
  if (iVar3 != 0) {
    return 0;
  }
  sub_40E9A0();
  cVar1 = sub_40E880();
  if (cVar1 == '\0') {
    return 0;
  }
  if (DAT_005fcf70 != (HGLOBAL)0x0) {
    GlobalFree(DAT_005fcf70);
  }
  DAT_005fcf6c = 1;
  for (piVar2 = DAT_00582260; (*piVar2 != 0 || (piVar2[1] == 0)); piVar2 = (int *)*piVar2) {
    DAT_005fcf6c = DAT_005fcf6c + 1;
  }
  DAT_005fcf70 = GlobalAlloc(0x40,DAT_005fcf6c * 0xc);
  if (DAT_005fcf70 != (undefined4 *)0x0) {
    puVar6 = DAT_005fcf70;
    for (uVar4 = DAT_005fcf6c * 3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    iVar5 = 0xc;
    for (iVar3 = 0; piVar2 = DAT_00582260, iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    for (; (*piVar2 != 0 || (piVar2[1] == 0)); piVar2 = (int *)*piVar2) {
      if (piVar2[0x1d] != 0) {
        *(byte *)(iVar5 + 9 + (int)DAT_005fcf70) = ~(byte)((uint)piVar2[0x1d] >> 1) & 1;
      }
      iVar5 = iVar5 + 0xc;
    }
    sub_40E0A0();
    sub_419810();
    return 1;
  }
  return 0;
}

