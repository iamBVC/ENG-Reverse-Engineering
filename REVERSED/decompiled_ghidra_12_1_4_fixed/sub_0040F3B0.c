/* sub_40F3B0 @ 0040f3b0   118 bytes */

void sub_40F3B0(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar1 = DAT_00582260;
  while ((piVar3 = piVar1, piVar1 = (int *)*piVar3, piVar1 != (int *)0x0 || (piVar3[1] == 0))) {
    if ((piVar3[0x1d] != 0) && ((piVar3[0x1d] & 0x80000000U) == 0)) {
      (**(code **)(*(int *)piVar3[2] + 0x20))((int *)piVar3[2]);
      piVar2 = (int *)piVar3[2];
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 8))(piVar2);
        piVar3[2] = 0;
      }
    }
    if ((*piVar3 != 0) && (piVar3[1] != 0)) {
      *(int *)(*piVar3 + 4) = piVar3[1];
      *(int *)piVar3[1] = *piVar3;
      *piVar3 = 0;
      piVar3[1] = 0;
    }
    if (piVar3 != (int *)0x0) {
      sub_40F430();
      sub_562941(piVar3);
    }
  }
  return;
}

