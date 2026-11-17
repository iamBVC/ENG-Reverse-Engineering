/* _AAL_QuitDriver@4 @ 21101420   85 bytes */

undefined4 _AAL_QuitDriver_4(int param_1)

{
                    /* 0x1420  53  _AAL_QuitDriver@4 */
  if (DAT_211155ac != (undefined4 *)0x0) {
    sub_21104A10(DAT_211155ac,param_1);
    if (param_1 != 0) {
      if (DAT_211155ac != (undefined4 *)0x0) {
        (**(code **)*DAT_211155ac)(1);
      }
      DAT_211155ac = (undefined4 *)0x0;
    }
  }
  if (DAT_211155b8 != (LPVOID)0x0) {
    sub_2110D4F4(DAT_211155b8);
    DAT_211155b8 = (LPVOID)0x0;
  }
  return 0;
}

