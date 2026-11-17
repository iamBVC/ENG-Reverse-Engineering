/* _AAL_GetLoopEndOffset@4 @ 211032f0   28 bytes */

undefined4 _AAL_GetLoopEndOffset_4(int param_1)

{
                    /* 0x32f0  29  _AAL_GetLoopEndOffset@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc);
  }
  return 0;
}

