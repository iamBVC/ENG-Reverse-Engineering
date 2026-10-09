/* sub_40C510 @ 0040c510   456 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_40C510(byte *param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  
  bVar1 = *param_1;
  if (((0x80 < bVar1) || (0x80 < *param_2)) || (0x80 < *param_3)) {
    if ((DAT_006d7c68 != '\0') && (DAT_005833e0 == '\0')) {
      return 1;
    }
    bVar1 = __ftol();
    *param_1 = bVar1;
    bVar1 = __ftol();
    *param_2 = bVar1;
    bVar1 = __ftol();
    *param_3 = bVar1;
    return 0;
  }
  if (bVar1 == 0x80) {
    bVar1 = 0xff;
  }
  else {
    bVar1 = bVar1 << 1;
  }
  *param_1 = bVar1;
  if (*param_2 == 0x80) {
    bVar1 = 0xff;
  }
  else {
    bVar1 = *param_2 << 1;
  }
  *param_2 = bVar1;
  if (*param_3 != 0x80) {
    *param_3 = *param_3 << 1;
    return 0;
  }
  *param_3 = 0xff;
  return 0;
}

