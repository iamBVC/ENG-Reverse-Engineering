/* _AAL_GetCurrentMix@0 @ 21101be0   19 bytes */

undefined4 _AAL_GetCurrentMix_0(void)

{
  undefined4 uVar1;
  
                    /* 0x1be0  18  _AAL_GetCurrentMix@0 */
  uVar1 = 0;
  if (DAT_211155ac != 0) {
    uVar1 = *(undefined4 *)(DAT_211155ac + 0xac);
  }
  return uVar1;
}

