/* sub_547CE0 @ 00547ce0   61 bytes */

void sub_547CE0(undefined4 *param_1,int param_2,int param_3)

{
  param_1[4] = param_2;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  if (0 < param_3) {
    do {
      sub_546E10(param_2,param_1);
      param_2 = param_2 + 0x1c;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

