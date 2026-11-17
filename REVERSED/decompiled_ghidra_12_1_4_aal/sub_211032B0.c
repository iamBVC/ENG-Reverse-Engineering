/* _AAL_GetSFKeyMap@4 @ 211032b0   23 bytes */

int _AAL_GetSFKeyMap_4(int param_1)

{
  int iVar1;
  
                    /* 0x32b0  34  _AAL_GetSFKeyMap@4 */
  iVar1 = 0;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar1 = *(int *)(param_1 + 0x20) + 0x5c;
  }
  return iVar1;
}

