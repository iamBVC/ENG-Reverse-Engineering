/* sub_5475B0 @ 005475b0   258 bytes */

void sub_5475B0(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x2c) != 0) {
    for (puVar1 = *(undefined4 **)(param_1 + 0x14); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((*(uint *)(param_1 + 0x2c) & 1 << (*(byte *)(puVar1 + 3) & 0x1f)) != 0) {
        _AAL_SetVoiceAttr_4(puVar1 + 4);
        puVar1[4] = 0;
      }
    }
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  uVar2 = *(uint *)(param_1 + 0x28);
  if (uVar2 != 0) {
    for (puVar1 = *(undefined4 **)(param_1 + 0x14); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((uVar2 & 1 << (*(byte *)(puVar1 + 3) & 0x1f)) != 0) {
        _AAL_StopVoice_4(puVar1[5]);
      }
    }
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  uVar2 = *(uint *)(param_1 + 0x24);
  if (uVar2 != 0) {
    for (puVar1 = *(undefined4 **)(param_1 + 0x14); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((uVar2 & 1 << (*(byte *)(puVar1 + 3) & 0x1f)) != 0) {
        _AAL_StartVoice_4(puVar1[5]);
      }
    }
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  if ((DAT_005834f4 != 0) && (*(int *)(DAT_006d9490 + 0x68) != 0)) {
    _AAL_Set3DAttributes_8(DAT_005834f4,DAT_006d9490 + 0x68);
    *(undefined4 *)(DAT_006d9490 + 0x68) = 0;
  }
  iVar3 = *(int *)(param_1 + 0x1c);
  if (iVar3 != 0) {
    do {
      sub_546E30(iVar3);
      sub_546E10(iVar3,param_1 + 0xc);
      iVar3 = *(int *)(param_1 + 0x1c);
    } while (iVar3 != 0);
  }
  return;
}

