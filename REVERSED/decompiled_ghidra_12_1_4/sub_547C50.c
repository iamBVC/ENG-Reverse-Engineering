/* sub_547C50 @ 00547c50   144 bytes */

void sub_547C50(int param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = *(int *)(param_1 + 0x20);
  *(undefined2 *)(param_1 + 0x76) = 0;
  uVar5 = (int)(*(int *)(DAT_006d9490 + 0x100) * *param_2) >> 0xc;
  *param_2 = uVar5;
  if ((*(uint *)(param_1 + 0x3c) & 0x400) == 0) {
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar1 + 0x30);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar1 + 0x34);
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(iVar1 + 0x38);
    }
    uVar3 = sub_547B60(param_1 + 0x24,(undefined2 *)(param_1 + 0x76));
    *(uint *)(param_1 + 0x40) = uVar3;
    if (*(uint *)(param_1 + 0x34) < uVar3) {
      uVar2 = *(uint *)(param_1 + 0x38);
      uVar4 = uVar2 - *(uint *)(param_1 + 0x34);
      if ((uVar3 < uVar2) && (0 < (int)uVar4)) {
        *param_2 = ((uVar2 - uVar3) * uVar5) / uVar4;
        return;
      }
      *param_2 = 0;
    }
  }
  return;
}

