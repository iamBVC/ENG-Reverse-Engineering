#include <math.h>
#include <stdint.h>
#include <string.h>

/* The original __ftol helper uses FISTP qword with the active FPU rounding
   mode, then returns the low 32 bits. The x87 integer-indefinite qword has a
   zero low dword, so invalid conversions return zero here. */
static int groove_camera_fistp(double value)
{
  double rounded = nearbyint(value);
  int64_t converted;
  uint32_t low_dword;
  int32_t result;

  if (!(rounded >= -9223372036854775808.0 &&
        rounded < 9223372036854775808.0))
    return 0;
  converted = (int64_t)rounded;
  low_dword = (uint32_t)(uint64_t)converted;
  memcpy(&result, &low_dword, sizeof(result));
  return (int)result;
}

/* sub_41A920 @ 0041a920
 * The original stores a float vector into DAT_00581168+0x0c and copies those
 * float dwords into the camera globals. The Ghidra global is typed uint*, so
 * use the local float view for all three stores and loads.
 */
int sub_41A920(int *param_1,int param_2,ushort param_3)
{
  float *pfVar3;
  uint uVar4;
  int iVar8;
  int delta_x;
  int delta_y;
  int delta_z;
  int horizontal_radius;
  uint32_t squared_sum;
  int32_t scaled_square;
  int yaw;
  int64_t yaw_difference;
  double radius_value;
  double pitch_value;
  double yaw_value;
  static uint camera_trace_count;
  uint camera_trace_index = camera_trace_count++;

  delta_x = *(int *)(param_2 + 0x10) - param_1[4];
  delta_z = *(int *)(param_2 + 0x18) - param_1[6];
  delta_y = *(int *)(param_2 + 0x14) - param_1[5];

  /* Match the original's 32-bit IMUL/ADD/SAR sequence before its x87 sqrt. */
  squared_sum = (uint32_t)delta_x * (uint32_t)delta_x +
                (uint32_t)delta_z * (uint32_t)delta_z;
  scaled_square = (int32_t)squared_sum >> 12;
  radius_value = sqrt((double)scaled_square * DAT_0056e020) * DAT_0056e070;
  horizontal_radius = groove_camera_fistp(radius_value);

  _DAT_005848b8 = horizontal_radius;
  _DAT_005848bc = delta_x;
  _DAT_005848c0 = delta_y;
  _DAT_005848c4 = delta_z;

  /* The original uses FPATAN then FISTP for these 12-bit turn angles. */
  pitch_value = atan2((double)delta_y, (double)horizontal_radius) *
                -(double)DAT_0056e078;
  yaw_value = atan2((double)delta_x, (double)delta_z) *
              (double)DAT_0056e078;
  iVar8 = groove_camera_fistp(pitch_value);
  yaw = groove_camera_fistp(yaw_value);
  if (horizontal_radius < 0x180) {
    yaw_difference = (int64_t)yaw - (int64_t)param_1[1];
    if (yaw_difference < 0) yaw_difference = -yaw_difference;
    if (0x10 < yaw_difference) yaw = param_1[1];
  }
  uVar4 = (uint32_t)yaw;
  pfVar3 = (float *)(void *)DAT_00581168;
  pfVar3[3] = (float)param_1[4] * (float)_DAT_0056e020;
  pfVar3[4] = (float)param_1[5] * (float)_DAT_0056e020;
  pfVar3[5] = (float)-param_1[6] * (float)_DAT_0056e020;
  *pfVar3 = (float)-iVar8 * (float)_DAT_0056e018;
  pfVar3[1] = (float)(int)(uVar4 ^ 0x800) * (float)_DAT_0056e018;
  pfVar3[2] = (float)(int)(short)(param_3 ^ 0x800) * (float)_DAT_0056e018;
  if (camera_trace_index < 3) {
    fprintf(stderr,
            "[camera-update] call=%u state=%u base=%p target=%p pos=%d/%d/%d target-pos=%d/%d/%d radius=%d pitch=%d yaw=%d scale=%.6f angle-scale=%.6f input-pos=%.3f/%.3f/%.3f clip-near-far=%.6f/%.6f\n",
            camera_trace_index + 1, DAT_005846e4, (void *)param_1, (void *)param_2,
            param_1[4], param_1[5], param_1[6],
            *(int *)(param_2 + 0x10), *(int *)(param_2 + 0x14), *(int *)(param_2 + 0x18),
            horizontal_radius, iVar8, yaw,
            (double)_DAT_0056e020, (double)_DAT_0056e018,
            (double)pfVar3[3], (double)pfVar3[4], (double)pfVar3[5],
            (double)pfVar3[6], (double)pfVar3[7]);
    fprintf(stderr,
            "[camera-source] override=%08x data=%08x global-target=%d/%d/%d",
            DAT_0057f8bc, (uint32_t)DAT_0057f854,
            DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
    if (DAT_0057f8bc != 0 && DAT_0057f854 != 0) {
      fprintf(stderr, " data-target=%d/%d/%d",
              *(int *)(DAT_0057f854 + 8),
              *(int *)(DAT_0057f854 + 0xc),
              *(int *)(DAT_0057f854 + 0x10));
    }
    fputc('\n', stderr);
  }
  sub_402960(pfVar3);
  _DAT_006d8400 = pfVar3[3];
  _DAT_006d8404 = pfVar3[4];
  _DAT_006d8408 = pfVar3[5];
  *param_1 = iVar8;
  param_1[1] = uVar4;
  param_1[2] = 0;
  if (DAT_006d9e28 != 0) {
    *(int *)(DAT_006d9e28 + 0x20) = iVar8 << 0xc;
    *(int *)(DAT_006d9e28 + 0x24) = param_1[1] << 0xc;
    *(int *)(DAT_006d9e28 + 0x28) = param_1[2] << 0xc;
  }
  return 0;
}
