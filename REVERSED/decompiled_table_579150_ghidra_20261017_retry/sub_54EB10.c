/* Selected Ghidra export at 0054eb10. */

void sub_54EB10(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auStack_24 [20];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  iVar2 = param_1;
  uVar3 = sub_54BC00(param_1);
  uStack_8 = sub_54BC00(iVar2);
  uStack_c = sub_54BC00(iVar2);
  uStack_10 = sub_54BC00(iVar2);
  sub_404DB0(&uStack_10,iVar2 + 0x30,auStack_24,&param_1);
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

