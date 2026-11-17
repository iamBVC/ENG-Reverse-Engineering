/* _AAL_StartVoice@4 @ 211019d0   130 bytes */

void _AAL_StartVoice_4(int param_1)

{
  uint uVar1;
  int iVar2;
  
                    /* 0x19d0  71  _AAL_StartVoice@4 */
  if ((DAT_211155ac == 0) || (param_1 == 0)) {
    AAL_SetError(s_AAL_is_not_initialised_2111408c);
  }
  else {
    uVar1 = *(uint *)(param_1 + 8);
    if (uVar1 == 0) {
      if ((((*(int *)(param_1 + 0xc) != 0) &&
           (iVar2 = *(int *)(param_1 + 0x58), *(int *)(param_1 + 0x48 + iVar2 * 4) != 0)) &&
          (*(int *)(param_1 + 0x38 + iVar2 * 4) != 0)) && (*(int *)(param_1 + 0x18) != 0)) {
        *(undefined4 *)(param_1 + 0x40 + iVar2 * 4) = 0;
        *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffe | 2;
        return;
      }
    }
    else if ((uVar1 <= *(uint *)*DAT_211155b4) &&
            (iVar2 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar1 * 0x30), iVar2 != 0)) {
      (**(code **)(iVar2 + 0x2c))(param_1);
      return;
    }
  }
  return;
}

