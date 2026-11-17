/* _AAL_GetDataSize@4 @ 21103210   16 bytes */

undefined4 _AAL_GetDataSize_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3210  21  _AAL_GetDataSize@4 */
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x2c);
  }
  return uVar1;
}

