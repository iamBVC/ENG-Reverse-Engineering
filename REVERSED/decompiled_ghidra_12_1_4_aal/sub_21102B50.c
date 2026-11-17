/* _AAL_UnregisterTimer@4 @ 21102b50   28 bytes */

void _AAL_UnregisterTimer_4(int param_1)

{
                    /* 0x2b50  75  _AAL_UnregisterTimer@4 */
  if ((DAT_211155b0 != (void *)0x0) && (param_1 != -1)) {
    sub_21109D20(DAT_211155b0,param_1);
  }
  return;
}

