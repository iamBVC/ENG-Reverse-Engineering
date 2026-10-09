/* sub_545FE0 @ 00545fe0   32 bytes */

int sub_545FE0(short param_1)

{
  if (DAT_006d9490 != 0) {
    return (int)((uint)*(ushort *)(DAT_006d9490 + 0x5c) * (int)param_1) >> 7;
  }
  return 0;
}

