/* _AAL_PauseVoice@4 @ 21101a60   75 bytes */

void _AAL_PauseVoice_4(int param_1)

{
  uint uVar1;
  int iVar2;
  
                    /* 0x1a60  50  _AAL_PauseVoice@4
                       0x1a60  72  _AAL_StopVoice@4 */
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    uVar1 = *(uint *)(param_1 + 8);
    if (uVar1 == 0) {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffd | 1;
    }
    else if ((uVar1 <= *(uint *)*DAT_211155b4) &&
            (iVar2 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar1 * 0x30), iVar2 != 0)) {
      (**(code **)(iVar2 + 0x30))(param_1);
      return;
    }
  }
  return;
}

