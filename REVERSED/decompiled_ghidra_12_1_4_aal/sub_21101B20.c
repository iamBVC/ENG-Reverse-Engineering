/* _AAL_GetPlayStatus@4 @ 21101b20   29 bytes */

uint _AAL_GetPlayStatus_4(int param_1)

{
  uint uVar1;
  
                    /* 0x1b20  33  _AAL_GetPlayStatus@4 */
  uVar1 = 0;
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    uVar1 = *(uint *)(param_1 + 0xc) & 2;
  }
  return uVar1;
}

