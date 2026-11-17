/* _AAL_GetLoopType@4 @ 211031d0   49 bytes */

bool _AAL_GetLoopType_4(int param_1)

{
                    /* 0x31d0  31  _AAL_GetLoopType@4 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) {
    return *(int *)(*(int *)(param_1 + 0x1c) + 0x14) == 0;
  }
  return false;
}

