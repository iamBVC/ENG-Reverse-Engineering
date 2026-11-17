/* _AAL_GetChannels@4 @ 211031a0   39 bytes */

undefined2 _AAL_GetChannels_4(int param_1)

{
                    /* 0x31a0  17  _AAL_GetChannels@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) != 0)) {
    return *(undefined2 *)(*(int *)(param_1 + 0x18) + 2);
  }
  return 0;
}

