/* sub_547840 @ 00547840   67 bytes */

void sub_547840(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = 1 << (*(byte *)(param_2 + 0xc) & 0x1f);
    *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 0x24) | uVar1;
    _AAL_SetVoiceAttr_4((undefined4 *)(param_2 + 0x10));
    *(undefined4 *)(param_2 + 0x10) = 0;
    if ((uVar1 & *(uint *)(param_1 + 0x28)) != 0) {
      *(uint *)(param_1 + 0x28) = ~uVar1 & *(uint *)(param_1 + 0x28);
    }
  }
  return;
}

