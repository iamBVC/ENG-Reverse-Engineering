/* sub_40C250 @ 0040c250   226 bytes */

uint sub_40C250(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar1 = *(uint *)(param_2 + 0x10);
  uVar2 = *(uint *)(param_2 + 0x14);
  uVar3 = *(uint *)(param_2 + 0x18);
  uVar4 = *(uint *)(param_2 + 0x1c);
  uVar5 = __ftol();
  uVar6 = __ftol();
  uVar7 = __ftol();
  uVar8 = __ftol();
  return uVar8 & uVar4 | uVar5 & uVar1 | uVar6 & uVar2 | uVar7 & uVar3;
}

