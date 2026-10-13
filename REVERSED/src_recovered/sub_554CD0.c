/* Selected Ghidra export at 00554cd0. */

void sub_554CD0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  iVar3 = sub_404D60(iVar2 + 0x30,param_1 + 0x30);
  iVar2 = *(int *)(param_1 + 0x24);
  uVar4 = iVar3 - iVar2;
  if (0x7ff000 < (int)uVar4) {
    uVar4 = uVar4 - 0x1000000;
  }
  if ((int)uVar4 < -0x7ff000) {
    uVar4 = uVar4 + 0x1000000;
  }
  uVar5 = (uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f);
  if (uVar1 < uVar5) {
    uVar5 = uVar1;
  }
  if (0 < (int)uVar4) {
    *(uint *)(param_1 + 0x24) = iVar2 + uVar5 & 0xffffff;
    return;
  }
  *(uint *)(param_1 + 0x24) = iVar2 - uVar5 & 0xffffff;
  return;
}

