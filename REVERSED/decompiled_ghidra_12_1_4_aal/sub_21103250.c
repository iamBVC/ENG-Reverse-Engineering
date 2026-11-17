/* _AAL_GetSFProgramCount@4 @ 21103250   23 bytes */

undefined4 _AAL_GetSFProgramCount_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3250  36  _AAL_GetSFProgramCount@4 */
  uVar1 = 0;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x50);
  }
  return uVar1;
}

