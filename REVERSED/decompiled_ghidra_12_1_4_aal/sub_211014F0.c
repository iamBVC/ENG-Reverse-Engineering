/* _AAL_SetDriverInfo@4 @ 211014f0   108 bytes */

undefined4 _AAL_SetDriverInfo_4(byte *param_1)

{
  int iVar1;
  
                    /* 0x14f0  62  _AAL_SetDriverInfo@4 */
  if (DAT_211155ac != 0) {
    if ((*param_1 & 2) != 0) {
      *(undefined4 *)(DAT_211155ac + 0x58) = *(undefined4 *)(param_1 + 0xc);
    }
    iVar1 = DAT_211155ac;
    if ((*param_1 & 1) != 0) {
      *(undefined4 *)(DAT_211155ac + 0xbc) = *(undefined4 *)(param_1 + 0x10);
      *(undefined4 *)(iVar1 + 0xc0) = *(undefined4 *)(param_1 + 0x14);
      *(undefined4 *)(iVar1 + 0xc4) = *(undefined4 *)(param_1 + 0x18);
      *(undefined4 *)(iVar1 + 200) = *(undefined4 *)(param_1 + 0x1c);
    }
    if ((*param_1 & 4) != 0) {
      *(uint *)(DAT_211155ac + 0xcc) =
           *(uint *)(DAT_211155ac + 0xcc) & 0xffff | *(uint *)(param_1 + 0x20);
    }
  }
  return 0;
}

