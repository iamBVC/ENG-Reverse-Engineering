/* sub_546040 @ 00546040   32 bytes */

int sub_546040(short param_1)

{
  if (DAT_006d9490 != 0) {
    return (int)((uint)*(ushort *)(DAT_006d9490 + 0x5e) * (int)param_1) >> 7;
  }
  return 0;
}

