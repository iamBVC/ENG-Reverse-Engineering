/* _AAL_GetVoiceAttr@4 @ 211018a0   299 bytes */

void _AAL_GetVoiceAttr_4(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
                    /* 0x18a0  40  _AAL_GetVoiceAttr@4 */
  if (((DAT_211155ac == 0) || (param_1 == (uint *)0x0)) || (uVar1 = param_1[1], uVar1 == 0)) {
    AAL_SetError(s_AAL_is_not_initialised_or_invali_211140a4);
  }
  else {
    uVar2 = *(uint *)(uVar1 + 8);
    if (uVar2 == 0) {
      uVar2 = *param_1;
      if ((uVar2 & 1) != 0) {
        param_1[2] = *(uint *)(uVar1 + 0x118);
      }
      if ((uVar2 & 2) != 0) {
        *(short *)(param_1 + 3) = *(short *)(uVar1 + 0x88) << 3;
        *(short *)((int)param_1 + 0xe) = *(short *)(uVar1 + 0x8c) << 3;
      }
      if ((uVar2 & 4) != 0) {
        param_1[0x2f] = *(uint *)(uVar1 + 100);
      }
      if ((uVar2 & 0x10) != 0) {
        param_1[0x2e] = *(uint *)(uVar1 + 0x6c);
      }
      if ((uVar2 & 8) != 0) {
        param_1[0x2c] = *(uint *)(uVar1 + 0x108);
        param_1[0x2d] = *(uint *)(uVar1 + 0xfc);
      }
      if ((uVar2 & 0x200) != 0) {
        param_1[0x33] = *(uint *)(uVar1 + 0x24);
      }
      if ((uVar2 & 0x400) != 0) {
        param_1[0x34] = *(uint *)(uVar1 + 0x20);
      }
      if ((uVar2 & 0x800) != 0) {
        param_1[0x35] = *(uint *)(uVar1 + 0x1c);
      }
      if ((uVar2 & 0x8000) != 0) {
        param_1[0x18] = *(uint *)(uVar1 + 0xb8);
        param_1[0x19] = *(uint *)(uVar1 + 0x28);
        param_1[0x1a] = *(uint *)(uVar1 + 0x2c);
        param_1[0x1b] = *(uint *)(uVar1 + 0x30);
        param_1[0x1c] = *(uint *)(uVar1 + 0x34);
        return;
      }
    }
    else if ((uVar2 <= *(uint *)*DAT_211155b4) &&
            (iVar3 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar2 * 0x30), iVar3 != 0)) {
      (**(code **)(iVar3 + 0x40))(uVar1,param_1);
      return;
    }
  }
  return;
}

