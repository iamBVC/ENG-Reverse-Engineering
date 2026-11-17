/* _AAL_FreeVoice@4 @ 21101660   94 bytes */

void _AAL_FreeVoice_4(int *param_1)

{
  uint uVar1;
  int iVar2;
  
                    /* 0x1660  11  _AAL_FreeVoice@4 */
  if (((DAT_211155ac == (void *)0x0) || (DAT_211155b4 == (undefined4 *)0x0)) ||
     (param_1 == (int *)0x0)) {
    AAL_SetError(s_AAL_is_not_initialised_2111408c);
  }
  else {
    uVar1 = param_1[2];
    if (uVar1 == 0) {
      sub_211048C0(DAT_211155ac,param_1);
      return;
    }
    if ((uVar1 <= *(uint *)*DAT_211155b4) &&
       (iVar2 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar1 * 0x30), iVar2 != 0)) {
      (**(code **)(iVar2 + 0x24))(param_1);
      return;
    }
  }
  return;
}

