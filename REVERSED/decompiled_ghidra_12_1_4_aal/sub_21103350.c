/* _AAL_GetADSVolume@4 @ 21103350   22 bytes */

undefined4 _AAL_GetADSVolume_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x3350  15  _AAL_GetADSVolume@4 */
  uVar1 = 0;
  if ((param_1 != 0) && (*(undefined4 **)(param_1 + 0x24) != (undefined4 *)0x0)) {
    uVar1 = **(undefined4 **)(param_1 + 0x24);
  }
  return uVar1;
}

