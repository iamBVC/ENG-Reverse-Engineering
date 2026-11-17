/* 004060C0-00406548: build preview geometry and submit each scene object.
 * The original reserves 0x1070 bytes of stack through __alloca_probe. Ghidra
 * rendered most of that local area as uninitialized in_stack_ arguments.
 */
int sub_4060C0(void)
{
  int scene = DAT_0057f858;
  int camera = DAT_0057f8b8;
  unsigned int object_index;
  float transform[6];
  float camera_matrix[16];
  float object_matrices[64][16]; /* original 0x1000-byte local region */
  float sx, sy, sz;

  for (object_index = 0; object_index < *(unsigned int *)(DAT_0057f858 + 4); ++object_index) {
    int object = DAT_0057f848 + object_index * 0x20;
    unsigned int vertex_index;
    unsigned int vertex_count = *(unsigned int *)(object + 0x10);
    unsigned int *packed = *(unsigned int **)(object + 0x14);
    float *vertices = *(float **)(*(int *)(scene + 0xc) + 0x70 + object_index * 0x8c);

    for (vertex_index = 0; vertex_index < vertex_count; ++vertex_index) {
      unsigned int value = packed[vertex_index];
      int x = ((int)(value << 22)) >> 20;
      int y = ((int)((value & 0xfffffcffU) << 12)) >> 20;
      int z = ((int)((value & 0xfff3ffffU) << 2)) >> 20;
      vertices[0] = (float)((double)x * DAT_0056e020);
      vertices[1] = (float)((double)y * DAT_0056e020);
      vertices[2] = (float)(-((double)z * DAT_0056e020));
      vertices += 6;
    }
  }

  transform[3] = (float)((double)*(int *)(camera + 0x30) * DAT_0056e020);
  transform[4] = (float)((double)*(int *)(camera + 0x34) * DAT_0056e020);
  transform[5] = (float)(-((double)*(int *)(camera + 0x38) * DAT_0056e020));
  transform[0] = (float)((double)*(int *)(camera + 0x20) * DAT_0056e058);
  transform[1] = (float)((double)*(int *)(camera + 0x24) * DAT_0056e058);
  transform[2] = (float)(-((double)*(int *)(camera + 0x28) * DAT_0056e058));

  sx = (float)((double)(*(int *)(camera + 0x60) ? *(int *)(camera + 0x60) : 1) * DAT_0056e020);
  sy = (float)((double)(*(int *)(camera + 0x64) ? *(int *)(camera + 0x64) : 1) * DAT_0056e020);
  sz = (float)((double)(*(int *)(camera + 0x68) ? *(int *)(camera + 0x68) : 1) * DAT_0056e020);
  sub_41E990(transform, sx, sy, sz, camera_matrix);

  for (object_index = 0; object_index < *(unsigned int *)(DAT_0057f858 + 4); ++object_index) {
    int object = DAT_0057f848 + object_index * 0x20;
    double px = (double)*(int *)(object + 0) * DAT_0056e020;
    double py = (double)*(int *)(object + 4) * DAT_0056e020;
    double pz = -((double)*(int *)(object + 8) * DAT_0056e020);
    unsigned int matrix_count = *(unsigned int *)(object + 0x18);
    unsigned int matrix_index;
    int object_mesh = *(int *)(DAT_0057f858 + 0xc) + object_index * 0x8c;

    transform[3] = (float)(camera_matrix[8] * pz + camera_matrix[4] * py + camera_matrix[0] * px + camera_matrix[12]);
    transform[4] = (float)(camera_matrix[9] * pz + camera_matrix[5] * py + camera_matrix[1] * px + camera_matrix[13]);
    transform[5] = (float)(camera_matrix[10] * pz + camera_matrix[6] * py + camera_matrix[2] * px + camera_matrix[14]);

    if (matrix_count != 0) {
      short *encoded = *(short **)(object + 0x1c);
      /* The original asset format must keep this count within the 64-entry
       * local array; the original routine performs no range check here. */
      for (matrix_index = 0; matrix_index < matrix_count; ++matrix_index) {
        float *out = object_matrices[matrix_index];
        short *m = encoded + matrix_index * 12;
        out[0] = (float)((double)m[0] * DAT_0056e020);
        out[1] = (float)((double)m[3] * DAT_0056e020);
        out[2] = (float)(-((double)m[6] * DAT_0056e020));
        out[3] = 0.0f;
        out[4] = (float)((double)m[1] * DAT_0056e020);
        out[5] = (float)((double)m[4] * DAT_0056e020);
        out[6] = (float)(-((double)m[7] * DAT_0056e020));
        out[7] = 0.0f;
        out[8] = (float)(-((double)m[2] * DAT_0056e020));
        out[9] = (float)(-((double)m[5] * DAT_0056e020));
        out[10] = (float)((double)m[8] * DAT_0056e020);
        out[11] = 0.0f;
        out[12] = (float)((double)m[9] * DAT_0056e020);
        out[13] = (float)((double)m[10] * DAT_0056e020);
        out[14] = (float)(-((double)m[11] * DAT_0056e020));
        out[15] = 1.0f;
      }
      sub_41FB30(object_mesh, (undefined4 *)transform, sx, sy, sz,
                 1.0f, 0, 1, (int)object_matrices, -1, -1, -1, 0, 0);
    } else {
      sub_41FB30(object_mesh, (undefined4 *)transform, sx, sy, sz,
                 1.0f, 0, *(int *)(object + 0x10) != 0, 0, -1, -1, -1, 0, 0);
    }
  }
  return 0; /* the sole original caller discards EAX */
}
