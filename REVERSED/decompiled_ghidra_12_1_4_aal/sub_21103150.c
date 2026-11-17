/* _AAL_GetSampleRate@4 @ 21103150   28 bytes */

undefined4 _AAL_GetSampleRate_4(int param_1)

{
                    /* 0x3150  38  _AAL_GetSampleRate@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0x18) + 4);
  }
  return 0;
}

