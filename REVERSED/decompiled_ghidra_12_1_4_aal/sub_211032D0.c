/* _AAL_GetLoopStartOffset@4 @ 211032d0   28 bytes */

undefined4 _AAL_GetLoopStartOffset_4(int param_1)

{
                    /* 0x32d0  30  _AAL_GetLoopStartOffset@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0x1c) + 8);
  }
  return 0;
}

