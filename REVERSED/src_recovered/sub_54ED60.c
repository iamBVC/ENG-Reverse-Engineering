/* Selected Ghidra export at 0054ed60. */

void sub_54ED60(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iStack_4;
  
  iVar2 = param_1;
  uVar3 = sub_54BC00(param_1);
  sub_404DB0(*(int *)(iVar2 + 0x120) + 0x18,iVar2 + 0x30,&param_1,&iStack_4);
  uVar5 = param_1 - *(int *)(iVar2 + 0x24);
  if (0x7ff000 < (int)uVar5) {
    uVar5 = uVar5 - 0x1000000;
  }
  if ((int)uVar5 < -0x7ff000) {
    uVar5 = uVar5 + 0x1000000;
  }
  uVar4 = (uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f);
  if (uVar3 < uVar4) {
    uVar4 = uVar3;
  }
  if ((int)uVar5 < 1) {
    uVar4 = -uVar4;
  }
  iVar1 = *(int *)(iVar2 + 0x20);
  *(uint *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + uVar4 & 0xffffff;
  uVar5 = (0x1000000 - iStack_4) - iVar1;
  if (0x7ff000 < (int)uVar5) {
    uVar5 = uVar5 - 0x1000000;
  }
  if ((int)uVar5 < -0x7ff000) {
    uVar5 = uVar5 + 0x1000000;
  }
  uVar4 = (uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f);
  if (uVar3 < uVar4) {
    uVar4 = uVar3;
  }
  if ((int)uVar5 < 1) {
    *(uint *)(iVar2 + 0x20) = iVar1 - uVar4 & 0xffffff;
    return;
  }
  *(uint *)(iVar2 + 0x20) = iVar1 + uVar4 & 0xffffff;
  return;
}

