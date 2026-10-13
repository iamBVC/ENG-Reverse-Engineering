/* Selected Ghidra export at 0054e720. */

void sub_54E720(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  
  iVar1 = sub_54BC00(param_1);
  uVar3 = (uint)*(ushort *)(param_1 + 0xc6);
  uVar2 = 0;
  if (uVar3 != 0) {
    pbVar4 = *(byte **)(param_1 + 200);
    do {
      if ((ushort)*pbVar4 == (ushort)(iVar1 >> 0xc)) break;
      uVar2 = uVar2 + 1;
      pbVar4 = pbVar4 + 4;
    } while ((int)uVar2 < (int)uVar3);
  }
  if (uVar2 != uVar3) {
    if ((int)uVar2 < (int)(uVar3 - 1)) {
      do {
        uVar2 = uVar2 + 1;
        *(undefined4 *)(*(int *)(param_1 + 200) + -4 + uVar2 * 4) =
             *(undefined4 *)(*(int *)(param_1 + 200) + uVar2 * 4);
      } while ((int)uVar2 < (int)(*(ushort *)(param_1 + 0xc6) - 1));
    }
    *(short *)(param_1 + 0xc6) = *(short *)(param_1 + 0xc6) + -1;
  }
  return;
}

