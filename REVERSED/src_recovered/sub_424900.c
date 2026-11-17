/* 00424900: six screen-scaled vertices for two menu highlight triangles. */
void sub_424900(int x, int y, int unused, float current, float start, float end)
{
  float scale_x;
  float scale_y;
  float fade_height;
  float *vertices;
  unsigned int *bits;
  unsigned int *node;
  int anchor_x;
  int anchor_y;
  int fade_height_int;
  int width;
  int marker;
  int step;
  int i;

  (void)unused;
  scale_x = (float)DAT_00583378 * 0.004166666883975267f;
  anchor_x = (int)((float)(x - 10) * scale_x);
  scale_y = (float)DAT_00583374 * 0.001953125f;
  anchor_y = (int)((float)y * scale_y);
  fade_height = scale_y * 200.0f;
  fade_height_int = (int)fade_height;
  width = (int)(scale_x * 15.0f);
  step = (int)(((current - start) / (end - start)) * scale_y * 200.0f);
  marker = (int)((float)anchor_y - fade_height + (float)step);

  vertices = (float *)(uintptr_t)sub_41ED90(0x180);
  if (vertices == (float *)0) return;
  bits = (unsigned int *)vertices;
  for (i = 0; i < 3; ++i) {
    vertices[i * 8 + 3] = 1.0f;
    vertices[i * 8 + 5] = 0.0f;
  }

  vertices[0] = (float)(anchor_y - fade_height_int);
  vertices[1] = (float)(anchor_x + width);
  vertices[8] = (float)anchor_y;
  vertices[9] = (float)anchor_x;
  vertices[16] = (float)anchor_y;
  vertices[17] = (float)(anchor_x + width);
  bits[4] = 0x00B48C00;
  bits[12] = 0x00FFD74A;
  bits[20] = 0x00FFD74A;

  vertices[24] = (float)(marker - 3);
  vertices[25] = (float)anchor_x;
  vertices[32] = (float)(marker + 3);
  vertices[33] = (float)anchor_x;
  vertices[40] = (float)marker;
  vertices[41] = (float)(anchor_x + width);
  bits[28] = 0x00303080;
  bits[36] = 0x00303080;
  bits[44] = 0x00303080;

  node = (unsigned int *)(uintptr_t)sub_41ED90(0x20);
  if (node != (unsigned int *)0) {
    node[0] = (unsigned int)DAT_005f6ef8;
    node[1] = (unsigned int)(uintptr_t)(vertices + 24);
    node[2] = 3;
    node[3] = node[4] = node[5] = node[6] = 0;
    node[7] = 0x61;
    DAT_005f6ef8 = (int)(uintptr_t)node;
  }

  node = (unsigned int *)(uintptr_t)sub_41ED90(0x20);
  if (node != (unsigned int *)0) {
    node[0] = (unsigned int)DAT_005f6ef8;
    node[1] = (unsigned int)(uintptr_t)vertices;
    node[2] = 3;
    node[3] = node[4] = node[5] = node[6] = 0;
    node[7] = 0x61;
    DAT_005f6ef8 = (int)(uintptr_t)node;
  }
}

