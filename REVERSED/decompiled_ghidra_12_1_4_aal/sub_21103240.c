/* _AAL_GetDataPointer@4 @ 21103240   16 bytes */

undefined4 _AAL_GetDataPointer_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3240  20  _AAL_GetDataPointer@4 */
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x34);
  }
  return uVar1;
}

