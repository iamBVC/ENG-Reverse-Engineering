/* Selected Ghidra export at 0054ee40. */

void sub_54EE40(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auStack_4 [4];
  
  iVar2 = param_1;
  uVar3 = sub_54BC00(param_1);
  sub_404DB0(*(int *)(iVar2 + 0x120) + 0x18,iVar2 + 0x30,auStack_4,&param_1);
  iVar1 = *(int *)(iVar2 + 0x20);
  uVar4 = (0x1000000 - param_1) - iVar1;
  if (0x7ff000 < (int)uVar4) {
    uVar4 = uVar4 - 0x1000000;
  }
  if ((int)uVar4 < -0x7ff000) {
    uVar4 = uVar4 + 0x1000000;
  }
  uVar5 = (uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f);
  if (uVar3 < uVar5) {
    uVar5 = uVar3;
  }
  if (0 < (int)uVar4) {
    *(uint *)(iVar2 + 0x20) = iVar1 + uVar5 & 0xffffff;
    return;
  }
  *(uint *)(iVar2 + 0x20) = iVar1 - uVar5 & 0xffffff;
  return;
}

