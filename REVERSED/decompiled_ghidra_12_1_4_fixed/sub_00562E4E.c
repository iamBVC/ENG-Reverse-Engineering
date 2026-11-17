/* sub_562E4E @ 00562e4e   45 bytes */

uint sub_562E4E(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_0057ca10) {
    uVar1 = sub_565AFC(param_1,0x80);
    return uVar1;
  }
  return (byte)PTR_DAT_0057c804[param_1 * 2] & 0x80;
}

