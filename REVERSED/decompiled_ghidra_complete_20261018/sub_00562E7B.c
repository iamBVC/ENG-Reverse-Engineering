/* sub_562E7B @ 00562e7b   40 bytes */

uint sub_562E7B(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_0057ca10) {
    uVar1 = sub_565AFC(param_1,8);
    return uVar1;
  }
  return (byte)PTR_DAT_0057c804[param_1 * 2] & 8;
}

