/* Restore the integer option and the FPU operands that the export lost at
 * __ftol calls. Texture UV spans determine the logical sprite dimensions. */

void sub_425D40(byte *record, uint option)
{
  ushort *sprite;
  byte *texture;
  float *vertices;
  uint *node;
  uint mode, opacity, index, red = 255, green = 255, blue = 255, alpha, color;
  uint table_index, normal_mode, normal_blend, alternate_mode, alternate_blend;
  int image, extra_pass = 0, grayscale = 1, pass, vertex;
  float width, height, left, right, top, bottom, u0, u1, v0, v1, delta, span;
  float scale_x, scale_y, factor;

  if (*(short *)record == 0)
    return;
  mode = option >> 1; opacity = record[8];
  image = DAT_005ff728 + *(int *)(record + 12) * 2;
  image += record[44] == 0 ? record[5] * 2 : record[record[5] * 2 + 47];
  if ((option & 1) != 0 && opacity == 0)
    ++image;
  sprite = (ushort *)(DAT_00581154 + image * 20);
  texture = (byte *)DAT_0058114c + (int)*(signed char *)((byte *)sprite + 2) * 32;
  table_index = ((*sprite >> 12) & 7) + ((*sprite >> 8) & 7) * 5;
  normal_mode = (&DAT_00573ef8)[table_index * 3];
  normal_blend = (&DAT_00573efc)[table_index * 3];
  alternate_mode = (&DAT_005740a0)[table_index * 3];
  alternate_blend = (&DAT_005740a4)[table_index * 3];
  memcpy(&u0, sprite + 2, 4); memcpy(&u1, sprite + 4, 4);
  memcpy(&v0, sprite + 6, 4); memcpy(&v1, sprite + 8, 4);
  width = *(int *)(record + 40) == 0 ?
          (u1 - u0) * *(int *)(texture + 4) :
          (float)(*(int *)(record + 40) - *(int *)(record + 20));
  height = (v1 - v0) * *(int *)(texture + 8) * 0.5f;
  switch (mode) {
  case 0: break;
  case 1: width *= 1.6f; break;
  case 10: width = 448.0f; height = 57.0f; break;
  case 11:
    if (*(int *)(record + 40) == 0) width *= 0.75f;
    height *= 0.75f; break;
  case 18:
    if (*(int *)(record + 40) == 0) width *= 0.5f;
    height *= 0.4f; break;
  case 19: width *= 0.8f; height *= 0.5f; break;
  case 20: width *= 0.375f; height *= 0.375f; break;
  default:
    if (mode < 10) { width *= mode; height *= mode; }
    else {
      factor = (float)pow(2.0, 11.0 - (double)mode);
      if (*(int *)(record + 40) == 0) width *= factor;
      height *= factor;
    }
  }
  alpha = record[0];
  if (opacity == 0) alpha = 255;
  else if (alpha < 128) alpha <<= 1;
  else if (alpha == 128) { alpha = 255; opacity = 0; }
  else if (alpha == 255) opacity = 0;
  if (*(byte *)(&DAT_00573f00 + table_index * 3) != 0)
    alpha = ((&DAT_00574280)[(*sprite >> 12) & 7] * alpha) >> 8;
  if (record[29] != 0) {
    red = record[30]; green = record[31]; blue = record[32];
    extra_pass = sub_40C510((byte *)&red, (byte *)&green, (byte *)&blue);
    grayscale = red == green && green == blue;
  }
  if (DAT_006d7c6f != 0 && alpha != 255) {
    red = red * alpha >> 8; green = green * alpha >> 8; blue = blue * alpha >> 8;
  }
  color = alpha << 24 | red << 16 | green << 8 | blue;
  vertices = (float *)sub_41ED90(extra_pass != 0 ? 256 : 128);
  if (vertices == (float *)0)
    return;
  scale_x = (float)DAT_00583374 * _DAT_0056e1dc;
  scale_y = (float)DAT_00583378 * _DAT_0056e1d8;
  left = (float)*(int *)(record + 20) * scale_x;
  right = left + width * scale_x;
  top = (float)*(int *)(record + 24) * scale_y;
  bottom = top + height * scale_y;
  left = (float)(int)left + 0.5f; right = (float)(int)right + 0.5f;
  top = (float)(int)top + 0.5f; bottom = (float)(int)bottom + 0.5f;
  if (record[35] != 0) { factor = u0; u0 = u1; u1 = factor; }
  if (record[36] != 0) { factor = v0; v0 = v1; v1 = factor; }
  if (left < 0) {
    delta = -left; span = right - left; left = 0;
    u0 += delta * (u1 - u0) / span;
  }
  if (DAT_00583374 < right) {
    delta = (float)DAT_00583374 - right; span = right - left;
    right = (float)DAT_00583374; u1 += delta * (u1 - u0) / span;
  }
  if (top < 0) {
    v0 += -top * (v1 - v0) / (bottom - top); top = 0;
  }
  if (DAT_00583378 < bottom) {
    v1 += ((float)DAT_00583378 - bottom) * (v1 - v0) / (bottom - top);
    bottom = (float)DAT_00583378;
  }
  if (bottom <= 0)
    return;
  for (vertex = 0; vertex < 4; ++vertex) {
    float *v = vertices + vertex * 8;
    v[0] = vertex == 0 || vertex == 3 ? left : right;
    v[1] = vertex < 2 ? top : bottom;
    v[2] = 0; v[3] = 1;
    ((uint *)v)[4] = color; ((uint *)v)[5] = 0;
    v[6] = vertex == 0 || vertex == 3 ? u0 : u1;
    v[7] = vertex < 2 ? v0 : v1;
  }
  if (extra_pass != 0) memcpy(vertices + 32, vertices, 128);
  if (opacity != 0) { normal_mode = alternate_mode; normal_blend = alternate_blend; }
  for (pass = extra_pass != 0 ? 1 : 0; pass >= 0; --pass) {
    node = (uint *)sub_41ED90(32);
    if (node != (uint *)0) {
      node[0] = DAT_005f6ef8; node[1] = (uint)(vertices + pass * 32);
      node[2] = 4; node[3] = 0; node[4] = 0; node[5] = (uint)texture; node[6] = 0;
      node[7] = (normal_blend * 4 | normal_mode) << 12 |
                (grayscale != 0 ? 4 : 0) | (pass != 0 ? 0x2000 : 0) | 0x7b;
      DAT_005f6ef8 = (int)node;
    }
  }
}
