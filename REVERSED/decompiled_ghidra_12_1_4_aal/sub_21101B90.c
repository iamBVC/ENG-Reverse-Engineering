/* _AAL_GetPlayPosition@4 @ 21101b90   74 bytes */

undefined4 _AAL_GetPlayPosition_4(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
                    /* 0x1b90  32  _AAL_GetPlayPosition@4 */
  uVar2 = 0;
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    uVar1 = *(uint *)(param_1 + 8);
    if (uVar1 == 0) {
      uVar2 = *(undefined4 *)(param_1 + 0x40 + *(int *)(param_1 + 0x58) * 4);
    }
    else if ((*(uint *)*DAT_211155b4 < uVar1) ||
            (*(int *)(((uint *)*DAT_211155b4)[3] + 0x10 + uVar1 * 0x30) == 0)) {
      return 0;
    }
  }
  return uVar2;
}

