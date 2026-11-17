#include <stdio.h>

/* sub_54BA90 @ 0054ba90
 * Preserve the original camera defaults and record when initialization runs.
 * This trace distinguishes an initialization-order problem from a later write.
 */
void sub_54BA90(void)
{
  sub_41A440(0xc0);
  DAT_006d9d30 = 0x1000;
  DAT_005790a4 = 0;
  DAT_006d9d80 = 0;
  DAT_005790b4 = 0x1000;
  DAT_006d9d84 = 0x1000;
  DAT_006d9d88 = 0;
  fprintf(stderr, "[camera-init] target=%d/%d/%d base=%d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88,
          DAT_005790b0, DAT_005790b4, DAT_005790b8);
  fflush(stderr);
}
