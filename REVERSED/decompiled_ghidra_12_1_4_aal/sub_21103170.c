/* _AAL_GetBitsPerSample@4 @ 21103170   39 bytes */

undefined2 _AAL_GetBitsPerSample_4(int param_1)

{
                    /* 0x3170  16  _AAL_GetBitsPerSample@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) != 0)) {
    return *(undefined2 *)(*(int *)(param_1 + 0x18) + 0xe);
  }
  return 0;
}

