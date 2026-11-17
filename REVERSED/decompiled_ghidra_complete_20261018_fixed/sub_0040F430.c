/* sub_40F430 @ 0040f430   73 bytes */

void __fastcall sub_40F430(int *param_1)

{
  if (param_1[0x1b] != 0) {
    sub_562941(param_1[0x1b]);
  }
  if (param_1[0x1c] != 0) {
    sub_562941(param_1[0x1c]);
  }
  if ((*param_1 != 0) && (param_1[1] != 0)) {
    *(int *)(*param_1 + 4) = param_1[1];
    *(int *)param_1[1] = *param_1;
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}

