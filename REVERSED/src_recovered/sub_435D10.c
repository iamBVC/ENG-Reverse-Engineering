/* The original nine stack arguments are integers. The decompiler reused their
 * slots for floating-point intermediates and incorrectly typed the interface. */

void sub_435D10(int sprite, int x, int y, int width, int height, uint color,
               char grayscale, char extra_pass, char alternate)
{
  static uint traced;
  int trace = traced++ < 3;
  ushort *description;
  float *vertices;
  uint *node;
  uint mode, blend, flags;
  int texture, index, half_height, pass;
  float left, right, top, bottom, u0, u1, v0, v1, delta, span;

  if (trace) fprintf(stderr, "[text] glyph=%d xy=%d/%d size=%d/%d clip=%g/%g/%g/%g\n",
                     sprite, x, y, width, height, (double)DAT_005ff718,
                     (double)DAT_005ff71c, (double)DAT_005ff720, (double)_DAT_005ff724);

  if (sprite == -1 || width == 0 || height == 0)
    return;
  description = (ushort *)(DAT_00581154 + sprite * 20);
  texture = (int)((byte *)DAT_0058114c +
                  (int)*(signed char *)((byte *)description + 2) * 32);
  index = ((*description >> 8) & 7) * 5 + ((*description >> 12) & 7);
  if (alternate == 0) {
    mode = (&DAT_00573ef8)[index * 3];
    blend = (&DAT_00573efc)[index * 3];
  }
  else {
    mode = (&DAT_005740a0)[index * 3];
    blend = (&DAT_005740a4)[index * 3];
  }
  vertices = (float *)sub_41ED90(128);
  if (vertices == (float *)0)
    return;
  if (DAT_005833f0 == 0 && (color & 0xf0f0f0) == 0xf0f0f0) {
    x -= 2; y -= 2; width += 4; height += 4;
  }
  left = (float)x * (float)DAT_00583374 * _DAT_0056e1dc;
  right = (float)(x + width) * (float)DAT_00583374 * _DAT_0056e1dc;
  top = (float)y * (float)DAT_00583378 * _DAT_0056e1d8;
  half_height = height / 2;
  bottom = (float)(y + half_height) * (float)DAT_00583378 * _DAT_0056e1d8;
  memcpy(&u0, description + 2, 4);
  memcpy(&u1, description + 4, 4);
  memcpy(&v0, description + 6, 4);
  memcpy(&v1, description + 8, 4);
  if (!(left < DAT_005ff71c && DAT_005ff718 < right &&
        top < _DAT_005ff724 && DAT_005ff720 < bottom))
    return;
  if (left < DAT_005ff718) {
    delta = DAT_005ff718 - left; span = right - left;
    left = DAT_005ff718;
    u0 += (u1 - u0) * delta / span;
  }
  if (DAT_005ff71c < right) {
    delta = DAT_005ff71c - right; span = right - left;
    right = DAT_005ff71c;
    u1 += (u1 - u0) * delta / span;
  }
  if (top < DAT_005ff720) {
    delta = DAT_005ff720 - top; span = bottom - top;
    top = DAT_005ff720;
    v0 += (v1 - v0) * delta / span;
  }
  if (_DAT_005ff724 < bottom) {
    v1 += (v1 - v0) * (_DAT_005ff724 - bottom) / (bottom - top);
    bottom = _DAT_005ff724;
  }
  for (index = 0; index < 4; ++index) {
    float *vertex = vertices + index * 8;
    vertex[0] = index == 0 || index == 3 ? left : right;
    vertex[1] = index < 2 ? top : bottom;
    vertex[2] = 0.0f; vertex[3] = 1.0f;
    ((uint *)vertex)[4] = color;
    ((uint *)vertex)[5] = 0;
    vertex[6] = index == 0 || index == 3 ? u0 : u1;
    vertex[7] = index < 2 ? v0 : v1;
  }
  flags = (blend * 4 | mode) << 12 | (grayscale != 0 ? 4 : 0) | 0x7b;
  /* The optional first pass precedes the ordinary pass in allocation order;
   * head insertion leaves the ordinary pass first in the submission queue. */
  for (pass = extra_pass != 0 ? 1 : 0; pass >= 0; --pass) {
    node = (uint *)sub_41ED90(32);
    if (node != (uint *)0) {
      node[0] = DAT_005f6ef8;
      node[1] = (uint)vertices; node[2] = 4;
      node[3] = 0; node[4] = 0; node[5] = texture; node[6] = 0;
      node[7] = flags | (pass != 0 ? 0x2000 : 0);
      DAT_005f6ef8 = (int)node;
      if (trace) fprintf(stderr, "[text] queued glyph texture=%08x vertices=%p\n", texture, vertices);
    }
  }
}
