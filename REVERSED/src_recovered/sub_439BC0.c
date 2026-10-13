/* Original homogeneous-plane clipper, with x87 values expressed directly in C.
   Vertices contain eight DWORDs; colour at +0x10 is packed, not a float value. */

int sub_439BC0(int param_1,int param_2,int param_3,float *param_4)
{
  float *current = (float *)param_2;
  float *previous;
  float previous_distance;
  double distance, fraction;
  int axis = param_1 / 2;
  int sign = (param_1 & 1) ? 1 : -1;
  int count = 0, index, field, shift, fixed, delta;
  float *start, *end;
  uint start_color, end_color, color;
  int fields[6] = {0,1,2,3,6,7};

  if (param_3 <= 0) return 0;
  previous = current + (param_3 - 1) * 8;
  previous_distance = (float)((double)sign * previous[axis] - previous[3]);
  for (index = 0; index < param_3; ++index, current += 8) {
    distance = (double)sign * current[axis] - current[3];
    start = end = NULL;
    if (distance > 0.0 && previous_distance < 0.0f) {
      start = previous; end = current;
      fraction = previous_distance / (previous_distance - distance);
    } else if (distance < 0.0 && previous_distance > 0.0f) {
      start = current; end = previous;
      fraction = distance / (distance - previous_distance);
    }
    if (start != NULL) {
      for (field = 0; field < 6; ++field) {
        int component = fields[field];
        param_4[component] = (float)(((double)end[component] - start[component]) * fraction + start[component]);
      }
      fixed = (int)(fraction * DAT_0056e49c);
      memcpy(&start_color, start + 4, sizeof start_color);
      memcpy(&end_color, end + 4, sizeof end_color);
      color = 0;
      for (shift = 0; shift < 32; shift += 8) {
        delta = (int)((end_color >> shift) & 255) - (int)((start_color >> shift) & 255);
        color |= (uint)(((int)((start_color >> shift) & 255) + ((delta * fixed) >> 16)) & 255) << shift;
      }
      memcpy(param_4 + 4, &color, sizeof color);
      /* The original does not interpolate the specular field at +0x14. */
      param_4[axis] = (float)sign * param_4[3];
      param_4 += 8;
      ++count;
    }
    if (distance <= 0.0) {
      memcpy(param_4, current, 8 * sizeof(float));
      param_4 += 8;
      ++count;
    }
    previous = current;
    previous_distance = (float)distance;
  }
  return count;
}
