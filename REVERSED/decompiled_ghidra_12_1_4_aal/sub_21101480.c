/* _AAL_GetDriverInfo@4 @ 21101480   99 bytes */

undefined4 _AAL_GetDriverInfo_4(int param_1)

{
  int iVar1;
  
                    /* 0x1480  27  _AAL_GetDriverInfo@4 */
  if ((DAT_211155ac != 0) && (param_1 != 0)) {
    *(undefined4 *)(param_1 + 4) = *(undefined4 *)(DAT_211155ac + 0xb8);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(DAT_211155ac + 0xb4);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(DAT_211155ac + 0xcc);
    iVar1 = DAT_211155ac;
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(DAT_211155ac + 0xbc);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(iVar1 + 0xc0);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar1 + 0xc4);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar1 + 200);
  }
  return 0;
}

