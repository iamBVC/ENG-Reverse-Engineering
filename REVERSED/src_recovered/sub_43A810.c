/* Ghidra: 0043a810, four side-plane polygon clipper. */

#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include <string.h>

static uint32_t clip43a810_color(uint32_t from, uint32_t to, float t)
{
  uint32_t result = 0;
  int scale = (int)(t * 65536.0f + 0.5f);
  unsigned shift;

  for (shift = 0; shift < 32; shift += 8) {
    int a = (int)((from >> shift) & 0xff);
    int b = (int)((to >> shift) & 0xff);
    int value = a + ((b - a) * scale >> 16);
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    result |= (uint32_t)value << shift;
  }
  return result;
}

static void clip43a810_intersection(const float *from, const float *to,
                                    float from_distance, float to_distance,
                                    float factor, float offset, int axis,
                                    float *out)
{
  float t = from_distance / (from_distance - to_distance);
  uint32_t from_color, to_color, color;

  out[0] = from[0] + (to[0] - from[0]) * t;
  out[1] = from[1] + (to[1] - from[1]) * t;
  out[2] = from[2] + (to[2] - from[2]) * t;
  out[3] = from[3] + (to[3] - from[3]) * t;
  out[6] = from[6] + (to[6] - from[6]) * t;
  out[7] = from[7] + (to[7] - from[7]) * t;

  memcpy(&from_color, &from[4], sizeof(from_color));
  memcpy(&to_color, &to[4], sizeof(to_color));
  color = clip43a810_color(from_color, to_color, t);
  memcpy(&out[4], &color, sizeof(color));

  /* Keep the generated coordinate exactly on the plane after float rounding. */
  if (factor != 0.0f)
    out[axis] = offset / factor;
}

int sub_43A810(int plane, float *input, int count, float *output, float mode)
{
  float factor, offset;
  float threshold = DAT_0056e00c;
  uint8_t mode_low;
  int axis, out_count = 0, i;

  memcpy(&mode_low, &mode, sizeof(mode_low));
  if (mode_low == 0) {
    switch (plane) {
      case 0: factor = DAT_0056e418; offset = -(float)DAT_00583398; break;
      case 1: factor = DAT_0056e008; offset = (float)DAT_0058339c; break;
      case 2: factor = DAT_0056e008; offset = (float)DAT_005833a4; break;
      case 3: factor = DAT_0056e418; offset = -(float)DAT_005833a0; break;
      default: factor = mode; offset = mode; break;
    }
  } else {
    switch (plane) {
      case 0:
      case 3: factor = DAT_0056e418; offset = DAT_0056e00c; break;
      case 1: factor = DAT_0056e008; offset = DAT_00583390; break;
      case 2: factor = DAT_0056e008; offset = DAT_00583394; break;
      default: factor = mode; offset = mode; break;
    }
  }

  axis = plane / 2;
  if (input == 0 || output == 0 || count <= 0 || axis < 0 || axis > 1)
    return 0;

  for (i = 0; i < count; ++i) {
    int previous_index = i == 0 ? count - 1 : i - 1;
    const float *previous = input + previous_index * 8;
    const float *current = input + i * 8;
    float previous_distance = factor * previous[axis] - offset;
    float current_distance = factor * current[axis] - offset;
    if (current_distance > threshold) {
      if (previous_distance < threshold) {
        clip43a810_intersection(previous, current, previous_distance,
                                current_distance, factor, offset,
                                axis, output + out_count * 8);
        ++out_count;
      }
    } else {
      if (previous_distance > threshold && current_distance < threshold) {
        clip43a810_intersection(current, previous, current_distance,
                                previous_distance, factor, offset,
                                axis, output + out_count * 8);
        ++out_count;
      }
      memcpy(output + out_count * 8, current, 8 * sizeof(float));
      ++out_count;
    }
  }

  return out_count;
}
