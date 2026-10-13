/* Original 11-argument menu texture converter. Coordinates are integer stack
   arguments; the Ghidra export reused their slots for temporary float channels. */
uint sub_409640(int param_1,int param_2,ushort *param_3,int param_4,int param_5,
                int param_6,int param_7,int param_8,int param_9,char param_10,uint *param_11)
{
  int x, y, bytes, channel;
  uint masks[4], rgb_mask, black_bit = 0, pixel;
  uint low[3];
  float costs[3], values[4], scale[4];
  ushort source;
  byte *destination;
  ushort *input;
  int premultiplied = DAT_006d7c6f != 0;

  if (param_11[3] != 8 && param_11[3] != 16 && param_11[3] != 32) return 0;
  bytes = param_11[3] / 8;
  for (channel = 0; channel < 4; ++channel) {
    masks[channel] = param_11[4 + channel];
    scale[channel] = (float)(double)masks[channel];
  }
  rgb_mask = masks[0] | masks[1] | masks[2];
  if (DAT_006d7c6e != 0) {
    for (channel = 0; channel < 3; ++channel)
      low[channel] = -masks[channel] & masks[channel];
    costs[0] = ((float)low[0] / (float)masks[0]) * DAT_0056e138;
    costs[1] = ((float)low[1] / (float)masks[1]) * DAT_0056e134;
    costs[2] = ((float)low[2] / (float)masks[2]) * DAT_0056e130;
    black_bit = low[1];
    if (costs[0] < costs[1]) { black_bit = low[0]; costs[1] = costs[0]; }
    if (costs[2] <= costs[1]) black_bit = low[2];
  }
  for (y = 0; y < param_8; ++y) {
    input = param_3 + (param_6 + y) * param_4 + param_5;
    destination = (byte *)param_1 + (param_6 + y) * param_2 + param_5 * bytes;
    for (x = 0; x < param_7; ++x) {
      source = input[x];
      pixel = 0;
      if (source != 0) {
        values[0] = (float)((double)(source & 0x1f) * DAT_0056e11c);
        values[1] = (float)((double)(source & 0x3e0) * DAT_0056e124);
        values[2] = (float)((double)(source & 0x7c00) * DAT_0056e12c);
        values[3] = 1.0f;
        if ((source & 0x8000) && param_9 != 0) {
          switch (param_9) {
          case 1:
            values[3] = 0.5f;
            if (premultiplied)
              for (channel = 0; channel < 3; ++channel) values[channel] *= DAT_0056e158;
            break;
          case 2:
            values[3] = (float)((double)values[0] * DAT_0056e138 +
                               (double)values[1] * DAT_0056e134 +
                               (double)values[2] * DAT_0056e130);
            if (!premultiplied) sub_409510(&values[0], &values[1], &values[2], values[3]);
            if (values[3] > 1.0f) values[3] = 1.0f;
            break;
          case 3:
            values[3] = (float)((double)values[0] * DAT_0056e148 +
                               (double)values[1] * DAT_0056e14c +
                               (double)values[2] * DAT_0056e150);
            if (values[3] > 1.0f) values[3] = 1.0f;
            values[0] = values[1] = values[2] = 0.0f;
            break;
          case 4:
            values[3] = (float)((double)values[0] * DAT_0056e13c +
                               (double)values[1] * DAT_0056e140 +
                               (double)values[2] * DAT_0056e144);
            if (!premultiplied) sub_409510(&values[0], &values[1], &values[2], values[3]);
            break;
          }
        }
        for (channel = 0; channel < 4; ++channel)
          pixel |= (uint)(int64_t)((double)values[channel] * scale[channel]) & masks[channel];
        if (param_10 != 0 && (pixel & rgb_mask) == 0)
          pixel = (pixel & ~rgb_mask) | black_bit;
      }
      if (bytes == 1) destination[x] = (byte)pixel;
      else if (bytes == 2) ((ushort *)destination)[x] = (ushort)pixel;
      else ((uint *)destination)[x] = pixel;
    }
  }
  return 1;
}

