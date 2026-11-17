/* Ghidra: 0043a110, near-plane polygon clipper.
 * The original reads a caller-stack slot that is already recovered as an
 * explicit plane argument by its x86 call site. */

#include "ghidra_shim.h"
#include "ghidra_globals.h"
#include <string.h>

static uint32_t clip43a110_color(uint32_t from, uint32_t to, float t)
{
  uint32_t result = 0;
  int scale = (int)(t * 65536.0f + 0.5f);
  unsigned shift;

  if (DAT_006d7c6c != 0 && DAT_006d7c6f != 0)
    return 0;

  for (shift = 0; shift < 32; shift += 8) {
    int a = (int)((from >> shift) & 0xff);
    int b = (int)((to >> shift) & 0xff);
    int value = a + ((b - a) * scale >> 16);

    if (DAT_006d7c6c == 0 && DAT_006d7c6b != 0 && shift != 24)
      continue;
    if (value < 0) value = 0;
    if (value > 255) value = 255;
    result |= (uint32_t)value << shift;
  }
  return result;
}

static void clip43a110_intersection(const float *from, const float *to,
                                    float from_distance, float to_distance,
                                    float sign, int axis, float *out)
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
  color = clip43a110_color(from_color, to_color, t);
  memcpy(&out[4], &color, sizeof(color));

  /* The original snaps the clipped coordinate to the exact homogeneous plane. */
  out[axis] = sign * out[3];
}

int sub_43A110(int plane, float *input, int count, float *output)
{
  float sign = (plane & 1) != 0 ? 1.0f : -1.0f;
  int axis = plane / 2;
  int out_count = 0;
  int i;

  if (input == 0 || output == 0 || count <= 0 || axis < 0 || axis > 2)
    return 0;

  for (i = 0; i < count; ++i) {
    int previous_index = i == 0 ? count - 1 : i - 1;
    const float *previous = input + previous_index * 8;
    const float *current = input + i * 8;
    float previous_distance = sign * previous[axis] - previous[3];
    float current_distance = sign * current[axis] - current[3];
    if (current_distance > DAT_0056e00c) {
      if (previous_distance < DAT_0056e00c) {
        clip43a110_intersection(previous, current, previous_distance,
                                current_distance, sign, axis,
                                output + out_count * 8);
        ++out_count;
      }
    } else {
      if (previous_distance > DAT_0056e00c &&
          current_distance < DAT_0056e00c) {
        clip43a110_intersection(current, previous, current_distance,
                                previous_distance, sign, axis,
                                output + out_count * 8);
        ++out_count;
      }
      memcpy(output + out_count * 8, current, 8 * sizeof(float));
      ++out_count;
    }
  }

  return out_count;
}
