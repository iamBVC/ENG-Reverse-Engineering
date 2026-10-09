/* sub_562EA3 @ 00562ea3   46 bytes */

uint sub_562EA3(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_0057ca10) {
    uVar1 = sub_565AFC(param_1,0x107);
    return uVar1;
  }
  return *(ushort *)(PTR_DAT_0057c804 + param_1 * 2) & 0x107;
}

