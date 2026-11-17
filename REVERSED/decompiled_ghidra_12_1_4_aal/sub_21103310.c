/* _AAL_GetADSR@12 @ 21103310   49 bytes */

undefined4 _AAL_GetADSR_12(int param_1,undefined4 *param_2,undefined4 *param_3)

{
                    /* 0x3310  14  _AAL_GetADSR@12 */
  if ((param_1 != 0) && (*(int *)(param_1 + 0x24) != 0)) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 8);
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 8);
    }
  }
  return 0;
}

