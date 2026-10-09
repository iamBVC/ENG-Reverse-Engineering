/* sub_564E72 @ 00564e72   53 bytes */

void sub_564E72(uint param_1,int *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    param_1 = sub_56461C(param_1,param_2);
  }
  else {
    *(undefined1 *)*param_2 = (undefined1)param_1;
    *param_2 = *param_2 + 1;
    param_1 = param_1 & 0xff;
  }
  if (param_1 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}

