/* _AAL_InitDriver@4 @ 211013c0   96 bytes */

int _AAL_InitDriver_4(int param_1)

{
  int iVar1;
  void *this;
  
                    /* 0x13c0  43  _AAL_InitDriver@4 */
  iVar1 = 0;
  if (DAT_211155ac == (undefined4 *)0x0) {
    this = operator_new(0xd0);
    if (this == (void *)0x0) {
      DAT_211155ac = (undefined4 *)0x0;
    }
    else {
      DAT_211155ac = sub_21104540(this,param_1);
    }
    iVar1 = sub_21104BF0(DAT_211155ac);
    if (iVar1 != 0) {
      if (DAT_211155ac != (undefined4 *)0x0) {
        (**(code **)*DAT_211155ac)(1);
      }
      DAT_211155ac = (undefined4 *)0x0;
    }
  }
  return iVar1;
}

