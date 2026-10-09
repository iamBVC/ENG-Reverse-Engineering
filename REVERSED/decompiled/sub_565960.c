/* sub_565960 @ 00565960   55 bytes */

uint sub_565960(uint param_1)

{
  uint uVar1;
  
  if (DAT_0057ca10 < 2) {
    uVar1 = (byte)PTR_DAT_0057c804[param_1 * 2] & 4;
  }
  else {
    uVar1 = sub_565AFC(param_1,4);
  }
  if (uVar1 == 0) {
    param_1 = (param_1 & 0xffffffdf) - 7;
  }
  return param_1;
}

