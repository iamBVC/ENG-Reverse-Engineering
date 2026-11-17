/* sub_54EED0 @ 0054eed0   126 bytes */

void sub_54EED0(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = sub_54BC00(param_1);
  if (*(int *)(param_1 + 0x120) != 0) {
    iVar3 = sub_404D60(*(int *)(param_1 + 0x120) + 0x18,param_1 + 0x30);
    iVar1 = *(int *)(param_1 + 0x24);
    uVar4 = iVar3 - iVar1;
    if (0x7ff000 < (int)uVar4) {
      uVar4 = uVar4 - 0x1000000;
    }
    if ((int)uVar4 < -0x7ff000) {
      uVar4 = uVar4 + 0x1000000;
    }
    uVar5 = (uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f);
    if (uVar2 < uVar5) {
      uVar5 = uVar2;
    }
    if (0 < (int)uVar4) {
      *(uint *)(param_1 + 0x24) = iVar1 + uVar5 & 0xffffff;
      return;
    }
    *(uint *)(param_1 + 0x24) = iVar1 - uVar5 & 0xffffff;
  }
  return;
}

