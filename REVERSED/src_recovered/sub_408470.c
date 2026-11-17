/* Restore the RGB555 channel scaling omitted from the Ghidra pseudo-C. */
int sub_408470(int destination, int destination_pitch, int source, int source_pitch,
               int x, int y, int width, int height, unsigned int unused,
               char preserve_black, short *format)
{
  unsigned int *format_words;
  unsigned int red_mask;
  unsigned int green_mask;
  unsigned int blue_mask;
  unsigned int alpha_mask;
  unsigned int rgb_mask;
  unsigned int transparent_rgb = 0;
  unsigned int bits_per_pixel;
  int bytes_per_pixel;
  int row;

  (void)unused;
  if (format == 0)
    return 0;
  format_words = (unsigned int *)format;
  bits_per_pixel = format_words[3];
  red_mask = format_words[4];
  green_mask = format_words[5];
  blue_mask = format_words[6];
  alpha_mask = format_words[7];
  rgb_mask = red_mask | green_mask | blue_mask;

  if (bits_per_pixel == 8)
    bytes_per_pixel = 1;
  else if (bits_per_pixel == 16)
    bytes_per_pixel = 2;
  else if (bits_per_pixel == 32)
    bytes_per_pixel = 4;
  else
    return 0;

  if (width <= 0 || height <= 0)
    return 1;
  if (destination == 0 || source == 0 || destination_pitch <= 0 ||
      source_pitch <= 0 || x < 0 || y < 0)
    return 0;

  if (DAT_006d7c6e != 0 && rgb_mask != 0) {
    unsigned int red_lsb = red_mask & (0U - red_mask);
    unsigned int green_lsb = green_mask & (0U - green_mask);
    unsigned int blue_lsb = blue_mask & (0U - blue_mask);
    float red_weight = red_mask ? (float)red_lsb / (float)red_mask * 0.21250001f : 1.0f;
    float green_weight = green_mask ? (float)green_lsb / (float)green_mask * 0.71539998f : 1.0f;
    float blue_weight = blue_mask ? (float)blue_lsb / (float)blue_mask * 0.072099999f : 1.0f;
    transparent_rgb = red_weight < green_weight ? red_lsb : green_lsb;
    if ((red_weight < green_weight ? red_weight : green_weight) >= blue_weight)
      transparent_rgb = blue_lsb;
  }

  for (row = 0; row < height; ++row) {
    const unsigned short *source_row =
        (const unsigned short *)(source + ((size_t)y + row) * (size_t)source_pitch * 2 +
                                 (size_t)x * 2);
    unsigned char *destination_row =
        (unsigned char *)(destination + ((size_t)y + row) * (size_t)destination_pitch +
                          (size_t)x * (size_t)bytes_per_pixel);
    int column;

    for (column = 0; column < width; ++column) {
      unsigned int packed = source_row[column];
      unsigned int converted = 0;

      if (packed != 0) {
        unsigned int red = (unsigned int)((float)(packed & 0x001fU) * 0.032258064f *
                                          (float)red_mask) & red_mask;
        unsigned int green = (unsigned int)((float)(packed & 0x03e0U) * 0.0010080645f *
                                            (float)green_mask) & green_mask;
        unsigned int blue = (unsigned int)((float)(packed & 0x7c00U) * 0.000031502015f *
                                           (float)blue_mask) & blue_mask;
        converted = red | green | blue | alpha_mask;
        if (preserve_black && (rgb_mask & converted) == 0)
          converted = (converted & ~rgb_mask) | transparent_rgb;
      }

      if (bytes_per_pixel == 1)
        destination_row[column] = (unsigned char)converted;
      else if (bytes_per_pixel == 2)
        ((unsigned short *)destination_row)[column] = (unsigned short)converted;
      else
        ((unsigned int *)destination_row)[column] = converted;
    }
  }
  return 1;
}
