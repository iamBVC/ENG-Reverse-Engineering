/* _AAL_GetDataType@4 @ 21103230   16 bytes */

undefined4 _AAL_GetDataType_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3230  22  _AAL_GetDataType@4 */
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x30);
  }
  return uVar1;
}

