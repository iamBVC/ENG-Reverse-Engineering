/* sub_439110 @ 00439110   68 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_439110(undefined1 *param_1)

{
  if (param_1 != (undefined1 *)0x0) {
    _DAT_006d8410 = 0;
    _DAT_006d8734 = 0;
    DAT_006d7c74 = (uint)CONCAT21(CONCAT11(*param_1,param_1[1]),param_1[2]);
    return;
  }
  DAT_006d7c74 = 0;
  _DAT_006d8410 = 0;
  _DAT_006d8734 = 0;
  return;
}

