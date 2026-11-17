/* _AAL_ResumeVoice@4 @ 21101ab0   105 bytes */

void _AAL_ResumeVoice_4(int param_1)

{
  uint uVar1;
  int iVar2;
  
                    /* 0x1ab0  60  _AAL_ResumeVoice@4 */
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    uVar1 = *(uint *)(param_1 + 8);
    if (uVar1 == 0) {
      if ((((*(int *)(param_1 + 0x48 + *(int *)(param_1 + 0x58) * 4) != 0) &&
           (*(int *)(param_1 + 0x38 + *(int *)(param_1 + 0x58) * 4) != 0)) &&
          (*(int *)(param_1 + 0x18) != 0)) && (*(uint *)(param_1 + 0xc) != 0)) {
        *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffe | 2;
      }
    }
    else if ((uVar1 <= *(uint *)*DAT_211155b4) &&
            (iVar2 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar1 * 0x30), iVar2 != 0)) {
      (**(code **)(iVar2 + 0x34))(param_1);
      return;
    }
  }
  return;
}

