/* _AAL_GetSFSampleCount@4 @ 21103290   23 bytes */

undefined4 _AAL_GetSFSampleCount_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3290  37  _AAL_GetSFSampleCount@4 */
  uVar1 = 0;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x54);
  }
  return uVar1;
}

