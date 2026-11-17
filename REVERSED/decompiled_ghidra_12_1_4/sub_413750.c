/* sub_413750 @ 00413750   53 bytes */

void __fastcall sub_413750(int *param_1)

{
  sub_5628BC(param_1[2]);
  if ((*param_1 != 0) && (param_1[1] != 0)) {
    *(int *)(*param_1 + 4) = param_1[1];
    *(int *)param_1[1] = *param_1;
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}

