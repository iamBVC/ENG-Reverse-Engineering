/* sub_56A73D @ 0056a73d   61 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_56A73D(uint param_1)

{
  if ((param_1 < DAT_006da8e0) &&
     ((*(byte *)((&DAT_006da7e0)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    return *(undefined4 *)((&DAT_006da7e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 8);
  }
  DAT_006da368 = 0;
  _DAT_006da364 = 9;
  return 0xffffffff;
}

