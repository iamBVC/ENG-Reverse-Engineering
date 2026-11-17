/* Convert packed RGB555 texels to the ARGB words used for palette upload. */
static uint sub_4083A0_expand_channel(uint value)
{
  /* The original uses a truncated x87 multiply by a float reciprocal. */
  if (value == 31)
    return 254;
  return (value * 255) / 31;
}

int sub_4083A0(uint *destination, ushort *source, undefined4 unused, int count,
               char preserve_black)
{
  int i;

  if (count <= 0)
    return count;

  (void)unused;
  for (i = 0; i < count; ++i) {
    uint packed = source[i];
    uint red = sub_4083A0_expand_channel((packed >> 10) & 0x1f);
    uint green = sub_4083A0_expand_channel((packed >> 5) & 0x1f);
    uint blue = sub_4083A0_expand_channel(packed & 0x1f);
    uint color = 0xff000000 | (red << 16) | (green << 8) | blue;

    if (preserve_black && (color & 0x00ffffff) == 0)
      color = 0xff000001;
    destination[i] = color;
  }
  return 0;
}
