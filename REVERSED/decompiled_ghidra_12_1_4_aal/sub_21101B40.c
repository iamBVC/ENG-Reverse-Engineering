/* _AAL_SetPlayPosition@8 @ 21101b40   76 bytes */

undefined4 _AAL_SetPlayPosition_8(int param_1,uint param_2)

{
                    /* 0x1b40  65  _AAL_SetPlayPosition@8 */
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    if (*(uint *)(param_1 + 8) == 0) {
      if (param_2 < *(uint *)(param_1 + 0x48 + *(int *)(param_1 + 0x58) * 4)) {
        *(uint *)(param_1 + 0x40 + *(int *)(param_1 + 0x58) * 4) = param_2;
      }
    }
    else if (*(uint *)(param_1 + 8) <= *(uint *)*DAT_211155b4) {
      return 0;
    }
  }
  return 0;
}

