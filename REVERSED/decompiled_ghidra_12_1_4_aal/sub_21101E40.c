/* _AAL_GetDeviceCount@4 @ 21101e40   40 bytes */

int _AAL_GetDeviceCount_4(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
                    /* 0x1e40  23  _AAL_GetDeviceCount@4 */
  iVar2 = 0;
  puVar1 = DAT_21115598;
  if ((param_1 == 1) || (puVar1 = DAT_2111559c, param_1 == 2)) {
    for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

