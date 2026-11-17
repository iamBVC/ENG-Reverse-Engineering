/* sub_413820 @ 00413820   124 bytes */

int * __thiscall sub_413820(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  if (param_1 != param_2) {
    if ((*param_2 == 0) || (piVar2 = param_2, param_2[1] == 0)) {
LAB_0041385a:
      param_2 = (int *)*param_1;
      goto LAB_0041386f;
    }
    do {
      if ((*piVar2 != 0) &&
         (((piVar1 = (int *)piVar2[1], piVar1 != (int *)0x0 && (*piVar1 != 0)) && (piVar1[1] == 0)))
         ) goto LAB_0041385a;
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != param_1);
  }
  piVar2 = (int *)param_1[1];
  if (*piVar2 == 0) {
    return piVar2;
  }
  if (piVar2[1] != 0) {
    return piVar2;
  }
  param_2 = (int *)*param_2;
LAB_0041386f:
  if ((*param_2 == 0) && (param_2[1] != 0)) {
    return (int *)0x0;
  }
  return param_2;
}

