/* sub_5476C0 @ 005476c0   70 bytes */

void sub_5476C0(int *param_1,int param_2)

{
  int *piVar1;
  
  if ((param_1 != (int *)0x0) && (piVar1 = (int *)*param_1, piVar1 != (int *)0x0)) {
    do {
      if (param_2 == 0) {
        if (piVar1[3] == 0) goto LAB_005476e8;
      }
      else if (piVar1[3] != 0) {
LAB_005476e8:
        (*(code *)piVar1[2])(piVar1);
      }
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
    if (param_2 == 0) {
      sub_5475B0(param_1);
    }
  }
  return;
}

