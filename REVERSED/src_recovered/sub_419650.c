#include <stdio.h>

/* sub_419650 @ 00419650. Keep the Ghidra control flow and capture each
 * initialization boundary while tracking the main-menu camera target.
 */
undefined4 sub_419650(void)
{
  DAT_005863fc = 0;
  DAT_005846b4 = 0;
  DAT_0058470c = 0;
  fprintf(stderr, "[camera-init-stage] enter sub_419650 state=%d target=%d/%d/%d\n",
          DAT_005846e4, DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  if ((code *)(&PTR_sub_426500_00578f7c)[DAT_005846e4] != (code *)0x0) {
    (*(code *)(&PTR_sub_426500_00578f7c)[DAT_005846e4])();
    fprintf(stderr, "[camera-init-stage] after state callback target=%d/%d/%d\n",
            DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  }
  sub_438180();
  fprintf(stderr, "[camera-init-stage] after sub_438180 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_424B60(DAT_006da330 & 0x800,1,0x3c23d70a,0x40a00000);
  fprintf(stderr, "[camera-init-stage] after sub_424B60 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_439600();
  fprintf(stderr, "[camera-init-stage] after sub_439600 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_435CE0();
  fprintf(stderr, "[camera-init-stage] after sub_435CE0 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_40D920();
  fprintf(stderr, "[camera-init-stage] after sub_40D920 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_4280C0();
  fprintf(stderr, "[camera-init-stage] after sub_4280C0 %d/%d/%d\n",
          DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  _DAT_0058471c = 0x100;
  sub_4060A0();
  sub_4195D0();
  sub_41D330();
  return 1;
}
