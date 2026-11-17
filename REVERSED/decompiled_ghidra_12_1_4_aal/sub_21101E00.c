/* _AAL_GetDeviceId@4 @ 21101e00   50 bytes */

int _AAL_GetDeviceId_4(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
                    /* 0x1e00  24  _AAL_GetDeviceId@4 */
  iVar2 = 0;
  puVar1 = DAT_21115598;
  if ((param_1 == 1) || (puVar1 = DAT_2111559c, param_1 == 2)) {
    for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      if (puVar1[5] != 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    }
  }
  return -1;
}

