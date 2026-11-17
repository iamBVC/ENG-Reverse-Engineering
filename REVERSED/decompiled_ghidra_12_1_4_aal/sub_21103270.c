/* _AAL_GetSFMapCount@4 @ 21103270   23 bytes */

undefined4 _AAL_GetSFMapCount_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3270  35  _AAL_GetSFMapCount@4 */
  uVar1 = 0;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x58);
  }
  return uVar1;
}

