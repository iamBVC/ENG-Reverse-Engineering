/* sub_547B60 @ 00547b60   150 bytes */

void sub_547B60(int *param_1,ushort *param_2)

{
  short sVar1;
  
  if (param_2 != (ushort *)0x0) {
    fpatan((float10)(*param_1 - DAT_005790b0 >> 6),(float10)(param_1[2] - DAT_005790b8 >> 6));
    sVar1 = __ftol();
    *param_2 = -sVar1 - (short)DAT_005790a4 & 0xfff;
  }
  __ftol();
  return;
}

