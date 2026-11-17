/* _AAL_GetDeviceName@8 @ 21101e70   67 bytes */

undefined4 _AAL_GetDeviceName_8(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
                    /* 0x1e70  26  _AAL_GetDeviceName@8 */
  iVar2 = 0;
  puVar1 = DAT_21115598;
  if (((param_1 == 1) || (puVar1 = DAT_2111559c, param_1 == 2)) && (puVar1 != (undefined4 *)0x0)) {
    for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      if (iVar2 == param_2) {
        return puVar1[6];
      }
      iVar2 = iVar2 + 1;
    }
  }
  return 0;
}

