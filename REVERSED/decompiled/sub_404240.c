/* sub_404240 @ 00404240   176 bytes */

void sub_404240(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_4;
  
  iVar1 = (int)*(short *)(param_1 + 0xd2);
  iVar2 = *(int *)(param_1 + 0x30) + iVar1 * -2 >> 0xc;
  uVar3 = *(int *)(param_1 + 0x30) + iVar1 * 2 >> 0xc;
  local_4 = *(int *)(param_1 + 0x38) + iVar1 * -2 >> 0xc;
  uVar4 = *(int *)(param_1 + 0x38) + iVar1 * 2 >> 0xc;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (*(int *)(param_3 + 0x14) - 1U < uVar3) {
    uVar3 = *(int *)(param_3 + 0x14) - 1;
  }
  if (local_4 < 0) {
    local_4 = 0;
  }
  if (*(int *)(param_3 + 0x18) - 1U < uVar4) {
    uVar4 = *(int *)(param_3 + 0x18) - 1;
  }
  for (; iVar1 = local_4, iVar2 <= (int)uVar3; iVar2 = iVar2 + 1) {
    for (; iVar1 <= (int)uVar4; iVar1 = iVar1 + 1) {
      sub_4042F0(iVar2,iVar1,param_1,param_2,param_3,param_4);
    }
  }
  return;
}

