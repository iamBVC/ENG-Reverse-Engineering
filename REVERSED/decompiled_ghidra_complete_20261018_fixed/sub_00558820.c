/* sub_558820 @ 00558820   94 bytes */

void sub_558820(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  if (*(char *)(param_1 + 5) != '\0') {
    sub_558C30(param_1);
  }
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  DAT_005ff728 = 0;
  DAT_005846ec = 0;
  DAT_00584648 = 0;
  param_1[4] = 0;
  DAT_006da354 = 0;
  DAT_006da334 = 0;
  DAT_006da338 = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  return;
}

