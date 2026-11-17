/* sub_547100 @ 00547100   225 bytes */

void sub_547100(undefined4 *param_1)

{
  int iVar1;
  
  if (DAT_006d9490 != 0) {
    *param_1 = 0;
    if (param_1[0x14] != 0) {
      sub_562941(param_1[0x14]);
      param_1[0x14] = 0;
    }
    if (param_1[0x13] != 0) {
      sub_562941(param_1[0x13]);
      param_1[0x13] = 0;
    }
    if (param_1[0x13] != 0) {
      sub_562941(param_1[0x13]);
      param_1[0x13] = 0;
    }
    if (param_1[2] != 0) {
      sub_562941(param_1[2]);
      param_1[2] = 0;
    }
    if (param_1[0x12] != 0) {
      sub_5628BC(param_1[0x12]);
      param_1[0x12] = 0;
    }
    if (param_1[0x11] != 0) {
      iVar1 = 0;
      do {
        if (*(int *)(iVar1 + param_1[0x11]) != 0) {
          sub_5628BC(*(int *)(iVar1 + param_1[0x11]));
          *(undefined4 *)(iVar1 + param_1[0x11]) = 0;
        }
        iVar1 = iVar1 + 4;
      } while (iVar1 < 0xc);
      if (param_1[0x11] != 0) {
        sub_5628BC(param_1[0x11]);
        param_1[0x11] = 0;
      }
    }
    if (param_1 != (undefined4 *)0x0) {
      sub_562941(param_1);
    }
    DAT_006d9490 = 0;
    if (DAT_005834f4 != 0) {
      _AAL_Close3DProvider_4(DAT_005834f4);
    }
    _AAL_QuitDriver_4(1);
  }
  return;
}

