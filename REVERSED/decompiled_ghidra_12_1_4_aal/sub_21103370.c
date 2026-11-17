/* _AAL_GetADSFlags@4 @ 21103370   23 bytes */

undefined4 _AAL_GetADSFlags_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3370  13  _AAL_GetADSFlags@4 */
  uVar1 = 0;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x24) != 0)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 4);
  }
  return uVar1;
}

