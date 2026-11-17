/* sub_413510 @ 00413510   88 bytes */

int * __thiscall sub_413510(int *param_1,int *param_2)

{
  int *piVar1;
  
  if (param_1 == param_2) {
    while ((((*param_1 == 0 || (piVar1 = (int *)param_1[1], piVar1 == (int *)0x0)) || (*piVar1 == 0)
            ) || (piVar1[1] != 0))) {
      param_1 = (int *)param_1[1];
    }
  }
  else {
    param_1 = (int *)*param_1;
  }
  if (param_1 == param_2) {
    param_1 = (int *)*param_1;
  }
  if ((*param_1 == 0) && (param_1[1] != 0)) {
    return (int *)0x0;
  }
  return param_1;
}

