/* Selected Ghidra export at 00417c50. */

undefined4 sub_417C50(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)*DAT_00583428;
  if (((((piVar1 == (int *)0x0) || (piVar2 = (int *)DAT_00583428[1], piVar2 == (int *)0x0)) ||
       (*piVar2 == 0)) || ((piVar2[1] != 0 || (*piVar1 != 0)))) || (piVar1[1] == 0)) {
    sub_546170(0,0xffffff80,8);
    DAT_006da2fc = 0xf000;
  }
  piVar1 = (int *)*DAT_00583428;
  if (((byte)DAT_005fcf08 & 0x80) == 0) {
    if (((piVar1 == (int *)0x0) || (DAT_00583428[1] == 0)) || ((*piVar1 != 0 || (piVar1[1] == 0))))
    {
      DAT_00583914 = 3;
      DAT_00583428 = piVar1;
      sub_417750();
      return 0;
    }
    while ((((*DAT_00583428 == 0 || (piVar1 = (int *)DAT_00583428[1], piVar1 == (int *)0x0)) ||
            (*piVar1 == 0)) || (piVar1[1] != 0))) {
      DAT_00583428 = (int *)DAT_00583428[1];
    }
  }
  else if (((piVar1 == (int *)0x0) || (piVar1 = (int *)DAT_00583428[1], piVar1 == (int *)0x0)) ||
          ((*piVar1 == 0 || (piVar2 = DAT_00583428, piVar1[1] != 0)))) {
    DAT_00583428 = (int *)DAT_00583428[1];
  }
  else {
    do {
      do {
        DAT_00583428 = piVar2;
        piVar2 = (int *)*DAT_00583428;
      } while (piVar2 == (int *)0x0);
    } while (((DAT_00583428[1] == 0) || (*piVar2 != 0)) || (piVar2[1] == 0));
  }
  DAT_00583914 = 3;
  sub_417750();
  return 0;
}

