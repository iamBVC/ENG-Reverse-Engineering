/* sub_40F170 @ 0040f170   169 bytes */

void sub_40F170(char param_1)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 == '\0') {
    if (DAT_00582a7c != (int *)0x0) {
      (**(code **)(*DAT_00582a7c + 0x1c))(DAT_00582a7c);
    }
    piVar2 = DAT_00582260;
    if (DAT_00582a80 != (int *)0x0) {
      (**(code **)(*DAT_00582a80 + 0x1c))(DAT_00582a80);
      piVar2 = DAT_00582260;
    }
    for (; (*piVar2 != 0 || (piVar2[1] == 0)); piVar2 = (int *)*piVar2) {
      if (((piVar2[0x1d] & 0x80000000U) != 0) &&
         (iVar1 = (**(code **)(*(int *)piVar2[2] + 0x1c))((int *)piVar2[2]), iVar1 == 0)) {
        piVar2[0x1d] = piVar2[0x1d] & 0x7fffffff;
      }
    }
  }
  else {
    if (DAT_00582a7c != (int *)0x0) {
      (**(code **)(*DAT_00582a7c + 0x20))(DAT_00582a7c);
    }
    piVar2 = DAT_00582260;
    if (DAT_00582a80 != (int *)0x0) {
      (**(code **)(*DAT_00582a80 + 0x20))(DAT_00582a80);
      piVar2 = DAT_00582260;
    }
    for (; (*piVar2 != 0 || (piVar2[1] == 0)); piVar2 = (int *)*piVar2) {
      if ((piVar2[0x1d] != 0) && ((piVar2[0x1d] & 0x80000000U) == 0)) {
        (**(code **)(*(int *)piVar2[2] + 0x20))((int *)piVar2[2]);
        piVar2[0x1d] = piVar2[0x1d] | 0x80000000;
      }
    }
  }
  return;
}

