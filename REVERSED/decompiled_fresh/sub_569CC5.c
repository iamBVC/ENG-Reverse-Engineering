/* sub_569CC5 @ 00569cc5   38 bytes */

byte sub_569CC5(uint param_1)

{
  if (DAT_006da8e0 <= param_1) {
    return 0;
  }
  return *(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 0x40;
}

