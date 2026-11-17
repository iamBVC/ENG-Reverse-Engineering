#include <stdio.h>

/* sub_54BAD0 @ 0054bad0
 * Keep the decompiled state update intact and report whether the direction
 * helper changes the target vector while deriving camera angles.
 */
void sub_54BAD0(void)
{
  int local_8;
  int local_4;
  static unsigned int trace_count;

  if (DAT_006d9e28 != 0) {
    DAT_006d9d20 = *(int *)(DAT_006d9e28 + 0x30);
    DAT_006d9d24 = *(int *)(DAT_006d9e28 + 0x34);
    DAT_006d9d28 = *(int *)(DAT_006d9e28 + 0x38);
    DAT_006d9d2c = *(int *)(DAT_006d9e28 + 0x3c);
    if (trace_count < 3) {
      fprintf(stderr, "[camera-state-before] target=%d/%d/%d entity=%d/%d/%d\n",
              DAT_006d9d80, DAT_006d9d84, DAT_006d9d88,
              DAT_006d9d20, DAT_006d9d24, DAT_006d9d28);
    }
    sub_404DB0(&DAT_006d9d80, &DAT_006d9d20, &local_8, &local_4);
    if (trace_count < 3) {
      fprintf(stderr, "[camera-state-after] target=%d/%d/%d angles=%d/%d\n",
              DAT_006d9d80, DAT_006d9d84, DAT_006d9d88, local_8, local_4);
      fflush(stderr);
      ++trace_count;
    }
    DAT_005790a4 = local_8 >> 0xc;
    _DAT_005790a0 = local_4 >> 0xc;
    DAT_005790b0 = DAT_006d9d20;
    DAT_005790b4 = DAT_006d9d24;
    DAT_005790b8 = DAT_006d9d28;
    _DAT_005790bc = DAT_006d9d2c;
  }
  return;
}
