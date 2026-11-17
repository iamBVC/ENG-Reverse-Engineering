/* _AAL_GetDataDuration@4 @ 21103220   16 bytes */

undefined4 _AAL_GetDataDuration_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3220  19  _AAL_GetDataDuration@4 */
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x28);
  }
  return uVar1;
}

