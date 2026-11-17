/* _AAL_AllocateVoice@4 @ 21101580   102 bytes */

int * _AAL_AllocateVoice_4(uint param_1)

{
  int iVar1;
  int *piVar2;
  
                    /* 0x1580  1  _AAL_AllocateVoice@4 */
  if ((DAT_211155ac == 0) || (DAT_211155b4 == (undefined4 *)0x0)) {
    AAL_SetError(s_AAL_is_not_initialised_2111408c);
    return (int *)0x0;
  }
  if (param_1 == 0) {
    piVar2 = sub_21104840(DAT_211155ac);
    return piVar2;
  }
  if ((param_1 <= *(uint *)*DAT_211155b4) &&
     (iVar1 = *(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + param_1 * 0x30), iVar1 != 0)) {
    piVar2 = (int *)(**(code **)(iVar1 + 0x20))(param_1,0);
    return piVar2;
  }
  return (int *)0x0;
}

