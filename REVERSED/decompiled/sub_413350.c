/* sub_413350 @ 00413350   58 bytes */

void __fastcall sub_413350(undefined4 *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  while (piVar1 != param_1 + 1) {
    if ((*piVar1 != 0) && (piVar1[1] != 0)) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      *piVar1 = 0;
      piVar1[1] = 0;
    }
    piVar1 = (int *)*param_1;
  }
  return;
}

